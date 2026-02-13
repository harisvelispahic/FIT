using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Disable;
public class DisableProductCategory2CommandValidator : AbstractValidator<DisableProductCategory2Command>
{
    public DisableProductCategory2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
