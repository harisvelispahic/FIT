namespace Market.Application.Modules.Catalog.ProductCategories.Commands.Status.Enable;

public sealed class EnableProduct2CommandValidator : AbstractValidator<EnableProductCategoryCommand>
{
    public EnableProduct2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
