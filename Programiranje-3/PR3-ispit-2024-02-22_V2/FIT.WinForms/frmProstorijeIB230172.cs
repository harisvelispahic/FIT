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

namespace FIT.WinForms
{
    public partial class frmProstorijeIB230172 : Form
    {
        public frmProstorijeIB230172()
        {
            InitializeComponent();
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmProstorijeIB230172_Load(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            dataGridView1.DataSource = null;
            dataGridView1.DataSource = SharedContext.db.ProstorijeIB230172.Include(x => x.NastavaIB230172).ToList();
        }

        private void btnNova_Click(object sender, EventArgs e)
        {
            if (new frmNovaProstorijaIB230172().ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 5) {
                new frmNastavaIB230172((dataGridView1.SelectedRows[0].DataBoundItem as ProstorijeIB230172).Id)
                    .ShowDialog();
            }
            else if (e.ColumnIndex == 6) {
                new frmPrisustvoIB230172((dataGridView1.SelectedRows[0].DataBoundItem as ProstorijeIB230172).Id)
                    .ShowDialog();
            }
        }

        private void btnPrintaj_Click(object sender, EventArgs e)
        {
            new frmIzvjestaji((dataGridView1.SelectedRows[0].DataBoundItem as ProstorijeIB230172).Id)
                .ShowDialog();
        }
    }
}
