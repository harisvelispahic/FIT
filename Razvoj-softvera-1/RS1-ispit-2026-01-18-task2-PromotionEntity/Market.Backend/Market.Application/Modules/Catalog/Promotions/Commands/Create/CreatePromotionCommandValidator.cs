using FluentValidation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Create;
public class CreatePromotionCommandValidator : AbstractValidator<CreatePromotionCommand>
{
    public CreatePromotionCommandValidator()
    {
        RuleFor(x => x.Title)
            .NotEmpty()
            .WithMessage("Title is required.")
            .MaximumLength(PromotionEntity.Constraints.TitleMaxLength)
            .WithMessage($"Title cannot exceed {PromotionEntity.Constraints.TitleMaxLength} characters.");

        RuleFor(x => x.ImageUrl)
            .NotEmpty()
            .WithMessage("ImageUrl is required.")
            .MaximumLength(PromotionEntity.Constraints.ImageUrlMaxLength)
            .WithMessage($"ImageUrl cannot exceed {PromotionEntity.Constraints.ImageUrlMaxLength} characters.");

        RuleFor(x => x.TargetUrl)
            .MaximumLength(PromotionEntity.Constraints.TargetUrlMaxLength)
            .WithMessage($"TargetUrl cannot exceed {PromotionEntity.Constraints.TargetUrlMaxLength} characters.");

        RuleFor(x => x.StartsAtUtc)
            .LessThanOrEqualTo(x => x.EndsAtUtc)
            .When(x => x.StartsAtUtc.HasValue && x.EndsAtUtc.HasValue)
            .WithMessage("StartsAtUtc must be earlier than or equal to EndsAtUtc.");

        RuleFor(x => x.SortOrder)
            .GreaterThanOrEqualTo(0)
            .WithMessage("SortOrder must be greater than or equal to 0.");

        RuleForEach(x => x.PromotionItems)
            .SetValidator(new CreatePromotionCommandItemValidator());
    }
}


public class CreatePromotionCommandItemValidator : AbstractValidator<CreatePromotionCommandPromotionItem>
{
    public CreatePromotionCommandItemValidator()
    {
        RuleFor(x => x.ProductId)
            .GreaterThan(0)
            .WithMessage("ProductId must be greater than 0.");

        RuleFor(x => x.DiscountPercent)
            .InclusiveBetween(0.001m, 0.999m)
            .WithMessage("DiscountPercent must be between 0 and 100.");
    }
}