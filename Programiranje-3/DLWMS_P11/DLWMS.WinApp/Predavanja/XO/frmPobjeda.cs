using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DLWMS.WinApp
{
    public partial class frmPobjeda : Form
    {
        public frmPobjeda()
        {
            InitializeComponent();
            BackColor = Color.Gray;
            TransparencyKey = Color.Gray;
        }

        private void frmPobjeda_Load(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
