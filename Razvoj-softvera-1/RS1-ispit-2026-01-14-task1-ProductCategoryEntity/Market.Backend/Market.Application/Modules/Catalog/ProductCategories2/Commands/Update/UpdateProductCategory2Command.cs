using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Update;
public class UpdateProductCategory2Command : IRequest<Unit>
{
    [JsonIgnore]
    public int Id { get; set; }
    public string Name { get; set; }
    public bool IsEnabled { get; set; }
}
