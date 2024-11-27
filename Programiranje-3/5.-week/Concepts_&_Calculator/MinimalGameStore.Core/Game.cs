namespace MinimalGameStore.Core
{
    public class Game
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Publisher { get; set; }
        public DateTime ReleaseDate { get; set; }
        public string CoverArt { get; set; }
        public List<Genre> Genres { get; set; }

        public override string ToString()
        {
            string output = "";
            for (int i = 0; i < Genres.Count; i++)
            {
                output += Genres[i] + ",\n";
            }
            return $"Id: {Id}\nName: {Name}\nPublisher: {Publisher}\n" +
                $"Release date: {ReleaseDate.ToString()}\nCover art: {CoverArt}\nGenres:\n{output}" + Divider.Lines;
        }
    }
}