namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.GetById;

public class GetProductCategory2ByIdQuery : IRequest<GetProductCategory2ByIdQueryDto>
{
    public int Id { get; set; }
}