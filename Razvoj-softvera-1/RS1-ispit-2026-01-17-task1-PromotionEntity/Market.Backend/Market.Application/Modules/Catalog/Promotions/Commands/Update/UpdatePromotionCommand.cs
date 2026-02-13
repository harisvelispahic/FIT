namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;

public sealed class UpdatePromotionCommand : IRequest<Unit>
{
    [JsonIgnore]
    public int Id { get; set; }
    public required string Title { get; set; }
    public required string ImageUrl { get; set; }
    public required string? TargetUrl { get; set; }
    public required bool IsActive { get; set; }
    public required DateTime? StartsAtUtc { get; set; }
    public required DateTime? EndsAtUtc { get; set; }
    public required int SortOrder { get; set; }
}
