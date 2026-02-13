using Market.Domain.Common;

namespace Market.Domain.Entities.Catalog;

public sealed class PromotionItemEntity : BaseEntity
{
    public int PromotionId { get; set; }
    public PromotionEntity? Promotion { get; set; }
    public int ProductId { get; set; }
    public ProductEntity? Product { get; set; }
    public decimal DiscountPercent { get; set; }

    public static class Constraints
    {
        public const int TitleMaxLength = 120;
        public const int ImageUrlMaxLength = 500;
        public const int TargetUrlMaxLength = 500;
    }
}
