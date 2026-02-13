using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Products2.Commands.Delete;

public class DeleteProduct2CommandHandler : IRequestHandler<DeleteProduct2Command, Unit>
{
    private readonly IAppDbContext _context;
    private readonly ICatalogCacheVersionService _cacheVersionService;

    public DeleteProduct2CommandHandler(
        IAppDbContext context,
        ICatalogCacheVersionService cacheVersionService)
    {
        _context = context;
        _cacheVersionService = cacheVersionService;
    }

    public async Task<Unit> Handle(DeleteProduct2Command request, CancellationToken cancellationToken)
    {
        var product2 = await _context.Products2
            .FirstOrDefaultAsync(x => x.Id == request.Id, cancellationToken);

        if (product2 is null)
            throw new MarketNotFoundException("Kategorija nije pronađena.");

        _context.Products2.Remove(product2);
        await _context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await _cacheVersionService.BumpVersionAsync(cancellationToken);

        return Unit.Value;
    }
}
