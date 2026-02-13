namespace Market.Application.Modules.Catalog.Products2.Queries.List;

public sealed class ListProducts2Query : BasePagedQuery<ListProducts2QueryDto>
{
    public string? Search { get; init; }
    public bool? OnlyEnabled { get; init; }
}
