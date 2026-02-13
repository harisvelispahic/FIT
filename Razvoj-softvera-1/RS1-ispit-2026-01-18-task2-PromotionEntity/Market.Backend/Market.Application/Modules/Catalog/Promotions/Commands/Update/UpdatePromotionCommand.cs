using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;
public class UpdatePromotionCommand : IRequest<int>
{
    [JsonIgnore]
    public int Id { get; set; }
    public string Title { get; set; }
    public string ImageUrl { get; set; }
    public string? TargetUrl { get; set; }
    public bool IsActive { get; set; }
    public DateTime? StartsAtUtc { get; set; }
    public DateTime? EndsAtUtc { get; set; }
    public int SortOrder { get; set; }
    public List<UpdatePromotionCommandPromotionItem> PromotionItems { get; set; } = new List<UpdatePromotionCommandPromotionItem>();
}

public class UpdatePromotionCommandPromotionItem
{
    public int Id { get; set; }
    public int ProductId { get; set; }
    public decimal DiscountPercent { get; set; }

}


