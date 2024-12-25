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
    public partial class frmIgraci : Form
    {
        public frmIgraci()
        {
            InitializeComponent();
        }

        public string Igrac1 { get; set; }
        public string Igrac2 { get; set; }


        private void btnStart_Click(object sender, EventArgs e)
        {
            Igrac1 = txtIgrac1.Text;
            Igrac2 = txtIgrac2.Text;
            Close();
        }
    }
}
