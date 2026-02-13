using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Products2.Commands.Create;

public class CreateProduct2CommandHandler(
    IAppDbContext context,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<CreateProduct2Command, int>
{
    public async Task<int> Handle(CreateProduct2Command request, CancellationToken cancellationToken)
    {
        var normalized = request.Name?.Trim();

        if (string.IsNullOrWhiteSpace(normalized))
            throw new ValidationException("Name is required.");

        // Check if a category with the same name already exists.
        bool exists = await context.Products2
            .AnyAsync(x => x.Name == normalized, cancellationToken);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        var product2 = new Product2Entity
        {
            Name = request.Name!.Trim(),
            Description = request.Description.Trim(),
            Price = request.Price,
            StockQuantity = request.StockQuantity,
            CategoryId = request.CategoryId,
            IsEnabled = request.IsEnabled
        };

        context.Products2.Add(product2);
        await context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(cancellationToken);

        return product2.Id;
    }
}
