namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Create;

public class CreateProductCategory2Command : IRequest<int>
{
    public required string Name { get; set; }
    public required bool IsEnabled { get; set; }
}
