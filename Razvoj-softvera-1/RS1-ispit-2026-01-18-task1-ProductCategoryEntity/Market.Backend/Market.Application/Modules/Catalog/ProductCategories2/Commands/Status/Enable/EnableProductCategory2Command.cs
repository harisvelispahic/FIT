namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Enable;

public sealed class EnableProductCategory2Command : IRequest<Unit>
{
    public required int Id { get; set; }
}
