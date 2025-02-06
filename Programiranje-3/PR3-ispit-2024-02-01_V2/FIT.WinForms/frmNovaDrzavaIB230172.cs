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
    public partial class frmNovaDrzavaIB230172 : Form
    {
        public int DrzavaId { get; set; }
        public bool modify { get; set; }
        public frmNovaDrzavaIB230172(int drzavaId = -1, bool modify = false)
        {
            InitializeComponent();
            DrzavaId = drzavaId;
            this.modify = modify;
        }

        private void frmNovaDrzavaIB230172_Load(object sender, EventArgs e)
        {
            if (modify) {
                var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);
                pictureBox1.Image = drzava.Zastava.ToImage();
                textBox1.Text = drzava.Naziv;
                checkBox1.Checked = drzava.Status;
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                var slika = pictureBox1.Image.ToByteArray();
                var naziv = textBox1.Text;
                var aktivna = checkBox1.Checked;

                var nova = new DrzaveIB230172 {
                    Naziv = naziv,
                    Status = aktivna,
                    Zastava = slika,
                };

                if (modify) {
                    var drzava = SharedContext.db.DrzaveIB230172.Find(DrzavaId);
                    drzava.Naziv = naziv;
                    drzava.Status = aktivna;
                    drzava.Zastava = slika;
                    SharedContext.db.DrzaveIB230172.Update(drzava);
                }
                else {
                    SharedContext.db.DrzaveIB230172.Add(nova);
                }

                SharedContext.db.SaveChanges();

                DialogResult = DialogResult.OK;
                Close();
            }
        }

        private bool Validiraj()
        {
            return Validator.ProvjeriUnos(pictureBox1, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(textBox1, err, Kljucevi.ReqiredValue);
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
