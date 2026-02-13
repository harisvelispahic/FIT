namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;

public sealed class UpdatePromotionCommandValidator
    : AbstractValidator<UpdatePromotionCommand>
{
    public UpdatePromotionCommandValidator()
    {
        RuleFor(x => x.Title)
            .NotEmpty()
            .WithMessage("Title is required.")
            .MaximumLength(PromotionEntity.Constraints.TitleMaxLength)
            .WithMessage($"Title can be at most {PromotionEntity.Constraints.TitleMaxLength} characters long.");

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

        RuleFor(x => x.SortOrder)
            .NotEmpty()
            .GreaterThan(0);
    }
}