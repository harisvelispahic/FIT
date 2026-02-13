using Market.Application.Modules.Catalog.Products.Queries.GetById;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.GetById;
public class GetProductCategory2ByIdQuery : IRequest<GetProductCategory2ByIdQueryDto>
{
    public int Id { get; set; }
}
