using Market.Domain.Entities.Sales;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Status
{
    /// <summary>
    /// Command to change Promotion status
    /// </summary>
    public class ChangePromotionStatusCommand : IRequest
    {
        public int Id { get; set; }
    }
}
