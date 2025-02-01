namespace FIT.WinForms
{
    partial class frmGradoviIB230172
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
            pbZastava = new PictureBox();
            lblNazivDrzave = new Label();
            label1 = new Label();
            txtNazivGrada = new TextBox();
            btnDodaj = new Button();
            dgvGradovi = new DataGridView();
            Naziv = new DataGridViewTextBoxColumn();
            Aktivan = new DataGridViewCheckBoxColumn();
            btnPromijeniStatus = new DataGridViewButtonColumn();
            Id = new DataGridViewTextBoxColumn();
            err = new ErrorProvider(components);
            groupBox1 = new GroupBox();
            txtInfo = new TextBox();
            btnGenerisi = new Button();
            cbAktivni = new CheckBox();
            txtBrojGradova = new TextBox();
            label3 = new Label();
            label2 = new Label();
            ((System.ComponentModel.ISupportInitialize)pbZastava).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dgvGradovi).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // pbZastava
            // 
            pbZastava.Location = new Point(23, 23);
            pbZastava.Name = "pbZastava";
            pbZastava.Size = new Size(117, 67);
            pbZastava.SizeMode = PictureBoxSizeMode.StretchImage;
            pbZastava.TabIndex = 0;
            pbZastava.TabStop = false;
            // 
            // lblNazivDrzave
            // 
            lblNazivDrzave.AutoSize = true;
            lblNazivDrzave.Location = new Point(168, 43);
            lblNazivDrzave.Name = "lblNazivDrzave";
            lblNazivDrzave.Size = new Size(38, 15);
            lblNazivDrzave.TabIndex = 1;
            lblNazivDrzave.Text = "label1";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(23, 113);
            label1.Name = "label1";
            label1.Size = new Size(149, 15);
            label1.TabIndex = 1;
            label1.Text = "Unesite naziv novog grada:";
            // 
            // txtNazivGrada
            // 
            txtNazivGrada.Location = new Point(178, 110);
            txtNazivGrada.Name = "txtNazivGrada";
            txtNazivGrada.Size = new Size(225, 23);
            txtNazivGrada.TabIndex = 2;
            // 
            // btnDodaj
            // 
            btnDodaj.Location = new Point(409, 110);
            btnDodaj.Name = "btnDodaj";
            btnDodaj.Size = new Size(84, 23);
            btnDodaj.TabIndex = 3;
            btnDodaj.Text = "Dodaj";
            btnDodaj.UseVisualStyleBackColor = true;
            btnDodaj.Click += btnDodaj_Click;
            // 
            // dgvGradovi
            // 
            dgvGradovi.AllowUserToAddRows = false;
            dgvGradovi.AllowUserToDeleteRows = false;
            dgvGradovi.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvGradovi.Columns.AddRange(new DataGridViewColumn[] { Naziv, Aktivan, btnPromijeniStatus, Id });
            dgvGradovi.Location = new Point(23, 148);
            dgvGradovi.Name = "dgvGradovi";
            dgvGradovi.ReadOnly = true;
            dgvGradovi.RowTemplate.Height = 25;
            dgvGradovi.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvGradovi.Size = new Size(470, 150);
            dgvGradovi.TabIndex = 4;
            dgvGradovi.CellContentClick += dgvGradovi_CellContentClick;
            // 
            // Naziv
            // 
            Naziv.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Naziv.DataPropertyName = "Naziv";
            Naziv.HeaderText = "Naziv";
            Naziv.Name = "Naziv";
            Naziv.ReadOnly = true;
            // 
            // Aktivan
            // 
            Aktivan.DataPropertyName = "Status";
            Aktivan.HeaderText = "Aktivan";
            Aktivan.Name = "Aktivan";
            Aktivan.ReadOnly = true;
            // 
            // btnPromijeniStatus
            // 
            btnPromijeniStatus.HeaderText = "";
            btnPromijeniStatus.Name = "btnPromijeniStatus";
            btnPromijeniStatus.ReadOnly = true;
            btnPromijeniStatus.Text = "Promijeni status";
            btnPromijeniStatus.UseColumnTextForButtonValue = true;
            // 
            // Id
            // 
            Id.DataPropertyName = "Id";
            Id.HeaderText = "Id";
            Id.Name = "Id";
            Id.ReadOnly = true;
            Id.Visible = false;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(txtInfo);
            groupBox1.Controls.Add(btnGenerisi);
            groupBox1.Controls.Add(cbAktivni);
            groupBox1.Controls.Add(txtBrojGradova);
            groupBox1.Controls.Add(label3);
            groupBox1.Controls.Add(label2);
            groupBox1.Location = new Point(23, 304);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(470, 196);
            groupBox1.TabIndex = 5;
            groupBox1.TabStop = false;
            groupBox1.Text = "Generator";
            // 
            // txtInfo
            // 
            txtInfo.Location = new Point(6, 62);
            txtInfo.Multiline = true;
            txtInfo.Name = "txtInfo";
            txtInfo.Size = new Size(458, 128);
            txtInfo.TabIndex = 4;
            // 
            // btnGenerisi
            // 
            btnGenerisi.Location = new Point(277, 16);
            btnGenerisi.Name = "btnGenerisi";
            btnGenerisi.Size = new Size(80, 23);
            btnGenerisi.TabIndex = 3;
            btnGenerisi.Text = "Generiši";
            btnGenerisi.UseVisualStyleBackColor = true;
            btnGenerisi.Click += btnGenerisi_Click;
            // 
            // cbAktivni
            // 
            cbAktivni.AutoSize = true;
            cbAktivni.Location = new Point(198, 18);
            cbAktivni.Name = "cbAktivni";
            cbAktivni.Size = new Size(63, 19);
            cbAktivni.TabIndex = 2;
            cbAktivni.Text = "Aktivni";
            cbAktivni.UseVisualStyleBackColor = true;
            // 
            // txtBrojGradova
            // 
            txtBrojGradova.Location = new Point(92, 16);
            txtBrojGradova.Name = "txtBrojGradova";
            txtBrojGradova.Size = new Size(100, 23);
            txtBrojGradova.TabIndex = 1;
            txtBrojGradova.TextChanged += textBox1_TextChanged;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(6, 44);
            label3.Name = "label3";
            label3.Size = new Size(31, 15);
            label3.TabIndex = 0;
            label3.Text = "Info:";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(6, 19);
            label2.Name = "label2";
            label2.Size = new Size(80, 15);
            label2.TabIndex = 0;
            label2.Text = "Broj gradova: ";
            // 
            // frmGradoviIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(505, 508);
            Controls.Add(groupBox1);
            Controls.Add(dgvGradovi);
            Controls.Add(btnDodaj);
            Controls.Add(txtNazivGrada);
            Controls.Add(label1);
            Controls.Add(lblNazivDrzave);
            Controls.Add(pbZastava);
            Name = "frmGradoviIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmGradoviIB230172";
            Load += frmGradoviIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)pbZastava).EndInit();
            ((System.ComponentModel.ISupportInitialize)dgvGradovi).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pbZastava;
        private Label lblNazivDrzave;
        private Label label1;
        private TextBox txtNazivGrada;
        private Button btnDodaj;
        private DataGridView dgvGradovi;
        private ErrorProvider err;
        private DataGridViewTextBoxColumn Naziv;
        private DataGridViewCheckBoxColumn Aktivan;
        private DataGridViewButtonColumn btnPromijeniStatus;
        private DataGridViewTextBoxColumn Id;
        private GroupBox groupBox1;
        private TextBox txtBrojGradova;
        private Label label2;
        private Button btnGenerisi;
        private CheckBox cbAktivni;
        private TextBox txtInfo;
        private Label label3;
    }
}