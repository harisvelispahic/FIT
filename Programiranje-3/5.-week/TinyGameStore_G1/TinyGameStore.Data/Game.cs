namespace TinyGameStore.Data
{
    public class Game
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Publisher { get; set; }
        public DateTime ReleaseDate { get; set; }
        public byte[]? CoverArt { get; set; }

        public virtual List<GamesGenre> GamesGenres { get; set; } = new List<GamesGenre>();
        public virtual List<UsersGame> UsersGames { get; set; } = new List<UsersGame>();
    }
}