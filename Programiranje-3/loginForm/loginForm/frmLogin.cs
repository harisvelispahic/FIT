using Data;

namespace loginForm
{
    public partial class frmLogin : Form
    {
        public frmLogin()
        {
            InitializeComponent();
            InternalDB.LoadUsers();
            this.AcceptButton = btnLogin; // Sets Enter to trigger btnLogin
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
            foreach (var user in Data.InternalDB.users) {
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
                    
                    frmGlavna frmGlavna = new frmGlavna(txtUsername.Text);
                    frmGlavna.Show();
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

        private void btnSignUp_Click(object sender, EventArgs e)
        {
            frmSignUp frmSignUp = new frmSignUp();
            frmSignUp.ShowDialog();
        }
    }
}