namespace Market.Application.Modules.Catalog.Promotions.Queries.GetById;

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
                PromotionItems = x.PromotionItems.Select(pi => new GetByIdPromotionQueryDtoPromotionItem
                {
                    Id = pi.Id,
                    ProductId = pi.ProductId,
                    DiscountPercent = pi.DiscountPercent,
                    Product = new GetByIdPromotionQueryDtoProduct
                    {
                        ProductId = pi.Product.Id,
                        ProductName = pi.Product.Name,
                        ProductCategoryName = pi.Product.Category.Name
                    }
                }).ToList()
            }).FirstOrDefaultAsync(ct);

        if (dto == null)
        {
            throw new MarketNotFoundException($"Promotion with Id {request.Id} not found.");
        }

        return dto;
    }
}
