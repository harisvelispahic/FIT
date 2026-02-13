namespace Market.Application.Modules.Catalog.Promotions.Commands.Status.Enable;

public sealed class EnablePromotionCommand : IRequest<Unit>
{
    public required int Id { get; set; }
}
