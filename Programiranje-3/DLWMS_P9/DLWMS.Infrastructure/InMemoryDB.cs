using DLWMS.Data;

namespace DLWMS.Infrastructure
{
    public class InMemoryDB
    {
        public static List<Korisnik> Korisnici { get; set; } = GenerisKorisnike();
        public static List<Spol> Spolovi { get; set; } = GenerisSpolove();
        public static List<Drzava> Drzave{ get; set; } = GenerisDrzave();
        public static List<Grad> Gradovi { get; set; } = GenerisGradove();
        public static List<Student> Studenti { get; set; } = GenerisStudente();

        private static List<Student> GenerisStudente()
        {
            return new List<Student>
            {
                new Student() { Id = 1, Ime = "John", Prezime = "Doe", DatumRodjenja = DateTime.Now, Email = "john.doe@fit.ba", Aktivan = true, BrojIndeksa = "IB150051", Lozinka = "johndoe", SpolId = 1, GradId = 1, Slika = null },
                new Student() { Id = 2, Ime = "Denis", Prezime = "Music",DatumRodjenja = DateTime.Now, Email = "denis.music@fit.ba", Aktivan = true, BrojIndeksa = "IB150052", Lozinka = "denis", SpolId = 1, GradId = 1,Slika = null },
                new Student() { Id = 3, Ime = "Jasmin", Prezime = "Azemovic", DatumRodjenja = DateTime.Now, Email = "jasmin.azemovic@fit.ba", Aktivan = true, BrojIndeksa = "IB150053", Lozinka = "jasmin", SpolId = 1, GradId = 1,Slika = null },
            };
        }

        private static List<Spol> GenerisSpolove()
        {
            return new List<Spol>
            {
                new Spol() { Id = 1, Naziv = "*********", Aktivan = true},
                new Spol() { Id = 2, Naziv = "Ženski", Aktivan = true},
                new Spol() { Id = 3, Naziv = "Muški", Aktivan = true},

            };
        }


        private static List<Drzava> GenerisDrzave()
        {
            return new List<Drzava>
            {
                new Drzava() { Id = 1, Naziv = "Bosna i Hercegovina", Oznaka = "BIH", Aktivan = true},
                new Drzava() { Id = 2, Naziv = "Hrvatska", Oznaka = "HR", Aktivan = true},
                new Drzava() { Id = 3, Naziv = "Srbija", Oznaka = "SRB", Aktivan = true},
            };
        }


        private static List<Grad> GenerisGradove()
        {
            return new List<Grad>
            {
                new Grad() { Id = 1, Naziv = "Mostar", DrzavaId = 1, Oznaka = "MO", Aktivan = true},
                new Grad() { Id = 2, Naziv = "Sarajevo", DrzavaId = 1, Oznaka = "SA", Aktivan = true},
                new Grad() { Id = 3, Naziv = "Zagreb",  DrzavaId = 2, Oznaka = "ZG", Aktivan = true},
                new Grad() { Id = 4, Naziv = "Beograd",  DrzavaId = 3, Oznaka = "BG", Aktivan = true},

            };
        }

        private static List<Korisnik> GenerisKorisnike()
        {
            return new List<Korisnik>
            {
                new Korisnik() { Id = 1, Ime = "John", Prezime = "Doe", Email = "john.doe@fit.ba", Aktivan = true, KorisnickoIme = "johndoe", Lozinka = "johndoe" },
                new Korisnik() { Id = 2, Ime = "Denis", Prezime = "Music", Email = "denis.music@fit.ba", Aktivan = true, KorisnickoIme = "denis", Lozinka = "denis" },
                new Korisnik() { Id = 3, Ime = "Jasmin", Prezime = "Azemovic", Email = "jasmin.azemovic@fit.ba", Aktivan = true, KorisnickoIme = "jasmin", Lozinka = "jasmin" },
            };
        }
    }
}
