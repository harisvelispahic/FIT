namespace Market.Application.Modules.Catalog.Promotions.Commands.Status.Disable;

public sealed class DisablePromotionCommandValidator : AbstractValidator<DisablePromotionCommand>
{
    public DisablePromotionCommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
