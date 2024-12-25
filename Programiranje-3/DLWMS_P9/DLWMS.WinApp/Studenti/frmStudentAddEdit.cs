using DLWMS.Data;
using DLWMS.Infrastructure;
using DLWMS.WinApp.Helpers;

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using static System.Windows.Forms.VisualStyles.VisualStyleElement.TaskbarClock;

namespace DLWMS.WinApp.Studenti
{
    public partial class frmStudentAddEdit : Form
    {
        public frmStudentAddEdit()
        {
            InitializeComponent();
        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {

            if (ValidanUnos()) {
                Student student = new Student {
                    Ime = txtIme.Text,
                    Prezime = txtPrezime.Text,
                    DatumRodjenja = dtpDatumRodjenja.Value,
                    SpolId = (int)cmbSpol.SelectedValue,
                    Email = txtEmail.Text,
                    BrojIndeksa = txtBrojIndeksa.Text,
                    Lozinka = txtLozinka.Text,
                    GradId = (int)cmbGradovi.SelectedValue,
                    Slika = pbSlika.Image,
                    Aktivan = cbAktivan.Checked
                };

                InMemoryDB.Studenti.Add(student);

                DialogResult = DialogResult.OK;
                Close();
            }


        }

        private bool ValidanUnos()
        {
            return
                    Validator.ProvjeriUnos(pbSlika, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtIme, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtPrezime, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(cmbSpol, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtBrojIndeksa, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtLozinka, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(cmbGradovi, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtEmail, err, Resursi.Get(Kljucevi.RequiredField));
        }

        private void frmStudentAddEdit_Load(object sender, EventArgs e)
        {
            UcitajSpolove();
            //UcitajDrzave();
            UcitajGenerisanePodatke();

        }

        private void GenerisiEmail()
        {
            txtEmail.Text = Generator.GenerisiEmail(txtIme.Text, txtPrezime.Text);
        }

        private void UcitajGenerisanePodatke()
        {
            txtBrojIndeksa.Text = Generator.GenerisiBrojIndeksa();
            txtLozinka.Text = Generator.GenerisiLozinku();
        }

        private void UcitajDrzave()
        {
            cmbDrzave.UcitajPodatke(InMemoryDB.Drzave);

            //cmbSpol.DataSource = InMemoryDB.Drzave;
            //cmbSpol.DisplayMember = "Naziv";
            //cmbSpol.ValueMember = "Id";
        }

        private void UcitajSpolove()
        {
            cmbSpol.UcitajPodatke(InMemoryDB.Spolovi);

            //cmbSpol.DataSource = InMemoryDB.Spolovi;
            //cmbSpol.DisplayMember = "Naziv";
            //cmbSpol.ValueMember = "Id";
        }

        private void btnUcitajSliku_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
                pbSlika.Image = Image.FromFile(openFileDialog1.FileName);
        }

        private void cmbDrzave_SelectedIndexChanged(object sender, EventArgs e)
        {
            var drzava = cmbDrzave.SelectedItem as Drzava;
            if (drzava == null)
                return;
            var gradovi = InMemoryDB.Gradovi.Where(x => x.DrzavaId == drzava.Id).ToList();
            cmbGradovi.UcitajPodatke(gradovi);
        }

        private void txtIme_TextChanged(object sender, EventArgs e)
        {
            GenerisiEmail();
        }

        private void txtPrezime_TextChanged(object sender, EventArgs e)
        {
            GenerisiEmail();
        }

        private void btnDržavaAdd_Click(object sender, EventArgs e)
        {
            var državaAdd = new frmDržavaAdd();
            if (državaAdd.ShowDialog() == DialogResult.OK) {
                cmbDrzave.UcitajPodatke(InMemoryDB.Drzave);
            }
        }
        //private void btnDržavaAdd_Click(object sender, EventArgs e)
        //{
        //    var državaAdd = new frmDržavaAdd();
        //    if (državaAdd.ShowDialog() == DialogResult.OK) {
        //        cmbDrzave.SelectedIndexChanged -= cmbDrzave_SelectedIndexChanged; // Unsubscribe
        //        cmbDrzave.UcitajPodatke(InMemoryDB.Drzave);
        //        cmbDrzave.SelectedIndexChanged += cmbDrzave_SelectedIndexChanged; // Re-subscribe
        //    }
        //}


        private void btnGradAdd_Click(object sender, EventArgs e)
        {
            var gradAdd = new frmGradAdd();
            if (gradAdd.ShowDialog() == DialogResult.OK) {
                //cmbGradovi.UcitajPodatke(InMemoryDB.Gradovi);
                var drzava = cmbDrzave.SelectedItem as Drzava;
                var gradovi = InMemoryDB.Gradovi.Where(x => x.DrzavaId == drzava.Id).ToList();
                cmbGradovi.UcitajPodatke(gradovi);
            }
        }

        private void pbSlika_Click(object sender, EventArgs e)
        {

        }
    }

    public class Generator
    {
        public static string GenerisiEmail(string ime, string prezime)
        {
           return $"{ime.ToLower()}.{prezime.ToLower()}@{Resursi.Get(Kljucevi.Domain)}";
        }

        public static string GenerisiBrojIndeksa()
        {
            return $"IB{(DateTime.Now.Year - 2000) * 10000 + InMemoryDB.Studenti.Count + 1}";
        }

        internal static string GenerisiLozinku(int brojZnakova = 15)
        {
            string znakovi = "ABCDEFGHIJKLMNOPQRSTUVWXYZ*!-+/!$#%&()abcdefghijklmnopqrstuvwxyz0123456789";
            string loznika = "";//Gh0W3rT5
            Random random = new Random();
            for (int i = 0; i < brojZnakova; i++)
            {
                var narednlaLokacija = random.Next(0, znakovi.Length);//32
                loznika += znakovi[narednlaLokacija];
            }
            return loznika;
        }
    }
}
