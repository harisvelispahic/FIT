namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Disable;

public sealed class DisableProductCategory2Command : IRequest<Unit>
{
    public required int Id { get; set; }
}
