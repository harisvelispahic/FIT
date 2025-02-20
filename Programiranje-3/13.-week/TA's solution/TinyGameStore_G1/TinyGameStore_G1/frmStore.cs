using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using TinyGameStore.Data;
using TinyGameStore.InMemory;
using TinyGameStore_G1.Extensions;

namespace TinyGameStore_G1
{
    public partial class frmStore : Form
    {
        User currentUser;
        DataContext dbContext;
        public frmStore()
        {
            dbContext = new DataContext();
            InitializeComponent();
        }

        public frmStore(User user): this()
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
            dgvGamesList.DataSource = dbContext.Games.ToList();
        }

        private void btnBuy_Click(object sender, EventArgs e)
        {
            var selectedGame = (Game)dgvGamesList.SelectedRows[0].DataBoundItem;
            var user = dbContext.Users.Where(u => u.Id == currentUser.Id).First();

            user.UsersGames.Add(new UsersGame()
            {
                Game = selectedGame,
                IsGifted = false,
                PurchaseDate = DateTime.Now
            });

            dbContext.SaveChanges();
        }

        private void btnAdmin_Click(object sender, EventArgs e)
        {
            new frmAdministration().Show();
        }

        private void btnRate_Click(object sender, EventArgs e)
        {
            var selectedRating = 0;
            //This will work because only one radio button will be checked
            //at any given point in time
            foreach(var control in grpRatings.Controls)
            {
                var rdRating = control as RadioButton;
                if (rdRating != null && rdRating.Checked)
                {
                    selectedRating = int.Parse(rdRating.Text);
                    break;
                }
            }
            var selectedGame = (Game)dgvGamesList.SelectedRows[0].DataBoundItem;
            var userGame = dbContext.UsersGames
                .FirstOrDefault(x => x.GameId == selectedGame.Id && x.UserId == currentUser.Id);
            
            userGame?.GameRatings.Add(new GameRating() { Rating = selectedRating });
            dbContext.SaveChanges();
        }

        private void pbCoverArt_DoubleClick(object sender, EventArgs e)
        {
            var openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image files|*.png;*.jpg;";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                pbCoverArt.Image = new Bitmap(openFileDialog.FileName);
            }
        }

        private void btnUpdateCoverArt_Click(object sender, EventArgs e)
        {
            var selectedGame = (Game)dgvGamesList.SelectedRows[0].DataBoundItem;
            selectedGame.CoverArt = pbCoverArt.Image.ToByteArray();

            dbContext.Update(selectedGame);
            dbContext.SaveChanges();
        }
    }
}
