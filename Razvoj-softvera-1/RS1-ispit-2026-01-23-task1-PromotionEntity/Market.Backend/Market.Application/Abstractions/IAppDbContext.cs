using Market.Domain.Entities.Sales;

namespace Market.Application.Abstractions;

// Application layer
public interface IAppDbContext
{
    DbSet<ProductEntity> Products { get; }
    DbSet<ProductCategoryEntity> ProductCategories { get; }
    DbSet<PromotionEntity> Promotions { get; }
    DbSet<MarketUserEntity> Users { get; }
    DbSet<RefreshTokenEntity> RefreshTokens { get; }

    DbSet<OrderEntity> Orders{ get; }
    DbSet<OrderItemEntity> OrderItems { get; }

    Task<int> SaveChangesAsync(CancellationToken ct);
}
