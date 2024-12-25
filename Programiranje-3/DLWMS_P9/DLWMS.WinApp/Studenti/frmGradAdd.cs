using DLWMS.Data;
using DLWMS.Infrastructure;
using DLWMS.WinApp.Helpers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DLWMS.WinApp.Studenti
{
    public partial class frmGradAdd : Form
    {
        public frmGradAdd()
        {
            InitializeComponent();
        }

        private void frmGradAdd_Load(object sender, EventArgs e)
        {
            cmbDržave.UcitajPodatke(InMemoryDB.Drzave);
        }

        private void btnSačuvaj_Click(object sender, EventArgs e)
        {
            //Data.Drzava drzava = cmbDržave.SelectedValue as Data.Drzava;
            InMemoryDB.Gradovi.Add(new Data.Grad {
                Id = InMemoryDB.Gradovi.Count + 1,
                Naziv = txtNaziv.Text,
                Oznaka = txtOznaka.Text,
                Aktivan = cbAktivan.Checked,
                DrzavaId = (int)cmbDržave.SelectedValue
            });
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
