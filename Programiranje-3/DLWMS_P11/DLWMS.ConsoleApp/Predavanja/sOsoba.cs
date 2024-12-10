namespace DLWMS.ConsoleApp.Predavanja
{
    public struct sOsoba
    {
        public string ImePrezime { get; set; }
        public string Spol { get; set; }
        public DateTime DatumRodjenja { get; set; }

        public sOsoba()
        {
            ImePrezime = Spol = "";
            DatumRodjenja = DateTime.MinValue;
        }

        public sOsoba(string imePrezime, string spol, DateTime datumRodjenja)
        {
            ImePrezime = imePrezime;
            Spol = spol;
            DatumRodjenja = datumRodjenja;
        }

        public override string ToString()
        {
            return PredsaviSe();
        }

        public string PredsaviSe()
        {
            return $"{ImePrezime} ({Spol}) {DatumRodjenja.ToString("dd.MM.yyyy")}";
        }
    }

}
