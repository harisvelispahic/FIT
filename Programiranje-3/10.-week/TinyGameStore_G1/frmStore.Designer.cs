namespace TinyGameStore_G1
{
    partial class frmStore
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            lblUsername = new Label();
            dgvGames = new DataGridView();
            Id = new DataGridViewTextBoxColumn();
            GameName = new DataGridViewTextBoxColumn();
            Publisher = new DataGridViewTextBoxColumn();
            ReleaseDate = new DataGridViewTextBoxColumn();
            btnBuyGame = new Button();
            btnViewGames = new Button();
            ((System.ComponentModel.ISupportInitialize)dgvGames).BeginInit();
            SuspendLayout();
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.Location = new Point(12, 9);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(63, 15);
            lblUsername.TabIndex = 0;
            lblUsername.Text = "Welcome, ";
            // 
            // dgvGames
            // 
            dgvGames.AllowUserToAddRows = false;
            dgvGames.AllowUserToDeleteRows = false;
            dgvGames.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvGames.Columns.AddRange(new DataGridViewColumn[] { Id, GameName, Publisher, ReleaseDate });
            dgvGames.Location = new Point(8, 47);
            dgvGames.Name = "dgvGames";
            dgvGames.ReadOnly = true;
            dgvGames.RowTemplate.Height = 25;
            dgvGames.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvGames.Size = new Size(709, 150);
            dgvGames.TabIndex = 1;
            dgvGames.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Id
            // 
            Id.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Id.DataPropertyName = "Id";
            Id.HeaderText = "Id";
            Id.Name = "Id";
            Id.ReadOnly = true;
            // 
            // GameName
            // 
            GameName.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            GameName.DataPropertyName = "Name";
            GameName.HeaderText = "Name";
            GameName.Name = "GameName";
            GameName.ReadOnly = true;
            // 
            // Publisher
            // 
            Publisher.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Publisher.DataPropertyName = "Publisher";
            Publisher.HeaderText = "Publisher";
            Publisher.Name = "Publisher";
            Publisher.ReadOnly = true;
            // 
            // ReleaseDate
            // 
            ReleaseDate.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            ReleaseDate.DataPropertyName = "ReleaseDate";
            ReleaseDate.HeaderText = "Release Date";
            ReleaseDate.Name = "ReleaseDate";
            ReleaseDate.ReadOnly = true;
            // 
            // btnBuyGame
            // 
            btnBuyGame.Location = new Point(604, 208);
            btnBuyGame.Name = "btnBuyGame";
            btnBuyGame.Size = new Size(107, 23);
            btnBuyGame.TabIndex = 2;
            btnBuyGame.Text = "Buy Game";
            btnBuyGame.UseVisualStyleBackColor = true;
            btnBuyGame.Click += btnBuyGame_Click;
            // 
            // btnViewGames
            // 
            btnViewGames.Location = new Point(8, 208);
            btnViewGames.Name = "btnViewGames";
            btnViewGames.Size = new Size(97, 23);
            btnViewGames.TabIndex = 3;
            btnViewGames.Text = "View games";
            btnViewGames.UseVisualStyleBackColor = true;
            btnViewGames.Click += btnViewGames_Click;
            // 
            // frmStore
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(723, 243);
            Controls.Add(btnViewGames);
            Controls.Add(btnBuyGame);
            Controls.Add(dgvGames);
            Controls.Add(lblUsername);
            Name = "frmStore";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Tiny Game Store";
            FormClosed += frmStore_FormClosed;
            Load += frmStore_Load;
            ((System.ComponentModel.ISupportInitialize)dgvGames).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblUsername;
        private DataGridView dgvGames;
        private DataGridViewTextBoxColumn Id;
        private DataGridViewTextBoxColumn GameName;
        private DataGridViewTextBoxColumn Publisher;
        private DataGridViewTextBoxColumn ReleaseDate;
        private Button btnBuyGame;
        private Button btnViewGames;
    }
}