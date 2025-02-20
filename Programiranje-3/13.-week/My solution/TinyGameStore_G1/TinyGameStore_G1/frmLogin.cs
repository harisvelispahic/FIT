using TinyGameStore.Data;
using TinyGameStore.InMemory;

namespace TinyGameStore_G1
{
    public partial class frmLogin : Form
    {
        private InMemoryDb Db;
        private DataContext dbContext;

        public frmLogin()
        {
            InitializeComponent();
            Db = new InMemoryDb();
            dbContext = new DataContext();
        }

        private void btnSignIn_Click(object sender, EventArgs e)
        {
            //ManualConnection manualConnection = new ManualConnection();
            
            User user = new User()
            {
                UserName = txtUsername.Text,
                Password = mtxtPassword.Text
            };
            
            var existingUser = dbContext.Users.Where(x => x.UserName == user.UserName && x.Password == user.Password).FirstOrDefault();
            
            //var result = Db.Authenticate(user);
            if (existingUser != null)
            {
                var frm = new frmStore(existingUser);
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