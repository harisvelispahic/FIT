using FIT.Infrastructure;
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
        DLWMSDbContext db;
        public int StudentId { get; set; }
        public double Prosjek { get; set; }
        public frmStudentInfo(int studentId, double prosjek)
        {
            InitializeComponent();
            db = new DLWMSDbContext();
            StudentId = studentId;
            Prosjek = prosjek;
            this.Text = db.Studenti.Find(StudentId).Indeks.ToString();
        }

        private void frmStudentInfo_Load(object sender, EventArgs e)
        {
            var student = db.Studenti.Find(StudentId);
            pbStudent.Image = student.Slika.ToImage();
            lblImePrezime.Text = student.Ime.ToString() + ' ' + student.Prezime.ToString();
            lblProsjek.Text = $"Prosjek: {Prosjek}"; 
        }
    }
}
