namespace FIT.WinForms
{
    partial class frmNovaPoruka
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
            cmbPredmet = new ComboBox();
            label1 = new Label();
            label2 = new Label();
            dateTimePicker1 = new DateTimePicker();
            label3 = new Label();
            cmbHitnost = new ComboBox();
            textBox1 = new TextBox();
            label4 = new Label();
            pictureBox1 = new PictureBox();
            label5 = new Label();
            btnOdustani = new Button();
            btnSacuvaj = new Button();
            err = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // cmbPredmet
            // 
            cmbPredmet.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbPredmet.FormattingEnabled = true;
            cmbPredmet.Location = new Point(12, 27);
            cmbPredmet.Name = "cmbPredmet";
            cmbPredmet.Size = new Size(225, 23);
            cmbPredmet.TabIndex = 0;
            cmbPredmet.SelectedIndexChanged += cmbPredmet_SelectedIndexChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(110, 15);
            label1.TabIndex = 1;
            label1.Text = "Odaberite predmet:";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(12, 53);
            label2.Name = "label2";
            label2.Size = new Size(117, 15);
            label2.TabIndex = 1;
            label2.Text = "Poruka je validna do:";
            // 
            // dateTimePicker1
            // 
            dateTimePicker1.Location = new Point(12, 71);
            dateTimePicker1.Name = "dateTimePicker1";
            dateTimePicker1.Size = new Size(225, 23);
            dateTimePicker1.TabIndex = 2;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(12, 116);
            label3.Name = "label3";
            label3.Size = new Size(89, 15);
            label3.TabIndex = 1;
            label3.Text = "Hitnost poruke:";
            // 
            // cmbHitnost
            // 
            cmbHitnost.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbHitnost.FormattingEnabled = true;
            cmbHitnost.Items.AddRange(new object[] { "Niska", "Srednja", "Visoka" });
            cmbHitnost.Location = new Point(12, 134);
            cmbHitnost.Name = "cmbHitnost";
            cmbHitnost.Size = new Size(225, 23);
            cmbHitnost.TabIndex = 0;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(12, 178);
            textBox1.Multiline = true;
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(225, 245);
            textBox1.TabIndex = 3;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(12, 160);
            label4.Name = "label4";
            label4.Size = new Size(47, 15);
            label4.TabIndex = 1;
            label4.Text = "Sadržaj:";
            // 
            // pictureBox1
            // 
            pictureBox1.BorderStyle = BorderStyle.FixedSingle;
            pictureBox1.Location = new Point(243, 27);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(429, 396);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.TabIndex = 4;
            pictureBox1.TabStop = false;
            pictureBox1.Click += pictureBox1_Click;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(243, 9);
            label5.Name = "label5";
            label5.Size = new Size(34, 15);
            label5.TabIndex = 1;
            label5.Text = "Slika:";
            // 
            // btnOdustani
            // 
            btnOdustani.Location = new Point(451, 439);
            btnOdustani.Name = "btnOdustani";
            btnOdustani.Size = new Size(113, 23);
            btnOdustani.TabIndex = 5;
            btnOdustani.Text = "Odustani";
            btnOdustani.UseVisualStyleBackColor = true;
            btnOdustani.Click += btnOdustani_Click;
            // 
            // btnSacuvaj
            // 
            btnSacuvaj.Location = new Point(570, 439);
            btnSacuvaj.Name = "btnSacuvaj";
            btnSacuvaj.Size = new Size(102, 23);
            btnSacuvaj.TabIndex = 6;
            btnSacuvaj.Text = "Sacuvaj";
            btnSacuvaj.UseVisualStyleBackColor = true;
            btnSacuvaj.Click += btnSacuvaj_Click;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // frmNovaPoruka
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(684, 476);
            Controls.Add(btnSacuvaj);
            Controls.Add(btnOdustani);
            Controls.Add(pictureBox1);
            Controls.Add(textBox1);
            Controls.Add(dateTimePicker1);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label5);
            Controls.Add(label1);
            Controls.Add(cmbHitnost);
            Controls.Add(cmbPredmet);
            Name = "frmNovaPoruka";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmNovaPoruka";
            Load += frmNovaPoruka_Load;
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ComboBox cmbPredmet;
        private Label label1;
        private Label label2;
        private DateTimePicker dateTimePicker1;
        private Label label3;
        private ComboBox cmbHitnost;
        private TextBox textBox1;
        private Label label4;
        private PictureBox pictureBox1;
        private Label label5;
        private Button btnOdustani;
        private Button btnSacuvaj;
        private ErrorProvider err;
    }
}