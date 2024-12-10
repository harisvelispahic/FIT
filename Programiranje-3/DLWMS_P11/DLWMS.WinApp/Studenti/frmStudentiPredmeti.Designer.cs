namespace DLWMS.WinApp.Studenti
{
    partial class frmStudentiPredmeti
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
            dgvPolozeni = new DataGridView();
            Predmet = new DataGridViewTextBoxColumn();
            DatumPolaganja = new DataGridViewTextBoxColumn();
            Ocjena = new DataGridViewTextBoxColumn();
            cmbPredmeti = new ComboBox();
            cmbOcjene = new ComboBox();
            dtpDatumPolaganja = new DateTimePicker();
            btnDodaj = new Button();
            txtNapomena = new TextBox();
            err = new ErrorProvider(components);
            pbSlika = new PictureBox();
            lblImePrezime = new Label();
            lblIndeks = new Label();
            ((System.ComponentModel.ISupportInitialize)dgvPolozeni).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pbSlika).BeginInit();
            SuspendLayout();
            // 
            // dgvPolozeni
            // 
            dgvPolozeni.AllowUserToAddRows = false;
            dgvPolozeni.AllowUserToDeleteRows = false;
            dgvPolozeni.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvPolozeni.Columns.AddRange(new DataGridViewColumn[] { Predmet, DatumPolaganja, Ocjena });
            dgvPolozeni.Location = new Point(23, 187);
            dgvPolozeni.Name = "dgvPolozeni";
            dgvPolozeni.ReadOnly = true;
            dgvPolozeni.Size = new Size(601, 150);
            dgvPolozeni.TabIndex = 0;
            // 
            // Predmet
            // 
            Predmet.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Predmet.DataPropertyName = "Predmet";
            Predmet.HeaderText = "Predmet";
            Predmet.Name = "Predmet";
            Predmet.ReadOnly = true;
            // 
            // DatumPolaganja
            // 
            DatumPolaganja.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            DatumPolaganja.DataPropertyName = "DatumPolaganja";
            DatumPolaganja.HeaderText = "Datum polaganja";
            DatumPolaganja.Name = "DatumPolaganja";
            DatumPolaganja.ReadOnly = true;
            // 
            // Ocjena
            // 
            Ocjena.DataPropertyName = "Ocjena";
            Ocjena.HeaderText = "Ocjena";
            Ocjena.Name = "Ocjena";
            Ocjena.ReadOnly = true;
            // 
            // cmbPredmeti
            // 
            cmbPredmeti.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbPredmeti.FormattingEnabled = true;
            cmbPredmeti.Location = new Point(23, 129);
            cmbPredmeti.Name = "cmbPredmeti";
            cmbPredmeti.Size = new Size(211, 23);
            cmbPredmeti.TabIndex = 1;
            // 
            // cmbOcjene
            // 
            cmbOcjene.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbOcjene.FormattingEnabled = true;
            cmbOcjene.Items.AddRange(new object[] { "6", "7", "8", "9", "10" });
            cmbOcjene.Location = new Point(240, 129);
            cmbOcjene.Name = "cmbOcjene";
            cmbOcjene.Size = new Size(97, 23);
            cmbOcjene.TabIndex = 2;
            // 
            // dtpDatumPolaganja
            // 
            dtpDatumPolaganja.Location = new Point(343, 129);
            dtpDatumPolaganja.Name = "dtpDatumPolaganja";
            dtpDatumPolaganja.Size = new Size(200, 23);
            dtpDatumPolaganja.TabIndex = 3;
            // 
            // btnDodaj
            // 
            btnDodaj.Location = new Point(549, 129);
            btnDodaj.Name = "btnDodaj";
            btnDodaj.Size = new Size(75, 52);
            btnDodaj.TabIndex = 4;
            btnDodaj.Text = "Dodaj";
            btnDodaj.UseVisualStyleBackColor = true;
            btnDodaj.Click += btnDodaj_Click;
            // 
            // txtNapomena
            // 
            txtNapomena.Location = new Point(23, 158);
            txtNapomena.Name = "txtNapomena";
            txtNapomena.Size = new Size(520, 23);
            txtNapomena.TabIndex = 5;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // pbSlika
            // 
            pbSlika.Location = new Point(23, 12);
            pbSlika.Name = "pbSlika";
            pbSlika.Size = new Size(110, 111);
            pbSlika.SizeMode = PictureBoxSizeMode.StretchImage;
            pbSlika.TabIndex = 6;
            pbSlika.TabStop = false;
            // 
            // lblImePrezime
            // 
            lblImePrezime.AutoSize = true;
            lblImePrezime.Font = new Font("Segoe UI", 25F);
            lblImePrezime.Location = new Point(149, 12);
            lblImePrezime.Name = "lblImePrezime";
            lblImePrezime.Size = new Size(109, 46);
            lblImePrezime.TabIndex = 7;
            lblImePrezime.Text = "label1";
            // 
            // lblIndeks
            // 
            lblIndeks.AutoSize = true;
            lblIndeks.Font = new Font("Segoe UI", 15F);
            lblIndeks.Location = new Point(153, 58);
            lblIndeks.Name = "lblIndeks";
            lblIndeks.Size = new Size(65, 28);
            lblIndeks.TabIndex = 8;
            lblIndeks.Text = "label1";
            // 
            // frmStudentiPredmeti
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(649, 349);
            Controls.Add(lblIndeks);
            Controls.Add(lblImePrezime);
            Controls.Add(pbSlika);
            Controls.Add(txtNapomena);
            Controls.Add(btnDodaj);
            Controls.Add(dtpDatumPolaganja);
            Controls.Add(cmbOcjene);
            Controls.Add(cmbPredmeti);
            Controls.Add(dgvPolozeni);
            Name = "frmStudentiPredmeti";
            Text = "Polozeni predmeti";
            Load += frmStudentiPredmeti_Load;
            ((System.ComponentModel.ISupportInitialize)dgvPolozeni).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ((System.ComponentModel.ISupportInitialize)pbSlika).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView dgvPolozeni;
        private DataGridViewTextBoxColumn Predmet;
        private DataGridViewTextBoxColumn DatumPolaganja;
        private DataGridViewTextBoxColumn Ocjena;
        private ComboBox cmbPredmeti;
        private ComboBox cmbOcjene;
        private DateTimePicker dtpDatumPolaganja;
        private Button btnDodaj;
        private TextBox txtNapomena;
        private ErrorProvider err;
        private Label lblIndeks;
        private Label lblImePrezime;
        private PictureBox pbSlika;
    }
}