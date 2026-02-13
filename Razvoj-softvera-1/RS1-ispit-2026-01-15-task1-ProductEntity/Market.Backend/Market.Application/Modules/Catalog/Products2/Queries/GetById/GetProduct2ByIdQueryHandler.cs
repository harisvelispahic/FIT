namespace Market.Application.Modules.Catalog.Products2.Queries.GetById;

public class GetProduct2ByIdQueryHandler(IAppDbContext context) : IRequestHandler<GetProduct2ByIdQuery, GetProduct2ByIdQueryDto>
{
    public async Task<GetProduct2ByIdQueryDto> Handle(GetProduct2ByIdQuery request, CancellationToken cancellationToken)
    {
        var product = await context.Products2
            .Where(c => c.Id == request.Id)
            .Select(x => new GetProduct2ByIdQueryDto
            {
                Id = x.Id,
                Name = x.Name,
                Description = x.Description,
                Price = x.Price,
                StockQuantity = x.StockQuantity,
                CategoryId=x.CategoryId,
                CategoryName = x.Category.Name,
                IsEnabled = x.IsEnabled
            })
            .FirstOrDefaultAsync(cancellationToken);

        if (product == null)
        {
            throw new MarketNotFoundException($"Product with Id {request.Id} not found.");
        }

        return product;
    }
}