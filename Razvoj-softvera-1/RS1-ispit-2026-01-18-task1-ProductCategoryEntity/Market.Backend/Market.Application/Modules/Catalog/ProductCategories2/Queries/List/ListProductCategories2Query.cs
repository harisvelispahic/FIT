namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.List;

public sealed class ListProductCategories2Query : BasePagedQuery<ListProductCategories2QueryDto>
{
    public string? Search { get; init; }
    public bool? OnlyEnabled { get; init; }
}
