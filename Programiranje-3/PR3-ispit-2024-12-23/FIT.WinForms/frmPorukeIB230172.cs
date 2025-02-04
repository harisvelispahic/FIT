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
    public partial class btnNovaPoruka : Form
    {
        public int StudentId {  get; set; }
        public btnNovaPoruka(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
        }

        private void frmPorukeIB230172_Load(object sender, EventArgs e)
        {
            var student = SharedContext.db.Studenti.Find(StudentId);
            label1.Text = "Poruke studenta " + student.ImePrezime + ":"; 
        }
    }
}
