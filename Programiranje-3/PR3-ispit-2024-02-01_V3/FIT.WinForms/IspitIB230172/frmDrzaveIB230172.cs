using FIT.Data;
using FIT.WinForms.Izvjestaji;
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
    public partial class frmDrzaveIB230172 : Form
    {
        public frmDrzaveIB230172()
        {
            InitializeComponent();
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmDrzaveIB230172_Load(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            var listaDrzava = SharedContext.db.DrzaveIB230172
                .ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = listaDrzava;

            for (int i = 0; i < listaDrzava.Count; i++) {
                var listaGradova = SharedContext.db.GradoviIB230172
                    .Where(x => x.DrzavaId == listaDrzava[i].Id)
                    .Select(x => x.Id)
                    .Distinct()
                    .ToList();
                dataGridView1.Rows[i].Cells["BrojGradova"].Value = listaGradova.Count;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label1.Text = $"Trenutno vrijeme {DateTime.Now}";
        }

        private void btnNovaDrzava_Click(object sender, EventArgs e)
        {
            if (new frmNovaDrzava().ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex != 4) {
                if (new frmNovaDrzava((dataGridView1.SelectedRows[0].DataBoundItem as DrzaveIB230172).Id, true).ShowDialog() == DialogResult.OK) {
                    UcitajPodatke();
                }
            }
            else {
                new frmGradoviIB230172((dataGridView1.SelectedRows[0].DataBoundItem as DrzaveIB230172).Id)
                    .ShowDialog();
            }
        }

        private void btnPrintaj_Click(object sender, EventArgs e)
        {
            new frmIzvjestaji((dataGridView1.SelectedRows[0].DataBoundItem as DrzaveIB230172).Id)
                    .ShowDialog();
        }
    }
}
