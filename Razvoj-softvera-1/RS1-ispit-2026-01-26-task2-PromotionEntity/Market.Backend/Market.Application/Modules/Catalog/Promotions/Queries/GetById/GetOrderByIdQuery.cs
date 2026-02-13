namespace Market.Application.Modules.Catalog.Promotions.Queries.GetById;

public sealed class GetPromotionByIdQuery : IRequest<GetPromotionByIdQueryDto>
{
    public int Id { get; set; }
}
