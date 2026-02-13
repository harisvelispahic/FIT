namespace Market.Application.Modules.Sales.Promotions.Queries.List;

public sealed class ListPromotionsQuery : BasePagedQuery<ListPromotionsQueryDto>
{
    public string? Search { get; init; }
    public bool? IsActive { get; init; }
}
