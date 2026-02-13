using FluentValidation;

namespace Market.Application.Modules.Sales.Promotions.Commands.Create;

public sealed class CreatePromotionCommandValidator : AbstractValidator<CreatePromotionCommand>
{
    public CreatePromotionCommandValidator()
    {
        RuleFor(x => x.Title)
            .MaximumLength(500).WithMessage("Title cannot exceed 500 characters.")
            .When(x => !string.IsNullOrEmpty(x.Title));

        RuleFor(x => x.ImageUrl)
            .MaximumLength(500).WithMessage("ImageUrl cannot exceed 500 characters.")
            .When(x => !string.IsNullOrEmpty(x.ImageUrl));

        RuleFor(x => x.TargetUrl)
            .MaximumLength(500).WithMessage("TargetUrl cannot exceed 500 characters.")
            .When(x => !string.IsNullOrEmpty(x.TargetUrl));

        RuleFor(x => x.IsActive)
            .NotEmpty();

        RuleFor(x => x.StartsAtUtc)
            .NotEmpty();

        RuleFor(x => x.EndsAtUtc)
            .NotEmpty();

        RuleFor(x => x.SortOrder)
            .NotEmpty();


        RuleFor(x => x.PromotionItems)
            .NotEmpty().WithMessage("Promotion must contain at least one item.");

        RuleForEach(x => x.PromotionItems)
            .SetValidator(new CreatePromotionCommandItemValidator());

        RuleFor(x => x.PromotionItems)
            .Must(items => items.Select(i => i.ProductId).Distinct().Count() == items.Count)
            .WithMessage("Promotion cannot contain duplicate products.")
            .When(x => x.PromotionItems != null && x.PromotionItems.Any());
    }
}

public sealed class CreatePromotionCommandItemValidator : AbstractValidator<CreatePromotionCommandPromotionItem>
{
    public CreatePromotionCommandItemValidator()
    {
        RuleFor(x => x.ProductId)
            .GreaterThan(0).WithMessage("ProductId must be greater than 0.");

        RuleFor(x => x.DiscountPercent)
            .InclusiveBetween(1, 100).WithMessage("Quantity must be between 1 and 999.");
    }
}
