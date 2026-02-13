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
        var product = await _ctx.Products2
            .Where(x => x.Id == request.Id)
            .FirstOrDefaultAsync(ct);

        if (product is null)
            throw new MarketNotFoundException($"Proizvod (ID={request.Id}) nije pronađena.");

        // Check for duplicate name (case-insensitive, except for the same ID)
        var exists = await _ctx.ProductCategories
            .AnyAsync(x => x.Id != request.Id && x.Name.ToLower() == request.Name.ToLower(), ct);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        product.Name = request.Name.Trim();
        product.Description = request.Description.Trim();
        product.Price = request.Price;
        //product.StockQuantity = request.StockQuantity;
        product.CategoryId = request.CategoryId;
        //product.IsEnabled = request.IsEnabled;

        await _ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await _cacheVersionService.BumpVersionAsync(ct);

        return Unit.Value;
    }
}
