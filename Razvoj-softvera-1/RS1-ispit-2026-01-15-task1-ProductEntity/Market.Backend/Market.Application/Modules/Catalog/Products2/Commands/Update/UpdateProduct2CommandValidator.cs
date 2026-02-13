namespace Market.Application.Modules.Catalog.Products2.Commands.Update;

public sealed class UpdateProduct2CommandValidator
    : AbstractValidator<UpdateProduct2Command>
{
    public UpdateProduct2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
        RuleFor(x => x.Name)
            .NotEmpty().WithMessage("Name is required.")
            .MaximumLength(ProductCategoryEntity.Constraints.NameMaxLength).WithMessage($"Name can be at most {ProductCategoryEntity.Constraints.NameMaxLength} characters long.");

        RuleFor(x => x.Description)
            .NotEmpty().WithMessage("Description is required.")
            .MaximumLength(ProductCategoryEntity.Constraints.NameMaxLength).WithMessage($"Description can be at most {ProductCategoryEntity.Constraints.NameMaxLength} characters long.");

        RuleFor(x => x.Price)
            .NotEmpty().WithMessage("Description is required.");

        RuleFor(x => x.CategoryId)
            .NotEmpty().WithMessage("Description is required.");
           

    }
}