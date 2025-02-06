using FIT.Data;
using FIT.WinForms.Helpers;
using Microsoft.Extensions.Options;
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
    public partial class frnGradoviIB230172 : Form
    {
        public int DrzavaId { get; set; }
        public frnGradoviIB230172(int drzavaId)
        {
            InitializeComponent();
            DrzavaId = drzavaId;
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frnGradoviIB230172_Load(object sender, EventArgs e)
        {
            UcitajPodatke();

            var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);

            pictureBox1.Image = drzava.Zastava.ToImage();
            lblZemlja.Text = drzava.Naziv;

        }

        private void UcitajPodatke()
        {
            dataGridView1.DataSource = null;
            dataGridView1.DataSource = SharedContext.db.GradoviIB230172.Where(x => x.DrzavaId == DrzavaId).ToList();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 2) {
                var grad = SharedContext.db.GradoviIB230172
                    .Find((dataGridView1.SelectedRows[0].DataBoundItem as GradoviIB230172).Id);

                grad.Status = !grad.Status;

                SharedContext.db.GradoviIB230172.Update(grad);
                SharedContext.db.SaveChanges();

                UcitajPodatke();
            }
        }

        private void btnDodaj_Click(object sender, EventArgs e)
        {
            if (Validator.ProvjeriUnos(txtNazivGrada, err, Kljucevi.ReqiredValue)) {
                var grad = txtNazivGrada.Text;
                if (SharedContext.db.GradoviIB230172.Any(x => x.Naziv.ToLower() == grad.ToLower())) {
                    MessageBox.Show("Grad vec postoji");
                }

                var noviGrad = new GradoviIB230172 {
                    Naziv = grad,
                    DrzavaId = DrzavaId,
                    Status = true
                };

                SharedContext.db.GradoviIB230172.Add(noviGrad);
                SharedContext.db.SaveChanges();

                UcitajPodatke();
            }
        }

        private async void btnGenerisi_Click(object sender, EventArgs e)
        {
            var brojGradova = int.Parse(txtBrojGradova.Text);
            var status = checkBox1.Checked;

            for(int i = 0; i < brojGradova; i++) {
                var grad = new GradoviIB230172 {
                    DrzavaId = DrzavaId,
                    Naziv = $"Grad {i + 1}",
                    Status = status
                };

                SharedContext.db.GradoviIB230172.Add(grad);
                txtInfo.Text += $"{DateTime.Now.ToString()} -> dodat grad {grad.Naziv} za državu {grad.Drzava.Naziv}{Environment.NewLine}";
                txtInfo.SelectionLength = txtInfo.Text.Length;
                txtInfo.ScrollToCaret();
                await Task.Delay(300);

            }
            SharedContext.db.SaveChanges();

            UcitajPodatke();

            MessageBox.Show("Gradovi uspjesno dodani!");
        }
    }
}
