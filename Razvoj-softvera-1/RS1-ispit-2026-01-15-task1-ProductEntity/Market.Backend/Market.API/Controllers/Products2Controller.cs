using Market.Application.Modules.Catalog.Products2.Commands.Delete;
using Market.Application.Modules.Catalog.Products2.Commands.Status.Disable;
using Market.Application.Modules.Catalog.Products2.Commands.Status.Enable;
using Market.Application.Modules.Catalog.Products2.Commands.Create;
using Market.Application.Modules.Catalog.Products2.Commands.Update;
using Market.Application.Modules.Catalog.Products2.Queries.GetById;
using Market.Application.Modules.Catalog.Products2.Queries.List;

namespace Market.API.Controllers;

[ApiController]
[Route("[controller]")]
[Authorize(Policy = "Staff")]
public class Products2Controller(ISender sender) : ControllerBase
{
    [HttpPost]
    public async Task<ActionResult<int>> CreateProduct(CreateProduct2Command command, CancellationToken ct)
    {
        int id = await sender.Send(command, ct);

        return CreatedAtAction(nameof(GetById), new { id }, new { id });
    }

    [HttpPut("{id:int}")]
    public async Task Update(int id, UpdateProduct2Command command, CancellationToken ct)
    {
        // ID from the route takes precedence
        command.Id = id;
        await sender.Send(command, ct);
        // no return -> 204 No Content
    }

    [HttpDelete("{id:int}")]
    public async Task Delete(int id, CancellationToken ct)
    {
        await sender.Send(new DeleteProduct2Command { Id = id }, ct);
        // no return -> 204 No Content
    }

    [HttpGet("{id:int}")]
    [AllowAnonymous]
    public async Task<GetProduct2ByIdQueryDto> GetById(int id, CancellationToken ct)
    {
        var category = await sender.Send(new GetProduct2ByIdQuery { Id = id }, ct);
        return category; // if NotFoundException -> 404 via middleware
    }

    [HttpGet]
    [AllowAnonymous]
    public async Task<PageResult<ListProducts2QueryDto>> List([FromQuery] ListProducts2Query query, CancellationToken ct)
    {
        var result = await sender.Send(query, ct);
        return result;
    }

    [HttpPut("{id:int}/disable")]
    public async Task Disable(int id, CancellationToken ct)
    {
        await sender.Send(new DisableProduct2Command { Id = id }, ct);
        // no return -> 204 No Content
    }

    [HttpPut("{id:int}/enable")]
    public async Task Enable(int id, CancellationToken ct)
    {
        await sender.Send(new EnableProduct2Command { Id = id }, ct);
        // no return -> 204 No Content
    }
}
