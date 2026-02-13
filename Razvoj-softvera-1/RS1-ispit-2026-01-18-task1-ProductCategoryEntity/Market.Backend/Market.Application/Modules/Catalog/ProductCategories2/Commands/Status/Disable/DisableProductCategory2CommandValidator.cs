namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Disable;

public sealed class DisableProductCategory2CommandValidator : AbstractValidator<DisableProductCategory2Command>
{
    public DisableProductCategory2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
