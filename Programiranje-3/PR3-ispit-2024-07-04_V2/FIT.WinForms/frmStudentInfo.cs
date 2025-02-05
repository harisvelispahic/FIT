using FIT.WinForms.Helpers;
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
    public partial class frmStudentInfo : Form
    {
        public int StudentId;
        public frmStudentInfo(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
        }

        private void frmStudentInfo_Load(object sender, EventArgs e)
        {
            var student = SharedContext.db.Studenti.Find(StudentId);
            this.Text = student.Indeks;
            label1.Text = student.ImePrezime;
            label2.Text = $"Prosjek: {student.Prosjek}";
            pictureBox1.Image = student.Slika.ToImage();
        }
    }
}
