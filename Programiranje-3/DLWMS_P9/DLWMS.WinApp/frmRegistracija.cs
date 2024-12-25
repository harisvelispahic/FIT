using DLWMS.Data;
using DLWMS.Infrastructure;
using DLWMS.WinApp.Helpers;

namespace DLWMS.WinApp
{
    public partial class frmRegistracija : Form
    {
        public frmRegistracija()
        {
            InitializeComponent();
        }

        private void txtIme_TextChanged(object sender, EventArgs e)
        {
            GenerisiPodatke();
        }

        private void GenerisiPodatke()
        {
            var ime = txtIme.Text.ToLower();
            var prezime = txtPrezime.Text.ToLower();

            txtEmail.Text = $"{ime}.{prezime}@{Resursi.Get(Kljucevi.Domain)}";
            txtKorisnickoIme.Text = $"{ime}.{prezime}";

        }

        private void txtPrezime_TextChanged(object sender, EventArgs e)
        {
            GenerisiPodatke();
        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            if (ValidanUnos())
            {
                var noviKorisnik = new Korisnik()
                {
                    Aktivan = true,
                    Email = txtEmail.Text,
                    Id = InMemoryDB.Korisnici.Count + 1,
                    Ime = txtIme.Text,
                    KorisnickoIme = txtKorisnickoIme.Text,
                    Lozinka = txtLozinka.Text,
                    Prezime = txtPrezime.Text   
                };
                InMemoryDB.Korisnici.Add(noviKorisnik);
                MessageBox.Show(Resursi.Get(Kljucevi.UserAddSuccess),
                  Resursi.Get(Kljucevi.Information),
                  MessageBoxButtons.OK,
                  MessageBoxIcon.Information
                  );
                Close();
            }
        }

        private bool ValidanUnos()
        {
            return
                    Validator.ProvjeriUnos(txtIme, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtPrezime, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtEmail, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtKorisnickoIme, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(txtLozinka, err, Resursi.Get(Kljucevi.RequiredField));
        }
    }
}
