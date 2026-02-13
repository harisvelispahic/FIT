using Market.Application.Abstractions.Caching;
using StackExchange.Redis;

namespace Market.Infrastructure.Caching;

public sealed class CatalogCacheVersionService : ICatalogCacheVersionService
{
    private readonly IConnectionMultiplexer _redis;
    private const string VersionKey = "catalog:ver";

    public CatalogCacheVersionService(IConnectionMultiplexer redis)
    {
        _redis = redis;
    }

    public async Task<long> GetVersionAsync(CancellationToken cancellationToken = default)
    {
        var db = _redis.GetDatabase();
        var value = await db.StringGetAsync(VersionKey);

        // If key doesn't exist, treat as version 1
        return value.HasValue ? (long)value : 1;
    }

    public async Task<long> BumpVersionAsync(CancellationToken cancellationToken = default)
    {
        var db = _redis.GetDatabase();

        // Atomic increment - returns new version
        var newVersion = await db.StringIncrementAsync(VersionKey);

        return newVersion;
    }
}
