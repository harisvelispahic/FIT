namespace Market.Application.Modules.Catalog.Promotions.Queries.List;

public sealed class ListPromotionsQuery : BasePagedQuery<ListPromotionsQueryDto>
{
    public string? Search { get; init; }
    public bool? OnlyActive { get; init; }
}
