using FIT.Data;
using FIT.WinForms.Izvjestaji;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Sqlite.Migrations.Internal;
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
    public partial class frmUvjerenjaIB230172 : Form
    {
        public int StudentId { get; set; }
        public frmUvjerenjaIB230172(int studentId)
        {
            InitializeComponent();
            dataGridView1.AutoGenerateColumns = false;
            StudentId = studentId;
        }

        private void frmUvjerenjaIB230172_Load(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            dataGridView1.DataSource = null;
            var listaUvjerenja = SharedContext.db.StudentiUvjerenjaIB230172.Where(x => x.StudentId == StudentId).ToList();
            dataGridView1.DataSource = listaUvjerenja;

            this.Text = $"Broj uvjerenja -> {listaUvjerenja.Count.ToString()}";

            if (listaUvjerenja.Count > 0) {
                button1.Enabled = true;
            }
            else {
                button1.Enabled = false;
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            var uvjerenje = dataGridView1.SelectedRows[0].DataBoundItem as StudentiUvjerenjaIB230172;
            
            if (e.ColumnIndex == 5) {
                if (MessageBox.Show(
                    "Da li  ste sigurni da želite obrisati ovo uvjerenje?",
                    "Potvrdite brisanje!",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning
                    ) == DialogResult.Yes) {
                    SharedContext.db.StudentiUvjerenjaIB230172.Remove(uvjerenje);
                    SharedContext.db.SaveChanges();

                    UcitajPodatke();
                }
            }
            else if (e.ColumnIndex == 6) {
                new frmIzvjestaji(uvjerenje.Id).ShowDialog();
                uvjerenje.Printano = true;

                SharedContext.db.StudentiUvjerenjaIB230172.Update(uvjerenje);
                SharedContext.db.SaveChanges();

                UcitajPodatke();
            }
        }

        private void btnNOviZahtjev_Click(object sender, EventArgs e)
        {
            if (new frmNovoUvjerenjeIB230172(StudentId).ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
            }
        }

        private async void button1_Click(object sender, EventArgs e)
        {
            try {

                var vrsta = comboBox1.Text;
                var svrha = textBox1.Text;
                var brojZahtjeva = int.Parse(textBox2.Text);

                var student = SharedContext.db.Studenti.Find(StudentId);

                for (int i = 0; i < brojZahtjeva; i++) {

                    var uvjerenje = new StudentiUvjerenjaIB230172 {
                        StudentId = student.Id,
                        Vrsta = vrsta,
                        Svrha = svrha,
                        Uplatnica = SharedContext.db.StudentiUvjerenjaIB230172.FirstOrDefault(x => x.StudentId == student.Id).Uplatnica,
                        Printano = false,
                        VrijemeKreiranja = DateTime.Now
                    };
                    textBox3.Text += $"{DateTime.Now.ToString("hh:mm:ss")} -> {vrsta} ({student.Indeks}) - {student.ImePrezime} u svrhu {svrha}{Environment.NewLine}";
                    textBox3.SelectionStart = textBox3.Text.Length;
                    textBox3.ScrollToCaret();

                    SharedContext.db.StudentiUvjerenjaIB230172.Add(uvjerenje);

                    await Task.Delay(300);
                }
                SharedContext.db.SaveChanges();
                UcitajPodatke();

                MessageBox.Show("Uvjerenja uspješno dodata!");
            }
            catch(Exception ex) {
                MessageBox.Show("Došlo je do greške -> " + ex.Message);
            }
        }
    }
}
