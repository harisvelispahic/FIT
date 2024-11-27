namespace PR3_G1_2024_Windows_Concepts
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private int Id;
        private void button1_Click(object sender, EventArgs e)
        {
            ++Id;
            var btn = new Button();
            btn.Name = Id.ToString();
            btn.Text = Id.ToString();

            btn.Location = new Point(Random.Shared.Next(this.Width - 30), Random.Shared.Next(this.Height - 10));
            btn.Click += GeneratedButtonClick;      // function pointer
            this.Controls.Add(btn);
        }

        private void GeneratedButtonClick(object sender, EventArgs e)
        {
            MessageBox.Show($"Clicked on: { ((Button)sender).Text}");
        }
    }
}