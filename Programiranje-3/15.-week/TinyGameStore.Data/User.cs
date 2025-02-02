using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TinyGameStore.Data
{
    public class User
    {
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string UserName { get; set; }
        public DateTime Birthdate { get; set; }
        public string Password { get; set; }

        public virtual List<UsersGame> UsersGames { get; set; } = new List<UsersGame>();
    }
}
