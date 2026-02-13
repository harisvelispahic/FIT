using Market.Domain.Common;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Domain.Entities.Catalog;
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
}
