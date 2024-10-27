namespace Calculator
{
    public partial class frmCalculator : Form
    {
        public List<int>? Operands { get; set; }
        public List<char>? Operators { get; set; }

        public frmCalculator()
        {
            InitializeComponent();
            foreach (var control in this.Controls) {
                if (control is Button btn) {
                    //btn.FlatStyle = FlatStyle.Flat;
                    btn.UseVisualStyleBackColor = false;
                }
            }

            Operands = new List<int>();
            Operators = new List<char>();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            //string currentNumber = "";
            //for (int i = 0; i < textBox1.Text.Length; i++) 
            //{
            //    char currentChar = textBox1.Text[i];
            //    if (currentChar == '+' || currentChar == '-' || currentChar == '/' || currentChar == '*')  
            //    {
            //        Operators.Add(currentChar);
            //    }
            //    else {
            //        int position = i;
            //        while (int.TryParse(textBox1.Text[i], out int result)) {

            //        }
            //    }
            //}
        }

        private void getOperandsAndOperators()
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Text += 1.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text += 2.ToString();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            textBox1.Text += 3.ToString();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            textBox1.Text += 4.ToString();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            textBox1.Text += 5.ToString();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            textBox1.Text += 6.ToString();

        }

        private void button7_Click(object sender, EventArgs e)
        {
            textBox1.Text += 7.ToString();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            textBox1.Text += 8.ToString();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            textBox1.Text += 9.ToString();
        }

        private void appendOperator(char newOperator)
        {
            if (textBox1.Text.Length == 0) {
                return;
            }
            if (textBox1.Text.Length > 0) {
                var lastChar = textBox1.Text[textBox1.Text.Length - 1];
                if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/') {
                    textBox1.Text = textBox1.Text.Substring(0, textBox1.Text.Length - 1);
                }
            }
            textBox1.Text += newOperator;
        }
        private void button17_Click(object sender, EventArgs e)
        {
            appendOperator('+');
        }


        private void button16_Click(object sender, EventArgs e)
        {
            appendOperator('-');
        }

        private void button15_Click(object sender, EventArgs e)
        {
            appendOperator('*');
        }

        private void button14_Click(object sender, EventArgs e)
        {
            appendOperator('/');
        }

        private void button13_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Length == 0)
                return;
            textBox1.Text = textBox1.Text.Substring(0, textBox1.Text.Length - 1);
        }

        private void button12_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }

        private void button18_Click(object sender, EventArgs e)
        {
            //if (textBox1.Text.Length == 0) {
            //    return;
            //}
            textBox1.Text += 0.ToString();
        }
    }
}