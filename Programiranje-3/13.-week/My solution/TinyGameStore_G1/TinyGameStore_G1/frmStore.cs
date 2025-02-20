using Microsoft.Data.Sqlite;
using TinyGameStore.Data;
using TinyGameStore.InMemory;
using TinyGameStore_G1.Extensions;

namespace TinyGameStore_G1
{
    public partial class frmStore : Form
    {
        DataContext dbContext;
        User currentUser;
        public frmStore()
        {
            InitializeComponent();
        }

        public frmStore(User user) : this()
        {
            currentUser = user;
            dbContext = new DataContext();
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
            // Get user from DB
            // Create UsersGame object
            // Fill in UsersGame object

            var selectedGame = (Game)dgvGamesList.SelectedRows[0].DataBoundItem;

            foreach (var item in dbContext.UsersGames)
            {
                if (item.GameId == selectedGame.Id)
                {
                    MessageBox.Show("Game has already been purchased!");
                    return;
                }
            }

            MessageBox.Show($"You've succesfully purchased the game: {selectedGame.Name}");

            var UsersGame = new UsersGame()
            {
                GameId = selectedGame.Id,
                UserId = currentUser.Id,
                IsGifted = false,
                PurchaseDate = DateTime.Now
            };

            dbContext.UsersGames.Add(UsersGame);
            dbContext.SaveChanges();

            // Njihov nacin
            //var user = dbContext.Users.Where(u => u.Id == currentUser.Id).First();
            //user.UsersGames.Add(new UsersGame()
            //{
            //    Game = selectedGame,
            //    IsGifted = false,
            //    PurchaseDate = DateTime.Now
            //});
        }

        private void btnAdmin_Click(object sender, EventArgs e)
        {
            //new frmAdministration(TinyStoreDb).Show();
        }

        private void btnInserGame_Click(object sender, EventArgs e)
        {

            //context.Games.Add(new Game() { Name = "Testing game insert", Price = 10.5m });
            //for(int i = 0; i < TinyStoreDb.GetAllGames().Count; i++)
            //{
            //    var igra = TinyStoreDb.GetAllGames()[i];
            //    context.Games.Add(new Game()
            //    {
            //        Id = igra.Id,
            //        Name = igra.Name,
            //        Publisher = igra.Publisher,
            //        ReleaseDate = igra.ReleaseDate,
            //        Price = 15
            //    });
            //}
            dbContext.SaveChanges();
        }

        private void btnRate_Click(object sender, EventArgs e)
        {
            var selectedGame = (Game)dgvGamesList.SelectedRows[0].DataBoundItem;

            int rating = 0;
            // This will work because only one radio button will be checked at any given point in time
            foreach (var item in gbRating.Controls)
            {
                if (item is RadioButton rButton)
                {
                    if (rButton.Checked)
                    {
                        rating = int.Parse(rButton.Text);
                        break;
                    }
                }
            }
            var userGames = (dbContext.UsersGames.
                FirstOrDefault(x => x.GameId == selectedGame.Id && x.UserId == currentUser.Id) as UsersGame);

            //dbContext.GameRatings.Add(new GameRating()
            //{
            //    UserGamesId = userGames,
            //    Rating = rating
            //});
            //dbContext.SaveChanges();

            if (userGames != null)
            {
                userGames.GameRatings.Add(new GameRating()
                {
                    //UserGamesId = userGames.Id,
                    Rating = rating
                });
                dbContext.SaveChanges();
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            var openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image files|*.png;*.jpg;";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                pbCoverArt.Image = new Bitmap(openFileDialog.FileName);
            }
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            if (pbCoverArt.Image == null) {
                err.SetError(pbCoverArt, "Morate odabrati sliku!");
                return;
            }
            //var selectedGame = (Game)dgvGamesList.SelectedRows[0].DataBoundItem;
            ////selectedGame.CoverArt = pbCoverArt.Image.ToByteArray();

            ////dbContext.Update()
            var selectedGame = (Game)dgvGamesList.SelectedRows[0].DataBoundItem;
            selectedGame.CoverArt = pbCoverArt.Image.ToByteArray();

            dbContext.Update(selectedGame);
            dbContext.SaveChanges();

            // refresh data source
            dgvGamesList.DataSource = null;
            dgvGamesList.DataSource = dbContext.Games.ToList();
        }
    }
}
