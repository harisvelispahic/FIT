namespace FIT.WinForms
{
    partial class frmPrisustvoIB230172
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
            label2 = new Label();
            comboBox1 = new ComboBox();
            label3 = new Label();
            comboBox2 = new ComboBox();
            btnDodaj = new Button();
            dataGridView1 = new DataGridView();
            PredmetProstorijaVrijeme = new DataGridViewTextBoxColumn();
            Student = new DataGridViewTextBoxColumn();
            lblKapacitet = new Label();
            groupBox1 = new GroupBox();
            label4 = new Label();
            txtBrojZapisa = new TextBox();
            btnGenerisi = new Button();
            txtInfo = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(38, 15);
            label1.TabIndex = 0;
            label1.Text = "label1";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(12, 61);
            label2.Name = "label2";
            label2.Size = new Size(47, 15);
            label2.TabIndex = 0;
            label2.Text = "nastava";
            // 
            // comboBox1
            // 
            comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox1.FormattingEnabled = true;
            comboBox1.Location = new Point(12, 79);
            comboBox1.Name = "comboBox1";
            comboBox1.Size = new Size(234, 23);
            comboBox1.TabIndex = 1;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(252, 61);
            label3.Name = "label3";
            label3.Size = new Size(47, 15);
            label3.TabIndex = 0;
            label3.Text = "student";
            // 
            // comboBox2
            // 
            comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox2.FormattingEnabled = true;
            comboBox2.Location = new Point(252, 79);
            comboBox2.Name = "comboBox2";
            comboBox2.Size = new Size(266, 23);
            comboBox2.TabIndex = 2;
            // 
            // btnDodaj
            // 
            btnDodaj.Location = new Point(524, 79);
            btnDodaj.Name = "btnDodaj";
            btnDodaj.Size = new Size(108, 23);
            btnDodaj.TabIndex = 3;
            btnDodaj.Text = "Dodaj";
            btnDodaj.UseVisualStyleBackColor = true;
            btnDodaj.Click += btnDodaj_Click;
            // 
            // dataGridView1
            // 
            dataGridView1.AllowUserToAddRows = false;
            dataGridView1.AllowUserToDeleteRows = false;
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { PredmetProstorijaVrijeme, Student });
            dataGridView1.Location = new Point(12, 108);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.ReadOnly = true;
            dataGridView1.RowTemplate.Height = 25;
            dataGridView1.Size = new Size(620, 206);
            dataGridView1.TabIndex = 4;
            // 
            // PredmetProstorijaVrijeme
            // 
            PredmetProstorijaVrijeme.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            PredmetProstorijaVrijeme.DataPropertyName = "PredmetProstorijaVrijeme";
            PredmetProstorijaVrijeme.HeaderText = "Predmet, prostorija, vrijeme";
            PredmetProstorijaVrijeme.Name = "PredmetProstorijaVrijeme";
            PredmetProstorijaVrijeme.ReadOnly = true;
            // 
            // Student
            // 
            Student.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Student.DataPropertyName = "StudentIndeks";
            Student.HeaderText = "Student";
            Student.Name = "Student";
            Student.ReadOnly = true;
            // 
            // lblKapacitet
            // 
            lblKapacitet.AutoSize = true;
            lblKapacitet.Location = new Point(594, 9);
            lblKapacitet.Name = "lblKapacitet";
            lblKapacitet.Size = new Size(38, 15);
            lblKapacitet.TabIndex = 5;
            lblKapacitet.Text = "label4";
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(txtInfo);
            groupBox1.Controls.Add(btnGenerisi);
            groupBox1.Controls.Add(txtBrojZapisa);
            groupBox1.Controls.Add(label4);
            groupBox1.Location = new Point(12, 320);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(620, 193);
            groupBox1.TabIndex = 6;
            groupBox1.TabStop = false;
            groupBox1.Text = "groupBox1";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(9, 29);
            label4.Name = "label4";
            label4.Size = new Size(63, 15);
            label4.TabIndex = 0;
            label4.Text = "broj zapisa";
            // 
            // txtBrojZapisa
            // 
            txtBrojZapisa.Location = new Point(90, 26);
            txtBrojZapisa.Name = "txtBrojZapisa";
            txtBrojZapisa.Size = new Size(100, 23);
            txtBrojZapisa.TabIndex = 1;
            // 
            // btnGenerisi
            // 
            btnGenerisi.Location = new Point(212, 29);
            btnGenerisi.Name = "btnGenerisi";
            btnGenerisi.Size = new Size(75, 23);
            btnGenerisi.TabIndex = 2;
            btnGenerisi.Text = "generisi";
            btnGenerisi.UseVisualStyleBackColor = true;
            btnGenerisi.Click += btnGenerisi_Click;
            // 
            // txtInfo
            // 
            txtInfo.Location = new Point(6, 71);
            txtInfo.Multiline = true;
            txtInfo.Name = "txtInfo";
            txtInfo.Size = new Size(608, 116);
            txtInfo.TabIndex = 3;
            // 
            // frmPrisustvoIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(648, 525);
            Controls.Add(groupBox1);
            Controls.Add(lblKapacitet);
            Controls.Add(dataGridView1);
            Controls.Add(btnDodaj);
            Controls.Add(comboBox2);
            Controls.Add(comboBox1);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "frmPrisustvoIB230172";
            Text = "frmPrisustvoIB230172";
            Load += frmPrisustvoIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private ComboBox comboBox1;
        private Label label3;
        private ComboBox comboBox2;
        private Button btnDodaj;
        private DataGridView dataGridView1;
        private Label lblKapacitet;
        private DataGridViewTextBoxColumn PredmetProstorijaVrijeme;
        private DataGridViewTextBoxColumn Student;
        private GroupBox groupBox1;
        private TextBox txtInfo;
        private Button btnGenerisi;
        private TextBox txtBrojZapisa;
        private Label label4;
    }
}