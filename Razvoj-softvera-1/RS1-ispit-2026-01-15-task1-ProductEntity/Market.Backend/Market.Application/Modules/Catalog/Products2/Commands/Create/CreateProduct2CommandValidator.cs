namespace Market.Application.Modules.Catalog.Products2.Commands.Create;

public sealed class CreateProduct2CommandValidator
    : AbstractValidator<CreateProduct2Command>
{
    public CreateProduct2CommandValidator()
    {
        RuleFor(x => x.Name)
            .NotEmpty().WithMessage("Name is required.")
            .MaximumLength(ProductCategoryEntity.Constraints.NameMaxLength).WithMessage($"Name can be at most {ProductCategoryEntity.Constraints.NameMaxLength} characters long.");

        RuleFor(x => x.Description)
           .NotEmpty().WithMessage("Name is required.")
           .MaximumLength(ProductCategoryEntity.Constraints.NameMaxLength).WithMessage($"Name can be at most {ProductCategoryEntity.Constraints.NameMaxLength} characters long.");

        RuleFor(x => x.Price)
            .GreaterThanOrEqualTo(0).WithMessage("Price must be non-negative.");

        RuleFor(x => x.CategoryId)
            .GreaterThan(0).WithMessage("CategoryId must be a positive integer.");
    }
}