namespace Market.Application.Modules.Catalog.Promotions.Queries.ListWithItems;

public sealed class ListPromotionsWithItemsQuery : BasePagedQuery<ListPromotionsWithItemsQueryDto>
{
    public string? Search { get; init; }
}
