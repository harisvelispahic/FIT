namespace FIT.WinForms
{
    partial class frnGradoviIB230172
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
            lblZemlja = new Label();
            txtNazivGrada = new TextBox();
            btnDodaj = new Button();
            dataGridView1 = new DataGridView();
            Naziv = new DataGridViewTextBoxColumn();
            Status = new DataGridViewCheckBoxColumn();
            btnPS = new DataGridViewButtonColumn();
            groupBox1 = new GroupBox();
            txtInfo = new TextBox();
            btnGenerisi = new Button();
            checkBox1 = new CheckBox();
            txtBrojGradova = new TextBox();
            label1 = new Label();
            label2 = new Label();
            err = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // pictureBox1
            // 
            pictureBox1.Location = new Point(12, 12);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(152, 90);
            pictureBox1.TabIndex = 0;
            pictureBox1.TabStop = false;
            // 
            // lblZemlja
            // 
            lblZemlja.AutoSize = true;
            lblZemlja.Location = new Point(194, 41);
            lblZemlja.Name = "lblZemlja";
            lblZemlja.Size = new Size(38, 15);
            lblZemlja.TabIndex = 1;
            lblZemlja.Text = "label1";
            // 
            // txtNazivGrada
            // 
            txtNazivGrada.Location = new Point(12, 121);
            txtNazivGrada.Name = "txtNazivGrada";
            txtNazivGrada.Size = new Size(249, 23);
            txtNazivGrada.TabIndex = 2;
            // 
            // btnDodaj
            // 
            btnDodaj.Location = new Point(267, 120);
            btnDodaj.Name = "btnDodaj";
            btnDodaj.Size = new Size(75, 23);
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
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { Naziv, Status, btnPS });
            dataGridView1.Location = new Point(12, 150);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.ReadOnly = true;
            dataGridView1.RowTemplate.Height = 25;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.Size = new Size(646, 150);
            dataGridView1.TabIndex = 4;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Naziv
            // 
            Naziv.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Naziv.DataPropertyName = "Naziv";
            Naziv.HeaderText = "NazivGrada";
            Naziv.Name = "Naziv";
            Naziv.ReadOnly = true;
            // 
            // Status
            // 
            Status.DataPropertyName = "Status";
            Status.HeaderText = "Aktivan";
            Status.Name = "Status";
            Status.ReadOnly = true;
            // 
            // btnPS
            // 
            btnPS.HeaderText = "";
            btnPS.Name = "btnPS";
            btnPS.ReadOnly = true;
            btnPS.Text = "Promijeni status";
            btnPS.UseColumnTextForButtonValue = true;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(txtInfo);
            groupBox1.Controls.Add(btnGenerisi);
            groupBox1.Controls.Add(checkBox1);
            groupBox1.Controls.Add(txtBrojGradova);
            groupBox1.Controls.Add(label1);
            groupBox1.Controls.Add(label2);
            groupBox1.Location = new Point(12, 306);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(646, 247);
            groupBox1.TabIndex = 5;
            groupBox1.TabStop = false;
            groupBox1.Text = "groupBox1";
            // 
            // txtInfo
            // 
            txtInfo.Location = new Point(6, 91);
            txtInfo.Multiline = true;
            txtInfo.Name = "txtInfo";
            txtInfo.Size = new Size(634, 150);
            txtInfo.TabIndex = 5;
            // 
            // btnGenerisi
            // 
            btnGenerisi.Location = new Point(255, 39);
            btnGenerisi.Name = "btnGenerisi";
            btnGenerisi.Size = new Size(75, 23);
            btnGenerisi.TabIndex = 4;
            btnGenerisi.Text = "generisi";
            btnGenerisi.UseVisualStyleBackColor = true;
            btnGenerisi.Click += btnGenerisi_Click;
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Location = new Point(166, 44);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(64, 19);
            checkBox1.TabIndex = 3;
            checkBox1.Text = "AKtivni";
            checkBox1.UseVisualStyleBackColor = true;
            // 
            // txtBrojGradova
            // 
            txtBrojGradova.Location = new Point(50, 40);
            txtBrojGradova.Name = "txtBrojGradova";
            txtBrojGradova.Size = new Size(100, 23);
            txtBrojGradova.TabIndex = 2;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(6, 73);
            label1.Name = "label1";
            label1.Size = new Size(28, 15);
            label1.TabIndex = 1;
            label1.Text = "info";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(6, 43);
            label2.Name = "label2";
            label2.Size = new Size(45, 15);
            label2.TabIndex = 1;
            label2.Text = "br.grad";
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // frnGradoviIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(670, 565);
            Controls.Add(groupBox1);
            Controls.Add(dataGridView1);
            Controls.Add(btnDodaj);
            Controls.Add(txtNazivGrada);
            Controls.Add(lblZemlja);
            Controls.Add(pictureBox1);
            Name = "frnGradoviIB230172";
            Text = "frnGradoviIB230172";
            Load += frnGradoviIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pictureBox1;
        private Label lblZemlja;
        private TextBox txtNazivGrada;
        private Button btnDodaj;
        private DataGridView dataGridView1;
        private DataGridViewTextBoxColumn Naziv;
        private DataGridViewCheckBoxColumn Status;
        private DataGridViewButtonColumn btnPS;
        private GroupBox groupBox1;
        private CheckBox checkBox1;
        private TextBox txtBrojGradova;
        private Label label2;
        private TextBox txtInfo;
        private Button btnGenerisi;
        private Label label1;
        private ErrorProvider err;
    }
}