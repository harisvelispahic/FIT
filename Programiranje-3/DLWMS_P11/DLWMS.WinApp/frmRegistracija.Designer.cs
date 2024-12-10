namespace DLWMS.WinApp
{
    partial class frmRegistracija
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
            txtIme = new TextBox();
            label1 = new Label();
            label2 = new Label();
            txtEmail = new TextBox();
            txtPrezime = new TextBox();
            label3 = new Label();
            txtLozinka = new TextBox();
            label4 = new Label();
            label5 = new Label();
            txtKorisnickoIme = new TextBox();
            btnSacuvaj = new Button();
            pictureBox1 = new PictureBox();
            err = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // txtIme
            // 
            txtIme.Location = new Point(218, 51);
            txtIme.Name = "txtIme";
            txtIme.Size = new Size(146, 23);
            txtIme.TabIndex = 0;
            txtIme.TextChanged += txtIme_TextChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(218, 33);
            label1.Name = "label1";
            label1.Size = new Size(27, 15);
            label1.TabIndex = 1;
            label1.Text = "Ime";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(370, 32);
            label2.Name = "label2";
            label2.Size = new Size(49, 15);
            label2.TabIndex = 3;
            label2.Text = "Prezime";
            // 
            // txtEmail
            // 
            txtEmail.Location = new Point(218, 95);
            txtEmail.Name = "txtEmail";
            txtEmail.Size = new Size(298, 23);
            txtEmail.TabIndex = 2;
            // 
            // txtPrezime
            // 
            txtPrezime.Location = new Point(370, 51);
            txtPrezime.Name = "txtPrezime";
            txtPrezime.Size = new Size(146, 23);
            txtPrezime.TabIndex = 1;
            txtPrezime.TextChanged += txtPrezime_TextChanged;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(218, 77);
            label3.Name = "label3";
            label3.Size = new Size(36, 15);
            label3.TabIndex = 5;
            label3.Text = "Email";
            // 
            // txtLozinka
            // 
            txtLozinka.Location = new Point(370, 150);
            txtLozinka.Name = "txtLozinka";
            txtLozinka.PasswordChar = '*';
            txtLozinka.Size = new Size(146, 23);
            txtLozinka.TabIndex = 4;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(370, 131);
            label4.Name = "label4";
            label4.Size = new Size(47, 15);
            label4.TabIndex = 8;
            label4.Text = "Lozinka";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(218, 132);
            label5.Name = "label5";
            label5.Size = new Size(85, 15);
            label5.TabIndex = 7;
            label5.Text = "Korisničko ime";
            // 
            // txtKorisnickoIme
            // 
            txtKorisnickoIme.Location = new Point(218, 150);
            txtKorisnickoIme.Name = "txtKorisnickoIme";
            txtKorisnickoIme.Size = new Size(146, 23);
            txtKorisnickoIme.TabIndex = 3;
            // 
            // btnSacuvaj
            // 
            btnSacuvaj.Location = new Point(441, 179);
            btnSacuvaj.Name = "btnSacuvaj";
            btnSacuvaj.Size = new Size(75, 23);
            btnSacuvaj.TabIndex = 5;
            btnSacuvaj.Text = "Sačuvaj";
            btnSacuvaj.UseVisualStyleBackColor = true;
            btnSacuvaj.Click += btnSacuvaj_Click;
            // 
            // pictureBox1
            // 
            pictureBox1.Image = Properties.Resources._3177440;
            pictureBox1.Location = new Point(12, 33);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(161, 169);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.TabIndex = 11;
            pictureBox1.TabStop = false;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // frmRegistracija
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(546, 216);
            Controls.Add(pictureBox1);
            Controls.Add(btnSacuvaj);
            Controls.Add(txtLozinka);
            Controls.Add(label4);
            Controls.Add(label5);
            Controls.Add(txtKorisnickoIme);
            Controls.Add(label3);
            Controls.Add(txtPrezime);
            Controls.Add(label2);
            Controls.Add(txtEmail);
            Controls.Add(label1);
            Controls.Add(txtIme);
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "frmRegistracija";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Registracija";
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox txtIme;
        private Label label1;
        private Label label2;
        private TextBox txtEmail;
        private TextBox txtPrezime;
        private Label label3;
        private TextBox txtLozinka;
        private Label label4;
        private Label label5;
        private TextBox txtKorisnickoIme;
        private Button btnSacuvaj;
        private PictureBox pictureBox1;
        private ErrorProvider err;
    }
}