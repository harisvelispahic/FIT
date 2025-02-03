namespace FIT.WinForms
{
    partial class frmNovaProstorijaIB230172
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
            components = new System.ComponentModel.Container();
            pbSlika = new PictureBox();
            label1 = new Label();
            label2 = new Label();
            txtNaziv = new TextBox();
            label3 = new Label();
            txtOznaka = new TextBox();
            txtKapacitet = new TextBox();
            label4 = new Label();
            label5 = new Label();
            btnSacuvaj = new Button();
            err = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)pbSlika).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // pbSlika
            // 
            pbSlika.BorderStyle = BorderStyle.FixedSingle;
            pbSlika.Location = new Point(12, 45);
            pbSlika.Name = "pbSlika";
            pbSlika.Size = new Size(191, 156);
            pbSlika.SizeMode = PictureBoxSizeMode.StretchImage;
            pbSlika.TabIndex = 0;
            pbSlika.TabStop = false;
            pbSlika.Click += pbSlika_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 18);
            label1.Name = "label1";
            label1.Size = new Size(37, 15);
            label1.TabIndex = 1;
            label1.Text = "Logo:";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(226, 45);
            label2.Name = "label2";
            label2.Size = new Size(39, 15);
            label2.TabIndex = 1;
            label2.Text = "Naziv:";
            // 
            // txtNaziv
            // 
            txtNaziv.Location = new Point(226, 63);
            txtNaziv.Name = "txtNaziv";
            txtNaziv.Size = new Size(235, 23);
            txtNaziv.TabIndex = 2;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(226, 117);
            label3.Name = "label3";
            label3.Size = new Size(49, 15);
            label3.TabIndex = 1;
            label3.Text = "Oznaka:";
            // 
            // txtOznaka
            // 
            txtOznaka.Location = new Point(231, 135);
            txtOznaka.Name = "txtOznaka";
            txtOznaka.Size = new Size(112, 23);
            txtOznaka.TabIndex = 3;
            // 
            // txtKapacitet
            // 
            txtKapacitet.Location = new Point(349, 135);
            txtKapacitet.Name = "txtKapacitet";
            txtKapacitet.Size = new Size(112, 23);
            txtKapacitet.TabIndex = 4;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(349, 117);
            label4.Name = "label4";
            label4.Size = new Size(49, 15);
            label4.TabIndex = 1;
            label4.Text = "Oznaka:";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(349, 117);
            label5.Name = "label5";
            label5.Size = new Size(59, 15);
            label5.TabIndex = 1;
            label5.Text = "Kapacitet:";
            // 
            // btnSacuvaj
            // 
            btnSacuvaj.Location = new Point(373, 178);
            btnSacuvaj.Name = "btnSacuvaj";
            btnSacuvaj.Size = new Size(88, 23);
            btnSacuvaj.TabIndex = 5;
            btnSacuvaj.Text = "Sačuvaj";
            btnSacuvaj.UseVisualStyleBackColor = true;
            btnSacuvaj.Click += btnSacuvaj_Click;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // frmNovaProstorijaIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(484, 231);
            Controls.Add(btnSacuvaj);
            Controls.Add(txtKapacitet);
            Controls.Add(txtOznaka);
            Controls.Add(txtNaziv);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(pbSlika);
            Name = "frmNovaProstorijaIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmNovaProstorijaIB230172";
            Load += frmNovaProstorijaIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)pbSlika).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pbSlika;
        private Label label1;
        private Label label2;
        private TextBox txtNaziv;
        private Label label3;
        private TextBox txtOznaka;
        private TextBox txtKapacitet;
        private Label label4;
        private Label label5;
        private Button btnSacuvaj;
        private ErrorProvider err;
    }
}