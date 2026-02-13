using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.GetById;
public class GetProductCategories2ByIdQueryHandler(IAppDbContext context)
    : IRequestHandler<GetProductCategory2ByIdQuery, GetProductCategory2ByIdQueryDto>
{
    public async Task<GetProductCategory2ByIdQueryDto> Handle(GetProductCategory2ByIdQuery request, CancellationToken cancellationToken)
    {
        var q = context.ProductCategories2
            .Where(c => c.Id == request.Id);

        var dto = await q
            .Select(x => new GetProductCategory2ByIdQueryDto
            {
                Id = x.Id,
                Name = x.Name,
                IsEnabled = x.IsEnabled,
            })
            .FirstOrDefaultAsync(cancellationToken);

        if (dto == null)
        {
            throw new MarketNotFoundException($"Product category with Id {request.Id} not found.");
        }

        return dto;
    }
}

