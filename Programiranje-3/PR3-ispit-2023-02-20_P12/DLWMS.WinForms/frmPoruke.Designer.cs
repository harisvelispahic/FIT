namespace DLWMS.WinForms
{
    partial class frmPoruke
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
            lblNaslov = new Label();
            btnNovaPoruka = new Button();
            dgvPoruke = new DataGridView();
            Predmet = new DataGridViewTextBoxColumn();
            Sadrzaj = new DataGridViewTextBoxColumn();
            Slika = new DataGridViewImageColumn();
            Validnost = new DataGridViewTextBoxColumn();
            Brisi = new DataGridViewButtonColumn();
            ((System.ComponentModel.ISupportInitialize)dgvPoruke).BeginInit();
            SuspendLayout();
            // 
            // lblNaslov
            // 
            lblNaslov.AutoSize = true;
            lblNaslov.Location = new Point(12, 16);
            lblNaslov.Name = "lblNaslov";
            lblNaslov.Size = new Size(96, 15);
            lblNaslov.TabIndex = 0;
            lblNaslov.Text = "Poruke studenta ";
            // 
            // btnNovaPoruka
            // 
            btnNovaPoruka.Location = new Point(694, 12);
            btnNovaPoruka.Name = "btnNovaPoruka";
            btnNovaPoruka.Size = new Size(94, 23);
            btnNovaPoruka.TabIndex = 1;
            btnNovaPoruka.Text = "Nova poruka";
            btnNovaPoruka.UseVisualStyleBackColor = true;
            btnNovaPoruka.Click += btnNovaPoruka_Click;
            // 
            // dgvPoruke
            // 
            dgvPoruke.AllowUserToAddRows = false;
            dgvPoruke.AllowUserToDeleteRows = false;
            dgvPoruke.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvPoruke.Columns.AddRange(new DataGridViewColumn[] { Predmet, Sadrzaj, Slika, Validnost, Brisi });
            dgvPoruke.Location = new Point(12, 41);
            dgvPoruke.Name = "dgvPoruke";
            dgvPoruke.ReadOnly = true;
            dgvPoruke.RowTemplate.Height = 25;
            dgvPoruke.Size = new Size(776, 199);
            dgvPoruke.TabIndex = 2;
            dgvPoruke.CellContentClick += dgvPoruke_CellContentClick;
            // 
            // Predmet
            // 
            Predmet.HeaderText = "Predmet";
            Predmet.Name = "Predmet";
            Predmet.ReadOnly = true;
            // 
            // Sadrzaj
            // 
            Sadrzaj.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Sadrzaj.HeaderText = "Sadrzaj";
            Sadrzaj.Name = "Sadrzaj";
            Sadrzaj.ReadOnly = true;
            // 
            // Slika
            // 
            Slika.DataPropertyName = "Slika";
            Slika.HeaderText = "Slika";
            Slika.ImageLayout = DataGridViewImageCellLayout.Stretch;
            Slika.Name = "Slika";
            Slika.ReadOnly = true;
            // 
            // Validnost
            // 
            Validnost.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Validnost.HeaderText = "Validnost";
            Validnost.Name = "Validnost";
            Validnost.ReadOnly = true;
            // 
            // Brisi
            // 
            Brisi.HeaderText = "";
            Brisi.Name = "Brisi";
            Brisi.ReadOnly = true;
            Brisi.Text = "Brisi";
            Brisi.UseColumnTextForButtonValue = true;
            // 
            // frmPoruke
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 248);
            Controls.Add(dgvPoruke);
            Controls.Add(btnNovaPoruka);
            Controls.Add(lblNaslov);
            Name = "frmPoruke";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPoruke";
            Load += frmPoruke_Load;
            ((System.ComponentModel.ISupportInitialize)dgvPoruke).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblNaslov;
        private Button btnNovaPoruka;
        private DataGridView dgvPoruke;
        private DataGridViewTextBoxColumn Predmet;
        private DataGridViewTextBoxColumn Sadrzaj;
        private DataGridViewImageColumn Slika;
        private DataGridViewTextBoxColumn Validnost;
        private DataGridViewButtonColumn Brisi;
    }
}