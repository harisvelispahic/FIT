using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.List;
public class ListProductCategories2QueryHandler(IAppDbContext ctx)
    : IRequestHandler<ListProductCategories2Query, PageResult<ListProductCategories2QueryDto>>
{
    public async Task<PageResult<ListProductCategories2QueryDto>> Handle(
        ListProductCategories2Query request, CancellationToken ct)
    {

        var q = ctx.ProductCategories2.AsNoTracking();

        var searchTerm = request.Search?.Trim().ToLower() ?? string.Empty;

        if (!string.IsNullOrWhiteSpace(request.Search))
        {
            q = q.Where(x => x.Name.ToLower().Contains(searchTerm));
        }

        if (request.OnlyEnabled is not null)
            q = q.Where(x => x.IsEnabled == request.OnlyEnabled);

        var projectedQuery = q.OrderBy(x => x.Name)
            .Select(x => new ListProductCategories2QueryDto
            {
                Id = x.Id,
                Name = x.Name,
                IsEnabled = x.IsEnabled,
            });

        return await PageResult<ListProductCategories2QueryDto>.FromQueryableAsync(projectedQuery, request.Paging, ct);

    }
}
