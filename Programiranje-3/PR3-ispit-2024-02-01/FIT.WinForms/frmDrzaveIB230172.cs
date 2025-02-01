using FIT.Infrastructure;
using FIT.WinForms.Helpers;
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
using FIT.WinForms.Helpers;
using FIT.WinForms.Izvjestaji;

namespace FIT.WinForms
{
    public partial class frmDrzaveIB230172 : Form
    {
        DLWMSDbContext db = new DLWMSDbContext();
        public frmDrzaveIB230172()
        {
            InitializeComponent();
            dgvDrzave.AutoGenerateColumns = false;
        }

        private void frmDrzaveIB230172_Load(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void dgvDrzave_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex != 4) {
                new frmNovaDrzavaIB230172(1, Convert.ToInt32(dgvDrzave.SelectedRows[0].Cells["Id"].Value)).ShowDialog();
            }
            else {
                new frmGradoviIB230172(Convert.ToInt32(dgvDrzave.SelectedRows[0].Cells["Id"].Value)).ShowDialog();
            }
        }

        private void UcitajPodatke()
        {
            DataTable dt = new DataTable();
            dt.Columns.Add("Zastava", typeof(Image));
            dt.Columns.Add("Drzava");
            dt.Columns.Add("BrojGradova");
            dt.Columns.Add("Aktivna");
            dt.Columns.Add("Id");

            var drzave = db.DrzaveIB230172.ToList();

            for (int i = 0; i < drzave.Count; i++) {
                DataRow dr = dt.NewRow();
                dr["Zastava"] = drzave[i].Zastava.ToImage();
                dr["Drzava"] = drzave[i].Naziv;
                dr["BrojGradova"] = db.GradoviIB230172.Count(gr => gr.DrzavaId == drzave[i].Id);
                dr["Aktivna"] = drzave[i].Status;
                dr["Id"] = drzave[i].Id;

                dt.Rows.Add(dr);
            }

            dgvDrzave.DataSource = null;
            dgvDrzave.DataSource = dt;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            lblVrijeme.Text = $"Trenutno vrijeme: {DateTime.Now.ToString("hh:mm:ss")}";
        }

        private void btnNovaDrzava_Click(object sender, EventArgs e)
        {
            if (new frmNovaDrzavaIB230172().ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
            }
        }

        private void btnPrintaj_Click(object sender, EventArgs e)
        {
            new frmIzvjestaji(Convert.ToInt32(dgvDrzave.SelectedRows[0].Cells["Id"].Value)).ShowDialog();
        }
    }
}
