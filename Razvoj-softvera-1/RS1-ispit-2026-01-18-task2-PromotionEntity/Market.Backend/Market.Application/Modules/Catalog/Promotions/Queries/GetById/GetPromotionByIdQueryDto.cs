
namespace Market.Application.Modules.Catalog.Promotions.Queries.GetById;
public class GetPromotionByIdQueryDto
{
    public required string Title { get; set; }
    public required string ImageUrl { get; set; }
    public required string? TargetUrl { get; set; }
    public required bool IsActive { get; set; }
    public required DateTime? StartsAtUtc { get; set; }
    public required DateTime? EndsAtUtc { get; set; }
    public required int SortOrder { get; set; }
    public required List<GetPromotionByIdQueryDtoPromotionItem> PromotionItems { get; set; }
}

public class GetPromotionByIdQueryDtoPromotionItem
{
    public required int Id { get; set; }
    public required int ProductId { get; set; }
    public required string ProductName { get; set; }
    public required string ProductCategoryName { get; set; }
    public required decimal DiscountPercent { get; set; }
}