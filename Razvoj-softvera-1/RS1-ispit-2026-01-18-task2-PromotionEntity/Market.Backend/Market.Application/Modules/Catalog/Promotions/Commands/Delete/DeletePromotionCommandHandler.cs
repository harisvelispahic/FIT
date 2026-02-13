
namespace Market.Application.Modules.Catalog.Promotions.Commands.Delete;
public class DeletePromotionCommandHandler(IAppDbContext context)
        : IRequestHandler<DeletePromotionCommand, Unit>
{
    public async Task<Unit> Handle(DeletePromotionCommand request, CancellationToken ct)
    {
        var promotion = await context.Promotions
            .Where(p => p.Id == request.Id)
            .FirstOrDefaultAsync(ct);

        if (promotion == null)
        {
            throw new MarketNotFoundException($"Promotion with Id {request.Id} not found.");
        }

        var promotionItems = await context.PromotionItems
            .Where(pi => pi.PromotionId == promotion.Id)
            .ToListAsync(ct);

        foreach (var item in promotionItems)
        {
            context.PromotionItems.Remove(item);
        }

        context.Promotions.Remove(promotion);
        await context.SaveChangesAsync(ct);

        return Unit.Value;
    }
}
