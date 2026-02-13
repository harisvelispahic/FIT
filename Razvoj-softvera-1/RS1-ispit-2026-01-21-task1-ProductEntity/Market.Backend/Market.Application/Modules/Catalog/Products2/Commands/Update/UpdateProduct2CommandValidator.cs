namespace Market.Application.Modules.Catalog.Products2.Commands.Update;

public sealed class UpdateProduct2CommandValidator
    : AbstractValidator<UpdateProduct2Command>
{
    public UpdateProduct2CommandValidator()
    {
        RuleFor(x => x.Name)
            .NotEmpty().WithMessage("Name is required.")
            .MaximumLength(Product2Entity.Constraints.NameMaxLength)
            .WithMessage($"Name can be at most {Product2Entity.Constraints.NameMaxLength} characters long.");

        RuleFor(x => x.Description)
                    .NotEmpty()
                    .WithMessage("Description is required.")
                    .MaximumLength(Product2Entity.Constraints.DescriptionMaxLength)
                    .WithMessage($"Description can be at most {Product2Entity.Constraints.DescriptionMaxLength} characters long.");

        RuleFor(x => x.Price)
                    .NotEmpty()
                    .WithMessage("Price is required.")
                    .GreaterThan(0)
                    .WithMessage($"Price must be positive.");

        RuleFor(x => x.StockQuantity)
                    .NotEmpty()
                    .WithMessage("StockQuantity is required.")
                    .GreaterThan(0)
                    .WithMessage($"StockQuantity must be positive.");

        RuleFor(x => x.CategoryId)
                    .NotEmpty()
                    .WithMessage("CategoryId is required.")
                    .GreaterThan(0)
                    .WithMessage($"CategoryId must be positive.");

        RuleFor(x => x.IsEnabled)
                    .NotEmpty()
                    .WithMessage("IsEnabled is required.");
    }
}