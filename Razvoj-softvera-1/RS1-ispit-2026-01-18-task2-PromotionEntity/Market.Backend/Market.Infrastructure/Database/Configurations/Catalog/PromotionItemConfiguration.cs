namespace Market.Infrastructure.Database.Configurations.Catalog;

public sealed class PromotionItemConfiguration : IEntityTypeConfiguration<PromotionItemEntity>
{
    public void Configure(EntityTypeBuilder<PromotionItemEntity> builder)
    {
        builder.ToTable("PromotionItems");

        builder.Property(x => x.DiscountPercent)
            .HasPrecision(5, 2)      // e.g. 0.2500
            .IsRequired();

        // prevent duplicates: same product twice in same promotion
        builder.HasIndex(x => new { x.PromotionId, x.ProductId })
            .IsUnique();

        builder.HasOne(x => x.Promotion)
            .WithMany(p => p.PromotionItems)
            .HasForeignKey(x => x.PromotionId)
            .OnDelete(DeleteBehavior.Cascade);

        builder.HasOne(x => x.Product)
            .WithMany() // optional reverse nav if you add it
            .HasForeignKey(x => x.ProductId)
            .OnDelete(DeleteBehavior.Restrict);
        // (restrict is usually safer: don't delete product if it's in promotions)
    }
}
