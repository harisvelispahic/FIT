using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Update;
public class UpdateProductCategories2CommandValidator : AbstractValidator<UpdateProductCategory2Command>
{
    public UpdateProductCategories2CommandValidator()
    {
        RuleFor(x => x.Id)
            .GreaterThan(0).WithMessage("Id must be greater than 0.");

        RuleFor(x => x.Name)
            .NotEmpty().WithMessage("Product name is required.")
            .MaximumLength(200).WithMessage("Product name cannot exceed 200 characters.");

        RuleFor(x => x.IsEnabled)
            .NotNull().WithMessage("IsEnabled is required.");
    }
}
