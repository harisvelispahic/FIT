using Microsoft.Reporting.WinForms;

namespace FIT.WinForms.Izvjestaji
{
    public partial class frmIzvjestaji : Form
    {
        public int DrzavaId {  get; set; }
        public frmIzvjestaji(int drzavaId)
        {
            InitializeComponent();
            DrzavaId = drzavaId;

        }

        private void frmIzvjestaji_Load(object sender, EventArgs e)
        {
            var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);

            dsGradovi dsGradovi = new dsGradovi();
            var gradoviTabela = new dsGradovi.dtGradoviDataTable();

            for (int i = 0; i < drzava.GradoviIB230172.Count; i++) 
            {
                var red = gradoviTabela.NewdtGradoviRow();
                red.Rb = (i + 1).ToString();
                red.Grad = drzava.GradoviIB230172[i].Naziv;
                red.Drzava = drzava.Naziv;
                red.Aktivan = drzava.GradoviIB230172[i].Status ? "DA" : "NE";

                gradoviTabela.AdddtGradoviRow(red);
            }

            var rdsGradovi = new ReportDataSource();
            rdsGradovi.Name = "DataSet1";
            rdsGradovi.Value = gradoviTabela;


            var parametri = new ReportParameterCollection();
            parametri.Add(new ReportParameter("pBrojGradova", (drzava.GradoviIB230172.Count).ToString()));


            reportViewer1.LocalReport.DataSources.Add(rdsGradovi);
            reportViewer1.LocalReport.SetParameters(parametri);
            reportViewer1.RefreshReport();
        }
    }
}
