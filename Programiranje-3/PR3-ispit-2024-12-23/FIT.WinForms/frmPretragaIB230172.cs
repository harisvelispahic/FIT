using FIT.Data;
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

namespace FIT.WinForms
{
    public partial class frmPretragaIB230172 : Form
    {
        public frmPretragaIB230172()
        {
            InitializeComponent();
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmPretragaIB230172_Load(object sender, EventArgs e)
        {
            cmbSemestar.UcitajPodatke(SharedContext.db.Semestri.ToList(), "Oznaka");
            cmbUloga.UcitajPodatke(SharedContext.db.Uloge.ToList());

            cmbSemestar.SelectedIndex = 0;
            cmbUloga.SelectedIndex = 0;

            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            cmbSemestar.UcitajPodatke(SharedContext.db.Semestri.ToList(), "Oznaka");
            cmbUloga.UcitajPodatke(SharedContext.db.Uloge.ToList());

            //cmbSemestar.SelectedIndex = 0;
            //cmbUloga.SelectedIndex = 0;

            dataGridView1.DataSource = null;
            var listaStudenata = SharedContext.db.Studenti
                .Include(x => x.PolozeniPredmeti)
                .ThenInclude(x => x.Predmet)
                .Include(x => x.StudentiUloge)
                .ThenInclude(x => x.Uloga)
                .Where(x => x.SemestarId == (cmbSemestar.SelectedItem as Semestri).Id &&
                (x.StudentiUloge.Any(y => y.UlogaId == (cmbUloga.SelectedItem as Uloge).Id) &&
                x.DatumRodjenja >= dtpOd.Value &&
                x.DatumRodjenja <= dtpDo.Value)
                ).ToList();

            dataGridView1.DataSource = listaStudenata;

            for (int i = 0; i < listaStudenata.Count; i++) {
                dataGridView1.Rows[i].Cells["Uloga"].Value = cmbUloga.Text;
            }


        }

        private void cmbSemestar_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void cmbUloga_SelectedIndexChanged(object sender, EventArgs e)
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

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 6) {
                //new frmPorukeIB230172((dataGridView1.SelectedRows[0].DataBoundItem as Student).Id).ShowDialog();
                new frmPorukeBrojIndeksa((dataGridView1.SelectedRows[0].DataBoundItem as Student).Id).ShowDialog();
            }
        }
    }
}
