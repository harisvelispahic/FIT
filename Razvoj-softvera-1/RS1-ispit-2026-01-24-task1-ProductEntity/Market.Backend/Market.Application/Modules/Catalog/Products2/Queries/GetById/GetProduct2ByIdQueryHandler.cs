namespace Market.Application.Modules.Catalog.Products2.Queries.GetById;

public class GetProduct2ByIdQueryHandler(IAppDbContext context) : IRequestHandler<GetProduct2ByIdQuery, GetProduct2ByIdQueryDto>
{
    public async Task<GetProduct2ByIdQueryDto> Handle(GetProduct2ByIdQuery request, CancellationToken cancellationToken)
    {
        var category = await context.Products2
            .Include(p => p.Category)
            .Where(c => c.Id == request.Id)
            .Select(x => new GetProduct2ByIdQueryDto
            {
                Id = x.Id,
                Name = x.Name,
                Description = x.Description,
                Price = x.Price,
                StockQuantity = x.StockQuantity,
                CategoryId = x.CategoryId,
                CategoryName = x.Category.Name,
                IsEnabled = x.IsEnabled
            })
            .FirstOrDefaultAsync(cancellationToken);

        if (category == null)
        {
            throw new MarketNotFoundException($"Product category with Id {request.Id} not found.");
        }

        Console.WriteLine(category.CategoryId);

        return category;
    }
}