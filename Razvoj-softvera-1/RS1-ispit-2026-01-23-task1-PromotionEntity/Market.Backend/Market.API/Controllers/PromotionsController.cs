using Market.Application.Modules.Catalog.Promotions.Commands.Delete;
using Market.Application.Modules.Catalog.Promotions.Commands.Status.Disable;
using Market.Application.Modules.Catalog.Promotions.Commands.Status.Enable;
using Market.Application.Modules.Catalog.Promotions.Commands.Create;
using Market.Application.Modules.Catalog.Promotions.Commands.Update;
using Market.Application.Modules.Catalog.Promotions.Queries.GetById;
using Market.Application.Modules.Catalog.Promotions.Queries.List;

namespace Market.API.Controllers;

[ApiController]
[Route("[controller]")]
[Authorize(Policy = "AdminOnly")]
public class PromotionsController(ISender sender) : ControllerBase
{
    [HttpPost]
    public async Task<ActionResult<int>> Create(CreatePromotionCommand command, CancellationToken ct)
    {
        int id = await sender.Send(command, ct);

        return CreatedAtAction(nameof(GetById), new { id }, new { id });
    }

    [HttpPut("{id:int}")]
    public async Task Update(int id, UpdatePromotionCommand command, CancellationToken ct)
    {
        // ID from the route takes precedence
        command.Id = id;
        await sender.Send(command, ct);
        // no return -> 204 No Content
    }

    [HttpDelete("{id:int}")]
    public async Task Delete(int id, CancellationToken ct)
    {
        await sender.Send(new DeletePromotionCommand { Id = id }, ct);
        // no return -> 204 No Content
    }

    [HttpGet("{id:int}")]
    [AllowAnonymous]
    public async Task<GetPromotionByIdQueryDto> GetById(int id, CancellationToken ct)
    {
        var category = await sender.Send(new GetPromotionByIdQuery { Id = id }, ct);
        return category; // if NotFoundException -> 404 via middleware
    }

    [HttpGet]
    [AllowAnonymous]
    public async Task<PageResult<ListPromotionsQueryDto>> List([FromQuery] ListPromotionsQuery query, CancellationToken ct)
    {
        var result = await sender.Send(query, ct);
        return result;
    }

    [HttpPut("{id:int}/disable")]
    public async Task Disable(int id, CancellationToken ct)
    {
        await sender.Send(new DisablePromotionCommand { Id = id }, ct);
        // no return -> 204 No Content
    }

    [HttpPut("{id:int}/enable")]
    public async Task Enable(int id, CancellationToken ct)
    {
        await sender.Send(new EnablePromotionCommand { Id = id }, ct);
        // no return -> 204 No Content
    }
}
