using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.ProductCategories2.Commands.Update;

public sealed class UpdateProductCategory2CommandHandler : IRequestHandler<UpdateProductCategory2Command, Unit>
{
    private readonly IAppDbContext _ctx;
    private readonly ICatalogCacheVersionService _cacheVersionService;

    public UpdateProductCategory2CommandHandler(
        IAppDbContext ctx,
        ICatalogCacheVersionService cacheVersionService)
    {
        _ctx = ctx;
        _cacheVersionService = cacheVersionService;
    }

    public async Task<Unit> Handle(UpdateProductCategory2Command request, CancellationToken ct)
    {
        var entity = await _ctx.ProductCategories2
            .Where(x => x.Id == request.Id)
            .FirstOrDefaultAsync(ct);

        if (entity is null)
            throw new MarketNotFoundException($"Kategorija (ID={request.Id}) nije pronađena.");

        // Check for duplicate name (case-insensitive, except for the same ID)
        var exists = await _ctx.ProductCategories2
            .AnyAsync(x => x.Id != request.Id && x.Name.ToLower() == request.Name.ToLower(), ct);

        if (exists)
        {
            throw new MarketConflictException("Name already exists.");
        }

        // Business rule: cannot disable if there are active products
        var hasActiveProducts = await _ctx.Products
            .AnyAsync(p => p.CategoryId == entity.Id && p.IsEnabled, ct);

        if (hasActiveProducts && !request.IsEnabled)
        {
            throw new MarketBusinessRuleException("category.disable.blocked.activeProducts",
                $"Category {entity.Name} cannot be disabled because it contains active products.");
        }

        entity.Name = request.Name.Trim();
        entity.IsEnabled = request.IsEnabled;


        await _ctx.SaveChangesAsync(ct);

        // Invalidate catalog cache
        await _cacheVersionService.BumpVersionAsync(ct);

        return Unit.Value;
    }
}
