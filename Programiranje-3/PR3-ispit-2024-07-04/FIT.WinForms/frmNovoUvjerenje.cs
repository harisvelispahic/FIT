using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using FIT.Data;
using FIT.Infrastructure;
using FIT.WinForms.Helpers;
using Microsoft.Reporting.WinForms.Internal.Soap.ReportingServices2005.Execution;

namespace FIT.WinForms
{
    public partial class frmNovoUvjerenje : Form
    {
        DLWMSDbContext db;
        public int StudentId { get; set; }
        public frmNovoUvjerenje(int studentId)
        {
            InitializeComponent();
            db = new();
            StudentId = studentId;
        }

        private void btnSacuvaj_Click(object sender, EventArgs e)
        {
            if (Validiraj()) {
                //MessageBox.Show("Test");
                var uvjerenje = new StudentiUvjerenja {
                    StudentId = this.StudentId,
                    VrijemeKreiranja = DateTime.Now,
                    Vrsta = cmbVrstaUvjerenja.Text,
                    Svrha = txtSvrhaIzdavanja.Text,
                    Uplatnica = pbUplatnica.Image.ToByteArray(),
                    Printano = false
                };

                db.StudentiUvjerenja.Add(uvjerenje);
                db.SaveChanges();

                DialogResult = DialogResult.OK;
                Close();
            }
        }

        private bool Validiraj()
        {
            return Validator.ProvjeriUnos(cmbVrstaUvjerenja, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(txtSvrhaIzdavanja, err, Kljucevi.ReqiredValue) &&
                Validator.ProvjeriUnos(pbUplatnica, err, Kljucevi.ReqiredValue);
        }

        private void pbUplatnica_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK) {

                pbUplatnica.Image = Image.FromFile(openFileDialog1.FileName);
            }
        }

        private void cmbVrstaUvjerenja_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
