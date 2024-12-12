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
            btnCreateTable = new Button();
            btnManualInsert = new Button();
            btnManualUpdate = new Button();
            btnManualDelete = new Button();
            btnSelectAll = new Button();
            dgvSelectResult = new DataGridView();
            ((System.ComponentModel.ISupportInitialize)dgvGamesList).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dgvSelectResult).BeginInit();
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
            btnAdmin.Location = new Point(556, 300);
            btnAdmin.Name = "btnAdmin";
            btnAdmin.Size = new Size(75, 23);
            btnAdmin.TabIndex = 3;
            btnAdmin.Text = "Admin";
            btnAdmin.UseVisualStyleBackColor = true;
            btnAdmin.Click += btnAdmin_Click;
            // 
            // btnCreateTable
            // 
            btnCreateTable.Location = new Point(12, 371);
            btnCreateTable.Name = "btnCreateTable";
            btnCreateTable.Size = new Size(99, 23);
            btnCreateTable.TabIndex = 4;
            btnCreateTable.Text = "CreateTable";
            btnCreateTable.UseVisualStyleBackColor = true;
            btnCreateTable.Click += btnCreateTable_Click;
            // 
            // btnManualInsert
            // 
            btnManualInsert.Location = new Point(12, 413);
            btnManualInsert.Name = "btnManualInsert";
            btnManualInsert.Size = new Size(99, 23);
            btnManualInsert.TabIndex = 5;
            btnManualInsert.Text = "Manual insert";
            btnManualInsert.UseVisualStyleBackColor = true;
            btnManualInsert.Click += btnManualInsert_Click;
            // 
            // btnManualUpdate
            // 
            btnManualUpdate.Location = new Point(12, 442);
            btnManualUpdate.Name = "btnManualUpdate";
            btnManualUpdate.Size = new Size(99, 23);
            btnManualUpdate.TabIndex = 6;
            btnManualUpdate.Text = "Manual update";
            btnManualUpdate.UseVisualStyleBackColor = true;
            btnManualUpdate.Click += btnManualUpdate_Click;
            // 
            // btnManualDelete
            // 
            btnManualDelete.Location = new Point(12, 471);
            btnManualDelete.Name = "btnManualDelete";
            btnManualDelete.Size = new Size(99, 24);
            btnManualDelete.TabIndex = 7;
            btnManualDelete.Text = "Manual delete";
            btnManualDelete.UseVisualStyleBackColor = true;
            btnManualDelete.Click += btnManualDelete_Click;
            // 
            // btnSelectAll
            // 
            btnSelectAll.Location = new Point(12, 501);
            btnSelectAll.Name = "btnSelectAll";
            btnSelectAll.Size = new Size(99, 23);
            btnSelectAll.TabIndex = 8;
            btnSelectAll.Text = "Select All";
            btnSelectAll.UseVisualStyleBackColor = true;
            btnSelectAll.Click += button1_Click;
            // 
            // dgvSelectResult
            // 
            dgvSelectResult.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvSelectResult.Location = new Point(139, 371);
            dgvSelectResult.Name = "dgvSelectResult";
            dgvSelectResult.RowTemplate.Height = 25;
            dgvSelectResult.Size = new Size(649, 153);
            dgvSelectResult.TabIndex = 9;
            // 
            // frmStore
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 620);
            Controls.Add(dgvSelectResult);
            Controls.Add(btnSelectAll);
            Controls.Add(btnManualDelete);
            Controls.Add(btnManualUpdate);
            Controls.Add(btnManualInsert);
            Controls.Add(btnCreateTable);
            Controls.Add(btnAdmin);
            Controls.Add(btnBuy);
            Controls.Add(dgvGamesList);
            Controls.Add(lblUsername);
            Name = "frmStore";
            Text = "Tiny Game Store";
            FormClosed += frmStore_FormClosed;
            Load += frmStore_Load;
            ((System.ComponentModel.ISupportInitialize)dgvGamesList).EndInit();
            ((System.ComponentModel.ISupportInitialize)dgvSelectResult).EndInit();
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
        private Button btnCreateTable;
        private Button btnManualInsert;
        private Button btnManualUpdate;
        private Button btnManualDelete;
        private Button btnSelectAll;
        private DataGridView dgvSelectResult;
    }
}