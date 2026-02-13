namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;

public class UpdatePromotionCommand : IRequest<int>
{
    [JsonIgnore]
    public int Id { get; set; }
    public required string Title { get; set; }
    public required string ImageUrl { get; set; }
    public required string? TargetUrl { get; set; }
    public required bool IsActive { get; set; }
    public required DateTime? StartsAtUtc { get; set; }
    public required DateTime? EndsAtUtc { get; set; }
    public required int SortOrder { get; set; }

    public List<UpdatePromotionCommandPromotionItem> PromotionItems { get; set; } = [];
}

public class UpdatePromotionCommandPromotionItem
{
    public int Id { get; set; }
    public required int ProductId { get; set; }
    public required decimal DiscountPercent { get; set; }
}