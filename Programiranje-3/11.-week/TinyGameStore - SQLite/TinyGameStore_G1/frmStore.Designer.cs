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
            dgvGamesList = new DataGridView();
            Id = new DataGridViewTextBoxColumn();
            GameName = new DataGridViewTextBoxColumn();
            Publisher = new DataGridViewTextBoxColumn();
            ReleaseDate = new DataGridViewTextBoxColumn();
            btnBuy = new Button();
            btnAdmin = new Button();
            btnInsertGame = new Button();
            ((System.ComponentModel.ISupportInitialize)dgvGamesList).BeginInit();
            SuspendLayout();
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.Location = new Point(12, 9);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(38, 15);
            lblUsername.TabIndex = 0;
            lblUsername.Text = "label1";
            // 
            // dgvGamesList
            // 
            dgvGamesList.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvGamesList.Columns.AddRange(new DataGridViewColumn[] { Id, GameName, Publisher, ReleaseDate });
            dgvGamesList.Location = new Point(12, 27);
            dgvGamesList.Name = "dgvGamesList";
            dgvGamesList.RowTemplate.Height = 25;
            dgvGamesList.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvGamesList.Size = new Size(776, 267);
            dgvGamesList.TabIndex = 1;
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
            // btnBuy
            // 
            btnBuy.Location = new Point(713, 300);
            btnBuy.Name = "btnBuy";
            btnBuy.Size = new Size(75, 23);
            btnBuy.TabIndex = 2;
            btnBuy.Text = "Buy";
            btnBuy.UseVisualStyleBackColor = true;
            btnBuy.Click += btnBuy_Click;
            // 
            // btnAdmin
            // 
            btnAdmin.Location = new Point(611, 300);
            btnAdmin.Name = "btnAdmin";
            btnAdmin.Size = new Size(75, 23);
            btnAdmin.TabIndex = 3;
            btnAdmin.Text = "Admin";
            btnAdmin.UseVisualStyleBackColor = true;
            btnAdmin.Click += btnAdmin_Click;
            // 
            // btnInsertGame
            // 
            btnInsertGame.Location = new Point(490, 300);
            btnInsertGame.Name = "btnInsertGame";
            btnInsertGame.Size = new Size(93, 23);
            btnInsertGame.TabIndex = 4;
            btnInsertGame.Text = "Insert game";
            btnInsertGame.UseVisualStyleBackColor = true;
            btnInsertGame.Click += btnInsertGame_Click;
            // 
            // frmStore
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 334);
            Controls.Add(btnInsertGame);
            Controls.Add(btnAdmin);
            Controls.Add(btnBuy);
            Controls.Add(dgvGamesList);
            Controls.Add(lblUsername);
            Name = "frmStore";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Tiny Game Store";
            FormClosed += frmStore_FormClosed;
            Load += frmStore_Load;
            ((System.ComponentModel.ISupportInitialize)dgvGamesList).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblUsername;
        private DataGridView dgvGamesList;
        private DataGridViewTextBoxColumn Id;
        private DataGridViewTextBoxColumn GameName;
        private DataGridViewTextBoxColumn Publisher;
        private DataGridViewTextBoxColumn ReleaseDate;
        private Button btnBuy;
        private Button btnAdmin;
        private Button btnInsertGame;
    }
}