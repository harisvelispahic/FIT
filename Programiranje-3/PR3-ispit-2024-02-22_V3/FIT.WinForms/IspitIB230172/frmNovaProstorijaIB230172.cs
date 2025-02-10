using FIT.Data;
using FIT.WinForms.Helpers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms.IspitIB230172
{
    public partial class frmNovaProstorijaIB230172 : Form
    {
        public int ProstorijaId { get; set; }
        public bool Modifikovanje { get; set; }
        public frmNovaProstorijaIB230172(int prostorijaId = -1, bool modifikovanje = false)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;
            Modifikovanje = modifikovanje;
        }

        private void frmNovaProstorijaIB230172_Load(object sender, EventArgs e)
        {
            if (Modifikovanje) {
                var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);

                pictureBox1.Image = prostorija.Logo.ToImage();
                txtNaziv.Text = prostorija.Naziv;
                txtOznaka.Text = prostorija.Oznaka;
                txtKapacitet.Text = prostorija.Kapacitet.ToString();
            }


        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {

                if (Modifikovanje) {
                    var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);

                    prostorija.Logo = pictureBox1.Image.ToByteArray();
                    prostorija.Naziv = txtNaziv.Text;
                    prostorija.Oznaka = txtOznaka.Text;
                    prostorija.Kapacitet = int.Parse(txtKapacitet.Text);

                    SharedContext.db.ProstorijeIB230172.Update(prostorija);
                }
                else {
                    var novaProstorija = new ProstorijeIB230172 {
                        Naziv = txtNaziv.Text,
                        Oznaka = txtOznaka.Text,
                        Logo = pictureBox1.Image.ToByteArray(),
                        Kapacitet = int.Parse(txtKapacitet.Text)
                    };

                    SharedContext.db.ProstorijeIB230172.Add(novaProstorija);
                }

                SharedContext.db.SaveChanges();

                DialogResult = DialogResult.OK;
                Close();
            }
        }

        private bool Validiraj()
        {
            return FIT.WinForms.Helpers.Validator.ProvjeriUnos(pictureBox1, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validator.ProvjeriUnos(txtNaziv, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validator.ProvjeriUnos(txtOznaka, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validator.ProvjeriUnos(txtKapacitet, err, Kljucevi.ReqiredValue);
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new();
            var slika = ofd.ShowDialog();
            if (slika != null) {
                pictureBox1.Image = Image.FromFile(ofd.FileName);
            }
        }
    }
}
