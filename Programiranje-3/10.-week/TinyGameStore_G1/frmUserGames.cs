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
    public partial class frmUserGames : Form
    {
        InMemoryDb TinyStoreDb = new InMemoryDb();
        User selectedUser = new User();
        public frmUserGames()
        {
            InitializeComponent();
            dgvGames.AutoGenerateColumns = false;
        }

        private void frmUserGames_Load(object sender, EventArgs e)
        {
            cmbUsers.DataSource = null;
            cmbUsers.DataSource = TinyStoreDb.GetUsers();
            cmbUsers.ValueMember = "UserName";  // istraziti ovo
            cmbUsers.DisplayMember = "UserName";
        }

        private void cmbUsers_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectedUser = (User)cmbUsers.SelectedItem;

            // uglavnom ovdje treba nekako medjutabelu prikazat pretpostavljam

            if (selectedUser != null)
            {
                var listGames = selectedUser.UsersGames.Select(x => x.Game).ToList();
                dgvGames.DataSource = null;
                dgvGames.DataSource = listGames;
            }

            
            // IMPORTANT
            // Uglavnom ovo neće nikad raditi jer ne referenciramo iste objekte, jer svaki put pravimo nove instance, a to "ne kažemo" InMemoryDb
            // Potencijalno rješenje je da InMemoryDb bude statički, te da nakon svakog dodavanja pronađemo odgovarajućeg Korisnika/Igru u InMemoryDb i nad tom instancom u bazu vršimo promjene što će osigurati da uvijek radimo sa istim objektom
            // To pronalaženje možemo možda uraditi pomoću Id-a ili UserName-a što je neka primitivna verzija upita/query-a
            // Zbog ovog je očigledno zašto se pojavljuje potreba za BAZOM PODATAKA !!!!!!!!!!
        }
    }
}
