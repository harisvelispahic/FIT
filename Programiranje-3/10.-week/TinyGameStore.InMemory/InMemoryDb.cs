using TinyGameStore.Data;

namespace TinyGameStore.InMemory
{
    public class InMemoryDb
    {
        private List<User> Users { get; set; }
        private List<Game> Games { get; set; }

        // ovdje treba List<UsersGame>

        public InMemoryDb()
        {
            FillMockData();
        }

        public void FillMockData()
        {
            Users = new List<User>() {
                new User() { UserName = "JonDoe", Password = "ILikeCats" },
                new User() { UserName = "admin", Password = "test123" },
                new User() { UserName = "user", Password = "user" },
                new User() { UserName = "TonyStark", Password = "ILoveYou3000" },
                new User() { UserName = "JohnWick", Password = "CanYouLikeDogs" },
                new User() { UserName = "Tarnished", Password = "FindTheRing" },
                new User() { UserName = "Hollow", Password = "Andre" }
                };

            Games = new List<Game>() {
                new Game() { Id = 1, Name="Assassin's Creed II", Publisher="Ubisoft", ReleaseDate=DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60,180),0,0,0))},
                new Game() { Id = 2, Name="Rocket League", Publisher="Psyonix", ReleaseDate=DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60,180),0,0,0))},
                new Game() { Id = 3, Name="Counter Strike 1.6", Publisher="Valve", ReleaseDate=DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60,180),0,0,0))},
                new Game() { Id = 4, Name="Half life 2", Publisher="Valve", ReleaseDate=DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60,180),0,0,0))},
                new Game() { Id = 5, Name="Red Dead Redemption II", Publisher="Rockstar Games", ReleaseDate=DateTime.Now.Subtract(new TimeSpan(Random.Shared.Next(60,180),0,0,0))},
            };
        }

        public void AddUser(User user)
        {
            Users.Add(user);
        }

        public bool Authenticate(User user)
        {
            foreach (var us in Users)
            {
                if (us.UserName == user.UserName
                    && us.Password == user.Password)
                    return true;
            }
            return false;
        }

        public List<Game> GetGames()
        {
            return Games;
        }

        public List<User> GetUsers()
        {
            return Users;
        }

        //public List<UsersGame> GetUsersGames()
        //{
            
        //}
    }
}