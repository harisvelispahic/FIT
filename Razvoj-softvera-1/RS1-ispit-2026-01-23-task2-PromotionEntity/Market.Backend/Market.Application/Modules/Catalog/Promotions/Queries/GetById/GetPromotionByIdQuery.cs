namespace Market.Application.Modules.Sales.Promotions.Queries.GetById;

public sealed class GetPromotionByIdQuery : IRequest<GetPromotionByIdQueryDto>
{
    public int Id { get; set; }
}
