using FIT.Data;
using FIT.WinForms.Helpers;
using FIT.WinForms.IspitIB230172;
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

namespace FIT.WinForms.Ispit
{
    public partial class frmPretraga : Form
    {
        bool mboxUpozorenje = false;
        public frmPretraga()
        {
            InitializeComponent();
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmPretraga_Load(object sender, EventArgs e)
        {
            UcitajSemestre();
            UcitajUloge();
            UcitajPodatke();
            mboxUpozorenje = true;
        }

        private void UcitajUloge()
        {
            cmbUloga.UcitajPodatke(SharedContext.db.Uloge.ToList());
        }

        private void UcitajSemestre()
        {
            cmbSemestar.UcitajPodatke(SharedContext.db.Semestri.ToList(), "Oznaka");
        }

        private void UcitajPodatke()
        {
            var semestar = cmbSemestar.SelectedItem as Semestri;
            var uloga = cmbUloga.SelectedItem as Uloge;
            if (semestar == null || uloga == null) {
                return;
            }

            var listaStudenata = SharedContext.db.Studenti
                .Include(x => x.PolozeniPredmeti)
                .Include(x => x.StudentiUloge)
                .Where(x => x.SemestarId == semestar.Id
                && x.StudentiUloge.Any(y => y.StudentId == x.Id && y.UlogaId == uloga.Id)
                && x.DatumRodjenja > dateTimePicker1.Value
                && x.DatumRodjenja < dateTimePicker2.Value).ToList();

            if (listaStudenata.Count == 0 && mboxUpozorenje) {
                dataGridView1.DataSource = null;
                MessageBox.Show($"U bazi nisu evidentirani studenti rođeni u periodu od {dateTimePicker1.Value}" +
                    $" – {dateTimePicker2.Value} godine, a koji su upisani u {semestar.Oznaka}" +
                    $" Semestar i posjeduju ulogu {uloga.Naziv}.");
                return;
            }

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = listaStudenata;

            for (int i = 0; i < listaStudenata.Count; i++) {
                dataGridView1.Rows[i].Cells["Uloga"].Value = uloga.Naziv;
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

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void dateTimePicker2_ValueChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == 6) {
                new frmPorukeIB230172((dataGridView1.SelectedRows[0].DataBoundItem as Student).Id)
                    .ShowDialog();
            }
        }
    }
}
