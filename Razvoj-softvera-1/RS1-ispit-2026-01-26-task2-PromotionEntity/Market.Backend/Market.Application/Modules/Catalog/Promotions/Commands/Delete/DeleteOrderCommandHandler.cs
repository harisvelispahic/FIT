using Market.Domain.Entities.Sales;
using Microsoft.EntityFrameworkCore;
using System.Threading;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;

public class DeletePromotionCommandHandler(IAppDbContext ctx)
    : IRequestHandler<DeletePromotionCommand, int>
{
    public async Task<int> Handle(DeletePromotionCommand request, CancellationToken ct)
    {
        var promotion = await ctx.Promotions
            .Where(x => x.Id == request.Id).FirstOrDefaultAsync();

        if(promotion is null)
            throw new MarketNotFoundException($"Promotion (ID={request.Id}) nije pronađen.");

        ctx.Promotions.Remove(promotion);

        var promotionItems = await ctx.PromotionItems
            .Where(pi => pi.PromotionId == request.Id)
            .ToListAsync(ct);

        ctx.PromotionItems.RemoveRange(promotionItems);

        await ctx.SaveChangesAsync(ct);


        return promotion.Id;
    }
}
