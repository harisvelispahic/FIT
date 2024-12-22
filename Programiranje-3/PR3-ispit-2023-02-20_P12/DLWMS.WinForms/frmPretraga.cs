using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DLWMS.Data;
using DLWMS.WinForms.Helpers;
using Microsoft.EntityFrameworkCore;

namespace DLWMS.WinForms
{
    public partial class frmPretraga : Form
    {
        DLWMSDbContext db = new DLWMSDbContext();
        public frmPretraga()
        {
            InitializeComponent();
            dgvStudentiPredmeti.AutoGenerateColumns = false;
        }

        private void cmbOcjenaOd_SelectedIndexChanged(object sender, EventArgs e)
        {
            FiltrirajPodatke();
        }

        private void FiltrirajPodatke()
        {
            if (
            !DLWMS.WinForms.Helpers.Validator.ValidirajKontrolu(cmbOcjenaOd, err, "") ||
            !DLWMS.WinForms.Helpers.Validator.ValidirajKontrolu(cmbOcjenaDo, err, ""))
                return;

            //int ocjenaOd = cmbOcjenaOd.SelectedItem != null ? (int)cmbOcjenaOd.SelectedItem : 6;
            //int ocjenaDo = cmbOcjenaDo.SelectedItem != null ? (int)cmbOcjenaDo.SelectedItem : 10;

            int ocjenaOd = (int)cmbOcjenaOd.SelectedValue;
            int ocjenaDo = (int)cmbOcjenaDo.SelectedValue;

            //DateTime polozenaOd = dtpPolozenaOd.Value;
            DateTime polozenaOd = new DateTime(2000, 1, 1);
            DateTime polozenaDo = dtpPolozenaDo.Value;

            List<StudentiPredmeti> listStudentiPredmeti =
                db.StudentiPredmeti.Where((obj) =>
                //obj.Ocjena >= int.Parse(cmbOcjenaOd.SelectedValue.ToString()) &&
                //obj.Ocjena <= int.Parse(cmbOcjenaDo.SelectedValue.ToString()) &&
                obj.Ocjena >= ocjenaOd &&
                obj.Ocjena <= ocjenaDo &&
                obj.Datum >= polozenaOd &&
                obj.Datum <= polozenaDo)
                .Include(sp => sp.Student).Include(sp => sp.Predmet)
                .ToList();

            //if (listStudentiPredmeti.Count == 0) {
            //    MessageBox.Show($"U periodu od {polozenaOd} - {polozenaDo} godine ne postoje evidentirane ocjene u opsegu od {ocjenaOd} do {ocjenaDo} za bilo kojeg studenta.");
            //}


            //foreach(var item in listStudentiPredmeti) {
            //    var odabraniStudent = db.Studenti.Where(obj => obj.Id == item.StudentId) as Student;
            //    var odabraniPredmet = db.Predmeti.Where(obj => obj.Id == item.PredmetId) as Predmeti;

            //    string brojIndeksa = odabraniStudent.BrojIndeksa;
            //    string imePrezime = odabraniStudent.Ime + " " + odabraniStudent.Prezime;
            //    string predmet = odabraniPredmet.Naziv;



            //}

            dgvStudentiPredmeti.DataSource = null;
            dgvStudentiPredmeti.DataSource = listStudentiPredmeti;
            //dgvStudentiPredmeti.DataSource = db.StudentiPredmeti.ToList();

            //for (int i = 0; i < listStudentiPredmeti.Count(); i++) {
            //    var odabraniStudent = db.Studenti.Where(obj => obj.Id == listStudentiPredmeti[i].StudentId) as Student;
            //    var odabraniPredmet = db.Predmeti.Where(obj => obj.Id == listStudentiPredmeti[i].PredmetId) as Predmeti;

            //    string brojIndeksa = odabraniStudent.BrojIndeksa;
            //    string imePrezime = odabraniStudent.Ime + " " + odabraniStudent.Prezime;
            //    string predmet = odabraniPredmet.Naziv;

            //    dgvStudentiPredmeti.Rows[i].Cells["Indeks"].Value = brojIndeksa;
            //    dgvStudentiPredmeti.Rows[i].Cells["ImeIPrezime"].Value = imePrezime;
            //    dgvStudentiPredmeti.Rows[i].Cells["Predmet"].Value = predmet;

            //}
            
            for (int i = 0; i < listStudentiPredmeti.Count(); i++) {
                var studentiPredmet = listStudentiPredmeti[i];
                
                // Extract details for DataGridView
                string brojIndeksa = studentiPredmet.Student.BrojIndeksa;
                string imePrezime = studentiPredmet.Student.Ime + " " + studentiPredmet.Student.Prezime;
                string predmet = studentiPredmet.Predmet.Naziv;

                dgvStudentiPredmeti.Rows[i].Cells["Indeks"].Value = brojIndeksa;
                dgvStudentiPredmeti.Rows[i].Cells["ImeIPrezime"].Value = imePrezime;
                dgvStudentiPredmeti.Rows[i].Cells["Predmet"].Value = predmet;
                dgvStudentiPredmeti.Rows[i].Cells["DatumPolaganja"].Value = listStudentiPredmeti[i].Datum.ToString();
            }


        }

        private void cmbOcjenaDo_SelectedIndexChanged(object sender, EventArgs e)
        {
            FiltrirajPodatke();
        }

        private void dtpPolozenaOd_ValueChanged(object sender, EventArgs e)
        {
            FiltrirajPodatke();
        }

        private void dtpPolozenaDo_ValueChanged(object sender, EventArgs e)
        {
            FiltrirajPodatke();
        }

        private void frmPretragaBrojIndeksa_Load(object sender, EventArgs e)
        {
            cmbOcjenaOd.DataSource = new List<int>() { 6, 7, 8, 9, 10 };
            cmbOcjenaDo.DataSource = new List<int>() { 6, 7, 8, 9, 10 };
        }

        private void dgvStudentiPredmeti_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            // Check if the clicked cell is in the button column
            if (e.RowIndex >= 0 && dgvStudentiPredmeti.Columns[e.ColumnIndex] is DataGridViewButtonColumn) {
                // Get the clicked row
                var selectedRow = dgvStudentiPredmeti.Rows[e.RowIndex];

                // Example: Retrieve data from the selected row
                string studentIndex = selectedRow.Cells["Indeks"].Value?.ToString();
                string studentName = selectedRow.Cells["ImeIPrezime"].Value?.ToString();

                // Perform your desired action
                //MessageBox.Show($"Button clicked in row {e.RowIndex}!\nStudent Index: {studentIndex}\nStudent Name: {studentName}");

                // Example: Execute specific logic
                // You can call a method or perform database operations here.
                int StudentId = (db.Studenti.FirstOrDefault(obj => obj.BrojIndeksa == studentIndex) as Student).Id;
                var frmPoruke = new frmPoruke(StudentId);
                frmPoruke.ShowDialog();
            }
        }

        
    }
}
