using FIT.Data;
using FIT.WinForms.Helpers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms
{
    public partial class frmPorukeBrojIndeksa : Form
    {
        public int StudentId { get; set; }
        public frmPorukeBrojIndeksa(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmPorukeBrojIndeksa_Load(object sender, EventArgs e)
        {
            var student = SharedContext.db.Studenti.Find(StudentId);
            label1.Text = "Poruke studenta " + student.ImePrezime + ":";
            UcitajPodatke();
            cmbPredmet.UcitajPodatke(SharedContext.db.Predmeti.ToList());
        }

        private void btnNovaPoruka_Click(object sender, EventArgs e)
        {
            if (new frmNovaPoruka(StudentId).ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
            }
        }

        private void UcitajPodatke()
        {
            dataGridView1.DataSource = null;
            var listaPoruka = SharedContext.db.StudentiPorukeIB230172
                .Where(x => x.StudentId == StudentId && x.Validnost > DateTime.Now)
                .ToList();
            dataGridView1.DataSource = listaPoruka;

            if (listaPoruka.Count > 0) {
                btnDodaj.Enabled = true;
            }
            else {
                btnDodaj.Enabled = false;
            }


        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 5) {
                if (MessageBox.Show(
                    "Da li ste sigurni da želite obrisati ovu poruku?",
                    "Potvrdite brisanje poruke!",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning)
                    == DialogResult.Yes
                    ) {
                    var porukaZaBrisati = dataGridView1.SelectedRows[0].DataBoundItem as StudentiPorukeIB230172;
                    SharedContext.db.StudentiPorukeIB230172.Remove(porukaZaBrisati);
                    SharedContext.db.SaveChanges();

                    UcitajPodatke();
                }
            }
        }

        private async void btnDodaj_Click(object sender, EventArgs e)
        {
            var brojPoruka = int.Parse(txtBrojPoruka.Text);
            var validnost = dateTimePicker1.Value;
            var predmet = cmbPredmet.SelectedItem as Predmeti;
            var student = SharedContext.db.Studenti.Find(StudentId);

            for (int i = 0; i < brojPoruka; i++) {

                var poruka = new StudentiPorukeIB230172 {
                    PredmetId = predmet.Id,
                    StudentId = this.StudentId,
                    Hitnost = "Srednja",
                    Sadrzaj = "...",
                    Slika = SharedContext.db.StudentiPorukeIB230172.FirstOrDefault(x => x.StudentId == this.StudentId).Slika,
                    Validnost = dateTimePicker1.Value,
                };

                SharedContext.db.StudentiPorukeIB230172.Add(poruka);
                textBox2.Text +=
                    $"{validnost} -> generisana poruka za {student.Ime} {student.Prezime} na predmetu {predmet.Naziv}{Environment.NewLine}";
                textBox2.SelectionLength = textBox2.Text.Length;
                textBox2.ScrollToCaret();
                await Task.Delay(300);
            }
            SharedContext.db.SaveChanges();
            UcitajPodatke();
            MessageBox.Show("Poruke uspješno dodane!");
        }

        
    }
}
