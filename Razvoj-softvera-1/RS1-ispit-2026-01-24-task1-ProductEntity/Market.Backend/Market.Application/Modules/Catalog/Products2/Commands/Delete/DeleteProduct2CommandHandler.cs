using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Products2.Commands.Delete;

public class DeleteProduct2CommandHandler : IRequestHandler<DeleteProduct2Command, Unit>
{
    private readonly IAppDbContext _context;
    private readonly IAppCurrentUser _appCurrentUser;
    private readonly ICatalogCacheVersionService _cacheVersionService;

    public DeleteProduct2CommandHandler(
        IAppDbContext context,
        IAppCurrentUser appCurrentUser,
        ICatalogCacheVersionService cacheVersionService)
    {
        _context = context;
        _appCurrentUser = appCurrentUser;
        _cacheVersionService = cacheVersionService;
    }

    public async Task<Unit> Handle(DeleteProduct2Command request, CancellationToken cancellationToken)
    {
        var category = await _context.Products2
            .FirstOrDefaultAsync(x => x.Id == request.Id, cancellationToken);

        if (category is null)
            throw new MarketNotFoundException("Kategorija nije pronađena.");

        _context.Products2.Remove(category);
        await _context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await _cacheVersionService.BumpVersionAsync(cancellationToken);

        return Unit.Value;
    }
}
