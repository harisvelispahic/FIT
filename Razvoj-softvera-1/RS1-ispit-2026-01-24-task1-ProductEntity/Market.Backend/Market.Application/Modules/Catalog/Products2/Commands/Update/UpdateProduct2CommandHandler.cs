using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Products2.Commands.Update;

public sealed class UpdateProduct2CommandHandler : IRequestHandler<UpdateProduct2Command, Unit>
{
    private readonly IAppDbContext _ctx;
    private readonly ICatalogCacheVersionService _cacheVersionService;

    public UpdateProduct2CommandHandler(
        IAppDbContext ctx,
        ICatalogCacheVersionService cacheVersionService)
    {
        _ctx = ctx;
        _cacheVersionService = cacheVersionService;
    }

    public async Task<Unit> Handle(UpdateProduct2Command request, CancellationToken ct)
    {
        var entity = await _ctx.Products2
            .Where(x => x.Id == request.Id)
            .FirstOrDefaultAsync(ct);

        if (entity is null)
            throw new MarketNotFoundException($"Kategorija (ID={request.Id}) nije pronađena.");

        // Check for duplicate name (case-insensitive, except for the same ID)
        var exists = await _ctx.Products2
            .AnyAsync(x => x.Id != request.Id && x.Name.ToLower() == request.Name.ToLower(), ct);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        entity.Name = request.Name.Trim();
        entity.Description = request.Description;
        entity.Price = request.Price;
        entity.StockQuantity = request.StockQuantity;
        entity.CategoryId = request.CategoryId;
        entity.IsEnabled = request.IsEnabled;

        await _ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await _cacheVersionService.BumpVersionAsync(ct);

        return Unit.Value;
    }
}
