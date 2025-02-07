using FIT.Data;
using FIT.WinForms.Helpers;
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

            lblnaziv.Text = $"{prostorija.Naziv} - {prostorija.Oznaka}";
            comboBox1.UcitajPodatke(SharedContext.db.Predmeti.ToList());

            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            dataGridView1.DataSource = null;
            dataGridView1.DataSource = SharedContext.db.NastavaIB230172.Where(x => x.ProstorijeId == ProstorijaId).ToList();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(SharedContext.db.NastavaIB230172.Any(x=>x.Dan==comboBox2.Text && x.Vrijeme == comboBox3.Text)) {
                MessageBox.Show($"U tom terminu nije dostupna ova prostorija!");
                return;
            }

            var nova = new NastavaIB230172 {
                PredmetId = (comboBox1.SelectedItem as Predmeti).Id,
                Dan = comboBox2.Text,
                Vrijeme = comboBox3.Text,
                ProstorijeId = ProstorijaId,
                Oznaka = $"{comboBox1.Text} :: {comboBox2.Text} :: {comboBox3.Text}"
            };

            SharedContext.db.NastavaIB230172.Add(nova);
            SharedContext.db.SaveChanges();

            UcitajPodatke();
        }
    }
}
