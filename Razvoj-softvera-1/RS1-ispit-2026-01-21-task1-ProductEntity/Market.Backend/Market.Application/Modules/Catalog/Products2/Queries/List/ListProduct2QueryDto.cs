namespace Market.Application.Modules.Catalog.Products2.Queries.List;

public sealed class ListProducts2QueryDto
{
    public required int Id { get; init; }
    public required string Name { get; set; }
    public required string Description { get; set; }
    public required decimal Price { get; set; }
    public required int StockQuantity { get; set; }
    public required int CategoryId { get; set; }
    public required string CategoryName { get; set; }
    public required bool IsEnabled { get; set; }
}
