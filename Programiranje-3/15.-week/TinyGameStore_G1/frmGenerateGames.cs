using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TinyGameStore_G1
{
    public partial class frmGenerateGames : Form
    {
        public frmGenerateGames()
        {
            InitializeComponent();
        }

        private async void btnGenerate_Click(object sender, EventArgs e)
        {
            for(int i = 0; i < 5; i++)
            {
                MessageBox.Show("Test");
                Thread.Sleep(1000);
            }
        }
    }
}
