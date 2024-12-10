namespace DLWMS.WinApp
{
    partial class frmPrijava
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
            txtKorisnickoIme = new TextBox();
            label1 = new Label();
            label2 = new Label();
            txtLozinka = new TextBox();
            btnPrijava = new Button();
            err = new ErrorProvider(components);
            llblRegistracija = new LinkLabel();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // txtKorisnickoIme
            // 
            txtKorisnickoIme.BackColor = SystemColors.ActiveCaption;
            txtKorisnickoIme.Font = new Font("Segoe UI", 15F);
            txtKorisnickoIme.Location = new Point(658, 249);
            txtKorisnickoIme.Name = "txtKorisnickoIme";
            txtKorisnickoIme.Size = new Size(298, 34);
            txtKorisnickoIme.TabIndex = 0;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.Transparent;
            label1.Font = new Font("Segoe UI", 11F, FontStyle.Bold);
            label1.ForeColor = SystemColors.ButtonHighlight;
            label1.Location = new Point(660, 224);
            label1.Name = "label1";
            label1.Size = new Size(112, 20);
            label1.TabIndex = 1;
            label1.Text = "Korisničko ime";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.BackColor = Color.Transparent;
            label2.Font = new Font("Segoe UI", 11F, FontStyle.Bold);
            label2.ForeColor = SystemColors.ButtonHighlight;
            label2.Location = new Point(660, 295);
            label2.Name = "label2";
            label2.Size = new Size(62, 20);
            label2.TabIndex = 3;
            label2.Text = "Lozinka";
            // 
            // txtLozinka
            // 
            txtLozinka.BackColor = SystemColors.ActiveCaption;
            txtLozinka.Font = new Font("Segoe UI", 15F);
            txtLozinka.Location = new Point(658, 320);
            txtLozinka.Name = "txtLozinka";
            txtLozinka.PasswordChar = '*';
            txtLozinka.Size = new Size(298, 34);
            txtLozinka.TabIndex = 2;
            // 
            // btnPrijava
            // 
            btnPrijava.BackColor = SystemColors.ActiveCaption;
            btnPrijava.Font = new Font("Segoe UI", 13F, FontStyle.Bold);
            btnPrijava.Location = new Point(835, 373);
            btnPrijava.Name = "btnPrijava";
            btnPrijava.Size = new Size(121, 38);
            btnPrijava.TabIndex = 4;
            btnPrijava.Text = "PRIJAVA";
            btnPrijava.UseVisualStyleBackColor = false;
            btnPrijava.Click += btnPrijava_Click;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // llblRegistracija
            // 
            llblRegistracija.AutoSize = true;
            llblRegistracija.BackColor = Color.Transparent;
            llblRegistracija.Font = new Font("Segoe UI", 12F);
            llblRegistracija.ForeColor = SystemColors.ButtonHighlight;
            llblRegistracija.LinkColor = Color.White;
            llblRegistracija.Location = new Point(658, 387);
            llblRegistracija.Name = "llblRegistracija";
            llblRegistracija.Size = new Size(140, 21);
            llblRegistracija.TabIndex = 5;
            llblRegistracija.TabStop = true;
            llblRegistracija.Text = "Niste registrovani?";
            llblRegistracija.LinkClicked += llblRegistracija_LinkClicked;
            // 
            // frmPrijava
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackgroundImage = Properties.Resources.background;
            BackgroundImageLayout = ImageLayout.Stretch;
            ClientSize = new Size(1013, 524);
            Controls.Add(llblRegistracija);
            Controls.Add(btnPrijava);
            Controls.Add(label2);
            Controls.Add(txtLozinka);
            Controls.Add(label1);
            Controls.Add(txtKorisnickoIme);
            FormBorderStyle = FormBorderStyle.None;
            Name = "frmPrijava";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPrijava";
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox txtKorisnickoIme;
        private Label label1;
        private Label label2;
        private TextBox txtLozinka;
        private Button btnPrijava;
        private ErrorProvider err;
        private LinkLabel llblRegistracija;
    }
}