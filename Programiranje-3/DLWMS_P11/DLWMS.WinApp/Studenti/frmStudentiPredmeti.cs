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
    public partial class frmStudentiPredmeti : Form
    {
        DLWMSContext db = new();
        private Student student;

        public frmStudentiPredmeti(Student odabraniStudent)
        {
            InitializeComponent();
            dgvPolozeni.AutoGenerateColumns = false;
            this.student = odabraniStudent;
        }

        private void frmStudentiPredmeti_Load(object sender, EventArgs e)
        {
            UcitajPolozenePredmete();
            UcitajPodatkeOStudentu();
            UcitajPredmete();
        }

        private void UcitajPodatkeOStudentu()
        {
            //pbSlika.Image = student.Slika;
            lblImePrezime.Text = student.Ime + " " + student.Prezime;
            lblIndeks.Text = student.BrojIndeksa;
        }

        private void UcitajPredmete()
        {
            //cmbPredmeti.UcitajPodatke(InMemoryDB.Predmeti);
            cmbPredmeti.UcitajPodatke(db.Predmeti.ToList());
        }

        private void UcitajPolozenePredmete()
        {
            dgvPolozeni.DataSource = null;
            //dgvPolozeni.DataSource = student.Polozeni;
            //dgvPolozeni.DataSource = db.PolozeniPredmeti.ToList();
            dgvPolozeni.DataSource = db.PolozeniPredmeti.Where(x => x.StudentId == student.Id).ToList();

        }

        private void btnDodaj_Click(object sender, EventArgs e)
        {
            if (ValidanUnos())
            {

                var predmet = cmbPredmeti.SelectedItem as Predmet;
                var polozeni = new PolozeniPredmet
                {
                    //Id = student.Polozeni.Count + 1,
                    StudentId = student.Id,
                    //Student = student,
                    PredmetId = predmet.Id,
                    //Predmet = predmet,
                    Ocjena = int.Parse(cmbOcjene.Text),
                    DatumPolaganja = dtpDatumPolaganja.Value,
                    Napomena = txtNapomena.Text
                };
                //student.Polozeni.Add(polozeni);
                db.PolozeniPredmeti.Add(polozeni);
                db.SaveChanges();
                UcitajPolozenePredmete();
            }
        }
        private bool ValidanUnos()
        {
            return
            Validator.ProvjeriUnos(cmbPredmeti, err, Resursi.Get(Kljucevi.RequiredField)) &&
                    Validator.ProvjeriUnos(cmbOcjene, err, Resursi.Get(Kljucevi.RequiredField));
        }
    }
}
