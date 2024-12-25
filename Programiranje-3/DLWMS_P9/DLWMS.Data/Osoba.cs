using System.Collections;

namespace DLWMS.Data
{
    public  class Osoba : IEnumerable
    {

        public IEnumerator GetEnumerator()
        {
            //for (int i = 0; i < tezine.Length; i++)
            //    yield return tezine[i];

            yield return tezine[0];
            yield return tezine[1];
            yield return tezine[2];
            yield return tezine[3];





        }


        int[] tezine = new int[] { 65, 66, 82, 95, 86 };

        public int this[int index] {
            get { return tezine[index] ; }
            set { tezine[index] = value; }
        }

        public string ImePrezime { get; set; }
        public string Spol { get; set; }
        public DateTime DatumRodjenja { get; set; }
        public int? GradId { get; set; }

        public Osoba()
        {
            ImePrezime = Spol = "";
            DatumRodjenja = DateTime.MinValue;
        }

        public Osoba(string imePrezime, string spol, DateTime datumRodjenja, int ? gradId = null)
        {
            ImePrezime = imePrezime;
            Spol = spol;
            DatumRodjenja = datumRodjenja;
            GradId = gradId;
        }

      
        public override string ToString()
        {
            return PredsaviSe();
        }

        public  string PredsaviSe()
        {
            return $"{ImePrezime} ({Spol}) {DatumRodjenja.ToString("dd.MM.yyyy")} {GradId}";
        }

      
    }

}
