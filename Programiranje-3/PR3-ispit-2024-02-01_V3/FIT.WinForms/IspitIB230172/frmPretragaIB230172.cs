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
    public partial class frmPretragaIB230172 : Form
    {
        public frmPretragaIB230172()
        {
            InitializeComponent();
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmPretragaIB230172_Load(object sender, EventArgs e)
        {
            comboBox1.UcitajPodatke(SharedContext.db.DrzaveIB230172.ToList());
            var listaGradova = SharedContext.db.GradoviIB230172
                .Include(x => x.Drzava)
                .Where(x => x.DrzavaId == (comboBox1.SelectedItem as DrzaveIB230172).Id)
                .ToList();
            comboBox2.UcitajPodatke(listaGradova);


            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            var grad = comboBox2.SelectedItem as GradoviIB230172;

            var listaStudenata = SharedContext.db.Studenti
                .Where(x => x.GradId == grad.Id)
                .ToList();

            dataGridView1.DataSource = null;
            dataGridView1.DataSource = listaStudenata;

            for (int i = 0; i < listaStudenata.Count; i++) {
                dataGridView1.Rows[i].Cells["Drzava"].Value = grad.Drzava.Naziv;
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajGradove();
            UcitajPodatke();
        }

        private void UcitajGradove()
        {
            var drzava = comboBox1.SelectedItem as DrzaveIB230172;
            var listaGradova = SharedContext.db.GradoviIB230172
                .Where(x => x.DrzavaId == drzava.Id)
                .ToList();

            comboBox2.UcitajPodatke(listaGradova);
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            UcitajPodatke();
        }
    }
}
