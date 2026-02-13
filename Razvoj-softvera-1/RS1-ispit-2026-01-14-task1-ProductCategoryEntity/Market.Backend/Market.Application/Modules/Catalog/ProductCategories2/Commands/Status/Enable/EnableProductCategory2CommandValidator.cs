using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Enable;
public class EnableProductCategory2CommandValidator : AbstractValidator<EnableProductCategory2Command>
{
    public EnableProductCategory2CommandValidator()
    {
        RuleFor(x => x.Id).GreaterThan(0);
    }
}
