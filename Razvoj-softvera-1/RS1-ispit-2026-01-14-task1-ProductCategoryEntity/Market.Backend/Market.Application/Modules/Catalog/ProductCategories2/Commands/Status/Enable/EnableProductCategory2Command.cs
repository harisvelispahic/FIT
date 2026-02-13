using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Enable;
public class EnableProductCategory2Command : IRequest<Unit>
{
    public required int Id { get; set; }

}
