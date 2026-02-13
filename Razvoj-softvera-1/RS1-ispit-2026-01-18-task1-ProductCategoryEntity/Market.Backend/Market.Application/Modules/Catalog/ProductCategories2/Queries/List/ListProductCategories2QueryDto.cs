namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.List;

public sealed class ListProductCategories2QueryDto
{
    public required int Id { get; init; }
    public required string Name { get; init; }
    public required bool IsEnabled { get; init; }
}
