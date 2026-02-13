using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;

public sealed class UpdatePromotionCommandHandler : IRequestHandler<UpdatePromotionCommand, Unit>
{
    private readonly IAppDbContext _ctx;
    private readonly ICatalogCacheVersionService _cacheVersionService;

    public UpdatePromotionCommandHandler(
        IAppDbContext ctx,
        ICatalogCacheVersionService cacheVersionService)
    {
        _ctx = ctx;
        _cacheVersionService = cacheVersionService;
    }

    public async Task<Unit> Handle(UpdatePromotionCommand request, CancellationToken ct)
    {
        var entity = await _ctx.Promotions
            .Where(x => x.Id == request.Id)
            .FirstOrDefaultAsync(ct);

        if (entity is null)
            throw new MarketNotFoundException($"Kategorija (ID={request.Id}) nije pronađena.");

        // Check for duplicate name (case-insensitive, except for the same ID)
        var exists = await _ctx.Promotions
            .AnyAsync(x => x.Id != request.Id && x.Title.ToLower() == request.Title.ToLower(), ct);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        entity.Title = request.Title.Trim();
        entity.ImageUrl = request.ImageUrl;
        entity.TargetUrl = request.TargetUrl;
        entity.IsActive = request.IsActive;
        entity.StartsAtUtc = request.StartsAtUtc;
        entity.EndsAtUtc = request.EndsAtUtc;
        entity.SortOrder = request.SortOrder;

        await _ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await _cacheVersionService.BumpVersionAsync(ct);

        return Unit.Value;
    }
}
