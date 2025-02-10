using FIT.Data;
using FIT.WinForms.Helpers;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design.Internal;
using System;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms.IspitIB230172
{
    public partial class frmGradoviIB230172 : Form
    {
        public int DrzavaId { get; set; }
        public frmGradoviIB230172(int drzavaId)
        {
            InitializeComponent();
            DrzavaId = drzavaId;
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmGradoviIB230172_Load(object sender, EventArgs e)
        {
            var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);

            pictureBox1.Image = drzava.Zastava.ToImage();
            lblDrzava.Text = drzava.Naziv;

            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            var listaGradova = SharedContext.db.GradoviIB230172
                .Include(x => x.Drzava)
                .Where(x => x.DrzavaId == DrzavaId)
                .ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = listaGradova;
        }

        private void btndodaj_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                var noviGrad = new GradoviIB230172 {
                    DrzavaId = DrzavaId,
                    Naziv = textBox1.Text,
                    Status = true
                };

                SharedContext.db.GradoviIB230172.Add(noviGrad);
                SharedContext.db.SaveChanges();
                UcitajPodatke();
            }
        }

        private bool Validiraj()
        {
            if (FIT.WinForms.Helpers.Validiraj.ProvjeriUnos(textBox1, err, Kljucevi.ReqiredValue) == false) {
                return false;
            }

            if (SharedContext.db.GradoviIB230172.Any(x => x.Naziv.ToLower() == textBox1.Text.ToLower())) {
                MessageBox.Show("Grad vec registrovan!");
                return false;
            }

            return true;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 2) {
                var grad = dataGridView1.SelectedRows[0].DataBoundItem as GradoviIB230172;
                grad.Status = !grad.Status;
                SharedContext.db.GradoviIB230172.Update(grad);
                SharedContext.db.SaveChanges();

                UcitajPodatke();
            }
        }

        private async void btnGenerisi_Click(object sender, EventArgs e)
        {
            var brojGradova = int.Parse(txtBroj.Text);
            var aktivni = cbAktivni.Checked;
            var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);

            for (int i = 0; i < brojGradova; i++) {
                var noviGrad = new GradoviIB230172 {
                    DrzavaId = this.DrzavaId,
                    Naziv = $"Grad {i + 1}.",
                    Status = aktivni
                };

                SharedContext.db.GradoviIB230172.Add(noviGrad);
                txtInfo.Text += $"{DateTime.Now} -> dodat grad {noviGrad.Naziv} za drzavu {drzava.Naziv}{Environment.NewLine}";
                txtInfo.SelectionLength= txtInfo.Text.Length;
                txtInfo.ScrollToCaret();

                await Task.Delay(300);
            }
            SharedContext.db.SaveChanges();
            UcitajPodatke();

            MessageBox.Show("Gradovi uspjesno dodati!");
        }
    }
}
