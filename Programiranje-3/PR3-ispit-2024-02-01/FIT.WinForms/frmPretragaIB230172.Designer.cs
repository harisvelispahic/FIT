namespace FIT.WinForms
{
    partial class frmPretragaIB230172
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
            cmbDrzave = new ComboBox();
            label1 = new Label();
            cmbGradovi = new ComboBox();
            label2 = new Label();
            dgvStudenti = new DataGridView();
            Ime = new DataGridViewTextBoxColumn();
            Id = new DataGridViewTextBoxColumn();
            Prezime = new DataGridViewTextBoxColumn();
            Grad = new DataGridViewTextBoxColumn();
            Drzava = new DataGridViewTextBoxColumn();
            Prosjek = new DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)dgvStudenti).BeginInit();
            SuspendLayout();
            // 
            // cmbDrzave
            // 
            cmbDrzave.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbDrzave.FormattingEnabled = true;
            cmbDrzave.Location = new Point(12, 35);
            cmbDrzave.Name = "cmbDrzave";
            cmbDrzave.Size = new Size(240, 23);
            cmbDrzave.TabIndex = 0;
            cmbDrzave.SelectedIndexChanged += cmbDrzave_SelectedIndexChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 17);
            label1.Name = "label1";
            label1.Size = new Size(45, 15);
            label1.TabIndex = 1;
            label1.Text = "Država:";
            // 
            // cmbGradovi
            // 
            cmbGradovi.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbGradovi.FormattingEnabled = true;
            cmbGradovi.Location = new Point(258, 35);
            cmbGradovi.Name = "cmbGradovi";
            cmbGradovi.Size = new Size(218, 23);
            cmbGradovi.TabIndex = 0;
            cmbGradovi.SelectedIndexChanged += cmbGradovi_SelectedIndexChanged;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(258, 17);
            label2.Name = "label2";
            label2.Size = new Size(35, 15);
            label2.TabIndex = 1;
            label2.Text = "Grad:";
            // 
            // dgvStudenti
            // 
            dgvStudenti.AllowUserToAddRows = false;
            dgvStudenti.AllowUserToDeleteRows = false;
            dgvStudenti.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvStudenti.Columns.AddRange(new DataGridViewColumn[] { Ime, Id, Prezime, Grad, Drzava, Prosjek });
            dgvStudenti.Location = new Point(12, 64);
            dgvStudenti.Name = "dgvStudenti";
            dgvStudenti.ReadOnly = true;
            dgvStudenti.RowTemplate.Height = 25;
            dgvStudenti.Size = new Size(776, 239);
            dgvStudenti.TabIndex = 2;
            dgvStudenti.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Ime
            // 
            Ime.DataPropertyName = "Ime";
            Ime.HeaderText = "Ime";
            Ime.Name = "Ime";
            Ime.ReadOnly = true;
            // 
            // Id
            // 
            Id.DataPropertyName = "Id";
            Id.HeaderText = "Id";
            Id.Name = "Id";
            Id.ReadOnly = true;
            Id.Visible = false;
            // 
            // Prezime
            // 
            Prezime.DataPropertyName = "Prezime";
            Prezime.HeaderText = "Prezime";
            Prezime.Name = "Prezime";
            Prezime.ReadOnly = true;
            // 
            // Grad
            // 
            Grad.DataPropertyName = "Grad";
            Grad.HeaderText = "Grad";
            Grad.Name = "Grad";
            Grad.ReadOnly = true;
            // 
            // Drzava
            // 
            Drzava.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Drzava.DataPropertyName = "Drzava";
            Drzava.HeaderText = "Drzava";
            Drzava.Name = "Drzava";
            Drzava.ReadOnly = true;
            // 
            // Prosjek
            // 
            Prosjek.DataPropertyName = "Prosjek";
            Prosjek.HeaderText = "Prosjek";
            Prosjek.Name = "Prosjek";
            Prosjek.ReadOnly = true;
            // 
            // frmPretragaIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 313);
            Controls.Add(dgvStudenti);
            Controls.Add(label2);
            Controls.Add(cmbGradovi);
            Controls.Add(label1);
            Controls.Add(cmbDrzave);
            Name = "frmPretragaIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPretragaIB230172";
            Load += frmPretragaIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dgvStudenti).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ComboBox cmbDrzave;
        private Label label1;
        private ComboBox cmbGradovi;
        private Label label2;
        private DataGridView dgvStudenti;
        private DataGridViewTextBoxColumn Ime;
        private DataGridViewTextBoxColumn Id;
        private DataGridViewTextBoxColumn Prezime;
        private DataGridViewTextBoxColumn Grad;
        private DataGridViewTextBoxColumn Drzava;
        private DataGridViewTextBoxColumn Prosjek;
    }
}