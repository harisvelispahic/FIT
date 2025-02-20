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
            this.lblUsername = new System.Windows.Forms.Label();
            this.dgvGamesList = new System.Windows.Forms.DataGridView();
            this.Id = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.GameName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Publisher = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ReleaseDate = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.btnBuy = new System.Windows.Forms.Button();
            this.btnAdmin = new System.Windows.Forms.Button();
            this.btnInserGame = new System.Windows.Forms.Button();
            this.grpRatings = new System.Windows.Forms.GroupBox();
            this.btnRate = new System.Windows.Forms.Button();
            this.radioButton5 = new System.Windows.Forms.RadioButton();
            this.radioButton4 = new System.Windows.Forms.RadioButton();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.pbCoverArt = new System.Windows.Forms.PictureBox();
            this.btnUpdateCoverArt = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvGamesList)).BeginInit();
            this.grpRatings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbCoverArt)).BeginInit();
            this.SuspendLayout();
            // 
            // lblUsername
            // 
            this.lblUsername.AutoSize = true;
            this.lblUsername.Location = new System.Drawing.Point(12, 9);
            this.lblUsername.Name = "lblUsername";
            this.lblUsername.Size = new System.Drawing.Size(38, 15);
            this.lblUsername.TabIndex = 0;
            this.lblUsername.Text = "label1";
            // 
            // dgvGamesList
            // 
            this.dgvGamesList.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvGamesList.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Id,
            this.GameName,
            this.Publisher,
            this.ReleaseDate});
            this.dgvGamesList.Location = new System.Drawing.Point(12, 27);
            this.dgvGamesList.Name = "dgvGamesList";
            this.dgvGamesList.RowTemplate.Height = 25;
            this.dgvGamesList.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgvGamesList.Size = new System.Drawing.Size(776, 267);
            this.dgvGamesList.TabIndex = 1;
            // 
            // Id
            // 
            this.Id.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Id.DataPropertyName = "Id";
            this.Id.HeaderText = "Id";
            this.Id.Name = "Id";
            this.Id.ReadOnly = true;
            // 
            // GameName
            // 
            this.GameName.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.GameName.DataPropertyName = "Name";
            this.GameName.HeaderText = "Name";
            this.GameName.Name = "GameName";
            this.GameName.ReadOnly = true;
            // 
            // Publisher
            // 
            this.Publisher.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.Publisher.DataPropertyName = "Publisher";
            this.Publisher.HeaderText = "Publisher";
            this.Publisher.Name = "Publisher";
            this.Publisher.ReadOnly = true;
            // 
            // ReleaseDate
            // 
            this.ReleaseDate.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ReleaseDate.DataPropertyName = "ReleaseDate";
            this.ReleaseDate.HeaderText = "Release Date";
            this.ReleaseDate.Name = "ReleaseDate";
            this.ReleaseDate.ReadOnly = true;
            // 
            // btnBuy
            // 
            this.btnBuy.Location = new System.Drawing.Point(713, 300);
            this.btnBuy.Name = "btnBuy";
            this.btnBuy.Size = new System.Drawing.Size(75, 23);
            this.btnBuy.TabIndex = 2;
            this.btnBuy.Text = "Buy";
            this.btnBuy.UseVisualStyleBackColor = true;
            this.btnBuy.Click += new System.EventHandler(this.btnBuy_Click);
            // 
            // btnAdmin
            // 
            this.btnAdmin.Location = new System.Drawing.Point(556, 300);
            this.btnAdmin.Name = "btnAdmin";
            this.btnAdmin.Size = new System.Drawing.Size(75, 23);
            this.btnAdmin.TabIndex = 3;
            this.btnAdmin.Text = "Admin";
            this.btnAdmin.UseVisualStyleBackColor = true;
            this.btnAdmin.Click += new System.EventHandler(this.btnAdmin_Click);
            // 
            // btnInserGame
            // 
            this.btnInserGame.Location = new System.Drawing.Point(676, 329);
            this.btnInserGame.Name = "btnInserGame";
            this.btnInserGame.Size = new System.Drawing.Size(112, 23);
            this.btnInserGame.TabIndex = 4;
            this.btnInserGame.Text = "TestingInsert";
            this.btnInserGame.UseVisualStyleBackColor = true;
            // 
            // grpRatings
            // 
            this.grpRatings.Controls.Add(this.btnRate);
            this.grpRatings.Controls.Add(this.radioButton5);
            this.grpRatings.Controls.Add(this.radioButton4);
            this.grpRatings.Controls.Add(this.radioButton3);
            this.grpRatings.Controls.Add(this.radioButton2);
            this.grpRatings.Controls.Add(this.radioButton1);
            this.grpRatings.Location = new System.Drawing.Point(12, 300);
            this.grpRatings.Name = "grpRatings";
            this.grpRatings.Size = new System.Drawing.Size(200, 84);
            this.grpRatings.TabIndex = 5;
            this.grpRatings.TabStop = false;
            this.grpRatings.Text = "Ratings:";
            // 
            // btnRate
            // 
            this.btnRate.Location = new System.Drawing.Point(58, 55);
            this.btnRate.Name = "btnRate";
            this.btnRate.Size = new System.Drawing.Size(75, 23);
            this.btnRate.TabIndex = 6;
            this.btnRate.Text = "Rate";
            this.btnRate.UseVisualStyleBackColor = true;
            this.btnRate.Click += new System.EventHandler(this.btnRate_Click);
            // 
            // radioButton5
            // 
            this.radioButton5.AutoSize = true;
            this.radioButton5.Location = new System.Drawing.Point(154, 22);
            this.radioButton5.Name = "radioButton5";
            this.radioButton5.Size = new System.Drawing.Size(31, 19);
            this.radioButton5.TabIndex = 10;
            this.radioButton5.TabStop = true;
            this.radioButton5.Text = "5";
            this.radioButton5.UseVisualStyleBackColor = true;
            // 
            // radioButton4
            // 
            this.radioButton4.AutoSize = true;
            this.radioButton4.Location = new System.Drawing.Point(117, 22);
            this.radioButton4.Name = "radioButton4";
            this.radioButton4.Size = new System.Drawing.Size(31, 19);
            this.radioButton4.TabIndex = 9;
            this.radioButton4.TabStop = true;
            this.radioButton4.Text = "4";
            this.radioButton4.UseVisualStyleBackColor = true;
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(80, 22);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(31, 19);
            this.radioButton3.TabIndex = 8;
            this.radioButton3.TabStop = true;
            this.radioButton3.Text = "3";
            this.radioButton3.UseVisualStyleBackColor = true;
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(43, 22);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(31, 19);
            this.radioButton2.TabIndex = 7;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "2";
            this.radioButton2.UseVisualStyleBackColor = true;
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(6, 22);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(31, 19);
            this.radioButton1.TabIndex = 6;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "1";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // pbCoverArt
            // 
            this.pbCoverArt.Location = new System.Drawing.Point(218, 309);
            this.pbCoverArt.Name = "pbCoverArt";
            this.pbCoverArt.Size = new System.Drawing.Size(237, 153);
            this.pbCoverArt.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pbCoverArt.TabIndex = 6;
            this.pbCoverArt.TabStop = false;
            this.pbCoverArt.DoubleClick += new System.EventHandler(this.pbCoverArt_DoubleClick);
            // 
            // btnUpdateCoverArt
            // 
            this.btnUpdateCoverArt.Location = new System.Drawing.Point(218, 468);
            this.btnUpdateCoverArt.Name = "btnUpdateCoverArt";
            this.btnUpdateCoverArt.Size = new System.Drawing.Size(75, 23);
            this.btnUpdateCoverArt.TabIndex = 7;
            this.btnUpdateCoverArt.Text = "Update cover art";
            this.btnUpdateCoverArt.UseVisualStyleBackColor = true;
            this.btnUpdateCoverArt.Click += new System.EventHandler(this.btnUpdateCoverArt_Click);
            // 
            // frmStore
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(809, 499);
            this.Controls.Add(this.btnUpdateCoverArt);
            this.Controls.Add(this.pbCoverArt);
            this.Controls.Add(this.grpRatings);
            this.Controls.Add(this.btnInserGame);
            this.Controls.Add(this.btnAdmin);
            this.Controls.Add(this.btnBuy);
            this.Controls.Add(this.dgvGamesList);
            this.Controls.Add(this.lblUsername);
            this.Name = "frmStore";
            this.Text = "Tiny Game Store";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.frmStore_FormClosed);
            this.Load += new System.EventHandler(this.frmStore_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvGamesList)).EndInit();
            this.grpRatings.ResumeLayout(false);
            this.grpRatings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbCoverArt)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

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
        private Button btnInserGame;
        private GroupBox grpRatings;
        private RadioButton radioButton5;
        private RadioButton radioButton4;
        private RadioButton radioButton3;
        private RadioButton radioButton2;
        private RadioButton radioButton1;
        private Button btnRate;
        private PictureBox pbCoverArt;
        private Button btnUpdateCoverArt;
    }
}