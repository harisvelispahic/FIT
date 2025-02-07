using FIT.Data;
using FIT.WinForms.Helpers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms.IspitIB230172
{
    public partial class frmNovaPorukaIB230172 : Form
    {
        public int StudentId { get; set; }
        public frmNovaPorukaIB230172(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
        }

        private void frmNovaPorukaIB230172_Load(object sender, EventArgs e)
        {
            UcitajPredmete();
        }

        private void UcitajPredmete()
        {
            comboBox1.UcitajPodatke(SharedContext.db.Predmeti.ToList());
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new();
            var slika = ofd.ShowDialog();
            if (slika != null) {
                pictureBox1.Image = Image.FromFile(ofd.FileName);
            }
        }

        private void btnOdustani_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                var novaPoruka = new StudentiPorukeIB230172 {
                    StudentId = StudentId,
                    PredmetId = (comboBox1.SelectedItem as Predmeti).Id,
                    Validnost = dateTimePicker1.Value,
                    Hitnost = comboBox2.Text,
                    Sadrzaj = textBox1.Text,
                    Slika = pictureBox1.Image.ToByteArray()
                };

                SharedContext.db.StudentiPorukeIB230172.Add(novaPoruka);
                SharedContext.db.SaveChanges();

                DialogResult = DialogResult.OK;
                Close();
            }
        }

        private bool Validiraj()
        {
            return Validator.ProvjeriUnos(comboBox1, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(comboBox2, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(textBox1, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(pictureBox1, err, Kljucevi.ReqiredValue);
        }
    }
}
