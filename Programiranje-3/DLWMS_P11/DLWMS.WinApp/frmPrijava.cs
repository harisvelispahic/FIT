using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using DLWMS.Infrastructure;
using DLWMS.WinApp.Helpers;

using static System.Windows.Forms.VisualStyles.VisualStyleElement.ListView;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TaskbarClock;

namespace DLWMS.WinApp
{
    public partial class frmPrijava : Form
    {
        public frmPrijava()
        {
            InitializeComponent();
        }

        private void btnPrijava_Click(object sender, EventArgs e)
        {
            var korisnickoIme = txtKorisnickoIme.Text;
            var lozinka = txtLozinka.Text;
            if (ValidanUnos())
            {
                foreach (var korisnik in InMemoryDB.Korisnici)
                {
                    if (korisnik.KorisnickoIme == korisnickoIme && korisnik.Lozinka == lozinka)
                    {
                        if (korisnik.Aktivan)
                        {
                            Hide();
                            if (new frmGlavna().ShowDialog() == DialogResult.OK)
                                Show();
                            else
                                Close();
                        }
                        else
                            MessageBox.Show(Resursi.Get(Kljucevi.NotActive));
                        return;
                    }
                }
                MessageBox.Show(Resursi.Get(Kljucevi.UsernameOrPasswordNotValid),
                    Resursi.Get(Kljucevi.Warning),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Warning
                    );
            }
        }

        private bool ValidanUnos()
        {
            return Validator.ProvjeriUnos(txtKorisnickoIme, err, Resursi.Get(Kljucevi.RequiredField)) &&
                Validator.ProvjeriUnos(txtLozinka, err, Resursi.Get(Kljucevi.RequiredField));
        }

        private void llblRegistracija_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            var registracija = new frmRegistracija();
            registracija.Show();  
        }
    }
}
