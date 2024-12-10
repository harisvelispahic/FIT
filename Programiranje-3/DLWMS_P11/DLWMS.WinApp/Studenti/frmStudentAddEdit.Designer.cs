namespace DLWMS.WinApp.Studenti
{
    partial class frmStudentAddEdit
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
            btnSacuvaj = new Button();
            pbSlika = new PictureBox();
            btnUcitajSliku = new Button();
            txtBrojIndeksa = new TextBox();
            label1 = new Label();
            label2 = new Label();
            txtEmail = new TextBox();
            label3 = new Label();
            txtPrezime = new TextBox();
            label4 = new Label();
            txtIme = new TextBox();
            dtpDatumRodjenja = new DateTimePicker();
            label5 = new Label();
            label6 = new Label();
            txtLozinka = new TextBox();
            cmbSpol = new ComboBox();
            label7 = new Label();
            label8 = new Label();
            cmbDrzave = new ComboBox();
            label9 = new Label();
            cmbGradovi = new ComboBox();
            cbAktivan = new CheckBox();
            openFileDialog1 = new OpenFileDialog();
            err = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)pbSlika).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // btnSacuvaj
            // 
            btnSacuvaj.Location = new Point(473, 262);
            btnSacuvaj.Name = "btnSacuvaj";
            btnSacuvaj.Size = new Size(75, 23);
            btnSacuvaj.TabIndex = 10;
            btnSacuvaj.Text = "Sačuvaj";
            btnSacuvaj.UseVisualStyleBackColor = true;
            btnSacuvaj.Click += btnSacuvaj_Click;
            // 
            // pbSlika
            // 
            pbSlika.BorderStyle = BorderStyle.FixedSingle;
            pbSlika.Location = new Point(12, 28);
            pbSlika.Name = "pbSlika";
            pbSlika.Size = new Size(184, 228);
            pbSlika.SizeMode = PictureBoxSizeMode.StretchImage;
            pbSlika.TabIndex = 1;
            pbSlika.TabStop = false;
            // 
            // btnUcitajSliku
            // 
            btnUcitajSliku.Location = new Point(12, 262);
            btnUcitajSliku.Name = "btnUcitajSliku";
            btnUcitajSliku.Size = new Size(184, 23);
            btnUcitajSliku.TabIndex = 2;
            btnUcitajSliku.Text = "Učitaj sliku";
            btnUcitajSliku.UseVisualStyleBackColor = true;
            btnUcitajSliku.Click += btnUcitajSliku_Click;
            // 
            // txtBrojIndeksa
            // 
            txtBrojIndeksa.Location = new Point(203, 140);
            txtBrojIndeksa.Name = "txtBrojIndeksa";
            txtBrojIndeksa.Size = new Size(171, 23);
            txtBrojIndeksa.TabIndex = 4;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(203, 122);
            label1.Name = "label1";
            label1.Size = new Size(74, 15);
            label1.TabIndex = 4;
            label1.Text = "Broj indeksa:";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(203, 215);
            label2.Name = "label2";
            label2.Size = new Size(39, 15);
            label2.TabIndex = 6;
            label2.Text = "Email:";
            // 
            // txtEmail
            // 
            txtEmail.Location = new Point(203, 233);
            txtEmail.Name = "txtEmail";
            txtEmail.Size = new Size(172, 23);
            txtEmail.TabIndex = 8;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(378, 24);
            label3.Name = "label3";
            label3.Size = new Size(52, 15);
            label3.TabIndex = 10;
            label3.Text = "Prezime:";
            // 
            // txtPrezime
            // 
            txtPrezime.Location = new Point(378, 42);
            txtPrezime.Name = "txtPrezime";
            txtPrezime.Size = new Size(172, 23);
            txtPrezime.TabIndex = 1;
            txtPrezime.TextChanged += txtPrezime_TextChanged;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(203, 24);
            label4.Name = "label4";
            label4.Size = new Size(30, 15);
            label4.TabIndex = 8;
            label4.Text = "Ime:";
            // 
            // txtIme
            // 
            txtIme.Location = new Point(203, 42);
            txtIme.Name = "txtIme";
            txtIme.Size = new Size(171, 23);
            txtIme.TabIndex = 0;
            txtIme.TextChanged += txtIme_TextChanged;
            // 
            // dtpDatumRodjenja
            // 
            dtpDatumRodjenja.Location = new Point(203, 91);
            dtpDatumRodjenja.Name = "dtpDatumRodjenja";
            dtpDatumRodjenja.Size = new Size(171, 23);
            dtpDatumRodjenja.TabIndex = 2;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(203, 73);
            label5.Name = "label5";
            label5.Size = new Size(89, 15);
            label5.TabIndex = 12;
            label5.Text = "Datum rođenja:";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(378, 122);
            label6.Name = "label6";
            label6.Size = new Size(50, 15);
            label6.TabIndex = 14;
            label6.Text = "Lozinka:";
            // 
            // txtLozinka
            // 
            txtLozinka.Location = new Point(378, 140);
            txtLozinka.Name = "txtLozinka";
            txtLozinka.Size = new Size(171, 23);
            txtLozinka.TabIndex = 5;
            // 
            // cmbSpol
            // 
            cmbSpol.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbSpol.FormattingEnabled = true;
            cmbSpol.Location = new Point(378, 91);
            cmbSpol.Name = "cmbSpol";
            cmbSpol.Size = new Size(170, 23);
            cmbSpol.TabIndex = 3;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(378, 73);
            label7.Name = "label7";
            label7.Size = new Size(33, 15);
            label7.TabIndex = 16;
            label7.Text = "Spol:";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(203, 166);
            label8.Name = "label8";
            label8.Size = new Size(45, 15);
            label8.TabIndex = 18;
            label8.Text = "Država:";
            // 
            // cmbDrzave
            // 
            cmbDrzave.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbDrzave.FormattingEnabled = true;
            cmbDrzave.Location = new Point(203, 184);
            cmbDrzave.Name = "cmbDrzave";
            cmbDrzave.Size = new Size(170, 23);
            cmbDrzave.TabIndex = 6;
            cmbDrzave.SelectedIndexChanged += cmbDrzave_SelectedIndexChanged;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new Point(378, 166);
            label9.Name = "label9";
            label9.Size = new Size(35, 15);
            label9.TabIndex = 20;
            label9.Text = "Grad:";
            // 
            // cmbGradovi
            // 
            cmbGradovi.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbGradovi.FormattingEnabled = true;
            cmbGradovi.Location = new Point(378, 184);
            cmbGradovi.Name = "cmbGradovi";
            cmbGradovi.Size = new Size(170, 23);
            cmbGradovi.TabIndex = 7;
            // 
            // cbAktivan
            // 
            cbAktivan.AutoSize = true;
            cbAktivan.Location = new Point(381, 235);
            cbAktivan.Name = "cbAktivan";
            cbAktivan.Size = new Size(66, 19);
            cbAktivan.TabIndex = 9;
            cbAktivan.Text = "Aktivan";
            cbAktivan.UseVisualStyleBackColor = true;
            // 
            // openFileDialog1
            // 
            openFileDialog1.FileName = "openFileDialog1";
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // frmStudentAddEdit
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(575, 302);
            Controls.Add(cbAktivan);
            Controls.Add(label9);
            Controls.Add(cmbGradovi);
            Controls.Add(label8);
            Controls.Add(cmbDrzave);
            Controls.Add(label7);
            Controls.Add(cmbSpol);
            Controls.Add(label6);
            Controls.Add(txtLozinka);
            Controls.Add(label5);
            Controls.Add(dtpDatumRodjenja);
            Controls.Add(label3);
            Controls.Add(txtPrezime);
            Controls.Add(label4);
            Controls.Add(txtIme);
            Controls.Add(label2);
            Controls.Add(txtEmail);
            Controls.Add(label1);
            Controls.Add(txtBrojIndeksa);
            Controls.Add(btnUcitajSliku);
            Controls.Add(pbSlika);
            Controls.Add(btnSacuvaj);
            Name = "frmStudentAddEdit";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Podaci o studentu";
            Load += frmStudentAddEdit_Load;
            ((System.ComponentModel.ISupportInitialize)pbSlika).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnSacuvaj;
        private PictureBox pbSlika;
        private Button btnUcitajSliku;
        private TextBox txtBrojIndeksa;
        private Label label1;
        private Label label2;
        private TextBox txtEmail;
        private Label label3;
        private TextBox txtPrezime;
        private Label label4;
        private TextBox txtIme;
        private DateTimePicker dtpDatumRodjenja;
        private Label label5;
        private Label label6;
        private TextBox txtLozinka;
        private ComboBox cmbSpol;
        private Label label7;
        private Label label8;
        private ComboBox cmbDrzave;
        private Label label9;
        private ComboBox cmbGradovi;
        private CheckBox cbAktivan;
        private OpenFileDialog openFileDialog1;
        private ErrorProvider err;
    }
}