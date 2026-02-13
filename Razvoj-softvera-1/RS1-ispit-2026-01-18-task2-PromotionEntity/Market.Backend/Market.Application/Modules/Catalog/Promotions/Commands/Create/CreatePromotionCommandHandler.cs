
namespace Market.Application.Modules.Catalog.Promotions.Commands.Create;
public class CreatePromotionCommandHandler(IAppDbContext ctx)
    : IRequestHandler<CreatePromotionCommand, int>
{
    public async Task<int> Handle(CreatePromotionCommand request, CancellationToken ct)
    {
        #region Create promotion and set basic properties
        var promotion = new PromotionEntity
        {
            Title = request.Title,
            ImageUrl = request.ImageUrl,
            TargetUrl = request.TargetUrl,
            IsActive = request.IsActive,
            StartsAtUtc = request.StartsAtUtc,
            EndsAtUtc = request.EndsAtUtc,
            SortOrder = request.SortOrder,
        };
        ctx.Promotions.Add(promotion);
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

        #region Create promotion items and calculate totals

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

            var promotionItem = new PromotionItemEntity
            {
                Promotion = promotion,
                ProductId = product.Id,
                DiscountPercent = item.DiscountPercent
            };

            ctx.PromotionItems.Add(promotionItem);
        }
        #endregion

        await ctx.SaveChangesAsync(ct);

        return promotion.Id;
    }
}
