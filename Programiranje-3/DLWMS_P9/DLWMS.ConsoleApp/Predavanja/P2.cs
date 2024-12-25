using DLWMS.Data;
using DLWMS.Infrastructure;

using System.Text;

namespace DLWMS.ConsoleApp.Predavanja
{
    internal class P2
    {
        static ILogger Logger;// = new FileLogger();

        public static void Pokreni(ILogger logger)//FileLogger ili DBLogger
        {
            Logger = logger;
            //Slojevi();
            //NullVrijednosti();
            //Var();
            //Imutabilnost();
            //Params();
            //Indeksri();
            Nasljedjivanje();
            Interfejsi(new Ucenik());           
        }

        private static void Interfejsi(IOdgoj odgoj)
        {
            odgoj.PredstaviSe();

            IOdgoj odgoj1 = new Ucenik();
            IOdgoj odgoj2 = new Polaznik();
            
            Logger.Log(DateTime.Now, "Pozvana metoda interfejsi");


            Osoba osoba = new Osoba("Jasmin Azemovic", "M", new System.DateTime(1983, 1, 1));
            
            foreach (var tezina in osoba)
            {
                Console.WriteLine(tezina);
            }

        }

        private static void Nasljedjivanje()
        {
            Osoba osoba = new Osoba("Jasmin Azemovic", "M", new System.DateTime(1983, 1, 1));
            Osoba student = new StudentInit("IB120021", "Denis Music", "M", new System.DateTime(1983, 1, 1));
            
            OsobaInfo(osoba);
            OsobaInfo(student);
            Logger.Log(DateTime.Now, "Demonstrirano nasljedjivanje");

        }

        private static void OsobaInfo(Osoba osoba)
        {
            if (osoba is StudentInit student)
                Console.WriteLine($"Student -> {student.BrojIndeksa} {student.ImePrezime}");
            else
                Console.WriteLine($"Osoba -> {osoba.ImePrezime}");


            if (osoba is StudentInit)
            {
                StudentInit student1 = (StudentInit)osoba;
                StudentInit student2 = osoba as StudentInit;//null dynamic_cast<Student*>(osoba)
                Console.WriteLine($"Student -> {student1.BrojIndeksa} {student1.ToString()}");
            }
            else
                Console.WriteLine($"Osoba -> {osoba}");


        }

        private static void Indeksri()
        {
            var osoba = new Osoba("Denis Music", "M", new System.DateTime(1983, 1, 1));
            osoba[0] = 55;
        }

        private static void Params()
        {
            var ispis = string.Join(" * ", 2024, "FIT", "Denis", 215, 3.5, "Mostar");
            Console.WriteLine(ispis);
            Console.WriteLine($"Suma -> { Sumiraj(new int[] { 5, 889, 8, 15, 65 }) }");
            Console.WriteLine($"Suma -> {Sumiraj(5, 889, 8, 15, 65, 150, 654)}");
        }

        private static object Sumiraj(params int[] niz)
        {
            int suma = 0;
            for (int i = 0; i < niz.Length; i++)
                suma += niz[i];
            return suma;
        }

        private static void Imutabilnost()
        {            
            string ime = "Denis";
            ime = ime.ToUpper();
            Console.WriteLine(ime);

            DateTime danas = DateTime.Now;
            DateTime buducnost =  danas.AddDays(150);
            Console.WriteLine(danas.ToString("dd.MM.yyyy"));
            Console.WriteLine(buducnost.ToString("dd.MM.yyyy"));

        }

        private static void Var()
        {
            var broj = 5;
            var osoba = new Osoba("Denis Music", "M", new System.DateTime(1983, 1, 1));
            var ime = "Denis";

            OsobaServis osobeServis = new OsobaServis();
            var osobe = osobeServis.GetOsobeByOpstina("Mostar");

            var appDomainUnloadedException = new AppDomainUnloadedException();

            Osoba denis = new();
        }

        private static void NullVrijednosti()
        {
            int ? brojIndeksa = null;//0

            OsobaServis osobeServis = new OsobaServis();
            Osoba osoba = new Osoba("Emina Junuz", "Z", DateTime.Now, null);    
            //osobeServis.GetOsobaByJMBG("1234567890123");

            string datumRodjenja = osoba?.DatumRodjenja.ToString() ?? "Datum rodjenja nepoznat";

            Console.WriteLine(datumRodjenja);
        }

        private static void Slojevi()
        {
            OsobaServis osobeServis = new OsobaServis();
            List<Osoba> osobe = osobeServis.GetOsobeByOpstina("Mostar");
            Console.WriteLine($"Broj osoba -> {osobe.Count}");
        }
    }

    public interface ILogger
    {
        void Log(DateTime datumVrijeme, string poruka);
    }
    public class FileLogger : ILogger
    {
        const string putanja = "log.txt";

        void ILogger.Log(DateTime datumVrijeme, string poruka)
        {
            throw new NotImplementedException();
        }
        //public void Log(DateTime datumVrijeme, string poruka)
        //{
        //    Console.WriteLine($"{putanja} -> {datumVrijeme.ToString("dd.MM.yyyy HH:mm:ss")} : {poruka}");
        //}
    }
    public class DBLogger : ILogger
    {
        const string putanja = "DBServer 192.168.1.1";//server = , dataase = , user = , pass =
        public void Log(DateTime datumVrijeme, string poruka)
        {
            Console.WriteLine($"{putanja} -> {datumVrijeme.ToString("dd.MM.yyyy HH:mm:ss")} : {poruka}");
        }
    }


    public interface IOdgoj
    {
        string PredstaviSe();
    }

    public class Polaznik : IOdgoj
    {
        public string PredstaviSe()
        {
            return "";
        }
    }

    public class Ucenik : IOdgoj
    {
        public string PredstaviSe()
        {
            return "";
        }
    }


}
