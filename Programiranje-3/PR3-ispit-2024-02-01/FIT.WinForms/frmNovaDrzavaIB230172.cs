using FIT.Data;
using FIT.Infrastructure;
using FIT.WinForms.Helpers;
using Microsoft.EntityFrameworkCore.Diagnostics;
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
        public int Modifikovanje { get; set; }
        public int DrzavaId { get; set; }
        DLWMSDbContext db = new();
        public frmNovaDrzavaIB230172(int modifikovanje = 0, int drzavaId = -1)
        {
            InitializeComponent();
            Modifikovanje = modifikovanje;
            DrzavaId = drzavaId;
        }

        private void frmNovaDrzavaIB230172_Load(object sender, EventArgs e)
        {
            if (Modifikovanje == 1) {
                var drzava = db.DrzaveIB230172.Find(DrzavaId);
                pbZastava.Image = drzava.Zastava.ToImage();
                txtNaziv.Text = drzava.Naziv.ToString();
                cbStatus.Checked = drzava.Status;
            }

        }

        private void pbZastava_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == DialogResult.OK) {

                var slika = openFileDialog.FileName;
                pbZastava.Image = Image.FromFile(slika);

            }
        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            var drzava = db.DrzaveIB230172.Find(DrzavaId);

            if (Modifikovanje == 1) {
                db.DrzaveIB230172.Update(drzava);
                db.SaveChanges();
            }
            else {
                if (Validna()) {

                    var novaDrzava = new DrzaveIB230172() {
                        Zastava = pbZastava.Image.ToByteArray(),
                        Naziv = txtNaziv.Text,
                        Status = cbStatus.Checked
                    };

                    db.DrzaveIB230172.Add(novaDrzava);
                    db.SaveChanges();
                }
            }
            DialogResult = DialogResult.OK;
            Close();
        }

        private bool Validna()
        {
            return Validator.ProvjeriUnos(pbZastava, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(txtNaziv, err, Kljucevi.ReqiredValue);
        }
    }
}
