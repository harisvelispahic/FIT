using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Products2.Commands.Status.Disable;

public sealed class DisableProduct2CommandHandler(
    IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<DisableProduct2Command, Unit>
{
    public async Task<Unit> Handle(DisableProduct2Command request, CancellationToken ct)
    {
        var cat = await ctx.Products2
            .FirstOrDefaultAsync(x => x.Id == request.Id, ct);

        if (cat is null)
        {
            throw new MarketNotFoundException($"Kategorija (ID={request.Id}) nije pronađena.");
        }

        if (!cat.IsEnabled) return Unit.Value; // idempotent

        cat.IsEnabled = false;

        await ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(ct);

        // await _bus.PublishAsync(new Product2DisabledV1IntegrationEvent(cat.Id, ...), ct);
        // await _cache.RemoveAsync(CacheKeys.CategoriesList, ct);

        return Unit.Value;
    }
}
