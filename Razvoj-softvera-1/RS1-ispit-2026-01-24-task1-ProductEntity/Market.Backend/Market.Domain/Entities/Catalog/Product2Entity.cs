using Market.Domain.Common;
using Market.Domain.Entities.Sales;

namespace Market.Domain.Entities.Catalog;

/// <summary>
/// Represents a product in the system.
/// </summary>
public class Product2Entity : BaseEntity
{
    public string Name { get; set; }
    public string? Description { get; set; }
    public decimal Price { get; set; }
    public int StockQuantity { get; set; }
    public int CategoryId { get; set; }
    public ProductCategoryEntity? Category { get; set; }
    public bool IsEnabled { get; set; }


    // Many-to-many: Users who favorited this product
    public ICollection<UserProductFavoriteEntity> FavoritedByUsers { get; private set; } = new List<UserProductFavoriteEntity>();


    ///// <summary>
    ///// Collection of order items.
    /////
    ///// **Napomena za studente:**

    ///// </summary>
    //public IReadOnlyCollection<OrderItemEntity> Items { get; set; } = new List<OrderItemEntity>();


    /// <summary>
    /// Single source of truth for technical/business constraints.
    /// Used in validators and EF configuration.
    /// </summary>
    public static class Constraints
    {
        public const int NameMaxLength = 150;

        public const int DescriptionMaxLength = 1000;
    }
}