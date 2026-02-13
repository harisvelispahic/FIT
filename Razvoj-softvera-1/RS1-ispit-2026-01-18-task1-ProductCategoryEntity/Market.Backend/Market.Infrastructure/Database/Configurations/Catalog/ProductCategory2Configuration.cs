namespace Market.Infrastructure.Database.Configurations.Catelog;

public class ProductCategory2Configuration : IEntityTypeConfiguration<ProductCategory2Entity>
{
    public void Configure(EntityTypeBuilder<ProductCategory2Entity> builder)
    {
        builder
            .ToTable("ProductCategories2");

        builder
            .Property(x => x.Name)
            .IsRequired()
            .HasMaxLength(ProductCategory2Entity.Constraints.NameMaxLength);

        builder
            .Property(x => x.IsEnabled)
            .IsRequired();

    }
}
