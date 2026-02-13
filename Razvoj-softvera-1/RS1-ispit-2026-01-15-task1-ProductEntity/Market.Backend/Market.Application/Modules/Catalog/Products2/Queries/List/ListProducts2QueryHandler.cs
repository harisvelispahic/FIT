namespace Market.Application.Modules.Catalog.Products2.Queries.List;

public sealed class ListProducts2QueryHandler(IAppDbContext ctx)
        : IRequestHandler<ListProducts2Query, PageResult<ListProducts2QueryDto>>
{
    public async Task<PageResult<ListProducts2QueryDto>> Handle(
        ListProducts2Query request, CancellationToken ct)
    {
        var q = ctx.Products2.AsNoTracking();

        if (!string.IsNullOrWhiteSpace(request.Search))
        {
            q = q.Where(x => x.Name.Contains(request.Search));
        }

        if (request.OnlyEnabled is not null)
            q = q.Where(x => x.IsEnabled == request.OnlyEnabled);

        var projectedQuery = q.OrderBy(x => x.Name)
            .Select(x => new ListProducts2QueryDto
            {
                Id = x.Id,
                Name = x.Name,
                Description = x.Description,
                Price = x.Price,
                StockQuantity = x.StockQuantity,
                CategoryId = x.CategoryId,
                CategoryName = x.Category.Name,
                IsEnabled = x.IsEnabled
            });

        return await PageResult<ListProducts2QueryDto>.FromQueryableAsync(projectedQuery, request.Paging, ct);
    }
}
