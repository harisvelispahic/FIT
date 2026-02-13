using Market.Application.Abstractions.Caching;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Create;
public class CreateProductCategory2CommandHandler(IAppDbContext ctx,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<CreateProductCategory2Command, int>
{
    public async Task<int> Handle(CreateProductCategory2Command request, CancellationToken ct)
    {
        var normalized = request.Name?.Trim();

        if (string.IsNullOrWhiteSpace(normalized))
            throw new ValidationException("Name is required.");

        // Check if a product with the same name already exists.
        bool exists = await ctx.Products
            .AnyAsync(x => x.Name == normalized, ct);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        var productCategory = new ProductCategory2Entity
        {
            Name = request.Name,
            IsEnabled = request.IsEnabled
        };

        ctx.ProductCategories2.Add(productCategory);
        await ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(ct);

        return productCategory.Id;
    }
}
