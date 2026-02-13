namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.GetById;

public class GetProductCategory2ByIdQueryHandler(IAppDbContext context) : IRequestHandler<GetProductCategory2ByIdQuery, GetProductCategory2ByIdQueryDto>
{
    public async Task<GetProductCategory2ByIdQueryDto> Handle(GetProductCategory2ByIdQuery request, CancellationToken cancellationToken)
    {
        var category = await context.ProductCategories2
            .Where(c => c.Id == request.Id)
            .Select(x => new GetProductCategory2ByIdQueryDto
            {
                Id = x.Id,
                Name = x.Name,
                IsEnabled = x.IsEnabled
            })
            .FirstOrDefaultAsync(cancellationToken);

        if (category == null)
        {
            throw new MarketNotFoundException($"Product category with Id {request.Id} not found.");
        }

        return category;
    }
}