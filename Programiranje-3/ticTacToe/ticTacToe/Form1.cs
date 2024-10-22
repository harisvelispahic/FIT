namespace ticTacToe
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public int Counter { get; set; }
        public int XCounter { get; set; }
        public int OCounter { get; set; }
        public int DrawCounter { get; set; }
        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void Input(object sender)
        {
            if (sender is Button btn) {
                if (btn.Text == "") {
                    btn.Text = Counter % 2 == 0 ? "X" : "O";

                    if (GameOver()) {
                        //MessageBox.Show("GAME OVER");
                        if (Counter % 2 == 0) {
                            XCounter++;
                            textBox1.Text = XCounter.ToString();
                        }
                        else {
                            OCounter++;
                            textBox2.Text = OCounter.ToString();
                        }
                        
                        foreach(Control control in this.Controls) {
                            if(control is Button bttn) {
                                bttn.Enabled = false;
                            }
                        }
                        button10.Enabled = true;
                        button10.Focus();
                    }

                    Counter++;
                }
            }
        }

        private bool GameOver()
        {
            var oldColor = button10.BackColor;
            var resultRows =
                CheckRows(button1, button2, button3) ||
                CheckRows(button4, button5, button6) ||
                CheckRows(button7, button8, button9);

            var resultColumns =
                CheckColumns(button1, button4, button7) ||
                CheckColumns(button2, button5, button8) ||
                CheckColumns(button3, button6, button9);

            var resultDiagonals =
                CheckDiagonals(button1, button5, button9) ||
                CheckDiagonals(button7, button5, button3);

            if (Counter == 8 && !resultRows && !resultColumns && !resultDiagonals) {
                DrawCounter++;
                textBox3.Text = DrawCounter.ToString();
                foreach (Control control in this.Controls) {
                    if (control is Button btn) {
                        btn.BackColor = Color.Gold;
                    }
                }
                button10.BackColor = oldColor;
            }

            return resultRows || resultColumns || resultDiagonals || (Counter == 8 && !resultRows && !resultColumns && !resultDiagonals);
        }

        private bool CheckRows(Button button1, Button button2, Button button3)
        {
            var result = button1.Text != "" && button1.Text == button2.Text &&
                button2.Text == button3.Text;
            if (result) {
                button1.BackColor = Color.ForestGreen;
                button2.BackColor = Color.ForestGreen;
                button3.BackColor = Color.ForestGreen;
            }
            return result;
        }

        private bool CheckColumns(Button button1, Button button2, Button button3)
        {
            var result = button1.Text != "" && button1.Text == button2.Text &&
                button2.Text == button3.Text;
            if (result) {
                button1.BackColor = Color.ForestGreen;
                button2.BackColor = Color.ForestGreen;
                button3.BackColor = Color.ForestGreen;
            }
            return result;
        }

        private bool CheckDiagonals(Button button1, Button button2, Button button3)
        {
            var result = button1.Text != "" && button1.Text == button2.Text &&
                button2.Text == button3.Text;
            if (result) {
                button1.BackColor = Color.ForestGreen;
                button2.BackColor = Color.ForestGreen;
                button3.BackColor = Color.ForestGreen;
            }
            return result;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            Input(sender);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            var oldColor = button10.BackColor;
            foreach (Control control in this.Controls) {
                if (control is Button btn) {
                    btn.Text = "";
                    btn.BackColor = oldColor;
                    btn.Enabled = true;
                }
            }
            Counter = 0;
            button10.Text = "Play again";
        }

    }
}
