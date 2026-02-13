namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Delete;

public class DeleteProductCategory2Command : IRequest<Unit>
{
    public required int Id { get; set; }
}
