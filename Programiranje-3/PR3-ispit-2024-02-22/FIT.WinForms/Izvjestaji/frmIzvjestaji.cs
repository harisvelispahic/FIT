using FIT.Infrastructure;
using Microsoft.EntityFrameworkCore;
using Microsoft.Reporting.WinForms;
using System.Data;
using System.Net.NetworkInformation;

namespace FIT.WinForms.Izvjestaji
{
    public partial class frmIzvjestaji : Form
    {
        public int ProstorijaId{ get; set; }
        DLWMSDbContext db = new();
        public frmIzvjestaji(int prostorijaId)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;
        }

        private void frmIzvjestaji_Load(object sender, EventArgs e)
        {
            var prostorija = db.ProstorijeIB230172.Find(ProstorijaId);
            //var nastava = db.NastavaIB230172.Where(x => x.ProstorijaId == ProstorijaId).ToList();
            var prisustvo = db.PrisustvoIB230172
                .Include(x => x.Nastava)
                .ThenInclude(n=>n.Predmet)
                .Include(p=>p.Student)
                .Where(x => x.Nastava.ProstorijaId == ProstorijaId)
                .ToList();

            var parametri = new ReportParameterCollection();
            parametri.Add(new ReportParameter("pNazivProstorije", prostorija.Naziv));
            parametri.Add(new ReportParameter("pBrojStudenata", prisustvo.Count.ToString()));

            var tblPrisustva = new Prostorije.dtProstorijeDataTable();
            for (int i = 0; i < prisustvo.Count; i++) {
                var red = tblPrisustva.NewdtProstorijeRow();
                red.Rb = (i + 1).ToString();
                red.Predmet = prisustvo[i].Nastava.Predmet.Naziv.ToString();
                red.Vrijeme = prisustvo[i].Nastava.Vrijeme;
                red.BrojIndeksa = prisustvo[i].Student.Indeks.ToString();
                red.ImePrezime = $"{prisustvo[i].Student.Ime} {prisustvo[i].Student.Prezime}";

                tblPrisustva.AdddtProstorijeRow(red);
            }

            var dsPrisustva = new ReportDataSource();
            dsPrisustva.Name = "Prostorije";
            dsPrisustva.Value = tblPrisustva;

            reportViewer1.LocalReport.DataSources.Add(dsPrisustva);
            reportViewer1.LocalReport.SetParameters(parametri);
            reportViewer1.RefreshReport();
        }
    }
}
