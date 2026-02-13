
namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;
public class UpdatePromotionCommandHandler(IAppDbContext ctx)
    : IRequestHandler<UpdatePromotionCommand, int>
{
    public async Task<int> Handle(UpdatePromotionCommand request, CancellationToken ct)
    {
        #region Querying existing order and set basic properties
        var q = ctx.Promotions
            .Where(x => x.Id == request.Id);

        var promotion = await q
            .FirstOrDefaultAsync(ct);

        if (promotion is null)
            throw new MarketNotFoundException($"Orders (ID={request.Id}) nije pronađen.");

        promotion.Title = request.Title;
        promotion.ImageUrl = request.ImageUrl;
        promotion.TargetUrl = request.TargetUrl;
        promotion.IsActive = request.IsActive;
        promotion.StartsAtUtc = request.StartsAtUtc;
        promotion.EndsAtUtc = request.EndsAtUtc;
        promotion.SortOrder = request.SortOrder;
        #endregion

        #region Query existing order items

        List<PromotionItemEntity> exisingOrderItems = await ctx.PromotionItems
                   .Where(pi => pi.PromotionId == promotion.Id)
                   //.AsNoTracking() // ne smije biti AsNoTracking jer želimo update orderItema
                   .ToListAsync(ct); //<--- prihvatljivo za peformanse: jedan (1) sql upit za sve iteme

        Dictionary<int, PromotionItemEntity> exisingOrderItemsMap = exisingOrderItems.ToDictionary(x => x.Id); //mapa postojecih itema po ID-u

        #endregion

        #region Delete order items items that are not in the API request
        //todo: brisanje starih itema

        var itemsToDelete = exisingOrderItems
            .Where(pi => request.PromotionItems.All(ri => ri.Id != pi.Id))
            .ToList();

        ctx.PromotionItems.RemoveRange(itemsToDelete);

        #endregion

        #region Check if all items are deleted - auto cancel

        // Ako nema stavki u request-u, automatski prebaci na Cancelled status
        if (request.PromotionItems == null || request.PromotionItems.Count == 0)
        {
            promotion.IsActive = false;
            await ctx.SaveChangesAsync(ct);
            return promotion.Id;
        }

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

        #region Querying existing or create order items and calculate totals

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

            PromotionItemEntity? promotionItem = null;

            //jel insert
            if (item.Id == 0)
            {
                // insert logic
                promotionItem = new PromotionItemEntity
                {
                    Promotion = promotion,
                    ProductId = product.Id,
                    DiscountPercent = item.DiscountPercent
                };

                ctx.PromotionItems.Add(promotionItem);
            }
            else
            {
                //update logic

                //orderItem = orderItems
                //    .Where(oi => oi.Id == item.Id) // ovo je O(n2)
                //    .FirstOrDefault(); //<--- nije kriticno za peformanse: ovo nije sql upit !!

                promotionItem = exisingOrderItemsMap.GetValueOrDefault(item.Id); //<--- bolja performansa O(1) jer koristi dictionary

                if (promotionItem is null)
                {
                    throw new ValidationException($"Order item (ID={item.Id}) not found in order (ID={promotion.Id}).");
                }

                //orderItem.OrderId = order.Id; // ne moze se menjati
                promotionItem.ProductId = item.ProductId;//todo: dozvoliti menjanje proizvoda?
                promotionItem.DiscountPercent = item.DiscountPercent;
            }
        }
        #endregion

        await ctx.SaveChangesAsync(ct);

        return promotion.Id;
    }
}
