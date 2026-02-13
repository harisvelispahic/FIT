namespace Market.Application.Modules.Catalog.Products2.Commands.Create;

public sealed class CreateProduct2CommandValidator
    : AbstractValidator<CreateProduct2Command>
{
    public CreateProduct2CommandValidator()
    {
        RuleFor(x => x.Name)
            .NotEmpty().WithMessage("Name is required.")
            .MaximumLength(Product2Entity.Constraints.NameMaxLength).WithMessage($"Name can be at most {Product2Entity.Constraints.NameMaxLength} characters long.");

        RuleFor(x => x.Description)
                .NotEmpty().WithMessage("Name is required.")
                .MaximumLength(Product2Entity.Constraints.DescriptionMaxLength).WithMessage($"Name can be at most {Product2Entity.Constraints.DescriptionMaxLength} characters long.");

        RuleFor(x => x.Price)
            .NotEmpty().WithMessage("Price is required.")
            .GreaterThan(0).WithMessage("Price must be greater than zero.");

        RuleFor(x => x.StockQuantity)
            .NotEmpty().WithMessage("StockQuantity is required.")
            .GreaterThan(0).WithMessage("StockQuantity must be greater than zero.");

        RuleFor(x => x.CategoryId)
            .NotEmpty().WithMessage("CategoryId is required.")
            .GreaterThan(0).WithMessage("CategoryId must be greater than zero.");

        RuleFor(x => x.IsEnabled)
            .NotEmpty().WithMessage("IsEnabled is required.");
    }
}