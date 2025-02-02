using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TinyGameStore.Data;

namespace TinyGameStore_G1
{
    public partial class frmRating : Form
    {
        public Game Game { get; set; }
        public User currentUser { get; set; }
        DataContext dbContext = new DataContext();
        public frmRating(Game Game, User User)
        {
            InitializeComponent();
            this.Game = Game;
            currentUser = User;
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
            var userGame = dbContext.UsersGames
                .FirstOrDefault(x => x.GameId == Game.Id && x.UserId == currentUser.Id);

            userGame?.GameRatings.Add(new GameRating() { Rating = selectedRating });
            dbContext.SaveChanges();

            this.DialogResult = DialogResult.OK;
            Close();
        }
    }
}
