using FIT.Data;
using FIT.WinForms.Izvjestaji;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms
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
            dataGridView1.DataSource = null;
            dataGridView1.DataSource = SharedContext.db.DrzaveIB230172.ToList();

            var gradovi = SharedContext.db.GradoviIB230172.ToList();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label1.Text = DateTime.Now.ToString("hh:mm:ss");
        }

        private void btnNova_Click(object sender, EventArgs e)
        {
            if (new frmNovaDrzavaIB230172().ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex != 4) {
                if (new frmNovaDrzavaIB230172((dataGridView1.SelectedRows[0].DataBoundItem as DrzaveIB230172).Id, true)
                    .ShowDialog() == DialogResult.OK) {
                    UcitajPodatke();
                }
            }
            else {
                new frnGradoviIB230172((dataGridView1.SelectedRows[0].DataBoundItem as DrzaveIB230172).Id).ShowDialog();
            }
        }

        private void btnPrintaj_Click(object sender, EventArgs e)
        {
            new frmIzvjestaji((dataGridView1.SelectedRows[0].DataBoundItem as DrzaveIB230172).Id).ShowDialog();
        }
    }
}
