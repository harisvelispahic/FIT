namespace Market.Application.Modules.Catalog.Promotions.Commands.Update;

public class DeletePromotionCommand : IRequest<int>
{
    [JsonIgnore]
    public int Id { get; set; }
}

