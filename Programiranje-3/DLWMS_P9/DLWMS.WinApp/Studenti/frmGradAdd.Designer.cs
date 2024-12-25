namespace DLWMS.WinApp.Studenti
{
    partial class frmGradAdd
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
            cbAktivan = new CheckBox();
            btnSačuvaj = new Button();
            txtOznaka = new TextBox();
            label2 = new Label();
            txtNaziv = new TextBox();
            label1 = new Label();
            label3 = new Label();
            cmbDržave = new ComboBox();
            SuspendLayout();
            // 
            // cbAktivan
            // 
            cbAktivan.AutoSize = true;
            cbAktivan.Location = new Point(187, 103);
            cbAktivan.Name = "cbAktivan";
            cbAktivan.Size = new Size(66, 19);
            cbAktivan.TabIndex = 12;
            cbAktivan.Text = "Aktivan";
            cbAktivan.UseVisualStyleBackColor = true;
            // 
            // btnSačuvaj
            // 
            btnSačuvaj.Location = new Point(256, 100);
            btnSačuvaj.Name = "btnSačuvaj";
            btnSačuvaj.Size = new Size(82, 23);
            btnSačuvaj.TabIndex = 11;
            btnSačuvaj.Text = "Sačuvaj";
            btnSačuvaj.UseVisualStyleBackColor = true;
            btnSačuvaj.Click += btnSačuvaj_Click;
            // 
            // txtOznaka
            // 
            txtOznaka.Location = new Point(187, 40);
            txtOznaka.Name = "txtOznaka";
            txtOznaka.Size = new Size(151, 23);
            txtOznaka.TabIndex = 10;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(187, 22);
            label2.Name = "label2";
            label2.Size = new Size(46, 15);
            label2.TabIndex = 9;
            label2.Text = "Oznaka";
            // 
            // txtNaziv
            // 
            txtNaziv.Location = new Point(27, 40);
            txtNaziv.Name = "txtNaziv";
            txtNaziv.Size = new Size(151, 23);
            txtNaziv.TabIndex = 8;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(27, 22);
            label1.Name = "label1";
            label1.Size = new Size(36, 15);
            label1.TabIndex = 7;
            label1.Text = "Naziv";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(27, 81);
            label3.Name = "label3";
            label3.Size = new Size(42, 15);
            label3.TabIndex = 13;
            label3.Text = "Država";
            // 
            // cmbDržave
            // 
            cmbDržave.FormattingEnabled = true;
            cmbDržave.Location = new Point(27, 99);
            cmbDržave.Name = "cmbDržave";
            cmbDržave.Size = new Size(151, 23);
            cmbDržave.TabIndex = 14;
            // 
            // frmGradAdd
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(367, 156);
            Controls.Add(cmbDržave);
            Controls.Add(label3);
            Controls.Add(cbAktivan);
            Controls.Add(btnSačuvaj);
            Controls.Add(txtOznaka);
            Controls.Add(label2);
            Controls.Add(txtNaziv);
            Controls.Add(label1);
            Name = "frmGradAdd";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Dodaj grad";
            Load += frmGradAdd_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private CheckBox cbAktivan;
        private Button btnSačuvaj;
        private TextBox txtOznaka;
        private Label label2;
        private TextBox txtNaziv;
        private Label label1;
        private Label label3;
        private ComboBox cmbDržave;
    }
}