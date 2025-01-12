using FIT.Data;
using FIT.Infrastructure;
using FIT.WinForms.Izvjestaji;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace FIT.WinForms
{
    public partial class frmUvjerenja : Form
    {
        DLWMSDbContext db;
        public int StudentID { get; set; }
        public frmUvjerenja(int studentID)
        {
            InitializeComponent();
            db = new DLWMSDbContext();
            StudentID = studentID;
            dgvUvjerenja.AutoGenerateColumns = false;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 5) {
                var pitanje = MessageBox.Show(
                    "Da li ste sigurni da želite obrisati ovo uvjerenje?",
                    "Potvrdite brisanje",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning);

                if (pitanje == DialogResult.Yes) {
                    var indexUvjerenja = dgvUvjerenja.Rows[e.RowIndex].Cells["Id"].Value;
                    var deleteUvjerenje = db.StudentiUvjerenja.Find(Convert.ToInt32(indexUvjerenja));
                    db.StudentiUvjerenja.Remove(deleteUvjerenje);
                    db.SaveChanges();

                    UcitajPodatke();

                    if (dgvUvjerenja.Rows.Count == 0) {
                        btnDodaj.Enabled = false;
                    }
                    else {
                        btnDodaj.Enabled = true;
                    }
                }
            }
            else if (e.ColumnIndex == 6) {
                var indexUvjerenja = dgvUvjerenja.Rows[e.RowIndex].Cells["Id"].Value;
                var uvjerenje = db.StudentiUvjerenja.Find(Convert.ToInt32(indexUvjerenja));
                uvjerenje.Printano = true;
                db.StudentiUvjerenja.Update(uvjerenje);
                db.SaveChanges();

                new frmIzvjestaji(uvjerenje.Id).ShowDialog();

                UcitajPodatke();
            }
        }

        private void frmUvjerenja_Load(object sender, EventArgs e)
        {
            UcitajPodatke();
            if (dgvUvjerenja.Rows.Count == 0) {
                btnDodaj.Enabled = false;
            }
            else {
                btnDodaj.Enabled = true;
            }
        }

        private void UcitajPodatke()
        {
            var uvjerenja = db.StudentiUvjerenja.Where(st => st.StudentId == StudentID).ToList();

            dgvUvjerenja.DataSource = null;
            dgvUvjerenja.DataSource = uvjerenja;

            this.Text = $"Broj uvjerenja -> {uvjerenja.Count}";
        }

        private void btnNoviZahtjev_Click(object sender, EventArgs e)
        {
            if (new frmNovoUvjerenje(StudentID).ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
                if (dgvUvjerenja.Rows.Count == 0) {
                    btnDodaj.Enabled = false;
                }
                else {
                    btnDodaj.Enabled = true;
                }
            }
        }

        private async void btnDodaj_Click(object sender, EventArgs e)
        {
            string vrstaUvjerenja = cmbVrstaUvjerenja.Text;
            string svrhaIzdavanja = txtSvrhaUvjerenja.Text;
            int brojZahtjeva = int.Parse(txtBrojZahtjeva.Text);

            

            var student = db.Studenti.Find(StudentID);
            
            for (int i = 0; i < brojZahtjeva; i++) {

                var uvjerenje = new StudentiUvjerenja() {
                    StudentId = this.StudentID,
                    VrijemeKreiranja = DateTime.Now,
                    Vrsta = vrstaUvjerenja,
                    Svrha = svrhaIzdavanja,
                    Uplatnica = db.StudentiUvjerenja.
                FirstOrDefault(su => su.StudentId == this.StudentID).Uplatnica,
                    Printano = false
                };


                await Task.Delay(300);
                string line = $"{DateTime.Now.Hour}:{DateTime.Now.Minute}:{DateTime.Now.Second} -> {vrstaUvjerenja} ({student.Indeks}) - {student.Ime} {student.Prezime} u svrhu {svrhaIzdavanja}{Environment.NewLine}";
                txtInfo.AppendText(line);
                PomjeriKursor();

                db.StudentiUvjerenja.Add(uvjerenje);
                db.SaveChanges();
            }

            MessageBox.Show("Uvjerenja uspješno dodana!");
            UcitajPodatke();

            this.Text = $"Broj uvjerenja -> {db.StudentiUvjerenja.Where(su => su.StudentId == StudentID).Count().ToString()}";
        }

        private void PomjeriKursor()
        {
            txtInfo.Focus();
            txtInfo.SelectionStart = txtInfo.Text.Length;
            txtInfo.SelectionLength = 0;
        }
    }
}
