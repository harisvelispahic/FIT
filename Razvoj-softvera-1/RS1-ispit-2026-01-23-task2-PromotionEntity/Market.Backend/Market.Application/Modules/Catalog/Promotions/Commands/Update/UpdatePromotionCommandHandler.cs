using Market.Domain.Entities.Sales;

namespace Market.Application.Modules.Sales.Promotions.Commands.Update;

public class UpdatePromotionCommandHandler(IAppDbContext ctx)
    : IRequestHandler<UpdatePromotionCommand, int>
{
    public async Task<int> Handle(UpdatePromotionCommand request, CancellationToken ct)
    {
        #region Querying existing Promotion and set basic properties
        var q = ctx.Promotions
            .Where(x => x.Id == request.Id);

        var Promotion = await q
            .FirstOrDefaultAsync(ct);

        if (Promotion is null)
            throw new MarketNotFoundException($"Promotions (ID={request.Id}) nije pronađen.");

        Promotion.Title = request.Title;
        Promotion.ImageUrl = request.ImageUrl;
        Promotion.TargetUrl = request.TargetUrl;
        Promotion.IsActive = request.IsActive;
        Promotion.StartsAtUtc = request.StartsAtUtc;
        Promotion.EndsAtUtc = request.EndsAtUtc;
        Promotion.SortOrder = request.SortOrder;
        #endregion

        #region Query existing Promotion items

        List<PromotionItemEntity> exisingPromotionItems = await ctx.PromotionItems
                   .Where(oi => oi.PromotionId == Promotion.Id)
                   //.AsNoTracking() // ne smije biti AsNoTracking jer želimo update PromotionItema
                   .ToListAsync(ct); //<--- prihvatljivo za peformanse: jedan (1) sql upit za sve iteme

        Dictionary<int, PromotionItemEntity> exisingPromotionItemsMap = exisingPromotionItems.ToDictionary(x => x.Id); //mapa postojecih itema po ID-u

        #endregion

        #region Delete Promotion items items that are not in the API request
        //todo: brisanje starih itema

        var itemsToDelete = exisingPromotionItems
            .Where(oi => request.PromotionItems.All(ri => ri.Id != oi.Id))
            .ToList();

        ctx.PromotionItems.RemoveRange(itemsToDelete);

        #endregion

        #region Check if all items are deleted - auto cancel
        
        // Ako nema stavki u request-u, automatski prebaci na Cancelled status
        if (request.PromotionItems == null || request.PromotionItems.Count == 0)
        {
            Promotion.IsActive = false;
            await ctx.SaveChangesAsync(ct);
            return Promotion.Id;
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

        #region Querying existing or create Promotion items and calculate totals


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

            PromotionItemEntity? PromotionItem = null;

            //jel insert
            if (item.Id == 0)
            {
                // insert logic
                PromotionItem = new PromotionItemEntity
                {
                    Promotion = Promotion,
                    ProductId = item.ProductId,
                    DiscountPercent = item.DiscountPercent,
                };

                ctx.PromotionItems.Add(PromotionItem);
            }
            else
            {
                //update logic

                //PromotionItem = PromotionItems
                //    .Where(oi => oi.Id == item.Id) // ovo je O(n2)
                //    .FirstOrDefault(); //<--- nije kriticno za peformanse: ovo nije sql upit !!

                PromotionItem = exisingPromotionItemsMap.GetValueOrDefault(item.Id); //<--- bolja performansa O(1) jer koristi dictionary

                if (PromotionItem is null)
                {
                    throw new ValidationException($"Promotion item (ID={item.Id}) not found in Promotion (ID={Promotion.Id}).");
                }

                //PromotionItem.PromotionId = Promotion.Id; // ne moze se menjati
                PromotionItem.ProductId = item.ProductId;//todo: dozvoliti menjanje proizvoda?
                PromotionItem.DiscountPercent = item.DiscountPercent;
            }

        }
        #endregion

        await ctx.SaveChangesAsync(ct);

        return Promotion.Id;
    }
}
