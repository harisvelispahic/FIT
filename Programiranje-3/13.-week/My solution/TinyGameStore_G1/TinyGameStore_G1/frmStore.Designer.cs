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
            components = new System.ComponentModel.Container();
            lblUsername = new Label();
            dgvGamesList = new DataGridView();
            btnBuy = new Button();
            btnAdmin = new Button();
            btnInserGame = new Button();
            gbRating = new GroupBox();
            radioButton5 = new RadioButton();
            radioButton4 = new RadioButton();
            radioButton3 = new RadioButton();
            radioButton2 = new RadioButton();
            radioButton1 = new RadioButton();
            btnRate = new Button();
            pbCoverArt = new PictureBox();
            btnUpdate = new Button();
            err = new ErrorProvider(components);
            Id = new DataGridViewTextBoxColumn();
            GameName = new DataGridViewTextBoxColumn();
            Publisher = new DataGridViewTextBoxColumn();
            ReleaseDate = new DataGridViewTextBoxColumn();
            CoverArt = new DataGridViewImageColumn();
            Price = new DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)dgvGamesList).BeginInit();
            gbRating.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)pbCoverArt).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.Location = new Point(14, 12);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(50, 20);
            lblUsername.TabIndex = 0;
            lblUsername.Text = "label1";
            // 
            // dgvGamesList
            // 
            dgvGamesList.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvGamesList.Columns.AddRange(new DataGridViewColumn[] { Id, GameName, Publisher, ReleaseDate, CoverArt, Price });
            dgvGamesList.Location = new Point(14, 36);
            dgvGamesList.Margin = new Padding(3, 4, 3, 4);
            dgvGamesList.Name = "dgvGamesList";
            dgvGamesList.RowHeadersWidth = 51;
            dgvGamesList.RowTemplate.Height = 25;
            dgvGamesList.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvGamesList.Size = new Size(887, 356);
            dgvGamesList.TabIndex = 1;
            // 
            // btnBuy
            // 
            btnBuy.Location = new Point(749, 415);
            btnBuy.Margin = new Padding(3, 4, 3, 4);
            btnBuy.Name = "btnBuy";
            btnBuy.Size = new Size(152, 31);
            btnBuy.TabIndex = 2;
            btnBuy.Text = "Buy";
            btnBuy.UseVisualStyleBackColor = true;
            btnBuy.Click += btnBuy_Click;
            // 
            // btnAdmin
            // 
            btnAdmin.Location = new Point(613, 300);
            btnAdmin.Name = "btnAdmin";
            btnAdmin.Size = new Size(75, 23);
            btnAdmin.TabIndex = 3;
            btnAdmin.Text = "Admin";
            btnAdmin.UseVisualStyleBackColor = true;
            btnAdmin.Click += btnAdmin_Click;
            // 
            // btnInserGame
            // 
            btnInserGame.Location = new Point(613, 338);
            btnInserGame.Name = "btnInserGame";
            btnInserGame.Size = new Size(112, 23);
            btnInserGame.TabIndex = 4;
            btnInserGame.Text = "TestingInsert";
            btnInserGame.UseVisualStyleBackColor = true;
            btnInserGame.Click += btnInserGame_Click;
            // 
            // gbRating
            // 
            gbRating.Controls.Add(radioButton5);
            gbRating.Controls.Add(radioButton4);
            gbRating.Controls.Add(radioButton3);
            gbRating.Controls.Add(radioButton2);
            gbRating.Controls.Add(radioButton1);
            gbRating.Location = new Point(14, 400);
            gbRating.Margin = new Padding(3, 4, 3, 4);
            gbRating.Name = "gbRating";
            gbRating.Padding = new Padding(3, 4, 3, 4);
            gbRating.Size = new Size(246, 81);
            gbRating.TabIndex = 5;
            gbRating.TabStop = false;
            gbRating.Text = "Rating";
            // 
            // radioButton5
            // 
            radioButton5.AutoSize = true;
            radioButton5.Location = new Point(176, 29);
            radioButton5.Margin = new Padding(3, 4, 3, 4);
            radioButton5.Name = "radioButton5";
            radioButton5.Size = new Size(38, 24);
            radioButton5.TabIndex = 0;
            radioButton5.TabStop = true;
            radioButton5.Text = "5";
            radioButton5.UseVisualStyleBackColor = true;
            // 
            // radioButton4
            // 
            radioButton4.AutoSize = true;
            radioButton4.Location = new Point(134, 29);
            radioButton4.Margin = new Padding(3, 4, 3, 4);
            radioButton4.Name = "radioButton4";
            radioButton4.Size = new Size(38, 24);
            radioButton4.TabIndex = 0;
            radioButton4.TabStop = true;
            radioButton4.Text = "4";
            radioButton4.UseVisualStyleBackColor = true;
            // 
            // radioButton3
            // 
            radioButton3.AutoSize = true;
            radioButton3.Location = new Point(91, 29);
            radioButton3.Margin = new Padding(3, 4, 3, 4);
            radioButton3.Name = "radioButton3";
            radioButton3.Size = new Size(38, 24);
            radioButton3.TabIndex = 0;
            radioButton3.TabStop = true;
            radioButton3.Text = "3";
            radioButton3.UseVisualStyleBackColor = true;
            // 
            // radioButton2
            // 
            radioButton2.AutoSize = true;
            radioButton2.Location = new Point(49, 29);
            radioButton2.Margin = new Padding(3, 4, 3, 4);
            radioButton2.Name = "radioButton2";
            radioButton2.Size = new Size(38, 24);
            radioButton2.TabIndex = 0;
            radioButton2.TabStop = true;
            radioButton2.Text = "2";
            radioButton2.UseVisualStyleBackColor = true;
            // 
            // radioButton1
            // 
            radioButton1.AutoSize = true;
            radioButton1.Location = new Point(7, 29);
            radioButton1.Margin = new Padding(3, 4, 3, 4);
            radioButton1.Name = "radioButton1";
            radioButton1.Size = new Size(38, 24);
            radioButton1.TabIndex = 0;
            radioButton1.TabStop = true;
            radioButton1.Text = "1";
            radioButton1.UseVisualStyleBackColor = true;
            // 
            // btnRate
            // 
            btnRate.Location = new Point(87, 489);
            btnRate.Margin = new Padding(3, 4, 3, 4);
            btnRate.Name = "btnRate";
            btnRate.Size = new Size(81, 31);
            btnRate.TabIndex = 6;
            btnRate.Text = "Rate";
            btnRate.UseVisualStyleBackColor = true;
            btnRate.Click += btnRate_Click;
            // 
            // pbCoverArt
            // 
            pbCoverArt.BorderStyle = BorderStyle.FixedSingle;
            pbCoverArt.Location = new Point(282, 415);
            pbCoverArt.Margin = new Padding(3, 4, 3, 4);
            pbCoverArt.Name = "pbCoverArt";
            pbCoverArt.Size = new Size(436, 226);
            pbCoverArt.SizeMode = PictureBoxSizeMode.Zoom;
            pbCoverArt.TabIndex = 7;
            pbCoverArt.TabStop = false;
            pbCoverArt.Click += pictureBox1_Click;
            // 
            // btnUpdate
            // 
            btnUpdate.Location = new Point(416, 649);
            btnUpdate.Margin = new Padding(3, 4, 3, 4);
            btnUpdate.Name = "btnUpdate";
            btnUpdate.Size = new Size(174, 31);
            btnUpdate.TabIndex = 8;
            btnUpdate.Text = "Update cover art";
            btnUpdate.UseVisualStyleBackColor = true;
            btnUpdate.Click += btnUpdate_Click;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // Id
            // 
            Id.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Id.DataPropertyName = "Id";
            Id.HeaderText = "Id";
            Id.MinimumWidth = 6;
            Id.Name = "Id";
            Id.ReadOnly = true;
            // 
            // GameName
            // 
            GameName.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            GameName.DataPropertyName = "Name";
            GameName.HeaderText = "Name";
            GameName.MinimumWidth = 6;
            GameName.Name = "GameName";
            GameName.ReadOnly = true;
            // 
            // Publisher
            // 
            Publisher.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Publisher.DataPropertyName = "Publisher";
            Publisher.HeaderText = "Publisher";
            Publisher.MinimumWidth = 6;
            Publisher.Name = "Publisher";
            Publisher.ReadOnly = true;
            // 
            // ReleaseDate
            // 
            ReleaseDate.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            ReleaseDate.DataPropertyName = "ReleaseDate";
            ReleaseDate.HeaderText = "Release Date";
            ReleaseDate.MinimumWidth = 6;
            ReleaseDate.Name = "ReleaseDate";
            ReleaseDate.ReadOnly = true;
            // 
            // CoverArt
            // 
            CoverArt.DataPropertyName = "CoverArt";
            CoverArt.HeaderText = "Cover Art";
            CoverArt.MinimumWidth = 6;
            CoverArt.Name = "CoverArt";
            CoverArt.Width = 125;
            // 
            // Price
            // 
            Price.DataPropertyName = "Price";
            Price.HeaderText = "Price";
            Price.MinimumWidth = 6;
            Price.Name = "Price";
            Price.Width = 125;
            // 
            // frmStore
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(919, 689);
            Controls.Add(btnUpdate);
            Controls.Add(pbCoverArt);
            Controls.Add(btnRate);
            Controls.Add(gbRating);
            Controls.Add(btnBuy);
            Controls.Add(dgvGamesList);
            Controls.Add(lblUsername);
            Margin = new Padding(3, 4, 3, 4);
            Name = "frmStore";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Tiny Game Store";
            FormClosed += frmStore_FormClosed;
            Load += frmStore_Load;
            ((System.ComponentModel.ISupportInitialize)dgvGamesList).EndInit();
            gbRating.ResumeLayout(false);
            gbRating.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)pbCoverArt).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblUsername;
        private DataGridView dgvGamesList;
        private Button btnBuy;
        private Button btnAdmin;
        private Button btnInserGame;
        private GroupBox gbRating;
        private RadioButton radioButton5;
        private RadioButton radioButton4;
        private RadioButton radioButton3;
        private RadioButton radioButton2;
        private RadioButton radioButton1;
        private Button btnRate;
        private PictureBox pbCoverArt;
        private Button btnUpdate;
        private ErrorProvider err;
        private DataGridViewTextBoxColumn Id;
        private DataGridViewTextBoxColumn GameName;
        private DataGridViewTextBoxColumn Publisher;
        private DataGridViewTextBoxColumn ReleaseDate;
        private DataGridViewImageColumn CoverArt;
        private DataGridViewTextBoxColumn Price;
    }
}