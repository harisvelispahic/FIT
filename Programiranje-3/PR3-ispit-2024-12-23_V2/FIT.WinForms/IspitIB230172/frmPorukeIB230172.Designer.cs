namespace FIT.WinForms.IspitIB230172
{
    partial class frmPorukeIB230172
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
            btnNova = new Button();
            lblStudent = new Label();
            dataGridView1 = new DataGridView();
            Predmet = new DataGridViewTextBoxColumn();
            Sadrzaj = new DataGridViewTextBoxColumn();
            Slika = new DataGridViewImageColumn();
            Hitnost = new DataGridViewTextBoxColumn();
            Validnost = new DataGridViewTextBoxColumn();
            btnBrisi = new DataGridViewButtonColumn();
            btnPrintaj = new Button();
            groupBox1 = new GroupBox();
            txtInfo = new TextBox();
            btnDodaj = new Button();
            dateTimePicker1 = new DateTimePicker();
            cmbPredmet = new ComboBox();
            txtBrojPoruka = new TextBox();
            label3 = new Label();
            label2 = new Label();
            label1 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // btnNova
            // 
            btnNova.Location = new Point(677, 12);
            btnNova.Name = "btnNova";
            btnNova.Size = new Size(111, 23);
            btnNova.TabIndex = 0;
            btnNova.Text = "Nova poruka";
            btnNova.UseVisualStyleBackColor = true;
            btnNova.Click += btnNova_Click;
            // 
            // lblStudent
            // 
            lblStudent.AutoSize = true;
            lblStudent.Location = new Point(12, 9);
            lblStudent.Name = "lblStudent";
            lblStudent.Size = new Size(38, 15);
            lblStudent.TabIndex = 1;
            lblStudent.Text = "label1";
            // 
            // dataGridView1
            // 
            dataGridView1.AllowUserToAddRows = false;
            dataGridView1.AllowUserToDeleteRows = false;
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { Predmet, Sadrzaj, Slika, Hitnost, Validnost, btnBrisi });
            dataGridView1.Location = new Point(12, 41);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.ReadOnly = true;
            dataGridView1.RowTemplate.Height = 25;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.Size = new Size(776, 258);
            dataGridView1.TabIndex = 2;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Predmet
            // 
            Predmet.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Predmet.DataPropertyName = "PredmetNaziv";
            Predmet.HeaderText = "Predmet";
            Predmet.Name = "Predmet";
            Predmet.ReadOnly = true;
            // 
            // Sadrzaj
            // 
            Sadrzaj.DataPropertyName = "Sadrzaj";
            Sadrzaj.HeaderText = "Sadrzaj";
            Sadrzaj.Name = "Sadrzaj";
            Sadrzaj.ReadOnly = true;
            // 
            // Slika
            // 
            Slika.DataPropertyName = "Slika";
            Slika.HeaderText = "Slika";
            Slika.Name = "Slika";
            Slika.ReadOnly = true;
            // 
            // Hitnost
            // 
            Hitnost.DataPropertyName = "Hitnost";
            Hitnost.HeaderText = "Hitnost";
            Hitnost.Name = "Hitnost";
            Hitnost.ReadOnly = true;
            // 
            // Validnost
            // 
            Validnost.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Validnost.DataPropertyName = "Validnost";
            Validnost.HeaderText = "Validnost";
            Validnost.Name = "Validnost";
            Validnost.ReadOnly = true;
            // 
            // btnBrisi
            // 
            btnBrisi.HeaderText = "";
            btnBrisi.Name = "btnBrisi";
            btnBrisi.ReadOnly = true;
            btnBrisi.Resizable = DataGridViewTriState.True;
            btnBrisi.SortMode = DataGridViewColumnSortMode.Automatic;
            btnBrisi.Text = "Brisi";
            btnBrisi.UseColumnTextForButtonValue = true;
            // 
            // btnPrintaj
            // 
            btnPrintaj.Location = new Point(713, 305);
            btnPrintaj.Name = "btnPrintaj";
            btnPrintaj.Size = new Size(75, 23);
            btnPrintaj.TabIndex = 3;
            btnPrintaj.Text = "Printaj";
            btnPrintaj.UseVisualStyleBackColor = true;
            btnPrintaj.Click += btnPrintaj_Click;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(txtInfo);
            groupBox1.Controls.Add(btnDodaj);
            groupBox1.Controls.Add(dateTimePicker1);
            groupBox1.Controls.Add(cmbPredmet);
            groupBox1.Controls.Add(txtBrojPoruka);
            groupBox1.Controls.Add(label3);
            groupBox1.Controls.Add(label2);
            groupBox1.Controls.Add(label1);
            groupBox1.Location = new Point(12, 355);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(776, 221);
            groupBox1.TabIndex = 4;
            groupBox1.TabStop = false;
            groupBox1.Text = "groupBox1";
            groupBox1.Enter += groupBox1_Enter;
            // 
            // txtInfo
            // 
            txtInfo.Location = new Point(225, 48);
            txtInfo.Multiline = true;
            txtInfo.Name = "txtInfo";
            txtInfo.Size = new Size(551, 150);
            txtInfo.TabIndex = 5;
            // 
            // btnDodaj
            // 
            btnDodaj.Enabled = false;
            btnDodaj.Location = new Point(15, 175);
            btnDodaj.Name = "btnDodaj";
            btnDodaj.Size = new Size(200, 23);
            btnDodaj.TabIndex = 4;
            btnDodaj.Text = "dodaj";
            btnDodaj.UseVisualStyleBackColor = true;
            btnDodaj.Click += btnDodaj_Click;
            // 
            // dateTimePicker1
            // 
            dateTimePicker1.Location = new Point(15, 136);
            dateTimePicker1.Name = "dateTimePicker1";
            dateTimePicker1.Size = new Size(200, 23);
            dateTimePicker1.TabIndex = 3;
            // 
            // cmbPredmet
            // 
            cmbPredmet.FormattingEnabled = true;
            cmbPredmet.Location = new Point(15, 92);
            cmbPredmet.Name = "cmbPredmet";
            cmbPredmet.Size = new Size(200, 23);
            cmbPredmet.TabIndex = 2;
            // 
            // txtBrojPoruka
            // 
            txtBrojPoruka.Location = new Point(15, 48);
            txtBrojPoruka.Name = "txtBrojPoruka";
            txtBrojPoruka.Size = new Size(200, 23);
            txtBrojPoruka.TabIndex = 1;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(15, 118);
            label3.Name = "label3";
            label3.Size = new Size(62, 15);
            label3.TabIndex = 0;
            label3.Text = "validna do";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(225, 30);
            label2.Name = "label2";
            label2.Size = new Size(28, 15);
            label2.TabIndex = 0;
            label2.Text = "info";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(15, 30);
            label1.Name = "label1";
            label1.Size = new Size(68, 15);
            label1.TabIndex = 0;
            label1.Text = "broj poruka";
            // 
            // frmPorukeIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 588);
            Controls.Add(groupBox1);
            Controls.Add(btnPrintaj);
            Controls.Add(dataGridView1);
            Controls.Add(lblStudent);
            Controls.Add(btnNova);
            Name = "frmPorukeIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPorukeIB230172";
            Load += frmPorukeIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnNova;
        private Label lblStudent;
        private DataGridView dataGridView1;
        private DataGridViewTextBoxColumn Predmet;
        private DataGridViewTextBoxColumn Sadrzaj;
        private DataGridViewImageColumn Slika;
        private DataGridViewTextBoxColumn Hitnost;
        private DataGridViewTextBoxColumn Validnost;
        private DataGridViewButtonColumn btnBrisi;
        private Button btnPrintaj;
        private GroupBox groupBox1;
        private Button btnDodaj;
        private DateTimePicker dateTimePicker1;
        private ComboBox cmbPredmet;
        private TextBox txtBrojPoruka;
        private Label label3;
        private Label label2;
        private Label label1;
        private TextBox txtInfo;
    }
}