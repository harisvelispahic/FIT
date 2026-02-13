using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Products2.Commands.Status.Enable;

public sealed class EnableProduct2CommandHandler(
    IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<EnableProduct2Command, Unit>
{
    public async Task<Unit> Handle(EnableProduct2Command request, CancellationToken ct)
    {
        var entity = await ctx.Products2
            .FirstOrDefaultAsync(x => x.Id == request.Id, ct);

        if (entity is null)
            throw new MarketNotFoundException($"Kategorija (ID={request.Id}) nije pronađena.");

        if (!entity.IsEnabled)
        {
            entity.IsEnabled = true;
            await ctx.SaveChangesAsync(ct);

            // Invalidate catalog cache
            await cacheVersionService.BumpVersionAsync(ct);
        }

        // If already enabled — nothing changes, idempotent
        return Unit.Value;
    }
}
