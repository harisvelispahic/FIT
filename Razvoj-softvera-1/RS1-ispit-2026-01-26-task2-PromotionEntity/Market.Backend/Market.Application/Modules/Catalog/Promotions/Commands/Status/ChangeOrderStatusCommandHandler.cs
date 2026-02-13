using Market.Application.Modules.Catalog.Promotions.Commands.Status;
using Market.Domain.Entities.Sales;

namespace Market.Application.Modules.Catalog.Promotions.Commands.ChangeStatus;



/// <summary>
/// Handler for changing Promotion status
/// </summary>
public class ChangePromotionStatusCommandHandler(IAppDbContext db) : IRequestHandler<ChangePromotionStatusCommand>
{
    public async Task Handle(ChangePromotionStatusCommand request, CancellationToken ct)
    {
        var Promotion = await db.Promotions
            .FirstOrDefaultAsync(o => o.Id == request.Id, ct)
            ?? throw new MarketNotFoundException($"{nameof(PromotionEntity)}, {request.Id}");

        Promotion.IsActive = !Promotion.IsActive;

        await db.SaveChangesAsync(ct);
    }
}