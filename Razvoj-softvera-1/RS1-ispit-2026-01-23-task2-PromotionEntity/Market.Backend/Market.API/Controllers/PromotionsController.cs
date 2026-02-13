using Market.Application.Modules.Catalog.Promotions.Commands.Delete;
using Market.Application.Modules.Sales.Promotions.Commands.Create;
//using Market.Application.Modules.Sales.Promotions.Commands.Status;
using Market.Application.Modules.Sales.Promotions.Commands.Update;
using Market.Application.Modules.Sales.Promotions.Queries.GetById;
using Market.Application.Modules.Sales.Promotions.Queries.List;
using Market.Application.Modules.Sales.Promotions.Queries.ListWithItems;

namespace Market.API.Controllers;

[ApiController]
[Route("[controller]")]
[AllowAnonymous]
public class PromotionsController(ISender sender) : ControllerBase
{
    [HttpPost]
    // Fallback policy already requires authenticated user
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
    public async Task<GetPromotionByIdQueryDto> GetById(int id, CancellationToken ct)
    {
        var dto = await sender.Send(new GetPromotionByIdQuery { Id = id }, ct);
        return dto; // if NotFoundException -> 404 via middleware
    }

    [HttpGet]
    public async Task<PageResult<ListPromotionsQueryDto>> List([FromQuery] ListPromotionsQuery query, CancellationToken ct)
    {
        var result = await sender.Send(query, ct);
        return result;
    }

    [HttpGet("with-items")]
    public async Task<PageResult<ListPromotionsWithItemsQueryDto>> ListWithItems([FromQuery] ListPromotionsWithItemsQuery query, CancellationToken ct)
    {
        var result = await sender.Send(query, ct);
        return result;
    }

    //[HttpPut("{id:int}/change-status")]
    //[Authorize(Policy = "Staff")]
    //public async Task ChangeStatus(int id, [FromBody] ChangePromotionstatusCommand command, CancellationToken ct)
    //{
    //    command.Id = id;
    //    await sender.Send(command, ct);
    //    // no return -> 204 No Content
    //}
}
