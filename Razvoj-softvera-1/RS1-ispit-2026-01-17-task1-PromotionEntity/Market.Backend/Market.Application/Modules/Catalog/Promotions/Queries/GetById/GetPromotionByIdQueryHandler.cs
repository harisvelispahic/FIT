namespace Market.Application.Modules.Catalog.Promotions.Queries.GetById;

public class GetPromotionByIdQueryHandler(IAppDbContext context) : IRequestHandler<GetPromotionByIdQuery, GetPromotionByIdQueryDto>
{
    public async Task<GetPromotionByIdQueryDto> Handle(GetPromotionByIdQuery request, CancellationToken cancellationToken)
    {
        var category = await context.Promotions
            .Where(c => c.Id == request.Id)
            .Select(x => new GetPromotionByIdQueryDto
            {
                Id = x.Id,
                Title = x.Title,
                ImageUrl = x.ImageUrl,
                TargetUrl = x.TargetUrl,
                IsActive = x.IsActive,
                StartsAtUtc = x.StartsAtUtc,
                EndsAtUtc = x.EndsAtUtc,
                SortOrder = x.SortOrder
            })
            .FirstOrDefaultAsync(cancellationToken);

        if (category == null)
        {
            throw new MarketNotFoundException($"Promotion with Id {request.Id} not found.");
        }

        return category;
    }
}