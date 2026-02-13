
namespace Market.Application.Modules.Catalog.Promotions.Queries.List;
public class ListPromotionsQuery : BasePagedQuery<ListPromotionsQueryDto>
{
    public string? Search { get; init; }
    public bool? IsActive { get; init; }
}
