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
        
        public int GradId {  get; set; }
        public GradoviIB230172 Grad {  get; set; }
        public override string ToString()
        {
            return $"{Indeks} {Ime} {Prezime}";
        }

        public List<PolozeniPredmeti> PolozeniPredmeti { get; set; } = new();


        [NotMapped]
        public string GradNaziv => Grad.Naziv;
        [NotMapped]
        public double Prosjek => PolozeniPredmeti.Where(x => x.StudentId == Id).ToList().Count == 0 ?
            5 :
            PolozeniPredmeti.Where(x => x.StudentId == Id).Average(x => x.Ocjena);
    }
}
