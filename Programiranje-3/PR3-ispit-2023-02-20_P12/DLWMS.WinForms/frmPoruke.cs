using DLWMS.Data;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DLWMS.WinForms
{
    public partial class frmPoruke : Form
    {
        public int StudentId { get; set; }
        DLWMSDbContext db = new DLWMSDbContext();
        Student odabraniStudent = new Student();
        public frmPoruke(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
            dgvPoruke.AutoGenerateColumns = false;
            odabraniStudent = db.Studenti.FirstOrDefault(obj => obj.Id == StudentId) as Student;
            lblNaslov.Text += (odabraniStudent.Ime + " " + odabraniStudent.Prezime + ":");
        }

        private void frmPoruke_Load(object sender, EventArgs e)
        {
            // SAKRIVENA KOLONA ID
            var column = new DataGridViewTextBoxColumn {
                Name = "Id",
                DataPropertyName = "Id",
                Visible = false
            };
            dgvPoruke.Columns.Add(column);

            var listStudentiPoruke = db.StudentiPoruke.Where(obj => obj.StudentId == odabraniStudent.Id).ToList();
            UcitajPoruke(listStudentiPoruke);

        }

        private void UcitajPoruke(List<StudentiPoruke> listStudentiPoruke)
        {
            dgvPoruke.DataSource = null;
            dgvPoruke.DataSource = listStudentiPoruke;
            // poslije odkomentarisati propertye u StudentiPoruke

            for (int i = 0; i < listStudentiPoruke.Count; i++) {
                var predmet = db.Predmeti.FirstOrDefault(obj => obj.Id == listStudentiPoruke[i].PredmetId);
                dgvPoruke.Rows[i].Cells["Predmet"].Value = predmet.Naziv;
                dgvPoruke.Rows[i].Cells["Sadrzaj"].Value = listStudentiPoruke[i].Sadrzaj;
                dgvPoruke.Rows[i].Cells["Validnost"].Value = listStudentiPoruke[i].Validnost;
                //dgvPoruke.Rows[i].Cells["Id"].Value = listStudentiPoruke[i].Id;
            }
        }

        private void dgvPoruke_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            // Check if the clicked cell is in the button column
            if (e.RowIndex >= 0 && dgvPoruke.Columns[e.ColumnIndex] is DataGridViewButtonColumn) {

                var result = MessageBox.Show(
                    "Da li ste sigurni da želite izbrisati ovu poruku?",
                    "Potvrdite brisanje",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning);


                if (result == DialogResult.Yes) {

                    // Get the clicked row
                    var selectedRow = dgvPoruke.Rows[e.RowIndex];

                    //var obrisanaPoruka = new StudentiPoruke() {
                    //    Id = Convert.ToInt32(selectedRow.Cells["Id"].Value)+11,
                    //    StudentId = odabraniStudent.Id,
                    //    PredmetId = (db.Predmeti.FirstOrDefault(obj => obj.Naziv == selectedRow.Cells["Predmet"].Value) as Predmeti).Id,
                    //    Validnost = Convert.ToDateTime(selectedRow.Cells["Validnost"].Value),
                    //    Sadrzaj="poruka iz aplikacije"
                    //};
                    int id = Convert.ToInt32(selectedRow.Cells["Id"].Value);

                    // Retrieve the record directly from the database
                    var obrisanaPoruka = db.StudentiPoruke.FirstOrDefault(p => p.Id == id);

                    ////db.StudentiPoruke.Attach(obrisanaPoruka);
                    //db.StudentiPoruke.Remove(obrisanaPoruka);
                    ////db.StudentiPoruke.Add(obrisanaPoruka);
                    //db.SaveChanges();
                    //var entry = db.Entry(obrisanaPoruka);
                    //MessageBox.Show(entry.State.ToString()); // Should be 'Deleted' after Remove()

                    var entry = db.Entry(obrisanaPoruka);

                    // If the entity is detached, attach it to the context first
                    if (entry.State == EntityState.Detached) {
                        db.StudentiPoruke.Attach(obrisanaPoruka);
                    }

                    db.StudentiPoruke.Remove(obrisanaPoruka);
                    db.SaveChanges();

                    var listStudentiPoruke = db.StudentiPoruke.Where(obj => obj.StudentId == odabraniStudent.Id).ToList();
                    UcitajPoruke(listStudentiPoruke);
                }
            }
        }

        private void btnNovaPoruka_Click(object sender, EventArgs e)
        {
            var frmNovaPoruka = new frmNovaPoruka(StudentId);
            frmNovaPoruka.ShowDialog();

            if (frmNovaPoruka.DialogResult == DialogResult.OK) {
                var listStudentiPoruke = db.StudentiPoruke.Where(obj => obj.StudentId == odabraniStudent.Id).ToList();
                UcitajPoruke(listStudentiPoruke);
            }
        }

        // CHAT GPT
        //private void dgvPoruke_CellContentClick(object sender, DataGridViewCellEventArgs e)
        //{
        //    // Check if the clicked cell is in the button column
        //    if (e.RowIndex >= 0 && dgvPoruke.Columns[e.ColumnIndex] is DataGridViewButtonColumn) {
        //        var result = MessageBox.Show(
        //            "Da li ste sigurni da želite izbrisati ovu poruku?",
        //            "Potvrdite brisanje",
        //            MessageBoxButtons.YesNo,
        //            MessageBoxIcon.Warning
        //        );

        //        if (result == DialogResult.Yes) {
        //            // Get the clicked row
        //            var selectedRow = dgvPoruke.Rows[e.RowIndex];
        //            int id = Convert.ToInt32(selectedRow.Cells["Id"].Value);

        //            // Retrieve the record directly from the database
        //            var obrisanaPoruka = db.StudentiPoruke.FirstOrDefault(p => p.Id == id);

        //            if (obrisanaPoruka != null) {
        //                try {
        //                    // Start a new transaction to ensure changes are committed properly
        //                    using (var transaction = db.Database.BeginTransaction()) {
        //                        // Remove the record from the DbSet
        //                        db.StudentiPoruke.Remove(obrisanaPoruka);

        //                        // Save the changes to the database
        //                        db.SaveChanges();

        //                        // Commit the transaction to ensure the changes are persisted
        //                        transaction.Commit();
        //                    }

        //                    // Optionally, reload the DataGridView after the change
        //                    var listStudentiPoruke = db.StudentiPoruke.Where(obj => obj.StudentId == odabraniStudent.Id).ToList();
        //                    UcitajPoruke(listStudentiPoruke);

        //                    MessageBox.Show("Poruka je uspješno obrisana.");
        //                }
        //                catch (Exception ex) {
        //                    MessageBox.Show("Došlo je do greške prilikom brisanja: " + ex.Message);
        //                    // In case of an error, rollback the transaction
        //                    db.Database.CurrentTransaction?.Rollback();
        //                }
        //            }
        //            else {
        //                MessageBox.Show("Poruka nije pronađena.");
        //            }
        //        }
        //    }
        //}



    }
}
