using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.Reporting.WinForms;

namespace FIT.WinForms.Izvjestaji
{
    public partial class frmIzvjestaji : Form
    {
        public int ProstorijaId {  get; set; }
        public frmIzvjestaji(int prostorijaId)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;

        }

        private void frmIzvjestaji_Load(object sender, EventArgs e)
        {

            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);

            var listaPrisustava = SharedContext.db.PrisustvoIB230172
                .Include(x => x.Nastava)
                .ThenInclude(x => x.Predmet)
                .Include(x => x.Student)
                .Where(x => x.Nastava.ProstorijaId == this.ProstorijaId)
                .ToList();

            var tabelaNastava = new dsProstorije.dtProstorijeDataTable();

            for(int i = 0; i < listaPrisustava.Count; i++) {
                var red = tabelaNastava.NewdtProstorijeRow();
                red["Rb"] = (i + 1).ToString();
                red["Predmet"] = listaPrisustava[i].Nastava.Predmet.Naziv;
                red["Vrijeme"] = listaPrisustava[i].Nastava.Vrijeme;
                red["BrojIndeksa"] = listaPrisustava[i].Student.Indeks;
                red["ImePrezime"] = $"{listaPrisustava[i].Student.Ime} {listaPrisustava[i].Student.Prezime}";

                tabelaNastava.Rows.Add(red);
            }

            var rds = new ReportDataSource();
            rds.Name = "dsProstorije";
            rds.Value = tabelaNastava;

            var parametri = new ReportParameterCollection();
            parametri.Add(new ReportParameter("pNazivProstorije", prostorija.Naziv));
            parametri.Add(new ReportParameter("pBrojStudenata", listaPrisustava.Count.ToString()));


            reportViewer1.LocalReport.SetParameters(parametri);
            reportViewer1.LocalReport.DataSources.Add(rds);
            reportViewer1.RefreshReport();
        }
    }
}
