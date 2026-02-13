namespace Market.Application.Modules.Catalog.Promotions.Commands.Status.Disable;

public sealed class DisablePromotionCommand : IRequest<Unit>
{
    public required int Id { get; set; }
}
