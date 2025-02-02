using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using System.Collections.ObjectModel;
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
            InitializeComponent();
            dbContext = new DataContext();
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
            dgvGamesList.DataSource = dbContext.Games.ToList();
            LoadRatings();
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
            foreach (var control in grpRatings.Controls)
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

        private void dgvGamesList_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            //MessageBox.Show("test");
            var selectedRow = dgvGamesList.Rows[e.RowIndex].DataBoundItem;
            //MessageBox.Show(selectedRow.Cells["Id"].Value.ToString());

            var frm = new frmRating((Game)selectedRow, currentUser).ShowDialog();
            if (frm == DialogResult.OK)
            {
                LoadRatings();
            }

        }

        public void LoadRatings()
        {
            int i = 0;
            foreach (var item in dgvGamesList.Rows)
            {
                //Game game = (Game)item;
                Game game = (Game)dgvGamesList.Rows[i].DataBoundItem;
                var usersGames = dbContext.UsersGames.Where(obj => obj.GameId == game.Id).ToList();

                int sum = 0;
                int counter = 0;
                double ratings = 0;
                foreach (var userGame in usersGames)
                {
                    var lstRatings = dbContext.GameRatings.Where(obj => obj.UserGamesId == userGame.Id).ToList();
                    if (lstRatings.Count == 0)
                        continue;

                    ratings = lstRatings.Average(x => x.Rating);
                    //foreach(var rating in ratings)
                    //{
                    //    sum += rating.Rating;
                    //    counter++;
                    //}
                    dgvGamesList.Rows[i].Cells["averageRating"].Value = ratings;
                }
                i++;
                if (counter == 0)
                    continue;

                //dgvGamesList.SelectedRows[i++].Cells["averageRating"].Value = sum / counter;
                counter = 0;
                sum = 0;
            }
        }

        private async void btnGenerate_Click(object sender, EventArgs e)
        {
            //for (int i = 0; i < 5; i++)
            //{
            //    MessageBox.Show("Test");
            //    Thread.Sleep(1000);
            //}
            int numberOfGames = 0;
            if (txtNumberOfGames.Text != "")
            {
                numberOfGames = int.Parse(txtNumberOfGames.Text);

            }
            //MessageBox.Show(numberOfGames.ToString());
            for (int i = 0; i < numberOfGames; i++)
            {
                await Task.Run(() =>
                {
                    // invoke omogucava da skocimo sa trenutnog threada, na main thread -> tako da mozemo pristupiti kontroli kojoj inace ne mozemo, jer thread ne posjeduje tu kontrolu
                    Invoke(() =>
                    {
                        rtbGame.Text += dtpGame.Value + " ->\n";
                    });
                    Thread.Sleep(500);
                });

                var Game = new Game()
                {
                    Name = $"Game {i}",
                    Publisher = $"Publisher {i}",
                    ReleaseDate = dtpGame.Value,
                    Price = 60
                };

                dbContext.Games.Add(Game);
                dbContext.SaveChanges();

                dgvGamesList.DataSource = null;
                dgvGamesList.DataSource = dbContext.Games.ToList();

                //rtbGame.Text += dtpGame.Value + " ->\n";
                //await Task.Delay(500);
            }
        }
    }


    
}
