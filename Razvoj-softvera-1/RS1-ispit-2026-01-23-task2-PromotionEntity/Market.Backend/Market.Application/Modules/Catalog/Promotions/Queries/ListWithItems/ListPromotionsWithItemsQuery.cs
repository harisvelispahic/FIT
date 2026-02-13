namespace Market.Application.Modules.Sales.Promotions.Queries.ListWithItems;

public sealed class ListPromotionsWithItemsQuery : BasePagedQuery<ListPromotionsWithItemsQueryDto>
{
    public string? Search { get; init; }
    public bool? IsActive { get; init; }
}
