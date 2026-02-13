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
        if (_appCurrentUser.UserId is null)
            throw new MarketBusinessRuleException("123", "Korisnik nije autentifikovan.");

        var product = await _context.Products2
            .FirstOrDefaultAsync(x => x.Id == request.Id, cancellationToken);

        if (product is null)
            throw new MarketNotFoundException("Kategorija nije pronađena.");

        _context.Products2.Remove(product);
        await _context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await _cacheVersionService.BumpVersionAsync(cancellationToken);

        return Unit.Value;
    }
}
