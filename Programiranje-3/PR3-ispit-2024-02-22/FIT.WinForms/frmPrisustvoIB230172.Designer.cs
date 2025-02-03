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
            lblNaziv = new Label();
            lblKapacitet = new Label();
            label1 = new Label();
            cmbNastava = new ComboBox();
            cmbStudent = new ComboBox();
            label2 = new Label();
            button1 = new Button();
            dgvPrisustva = new DataGridView();
            PredmetProstorijaVrijeme = new DataGridViewTextBoxColumn();
            Student = new DataGridViewTextBoxColumn();
            groupBox1 = new GroupBox();
            label3 = new Label();
            txtBrojZapisa = new TextBox();
            btnGenerisi = new Button();
            label4 = new Label();
            txtInfo = new TextBox();
            ((System.ComponentModel.ISupportInitialize)dgvPrisustva).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // lblNaziv
            // 
            lblNaziv.AutoSize = true;
            lblNaziv.Font = new Font("Segoe UI", 20.25F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblNaziv.Location = new Point(12, 27);
            lblNaziv.Name = "lblNaziv";
            lblNaziv.Size = new Size(96, 37);
            lblNaziv.TabIndex = 0;
            lblNaziv.Text = "label1";
            // 
            // lblKapacitet
            // 
            lblKapacitet.AutoSize = true;
            lblKapacitet.Font = new Font("Segoe UI Semibold", 18F, FontStyle.Bold, GraphicsUnit.Point, 0);
            lblKapacitet.Location = new Point(622, 32);
            lblKapacitet.Name = "lblKapacitet";
            lblKapacitet.Size = new Size(76, 32);
            lblKapacitet.TabIndex = 1;
            lblKapacitet.Text = "label1";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 110);
            label1.Name = "label1";
            label1.Size = new Size(52, 15);
            label1.TabIndex = 2;
            label1.Text = "Nastava:";
            // 
            // cmbNastava
            // 
            cmbNastava.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbNastava.FormattingEnabled = true;
            cmbNastava.Location = new Point(12, 128);
            cmbNastava.Name = "cmbNastava";
            cmbNastava.Size = new Size(279, 23);
            cmbNastava.TabIndex = 3;
            cmbNastava.SelectedIndexChanged += cmbNastava_SelectedIndexChanged;
            // 
            // cmbStudent
            // 
            cmbStudent.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbStudent.FormattingEnabled = true;
            cmbStudent.Location = new Point(297, 128);
            cmbStudent.Name = "cmbStudent";
            cmbStudent.Size = new Size(297, 23);
            cmbStudent.TabIndex = 4;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(297, 110);
            label2.Name = "label2";
            label2.Size = new Size(51, 15);
            label2.TabIndex = 2;
            label2.Text = "Student:";
            // 
            // button1
            // 
            button1.Location = new Point(600, 128);
            button1.Name = "button1";
            button1.Size = new Size(98, 23);
            button1.TabIndex = 5;
            button1.Text = "Dodaj";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // dgvPrisustva
            // 
            dgvPrisustva.AllowUserToAddRows = false;
            dgvPrisustva.AllowUserToDeleteRows = false;
            dgvPrisustva.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvPrisustva.Columns.AddRange(new DataGridViewColumn[] { PredmetProstorijaVrijeme, Student });
            dgvPrisustva.Location = new Point(12, 157);
            dgvPrisustva.Name = "dgvPrisustva";
            dgvPrisustva.ReadOnly = true;
            dgvPrisustva.RowTemplate.Height = 25;
            dgvPrisustva.Size = new Size(686, 244);
            dgvPrisustva.TabIndex = 6;
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
            Student.DataPropertyName = "Student";
            Student.HeaderText = "Student";
            Student.Name = "Student";
            Student.ReadOnly = true;
            Student.Width = 321;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(txtInfo);
            groupBox1.Controls.Add(btnGenerisi);
            groupBox1.Controls.Add(txtBrojZapisa);
            groupBox1.Controls.Add(label4);
            groupBox1.Controls.Add(label3);
            groupBox1.Location = new Point(12, 407);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(686, 227);
            groupBox1.TabIndex = 7;
            groupBox1.TabStop = false;
            groupBox1.Text = "Generator";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(14, 41);
            label3.Name = "label3";
            label3.Size = new Size(66, 15);
            label3.TabIndex = 0;
            label3.Text = "Broj zapisa:";
            // 
            // txtBrojZapisa
            // 
            txtBrojZapisa.Location = new Point(86, 41);
            txtBrojZapisa.Name = "txtBrojZapisa";
            txtBrojZapisa.Size = new Size(100, 23);
            txtBrojZapisa.TabIndex = 1;
            // 
            // btnGenerisi
            // 
            btnGenerisi.Location = new Point(204, 40);
            btnGenerisi.Name = "btnGenerisi";
            btnGenerisi.Size = new Size(75, 23);
            btnGenerisi.TabIndex = 2;
            btnGenerisi.Text = "Generiši";
            btnGenerisi.UseVisualStyleBackColor = true;
            btnGenerisi.Click += btnGenerisi_Click;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(14, 94);
            label4.Name = "label4";
            label4.Size = new Size(31, 15);
            label4.TabIndex = 0;
            label4.Text = "Info:";
            // 
            // txtInfo
            // 
            txtInfo.Location = new Point(14, 112);
            txtInfo.Multiline = true;
            txtInfo.Name = "txtInfo";
            txtInfo.Size = new Size(666, 109);
            txtInfo.TabIndex = 3;
            // 
            // frmPrisustvoIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(710, 646);
            Controls.Add(groupBox1);
            Controls.Add(dgvPrisustva);
            Controls.Add(button1);
            Controls.Add(cmbStudent);
            Controls.Add(cmbNastava);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(lblKapacitet);
            Controls.Add(lblNaziv);
            Name = "frmPrisustvoIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmPrisustvoIB230172";
            Load += frmPrisustvoIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dgvPrisustva).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblNaziv;
        private Label lblKapacitet;
        private Label label1;
        private ComboBox cmbNastava;
        private ComboBox cmbStudent;
        private Label label2;
        private Button button1;
        private DataGridView dgvPrisustva;
        private DataGridViewTextBoxColumn PredmetProstorijaVrijeme;
        private DataGridViewTextBoxColumn Student;
        private GroupBox groupBox1;
        private Label label3;
        private TextBox txtInfo;
        private Button btnGenerisi;
        private TextBox txtBrojZapisa;
        private Label label4;
    }
}