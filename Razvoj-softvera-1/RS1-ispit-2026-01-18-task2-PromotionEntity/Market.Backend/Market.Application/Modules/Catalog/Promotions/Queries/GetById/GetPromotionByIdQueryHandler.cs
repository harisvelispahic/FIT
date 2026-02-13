
namespace Market.Application.Modules.Catalog.Promotions.Queries.GetById;
public class GetPromotionByIdQueryHandler(IAppDbContext ctx)
        : IRequestHandler<GetPromotionByIdQuery, GetPromotionByIdQueryDto>
{
    public async Task<GetPromotionByIdQueryDto> Handle(GetPromotionByIdQuery request, CancellationToken ct)
    {
        var q = ctx.Promotions
            .Where(c => c.Id == request.Id);


        var dto = await q.OrderBy(x => x.EndsAtUtc)
            .Select(x => new GetPromotionByIdQueryDto
            {
                Title = x.Title,
                ImageUrl = x.ImageUrl,
                TargetUrl = x.TargetUrl,
                IsActive = x.IsActive,
                StartsAtUtc = x.StartsAtUtc,
                EndsAtUtc = x.EndsAtUtc,
                SortOrder = x.SortOrder,
                PromotionItems = x.PromotionItems.Select(i => new GetPromotionByIdQueryDtoPromotionItem
                {
                    Id = i.Id,
                    ProductId = i.ProductId,
                    ProductName = i.Product!.Name,
                    ProductCategoryName = i.Product!.Category!.Name,
                    DiscountPercent = i.DiscountPercent
                }).ToList()
            }).FirstOrDefaultAsync(ct);

        if (dto == null)
        {
            throw new MarketNotFoundException($"Promotion with Id {request.Id} not found.");
        }

        return dto;
    }

}


