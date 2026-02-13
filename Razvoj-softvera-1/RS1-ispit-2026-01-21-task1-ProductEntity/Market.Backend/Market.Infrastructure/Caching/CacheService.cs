using Market.Application.Abstractions.Caching;
using Microsoft.Extensions.Caching.Distributed;
using System.Text.Json;

namespace Market.Infrastructure.Caching;

public sealed class CacheService : ICacheService
{
    private readonly IDistributedCache _cache;
    private static readonly JsonSerializerOptions JsonOptions = new(JsonSerializerDefaults.Web);

    public CacheService(IDistributedCache cache)
    {
        _cache = cache;
    }

    public async Task<T?> GetOrCreateAsync<T>(
        string key,
        Func<CancellationToken, Task<T>> factory,
        TimeSpan ttl,
        CancellationToken cancellationToken = default) where T : class
    {
        // Try get from cache
        var cachedData = await _cache.GetStringAsync(key, cancellationToken);

        if (!string.IsNullOrEmpty(cachedData))
        {
            return JsonSerializer.Deserialize<T>(cachedData, JsonOptions);
        }

        // Factory creates the data
        var data = await factory(cancellationToken);

        if (data is not null)
        {
            // Serialize and cache
            var serialized = JsonSerializer.Serialize(data, JsonOptions);
            var options = new DistributedCacheEntryOptions
            {
                AbsoluteExpirationRelativeToNow = ttl
            };

            await _cache.SetStringAsync(key, serialized, options, cancellationToken);
        }

        return data;
    }
}
