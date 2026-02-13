using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Create;

public class CreatePromotionCommandHandler(
    IAppDbContext context,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<CreatePromotionCommand, int>
{
    public async Task<int> Handle(CreatePromotionCommand request, CancellationToken cancellationToken)
    {
        var normalized = request.Title?.Trim();

        if (string.IsNullOrWhiteSpace(normalized))
            throw new ValidationException("Title is required.");

        // Check if a category with the same name already exists.
        bool exists = await context.Promotions
            .AnyAsync(x => x.Title == normalized, cancellationToken);

        if (exists)
        {
            throw new MarketConflictException("Title already exists.");
        }

        var category = new PromotionEntity
        {
            Title = normalized,
            ImageUrl = request.ImageUrl.Trim(),
            TargetUrl = request.TargetUrl?.Trim(),
            IsActive = request.IsActive,
            StartsAtUtc = request.StartsAtUtc,
            EndsAtUtc = request.EndsAtUtc,
            SortOrder = request.SortOrder
        };

        context.Promotions.Add(category);
        await context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(cancellationToken);

        return category.Id;
    }
}
