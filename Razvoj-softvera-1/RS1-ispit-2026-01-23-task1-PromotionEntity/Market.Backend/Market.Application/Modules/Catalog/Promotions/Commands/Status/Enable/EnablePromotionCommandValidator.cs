namespace Market.Application.Modules.Catalog.Promotions.Commands.Status.Enable;

public sealed class EnablePromotionCommandValidator : AbstractValidator<EnablePromotionCommand>
{
    public EnablePromotionCommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
