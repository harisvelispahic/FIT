using DLWMS.Infrastructure;

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
    public partial class frmStudentiPretraga : Form
    {
        public frmStudentiPretraga()
        {
            InitializeComponent();
            dgvStudenti.AutoGenerateColumns = false;
        }

        private void frmStudentiPretraga_Load(object sender, EventArgs e)
        {
            UcitajStudente();
        }

        private void UcitajStudente()
        {
            dgvStudenti.DataSource = null;
            dgvStudenti.DataSource = InMemoryDB.Studenti;
        }

        private void btnDodajStudenta_Click(object sender, EventArgs e)
        {
            if(new frmStudentAddEdit().ShowDialog()== DialogResult.OK)
                UcitajStudente();
        }
    }
}
