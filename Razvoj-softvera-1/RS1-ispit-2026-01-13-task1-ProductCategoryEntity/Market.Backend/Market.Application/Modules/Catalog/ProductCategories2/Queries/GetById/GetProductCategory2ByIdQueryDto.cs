using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.GetById;
public class GetProductCategory2ByIdQueryDto
{
    public required int Id { get; init; }
    public required string Name { get; init; }
    public required bool IsEnabled { get; init; }
}
