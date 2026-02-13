namespace Market.Application.Modules.Catalog.Products2.Commands.Update;

public sealed class UpdateProduct2Command : IRequest<Unit>
{
    [JsonIgnore]
    public int Id { get; set; }
    public required string Name { get; set; }
    public required string Description { get; set; }
    public required decimal Price { get; set; }
    public required int StockQuantity { get; set; }
    public required int CategoryId { get; set; }
    public required bool IsEnabled { get; set; }
}
