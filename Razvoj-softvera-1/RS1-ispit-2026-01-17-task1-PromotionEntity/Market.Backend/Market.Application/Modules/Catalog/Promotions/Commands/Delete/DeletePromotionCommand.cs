namespace Market.Application.Modules.Catalog.Promotions.Commands.Delete;

public class DeletePromotionCommand : IRequest<Unit>
{
    public required int Id { get; set; }
}
