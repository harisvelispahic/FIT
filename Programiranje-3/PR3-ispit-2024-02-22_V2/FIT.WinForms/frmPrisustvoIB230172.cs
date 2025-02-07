using FIT.Data;
using FIT.WinForms.Helpers;
using Microsoft.CodeAnalysis.VisualBasic.Syntax;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FIT.WinForms
{
    public partial class frmPrisustvoIB230172 : Form
    {
        public int ProstorijaId { get; set; }
        public frmPrisustvoIB230172(int prostorijaId)
        {
            InitializeComponent();
            ProstorijaId = prostorijaId;
            dataGridView1.AutoGenerateColumns = false;
        }

        private void frmPrisustvoIB230172_Load(object sender, EventArgs e)
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);

            label1.Text = $"{prostorija.Naziv} - {prostorija.Oznaka}";
            comboBox1.UcitajPodatke(SharedContext.db.NastavaIB230172
                .Include(x => x.Prostorije)
                .Include(x => x.Predmet)
                .Where(x => x.ProstorijeId == ProstorijaId).ToList(), "Oznaka");

            comboBox2.UcitajPodatke(SharedContext.db.Studenti
                .ToList(), "StudentBrIndeksa");

            UcitajPodatke();
        }

        private void UcitajPodatke()
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);

            var listaPrisustva = SharedContext.db.PrisustvoIB230172
                .Include(x => x.Nastava)
                .ToList();
            dataGridView1.DataSource = null;
            dataGridView1.DataSource = listaPrisustva;

            lblKapacitet.Text = $"{listaPrisustva.Count}/{prostorija.Kapacitet}";
        }

        private void btnDodaj_Click(object sender, EventArgs e)
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);
            var listaPrisustva = SharedContext.db.PrisustvoIB230172.ToList();

            var nastava = comboBox1.SelectedItem as NastavaIB230172;
            var student = comboBox2.SelectedItem as Student;

            if (SharedContext.db.PrisustvoIB230172.Any(x => x.NastavaId == nastava.Id && x.StudentId == student.Id)) {
                MessageBox.Show("Student vec prijavljen na tu nastavu!");
                return;
            }
            if (listaPrisustva.Count >= prostorija.Kapacitet) {
                MessageBox.Show("Kapacitet je pun!");
                return;
            }


            var novo = new PrisustvoIB230172 {
                NastavaId = nastava.Id,
                StudentId = student.Id
            };

            SharedContext.db.PrisustvoIB230172.Add(novo);
            SharedContext.db.SaveChanges();

            UcitajPodatke();
        }

        private async void btnGenerisi_Click(object sender, EventArgs e)
        {
            var prostorija = SharedContext.db.ProstorijeIB230172.Find(ProstorijaId);
            //var listaPrisustva = SharedContext.db.PrisustvoIB230172.ToList();

            var nastava = comboBox1.SelectedItem as NastavaIB230172;
            var student = comboBox2.SelectedItem as Student;
            var broj = int.Parse(txtBrojZapisa.Text);

            for(int i = 0; i < broj; i++) {

                var novo = new PrisustvoIB230172 {
                    NastavaId = nastava.Id,
                    StudentId = student.Id,
                };

                SharedContext.db.PrisustvoIB230172.Add(novo);
                txtInfo.Text += $"{DateTime.Now:dd.MM HH:mm:ss} -> {student.StudentBrIndeksa} -> za {nastava.Oznaka}{Environment.NewLine}";
                txtInfo.SelectionLength = txtInfo.Text.Length;
                txtInfo.ScrollToCaret();

                await Task.Delay(300);
            }
            SharedContext.db.SaveChanges();
            UcitajPodatke();

            MessageBox.Show("Uspjesno dodana prisustva!");
        }
    }
}
