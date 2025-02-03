using FIT.Data;
using FIT.Infrastructure;
using FIT.WinForms.Helpers;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Update;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms
{
    public partial class frmPrisustvoIB230172 : Form
    {
        public int ProstorijaId { get; set; }
        DLWMSDbContext db = new();
        public frmPrisustvoIB230172(int prostorijaId)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;
        }

        private void frmPrisustvoIB230172_Load(object sender, EventArgs e)
        {
            var prostorija = db.ProstorijeIB230172.Find(ProstorijaId);

            lblNaziv.Text = $"{prostorija.Naziv} - {prostorija.Oznaka}";

            cmbNastava.UcitajPodatke(db.NastavaIB230172.Where(x => x.ProstorijaId == ProstorijaId).ToList(), "Oznaka");
            cmbStudent.UcitajPodatke(db.Studenti.ToList(), "studentDto");

            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            var nastavacmb = cmbNastava.SelectedItem as NastavaIB230172;

            var prisustva = db.PrisustvoIB230172.Include(x => x.Nastava).Where(x => x.Nastava.ProstorijaId == ProstorijaId && x.Nastava.Id == nastavacmb.Id).ToList();

            lblKapacitet.Text = $"{db.PrisustvoIB230172.Include(x => x.Nastava).Where(x => x.Nastava.ProstorijaId == ProstorijaId).ToList().Count}/{db.ProstorijeIB230172.Find(ProstorijaId).Kapacitet}";

            var dt = new DataTable();
            //dt.Columns.Add("Id");
            dt.Columns.Add("PredmetProstorijaVrijeme");
            dt.Columns.Add("Student");

            for (int i = 0; i < prisustva.Count; i++) {
                var dr = dt.NewRow();

                var nastava = prisustva[i].Nastava;

                //dr["Id"] = prisustva[i].Id;
                dr["PredmetProstorijaVrijeme"] = $"{db.Predmeti.Find(nastava.PredmetId).Naziv} - u {nastava.Dan} @ {nastava.Vrijeme}";
                dr["Student"] = db.Studenti.Find(prisustva[i].StudentId).ToString();

                dt.Rows.Add(dr);
            }

            dgvPrisustva.DataSource = null;
            dgvPrisustva.DataSource = dt;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            var nastava = cmbNastava.SelectedItem as NastavaIB230172;
            var student = cmbStudent.SelectedItem as Student;

            if (db.PrisustvoIB230172.Any(x => x.NastavaId == nastava.Id && x.StudentId == student.Id)) {
                MessageBox.Show("Student je već na toj nastavi!");
                return;
            }
            if (db.PrisustvoIB230172.Include(x => x.Nastava).Where(x => x.Nastava.ProstorijaId == ProstorijaId).ToList().Count >= db.ProstorijeIB230172.Find(ProstorijaId).Kapacitet) {
                MessageBox.Show("Prostorija je popunjena!");
                return;
            }

            var prisustvo = new PrisustvoIB230172 {
                NastavaId = nastava.Id,
                StudentId = student.Id
            };

            db.PrisustvoIB230172.Add(prisustvo);
            db.SaveChanges();

            UcitajPodatke();
        }

        private void cmbNastava_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private async void btnGenerisi_Click(object sender, EventArgs e)
        {
            var brojPonavljanja = int.Parse(txtBrojZapisa.Text);
            var nastava = cmbNastava.SelectedItem as NastavaIB230172;
            var student = cmbStudent.SelectedItem as Student;
            var predmetText = db.Predmeti.Find(nastava.PredmetId).Naziv;

            for(int i = 0; i < brojPonavljanja; i++) {
                var prisustvo = new PrisustvoIB230172 {
                    NastavaId = nastava.Id,
                    StudentId = student.Id
                };

                await Task.Delay(300);
                db.PrisustvoIB230172.Add(prisustvo);

                txtInfo.Text += $"{DateTime.Now.ToString("mm:yy hh:mm:ss")} -> {student.ToString()} za {predmetText} - u {nastava.Dan} @ {nastava.Vrijeme}{Environment.NewLine}";
                txtInfo.SelectionLength = txtInfo.Text.Length;
                txtInfo.ScrollToCaret();
            }
            db.SaveChanges();

            MessageBox.Show("Prisustva uspješno dodana!");
            UcitajPodatke();
        }
    }
}
