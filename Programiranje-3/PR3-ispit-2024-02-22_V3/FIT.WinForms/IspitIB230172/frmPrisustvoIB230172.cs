using FIT.Data;
using FIT.WinForms.Helpers;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms.IspitIB230172
{
    public partial class frmPrisustvoIB230172 : Form
    {
        public int ProstorijaId { get; set; }
        public frmPrisustvoIB230172(int prostorijaId)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmPrisustvoIB230172_Load(object sender, EventArgs e)
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);
            lblProstorija.Text = prostorija.Naziv;

            cmbNastava.UcitajPodatke(SharedContext.db.NastavaIB230172
                .Include(x => x.Prostorija)
                .Where(x => x.ProstorijaId == ProstorijaId)
                .ToList(), "Oznaka");
            cmbStudent.UcitajPodatke(SharedContext.db.Studenti.ToList(), "IndeksStudent");

            UcitajPodatke();

        }

        private void UcitajPodatke()
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);
            var nastava = cmbNastava.SelectedItem as NastavaIB230172;

            if (nastava == null) {
            lblKapacitet.Text = "-/-";
                return;
            }

            var listaPrisustava = SharedContext.db.PrisustvoIB230172
                .Include(x => x.Student)
                .Include(x => x.Nastava)
                .ThenInclude(y => y.Predmet)
                .Where(x => x.NastavaId == nastava.Id)
                .ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = listaPrisustava;

            lblKapacitet.Text = $"{listaPrisustava.Count}/{prostorija.Kapacitet}";
        }

        private void btnDodaj_Click(object sender, EventArgs e)
        {
            var nastava = cmbNastava.SelectedItem as NastavaIB230172;
            var student = cmbStudent.SelectedItem as Student;
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);


            var listaPrisustava = SharedContext.db.PrisustvoIB230172
                .Include(x => x.Student)
                .Include(x => x.Nastava)
                .ThenInclude(y => y.Predmet)
                .Where(x => x.NastavaId == nastava.Id)
                .ToList();

            if (listaPrisustava.Count >= prostorija.Kapacitet) {
                MessageBox.Show("Nastava popunjena!");
                return;
            }


            if (SharedContext.db.PrisustvoIB230172
                .Any(x => x.NastavaId == nastava.Id && x.StudentId == student.Id)) {
                MessageBox.Show("Zauzeto !!!!!!!!!!!!!!!!!");
                return;
            }

            var novoPrisustvo = new PrisustvoIB230172 {
                NastavaId = nastava.Id,
                StudentId = student.Id
            };

            SharedContext.db.PrisustvoIB230172.Add(novoPrisustvo);
            SharedContext.db.SaveChanges();

            UcitajPodatke();
        }

        private void cmbNastava_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void cmbStudent_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private async void btngenerisi_Click(object sender, EventArgs e)
        {
            var prisustvo = dataGridView1.SelectedRows[0].DataBoundItem as PrisustvoIB230172;

            int brojZapisa = int.Parse(textBox1.Text);
            var nastava = prisustvo.Nastava;
            var student = prisustvo.Student;

            for (int i = 0; i < brojZapisa; i++) {
                var novoPrisustvo = new PrisustvoIB230172 {
                    NastavaId = nastava.Id,
                    StudentId = student.Id
                };

                txtInfo.Text += $"{DateTime.Now} -> {student.ToString()} za {prisustvo.PredmetProstorijaVrijeme}{Environment.NewLine}";
                txtInfo.SelectionLength = txtInfo.Text.Length;
                txtInfo.ScrollToCaret();

                SharedContext.db.PrisustvoIB230172.Add(novoPrisustvo);
                await Task.Delay(300);

            }

            SharedContext.db.SaveChanges();
            UcitajPodatke();

            MessageBox.Show("Prisustva uspjesno dodana!");
        }
    }
}
