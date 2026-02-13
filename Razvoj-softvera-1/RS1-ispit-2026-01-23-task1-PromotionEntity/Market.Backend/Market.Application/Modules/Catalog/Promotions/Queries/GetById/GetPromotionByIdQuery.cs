namespace Market.Application.Modules.Catalog.Promotions.Queries.GetById;

public class GetPromotionByIdQuery : IRequest<GetPromotionByIdQueryDto>
{
    public int Id { get; set; }
}