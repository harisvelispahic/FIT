using System.ComponentModel.DataAnnotations.Schema;
using System.Drawing;

namespace FIT.Data
{
    public class Student
    {
        public int Id { get; set; }
        public string Indeks { get; set; }
        public string Lozinka { get; set; }
        public string Ime { get; set; }
        public string Prezime { get; set; }
        public string Email { get; set; }
        public byte[] Slika { get; set; }
        public DateTime DatumRodjenja { get; set; }
        public bool Aktivan { get; set; }        
        public int SemestarId { get; set; }
        public override string ToString()
        {
            return $"{Indeks} {Ime} {Prezime}";
        }

        public List<PolozeniPredmeti> PolozeniPredmeti { get; set; } = new List<PolozeniPredmeti>();
        public List<StudentiUloge> StudentiUloge { get; set; } = new List<StudentiUloge>();

        [NotMapped]
        public string ImePrezime => $"{Ime} {Prezime} ({DateTime.Now.Year - DatumRodjenja.Year})";
        [NotMapped]
        public double Prosjek => PolozeniPredmeti.Where(x => x.StudentId == Id).ToList().Count == 0 ?
            0 :
            PolozeniPredmeti.Where(x => x.StudentId == Id).ToList().Average(x => x.Ocjena);
    }
}
