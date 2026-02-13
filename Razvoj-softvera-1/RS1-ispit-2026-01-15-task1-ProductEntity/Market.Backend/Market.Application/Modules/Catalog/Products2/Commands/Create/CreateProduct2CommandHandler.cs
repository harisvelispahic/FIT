using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Products2.Commands.Create;

public class CreateProduct2CommandHandler(
    IAppDbContext context,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<CreateProduct2Command, int>
{
    public async Task<int> Handle(CreateProduct2Command request, CancellationToken cancellationToken)
    {
        var normalizedName = request.Name?.Trim();
        var normalizedDescription = request.Description?.Trim();


        if (string.IsNullOrWhiteSpace(normalizedName))
            throw new ValidationException("Name is required.");

        if (string.IsNullOrWhiteSpace(normalizedDescription))
            throw new ValidationException("Description is required.");

        // Check if a category with the same name already exists.
        bool exists = await context.ProductCategories
            .AnyAsync(x => x.Name == normalizedName, cancellationToken);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        var product = new Product2Entity
        {
            Name = request.Name!.Trim(),
            Description = request.Description!.Trim(),
            Price = request.Price,
            StockQuantity = 0,
            CategoryId = request.CategoryId,
            IsEnabled = true
        };

        context.Products2.Add(product);
        await context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(cancellationToken);

        return product.Id;
    }
}
