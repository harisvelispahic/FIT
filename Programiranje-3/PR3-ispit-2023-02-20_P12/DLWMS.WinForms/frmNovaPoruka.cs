using DLWMS.Data;
using DLWMS.WinForms.Helpers;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DLWMS.WinForms
{
    public partial class frmNovaPoruka : Form
    {
        public int StudentId { get; set; }
        DLWMSDbContext db = new DLWMSDbContext();
        public frmNovaPoruka(int studentId)
        {
            InitializeComponent();
            StudentId = studentId;
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            if (ofdSlika.ShowDialog() == DialogResult.OK) {
                pbSlika.Image = Image.FromFile(ofdSlika.FileName);
            }
            //ofdSlika.OpenFile();
        }

        private void frmNovaPoruka_Load(object sender, EventArgs e)
        {
            List<StudentiPredmeti> listStudentiPredmeti = db.StudentiPredmeti.
                Where(sp => sp.StudentId == StudentId)
                .Include(sp => sp.Predmet)
                .ToList();

            //string txt = "";
            //foreach (var item in listPredmeti) {
            //    txt += item.Predmet.Naziv + "\n";
            //}

            //MessageBox.Show(txt);

            List<Predmeti> listPredmeti = new List<Predmeti>();
            foreach (var item in listStudentiPredmeti) {
                listPredmeti.Add(item.Predmet);
            }

            cmbPredmeti.ValueMember = "Id";
            cmbPredmeti.DisplayMember = "Naziv";
            cmbPredmeti.DataSource = listPredmeti;
        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            int predmetId = int.Parse(cmbPredmeti.SelectedValue.ToString());
            DateTime validnost = dtpValidnost.Value;
            string sadrzaj = txtSadrzaj.Text;
            byte[] slika = ImageHelper.FromImageToByte(pbSlika.Image);

            StudentiPoruke novaStudentPoruka = new StudentiPoruke() {
                StudentId = StudentId,
                PredmetId = predmetId,
                Validnost = validnost,
                Sadrzaj = sadrzaj,
                Slika = slika
            };

            db.StudentiPoruke.Add(novaStudentPoruka);
            db.SaveChanges();

            DialogResult = DialogResult.OK;
            Close();
        }

        private void btnOdustani_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
