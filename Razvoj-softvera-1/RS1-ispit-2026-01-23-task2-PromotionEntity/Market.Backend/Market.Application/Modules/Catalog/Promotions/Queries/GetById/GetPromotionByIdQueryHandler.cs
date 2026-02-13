using Market.Application.Modules.Sales.Promotions.Queries.ListWithItems;

namespace Market.Application.Modules.Sales.Promotions.Queries.GetById;

public sealed class GetPromotionByIdQueryHandler(IAppDbContext ctx, IAppCurrentUser currentUser)
        : IRequestHandler<GetPromotionByIdQuery, GetPromotionByIdQueryDto>
{

    public async Task<GetPromotionByIdQueryDto> Handle(GetPromotionByIdQuery request, CancellationToken ct)
    {
        var q = ctx.Promotions
            .Where(c => c.Id == request.Id);


        var dto = await q.OrderBy(x => x.EndsAtUtc)
            .Select(x => new GetPromotionByIdQueryDto
            {
                Id = x.Id,
                Title = x.Title,
                ImageUrl = x.ImageUrl,
                TargetUrl = x.TargetUrl,
                IsActive = x.IsActive,
                StartsAtUtc = x.StartsAtUtc,
                EndsAtUtc = x.EndsAtUtc,
                SortOrder = x.SortOrder,
                PromotionItems = x.PromotionItems
                .Select(pi => new GetPromotionByIdQueryDtoPromotionItem
                {
                    Id = pi.Id,
                    ProductId = pi.ProductId,
                    ProductName = pi.Product.Name,
                    ProductCategoryName = pi.Product.Category.Name,
                    DiscountPercent = pi.DiscountPercent
                }).ToList()
            }).FirstOrDefaultAsync(ct);

        if (dto == null)
        {
            throw new MarketNotFoundException($"Promotion with Id {request.Id} not found.");
        }

        return dto;
    }
}
