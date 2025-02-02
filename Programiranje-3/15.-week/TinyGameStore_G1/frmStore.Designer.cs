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
            averageRating = new DataGridViewTextBoxColumn();
            btnBuy = new Button();
            btnAdmin = new Button();
            btnInserGame = new Button();
            grpRatings = new GroupBox();
            btnRate = new Button();
            radioButton5 = new RadioButton();
            radioButton4 = new RadioButton();
            radioButton3 = new RadioButton();
            radioButton2 = new RadioButton();
            radioButton1 = new RadioButton();
            pbCoverArt = new PictureBox();
            btnUpdateCoverArt = new Button();
            btnGenerate = new Button();
            rtbGame = new RichTextBox();
            label1 = new Label();
            txtNumberOfGames = new TextBox();
            dtpGame = new DateTimePicker();
            ((System.ComponentModel.ISupportInitialize)dgvGamesList).BeginInit();
            grpRatings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)pbCoverArt).BeginInit();
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
            dgvGamesList.Columns.AddRange(new DataGridViewColumn[] { Id, GameName, Publisher, ReleaseDate, averageRating });
            dgvGamesList.Location = new Point(12, 27);
            dgvGamesList.Name = "dgvGamesList";
            dgvGamesList.RowTemplate.Height = 25;
            dgvGamesList.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvGamesList.Size = new Size(776, 267);
            dgvGamesList.TabIndex = 1;
            dgvGamesList.CellContentClick += dgvGamesList_CellDoubleClick;
            // 
            // Id
            // 
            Id.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Id.DataPropertyName = "Id";
            Id.HeaderText = "Id";
            Id.Name = "Id";
            // 
            // GameName
            // 
            GameName.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            GameName.DataPropertyName = "Name";
            GameName.HeaderText = "Name";
            GameName.Name = "GameName";
            // 
            // Publisher
            // 
            Publisher.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Publisher.DataPropertyName = "Publisher";
            Publisher.HeaderText = "Publisher";
            Publisher.Name = "Publisher";
            // 
            // ReleaseDate
            // 
            ReleaseDate.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            ReleaseDate.DataPropertyName = "ReleaseDate";
            ReleaseDate.HeaderText = "Release Date";
            ReleaseDate.Name = "ReleaseDate";
            // 
            // averageRating
            // 
            averageRating.DataPropertyName = "averageRating";
            averageRating.HeaderText = "Average Rating";
            averageRating.Name = "averageRating";
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
            btnAdmin.Location = new Point(496, 300);
            btnAdmin.Name = "btnAdmin";
            btnAdmin.Size = new Size(75, 23);
            btnAdmin.TabIndex = 3;
            btnAdmin.Text = "Admin";
            btnAdmin.UseVisualStyleBackColor = true;
            btnAdmin.Click += btnAdmin_Click;
            // 
            // btnInserGame
            // 
            btnInserGame.Location = new Point(577, 300);
            btnInserGame.Name = "btnInserGame";
            btnInserGame.Size = new Size(112, 23);
            btnInserGame.TabIndex = 4;
            btnInserGame.Text = "Testing Insert";
            btnInserGame.UseVisualStyleBackColor = true;
            // 
            // grpRatings
            // 
            grpRatings.Controls.Add(btnRate);
            grpRatings.Controls.Add(radioButton5);
            grpRatings.Controls.Add(radioButton4);
            grpRatings.Controls.Add(radioButton3);
            grpRatings.Controls.Add(radioButton2);
            grpRatings.Controls.Add(radioButton1);
            grpRatings.Location = new Point(12, 300);
            grpRatings.Name = "grpRatings";
            grpRatings.Size = new Size(200, 84);
            grpRatings.TabIndex = 5;
            grpRatings.TabStop = false;
            grpRatings.Text = "Ratings:";
            // 
            // btnRate
            // 
            btnRate.Location = new Point(58, 55);
            btnRate.Name = "btnRate";
            btnRate.Size = new Size(75, 23);
            btnRate.TabIndex = 6;
            btnRate.Text = "Rate";
            btnRate.UseVisualStyleBackColor = true;
            btnRate.Click += btnRate_Click;
            // 
            // radioButton5
            // 
            radioButton5.AutoSize = true;
            radioButton5.Location = new Point(154, 22);
            radioButton5.Name = "radioButton5";
            radioButton5.Size = new Size(31, 19);
            radioButton5.TabIndex = 10;
            radioButton5.TabStop = true;
            radioButton5.Text = "5";
            radioButton5.UseVisualStyleBackColor = true;
            // 
            // radioButton4
            // 
            radioButton4.AutoSize = true;
            radioButton4.Location = new Point(117, 22);
            radioButton4.Name = "radioButton4";
            radioButton4.Size = new Size(31, 19);
            radioButton4.TabIndex = 9;
            radioButton4.TabStop = true;
            radioButton4.Text = "4";
            radioButton4.UseVisualStyleBackColor = true;
            // 
            // radioButton3
            // 
            radioButton3.AutoSize = true;
            radioButton3.Location = new Point(80, 22);
            radioButton3.Name = "radioButton3";
            radioButton3.Size = new Size(31, 19);
            radioButton3.TabIndex = 8;
            radioButton3.TabStop = true;
            radioButton3.Text = "3";
            radioButton3.UseVisualStyleBackColor = true;
            // 
            // radioButton2
            // 
            radioButton2.AutoSize = true;
            radioButton2.Location = new Point(43, 22);
            radioButton2.Name = "radioButton2";
            radioButton2.Size = new Size(31, 19);
            radioButton2.TabIndex = 7;
            radioButton2.TabStop = true;
            radioButton2.Text = "2";
            radioButton2.UseVisualStyleBackColor = true;
            // 
            // radioButton1
            // 
            radioButton1.AutoSize = true;
            radioButton1.Location = new Point(6, 22);
            radioButton1.Name = "radioButton1";
            radioButton1.Size = new Size(31, 19);
            radioButton1.TabIndex = 6;
            radioButton1.TabStop = true;
            radioButton1.Text = "1";
            radioButton1.UseVisualStyleBackColor = true;
            // 
            // pbCoverArt
            // 
            pbCoverArt.BorderStyle = BorderStyle.FixedSingle;
            pbCoverArt.Location = new Point(12, 409);
            pbCoverArt.Name = "pbCoverArt";
            pbCoverArt.Size = new Size(237, 153);
            pbCoverArt.SizeMode = PictureBoxSizeMode.Zoom;
            pbCoverArt.TabIndex = 6;
            pbCoverArt.TabStop = false;
            pbCoverArt.DoubleClick += pbCoverArt_DoubleClick;
            // 
            // btnUpdateCoverArt
            // 
            btnUpdateCoverArt.Location = new Point(12, 568);
            btnUpdateCoverArt.Name = "btnUpdateCoverArt";
            btnUpdateCoverArt.Size = new Size(75, 23);
            btnUpdateCoverArt.TabIndex = 7;
            btnUpdateCoverArt.Text = "Update cover art";
            btnUpdateCoverArt.UseVisualStyleBackColor = true;
            btnUpdateCoverArt.Click += btnUpdateCoverArt_Click;
            // 
            // btnGenerate
            // 
            btnGenerate.Location = new Point(329, 511);
            btnGenerate.Name = "btnGenerate";
            btnGenerate.Size = new Size(75, 23);
            btnGenerate.TabIndex = 12;
            btnGenerate.Text = "Generate";
            btnGenerate.UseVisualStyleBackColor = true;
            btnGenerate.Click += btnGenerate_Click;
            // 
            // rtbGame
            // 
            rtbGame.Location = new Point(476, 355);
            rtbGame.Name = "rtbGame";
            rtbGame.Size = new Size(321, 262);
            rtbGame.TabIndex = 11;
            rtbGame.Text = "";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(270, 474);
            label1.Name = "label1";
            label1.Size = new Size(106, 15);
            label1.TabIndex = 10;
            label1.Text = "Number of games:";
            // 
            // txtNumberOfGames
            // 
            txtNumberOfGames.Location = new Point(394, 471);
            txtNumberOfGames.Name = "txtNumberOfGames";
            txtNumberOfGames.Size = new Size(76, 23);
            txtNumberOfGames.TabIndex = 9;
            // 
            // dtpGame
            // 
            dtpGame.Location = new Point(270, 442);
            dtpGame.Name = "dtpGame";
            dtpGame.Size = new Size(200, 23);
            dtpGame.TabIndex = 8;
            // 
            // frmStore
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(809, 629);
            Controls.Add(btnGenerate);
            Controls.Add(rtbGame);
            Controls.Add(label1);
            Controls.Add(txtNumberOfGames);
            Controls.Add(dtpGame);
            Controls.Add(btnUpdateCoverArt);
            Controls.Add(pbCoverArt);
            Controls.Add(grpRatings);
            Controls.Add(btnInserGame);
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
            grpRatings.ResumeLayout(false);
            grpRatings.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)pbCoverArt).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblUsername;
        private DataGridView dgvGamesList;
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
        private DataGridViewTextBoxColumn Id;
        private DataGridViewTextBoxColumn GameName;
        private DataGridViewTextBoxColumn Publisher;
        private DataGridViewTextBoxColumn ReleaseDate;
        private DataGridViewTextBoxColumn averageRating;
        private Button btnGenerate;
        private RichTextBox rtbGame;
        private Label label1;
        private TextBox txtNumberOfGames;
        private DateTimePicker dtpGame;
    }
}