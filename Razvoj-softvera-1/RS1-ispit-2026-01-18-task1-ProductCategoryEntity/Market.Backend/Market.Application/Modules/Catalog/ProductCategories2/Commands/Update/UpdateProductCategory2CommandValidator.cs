namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Update;

public sealed class UpdateProductCategory2CommandValidator
    : AbstractValidator<UpdateProductCategory2Command>
{
    public UpdateProductCategory2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
        RuleFor(x => x.Name)
            .NotEmpty().WithMessage("Name is required.")
            .MaximumLength(ProductCategory2Entity.Constraints.NameMaxLength).WithMessage($"Name can be at most {ProductCategory2Entity.Constraints.NameMaxLength} characters long.");
    }
}