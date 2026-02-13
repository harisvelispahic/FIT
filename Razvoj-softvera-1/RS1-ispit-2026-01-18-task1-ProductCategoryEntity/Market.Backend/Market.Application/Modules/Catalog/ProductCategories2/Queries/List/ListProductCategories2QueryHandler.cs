namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.List;

public sealed class ListProductCategories2QueryHandler(IAppDbContext ctx)
        : IRequestHandler<ListProductCategories2Query, PageResult<ListProductCategories2QueryDto>>
{
    public async Task<PageResult<ListProductCategories2QueryDto>> Handle(
        ListProductCategories2Query request, CancellationToken ct)
    {
        var q = ctx.ProductCategories2.AsNoTracking();

        if (!string.IsNullOrWhiteSpace(request.Search))
        {
             q = q.Where(x => x.Name.Contains(request.Search));
        }

        if (request.OnlyEnabled is not null)
            q = q.Where(x => x.IsEnabled == request.OnlyEnabled);

        var projectedQuery = q.OrderBy(x => x.Name)
            .Select(x => new ListProductCategories2QueryDto
            {
                Id = x.Id,
                Name = x.Name,
                IsEnabled = x.IsEnabled
            });

        return await PageResult<ListProductCategories2QueryDto>.FromQueryableAsync(projectedQuery, request.Paging, ct);
    }
}
