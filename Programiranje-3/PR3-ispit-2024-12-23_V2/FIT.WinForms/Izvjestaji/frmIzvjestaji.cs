using Microsoft.EntityFrameworkCore;
using Microsoft.Reporting.WinForms;

namespace FIT.WinForms.Izvjestaji
{
    public partial class frmIzvjestaji : Form
    {
        public int StudentId { get; set; }
        public frmIzvjestaji(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;

        }

        private void frmIzvjestaji_Load(object sender, EventArgs e)
        {

            var student = SharedContext.db.Studenti.Find(StudentId);
            var studentiPoruke = SharedContext.db.StudentiPorukeIB230172
                .Include(x => x.Student)
                .Include(x => x.Predmet)
                .Where(x => x.StudentId == this.StudentId)
                .ToList();

            var porukeTabela = new dsStudentiPoruke.dtStudentiPorukeDataTable();

            int brojZnakova = 0;

            for(int i = 0; i < studentiPoruke.Count; i++) {
                var red = porukeTabela.NewdtStudentiPorukeRow();
                var trenutnaPoruka = studentiPoruke[i];

                red["Rb"] = (i + 1).ToString();
                red["Predmet"] = trenutnaPoruka.Predmet.Naziv;
                red["Poruka"] = trenutnaPoruka.Sadrzaj;
                red["BrojZnakova"] = trenutnaPoruka.Sadrzaj.Length;
                red["Validnost"] = trenutnaPoruka.Validnost;

                porukeTabela.AdddtStudentiPorukeRow(red);

                brojZnakova += trenutnaPoruka.Sadrzaj.Length;
            }

            var rds = new ReportDataSource();
            rds.Name = "dsStudentiPoruke";
            rds.Value = porukeTabela;


            var parametri = new ReportParameterCollection();

            parametri.Add(new ReportParameter("pImePrezime", student.ImePrezime));
            parametri.Add(new ReportParameter("pBrojPoruka", studentiPoruke.Count.ToString()));
            var prosjek = studentiPoruke.Count == 0 ? 0 : brojZnakova / studentiPoruke.Count;
            parametri.Add(new ReportParameter("pProsjecnoKaraktera", prosjek.ToString()));


            reportViewer1.LocalReport.DataSources.Add(rds);
            reportViewer1.LocalReport.SetParameters(parametri);
            reportViewer1.RefreshReport();
        }

        private void reportViewer1_Load(object sender, EventArgs e)
        {

        }
    }
}
