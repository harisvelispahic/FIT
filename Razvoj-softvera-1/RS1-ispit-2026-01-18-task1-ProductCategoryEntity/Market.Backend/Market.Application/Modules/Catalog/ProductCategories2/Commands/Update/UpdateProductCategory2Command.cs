namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Update;

public sealed class UpdateProductCategory2Command : IRequest<Unit>
{
    [JsonIgnore]
    public int Id { get; set; }
    public required string Name { get; set; }
    public required bool IsEnabled { get; set; }
}
