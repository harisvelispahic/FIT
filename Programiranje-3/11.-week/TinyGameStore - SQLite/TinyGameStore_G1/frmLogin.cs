using TinyGameStore.Data;
using TinyGameStore.InMemory;

namespace TinyGameStore_G1
{
    public partial class frmLogin : Form
    {
        private InMemoryDb Db;

        public frmLogin()
        {
            InitializeComponent();
            Db = new InMemoryDb();
        }

        private void btnSignIn_Click(object sender, EventArgs e)
        {
            ManualConnection manualConnection = new ManualConnection();

            User user = new User()
            {
                UserName = txtUsername.Text,
                Password = mtxtPassword.Text
            };
            var result = Db.Authenticate(user);
            if (result.Item1)
            {
                var frm = new frmStore(result.Item2);
                frm.Show();

                this.Hide();
            }
            else
            {
                MessageBox.Show("User doesn't exist", 
                    "Tiny game store", 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Error);
            }
        }

        private void mtxtPassword_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                btnSignIn_Click(sender, e);
        }
    }
}