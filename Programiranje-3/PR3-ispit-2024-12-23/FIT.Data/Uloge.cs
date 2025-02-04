using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class Uloge
    {
        public int Id { get; set; }
        public string Naziv { get; set; }

        public List<StudentiUloge> StudentiUloge { get; set; } = new List<StudentiUloge>();
    }
}
