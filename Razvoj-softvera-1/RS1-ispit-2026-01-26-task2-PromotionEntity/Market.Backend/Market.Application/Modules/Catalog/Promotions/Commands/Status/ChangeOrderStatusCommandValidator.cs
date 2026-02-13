using FluentValidation;
using Market.Domain.Entities.Sales;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Status;

public sealed class ChangePromotionStatusCommandValidator : AbstractValidator<ChangePromotionStatusCommand>
{
    public ChangePromotionStatusCommandValidator()
    {
        RuleFor(x => x.Id)
            .GreaterThan(0).WithMessage("Promotion Id must be greater than 0.");
    }
}
