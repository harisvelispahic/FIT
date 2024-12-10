

using DLWMS.Data;

using System.Runtime.Versioning;

namespace DLWMS.ConsoleApp.Predavanja
{
    internal class P1
    {
        public static void Pokreni()
        {
            //OsnovniTipoviPodataka();
            //Klase();
            //BazniTip();
            VrijednistiRefrence();
        }
        private static void VrijednistiRefrence()
        {
            int a = 0;
            int b = new int();//0

            if(a == b)
                Console.WriteLine("b == a");

            Osoba denis = new Osoba();
            denis.Spol = "M";

            KlaseIStrukture();
            Nizovi();
        }
        private static void Nizovi()
        {
            int[] niz1 = [1, 2, 3, 4, 5];
            int[] niz2 = [55, 8 , 924, 16];

            int[] niz3 = [..niz1, ..niz2];
            foreach (var el in niz3)
                Console.Write($"{el}, ");
            Console.WriteLine(Prikazi.Crtice);


            Osoba[] mostar = new Osoba[3];
            sOsoba[] sarajevo = new sOsoba[3];

            for (int i = 0; i < sarajevo.Length; i++)
            {
                sarajevo[i].Spol = "M";
                sarajevo[i].ImePrezime = $"Osoba {i}";
                sarajevo[i].DatumRodjenja = new DateTime(1980, 1, 1).AddYears(i);
            }

            for (int i = 0; i < mostar.Length; i++)
            {
                mostar[i] = new Osoba();
                mostar[i].Spol = "M";
                mostar[i].ImePrezime = $"Osoba {i}";
                mostar[i].DatumRodjenja = new DateTime(1980, 1, 1).AddYears(i);
            }
        }
        private static void KlaseIStrukture()
        {

            Osoba adel1 = new Osoba("Adel Handzic", "M", new DateTime(1980, 3, 3));
            Osoba adel2 = adel1;
            Console.WriteLine($"{adel1}{Environment.NewLine}{adel2}{Prikazi.Crtice}");
            adel1.ImePrezime = "Goran Skondric";
            Console.Write($"{adel1}{Environment.NewLine}{adel2}{Prikazi.Crtice}");


            sOsoba goran1 = new sOsoba("Goran Skondric", "M", new DateTime(1980, 3, 3));
            sOsoba goran2 = goran1;
            Console.WriteLine($"{goran1}{Environment.NewLine}{goran2}{Prikazi.Crtice}");
            goran1.ImePrezime = "Adel Handzic";
            Console.Write($"{goran1}{Environment.NewLine}{goran2}{Prikazi.Crtice}");
        }
        private static void BazniTip()
        {
            int indeks = 230032;
            string imePrezime = "Denis Music";

            indeks.ToString();

            Osoba denis = new Osoba();
            denis.Spol = "M";
            denis.ImePrezime = "Denis Music";
            denis.DatumRodjenja = new DateTime(1980, 1, 1);

            object oOsoba = denis;
            object oIndeks = indeks;
            object oImePrezime = imePrezime;

            oOsoba.ToString();

            FromObject(oIndeks);
            FromObject(oOsoba);
        }
        private static void FromObject(object obj)
        {
            if(obj is int)
                Console.WriteLine($"Int: {obj}");
            else if (obj is Osoba)
                Console.WriteLine($"Osoba: {((Osoba)obj).PredsaviSe()}");
        }
        private static void Klase()
        {
            Osoba denis = new Osoba();
            denis.Spol = "M";          
            denis.ImePrezime = "Denis Music";
            denis.DatumRodjenja = new DateTime(1980, 1, 1);

            Console.WriteLine(denis);

            Osoba jasmin = new Osoba()
            {
                ImePrezime = "Jasmin Azemovic",
                Spol = "M",
                DatumRodjenja = new DateTime(1979, 2, 2)
            };
            Console.WriteLine(jasmin);

            Osoba adel = new Osoba("Adel Handzic", "M", new DateTime(1980, 3, 3));
            Console.WriteLine(adel);


            Nastava prIII = new Nastava("Programiranje III", 2);

        }
        private static void OsnovniTipoviPodataka()
        {
            string ime = "John";
            int godine = 30;
            double plata = 1000.50;

            Console.WriteLine("Ime: " + ime + " starost: " + godine + " plata: " + plata);
            Console.WriteLine($"Ime: {ime} starost: {godine} plata: {plata}");
        }
    }

    public class Nastava(string predmet, int brojSati)
    {
        public int BrojSati => brojSati;
        public string Predmet = predmet;
    }
    public class Prikazi
    {
        public static string Crtice { get; set; } = "\n----------------------------\n";
    }
    public class AppInfo {
        public const string Naziv = "DLWMS App";
        public readonly string Verzija;

        public AppInfo(string verzija) 
        {
            Verzija = verzija;
        }      

    }
}
