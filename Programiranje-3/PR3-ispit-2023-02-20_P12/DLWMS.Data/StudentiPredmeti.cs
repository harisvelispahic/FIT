using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DLWMS.Data
{
    public class StudentiPredmeti
    {
        public int Id { get; set; }
        public int StudentId { get; set; }
        public Student Student { get; set; }
        public int PredmetId { get; set; }
        public Predmeti Predmet { get; set; }
        public int Ocjena { get; set; }
        public DateTime Datum { get; set; }
    }
}
