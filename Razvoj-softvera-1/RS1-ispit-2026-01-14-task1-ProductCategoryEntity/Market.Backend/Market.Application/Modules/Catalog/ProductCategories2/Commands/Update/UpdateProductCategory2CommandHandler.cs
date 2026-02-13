using Market.Application.Abstractions.Caching;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Update;


public sealed class UpdateProductCategory2CommandHandler(
    IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<UpdateProductCategory2Command, Unit>
{
    public async Task<Unit> Handle(UpdateProductCategory2Command request, CancellationToken ct)
    {
        var entity = await ctx.ProductCategories2
            .Where(x => x.Id == request.Id)
            .FirstOrDefaultAsync(ct);

        if (entity is null)
            throw new MarketNotFoundException($"Product category (ID={request.Id}) nije pronađena.");

        // Check for duplicate name (case-insensitive, except for the same ID)
        var exists = await ctx.Products
            .AnyAsync(x => x.Id != request.Id && x.Name.ToLower() == request.Name.ToLower(), ct);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        var hasActiveProducts = await ctx.Products
            .AnyAsync(p => p.CategoryId == entity.Id && p.IsEnabled, ct);

        if (hasActiveProducts && !request.IsEnabled)
        {
            throw new MarketBusinessRuleException("category.disable.blocked.activeProducts",
                $"Category {entity.Name} cannot be disabled because it contains active products.");
        }

        entity.Name = request.Name.Trim();
        entity.IsEnabled = request.IsEnabled;

        await ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(ct);

        return Unit.Value;
    }
}
