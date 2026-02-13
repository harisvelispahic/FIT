using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Delete;
public class DeletePromotionCommandValidator : AbstractValidator<DeletePromotionCommand>
{
    public DeletePromotionCommandValidator()
    {
        RuleFor(x => x.Id)
            .GreaterThan(0)
            .WithMessage("Id must be greater than 0.");
    }
}
