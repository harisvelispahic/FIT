using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Create;
public class CreateProductCategory2Command : IRequest<int>
{
    public string Name { get; set; }
    public bool IsEnabled { get; set; }
}
