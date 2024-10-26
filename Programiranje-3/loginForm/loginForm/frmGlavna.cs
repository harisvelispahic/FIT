using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace loginForm
{
    public partial class frmGlavna : Form
    {
        public frmGlavna()
        {
            InitializeComponent();
            frmLogin frmLogin = new frmLogin(this);
            frmLogin.ShowDialog();
            this.Hide();
        }
    }
}
