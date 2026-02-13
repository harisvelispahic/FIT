namespace Market.Application.Modules.Catalog.Products2.Queries.GetById;

public class GetProduct2ByIdQuery : IRequest<GetProduct2ByIdQueryDto>
{
    public int Id { get; set; }
}