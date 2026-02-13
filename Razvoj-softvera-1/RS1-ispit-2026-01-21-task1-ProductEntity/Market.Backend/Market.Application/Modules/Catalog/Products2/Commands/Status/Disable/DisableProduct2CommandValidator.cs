namespace Market.Application.Modules.Catalog.Products2.Commands.Status.Disable;

public sealed class DisableProduct2CommandValidator : AbstractValidator<DisableProduct2Command>
{
    public DisableProduct2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
