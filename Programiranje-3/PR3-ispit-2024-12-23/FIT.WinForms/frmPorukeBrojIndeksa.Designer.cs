namespace FIT.WinForms
{
    partial class frmPorukeBrojIndeksa
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
            dataGridView1 = new DataGridView();
            Predmet = new DataGridViewTextBoxColumn();
            Sadrzaj = new DataGridViewTextBoxColumn();
            Slika = new DataGridViewImageColumn();
            Hitnost = new DataGridViewTextBoxColumn();
            Validnost = new DataGridViewTextBoxColumn();
            btnBrisi = new DataGridViewButtonColumn();
            btnNovaPoruka = new Button();
            label1 = new Label();
            groupBox1 = new GroupBox();
            btnDodaj = new Button();
            textBox2 = new TextBox();
            dateTimePicker1 = new DateTimePicker();
            cmbPredmet = new ComboBox();
            txtBrojPoruka = new TextBox();
            label4 = new Label();
            label3 = new Label();
            label5 = new Label();
            label2 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
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
            dataGridView1.Size = new Size(776, 278);
            dataGridView1.TabIndex = 5;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Predmet
            // 
            Predmet.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Predmet.DataPropertyName = "NazivPredmeta";
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
            Slika.Resizable = DataGridViewTriState.True;
            Slika.SortMode = DataGridViewColumnSortMode.Automatic;
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
            btnBrisi.Text = "Brisi";
            btnBrisi.UseColumnTextForButtonValue = true;
            // 
            // btnNovaPoruka
            // 
            btnNovaPoruka.Location = new Point(688, 12);
            btnNovaPoruka.Name = "btnNovaPoruka";
            btnNovaPoruka.Size = new Size(100, 23);
            btnNovaPoruka.TabIndex = 4;
            btnNovaPoruka.Text = "Nova poruka";
            btnNovaPoruka.UseVisualStyleBackColor = true;
            btnNovaPoruka.Click += btnNovaPoruka_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(27, 15);
            label1.TabIndex = 3;
            label1.Text = "ime";
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(btnDodaj);
            groupBox1.Controls.Add(textBox2);
            groupBox1.Controls.Add(dateTimePicker1);
            groupBox1.Controls.Add(cmbPredmet);
            groupBox1.Controls.Add(txtBrojPoruka);
            groupBox1.Controls.Add(label4);
            groupBox1.Controls.Add(label3);
            groupBox1.Controls.Add(label5);
            groupBox1.Controls.Add(label2);
            groupBox1.Location = new Point(12, 325);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(776, 219);
            groupBox1.TabIndex = 6;
            groupBox1.TabStop = false;
            groupBox1.Text = "Dodavanje poruka:";
            // 
            // btnDodaj
            // 
            btnDodaj.Enabled = false;
            btnDodaj.Location = new Point(6, 167);
            btnDodaj.Name = "btnDodaj";
            btnDodaj.Size = new Size(200, 23);
            btnDodaj.TabIndex = 5;
            btnDodaj.Text = "Dodaj =>";
            btnDodaj.UseVisualStyleBackColor = true;
            btnDodaj.Click += btnDodaj_Click;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(212, 50);
            textBox2.Multiline = true;
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(558, 140);
            textBox2.TabIndex = 4;
            // 
            // dateTimePicker1
            // 
            dateTimePicker1.Location = new Point(6, 138);
            dateTimePicker1.Name = "dateTimePicker1";
            dateTimePicker1.Size = new Size(200, 23);
            dateTimePicker1.TabIndex = 3;
            // 
            // cmbPredmet
            // 
            cmbPredmet.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbPredmet.FormattingEnabled = true;
            cmbPredmet.Location = new Point(6, 94);
            cmbPredmet.Name = "cmbPredmet";
            cmbPredmet.Size = new Size(200, 23);
            cmbPredmet.TabIndex = 2;
            // 
            // txtBrojPoruka
            // 
            txtBrojPoruka.Location = new Point(6, 50);
            txtBrojPoruka.Name = "txtBrojPoruka";
            txtBrojPoruka.Size = new Size(200, 23);
            txtBrojPoruka.TabIndex = 1;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(6, 120);
            label4.Name = "label4";
            label4.Size = new Size(117, 15);
            label4.TabIndex = 0;
            label4.Text = "Poruka je validna do:";
            label4.Click += label2_Click;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(6, 76);
            label3.Name = "label3";
            label3.Size = new Size(55, 15);
            label3.TabIndex = 0;
            label3.Text = "Predmet:";
            label3.Click += label2_Click;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(212, 32);
            label5.Name = "label5";
            label5.Size = new Size(31, 15);
            label5.TabIndex = 0;
            label5.Text = "Info:";
            label5.Click += label2_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(6, 32);
            label2.Name = "label2";
            label2.Size = new Size(71, 15);
            label2.TabIndex = 0;
            label2.Text = "Broj poruka:";
            label2.Click += label2_Click;
            // 
            // frmPorukeBrojIndeksa
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 556);
            Controls.Add(groupBox1);
            Controls.Add(dataGridView1);
            Controls.Add(btnNovaPoruka);
            Controls.Add(label1);
            Name = "frmPorukeBrojIndeksa";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPorukeBrojIndeksa";
            Load += frmPorukeBrojIndeksa_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView dataGridView1;
        private DataGridViewTextBoxColumn Predmet;
        private DataGridViewTextBoxColumn Sadrzaj;
        private DataGridViewImageColumn Slika;
        private DataGridViewTextBoxColumn Hitnost;
        private DataGridViewTextBoxColumn Validnost;
        private DataGridViewButtonColumn btnBrisi;
        private Button btnNovaPoruka;
        private Label label1;
        private GroupBox groupBox1;
        private ComboBox cmbPredmet;
        private TextBox txtBrojPoruka;
        private Label label2;
        private Button btnDodaj;
        private TextBox textBox2;
        private DateTimePicker dateTimePicker1;
        private Label label4;
        private Label label3;
        private Label label5;
    }
}