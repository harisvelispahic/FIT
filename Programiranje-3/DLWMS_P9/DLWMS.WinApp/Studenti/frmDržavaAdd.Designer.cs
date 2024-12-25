namespace DLWMS.WinApp.Studenti
{
    partial class frmDržavaAdd
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
            txtNaziv = new TextBox();
            txtOznaka = new TextBox();
            label2 = new Label();
            btnSačuvaj = new Button();
            cbAktivan = new CheckBox();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(35, 38);
            label1.Name = "label1";
            label1.Size = new Size(36, 15);
            label1.TabIndex = 0;
            label1.Text = "Naziv";
            // 
            // txtNaziv
            // 
            txtNaziv.Location = new Point(35, 56);
            txtNaziv.Name = "txtNaziv";
            txtNaziv.Size = new Size(151, 23);
            txtNaziv.TabIndex = 1;
            txtNaziv.TextChanged += textBox1_TextChanged;
            // 
            // txtOznaka
            // 
            txtOznaka.Location = new Point(195, 56);
            txtOznaka.Name = "txtOznaka";
            txtOznaka.Size = new Size(151, 23);
            txtOznaka.TabIndex = 3;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(195, 38);
            label2.Name = "label2";
            label2.Size = new Size(46, 15);
            label2.TabIndex = 2;
            label2.Text = "Oznaka";
            label2.Click += label2_Click;
            // 
            // btnSačuvaj
            // 
            btnSačuvaj.Location = new Point(264, 102);
            btnSačuvaj.Name = "btnSačuvaj";
            btnSačuvaj.Size = new Size(82, 23);
            btnSačuvaj.TabIndex = 4;
            btnSačuvaj.Text = "Sačuvaj";
            btnSačuvaj.UseVisualStyleBackColor = true;
            btnSačuvaj.Click += btnSačuvaj_Click;
            // 
            // cbAktivan
            // 
            cbAktivan.AutoSize = true;
            cbAktivan.Location = new Point(35, 106);
            cbAktivan.Name = "cbAktivan";
            cbAktivan.Size = new Size(66, 19);
            cbAktivan.TabIndex = 6;
            cbAktivan.Text = "Aktivan";
            cbAktivan.UseVisualStyleBackColor = true;
            // 
            // frmDržavaAdd
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(385, 152);
            Controls.Add(cbAktivan);
            Controls.Add(btnSačuvaj);
            Controls.Add(txtOznaka);
            Controls.Add(label2);
            Controls.Add(txtNaziv);
            Controls.Add(label1);
            Name = "frmDržavaAdd";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Dodaj državu";
            Load += frmDržavaAdd_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private TextBox txtNaziv;
        private TextBox txtOznaka;
        private Label label2;
        private Button btnSačuvaj;
        private CheckBox cbAktivan;
    }
}