using Market.Application.Abstractions.Caching;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Delete;
public class DeleteProductCategory2CommandHandler
{
}
public class DeleteProductCommandHandler(
    IAppDbContext context,
    IAppCurrentUser appCurrentUser,
    ICatalogCacheVersionService cacheVersionService) : IRequestHandler<DeleteProductCategory2Command, Unit>
{
    public async Task<Unit> Handle(DeleteProductCategory2Command request, CancellationToken cancellationToken)
    {
        if (!appCurrentUser.IsAdmin)
            throw new MarketBusinessRuleException("123", "Samo admin moze brisati.");

        var productCategory = await context.ProductCategories2
            .FirstOrDefaultAsync(x => x.Id == request.Id, cancellationToken);

        if (productCategory is null)
            throw new MarketNotFoundException("Proizvod nije pronađena.");

        context.ProductCategories2.Remove(productCategory);
        await context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await cacheVersionService.BumpVersionAsync(cancellationToken);

        return Unit.Value;
    }
}

