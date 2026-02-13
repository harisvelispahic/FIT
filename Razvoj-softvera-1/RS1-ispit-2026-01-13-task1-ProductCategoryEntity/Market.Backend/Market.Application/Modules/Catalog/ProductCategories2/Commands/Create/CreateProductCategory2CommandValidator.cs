using Market.Application.Modules.Catalog.Products.Commands.Create;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Create;
public class CreateProductCategory2CommandValidator : AbstractValidator<CreateProductCategory2Command>
{
    public CreateProductCategory2CommandValidator()
    {
        RuleFor(x => x.Name)
            .NotEmpty().WithMessage("Product name is required.")
            .MinimumLength(3).WithMessage("Product name must be at least 3 characters long.")
            .MaximumLength(200).WithMessage("Product name cannot exceed 200 characters.");

        RuleFor(x => x.IsEnabled)
            .NotEmpty().WithMessage("IsEnabled is required.");
    }
}
