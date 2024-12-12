using TinyGameStore.Data;

namespace TinyGameStore.InMemory
{
    public class InMemoryDb
    {
        DataContext context = new DataContext();
        private List<User> Users { get; set; }
        private List<Game> Games { get; set; }

        public InMemoryDb()
        {
            FillMockData();
        }

        public void FillMockData()
        {
            Users = new List<User>() {
                // user1 user1  ->  login
                new User() { FirstName = "Jan", LastName="Doe", UserName = "JonDoe", Password = "ILikeCats" },
                new User() { FirstName = "admin", LastName="admin", UserName = "admin", Password = "test123" },
                new User() { FirstName = "user", LastName="user", UserName = "user", Password = "user" },
                new User() { FirstName = "Tony", LastName="Stark", UserName = "TonyStark", Password = "ILoveYou3000" },
                new User() { FirstName = "John", LastName="Wick", UserName = "JohnWick", Password = "CanYouLikeDogs" },
                new User() { FirstName = "Tarnished", LastName="Dark", UserName = "Tarnished", Password = "FindTheRing" },
                new User() { FirstName = "Hollow", LastName="Knight", UserName = "Hollow", Password = "Andre" }
                };

            Games = new List<Game>()
            {
                new Game() { Id = 1, Name = "Family farm", Publisher = "XYZ", ReleaseDate = DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60, 180),0,0,0)) },
                new Game() { Id = 2, Name = "Assassins Creed", Publisher = "Ubisoft", ReleaseDate = DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60, 180),0,0,0)) },
                new Game() { Id = 3, Name = "Five nights and Fredies", Publisher = "ScottCoffen", ReleaseDate = DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60, 180),0,0,0)) },
                new Game() { Id = 4, Name = "Undertale", Publisher = "TobyFox", ReleaseDate = DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60, 180),0,0,0)) },
                new Game() { Id = 5, Name = "Dying light", Publisher = "UVW", ReleaseDate = DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60, 180),0,0,0)) },
                new Game() { Id = 6, Name = "Little nightmares", Publisher = "Bandai Namco", ReleaseDate = DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60, 180),0,0,0)) },
                new Game() { Id = 7, Name = "Dark souls", Publisher = "Bandai Namco", ReleaseDate = DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60, 180),0,0,0)) },
                new Game() { Id = 8, Name = "Witcher", Publisher = "CD Project Red", ReleaseDate = DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60, 180),0,0,0)) },
            };
        }

        public List<Game> GetAllGames() { return Games; }
        public List<User> GetAllUsers() => context.Users.ToList();

        public void AddUser(User user)
        {
            Users.Add(user);
        }

        public Tuple<bool, User> Authenticate(User user)
        {
            foreach (var us in GetAllUsers())
            {
                if (us.UserName == user.UserName
                    && us.Password == user.Password)
                    return new Tuple<bool, User>(true, us);
            }
            return new Tuple<bool, User>(false, null);
        }

        
    }
}