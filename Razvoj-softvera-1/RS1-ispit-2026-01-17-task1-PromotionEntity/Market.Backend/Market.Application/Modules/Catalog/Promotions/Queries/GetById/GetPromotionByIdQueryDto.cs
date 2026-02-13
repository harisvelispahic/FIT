namespace Market.Application.Modules.Catalog.Promotions.Queries.GetById;

public class GetPromotionByIdQueryDto
{
    public required int Id { get; init; }
    public required string Title { get; init; }
    public string? ImageUrl { get; init; }
    public string? TargetUrl { get; init; }
    public required bool IsActive { get; init; }
    public DateTime? StartsAtUtc { get; init; }
    public DateTime? EndsAtUtc { get; init; }
    public required int SortOrder { get; init; }
}
