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
            label1 = new Label();
            cmbSemestar = new ComboBox();
            label2 = new Label();
            cmbUloga = new ComboBox();
            dtpOd = new DateTimePicker();
            label3 = new Label();
            label4 = new Label();
            dtpDo = new DateTimePicker();
            dataGridView1 = new DataGridView();
            Indeks = new DataGridViewTextBoxColumn();
            ImePrezime = new DataGridViewTextBoxColumn();
            DatumRodjenja = new DataGridViewTextBoxColumn();
            Prosjek = new DataGridViewTextBoxColumn();
            Uloga = new DataGridViewTextBoxColumn();
            Aktivan = new DataGridViewCheckBoxColumn();
            btnPoruke = new DataGridViewButtonColumn();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(58, 15);
            label1.TabIndex = 0;
            label1.Text = "Semestar:";
            // 
            // cmbSemestar
            // 
            cmbSemestar.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbSemestar.FormattingEnabled = true;
            cmbSemestar.Location = new Point(76, 6);
            cmbSemestar.Name = "cmbSemestar";
            cmbSemestar.Size = new Size(121, 23);
            cmbSemestar.TabIndex = 1;
            cmbSemestar.SelectedIndexChanged += cmbSemestar_SelectedIndexChanged;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(212, 9);
            label2.Name = "label2";
            label2.Size = new Size(41, 15);
            label2.TabIndex = 0;
            label2.Text = "Uloga:";
            // 
            // cmbUloga
            // 
            cmbUloga.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbUloga.FormattingEnabled = true;
            cmbUloga.Location = new Point(259, 6);
            cmbUloga.Name = "cmbUloga";
            cmbUloga.Size = new Size(121, 23);
            cmbUloga.TabIndex = 2;
            cmbUloga.SelectedIndexChanged += cmbUloga_SelectedIndexChanged;
            // 
            // dtpOd
            // 
            dtpOd.Location = new Point(504, 6);
            dtpOd.Name = "dtpOd";
            dtpOd.Size = new Size(200, 23);
            dtpOd.TabIndex = 3;
            dtpOd.ValueChanged += dtpOd_ValueChanged;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(386, 9);
            label3.Name = "label3";
            label3.Size = new Size(112, 15);
            label3.TabIndex = 0;
            label3.Text = "rođen u periodu od:";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(710, 9);
            label4.Name = "label4";
            label4.Size = new Size(24, 15);
            label4.TabIndex = 0;
            label4.Text = "do:";
            // 
            // dtpDo
            // 
            dtpDo.Location = new Point(740, 6);
            dtpDo.Name = "dtpDo";
            dtpDo.Size = new Size(200, 23);
            dtpDo.TabIndex = 3;
            dtpDo.ValueChanged += dtpDo_ValueChanged;
            // 
            // dataGridView1
            // 
            dataGridView1.AllowUserToAddRows = false;
            dataGridView1.AllowUserToDeleteRows = false;
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { Indeks, ImePrezime, DatumRodjenja, Prosjek, Uloga, Aktivan, btnPoruke });
            dataGridView1.Location = new Point(12, 35);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.ReadOnly = true;
            dataGridView1.RowTemplate.Height = 25;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.Size = new Size(928, 317);
            dataGridView1.TabIndex = 4;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Indeks
            // 
            Indeks.DataPropertyName = "Indeks";
            Indeks.HeaderText = "Indeks";
            Indeks.Name = "Indeks";
            Indeks.ReadOnly = true;
            // 
            // ImePrezime
            // 
            ImePrezime.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            ImePrezime.DataPropertyName = "ImePrezime";
            ImePrezime.HeaderText = "Ime i prezime";
            ImePrezime.Name = "ImePrezime";
            ImePrezime.ReadOnly = true;
            // 
            // DatumRodjenja
            // 
            DatumRodjenja.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            DatumRodjenja.DataPropertyName = "DatumRodjenja";
            DatumRodjenja.HeaderText = "Datum Rođenja";
            DatumRodjenja.Name = "DatumRodjenja";
            DatumRodjenja.ReadOnly = true;
            // 
            // Prosjek
            // 
            Prosjek.DataPropertyName = "Prosjek";
            Prosjek.HeaderText = "Prosječna ocjena";
            Prosjek.Name = "Prosjek";
            Prosjek.ReadOnly = true;
            // 
            // Uloga
            // 
            Uloga.DataPropertyName = "Uloga";
            Uloga.HeaderText = "Uloga";
            Uloga.Name = "Uloga";
            Uloga.ReadOnly = true;
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
            // btnPoruke
            // 
            btnPoruke.HeaderText = "";
            btnPoruke.Name = "btnPoruke";
            btnPoruke.ReadOnly = true;
            btnPoruke.Text = "Poruke";
            btnPoruke.UseColumnTextForButtonValue = true;
            // 
            // frmPretragaIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(950, 364);
            Controls.Add(dataGridView1);
            Controls.Add(dtpDo);
            Controls.Add(dtpOd);
            Controls.Add(cmbUloga);
            Controls.Add(cmbSemestar);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "frmPretragaIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPretragaIB230172";
            Load += frmPretragaIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private ComboBox cmbSemestar;
        private Label label2;
        private ComboBox cmbUloga;
        private DateTimePicker dtpOd;
        private Label label3;
        private Label label4;
        private DateTimePicker dtpDo;
        private DataGridView dataGridView1;
        private DataGridViewTextBoxColumn Indeks;
        private DataGridViewTextBoxColumn ImePrezime;
        private DataGridViewTextBoxColumn DatumRodjenja;
        private DataGridViewTextBoxColumn Prosjek;
        private DataGridViewTextBoxColumn Uloga;
        private DataGridViewCheckBoxColumn Aktivan;
        private DataGridViewButtonColumn btnPoruke;
    }
}