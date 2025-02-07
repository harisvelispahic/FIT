using FIT.Data;
using FIT.WinForms.Helpers;
using FIT.WinForms.Izvjestaji;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
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
    public partial class frmPorukeIB230172 : Form
    {
        public int StudentId { get; set; }
        public frmPorukeIB230172(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmPorukeIB230172_Load(object sender, EventArgs e)
        {
            var student = SharedContext.db.Studenti.Find(StudentId);
            lblStudent.Text = $"Poruke studenta {student.ImePrezime}:";

            UcitajPredmete();
            UcitajPodatke();

        }

        private void UcitajPredmete()
        {
            cmbPredmet.UcitajPodatke(SharedContext.db.Predmeti.ToList());
        }

        private void UcitajPodatke()
        {
            var student = SharedContext.db.Studenti.Find(StudentId);

            var listaPoruka = SharedContext.db.StudentiPorukeIB230172
                .Include(x => x.Student)
                .Include(x => x.Predmet)
                .Where(x => x.StudentId == StudentId && x.Validnost > DateTime.Now)
                .ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = listaPoruka;

            if (listaPoruka.Count > 0) {
                btnDodaj.Enabled = true;
            }
            else {
                btnDodaj.Enabled = false;
            }

            this.Text = $"Broj poruka -> {listaPoruka.Count}";

        }

        private void btnNova_Click(object sender, EventArgs e)
        {
            if (new frmNovaPorukaIB230172(StudentId).ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 5) {
                var porukaId = (dataGridView1.SelectedRows[0].DataBoundItem as StudentiPorukeIB230172).Id;
                var poruka = SharedContext.db.StudentiPorukeIB230172.Find(porukaId);

                SharedContext.db.StudentiPorukeIB230172.Remove(poruka);
                SharedContext.db.SaveChanges();

                UcitajPodatke();
            }
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private async void btnDodaj_Click(object sender, EventArgs e)
        {
            var brojPoruka = int.Parse(txtBrojPoruka.Text);
            var predmet = cmbPredmet.SelectedItem as Predmeti;
            var validnost = dateTimePicker1.Value;
            var student = SharedContext.db.Studenti.Find(StudentId);

            for (int i = 0; i < brojPoruka; i++) {
                var novaPoruka = new StudentiPorukeIB230172 {
                    StudentId = this.StudentId,
                    PredmetId = predmet.Id,
                    Hitnost = "Srednja",
                    Validnost = validnost,
                    Sadrzaj = "...",
                    Slika = SharedContext.db.StudentiPorukeIB230172.FirstOrDefault(x => x.StudentId == this.StudentId).Slika
                };

                txtInfo.Text += $"{DateTime.Now} -> generisana poruka za {student.ImePrezime} na predmetu {predmet.Naziv}{Environment.NewLine}";
                txtInfo.SelectionLength = txtInfo.Text.Length;
                txtInfo.ScrollToCaret();

                await Task.Delay(300);

                SharedContext.db.StudentiPorukeIB230172.Add(novaPoruka);
            }

            SharedContext.db.SaveChanges();
            UcitajPodatke();

            MessageBox.Show("Poruke uspjesno dodate!");

        }

        private void btnPrintaj_Click(object sender, EventArgs e)
        {
            new frmIzvjestaji(StudentId).ShowDialog();
        }
    }
}
