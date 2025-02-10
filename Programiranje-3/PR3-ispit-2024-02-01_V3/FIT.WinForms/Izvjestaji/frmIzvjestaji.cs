using Microsoft.EntityFrameworkCore;
using Microsoft.Reporting.WinForms;

namespace FIT.WinForms.Izvjestaji
{
    public partial class frmIzvjestaji : Form
    {
        public int DrzavaId { get; set; }
        public frmIzvjestaji(int drzavaId)
        {
            InitializeComponent();
            DrzavaId = drzavaId;

        }

        private void frmIzvjestaji_Load(object sender, EventArgs e)
        {
            var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);
            var listaGradova = SharedContext.db.GradoviIB230172
                .Include(x => x.Drzava)
                .Where(x => x.DrzavaId == DrzavaId)
                .ToList();

            var tabelaDrzava = new dsGradovi.dtGradoviDataTable();
            for(int i = 0; i < listaGradova.Count; i++) {
                var red = tabelaDrzava.NewdtGradoviRow();

                red["Rb"] = (i + 1).ToString();
                red["Grad"] = listaGradova[i].Naziv;
                red["Drzava"] = drzava.Naziv;
                string aktivan = listaGradova[i].Status ? "DA" : "NE";
                red["Aktivan"] = aktivan;

                tabelaDrzava.Rows.Add(red);
            }

            var rds = new ReportDataSource();
            rds.Name = "dsGradovi";
            rds.Value = tabelaDrzava;


            var parametri = new ReportParameterCollection();
            parametri.Add(new ReportParameter("pBrojGradova", listaGradova.Count.ToString()));

            reportViewer1.LocalReport.DataSources.Add(rds);
            reportViewer1.LocalReport.SetParameters(parametri);
            reportViewer1.RefreshReport();
        }

        private void reportViewer1_Load(object sender, EventArgs e)
        {

        }
    }
}
