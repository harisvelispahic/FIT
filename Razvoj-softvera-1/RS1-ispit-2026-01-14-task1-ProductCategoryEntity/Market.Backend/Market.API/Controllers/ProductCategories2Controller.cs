using Market.Application.Modules.Catalog.ProductCategories2.Commands.Create;
using Market.Application.Modules.Catalog.ProductCategories2.Commands.Delete;
using Market.Application.Modules.Catalog.ProductCategories2.Commands.Update;
using Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Enable;
using Market.Application.Modules.Catalog.ProductCategories2.Commands.Status.Disable;
using Market.Application.Modules.Catalog.ProductCategories2.Queries.GetById;
using Market.Application.Modules.Catalog.ProductCategories2.Queries.List;

namespace Market.API.Controllers;

[ApiController]
[Route("[controller]")]
public class ProductCategories2Controller(ISender sender) : ControllerBase
{
    [HttpPost]
    [Authorize(Policy = "Staff")]
    public async Task<ActionResult<int>> Create(CreateProductCategory2Command command, CancellationToken ct)
    {
        int id = await sender.Send(command, ct);

        return CreatedAtAction(nameof(GetById), new { id }, new { id });
    }

    [HttpPut("{id:int}")]
    [Authorize(Policy = "Staff")]
    public async Task Update(int id, UpdateProductCategory2Command command, CancellationToken ct)
    {
        // ID from the route takes precedence
        command.Id = id;
        await sender.Send(command, ct);
        // no return -> 204 No Content
    }

    [HttpDelete("{id:int}")]
    [Authorize(Policy = "Staff")]
    public async Task Delete(int id, CancellationToken ct)
    {
        await sender.Send(new DeleteProductCategory2Command { Id = id }, ct);
        // no return -> 204 No Content
    }

    [HttpGet("{id:int}")]
    [AllowAnonymous]
    public async Task<GetProductCategory2ByIdQueryDto> GetById(int id, CancellationToken ct)
    {
        var category = await sender.Send(new GetProductCategory2ByIdQuery { Id = id }, ct);
        return category; // if NotFoundException -> 404 via middleware
    }

    [HttpGet]
    [AllowAnonymous]
    public async Task<PageResult<ListProductCategories2QueryDto>> List([FromQuery] ListProductCategories2Query query, CancellationToken ct)
    {
        var result = await sender.Send(query, ct);
        return result;
    }

    [HttpPut("{id:int}/disable")]
    public async Task Disable(int id, CancellationToken ct)
    {
        await sender.Send(new DisableProductCategory2Command { Id = id }, ct);
        // no return -> 204 No Content
    }

    [HttpPut("{id:int}/enable")]
    public async Task Enable(int id, CancellationToken ct)
    {
        await sender.Send(new EnableProductCategory2Command { Id = id }, ct);
        // no return -> 204 No Content
    }
}
