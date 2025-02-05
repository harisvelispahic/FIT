using FIT.Data;
using FIT.Infrastructure;
using Microsoft.EntityFrameworkCore;
using Microsoft.Reporting.WinForms;
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
    public partial class frmPretragaIB230172 : Form
    {
        public frmPretragaIB230172()
        {
            InitializeComponent();
            dgvStudenti.AutoGenerateColumns = false;
        }

        private void frmPretragaIB230172_Load(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            dgvStudenti.DataSource = null;
            dgvStudenti.DataSource = SharedContext.db.Studenti
                .Include(pp => pp.PolozeniPredmeti)
                .Where(x => x.Spol == cmbSpol.Text &&
                    x.DatumRodjenja >= dtpOd.Value &&
                    x.DatumRodjenja <= dtpDo.Value)
                .ToList();
        }

        private void dgvStudenti_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            //MessageBox.Show((dgvStudenti.SelectedRows[0].DataBoundItem as Student).Id.ToString());
            if (e.ColumnIndex != 5) {
                new frmStudentInfo((dgvStudenti.SelectedRows[0].DataBoundItem as Student).Id).ShowDialog();
            }
            else {
                new frmUvjerenjaIB230172((dgvStudenti.SelectedRows[0].DataBoundItem as Student).Id).ShowDialog();
            }
        }

        private void cmbSpol_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void dtpOd_ValueChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void dtpDo_ValueChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void dgvStudenti_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
