using FIT.Data;
using FIT.WinForms.Helpers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography.Xml;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms.IspitIB230172
{
    public partial class frmNovaDrzava : Form
    {
        public int DrzavaId { get; set; }
        public bool Modifikovanje { get; set; }
        public frmNovaDrzava(int drzavaId=-1, bool modifikovanje=false)
        {
            InitializeComponent();
            DrzavaId = drzavaId;
            Modifikovanje = modifikovanje;
        }

        private void frmNovaDrzava_Load(object sender, EventArgs e)
        {
            if (Modifikovanje) {
                var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);
                pictureBox1.Image = drzava.Zastava.ToImage();
                textBox1.Text = drzava.Naziv;
                checkBox1.Checked = drzava.Status;
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            var ofd = new OpenFileDialog();
            var slika = ofd.ShowDialog();

            if (slika != null) {
                pictureBox1.Image = Image.FromFile(ofd.FileName);
            }
        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                if (Modifikovanje) {
                    var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);

                    drzava.Zastava = pictureBox1.Image.ToByteArray();
                    drzava.Naziv = textBox1.Text;
                    drzava.Status = checkBox1.Checked;

                    SharedContext.db.DrzaveIB230172.Update(drzava);
                }
                else {
                    var novaDrzava = new DrzaveIB230172 {
                        Zastava = pictureBox1.Image.ToByteArray(),
                        Naziv = textBox1.Text,
                        Status = checkBox1.Checked

                    };

                    SharedContext.db.DrzaveIB230172.Add(novaDrzava);
                }

                SharedContext.db.SaveChanges();
                DialogResult = DialogResult.OK;

                Close();
            }
        }

        private bool Validiraj()
        {
            return FIT.WinForms.Helpers.Validiraj.ProvjeriUnos(pictureBox1, err, Kljucevi.ReqiredValue) &&
                FIT.WinForms.Helpers.Validiraj.ProvjeriUnos(textBox1, err, Kljucevi.ReqiredValue);
        }
    }
}
