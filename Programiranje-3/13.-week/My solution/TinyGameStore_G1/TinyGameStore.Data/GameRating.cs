using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TinyGameStore.Data
{
    [Table("GamesRatings")]
    public class GameRating
    {
        public int Id { get; set; }
        public int UserGamesId { get; set; }
        public int Rating { get; set; }
        public virtual UsersGame UsersGame { get; set; }
    }
}
