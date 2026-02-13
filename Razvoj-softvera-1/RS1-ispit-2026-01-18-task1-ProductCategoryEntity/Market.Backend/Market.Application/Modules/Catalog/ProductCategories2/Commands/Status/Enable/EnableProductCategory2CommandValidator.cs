namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Enable;

public sealed class EnableProductCategory2CommandValidator : AbstractValidator<EnableProductCategory2Command>
{
    public EnableProductCategory2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
