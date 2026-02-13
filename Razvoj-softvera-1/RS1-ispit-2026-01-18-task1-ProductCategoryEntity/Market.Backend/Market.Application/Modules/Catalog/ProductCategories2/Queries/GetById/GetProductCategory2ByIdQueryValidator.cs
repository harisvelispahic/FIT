using Market.Application.Modules.Catalog.ProductCategories2.Queries.GetById;

public sealed class GetProductCategory2ByIdQueryValidator : AbstractValidator<GetProductCategory2ByIdQuery>
{
    public GetProductCategory2ByIdQueryValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0).WithMessage("Id must be a positive value.");
    }
}