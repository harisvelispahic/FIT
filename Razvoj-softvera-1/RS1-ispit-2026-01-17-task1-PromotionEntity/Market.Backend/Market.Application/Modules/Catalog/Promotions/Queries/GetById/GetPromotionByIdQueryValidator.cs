using Market.Application.Modules.Catalog.Promotions.Queries.GetById;

public sealed class GetPromotionByIdQueryValidator : AbstractValidator<GetPromotionByIdQuery>
{
    public GetPromotionByIdQueryValidator()
    {
        RuleFor(x => x.Id)
            .GreaterThan(0)
            .WithMessage("Id must be a positive value.");
    }
}