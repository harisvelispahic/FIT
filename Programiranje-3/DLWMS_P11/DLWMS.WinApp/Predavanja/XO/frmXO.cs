using DLWMS.Data;
using DLWMS.Infrastructure;

namespace DLWMS.WinApp
{
    public partial class frmXO : Form
    {
        public int Brojac { get; set; }
        public string Igrac1 { get; set; }
        public string Igrac2 { get; set; }
        public frmXO()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InicijalizujNovuIgru();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void RegistrujPotez(object sender)
        {
            if (sender is Button button && button.Text == "")
            {
                button.Text = Brojac % 2 == 0 ? "X" : "O";
                Text = Brojac % 2 == 0 ? Igrac1 : Igrac2;

                if (KrajIgre())
                {
                    new frmPobjeda().ShowDialog();
                    PromijeniStatusDugmica(false);
                }

                Brojac++;
            }
        }

        private void PromijeniStatusDugmica(bool aktivan, bool tekst = false, bool pozadina = false)
        {
            foreach (var kontrola in Controls)
            {
                if (kontrola is Button dugmic)
                {
                    dugmic.Enabled = aktivan;
                    if (tekst)
                        dugmic.Text = "";
                    if (pozadina)
                        dugmic.UseVisualStyleBackColor = true;
                }
            }
        }

        private bool KrajIgre()
        {
            return ProvjeriRedove() || ProvjeriKolone() || ProvjeriDijagonale();
        }

        private bool ProvjeriDijagonale()
        {
            return ProvjeriPobjedu(button1, button5, button9) ||
                    ProvjeriPobjedu(button3, button5, button7);
        }

        private bool ProvjeriKolone()
        {
            return ProvjeriPobjedu(button1, button4, button7) ||
                    ProvjeriPobjedu(button2, button5, button8) ||
                    ProvjeriPobjedu(button3, button6, button9);
        }

        private bool ProvjeriRedove()
        {
            return ProvjeriPobjedu(button1, button2, button3) ||
                   ProvjeriPobjedu(button4, button5, button6) ||
                   ProvjeriPobjedu(button7, button8, button9);
        }

        private bool ProvjeriPobjedu(Button button1, Button button2, Button button3)
        {
            var pobjeda = button1.Text != "" && button1.Text == button2.Text && button2.Text == button3.Text;
            if (pobjeda)
                button1.BackColor = button2.BackColor = button3.BackColor = Color.Green;
            return pobjeda;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            RegistrujPotez(sender);
        }

        private void novaIgraToolStripMenuItem_Click(object sender, EventArgs e)
        {
            InicijalizujNovuIgru();
        }

        private void InicijalizujNovuIgru()
        {
            Brojac = 0;
            PromijeniStatusDugmica(true, true, true);
            var igraci = new frmIgraci();
            igraci.ShowDialog();

            Igrac1 = igraci.Igrac1;
            Igrac2 = igraci.Igrac2;

        }

 
    }
}
