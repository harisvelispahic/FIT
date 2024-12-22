namespace DLWMS.WinForms
{
    partial class frmPretraga
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
            label1 = new Label();
            label2 = new Label();
            cmbOcjenaOd = new ComboBox();
            cmbOcjenaDo = new ComboBox();
            label3 = new Label();
            label4 = new Label();
            dtpPolozenaOd = new DateTimePicker();
            dtpPolozenaDo = new DateTimePicker();
            dgvStudentiPredmeti = new DataGridView();
            err = new ErrorProvider(components);
            Indeks = new DataGridViewTextBoxColumn();
            ImeIPrezime = new DataGridViewTextBoxColumn();
            Predmet = new DataGridViewTextBoxColumn();
            Ocjena = new DataGridViewTextBoxColumn();
            DatumPolaganja = new DataGridViewTextBoxColumn();
            poruke = new DataGridViewButtonColumn();
            ((System.ComponentModel.ISupportInitialize)dgvStudentiPredmeti).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 23);
            label1.Name = "label1";
            label1.Size = new Size(64, 15);
            label1.TabIndex = 0;
            label1.Text = "Ocjena od:";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(151, 23);
            label2.Name = "label2";
            label2.Size = new Size(24, 15);
            label2.TabIndex = 0;
            label2.Text = "do:";
            // 
            // cmbOcjenaOd
            // 
            cmbOcjenaOd.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbOcjenaOd.FormattingEnabled = true;
            cmbOcjenaOd.Location = new Point(82, 20);
            cmbOcjenaOd.Name = "cmbOcjenaOd";
            cmbOcjenaOd.Size = new Size(63, 23);
            cmbOcjenaOd.TabIndex = 1;
            cmbOcjenaOd.SelectedIndexChanged += cmbOcjenaOd_SelectedIndexChanged;
            // 
            // cmbOcjenaDo
            // 
            cmbOcjenaDo.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbOcjenaDo.FormattingEnabled = true;
            cmbOcjenaDo.Location = new Point(181, 20);
            cmbOcjenaDo.Name = "cmbOcjenaDo";
            cmbOcjenaDo.Size = new Size(62, 23);
            cmbOcjenaDo.TabIndex = 1;
            cmbOcjenaDo.SelectedIndexChanged += cmbOcjenaDo_SelectedIndexChanged;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(268, 23);
            label3.Name = "label3";
            label3.Size = new Size(129, 15);
            label3.TabIndex = 0;
            label3.Text = "položena u periodu od:";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(609, 23);
            label4.Name = "label4";
            label4.Size = new Size(24, 15);
            label4.TabIndex = 0;
            label4.Text = "do:";
            // 
            // dtpPolozenaOd
            // 
            dtpPolozenaOd.Location = new Point(403, 20);
            dtpPolozenaOd.Name = "dtpPolozenaOd";
            dtpPolozenaOd.Size = new Size(200, 23);
            dtpPolozenaOd.TabIndex = 2;
            dtpPolozenaOd.ValueChanged += dtpPolozenaOd_ValueChanged;
            // 
            // dtpPolozenaDo
            // 
            dtpPolozenaDo.Location = new Point(639, 20);
            dtpPolozenaDo.Name = "dtpPolozenaDo";
            dtpPolozenaDo.Size = new Size(200, 23);
            dtpPolozenaDo.TabIndex = 2;
            dtpPolozenaDo.ValueChanged += dtpPolozenaDo_ValueChanged;
            // 
            // dgvStudentiPredmeti
            // 
            dgvStudentiPredmeti.AllowUserToAddRows = false;
            dgvStudentiPredmeti.AllowUserToDeleteRows = false;
            dgvStudentiPredmeti.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvStudentiPredmeti.Columns.AddRange(new DataGridViewColumn[] { Indeks, ImeIPrezime, Predmet, Ocjena, DatumPolaganja, poruke });
            dgvStudentiPredmeti.Location = new Point(12, 49);
            dgvStudentiPredmeti.Name = "dgvStudentiPredmeti";
            dgvStudentiPredmeti.ReadOnly = true;
            dgvStudentiPredmeti.RowTemplate.Height = 25;
            dgvStudentiPredmeti.Size = new Size(827, 177);
            dgvStudentiPredmeti.TabIndex = 3;
            dgvStudentiPredmeti.CellContentClick += dgvStudentiPredmeti_CellContentClick;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // Indeks
            // 
            Indeks.DataPropertyName = "Indeks";
            Indeks.HeaderText = "Indeks";
            Indeks.Name = "Indeks";
            Indeks.ReadOnly = true;
            // 
            // ImeIPrezime
            // 
            ImeIPrezime.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            ImeIPrezime.DataPropertyName = "ImeIPrezime";
            ImeIPrezime.HeaderText = "Ime i prezime";
            ImeIPrezime.Name = "ImeIPrezime";
            ImeIPrezime.ReadOnly = true;
            // 
            // Predmet
            // 
            Predmet.HeaderText = "Predmet";
            Predmet.Name = "Predmet";
            Predmet.ReadOnly = true;
            // 
            // Ocjena
            // 
            Ocjena.DataPropertyName = "Ocjena";
            Ocjena.HeaderText = "Ocjena";
            Ocjena.Name = "Ocjena";
            Ocjena.ReadOnly = true;
            // 
            // DatumPolaganja
            // 
            DatumPolaganja.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            DatumPolaganja.DataPropertyName = "DatumPolaganja";
            DatumPolaganja.HeaderText = "Datum polaganja";
            DatumPolaganja.Name = "DatumPolaganja";
            DatumPolaganja.ReadOnly = true;
            // 
            // poruke
            // 
            poruke.DataPropertyName = "Poruke";
            poruke.HeaderText = "Poruke";
            poruke.Name = "poruke";
            poruke.ReadOnly = true;
            poruke.Text = "Poruke";
            poruke.UseColumnTextForButtonValue = true;
            // 
            // frmPretraga
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(854, 242);
            Controls.Add(dgvStudentiPredmeti);
            Controls.Add(dtpPolozenaDo);
            Controls.Add(dtpPolozenaOd);
            Controls.Add(cmbOcjenaDo);
            Controls.Add(cmbOcjenaOd);
            Controls.Add(label3);
            Controls.Add(label4);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "frmPretraga";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPretragaBrojIndeksa";
            Load += frmPretragaBrojIndeksa_Load;
            ((System.ComponentModel.ISupportInitialize)dgvStudentiPredmeti).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private ComboBox cmbOcjenaOd;
        private ComboBox cmbOcjenaDo;
        private Label label3;
        private Label label4;
        private DateTimePicker dtpPolozenaOd;
        private DateTimePicker dtpPolozenaDo;
        private DataGridView dgvStudentiPredmeti;
        private ErrorProvider err;
        private DataGridViewTextBoxColumn Indeks;
        private DataGridViewTextBoxColumn ImeIPrezime;
        private DataGridViewTextBoxColumn Predmet;
        private DataGridViewTextBoxColumn Ocjena;
        private DataGridViewTextBoxColumn DatumPolaganja;
        private DataGridViewButtonColumn poruke;
    }
}