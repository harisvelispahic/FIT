namespace FIT.WinForms.IspitIB230172
{
    partial class frmDrzaveIB230172
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
            btnNovaDrzava = new Button();
            dataGridView1 = new DataGridView();
            Zastava = new DataGridViewImageColumn();
            Drzava = new DataGridViewTextBoxColumn();
            BrojGradova = new DataGridViewTextBoxColumn();
            Aktivna = new DataGridViewCheckBoxColumn();
            btnGradovi = new DataGridViewButtonColumn();
            btnPrintaj = new Button();
            timer1 = new System.Windows.Forms.Timer(components);
            label1 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // btnNovaDrzava
            // 
            btnNovaDrzava.Location = new Point(676, 12);
            btnNovaDrzava.Name = "btnNovaDrzava";
            btnNovaDrzava.Size = new Size(112, 23);
            btnNovaDrzava.TabIndex = 0;
            btnNovaDrzava.Text = "Nova drzava";
            btnNovaDrzava.UseVisualStyleBackColor = true;
            btnNovaDrzava.Click += btnNovaDrzava_Click;
            // 
            // dataGridView1
            // 
            dataGridView1.AllowUserToAddRows = false;
            dataGridView1.AllowUserToDeleteRows = false;
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { Zastava, Drzava, BrojGradova, Aktivna, btnGradovi });
            dataGridView1.Location = new Point(12, 41);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.ReadOnly = true;
            dataGridView1.RowTemplate.Height = 25;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.Size = new Size(776, 282);
            dataGridView1.TabIndex = 1;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // Zastava
            // 
            Zastava.DataPropertyName = "Zastava";
            Zastava.HeaderText = "Zastava";
            Zastava.Name = "Zastava";
            Zastava.ReadOnly = true;
            // 
            // Drzava
            // 
            Drzava.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
            Drzava.DataPropertyName = "Naziv";
            Drzava.HeaderText = "Država";
            Drzava.Name = "Drzava";
            Drzava.ReadOnly = true;
            // 
            // BrojGradova
            // 
            BrojGradova.DataPropertyName = "BrojGradova";
            BrojGradova.HeaderText = "Broj Gradova";
            BrojGradova.Name = "BrojGradova";
            BrojGradova.ReadOnly = true;
            // 
            // Aktivna
            // 
            Aktivna.DataPropertyName = "Status";
            Aktivna.HeaderText = "Aktivna";
            Aktivna.Name = "Aktivna";
            Aktivna.ReadOnly = true;
            Aktivna.Resizable = DataGridViewTriState.True;
            Aktivna.SortMode = DataGridViewColumnSortMode.Automatic;
            // 
            // btnGradovi
            // 
            btnGradovi.HeaderText = "";
            btnGradovi.Name = "btnGradovi";
            btnGradovi.ReadOnly = true;
            btnGradovi.Text = "Gradovi";
            btnGradovi.UseColumnTextForButtonValue = true;
            // 
            // btnPrintaj
            // 
            btnPrintaj.Location = new Point(693, 329);
            btnPrintaj.Name = "btnPrintaj";
            btnPrintaj.Size = new Size(95, 23);
            btnPrintaj.TabIndex = 2;
            btnPrintaj.Text = "Printaj";
            btnPrintaj.UseVisualStyleBackColor = true;
            btnPrintaj.Click += btnPrintaj_Click;
            // 
            // timer1
            // 
            timer1.Enabled = true;
            timer1.Tick += timer1_Tick;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 378);
            label1.Name = "label1";
            label1.Size = new Size(38, 15);
            label1.TabIndex = 3;
            label1.Text = "label1";
            // 
            // frmDrzaveIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 402);
            Controls.Add(label1);
            Controls.Add(btnPrintaj);
            Controls.Add(dataGridView1);
            Controls.Add(btnNovaDrzava);
            Name = "frmDrzaveIB230172";
            Text = "frmDrzaveIB230172";
            Load += frmDrzaveIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnNovaDrzava;
        private DataGridView dataGridView1;
        private DataGridViewImageColumn Zastava;
        private DataGridViewTextBoxColumn Drzava;
        private DataGridViewTextBoxColumn BrojGradova;
        private DataGridViewCheckBoxColumn Aktivna;
        private DataGridViewButtonColumn btnGradovi;
        private Button btnPrintaj;
        private System.Windows.Forms.Timer timer1;
        private Label label1;
    }
}