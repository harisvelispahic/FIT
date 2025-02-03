using FIT.Data;
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
using System.Xml;

namespace FIT.WinForms
{
    public partial class frmNastavaIB230172 : Form
    {
        public int ProstorijaId { get; set; }
        DLWMSDbContext db = new();
        public frmNastavaIB230172(int prostorijaId)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;
            dgvNastava.AutoGenerateColumns = false;
        }

        private void frmNastavaIB230172_Load(object sender, EventArgs e)
        {
            var prostorija = db.ProstorijeIB230172.Find(ProstorijaId);

            lblNaziv.Text = $"{prostorija.Naziv} - {prostorija.Oznaka}";

            cmbPredmet.UcitajPodatke(db.Predmeti.ToList());

            UcitajPodatke();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void btnDodaj_Click(object sender, EventArgs e)
        {
            var predmet = cmbPredmet.SelectedItem as Predmeti;
            var dan = cmbDan.Text;
            var vrijeme = cmbVrijeme.Text;

            if (db.NastavaIB230172.Any(x => x.ProstorijaId == ProstorijaId && x.Vrijeme == vrijeme && x.Dan == dan)) {
                MessageBox.Show("Prostorija zauzeta!");
                return;
            }

            var nastava = new NastavaIB230172 {
                ProstorijaId = this.ProstorijaId,
                PredmetId = predmet.Id,
                Dan = dan,
                Vrijeme = vrijeme,
                Oznaka = $"{predmet.Naziv} :: {dan} :: {vrijeme}"
            };

            db.NastavaIB230172.Add(nastava);
            db.SaveChanges();
            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            var nastava = db.NastavaIB230172.Where(x => x.ProstorijaId == this.ProstorijaId).ToList();

            var dt = new DataTable();
            dt.Columns.Add("Id");
            dt.Columns.Add("Predmet");
            dt.Columns.Add("Dan");
            dt.Columns.Add("Vrijeme");

            for(int  i = 0; i < nastava.Count; i++) {
                var dr = dt.NewRow();

                dr["Id"] = nastava[i].Id;
                dr["Predmet"] = db.Predmeti.Find(nastava[i].PredmetId);
                dr["Dan"] = nastava[i].Dan;
                dr["Vrijeme"] = nastava[i].Vrijeme;

                dt.Rows.Add(dr);
            }
            dgvNastava.DataSource = null;
            dgvNastava.DataSource = dt;
            
        }
    }
}
