using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Status.Disable;

public sealed class DisablePromotionCommandHandler(
    IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<DisablePromotionCommand, Unit>
{
    public async Task<Unit> Handle(DisablePromotionCommand request, CancellationToken ct)
    {
        var cat = await ctx.Promotions
            .FirstOrDefaultAsync(x => x.Id == request.Id, ct);

        if (cat is null)
        {
            throw new MarketNotFoundException($"Promocija (ID={request.Id}) nije pronađena.");
        }

        if (!cat.IsActive) return Unit.Value; // idempotent


        cat.IsActive = false;

        await ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(ct);

        // await _bus.PublishAsync(new PromotionDisabledV1IntegrationEvent(cat.Id, ...), ct);
        // await _cache.RemoveAsync(CacheKeys.CategoriesList, ct);

        return Unit.Value;
    }
}
