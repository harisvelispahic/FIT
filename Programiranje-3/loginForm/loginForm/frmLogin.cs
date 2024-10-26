namespace loginForm
{
    public partial class frmLogin : Form
    {
        private frmGlavna frmGlavna;
        public frmLogin(frmGlavna frmGlavna)
        {
            InitializeComponent();
            this.FormClosing += frmLogin_FormClosing;
            this.frmGlavna = frmGlavna;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        public class User
        {
            public int Id { get; set; }
            public string firstName { get; set; }
            public string lastName { get; set; }
            public string Username { get; set; }
            public string Password { get; set; }
            public bool IsActive { get; set; }
        }

        public static class InternalDB
        {
            public static List<User> users = new List<User>() {
                new User(){ Id = 0, firstName = "Haris", lastName = "Velispahic", Username = "haris123", Password = "12345678", IsActive = true },
                new User(){ Id = 1, firstName = "Edin", lastName = "Dzeko", Username = "edinedin", Password = "edindzeko", IsActive = false}
            };
        }



        private void btnClose_Click(object sender, EventArgs e)
        {
            //Close();
            Application.Exit();
        }

        private void frmLogin_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Check if the close reason is due to the user trying to close the form (Alt+F4)
            if (e.CloseReason == CloseReason.UserClosing) {
                // Exit the application to ensure all forms are closed
                Application.Exit();
            }
        }



        private void btnLogin_Click(object sender, EventArgs e)
        {
            bool found = false;
            foreach (var user in InternalDB.users) {
                if (!isAuthValid(txtUsername.Text)) {
                    errorUsername.SetError(txtUsername, "You must fill out this field.");
                    if (!isAuthValid(txtPassword.Text)) {
                        errorPassword.SetError(txtPassword, "You must fill out this field.");
                    }
                    else {
                        errorPassword.Clear();
                    }
                    return;
                }
                else {
                    errorUsername.Clear();
                }

                if (!isAuthValid(txtPassword.Text)) {
                    errorPassword.SetError(txtPassword, "You must fill out this field.");
                    return;
                }
                else {
                    errorPassword.Clear();
                }


                if (user.Username == txtUsername.Text && user.Password == txtPassword.Text) {
                    found = true;
                    if (!user.IsActive) {
                        MessageBox.Show("This user does not have an active account.");
                        return;
                    }
                    //MessageBox.Show("SUCCESS!");
                    //frmGlavna frmGlavna = new frmGlavna();
                    //frmGlavna.ShowDialog();
                    this.DialogResult = DialogResult.OK;
                    this.frmGlavna.Show();
                    this.Hide();
                    return;
                }

            }

            if (!found) {
                MessageBox.Show("Username or password is incorrect!");
            }
        }

        private bool isAuthValid(string text)
        {
            return !string.IsNullOrEmpty(text);
        }


        private void btnMinimize_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void txtUsername_TextChanged(object sender, EventArgs e)
        {
            errorUsername.Clear();
        }

        private void txtPassword_TextChanged(object sender, EventArgs e)
        {
            errorPassword.Clear();
        }
    }
}
