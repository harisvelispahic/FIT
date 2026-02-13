namespace Market.Application.Modules.Catalog.Products2.Commands.Status.Enable;

public sealed class EnableProduct2Command : IRequest<Unit>
{
    public required int Id { get; set; }
}
