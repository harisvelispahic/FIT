using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Disable;

public sealed class DisableProductCategory2CommandHandler(
    IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<DisableProductCategory2Command, Unit>
{
    public async Task<Unit> Handle(DisableProductCategory2Command request, CancellationToken ct)
    {
        var cat = await ctx.ProductCategories2
            .FirstOrDefaultAsync(x => x.Id == request.Id, ct);

        if (cat is null)
        {
            throw new MarketNotFoundException($"Kategorija (ID={request.Id}) nije pronađena.");
        }

        if (!cat.IsEnabled) return Unit.Value; // idempotent

        // Business rule: cannot disable if there are active products
        var hasActiveProducts = await ctx.Products
            .AnyAsync(p => p.CategoryId == cat.Id && p.IsEnabled, ct);

        if (hasActiveProducts)
        {
            throw new MarketBusinessRuleException("category.disable.blocked.activeProducts",
                $"Category {cat.Name} cannot be disabled because it contains active products.");
        }

        cat.IsEnabled = false;

        await ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(ct);

        // await _bus.PublishAsync(new ProductCategory2DisabledV1IntegrationEvent(cat.Id, ...), ct);
        // await _cache.RemoveAsync(CacheKeys.CategoriesList, ct);

        return Unit.Value;
    }
}
