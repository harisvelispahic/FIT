
namespace Market.Application.Modules.Catalog.Promotions.Queries.ListWithItems;
public class ListPromotionsQueryHandler(IAppDbContext ctx)
        : IRequestHandler<ListPromotionsWithItemsQuery, PageResult<ListPromotionsWithItemsQueryDto>>
{
    public async Task<PageResult<ListPromotionsWithItemsQueryDto>> Handle(ListPromotionsWithItemsQuery request, CancellationToken ct)
    {
        var q = ctx.Promotions.AsNoTracking();

        var searchTerm = request.Search?.Trim().ToLower() ?? string.Empty;

        if (!string.IsNullOrWhiteSpace(request.Search))
        {
            q = q.Where(x => x.Title.ToLower().Contains(searchTerm));
        }

        var projectedQuery = q.OrderBy(x => x.EndsAtUtc)
            .Select(x => new ListPromotionsWithItemsQueryDto
            {
                Id = x.Id,
                Title = x.Title,
                ImageUrl = x.ImageUrl,
                TargetUrl = x.TargetUrl,
                IsActive = x.IsActive,
                StartsAtUtc = x.StartsAtUtc,
                EndsAtUtc = x.EndsAtUtc,
                SortOrder = x.SortOrder,
                PromotionItems = x.PromotionItems.Select(pi => new ListPromotionsWithItemsQueryDtoPromotionItem
                {
                    Id = pi.Id,
                    ProductId = pi.ProductId,
                    ProductName = pi.Product!.Name,
                    ProductCategoryName = pi.Product!.Category!.Name,
                    DiscountPercent = pi.DiscountPercent
                }).ToList()
            });

        return await PageResult<ListPromotionsWithItemsQueryDto>.FromQueryableAsync(projectedQuery, request.Paging, ct);
    }
}
