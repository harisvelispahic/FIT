namespace TinyGameStore_G1
{
    partial class frmUserGames
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
            lblSelect = new Label();
            cmbUsers = new ComboBox();
            dgvGames = new DataGridView();
            Id = new DataGridViewTextBoxColumn();
            GameName = new DataGridViewTextBoxColumn();
            Publisher = new DataGridViewTextBoxColumn();
            ReleaseDate = new DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)dgvGames).BeginInit();
            SuspendLayout();
            // 
            // lblSelect
            // 
            lblSelect.AutoSize = true;
            lblSelect.Location = new Point(12, 18);
            lblSelect.Name = "lblSelect";
            lblSelect.Size = new Size(66, 15);
            lblSelect.TabIndex = 0;
            lblSelect.Text = "Select user:";
            // 
            // cmbUsers
            // 
            cmbUsers.FormattingEnabled = true;
            cmbUsers.Location = new Point(84, 12);
            cmbUsers.Name = "cmbUsers";
            cmbUsers.Size = new Size(205, 23);
            cmbUsers.TabIndex = 1;
            cmbUsers.SelectedIndexChanged += cmbUsers_SelectedIndexChanged;
            // 
            // dgvGames
            // 
            dgvGames.AllowUserToAddRows = false;
            dgvGames.AllowUserToDeleteRows = false;
            dgvGames.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvGames.Columns.AddRange(new DataGridViewColumn[] { Id, GameName, Publisher, ReleaseDate });
            dgvGames.Location = new Point(12, 41);
            dgvGames.Name = "dgvGames";
            dgvGames.ReadOnly = true;
            dgvGames.RowTemplate.Height = 25;
            dgvGames.Size = new Size(639, 150);
            dgvGames.TabIndex = 2;
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
            // frmUserGames
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(663, 204);
            Controls.Add(dgvGames);
            Controls.Add(cmbUsers);
            Controls.Add(lblSelect);
            Name = "frmUserGames";
            Text = "frmUserGames";
            Load += frmUserGames_Load;
            ((System.ComponentModel.ISupportInitialize)dgvGames).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblSelect;
        private ComboBox cmbUsers;
        private DataGridView dgvGames;
        private DataGridViewTextBoxColumn Id;
        private DataGridViewTextBoxColumn GameName;
        private DataGridViewTextBoxColumn Publisher;
        private DataGridViewTextBoxColumn ReleaseDate;
    }
}