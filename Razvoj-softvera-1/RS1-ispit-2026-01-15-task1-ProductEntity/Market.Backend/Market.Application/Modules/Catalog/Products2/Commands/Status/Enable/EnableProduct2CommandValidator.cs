namespace Market.Application.Modules.Catalog.Products2.Commands.Status.Enable;

public sealed class EnableProduct2CommandValidator : AbstractValidator<EnableProduct2Command>
{
    public EnableProduct2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
