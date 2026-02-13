using Market.Domain.Entities.Sales;

namespace Market.Application.Modules.Sales.Promotions.Queries.ListWithItems;

public sealed class ListPromotionsWithItemsQueryDto
{
    public required int Id { get; init; }
    public required string Title { get; set; } = string.Empty;
    public required string ImageUrl { get; set; } = string.Empty;
    public required string? TargetUrl { get; set; }
    public required bool IsActive { get; set; }
    public required DateTime? StartsAtUtc { get; set; }
    public required DateTime? EndsAtUtc { get; set; }
    public required int SortOrder { get; set; }

    public List<ListPromotionsWithItemsQueryDtoPromotionItem> PromotionItems { get; set; }


}
public sealed class ListPromotionsWithItemsQueryDtoPromotionItem
{
    public int Id { get; set; }
    public int ProductId { get; set; }
    public string ProductName { get; set; }
    public string ProductCategoryName { get; set; }
    public decimal DiscountPercent { get; set; } // 0.00 .. 1.00

}