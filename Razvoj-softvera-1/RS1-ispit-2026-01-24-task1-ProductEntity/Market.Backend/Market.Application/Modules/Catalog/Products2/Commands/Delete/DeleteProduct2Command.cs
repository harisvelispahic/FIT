namespace Market.Application.Modules.Catalog.Products2.Commands.Delete;

public class DeleteProduct2Command : IRequest<Unit>
{
    public required int Id { get; set; }
}
