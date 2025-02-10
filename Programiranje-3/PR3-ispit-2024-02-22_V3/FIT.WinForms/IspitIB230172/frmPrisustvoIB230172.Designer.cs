namespace FIT.WinForms.IspitIB230172
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
            lblProstorija = new Label();
            lblKapacitet = new Label();
            label1 = new Label();
            cmbNastava = new ComboBox();
            label2 = new Label();
            cmbStudent = new ComboBox();
            btnDodaj = new Button();
            dataGridView1 = new DataGridView();
            PredmetProstorijaVrijeme = new DataGridViewTextBoxColumn();
            Student = new DataGridViewTextBoxColumn();
            groupBox1 = new GroupBox();
            txtInfo = new TextBox();
            btngenerisi = new Button();
            textBox1 = new TextBox();
            label4 = new Label();
            label3 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // lblProstorija
            // 
            lblProstorija.AutoSize = true;
            lblProstorija.Location = new Point(10, 7);
            lblProstorija.Name = "lblProstorija";
            lblProstorija.Size = new Size(38, 15);
            lblProstorija.TabIndex = 0;
            lblProstorija.Text = "label1";
            // 
            // lblKapacitet
            // 
            lblKapacitet.AutoSize = true;
            lblKapacitet.Location = new Point(646, 7);
            lblKapacitet.Name = "lblKapacitet";
            lblKapacitet.Size = new Size(38, 15);
            lblKapacitet.TabIndex = 1;
            lblKapacitet.Text = "label1";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(10, 46);
            label1.Name = "label1";
            label1.Size = new Size(49, 15);
            label1.TabIndex = 2;
            label1.Text = "Nastava";
            // 
            // cmbNastava
            // 
            cmbNastava.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbNastava.FormattingEnabled = true;
            cmbNastava.Location = new Point(10, 64);
            cmbNastava.Margin = new Padding(3, 2, 3, 2);
            cmbNastava.Name = "cmbNastava";
            cmbNastava.Size = new Size(295, 23);
            cmbNastava.TabIndex = 3;
            cmbNastava.SelectedIndexChanged += cmbNastava_SelectedIndexChanged;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(311, 46);
            label2.Name = "label2";
            label2.Size = new Size(48, 15);
            label2.TabIndex = 2;
            label2.Text = "Student";
            // 
            // cmbStudent
            // 
            cmbStudent.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbStudent.FormattingEnabled = true;
            cmbStudent.Location = new Point(311, 64);
            cmbStudent.Margin = new Padding(3, 2, 3, 2);
            cmbStudent.Name = "cmbStudent";
            cmbStudent.Size = new Size(263, 23);
            cmbStudent.TabIndex = 4;
            cmbStudent.SelectedIndexChanged += cmbStudent_SelectedIndexChanged;
            // 
            // btnDodaj
            // 
            btnDodaj.Location = new Point(578, 64);
            btnDodaj.Margin = new Padding(3, 2, 3, 2);
            btnDodaj.Name = "btnDodaj";
            btnDodaj.Size = new Size(111, 22);
            btnDodaj.TabIndex = 5;
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
            dataGridView1.Location = new Point(10, 89);
            dataGridView1.Margin = new Padding(3, 2, 3, 2);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.ReadOnly = true;
            dataGridView1.RowHeadersWidth = 51;
            dataGridView1.RowTemplate.Height = 29;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.Size = new Size(679, 161);
            dataGridView1.TabIndex = 6;
            // 
            // PredmetProstorijaVrijeme
            // 
            PredmetProstorijaVrijeme.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            PredmetProstorijaVrijeme.DataPropertyName = "PredmetProstorijaVrijeme";
            PredmetProstorijaVrijeme.HeaderText = "PredmetProstorijaVrijeme";
            PredmetProstorijaVrijeme.MinimumWidth = 6;
            PredmetProstorijaVrijeme.Name = "PredmetProstorijaVrijeme";
            PredmetProstorijaVrijeme.ReadOnly = true;
            // 
            // Student
            // 
            Student.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Student.DataPropertyName = "IndeksStudent";
            Student.HeaderText = "Student";
            Student.MinimumWidth = 6;
            Student.Name = "Student";
            Student.ReadOnly = true;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(txtInfo);
            groupBox1.Controls.Add(btngenerisi);
            groupBox1.Controls.Add(textBox1);
            groupBox1.Controls.Add(label4);
            groupBox1.Controls.Add(label3);
            groupBox1.Location = new Point(10, 255);
            groupBox1.Margin = new Padding(3, 2, 3, 2);
            groupBox1.Name = "groupBox1";
            groupBox1.Padding = new Padding(3, 2, 3, 2);
            groupBox1.Size = new Size(679, 250);
            groupBox1.TabIndex = 7;
            groupBox1.TabStop = false;
            groupBox1.Text = "Generator";
            // 
            // txtInfo
            // 
            txtInfo.Location = new Point(0, 88);
            txtInfo.Margin = new Padding(3, 2, 3, 2);
            txtInfo.Multiline = true;
            txtInfo.Name = "txtInfo";
            txtInfo.Size = new Size(674, 158);
            txtInfo.TabIndex = 3;
            // 
            // btngenerisi
            // 
            btngenerisi.Location = new Point(213, 33);
            btngenerisi.Margin = new Padding(3, 2, 3, 2);
            btngenerisi.Name = "btngenerisi";
            btngenerisi.Size = new Size(82, 22);
            btngenerisi.TabIndex = 2;
            btngenerisi.Text = "generisi";
            btngenerisi.UseVisualStyleBackColor = true;
            btngenerisi.Click += btngenerisi_Click;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(82, 34);
            textBox1.Margin = new Padding(3, 2, 3, 2);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(110, 23);
            textBox1.TabIndex = 1;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(5, 71);
            label4.Name = "label4";
            label4.Size = new Size(28, 15);
            label4.TabIndex = 0;
            label4.Text = "info";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(5, 37);
            label3.Name = "label3";
            label3.Size = new Size(63, 15);
            label3.TabIndex = 0;
            label3.Text = "broj zapisa";
            // 
            // frmPrisustvoIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(700, 512);
            Controls.Add(groupBox1);
            Controls.Add(dataGridView1);
            Controls.Add(btnDodaj);
            Controls.Add(cmbStudent);
            Controls.Add(cmbNastava);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(lblKapacitet);
            Controls.Add(lblProstorija);
            Margin = new Padding(3, 2, 3, 2);
            Name = "frmPrisustvoIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPrisustvoIB230172";
            Load += frmPrisustvoIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblProstorija;
        private Label lblKapacitet;
        private Label label1;
        private ComboBox cmbNastava;
        private Label label2;
        private ComboBox cmbStudent;
        private Button btnDodaj;
        private DataGridView dataGridView1;
        private DataGridViewTextBoxColumn PredmetProstorijaVrijeme;
        private DataGridViewTextBoxColumn Student;
        private GroupBox groupBox1;
        private TextBox txtInfo;
        private Button btngenerisi;
        private TextBox textBox1;
        private Label label4;
        private Label label3;
    }
}