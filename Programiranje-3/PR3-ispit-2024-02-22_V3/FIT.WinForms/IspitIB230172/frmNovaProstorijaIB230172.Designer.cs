namespace FIT.WinForms.IspitIB230172
{
    partial class frmNovaProstorijaIB230172
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
            txtNaziv = new TextBox();
            label1 = new Label();
            label2 = new Label();
            txtOznaka = new TextBox();
            txtKapacitet = new TextBox();
            label3 = new Label();
            button1 = new Button();
            err = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // pictureBox1
            // 
            pictureBox1.BorderStyle = BorderStyle.FixedSingle;
            pictureBox1.Location = new Point(10, 9);
            pictureBox1.Margin = new Padding(3, 2, 3, 2);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(214, 162);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.TabIndex = 0;
            pictureBox1.TabStop = false;
            pictureBox1.DoubleClick += pictureBox1_Click;
            // 
            // txtNaziv
            // 
            txtNaziv.Location = new Point(237, 24);
            txtNaziv.Margin = new Padding(3, 2, 3, 2);
            txtNaziv.Name = "txtNaziv";
            txtNaziv.Size = new Size(238, 23);
            txtNaziv.TabIndex = 1;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(237, 7);
            label1.Name = "label1";
            label1.Size = new Size(36, 15);
            label1.TabIndex = 2;
            label1.Text = "Naziv";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(237, 80);
            label2.Name = "label2";
            label2.Size = new Size(46, 15);
            label2.TabIndex = 2;
            label2.Text = "Oznaka";
            // 
            // txtOznaka
            // 
            txtOznaka.Location = new Point(237, 97);
            txtOznaka.Margin = new Padding(3, 2, 3, 2);
            txtOznaka.Name = "txtOznaka";
            txtOznaka.Size = new Size(110, 23);
            txtOznaka.TabIndex = 3;
            // 
            // txtKapacitet
            // 
            txtKapacitet.Location = new Point(366, 97);
            txtKapacitet.Margin = new Padding(3, 2, 3, 2);
            txtKapacitet.Name = "txtKapacitet";
            txtKapacitet.Size = new Size(110, 23);
            txtKapacitet.TabIndex = 4;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(366, 80);
            label3.Name = "label3";
            label3.Size = new Size(55, 15);
            label3.TabIndex = 2;
            label3.Text = "kapacitet";
            // 
            // button1
            // 
            button1.Location = new Point(393, 149);
            button1.Margin = new Padding(3, 2, 3, 2);
            button1.Name = "button1";
            button1.Size = new Size(82, 22);
            button1.TabIndex = 5;
            button1.Text = "Sačuvaj";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // frmNovaProstorijaIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(494, 185);
            Controls.Add(button1);
            Controls.Add(txtKapacitet);
            Controls.Add(txtOznaka);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(txtNaziv);
            Controls.Add(pictureBox1);
            Margin = new Padding(3, 2, 3, 2);
            Name = "frmNovaProstorijaIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmNovaProstorijaIB230172";
            Load += frmNovaProstorijaIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pictureBox1;
        private TextBox txtNaziv;
        private Label label1;
        private Label label2;
        private TextBox txtOznaka;
        private TextBox txtKapacitet;
        private Label label3;
        private Button button1;
        private ErrorProvider err;
    }
}