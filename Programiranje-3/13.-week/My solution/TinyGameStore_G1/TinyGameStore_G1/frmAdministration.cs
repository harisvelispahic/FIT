using System.Configuration;
using TinyGameStore.Data;
using TinyGameStore.InMemory;

namespace TinyGameStore_G1
{
    public partial class frmAdministration : Form
    {
        InMemoryDb TinyStoreDb { get; set; }
        public frmAdministration()
        {
            InitializeComponent();
        }

        public frmAdministration(InMemoryDb db): this()
        {
            TinyStoreDb = db;
        }

        private void frmAdministration_Load(object sender, EventArgs e)
        {
            cmbUsers.DataSource = TinyStoreDb.GetAllUsers();
            cmbUsers.DisplayMember = "UserName";
            cmbUsers.ValueMember = "Id";
        }

        private void cmbUsers_SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedUser = (User)cmbUsers.SelectedItem;

            if(selectedUser != null)
            {
                var lstOwned = selectedUser.UsersGames.Select(x => x.Game).ToList();
                dgvOwnedGames.DataSource = null;
                dgvOwnedGames.DataSource = lstOwned;
            }
        }

        private void btnTestingConfig_Click(object sender, EventArgs e)
        {
            var appsettingsConfig = ConfigurationManager.AppSettings["AppName"];
            MessageBox.Show(appsettingsConfig);

            var connectionConfig = ConfigurationManager.ConnectionStrings[1];
            MessageBox.Show(connectionConfig.ConnectionString);
        }
    }
}
