using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DLWMS.WinApp.Predavanja
{
    public partial class frmNotifikacije : Form
    {
        const string crt = $"-----------------------------------";

        void PosaljiSMS(string sadrzaj)
        {
            //MessageBox.Show($"To: +38761111222 SMS -> {sadrzaj} ");
            DodajSadrzaj($"To: +38761111222 {Environment.NewLine} SMS -> {sadrzaj} ");
        }
        void PosaljiViber(string sadrzaj)
        {
            //MessageBox.Show($"To: +38761111222 Viber -> {sadrzaj} ");
            DodajSadrzaj($"To: +38761111222 {Environment.NewLine} Viber -> {sadrzaj} ");
        }
        void PosaljiEmail(string sadrzaj)
        {
            //MessageBox.Show($"From:info@fit.ba\nTo: admin@fit.ba\nEmail ->{sadrzaj} ");
            DodajSadrzaj($"From:info@fit.ba{Environment.NewLine}To: admin@fit.ba {Environment.NewLine} Email -> {sadrzaj} ");
        }

        private void DodajSadrzaj(string sadrzaj)
        {
            txtIspis.AppendText(Environment.NewLine + crt + Environment.NewLine);
            foreach (var znak in sadrzaj)
            {
                txtIspis.AppendText(znak.ToString());
                Task.Delay(30).Wait();
            }
        }

        delegate void Notifikacija(string poruka);
        event Notifikacija CudnaPrijavaNaSistem;

        public frmNotifikacije()
        {
            InitializeComponent();
        }

        private void btnPosalji_Click(object sender, EventArgs e)
        {
            CudnaPrijavaNaSistem?.Invoke(txtPoruka.Text);
            //CudnaPrijavaNaSistem(txtPoruka.Text);
        }

        private void cbSMS_CheckedChanged(object sender, EventArgs e)
        {
            PromijeniStatusPretplate(sender as CheckBox, PosaljiSMS);
        }

        private void PromijeniStatusPretplate(CheckBox checkBox, Notifikacija metoda)
        {
            if (checkBox.Checked)
                CudnaPrijavaNaSistem += metoda;
            else
                CudnaPrijavaNaSistem -= metoda;
        }

        private void cbViber_CheckedChanged(object sender, EventArgs e)
        {
            PromijeniStatusPretplate(sender as CheckBox, PosaljiViber);
        }

        private void cbEmail_CheckedChanged(object sender, EventArgs e)
        {
            PromijeniStatusPretplate(sender as CheckBox, PosaljiEmail);
        }

        int Test(int a, string b) { return 0; }
        bool DobreOcjene(int ocjena) { return ocjena >= 8; }        

        private void frmNotifikacije_Load(object sender, EventArgs e)
        {
            Func<int, string, int> func = Test;
            Func<int, bool> filter = DobreOcjene;  

            int[] ocjene = new int[] { 6, 6, 8, 10, 7, 7, 9 };
            var dobreOcjene1 = ocjene.Where(DobreOcjene);//8 10 9
            var dobreOcjene2 = ocjene.Where(filter);//8 10 9
            var dobreOcjene3 = ocjene.Where(ocjena => ocjena >= 8);//8 10 9
            var dobreOcjene4 = ocjene.Where(x => x >= 8);//8 10 9


        }
    }
}
