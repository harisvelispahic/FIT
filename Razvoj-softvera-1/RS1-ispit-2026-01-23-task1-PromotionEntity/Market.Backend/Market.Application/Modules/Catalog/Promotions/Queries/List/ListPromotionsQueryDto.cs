namespace Market.Application.Modules.Catalog.Promotions.Queries.List;

public sealed class ListPromotionsQueryDto
{
    public required int Id { get; init; }
    public required string Title { get; set; }
    public required string ImageUrl { get; set; }
    public required string? TargetUrl { get; set; }
    public required bool IsActive { get; set; }
    public required DateTime? StartsAtUtc { get; set; }
    public required DateTime? EndsAtUtc { get; set; }
    public required int SortOrder { get; set; }
}
