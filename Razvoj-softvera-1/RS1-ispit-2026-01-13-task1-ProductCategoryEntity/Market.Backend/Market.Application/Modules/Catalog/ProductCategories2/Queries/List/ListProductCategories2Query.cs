using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Market.Application.Modules.Catalog.ProductCategories2.Queries.List;
public class ListProductCategories2Query : BasePagedQuery<ListProductCategories2QueryDto>
{
    public string? Search { get; init; }
    public bool? OnlyEnabled { get; init; }
}
