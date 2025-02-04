using FIT.Data;
using FIT.WinForms.Helpers;
using Microsoft.EntityFrameworkCore;
using System.Data;

namespace FIT.WinForms
{
    public partial class frmNovaPoruka : Form
    {
        public int StudentId { get; set; }
        public frmNovaPoruka(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                var poruka = new StudentiPorukeIB230172 {
                    PredmetId = (cmbPredmet.SelectedItem as Predmeti).Id,
                    StudentId = StudentId,
                    Slika = pictureBox1.Image.ToByteArray(),
                    Validnost = dateTimePicker1.Value,
                    Hitnost = cmbHitnost.Text,
                    Sadrzaj = textBox1.Text
                };

                SharedContext.db.StudentiPorukeIB230172.Add(poruka);
                SharedContext.db.SaveChanges();

                DialogResult = DialogResult.OK;
                Close();
            }

        }

        private bool Validiraj()
        {
            return FIT.WinForms.Helpers.Validator.ProvjeriUnos(cmbPredmet, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validator.ProvjeriUnos(cmbHitnost, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validator.ProvjeriUnos(textBox1, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validator.ProvjeriUnos(pictureBox1, err, Kljucevi.ReqiredValue);
        }

        private void btnOdustani_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void frmNovaPoruka_Load(object sender, EventArgs e)
        {
            var listPredmeti = SharedContext.db.Predmeti.ToList();

            cmbPredmet.UcitajPodatke(listPredmeti);
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            var ofd = new OpenFileDialog();
            var slika = ofd.ShowDialog();
            if (slika != null) {
                pictureBox1.Image = Image.FromFile(ofd.FileName);
            }
        }

        private void cmbPredmet_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
