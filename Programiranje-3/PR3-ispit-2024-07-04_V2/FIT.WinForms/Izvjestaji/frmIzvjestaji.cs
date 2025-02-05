using Microsoft.EntityFrameworkCore;
using Microsoft.Reporting.WinForms;

namespace FIT.WinForms.Izvjestaji
{
    public partial class frmIzvjestaji : Form
    {
        public int UvjerenjeId {  get; set; }
        public frmIzvjestaji(int uvjerenjeId)
        {
            InitializeComponent();
            UvjerenjeId= uvjerenjeId;

        }

        private void frmIzvjestaji_Load(object sender, EventArgs e)
        {
            var uvjerenje = SharedContext.db.StudentiUvjerenjaIB230172.Find(UvjerenjeId);
            var student = SharedContext.db.Studenti.Find(uvjerenje.StudentId);

            var parametri = new ReportParameterCollection();

            parametri.Add(new ReportParameter("pImePrezime", student.ImePrezime));
            parametri.Add(new ReportParameter("pIndeks", student.Indeks));
            parametri.Add(new ReportParameter("pSvrha", uvjerenje.Svrha));
            parametri.Add(new ReportParameter("pStatus", (student.Aktivan) ? "AKTIVAN" : "NEAKTIVAN"));

            var listaPolozenih = SharedContext.db.PolozeniPredmeti
                .Include(x=>x.Predmet)
                .Where(x => x.StudentId == uvjerenje.StudentId)
                .ToList();

            parametri.Add(new ReportParameter("pBrojIspita", listaPolozenih.Count.ToString()));
            var text = "";
            for(int i = 0; i < listaPolozenih.Count; i++) {
                text += $"{listaPolozenih[i].Predmet.Naziv} ({listaPolozenih[i].Ocjena}), ";
            }
            parametri.Add(new ReportParameter("pListaIspita", text));
            parametri.Add(new ReportParameter("pProsjek", student.Prosjek.ToString()));


            reportViewer1.LocalReport.SetParameters(parametri);
            reportViewer1.RefreshReport();
        }
    }
}
