using Market.Application.Abstractions.Caching;

namespace Market.Application.Modules.Catalog.Promotions.Commands.Delete;

public class DeletePromotionCommandHandler : IRequestHandler<DeletePromotionCommand, Unit>
{
    private readonly IAppDbContext _context;
    private readonly IAppCurrentUser _appCurrentUser;
    private readonly ICatalogCacheVersionService _cacheVersionService;

    public DeletePromotionCommandHandler(
        IAppDbContext context,
        IAppCurrentUser appCurrentUser,
        ICatalogCacheVersionService cacheVersionService)
    {
        _context = context;
        _appCurrentUser = appCurrentUser;
        _cacheVersionService = cacheVersionService;
    }

    public async Task<Unit> Handle(DeletePromotionCommand request, CancellationToken cancellationToken)
    {
        if (_appCurrentUser.UserId is null)
            throw new MarketBusinessRuleException("123", "Korisnik nije autentifikovan.");

        var promotion = await _context.Promotions
            .FirstOrDefaultAsync(x => x.Id == request.Id, cancellationToken);

        if (promotion is null)
            throw new MarketNotFoundException("Promocija nije pronađena.");

        _context.Promotions.Remove(promotion);
        await _context.SaveChangesAsync(cancellationToken);

        // Invalidate catalog cache
        await _cacheVersionService.BumpVersionAsync(cancellationToken);

        return Unit.Value;
    }
}
