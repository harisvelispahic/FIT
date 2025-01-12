using FIT.Infrastructure;
using Microsoft.Reporting.WinForms;
using System.Reflection.Metadata.Ecma335;

namespace FIT.WinForms.Izvjestaji
{
    public partial class frmIzvjestaji : Form
    {
        DLWMSDbContext db;
        public int UvjerenjeId {  get; set; }
        public frmIzvjestaji(int uvjerenjeId)
        {
            InitializeComponent();
            db = new();
            UvjerenjeId = uvjerenjeId;
            
        }

        private void frmIzvjestaji_Load(object sender, EventArgs e)
        {
            var uvjerenje = db.StudentiUvjerenja.Find(UvjerenjeId);
            var student = db.Studenti.Find(uvjerenje.StudentId);


            var parametri = new ReportParameterCollection();
            parametri.Add(new ReportParameter("pImePrezime", $"{student.Ime} {student.Prezime}"));
            parametri.Add(new ReportParameter("pIndeks", student.Indeks));
            parametri.Add(new ReportParameter("pSvrha", uvjerenje.Svrha));
            string status = student.Aktivan ? "Aktivan" : "Neaktivan";
            parametri.Add(new ReportParameter("pStatus", status));

            var polozeniPredmeti = db.PolozeniPredmeti.Where(pp => pp.StudentId == student.Id).ToList();
            parametri.Add(new ReportParameter("pBrojPolozenihIspita", polozeniPredmeti.Count.ToString()));
            string ispitiStr = "";
            foreach(var item in polozeniPredmeti) {
                var predmet = db.Predmeti.Find(item.PredmetId);
                ispitiStr += $"{predmet.Naziv} ({item.Ocjena}), ";
            }
            parametri.Add(new ReportParameter("pListaIspita", ispitiStr));
            parametri.Add(new ReportParameter("pProsjek", polozeniPredmeti.Average(pp => pp.Ocjena).ToString()));

            reportViewer1.LocalReport.SetParameters(parametri);

            reportViewer1.RefreshReport();
        }
    }
}
