using FIT.Infrastructure;
using Microsoft.Reporting.WinForms;
using System.Data;

namespace FIT.WinForms.Izvjestaji
{
    public partial class frmIzvjestaji : Form
    {
        public int DrzavaId { get; set; }
        DLWMSDbContext db = new();
        public frmIzvjestaji(int drzavaId)
        {
            InitializeComponent();
            DrzavaId = drzavaId;
        }

        private void frmIzvjestaji_Load(object sender, EventArgs e)
        {

            var drzava = db.DrzaveIB230172.Find(DrzavaId);
            var gradovi = db.GradoviIB230172.Where(x => x.DrzavaId == drzava.Id).ToList();

            var gradoviTabela = new DataSet1.GradoviDataTable();
            for (int i = 0; i < gradovi.Count; i++) {
                var red = gradoviTabela.NewGradoviRow();
                red.Rb = (i + 1).ToString();
                red.Grad = gradovi[i].Naziv;
                red.Drzava = drzava.Naziv;
                red.Aktivan = (gradovi[i].Status ? "DA" : "NE");

                gradoviTabela.AddGradoviRow(red);
            }

            var dsGradovi = new ReportDataSource();
            dsGradovi.Name = "DataSet1";
            dsGradovi.Value = gradoviTabela;


            var parametri = new ReportParameterCollection();
            parametri.Add(new ReportParameter("BrojGradova", gradovi.Count.ToString()));


            reportViewer1.LocalReport.DataSources.Add(dsGradovi);
            reportViewer1.LocalReport.SetParameters(parametri);
            reportViewer1.RefreshReport();
        }

        private void reportViewer1_Load(object sender, EventArgs e)
        {

        }
    }
}
