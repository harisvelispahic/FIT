using System.Text.Json;
using System.IO;

namespace Data
{
    public class User
    {
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string Username { get; set; }
        public string Password { get; set; }
        public bool IsActive { get; set; }

        public User(int id, string firstName, string lastName, string username, string password)
        {
            Id = id;
            FirstName = firstName;
            LastName = lastName;
            Username = username;
            Password = password;
            IsActive = true;
        }
        public User()
        {
            
        }
    }

    public static class InternalDB
    {
        public static int IDCounter { get; set; } = 0;

        public static List<User> users = new List<User>();

        private static readonly string filePath = "users.json";

        public static void SaveUsers()
        {
            var options = new JsonSerializerOptions { WriteIndented = true };
            File.WriteAllText(filePath, JsonSerializer.Serialize(users, options));
        }

        public static void LoadUsers()
        {
            if (File.Exists(filePath)) {
                var jsonData = File.ReadAllText(filePath);
                users = JsonSerializer.Deserialize<List<User>>(jsonData) ?? new List<User>();
                IDCounter = users.Any() ? users.Max(u => u.Id) + 1 : 0;  // Ensure IDCounter is set correctly
            }
        }
    }
}
