
namespace Market.Application.Modules.Catalog.Promotions.Commands.Create;
public class CreatePromotionCommand : IRequest<int>
{
    public string Title { get; set; }
    public string ImageUrl { get; set; }
    public string? TargetUrl { get; set; }
    public bool IsActive { get; set; }
    public DateTime? StartsAtUtc { get; set; }
    public DateTime? EndsAtUtc { get; set; }
    public int SortOrder { get; set; }
    public List<CreatePromotionCommandPromotionItem> PromotionItems { get; set; } = new List<CreatePromotionCommandPromotionItem>();
}

public class CreatePromotionCommandPromotionItem
{
    public int ProductId { get; set; }
    public decimal DiscountPercent { get; set; }

}
