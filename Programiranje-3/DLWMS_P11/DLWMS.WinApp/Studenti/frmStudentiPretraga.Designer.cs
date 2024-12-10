namespace DLWMS.WinApp.Studenti
{
    partial class frmStudentiPretraga
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
            dgvStudenti = new DataGridView();
            btnDodajStudenta = new Button();
            txtFilter = new TextBox();
            BrojIndeksa = new DataGridViewTextBoxColumn();
            Ime = new DataGridViewTextBoxColumn();
            Prezime = new DataGridViewTextBoxColumn();
            DatumRodjenja = new DataGridViewTextBoxColumn();
            Email = new DataGridViewTextBoxColumn();
            Aktivan = new DataGridViewCheckBoxColumn();
            Predmeti = new DataGridViewButtonColumn();
            btnDodajStudenta = new Button();
            txtFilter = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dgvStudenti).BeginInit();
            SuspendLayout();
            // 
            // dgvStudenti
            // 
            dgvStudenti.AllowUserToAddRows = false;
            dgvStudenti.AllowUserToDeleteRows = false;
            dgvStudenti.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvStudenti.Columns.AddRange(new DataGridViewColumn[] { BrojIndeksa, Ime, Prezime, DatumRodjenja, Email, Aktivan, Predmeti });
            dgvStudenti.Location = new Point(12, 47);
            dgvStudenti.Name = "dgvStudenti";
            dgvStudenti.ReadOnly = true;
            dgvStudenti.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvStudenti.Size = new Size(776, 235);
            dgvStudenti.TabIndex = 0;
            dgvStudenti.CellContentClick += dgvStudenti_CellContentClick;
            // 
            // btnDodajStudenta
            // 
            btnDodajStudenta.Location = new Point(681, 18);
            btnDodajStudenta.Name = "btnDodajStudenta";
            btnDodajStudenta.Size = new Size(107, 23);
            btnDodajStudenta.TabIndex = 1;
            btnDodajStudenta.Text = "Dodaj studenta";
            btnDodajStudenta.UseVisualStyleBackColor = true;
            btnDodajStudenta.Click += btnDodajStudenta_Click;
            // 
            // txtFilter
            // 
            txtFilter.Location = new Point(12, 18);
            txtFilter.Name = "txtFilter";
            txtFilter.Size = new Size(663, 23);
            txtFilter.TabIndex = 2;
            txtFilter.TextChanged += txtFilter_TextChanged;
            // 
            // BrojIndeksa
            // 
            BrojIndeksa.DataPropertyName = "BrojIndeksa";
            BrojIndeksa.HeaderText = "Broj indeksa";
            BrojIndeksa.Name = "BrojIndeksa";
            BrojIndeksa.ReadOnly = true;
            // 
            // Ime
            // 
            Ime.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Ime.DataPropertyName = "Ime";
            Ime.HeaderText = "Ime";
            Ime.Name = "Ime";
            Ime.ReadOnly = true;
            // 
            // Prezime
            // 
            Prezime.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Prezime.DataPropertyName = "Prezime";
            Prezime.HeaderText = "Prezime";
            Prezime.Name = "Prezime";
            Prezime.ReadOnly = true;
            // 
            // DatumRodjenja
            // 
            DatumRodjenja.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            DatumRodjenja.DataPropertyName = "DatumRodjenja";
            DatumRodjenja.HeaderText = "Datum rođenja";
            DatumRodjenja.Name = "DatumRodjenja";
            DatumRodjenja.ReadOnly = true;
            // 
            // Email
            // 
            Email.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Email.DataPropertyName = "Email";
            Email.HeaderText = "Email";
            Email.Name = "Email";
            Email.ReadOnly = true;
            // 
            // Aktivan
            // 
            Aktivan.DataPropertyName = "Aktivan";
            Aktivan.HeaderText = "Aktivan";
            Aktivan.Name = "Aktivan";
            Aktivan.ReadOnly = true;
            Aktivan.Resizable = DataGridViewTriState.True;
            Aktivan.SortMode = DataGridViewColumnSortMode.Automatic;
            // 
            // Predmeti
            // 
            Predmeti.HeaderText = "Predmeti";
            Predmeti.Name = "Predmeti";
            Predmeti.ReadOnly = true;
            Predmeti.Resizable = DataGridViewTriState.True;
            Predmeti.SortMode = DataGridViewColumnSortMode.Automatic;
            Predmeti.Text = "Predmeti";
            Predmeti.UseColumnTextForButtonValue = true;
            // 
            // txtFilter
            // 
            txtFilter.Location = new Point(12, 18);
            txtFilter.Name = "txtFilter";
            txtFilter.Size = new Size(663, 23);
            txtFilter.TabIndex = 2;
            txtFilter.TextChanged += txtFilter_TextChanged;
            // 
            // frmStudentiPretraga
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 297);
            Controls.Add(txtFilter);
            Controls.Add(btnDodajStudenta);
            Controls.Add(dgvStudenti);
            Name = "frmStudentiPretraga";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Pretraga studenata";
            Load += frmStudentiPretraga_Load;
            ((System.ComponentModel.ISupportInitialize)dgvStudenti).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView dgvStudenti;
        private Button btnDodajStudenta;
        private TextBox txtFilter;
        private DataGridViewTextBoxColumn BrojIndeksa;
        private DataGridViewTextBoxColumn Ime;
        private DataGridViewTextBoxColumn Prezime;
        private DataGridViewTextBoxColumn DatumRodjenja;
        private DataGridViewTextBoxColumn Email;
        private DataGridViewCheckBoxColumn Aktivan;
        private DataGridViewButtonColumn Predmeti ;


    }
}