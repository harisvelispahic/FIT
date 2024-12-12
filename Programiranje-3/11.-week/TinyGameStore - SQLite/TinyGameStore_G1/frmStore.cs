using Microsoft.Data.Sqlite;
using TinyGameStore.Data;
using TinyGameStore.InMemory;

namespace TinyGameStore_G1
{
    public partial class frmStore : Form
    {
        InMemoryDb TinyStoreDb { get; set; }
        User currentUser;
        public frmStore()
        {
            TinyStoreDb = new InMemoryDb();
            InitializeComponent();
        }

        public frmStore(User user) : this()
        {
            currentUser = user;
        }

        private void frmStore_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void frmStore_Load(object sender, EventArgs e)
        {
            lblUsername.Text = currentUser.UserName;
            dgvGamesList.DataSource = null;
            dgvGamesList.DataSource = TinyStoreDb.GetAllGames();
        }

        private void btnBuy_Click(object sender, EventArgs e)
        {
            var selectedGame = (Game)dgvGamesList.SelectedRows[0].DataBoundItem;

            currentUser.UsersGames.Add(new UsersGame()
            {
                Game = selectedGame,
                User = currentUser,
                PurchaseDate = DateTime.Now
            });
        }

        private void btnAdmin_Click(object sender, EventArgs e)
        {
            new frmAdministration(TinyStoreDb).Show();
        }

        private void btnInsertGame_Click(object sender, EventArgs e)
        {
            DataContext context = new DataContext();
            context.Games.Add(new Game() { Name = "Testing game insert", Price = 10.5m });
            context.SaveChanges();
        }
    }
}
