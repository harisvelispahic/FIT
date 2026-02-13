using Market.Domain.Entities.Sales;

namespace Market.Application.Modules.Catalog.Promotions.Queries.ListWithItems;

public sealed class ListPromotionsWithItemsQueryDto
{
    public required int Id { get; set; }
    public required string Title { get; set; }
    public required string ImageUrl { get; set; }
    public required string? TargetUrl { get; set; }
    public required bool IsActive { get; set; }
    public required DateTime? StartsAtUtc { get; set; }
    public required DateTime? EndsAtUtc { get; set; }
    public required int SortOrder { get; set; }

    public required List<ListPromotionsWithItemsQueryDtoPromotionItem> PromotionItems { get; set; } = [];

}
public sealed class ListPromotionsWithItemsQueryDtoPromotionItem
{
    public required int Id { get; set; }
    public required int ProductId { get; set; }
    public required ListPromotionsWithItemsQueryDtoProduct? Product { get; set; }
    public required decimal DiscountPercent { get; set; }
}

public class ListPromotionsWithItemsQueryDtoProduct
{
    public required int ProductId { get; set; }
    public required string ProductName { get; set; }
    public required string ProductCategoryName { get; set; }

}