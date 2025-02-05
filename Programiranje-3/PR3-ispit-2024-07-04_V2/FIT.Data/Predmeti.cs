using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class Predmeti
    {
        public int Id { get; set; }
        public string Naziv { get; set; }
        public int Semestar{ get; set; }

        public List<PolozeniPredmeti> PolozeniPredmeti { get; set; } = new List<PolozeniPredmeti>();

    }
}
