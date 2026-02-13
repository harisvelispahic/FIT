using Market.Domain.Entities.Sales;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Create;

public class CreatePromotionCommandHandler(IAppDbContext ctx, IAppCurrentUser currentUser)
    : IRequestHandler<CreatePromotionCommand, int>
{
    public async Task<int> Handle(CreatePromotionCommand request, CancellationToken ct)
    {
        #region Create Promotion and set basic properties
        var Promotion = new PromotionEntity
        {
            Title = request.Title,
            ImageUrl = request.ImageUrl,
            TargetUrl = request.TargetUrl,
            IsActive = request.IsActive,
            StartsAtUtc = request.StartsAtUtc,
            EndsAtUtc = request.EndsAtUtc,
            SortOrder = request.SortOrder
        };
        ctx.Promotions.Add(Promotion);
        #endregion

        #region Load products from database and prepare a map

        // pokupiti sve id-ove proizvoda koji se naručuju
        List<int> productIds = request.PromotionItems.Select(ri => ri.ProductId).ToList(); // ne treba hashset jer filter se radi u bazi

        List<ProductEntity> products = await ctx.Products
            .Where(p => productIds.Contains(p.Id)) //<-- dorada nakon nastave za poboljsanje performansi: filtrirati samo proizvode koji su u request.Items
            .AsNoTracking()
            .ToListAsync(ct);

        Dictionary<int, ProductEntity> productsMap = products.ToDictionary(x => x.Id);
        #endregion

        #region Create Promotion items and calculate totals

        // za demo svrhe, svi proizvodi imaju 5% popusta
        decimal discountPercent = 0.05m;

        foreach (var item in request.PromotionItems)
        {
            ProductEntity? product = productsMap.GetValueOrDefault(item.ProductId); //<--- bolja performansa O(n) jer koristi dictionary

            if (product is null)
            {
                throw new ValidationException(message: $"Invalid productId {item.ProductId}.");
            }

            if (product.IsEnabled == false)
            {
                throw new ValidationException($"Product {product.Name} is disabled.");
            }

            var PromotionItem = new PromotionItemEntity
            {
                Promotion = Promotion,
                ProductId = item.ProductId,
                DiscountPercent = item.DiscountPercent,
            };

            ctx.PromotionItems.Add(PromotionItem);
        }
        #endregion

        await ctx.SaveChangesAsync(ct);

        return Promotion.Id;
    }
}