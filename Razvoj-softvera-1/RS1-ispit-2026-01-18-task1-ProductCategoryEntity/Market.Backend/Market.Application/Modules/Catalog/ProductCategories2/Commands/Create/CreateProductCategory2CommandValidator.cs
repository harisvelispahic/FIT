namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Create;

public sealed class CreateProductCategory2CommandValidator
    : AbstractValidator<CreateProductCategory2Command>
{
    public CreateProductCategory2CommandValidator()
    {
        RuleFor(x => x.Name)
            .NotEmpty().WithMessage("Name is required.")
            .MaximumLength(ProductCategory2Entity.Constraints.NameMaxLength).WithMessage($"Name can be at most {ProductCategory2Entity.Constraints.NameMaxLength} characters long.");
    }
}