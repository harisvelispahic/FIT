using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TinyGameStore.InMemory;
using TinyGameStore.Data;

namespace TinyGameStore_G1
{
    public partial class frmStore : Form
    {
        InMemoryDb TinyStoredDb = new InMemoryDb();
        User User = new User();
        public frmStore(User user)
        {
            InitializeComponent();
            dgvGames.AutoGenerateColumns = false;
            lblUsername.Text = "Welcome, " + user.UserName;
        }

        private void frmStore_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void frmStore_Load(object sender, EventArgs e)
        {
            dgvGames.DataSource = null;
            dgvGames.DataSource = TinyStoredDb.GetGames();
        }

        private void btnBuyGame_Click(object sender, EventArgs e)
        {
            var game = (Game)dgvGames.SelectedRows[0].DataBoundItem;
            //MessageBox.Show(game.Name);

            UsersGame usersGame = new UsersGame()
            {
                Id = 0,
                GameId = game.Id,
                UserId = User.Id,
                PurchaseDate = DateTime.Now,
                Game = game,
            };

            User currentUser = TinyStoredDb.GetUsers().Where(x => x.Id == usersGame.UserId).ToList()[0];
            //currentUser.UsersGames.Add(usersGame);
            User.UsersGames.Add(usersGame);

            Game currentGame = TinyStoredDb.GetGames().Where(x => x.Id == usersGame.GameId).ToList()[0];
            currentGame.UsersGames.Add(usersGame);

            string gamesText = "";
            for (int i = 0; i < User.UsersGames.Count; i++)
            {
                gamesText += User.UsersGames[i].Game.Name + "\n";
            }
            MessageBox.Show($"Users games: \n{gamesText}");
        }

        private void btnViewGames_Click(object sender, EventArgs e)
        {
            var usersGames = new frmUserGames();
            usersGames.ShowDialog();
        }
    }
}
