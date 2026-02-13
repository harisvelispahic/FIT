using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Products2.Commands.Status.Disable;

public sealed class DisableProduct2CommandHandler(
    IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<DisableProduct2Command, Unit>
{
    public async Task<Unit> Handle(DisableProduct2Command request, CancellationToken ct)
    {
        var product = await ctx.Products2
            .FirstOrDefaultAsync(x => x.Id == request.Id, ct);

        if (product is null)
        {
            throw new MarketNotFoundException($"Kategorija (ID={request.Id}) nije pronađena.");
        }

        if (!product.IsEnabled) return Unit.Value; // idempotent

        // Business rule: cannot disable if there are active products
        var hasActiveProducts = await ctx.Products
            .AnyAsync(p => p.CategoryId == product.Id && p.IsEnabled, ct);

        if (hasActiveProducts)
        {
            throw new MarketBusinessRuleException("category.disable.blocked.activeProducts",
                $"Category {product.Name} cannot be disabled because it contains active products.");
        }

        product.IsEnabled = false;

        await ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(ct);

        // await _bus.PublishAsync(new ProductCategoryDisabledV1IntegrationEvent(cat.Id, ...), ct);
        // await _cache.RemoveAsync(CacheKeys.CategoriesList, ct);

        return Unit.Value;
    }
}
