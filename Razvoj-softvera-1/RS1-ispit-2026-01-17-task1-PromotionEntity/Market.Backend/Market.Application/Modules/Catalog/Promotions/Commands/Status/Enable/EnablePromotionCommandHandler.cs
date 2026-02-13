using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Status.Enable;

public sealed class EnablePromotionCommandHandler(
    IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<EnablePromotionCommand, Unit>
{
    public async Task<Unit> Handle(EnablePromotionCommand request, CancellationToken ct)
    {
        var entity = await ctx.Promotions
            .FirstOrDefaultAsync(x => x.Id == request.Id, ct);

        if (entity is null)
            throw new MarketNotFoundException($"Promocija (ID={request.Id}) nije pronađena.");

        if (!entity.IsActive)
        {
            entity.IsActive = true;
            await ctx.SaveChangesAsync(ct);

            // Invalidate catalog cache
            await cacheVersionService.BumpVersionAsync(ct);
        }

        // If already enabled — nothing changes, idempotent
        return Unit.Value;
    }
}
