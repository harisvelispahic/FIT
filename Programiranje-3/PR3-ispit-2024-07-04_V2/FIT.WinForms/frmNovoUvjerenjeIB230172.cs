using FIT.Data;
using FIT.WinForms.Helpers;
using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms
{
    public partial class frmNovoUvjerenjeIB230172 : Form
    {
        public int StudentId { get; set; }
        public frmNovoUvjerenjeIB230172(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
        }

        private void frmNovoUvjerenjeIB230172_Load(object sender, EventArgs e)
        {

        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                var uvjerenje = new StudentiUvjerenjaIB230172 {
                    StudentId = this.StudentId,
                    Vrsta = comboBox1.Text,
                    Svrha = textBox1.Text,
                    Uplatnica = pictureBox1.Image.ToByteArray(),
                    VrijemeKreiranja = DateTime.Now,
                    Printano = false
                };
                SharedContext.db.StudentiUvjerenjaIB230172.Add(uvjerenje);
                SharedContext.db.SaveChanges();

                DialogResult = DialogResult.OK;
                Close();
            }
        }

        private bool Validiraj()
        {
            return FIT.WinForms.Helpers.Validator.ProvjeriUnos(comboBox1, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validator.ProvjeriUnos(textBox1, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validator.ProvjeriUnos(pictureBox1, err, Kljucevi.ReqiredValue);
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            var slika = openFileDialog.ShowDialog();
            if (slika != null) {
                pictureBox1.Image = Image.FromFile(openFileDialog.FileName);
            }
        }
    }
}
