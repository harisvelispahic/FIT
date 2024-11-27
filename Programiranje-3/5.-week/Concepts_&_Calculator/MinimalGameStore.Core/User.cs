using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace MinimalGameStore.Core
{
    public class User
    {
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public DateTime BirthDate { get; set; }
        public List<Game> Games { get; set; }

        public User(int id, string firstName, string lastName, DateTime birthDate, List<Game> games)
        {
            Id = id;
            FirstName = firstName;
            LastName = lastName;
            BirthDate = birthDate;
            Games = games;
        }

        public User()
        {
        }

        public override string ToString()
        {
            string output = "";
            for (int i = 0; i < Games.Count; i++)
            {
                output += Games[i].ToString();
            }
            return $"Id: {Id}\nFirst name: {FirstName}\nLast name: {LastName}\nBirth date: {BirthDate}\nGames:\n{output}";
        }
    }
}
