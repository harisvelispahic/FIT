namespace DLWMS.WinForms
{
    partial class frmNovaPoruka
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
            if (disposing && (components != null)) {
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
            label1 = new Label();
            cmbPredmeti = new ComboBox();
            label2 = new Label();
            dtpValidnost = new DateTimePicker();
            label3 = new Label();
            txtSadrzaj = new TextBox();
            label4 = new Label();
            pbSlika = new PictureBox();
            btnSacuvaj = new Button();
            btnOdustani = new Button();
            ofdSlika = new OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)pbSlika).BeginInit();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(110, 15);
            label1.TabIndex = 0;
            label1.Text = "Odaberite predmet:";
            // 
            // cmbPredmeti
            // 
            cmbPredmeti.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbPredmeti.FormattingEnabled = true;
            cmbPredmeti.Location = new Point(12, 27);
            cmbPredmeti.Name = "cmbPredmeti";
            cmbPredmeti.Size = new Size(200, 23);
            cmbPredmeti.TabIndex = 1;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(12, 53);
            label2.Name = "label2";
            label2.Size = new Size(117, 15);
            label2.TabIndex = 0;
            label2.Text = "Poruka je validna do:";
            // 
            // dtpValidnost
            // 
            dtpValidnost.Location = new Point(12, 71);
            dtpValidnost.Name = "dtpValidnost";
            dtpValidnost.Size = new Size(200, 23);
            dtpValidnost.TabIndex = 2;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(12, 117);
            label3.Name = "label3";
            label3.Size = new Size(87, 15);
            label3.TabIndex = 0;
            label3.Text = "Sadržaj poruke:";
            // 
            // txtSadrzaj
            // 
            txtSadrzaj.Location = new Point(12, 135);
            txtSadrzaj.Multiline = true;
            txtSadrzaj.Name = "txtSadrzaj";
            txtSadrzaj.Size = new Size(200, 185);
            txtSadrzaj.TabIndex = 3;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(228, 9);
            label4.Name = "label4";
            label4.Size = new Size(34, 15);
            label4.TabIndex = 0;
            label4.Text = "Slika:";
            // 
            // pbSlika
            // 
            pbSlika.BorderStyle = BorderStyle.FixedSingle;
            pbSlika.Location = new Point(228, 27);
            pbSlika.Name = "pbSlika";
            pbSlika.Size = new Size(255, 293);
            pbSlika.SizeMode = PictureBoxSizeMode.StretchImage;
            pbSlika.TabIndex = 4;
            pbSlika.TabStop = false;
            pbSlika.Click += pictureBox1_Click;
            // 
            // btnSacuvaj
            // 
            btnSacuvaj.Location = new Point(394, 326);
            btnSacuvaj.Name = "btnSacuvaj";
            btnSacuvaj.Size = new Size(89, 23);
            btnSacuvaj.TabIndex = 5;
            btnSacuvaj.Text = "Sačuvaj";
            btnSacuvaj.UseVisualStyleBackColor = true;
            btnSacuvaj.Click += btnSacuvaj_Click;
            // 
            // btnOdustani
            // 
            btnOdustani.Location = new Point(299, 326);
            btnOdustani.Name = "btnOdustani";
            btnOdustani.Size = new Size(89, 23);
            btnOdustani.TabIndex = 5;
            btnOdustani.Text = "Odustani";
            btnOdustani.UseVisualStyleBackColor = true;
            btnOdustani.Click += btnOdustani_Click;
            // 
            // ofdSlika
            // 
            ofdSlika.FileName = "openFileDialog1";
            // 
            // frmNovaPoruka
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(498, 356);
            Controls.Add(btnOdustani);
            Controls.Add(btnSacuvaj);
            Controls.Add(pbSlika);
            Controls.Add(txtSadrzaj);
            Controls.Add(dtpValidnost);
            Controls.Add(cmbPredmeti);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label4);
            Controls.Add(label1);
            Name = "frmNovaPoruka";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmNovaPoruka";
            Load += frmNovaPoruka_Load;
            ((System.ComponentModel.ISupportInitialize)pbSlika).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private ComboBox cmbPredmeti;
        private Label label2;
        private DateTimePicker dtpValidnost;
        private Label label3;
        private TextBox txtSadrzaj;
        private Label label4;
        private PictureBox pbSlika;
        private Button btnSacuvaj;
        private Button btnOdustani;
        private OpenFileDialog ofdSlika;
    }
}