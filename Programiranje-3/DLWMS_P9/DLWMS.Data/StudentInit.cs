namespace DLWMS.Data
{
    public class StudentInit : Osoba
    {
        public string BrojIndeksa { get; set; }

        public StudentInit()
        {
            
        }

        public StudentInit(string brojIndeksa, string imePrezime, string spol, 
            DateTime datumRodjenja, int? gradId = null)
            : base(imePrezime, spol, datumRodjenja, gradId)
        { 
            BrojIndeksa = brojIndeksa;
        }
        public void PrijaviIspit()
        {

        }       
    }

}
