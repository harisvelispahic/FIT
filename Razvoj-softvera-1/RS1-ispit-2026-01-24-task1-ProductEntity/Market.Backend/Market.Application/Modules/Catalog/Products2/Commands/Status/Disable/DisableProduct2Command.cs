namespace Market.Application.Modules.Catalog.Products2.Commands.Status.Disable;

public sealed class DisableProduct2Command : IRequest<Unit>
{
    public required int Id { get; set; }
}
