namespace FIT.WinForms
{
    partial class frmProstorijeIB230172
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
            dgvProstrorije = new DataGridView();
            Id = new DataGridViewTextBoxColumn();
            Logo = new DataGridViewImageColumn();
            Naziv = new DataGridViewTextBoxColumn();
            Oznaka = new DataGridViewTextBoxColumn();
            Kapacitet = new DataGridViewTextBoxColumn();
            BrojPredmeta = new DataGridViewTextBoxColumn();
            btnNastava = new DataGridViewButtonColumn();
            btnPrisustvo = new DataGridViewButtonColumn();
            btnNovaProstorija = new Button();
            btnPrintaj = new Button();
            ((System.ComponentModel.ISupportInitialize)dgvProstrorije).BeginInit();
            SuspendLayout();
            // 
            // dgvProstrorije
            // 
            dgvProstrorije.AllowUserToAddRows = false;
            dgvProstrorije.AllowUserToDeleteRows = false;
            dgvProstrorije.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvProstrorije.Columns.AddRange(new DataGridViewColumn[] { Id, Logo, Naziv, Oznaka, Kapacitet, BrojPredmeta, btnNastava, btnPrisustvo });
            dgvProstrorije.Location = new Point(12, 41);
            dgvProstrorije.Name = "dgvProstrorije";
            dgvProstrorije.ReadOnly = true;
            dgvProstrorije.RowTemplate.Height = 25;
            dgvProstrorije.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvProstrorije.Size = new Size(776, 150);
            dgvProstrorije.TabIndex = 0;
            dgvProstrorije.CellContentClick += dgvProstrorije_CellContentClick;
            // 
            // Id
            // 
            Id.DataPropertyName = "Id";
            Id.HeaderText = "Id";
            Id.Name = "Id";
            Id.ReadOnly = true;
            Id.Visible = false;
            // 
            // Logo
            // 
            Logo.DataPropertyName = "Logo";
            Logo.HeaderText = "Logo";
            Logo.ImageLayout = DataGridViewImageCellLayout.Stretch;
            Logo.Name = "Logo";
            Logo.ReadOnly = true;
            // 
            // Naziv
            // 
            Naziv.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Naziv.DataPropertyName = "Naziv";
            Naziv.HeaderText = "Naziv";
            Naziv.Name = "Naziv";
            Naziv.ReadOnly = true;
            Naziv.Resizable = DataGridViewTriState.True;
            Naziv.SortMode = DataGridViewColumnSortMode.NotSortable;
            // 
            // Oznaka
            // 
            Oznaka.DataPropertyName = "Oznaka";
            Oznaka.HeaderText = "Oznaka";
            Oznaka.Name = "Oznaka";
            Oznaka.ReadOnly = true;
            // 
            // Kapacitet
            // 
            Kapacitet.DataPropertyName = "Kapacitet";
            Kapacitet.HeaderText = "Kapacitet";
            Kapacitet.Name = "Kapacitet";
            Kapacitet.ReadOnly = true;
            // 
            // BrojPredmeta
            // 
            BrojPredmeta.DataPropertyName = "BrojPredmeta";
            BrojPredmeta.HeaderText = "Br. predmeta";
            BrojPredmeta.Name = "BrojPredmeta";
            BrojPredmeta.ReadOnly = true;
            // 
            // btnNastava
            // 
            btnNastava.HeaderText = "";
            btnNastava.Name = "btnNastava";
            btnNastava.ReadOnly = true;
            btnNastava.Text = "Nastava";
            btnNastava.UseColumnTextForButtonValue = true;
            // 
            // btnPrisustvo
            // 
            btnPrisustvo.HeaderText = "";
            btnPrisustvo.Name = "btnPrisustvo";
            btnPrisustvo.ReadOnly = true;
            btnPrisustvo.Text = "Prisustvo";
            btnPrisustvo.UseColumnTextForButtonValue = true;
            // 
            // btnNovaProstorija
            // 
            btnNovaProstorija.Location = new Point(672, 12);
            btnNovaProstorija.Name = "btnNovaProstorija";
            btnNovaProstorija.Size = new Size(116, 23);
            btnNovaProstorija.TabIndex = 1;
            btnNovaProstorija.Text = "Nova prostorija";
            btnNovaProstorija.UseVisualStyleBackColor = true;
            btnNovaProstorija.Click += btnNovaProstorija_Click;
            // 
            // btnPrintaj
            // 
            btnPrintaj.Location = new Point(672, 197);
            btnPrintaj.Name = "btnPrintaj";
            btnPrintaj.Size = new Size(116, 23);
            btnPrintaj.TabIndex = 2;
            btnPrintaj.Text = "Printaj";
            btnPrintaj.UseVisualStyleBackColor = true;
            btnPrintaj.Click += btnPrintaj_Click;
            // 
            // frmProstorijeIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 235);
            Controls.Add(btnPrintaj);
            Controls.Add(btnNovaProstorija);
            Controls.Add(dgvProstrorije);
            Name = "frmProstorijeIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmProstorijeIB230172";
            Load += frmProstorijeIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dgvProstrorije).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private DataGridView dgvProstrorije;
        private Button btnNovaProstorija;
        private Button btnPrintaj;
        private DataGridViewTextBoxColumn Id;
        private DataGridViewImageColumn Logo;
        private DataGridViewTextBoxColumn Naziv;
        private DataGridViewTextBoxColumn Oznaka;
        private DataGridViewTextBoxColumn Kapacitet;
        private DataGridViewTextBoxColumn BrojPredmeta;
        private DataGridViewButtonColumn btnNastava;
        private DataGridViewButtonColumn btnPrisustvo;
    }
}