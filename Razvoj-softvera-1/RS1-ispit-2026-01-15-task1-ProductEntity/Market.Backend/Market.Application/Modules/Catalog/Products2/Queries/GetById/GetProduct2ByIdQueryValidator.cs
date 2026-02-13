using Market.Application.Modules.Catalog.Products2.Queries.GetById;

public sealed class GetProduct2ByIdQueryValidator : AbstractValidator<GetProduct2ByIdQuery>
{
    public GetProduct2ByIdQueryValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0).WithMessage("Id must be a positive value.");
    }
}