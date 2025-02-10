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

namespace FIT.WinForms.IspitIB230172
{
    public partial class frmNastavaIB230172 : Form
    {
        public int ProstorijaId { get; set; }
        public frmNastavaIB230172(int prostorijaId)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmNastavaIB230172_Load(object sender, EventArgs e)
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);

            lblProstorija.Text = prostorija.Naziv;

            UcitajPodatke();

            comboBox1.UcitajPodatke(SharedContext.db.Predmeti.ToList());
            comboBox2.SelectedIndex = 0;
            comboBox3.SelectedIndex = 0;
        }

        private void UcitajPodatke()
        {
            var listaNastava = SharedContext.db.NastavaIB230172
                .Include(x => x.Predmet)
                .Where(x => x.ProstorijaId == this.ProstorijaId)
                .ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = listaNastava;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var predmet = comboBox1.SelectedItem as Predmeti;
            var dan = comboBox2.Text;
            var vrijeme = comboBox3.Text;

            if(SharedContext.db.NastavaIB230172
                .Include(x=>x.Prostorija)
                .Any(x=>x.ProstorijaId==this.ProstorijaId && x.Dan==dan && x.Vrijeme == vrijeme)) {
                MessageBox.Show("Zauzeto");
                return;
            }

            var novaNastava = new NastavaIB230172 {
                PredmetId = predmet.Id,
                Dan = dan,
                Vrijeme = vrijeme,
                ProstorijaId = this.ProstorijaId,
                Oznaka = $"{predmet.Naziv} :: {dan} :: {vrijeme}"
            };

            SharedContext.db.NastavaIB230172.Add(novaNastava);
            SharedContext.db.SaveChanges();

            UcitajPodatke();
        }
    }
}
