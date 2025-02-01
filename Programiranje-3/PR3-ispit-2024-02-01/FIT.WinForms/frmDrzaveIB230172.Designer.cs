namespace FIT.WinForms
{
    partial class frmDrzaveIB230172
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
            btnNovaDrzava = new Button();
            dgvDrzave = new DataGridView();
            Zastava = new DataGridViewImageColumn();
            Drzava = new DataGridViewTextBoxColumn();
            BrojGradova = new DataGridViewTextBoxColumn();
            Aktivna = new DataGridViewCheckBoxColumn();
            btnGradovi = new DataGridViewButtonColumn();
            Id = new DataGridViewTextBoxColumn();
            timer1 = new System.Windows.Forms.Timer(components);
            lblVrijeme = new Label();
            btnPrintaj = new Button();
            ((System.ComponentModel.ISupportInitialize)dgvDrzave).BeginInit();
            SuspendLayout();
            // 
            // btnNovaDrzava
            // 
            btnNovaDrzava.Location = new Point(667, 12);
            btnNovaDrzava.Name = "btnNovaDrzava";
            btnNovaDrzava.Size = new Size(121, 23);
            btnNovaDrzava.TabIndex = 0;
            btnNovaDrzava.Text = "Nova Drzava";
            btnNovaDrzava.UseVisualStyleBackColor = true;
            btnNovaDrzava.Click += btnNovaDrzava_Click;
            // 
            // dgvDrzave
            // 
            dgvDrzave.AllowUserToAddRows = false;
            dgvDrzave.AllowUserToDeleteRows = false;
            dgvDrzave.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvDrzave.Columns.AddRange(new DataGridViewColumn[] { Zastava, Drzava, BrojGradova, Aktivna, btnGradovi, Id });
            dgvDrzave.Location = new Point(12, 41);
            dgvDrzave.Name = "dgvDrzave";
            dgvDrzave.ReadOnly = true;
            dgvDrzave.RowTemplate.Height = 25;
            dgvDrzave.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvDrzave.Size = new Size(776, 242);
            dgvDrzave.TabIndex = 1;
            dgvDrzave.CellContentClick += dgvDrzave_CellContentClick;
            // 
            // Zastava
            // 
            Zastava.DataPropertyName = "Zastava";
            Zastava.HeaderText = "Zastava";
            Zastava.ImageLayout = DataGridViewImageCellLayout.Stretch;
            Zastava.Name = "Zastava";
            Zastava.ReadOnly = true;
            // 
            // Drzava
            // 
            Drzava.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Drzava.DataPropertyName = "Drzava";
            Drzava.HeaderText = "Država";
            Drzava.Name = "Drzava";
            Drzava.ReadOnly = true;
            // 
            // BrojGradova
            // 
            BrojGradova.DataPropertyName = "BrojGradova";
            BrojGradova.HeaderText = "Broj gradova";
            BrojGradova.Name = "BrojGradova";
            BrojGradova.ReadOnly = true;
            // 
            // Aktivna
            // 
            Aktivna.DataPropertyName = "Aktivna";
            Aktivna.HeaderText = "Aktivna";
            Aktivna.Name = "Aktivna";
            Aktivna.ReadOnly = true;
            // 
            // btnGradovi
            // 
            btnGradovi.HeaderText = "";
            btnGradovi.Name = "btnGradovi";
            btnGradovi.ReadOnly = true;
            btnGradovi.Text = "Gradovi";
            btnGradovi.UseColumnTextForButtonValue = true;
            // 
            // Id
            // 
            Id.DataPropertyName = "Id";
            Id.HeaderText = "Id";
            Id.Name = "Id";
            Id.ReadOnly = true;
            Id.Visible = false;
            // 
            // timer1
            // 
            timer1.Enabled = true;
            timer1.Interval = 1000;
            timer1.Tick += timer1_Tick;
            // 
            // lblVrijeme
            // 
            lblVrijeme.AutoSize = true;
            lblVrijeme.Location = new Point(12, 320);
            lblVrijeme.Name = "lblVrijeme";
            lblVrijeme.Size = new Size(38, 15);
            lblVrijeme.TabIndex = 2;
            lblVrijeme.Text = "label1";
            // 
            // btnPrintaj
            // 
            btnPrintaj.Location = new Point(667, 289);
            btnPrintaj.Name = "btnPrintaj";
            btnPrintaj.Size = new Size(121, 23);
            btnPrintaj.TabIndex = 0;
            btnPrintaj.Text = "Printaj";
            btnPrintaj.UseVisualStyleBackColor = true;
            btnPrintaj.Click += btnPrintaj_Click;
            // 
            // frmDrzaveIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 341);
            Controls.Add(lblVrijeme);
            Controls.Add(dgvDrzave);
            Controls.Add(btnPrintaj);
            Controls.Add(btnNovaDrzava);
            Name = "frmDrzaveIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Države";
            Load += frmDrzaveIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dgvDrzave).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnNovaDrzava;
        private DataGridView dgvDrzave;
        private System.Windows.Forms.Timer timer1;
        private Label lblVrijeme;
        private Button btnPrintaj;
        private DataGridViewImageColumn Zastava;
        private DataGridViewTextBoxColumn Drzava;
        private DataGridViewTextBoxColumn BrojGradova;
        private DataGridViewCheckBoxColumn Aktivna;
        private DataGridViewButtonColumn btnGradovi;
        private DataGridViewTextBoxColumn Id;
    }
}