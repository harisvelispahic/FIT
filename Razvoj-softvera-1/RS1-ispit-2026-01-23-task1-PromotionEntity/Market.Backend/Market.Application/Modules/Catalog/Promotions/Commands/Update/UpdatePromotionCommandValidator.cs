namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;

public sealed class UpdatePromotionCommandValidator
    : AbstractValidator<UpdatePromotionCommand>
{
    public UpdatePromotionCommandValidator()
    {
        RuleFor(x => x.Title)
            .NotEmpty()
            .WithMessage("Name is required.")
            .MaximumLength(PromotionEntity.Constraints.TitleMaxLength)
            .WithMessage($"Name can be at most {PromotionEntity.Constraints.TitleMaxLength} characters long.");

        RuleFor(x => x.ImageUrl)
                    .NotEmpty()
                    .WithMessage("ImageUrl is required.")
                    .MaximumLength(PromotionEntity.Constraints.ImageUrlMaxLength)
                    .WithMessage($"ImageUrl can be at most {PromotionEntity.Constraints.ImageUrlMaxLength} characters long.");

        RuleFor(x => x.TargetUrl)
            .NotEmpty()
            .WithMessage("TargetUrl is required.")
            .MaximumLength(PromotionEntity.Constraints.TargetUrlMaxLength)
            .WithMessage($"TargetUrl can be at most {PromotionEntity.Constraints.TargetUrlMaxLength} characters long.");

        RuleFor(x => x.IsActive)
            .NotEmpty()
            .WithMessage("IsActive is required.");

        RuleFor(x => x.StartsAtUtc)
            .NotEmpty()
            .WithMessage("StartsAtUtc is required.");

        RuleFor(x => x.EndsAtUtc)
            .NotEmpty()
            .WithMessage("EndsAtUtc is required.");

        RuleFor(x => x.SortOrder)
            .NotEmpty()
            .WithMessage("SortOrder is required.");
    }
}