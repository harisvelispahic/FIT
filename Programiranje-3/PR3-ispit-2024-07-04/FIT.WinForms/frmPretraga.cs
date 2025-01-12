using FIT.Data;
using FIT.Infrastructure;
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
    public partial class frmPretraga : Form
    {
        DLWMSDbContext db;
        public frmPretraga()
        {
            InitializeComponent();
            db = new DLWMSDbContext();
            dgvPretraga.AutoGenerateColumns = false;
        }

        private int UcitajPodatke()
        {
            List<Student> listStudenti;
            if(cmbSpol.Text.ToString() != "Svi spolovi") {

                listStudenti = db.Studenti.
                Where(st => st.Spol == cmbSpol.Text.ToString() &&
                    st.DatumRodjenja > dtpOd.Value &&
                    st.DatumRodjenja < dtpDo.Value).
                ToList();
            }
            else {
                listStudenti = db.Studenti.
                Where(st => st.DatumRodjenja > dtpOd.Value &&
                    st.DatumRodjenja < dtpDo.Value).
                ToList();
            }

            DataTable dt = new DataTable();
            dt.Columns.Add("Indeks");
            dt.Columns.Add("ImePrezime");
            dt.Columns.Add("Prosjek");
            dt.Columns.Add("DatumRodjenja");
            dt.Columns.Add("Aktivan");
            dt.Columns.Add("Id");

            for (int i = 0; i < listStudenti.Count; i++) {
                var dr = dt.NewRow();
                dr["Indeks"] = listStudenti[i].Indeks;
                dr["ImePrezime"] = listStudenti[i].Ime + ' ' + listStudenti[i].Prezime;

                var ocjene = db.PolozeniPredmeti.
                    Where(pp => pp.StudentId == listStudenti[i].Id).ToList();
                //double prosjek = 0;
                //for(int j = 0; j < ocjene.Count; j++) {
                //    prosjek += ocjene[j].Ocjena;
                //}
                //if (ocjene.Count != 0)
                //    prosjek /= ocjene.Count;

                dr["Prosjek"] = ocjene.Count == 0 ? 0 : ocjene.Average(pp => pp.Ocjena);

                dr["DatumRodjenja"] = listStudenti[i].DatumRodjenja.ToString();
                dr["Aktivan"] = listStudenti[i].Aktivan;
                dr["Id"] = listStudenti[i].Id;

                dt.Rows.Add(dr);
            }

            dgvPretraga.DataSource = null;
            dgvPretraga.DataSource = dt;

            return listStudenti.Count;
        }

        private void cmbSpol_SelectedIndexChanged(object sender, EventArgs e)
        {
            //MessageBox.Show(cmbSpol.Text.ToString());
            if(UcitajPodatke()==0)
                MessageBox.Show("Nijedan student ne zadovoljava ovaj kriterij!");

        }

        private void frmPretraga_Load(object sender, EventArgs e)
        {
            dtpOd.Value = new DateTime(2000, 1, 1);
            UcitajPodatke();
        }

        private void dtpOd_ValueChanged(object sender, EventArgs e)
        {
            //if (UcitajPodatke() == 0)
            //    MessageBox.Show("Nijedan student ne zadovoljava ovaj kriterij!");
            UcitajPodatke();
        }

        private void dtpDo_ValueChanged(object sender, EventArgs e)
        {
            if (UcitajPodatke() == 0)
                MessageBox.Show("Nijedan student ne zadovoljava ovaj kriterij!");
        }

        private void dgvPretraga_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex != 5) {
                //MessageBox.Show("Test");
                var idValue = dgvPretraga.SelectedRows[0].Cells["Id"].Value;
                var prosjek = dgvPretraga.SelectedRows[0].Cells["Prosjek"].Value;
                new frmStudentInfo(Convert.ToInt32(idValue), Convert.ToDouble(prosjek)).ShowDialog();
            }
            else {
                new frmUvjerenja(Convert.ToInt32(dgvPretraga.SelectedRows[0].Cells["Id"].Value)).ShowDialog();
            }
        }
    }
}
