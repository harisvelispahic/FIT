namespace FIT.WinForms.IspitIB230172
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
            btnNovaProstorija = new Button();
            dataGridView1 = new DataGridView();
            Logo = new DataGridViewImageColumn();
            Naziv = new DataGridViewTextBoxColumn();
            Oznaka = new DataGridViewTextBoxColumn();
            Kapacitet = new DataGridViewTextBoxColumn();
            BrojPredmeta = new DataGridViewTextBoxColumn();
            btnNastava = new DataGridViewButtonColumn();
            btnPrisustvo = new DataGridViewButtonColumn();
            btnPrintaj = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // btnNovaProstorija
            // 
            btnNovaProstorija.Location = new Point(739, 9);
            btnNovaProstorija.Margin = new Padding(3, 2, 3, 2);
            btnNovaProstorija.Name = "btnNovaProstorija";
            btnNovaProstorija.Size = new Size(140, 22);
            btnNovaProstorija.TabIndex = 0;
            btnNovaProstorija.Text = "Nova prostorija";
            btnNovaProstorija.UseVisualStyleBackColor = true;
            btnNovaProstorija.Click += btnNovaProstorija_Click;
            // 
            // dataGridView1
            // 
            dataGridView1.AllowUserToAddRows = false;
            dataGridView1.AllowUserToDeleteRows = false;
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { Logo, Naziv, Oznaka, Kapacitet, BrojPredmeta, btnNastava, btnPrisustvo });
            dataGridView1.Location = new Point(10, 35);
            dataGridView1.Margin = new Padding(3, 2, 3, 2);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.ReadOnly = true;
            dataGridView1.RowHeadersWidth = 51;
            dataGridView1.RowTemplate.Height = 29;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.Size = new Size(869, 178);
            dataGridView1.TabIndex = 1;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Logo
            // 
            Logo.DataPropertyName = "Logo";
            Logo.HeaderText = "Logo";
            Logo.MinimumWidth = 6;
            Logo.Name = "Logo";
            Logo.ReadOnly = true;
            Logo.Width = 125;
            // 
            // Naziv
            // 
            Naziv.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Naziv.DataPropertyName = "Naziv";
            Naziv.HeaderText = "Naziv";
            Naziv.MinimumWidth = 6;
            Naziv.Name = "Naziv";
            Naziv.ReadOnly = true;
            // 
            // Oznaka
            // 
            Oznaka.DataPropertyName = "Oznaka";
            Oznaka.HeaderText = "Oznaka";
            Oznaka.MinimumWidth = 6;
            Oznaka.Name = "Oznaka";
            Oznaka.ReadOnly = true;
            Oznaka.Width = 125;
            // 
            // Kapacitet
            // 
            Kapacitet.DataPropertyName = "Kapacitet";
            Kapacitet.HeaderText = "Kapacitet";
            Kapacitet.MinimumWidth = 6;
            Kapacitet.Name = "Kapacitet";
            Kapacitet.ReadOnly = true;
            Kapacitet.Width = 125;
            // 
            // BrojPredmeta
            // 
            BrojPredmeta.DataPropertyName = "BrojPredmeta";
            BrojPredmeta.HeaderText = "BrojPredmeta";
            BrojPredmeta.MinimumWidth = 6;
            BrojPredmeta.Name = "BrojPredmeta";
            BrojPredmeta.ReadOnly = true;
            BrojPredmeta.Width = 125;
            // 
            // btnNastava
            // 
            btnNastava.HeaderText = "";
            btnNastava.MinimumWidth = 6;
            btnNastava.Name = "btnNastava";
            btnNastava.ReadOnly = true;
            btnNastava.Text = "Nastava";
            btnNastava.UseColumnTextForButtonValue = true;
            btnNastava.Width = 125;
            // 
            // btnPrisustvo
            // 
            btnPrisustvo.HeaderText = "";
            btnPrisustvo.MinimumWidth = 6;
            btnPrisustvo.Name = "btnPrisustvo";
            btnPrisustvo.ReadOnly = true;
            btnPrisustvo.Text = "Prisustvo";
            btnPrisustvo.UseColumnTextForButtonValue = true;
            btnPrisustvo.Width = 125;
            // 
            // btnPrintaj
            // 
            btnPrintaj.Location = new Point(739, 226);
            btnPrintaj.Margin = new Padding(3, 2, 3, 2);
            btnPrintaj.Name = "btnPrintaj";
            btnPrintaj.Size = new Size(140, 22);
            btnPrintaj.TabIndex = 2;
            btnPrintaj.Text = "Printaj";
            btnPrintaj.UseVisualStyleBackColor = true;
            btnPrintaj.Click += btnPrintaj_Click;
            // 
            // frmProstorijeIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(890, 271);
            Controls.Add(btnPrintaj);
            Controls.Add(dataGridView1);
            Controls.Add(btnNovaProstorija);
            Margin = new Padding(3, 2, 3, 2);
            Name = "frmProstorijeIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Prostorije";
            Load += frmProstorijeIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private Button btnNovaProstorija;
        private DataGridView dataGridView1;
        private DataGridViewImageColumn Logo;
        private DataGridViewTextBoxColumn Naziv;
        private DataGridViewTextBoxColumn Oznaka;
        private DataGridViewTextBoxColumn Kapacitet;
        private DataGridViewTextBoxColumn BrojPredmeta;
        private DataGridViewButtonColumn btnNastava;
        private DataGridViewButtonColumn btnPrisustvo;
        private Button btnPrintaj;
    }
}