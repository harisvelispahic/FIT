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

        private void btnCreateTable_Click(object sender, EventArgs e)
        {
            var sqliteConnection = new ManualConnection();
            var connection = sqliteConnection.Connection;
            connection.Open();
            var query = "CREATE TABLE Games (Id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, Price REAL)";
            var command = new SqliteCommand(query, connection);
            command.ExecuteNonQuery();
            connection.Dispose();
        }

        // ova metoda za nas radi sve sto radi entity framework
        // course of action: open connection - do stuff - close connection
        // entity framework dobar za small to mid scale projects
        private void btnManualInsert_Click(object sender, EventArgs e)
        {

            const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

            // kada izadje iz ovog scopa, pozvati ce dispose na sqlite objekat
            // manuelno disposovanje

            using (var sqlite = new ManualConnection())
            {
                var connection = sqlite.Connection; ;
                connection.Open();

                for (int i = 0; i < 50; i++)
                {
                    var query = "INSERT INTO Games (Name, Price) VALUES (@Name, @Price)";
                    var command = new SqliteCommand(query, connection);

                    // random biramo 15 karaktera iz chars
                    command.Parameters.AddWithValue("@Name",
                        $"{new string(Enumerable.Repeat(chars, 15).Select(s => s[Random.Shared.Next(s.Length)]).ToArray())}");
                    command.Parameters.AddWithValue("@Price", Random.Shared.NextDouble());

                    command.ExecuteNonQuery();  // vraća integers koji će bit rows affected
                }
            }
        }

        private void btnManualUpdate_Click(object sender, EventArgs e)
        {
            using (var sqlite = new ManualConnection())
            {
                var connection = sqlite.Connection; ;
                connection.Open();

                var query = "UPDATE Games SET Name=@Name WHERE Id=@id";
                var command = new SqliteCommand(query, connection);
                command.Parameters.AddWithValue("@id", 2);
                command.Parameters.AddWithValue("@Name", "Dark souls");
                command.ExecuteNonQuery();
                // transakcija - sve ili ništa
                // ISTRAŽITI !!!
                //command.Transaction;
            }
        }

        private void btnManualDelete_Click(object sender, EventArgs e)
        {
            using (var sqlite = new ManualConnection())
            {
                var connection = sqlite.Connection; ;
                connection.Open();

                var query = "DELETE FROM Games WHERE Id=@id";
                var command = new SqliteCommand(query, connection);
                command.Parameters.AddWithValue("@id", 3);
                command.ExecuteNonQuery();

            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var listGames = new List<Game>();

            using (var sqlite = new ManualConnection())
            {
                var connection = sqlite.Connection; ;
                connection.Open();

                var query = "SELECT * FROM Games";
                var command = new SqliteCommand(query, connection);

                var reader = command.ExecuteReader();

                while (reader.Read())
                {
                    // ordinal - kolona u bazi podataka
                    // uzmi prvi kolonu - id, drugu - gameName i trecu price
                    var id = reader.GetInt32(0);
                    var gameName = reader.GetString(1);
                    var price = reader.GetDecimal(2);

                    var game = new Game()
                    {
                        Id = id,
                        Name = gameName,
                        Price = price
                    };

                    listGames.Add(game);

                    dgvSelectResult.DataSource = null;
                    dgvSelectResult.DataSource = listGames;
                }
            }
        }
    }
}
