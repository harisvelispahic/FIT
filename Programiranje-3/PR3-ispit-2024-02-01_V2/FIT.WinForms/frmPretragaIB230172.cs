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
            UcitajDrzave();
            UcitajGradove();

            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            var grad = comboBox2.SelectedItem as GradoviIB230172;

            dataGridView1.DataSource = null;
            var listaStudenata = SharedContext.db.Studenti
                .Include(x => x.PolozeniPredmeti)
                //.Include(x => x.Grad)
                //.ThenInclude(x=>x.Drzava)
                .Where(x => x.GradId == grad.Id)
                .ToList();
            dataGridView1.DataSource = listaStudenata;

            if(listaStudenata.Count == 0) {
                MessageBox.Show($"Nema studenata rođenih u gradu {comboBox2.Text}, država {comboBox1.Text}");
                return;
            }

            for(int i = 0; i < listaStudenata.Count; i++) {
                if (dataGridView1.Rows[i].Cells["Prosjek"].Value == 0.ToString()) {
                    dataGridView1.Rows[i].Cells["Prosjek"].Value = 5.ToString();
                }
            }
        }

        private void UcitajGradove()
        {
            var drzava = comboBox1.SelectedItem as DrzaveIB230172;
            comboBox2.UcitajPodatke(SharedContext.db.GradoviIB230172.Where(x => x.DrzavaId == drzava.Id).ToList());
        }

        private void UcitajDrzave()
        {
            comboBox1.UcitajPodatke(SharedContext.db.DrzaveIB230172.ToList());
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajGradove();
            int brojGradova = comboBox2.Items.Count;
            if (brojGradova > 0)
                UcitajPodatke();
            else {
                MessageBox.Show($"Nema studenata rođenih u državi {comboBox1.Text}");

            }

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajPodatke();

        }
    }
}
