using FIT.Data;
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
    public partial class frmNovaProstorijaIB230172 : Form
    {
        public bool Modifikovanje { get; set; }
        public int ProstorijaID { get; set; }
        public frmNovaProstorijaIB230172(bool modifikovanje = false, int prostorijaID = -1)
        {
            InitializeComponent();
            Modifikovanje = modifikovanje;
            ProstorijaID = prostorijaID;
        }

        private void frmNovaProstorijaIB230172_Load(object sender, EventArgs e)
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaID);
            if (Modifikovanje) {
                pictureBox1.Image = prostorija.Logo.ToImage();
                textBox1.Text = prostorija.Naziv;
                textBox2.Text = prostorija.Oznaka;
                textBox3.Text = prostorija.Kapacitet.ToString();
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            var slika = ofd.ShowDialog();
            if (slika != null) {
                pictureBox1.Image = Image.FromFile(ofd.FileName);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaID);

            if (Validiraj()) {
                if (Modifikovanje) {
                    SharedContext.db.ProstorijeIB230172.Update(prostorija);
                }
                else {
                    var nova = new ProstorijeIB230172 {
                        Logo = pictureBox1.Image.ToByteArray(),
                        Naziv = textBox1.Text,
                        Oznaka = textBox2.Text,
                        Kapacitet = int.Parse(textBox3.Text)
                    };

                    SharedContext.db.ProstorijeIB230172.Add(nova);
                }

                SharedContext.db.SaveChanges();

                DialogResult = DialogResult.OK;
                Close();
            }
            
        }

        private bool Validiraj()
        {
            return Validator.ProvjeriUnos(pictureBox1, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(textBox1, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(textBox2, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(textBox3, err, Kljucevi.ReqiredValue);
        }
    }
}
