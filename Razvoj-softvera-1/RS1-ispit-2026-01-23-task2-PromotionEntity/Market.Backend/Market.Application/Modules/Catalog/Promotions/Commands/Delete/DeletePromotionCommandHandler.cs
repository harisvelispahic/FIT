
namespace Market.Application.Modules.Catalog.Promotions.Commands.Delete;
public class DeletePromotionCommandHandler(IAppDbContext ctx)
    : IRequestHandler<DeletePromotionCommand, int>
{
    public async Task<int> Handle(DeletePromotionCommand request, CancellationToken ct)
    {
        var promotion = await ctx.Promotions
            .Include(p => p.PromotionItems)
            .FirstOrDefaultAsync(p => p.Id == request.Id, ct);

        if (promotion == null)
        {
            throw new Exception($"Promotion with Id {request.Id} not found.");
        }

        foreach (var item in promotion.PromotionItems)
        {
            ctx.PromotionItems.Remove(item);
        }

        ctx.Promotions.Remove(promotion);
        await ctx.SaveChangesAsync(ct);

        return promotion.Id;
    }
}
