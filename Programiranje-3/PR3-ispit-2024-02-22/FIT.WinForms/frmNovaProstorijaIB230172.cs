using FIT.Data;
using FIT.Infrastructure;
using FIT.WinForms.Helpers;
using Microsoft.CodeAnalysis.VisualBasic.Syntax;
using Microsoft.EntityFrameworkCore.Update;
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
        DLWMSDbContext db = new();
        public int ProstorijaId { get; set; }
        public bool Modificiranje { get; set; } = false;
        public frmNovaProstorijaIB230172(int prostorijaId = 0, bool modificiranje = false)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;
            Modificiranje = modificiranje;
        }

        private void frmNovaProstorijaIB230172_Load(object sender, EventArgs e)
        {
            if (Modificiranje) {
                var prostorija = db.ProstorijeIB230172.Find(ProstorijaId);
                pbSlika.Image = prostorija.Logo.ToImage();
                txtNaziv.Text = prostorija.Naziv;
                txtOznaka.Text = prostorija.Oznaka;
                txtKapacitet.Text = prostorija.Kapacitet.ToString();
            }

            

        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                if (Modificiranje == false) {
                    var prostorija = new ProstorijeIB230172 {

                        Logo = pbSlika.Image.ToByteArray(),
                        Naziv = txtNaziv.Text,
                        Oznaka = txtOznaka.Text,
                        Kapacitet = int.Parse(txtKapacitet.Text)
                    };

                    db.ProstorijeIB230172.Add(prostorija);
                    db.SaveChanges();
                }
                else {
                    var prostorija = db.ProstorijeIB230172.Find(ProstorijaId);

                    prostorija.Logo = pbSlika.Image.ToByteArray();
                    prostorija.Naziv = txtNaziv.Text;
                    prostorija.Oznaka = txtOznaka.Text;
                    prostorija.Kapacitet = int.Parse(txtKapacitet.Text);


                    db.ProstorijeIB230172.Update(prostorija);
                    db.SaveChanges();
                    DialogResult = DialogResult.OK;
                    Close();
                    
                }


                DialogResult = DialogResult.OK;
                Close();
            }                                    
        }

        private bool Validiraj()
        {
            return Validator.ProvjeriUnos(pbSlika, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(txtNaziv, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(txtOznaka, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(txtKapacitet, err, Kljucevi.ReqiredValue);

        }

        private void pbSlika_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new();
            var rezultat = ofd.ShowDialog();
            if (rezultat != null) {
                pbSlika.Image = Image.FromFile(ofd.FileName);
            }
        }
    }
}
