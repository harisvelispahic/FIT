using FIT.Infrastructure;
using FIT.WinForms.Helpers;
using FIT.WinForms.Izvjestaji;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms
{
    public partial class frmProstorijeIB230172 : Form
    {
        DLWMSDbContext db = new();
        public frmProstorijeIB230172()
        {
            InitializeComponent();
            dgvProstrorije.AutoGenerateColumns = false;
        }

        private void frmProstorijeIB230172_Load(object sender, EventArgs e)
        {
            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            var prostorije = db.ProstorijeIB230172.ToList();

            var dt = new DataTable();
            dt.Columns.Add("ID");
            dt.Columns.Add("Naziv");
            dt.Columns.Add("Logo", typeof(Image));
            dt.Columns.Add("Oznaka");
            dt.Columns.Add("Kapacitet");
            dt.Columns.Add("BrojPredmeta");

            for (int i = 0; i < prostorije.Count; i++) {
                var dr = dt.NewRow();
                dr["Id"] = prostorije[i].Id;
                dr["Naziv"] = prostorije[i].Naziv;
                dr["Logo"] = prostorije[i].Logo.ToImage();
                dr["Oznaka"] = prostorije[i].Oznaka;
                dr["Kapacitet"] = prostorije[i].Kapacitet;
                dr["BrojPredmeta"] = db.NastavaIB230172.Count(x => x.ProstorijaId == prostorije[i].Id);

                dt.Rows.Add(dr);
            }

            dgvProstrorije.DataSource = null;
            dgvProstrorije.DataSource = dt;

        }

        private void btnNovaProstorija_Click(object sender, EventArgs e)
        {
            if (new frmNovaProstorijaIB230172().ShowDialog() == DialogResult.OK) {
                UcitajPodatke();
            }
        }

        private void dgvProstrorije_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex != 6 && e.ColumnIndex != 7) {
                if (new frmNovaProstorijaIB230172(Convert.ToInt32(dgvProstrorije.SelectedRows[0].Cells["Id"].Value), true).
                    ShowDialog() == DialogResult.OK) {
                    UcitajPodatke();
                }
            }
            else if (e.ColumnIndex == 6) {
                new frmNastavaIB230172(Convert.ToInt32(dgvProstrorije.SelectedRows[0].Cells["Id"].Value)).
                    ShowDialog();
            }
            else if (e.ColumnIndex == 7) {
                new frmPrisustvoIB230172(Convert.ToInt32(dgvProstrorije.SelectedRows[0].Cells["Id"].Value)).
                    ShowDialog();
            }
        }

        private void btnPrintaj_Click(object sender, EventArgs e)
        {
            new frmIzvjestaji(Convert.ToInt32(dgvProstrorije.SelectedRows[0].Cells["Id"].Value)).ShowDialog();
        }
    }
}
