using DLWMS.Data;

using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

using System;
using System.Collections.Generic;
using System.Diagnostics.Metrics;
using System.Dynamic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace DLWMS.ConsoleApp.Predavanja
{
    internal class P8
    {
        public static void Pokreni()
        {
            //TipoviPodataka();
            //DinamicniTipPodatka();
            Linq();
        }

        private static void Linq()
        {
            /*
                FROM Customers
                WHERE Country = 'Germany'
                SELECT*
            */

            var ocjene = new List<int>() { 6, 6, 8, 7, 9, 6 , 10};

            var superDobreOcjene1 =   (from ocjena in ocjene
                                where ocjena > 8
                                select ocjena).ToList();
            
            var superDobreOcjene2 = ocjene.Where(o => o > 8).ToList();

            var superDobreOcjene3 = ocjene.Where(SuperDobreOcjene).ToList();



        }

        private static bool SuperDobreOcjene(int ocjena)
        {
            return ocjena > 8;
        }

        private static void DinamicniTipPodatka()
        {
            try
            {
                var adresaAPI = "https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&hourly=temperature_2m";

                var httpKlijent = new HttpClient();
                var httpOdgovor = httpKlijent.GetAsync(adresaAPI);
                var sadrzajHttpOdgovora = httpOdgovor.Result.Content.ReadAsStringAsync();
                dynamic temperature = JsonConvert.DeserializeObject(sadrzajHttpOdgovora.Result);

                for (int i = 0; i < temperature.hourly.time.Count; i++)
                    Console.WriteLine($"{temperature.hourly.time[i]} -> {temperature.hourly.temperature_2m[i]}");


            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }
        private static void TipoviPodataka()
        {
            object ime = "Denis";
            ime.ToString();

            var prezime = "Music";


            var jasmin = (id: 1, ime: "Jasmin", prezime: "Azemovic", prosjek: 8.5);
            var zanin = new { id= 2, ime= "Zanin", prezime= "Vejzovic", prosjek= 7.5};

            dynamic dinamicniObj;
            dinamicniObj = 2024;
            dinamicniObj = "Denis Music";
            dinamicniObj = new Student();
            dinamicniObj = new List<int>() { 6, 6, 8, 7, 9, 6 };

            Info(ime);
            Info(prezime);          
            //Info(dinamicniObj);//<<<

            Dictionary<string, int> rezultati = new Dictionary<string, int>();
            rezultati.Add("IB210012", 8);
            rezultati.Add("IB210056", 9);
            rezultati.Add("IB210076", 5);
            rezultati.Add("IB210078", 8);
            foreach (var rezultat in rezultati)
                Console.WriteLine($"{rezultat.Key} -> {rezultat.Value}" );

            Console.WriteLine(Environment.NewLine);


            dynamic obj = new ExpandoObject();
            obj.Id = 1;
            obj.Indeks = "IB210012";
            obj.ImePrezime = "Denis Music";
            foreach (var osobina in obj)
                Console.WriteLine($"{osobina.Key} -> {osobina.Value}");

            Console.WriteLine(Environment.NewLine);
            
            string json = @"{
                'Id': 1,
                'Indeks': 'IB210012',
                'ImePrezime': 'Denis Music'
            }";
            dynamic objFromJson = JsonConvert.DeserializeObject(json);           

            Console.WriteLine($"Indeks {objFromJson.Indeks}");


        }
        private static void Info(dynamic obj)
        {
            var sadrzaj = obj.ToUpper();
        }
    }
}
