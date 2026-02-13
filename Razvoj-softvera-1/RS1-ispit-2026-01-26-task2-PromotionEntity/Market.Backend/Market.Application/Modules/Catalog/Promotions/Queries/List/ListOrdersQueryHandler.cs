namespace Market.Application.Modules.Catalog.Promotions.Queries.List;

public sealed class ListPromotionsQueryHandler(IAppDbContext ctx, IAppCurrentUser currentUser)
        : IRequestHandler<ListPromotionsQuery, PageResult<ListPromotionsQueryDto>>
{

    public async Task<PageResult<ListPromotionsQueryDto>> Handle(ListPromotionsQuery request, CancellationToken ct)
    {
        var q = ctx.Promotions.AsNoTracking();


        var searchTerm = request.Search?.Trim().ToLower() ?? string.Empty;

        if (!string.IsNullOrWhiteSpace(request.Search))
        {
            q = q.Where(x => x.Title.ToLower().Contains(searchTerm));
        }

        if (request.IsActive is not null)
        {
            q = q.Where(x => x.IsActive == request.IsActive);
        }

        var projectedQuery = q.OrderBy(x => x.EndsAtUtc)
            .Select(x => new ListPromotionsQueryDto
            {
                Id = x.Id,
                Title = x.Title,
                ImageUrl = x.ImageUrl,
                TargetUrl = x.TargetUrl,
                IsActive = x.IsActive,
                StartsAtUtc = x.StartsAtUtc,
                EndsAtUtc = x.EndsAtUtc,
                SortOrder = x.SortOrder,
            });

        return await PageResult<ListPromotionsQueryDto>.FromQueryableAsync(projectedQuery, request.Paging, ct);
    }
}
