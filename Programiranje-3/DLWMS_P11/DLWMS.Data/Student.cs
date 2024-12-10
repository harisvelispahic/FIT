using System.Drawing;

namespace DLWMS.Data
{
    public class Student
    {
        public int Id { get; set; }
        public string Ime { get; set; }
        public string Prezime { get; set; }
        public DateTime DatumRodjenja { get; set; }
        public string Email { get; set; }
        public string BrojIndeksa { get; set; }
        public string Lozinka { get; set; }
        public int GradId { get; set; }
        public int SpolId { get; set; }

        //public Image[] Slika { get; set; }//byte[]
        public byte[] Slika { get; set; }//byte[]
        public bool Aktivan { get; set; }
        public List<PolozeniPredmet> Polozeni { get; set; }
        public Student()
        {
            Polozeni = new List<PolozeniPredmet>();
        }
    }
}