using Market.Application.Abstractions.Caching;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Enable;
public class EnableProductCategory2CommandHandler(
    IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<EnableProductCategory2Command, Unit>
{
    public async Task<Unit> Handle(EnableProductCategory2Command request, CancellationToken ct)
    {
        var entity = await ctx.ProductCategories2
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
