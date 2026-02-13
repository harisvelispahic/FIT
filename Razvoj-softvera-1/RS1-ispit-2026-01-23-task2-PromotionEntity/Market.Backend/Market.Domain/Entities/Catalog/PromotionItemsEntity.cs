using Market.Domain.Common;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Domain.Entities.Catalog;
public sealed class PromotionItemEntity : BaseEntity
{
    public int PromotionId { get; set; }
    public PromotionEntity Promotion { get; set; } = null!;

    public int ProductId { get; set; }
    public ProductEntity Product { get; set; } = null!;

    public decimal DiscountPercent { get; set; } // 0.00 .. 1.00
}

