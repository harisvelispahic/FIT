
namespace Market.Application.Modules.Catalog.Promotions.Queries.ListWithItems;
public class ListPromotionsWithItemsQuery : BasePagedQuery<ListPromotionsWithItemsQueryDto>
{
    public string? Search { get; init; }
}
