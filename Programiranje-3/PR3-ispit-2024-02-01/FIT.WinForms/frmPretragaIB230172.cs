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

namespace FIT.WinForms
{
    public partial class frmPretragaIB230172 : Form
    {
        public bool mboxUpozorenje = false;
        DLWMSDbContext db = new();
        public frmPretragaIB230172()
        {
            InitializeComponent();
            dgvStudenti.AutoGenerateColumns = false;
        }

        private void frmPretragaIB230172_Load(object sender, EventArgs e)
        {
            PopuniDrzave();
            mboxUpozorenje = true;
        }

        private void PopuniDrzave()
        {
            cmbDrzave.UcitajPodatke(db.DrzaveIB230172.ToList());
        }
        private void PopuniGradove()
        {
            var drzava = cmbDrzave.Text;
            cmbGradovi.UcitajPodatke(db.GradoviIB230172.Include(x => x.Drzava).Where(x => x.Drzava.Naziv == drzava).ToList());
        }
        private void UcitajPodatke()
        {

            var drzavaText = cmbDrzave.Text;
            var gradText = cmbGradovi.Text;

            DataTable dt = new DataTable();
            dt.Columns.Add("Id");
            dt.Columns.Add("Ime");
            dt.Columns.Add("Prezime");
            dt.Columns.Add("Grad");
            dt.Columns.Add("Drzava");
            dt.Columns.Add("Prosjek");

            var podaci = db.Studenti.Include(x => x.Grad).Where(x => x.Grad.Naziv == gradText).ToList();
            

            for (int i = 0; i < podaci.Count; i++) {
                var dr = dt.NewRow();

                dr["Id"] = podaci[i].Id;
                dr["Ime"] = podaci[i].Ime;
                dr["Prezime"] = podaci[i].Prezime;
                dr["Grad"] = gradText;
                dr["Drzava"] = drzavaText;
                var listaPredmeta = db.PolozeniPredmeti.Where(x => x.StudentId == podaci[i].Id).ToList();
                if (listaPredmeta.Count == 0) {
                    dr["Prosjek"] = 5;
                }
                else {
                    dr["Prosjek"] = listaPredmeta.Average(x => x.Ocjena);
                }

                dt.Rows.Add(dr);
            }

            dgvStudenti.DataSource = null;
            dgvStudenti.DataSource = dt;

            if (podaci.Count == 0 && mboxUpozorenje) {
                MessageBox.Show($"U bazi nije evidentiran niti jedan student rođen u gradu {gradText}, {drzavaText}");
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void cmbDrzave_SelectedIndexChanged(object sender, EventArgs e)
        {
            PopuniGradove();
            UcitajPodatke();
        }

        private void cmbGradovi_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }
    }
}
