using DLWMS.Data;

using System.Diagnostics.CodeAnalysis;

namespace DLWMS.Infrastructure
{
    public class OsobaServis
    {
        public Osoba GetOsobaByJMBG(string jmbg)
        {
            return null;
        }

        public List<Osoba> GetOsobeByOpstina(string opstina)
        {
            //Osoba osoba1 = new Osoba("Denis Music", "M", new DateTime(1983, 1, 1));
            //Osoba osoba2 = new Osoba("Jasmin Azemovic", "M", new DateTime(1983, 1, 1));

            //List<Osoba> osobe = new List<Osoba>();
            //osobe.Add(osoba1);
            //osobe.Add(osoba2);           

            //return osobe;

            return new List<Osoba>()
            {
                new Osoba("Denis Music", "M", new DateTime(1983, 1, 1)),
                new Osoba("Jasmin Azemovic", "M", new DateTime(1983, 1, 1))
            };
        }
    }
}
