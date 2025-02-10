namespace FIT.WinForms.IspitIB230172
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
            pictureBox1 = new PictureBox();
            lblDrzava = new Label();
            label1 = new Label();
            textBox1 = new TextBox();
            btndodaj = new Button();
            dataGridView1 = new DataGridView();
            Naziv = new DataGridViewTextBoxColumn();
            Aktivan = new DataGridViewCheckBoxColumn();
            btnStatus = new DataGridViewButtonColumn();
            err = new ErrorProvider(components);
            groupBox1 = new GroupBox();
            txtInfo = new TextBox();
            btnGenerisi = new Button();
            cbAktivni = new CheckBox();
            txtBroj = new TextBox();
            label2 = new Label();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // pictureBox1
            // 
            pictureBox1.Location = new Point(12, 12);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(160, 89);
            pictureBox1.TabIndex = 0;
            pictureBox1.TabStop = false;
            // 
            // lblDrzava
            // 
            lblDrzava.AutoSize = true;
            lblDrzava.Location = new Point(191, 45);
            lblDrzava.Name = "lblDrzava";
            lblDrzava.Size = new Size(38, 15);
            lblDrzava.TabIndex = 1;
            lblDrzava.Text = "label1";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 120);
            label1.Name = "label1";
            label1.Size = new Size(67, 15);
            label1.TabIndex = 1;
            label1.Text = "naziv grada";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(85, 117);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(319, 23);
            textBox1.TabIndex = 2;
            // 
            // btndodaj
            // 
            btndodaj.Location = new Point(410, 117);
            btndodaj.Name = "btndodaj";
            btndodaj.Size = new Size(93, 23);
            btndodaj.TabIndex = 3;
            btndodaj.Text = "dodaj";
            btndodaj.UseVisualStyleBackColor = true;
            btndodaj.Click += btndodaj_Click;
            // 
            // dataGridView1
            // 
            dataGridView1.AllowUserToAddRows = false;
            dataGridView1.AllowUserToDeleteRows = false;
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { Naziv, Aktivan, btnStatus });
            dataGridView1.Location = new Point(12, 146);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.ReadOnly = true;
            dataGridView1.RowTemplate.Height = 25;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.Size = new Size(491, 198);
            dataGridView1.TabIndex = 4;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Naziv
            // 
            Naziv.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Naziv.DataPropertyName = "Naziv";
            Naziv.HeaderText = "Naziv grada";
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
            // btnStatus
            // 
            btnStatus.HeaderText = "";
            btnStatus.Name = "btnStatus";
            btnStatus.ReadOnly = true;
            btnStatus.Text = "Promijeni status";
            btnStatus.UseColumnTextForButtonValue = true;
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
            groupBox1.Controls.Add(txtBroj);
            groupBox1.Controls.Add(label2);
            groupBox1.Location = new Point(12, 350);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(488, 185);
            groupBox1.TabIndex = 5;
            groupBox1.TabStop = false;
            groupBox1.Text = "Generator";
            // 
            // txtInfo
            // 
            txtInfo.Location = new Point(6, 48);
            txtInfo.Multiline = true;
            txtInfo.Name = "txtInfo";
            txtInfo.Size = new Size(476, 131);
            txtInfo.TabIndex = 4;
            // 
            // btnGenerisi
            // 
            btnGenerisi.Location = new Point(213, 23);
            btnGenerisi.Name = "btnGenerisi";
            btnGenerisi.Size = new Size(75, 23);
            btnGenerisi.TabIndex = 3;
            btnGenerisi.Text = "generisi";
            btnGenerisi.UseVisualStyleBackColor = true;
            btnGenerisi.Click += btnGenerisi_Click;
            // 
            // cbAktivni
            // 
            cbAktivni.AutoSize = true;
            cbAktivni.Location = new Point(146, 23);
            cbAktivni.Name = "cbAktivni";
            cbAktivni.Size = new Size(61, 19);
            cbAktivni.TabIndex = 2;
            cbAktivni.Text = "aktivni";
            cbAktivni.UseVisualStyleBackColor = true;
            // 
            // txtBroj
            // 
            txtBroj.Location = new Point(40, 19);
            txtBroj.Name = "txtBroj";
            txtBroj.Size = new Size(100, 23);
            txtBroj.TabIndex = 1;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(6, 19);
            label2.Name = "label2";
            label2.Size = new Size(28, 15);
            label2.TabIndex = 0;
            label2.Text = "Broj";
            // 
            // frmGradoviIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(512, 547);
            Controls.Add(groupBox1);
            Controls.Add(dataGridView1);
            Controls.Add(btndodaj);
            Controls.Add(textBox1);
            Controls.Add(label1);
            Controls.Add(lblDrzava);
            Controls.Add(pictureBox1);
            Name = "frmGradoviIB230172";
            Text = "frmGradoviIB230172";
            Load += frmGradoviIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pictureBox1;
        private Label lblDrzava;
        private Label label1;
        private TextBox textBox1;
        private Button btndodaj;
        private DataGridView dataGridView1;
        private DataGridViewTextBoxColumn Naziv;
        private DataGridViewCheckBoxColumn Aktivan;
        private DataGridViewButtonColumn btnStatus;
        private ErrorProvider err;
        private GroupBox groupBox1;
        private TextBox txtInfo;
        private Button btnGenerisi;
        private CheckBox cbAktivni;
        private TextBox txtBroj;
        private Label label2;
    }
}