using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Create;

public class CreateProductCategory2CommandHandler(
    IAppDbContext context,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<CreateProductCategory2Command, int>
{
    public async Task<int> Handle(CreateProductCategory2Command request, CancellationToken cancellationToken)
    {
        var normalized = request.Name?.Trim();

        if (string.IsNullOrWhiteSpace(normalized))
            throw new ValidationException("Name is required.");

        // Check if a category with the same name already exists.
        bool exists = await context.ProductCategories2
            .AnyAsync(x => x.Name == normalized, cancellationToken);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        var category = new ProductCategory2Entity
        {
            Name = request.Name!.Trim(),
            IsEnabled = request.IsEnabled
        };

        context.ProductCategories2.Add(category);
        await context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(cancellationToken);

        return category.Id;
    }
}
