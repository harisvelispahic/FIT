using TinyGameStore.Data;

namespace TinyGameStore.InMemory
{
    public class InMemoryDb
    {
        private List<User> Users { get; set; }

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
    }
}