using FIT.Data;
using FIT.Infrastructure;
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
    public partial class frmGradoviIB230172 : Form
    {
        public int DrzavaId { get; set; }
        DLWMSDbContext db = new();
        public frmGradoviIB230172(int drzavaId)
        {
            InitializeComponent();
            dgvGradovi.AutoGenerateColumns = false;
            DrzavaId = drzavaId;
        }

        private void frmGradoviIB230172_Load(object sender, EventArgs e)
        {
            var drzava = db.DrzaveIB230172.Find(DrzavaId);

            pbZastava.Image = drzava.Zastava.ToImage();
            lblNazivDrzave.Text = drzava.Naziv;
            UcitajDGV();
        }

        private void UcitajDGV()
        {
            dgvGradovi.DataSource = null;
            dgvGradovi.DataSource = db.GradoviIB230172.Where(x => x.DrzavaId == DrzavaId).ToList();
        }

        private void dgvGradovi_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 2) {
                int idGrada = Convert.ToInt32(dgvGradovi.SelectedRows[0].Cells["Id"].Value);
                var grad = db.GradoviIB230172.Find(idGrada);

                grad.Status = !grad.Status;

                db.GradoviIB230172.Update(grad);
                UcitajDGV();
            }
        }

        private void btnDodaj_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                var grad = new GradoviIB230172 {
                    Naziv = txtNazivGrada.Text,
                    Status = true,
                    DrzavaId = this.DrzavaId
                };

                db.GradoviIB230172.Add(grad);
                db.SaveChanges();

                UcitajDGV();
            }
            else {
                MessageBox.Show("Podaci nisu validni/Grad već postoji");
            }
        }

        private bool Validiraj()
        {
            return Validator.ProvjeriUnos(txtNazivGrada, err, Kljucevi.ReqiredValue)
                && !db.GradoviIB230172.Any(x => x.Naziv == txtNazivGrada.Text);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private async void btnGenerisi_Click(object sender, EventArgs e)
        {
            var drzava = db.DrzaveIB230172.Find(DrzavaId).Naziv;
            var brojGradova = int.Parse(txtBrojGradova.Text);
            var aktivni = cbAktivni.Checked;

            for(int i = 0; i < brojGradova; i++) {
                var grad = new GradoviIB230172 {
                    Naziv = $"Grad {i + 1}.",
                    Status = aktivni,
                    DrzavaId = this.DrzavaId
                };
                await Task.Delay(300);
                db.GradoviIB230172.Add(grad);
                txtInfo.Text += $"{DateTime.Now.ToString()} -> dodat grad {grad.Naziv} za državu {drzava}{Environment.NewLine}";
                txtInfo.SelectionStart = txtInfo.Text.Length;
                txtInfo.ScrollToCaret();
            }
            db.SaveChanges();
            UcitajDGV();
        }
    }
}
