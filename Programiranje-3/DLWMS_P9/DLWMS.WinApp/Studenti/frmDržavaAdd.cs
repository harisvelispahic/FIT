using DLWMS.Infrastructure;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DLWMS.WinApp.Studenti
{
    public partial class frmDržavaAdd : Form
    {
        public frmDržavaAdd()
        {
            InitializeComponent();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void frmDržavaAdd_Load(object sender, EventArgs e)
        {

        }

        private void btnSačuvaj_Click(object sender, EventArgs e)
        {
            InMemoryDB.Drzave.Add(new Data.Drzava {
                Id = InMemoryDB.Drzave.Count + 1,
                Naziv = txtNaziv.Text,
                Oznaka = txtOznaka.Text,
                Aktivan = cbAktivan.Checked
            });
            DialogResult = DialogResult.OK;
            Close();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
