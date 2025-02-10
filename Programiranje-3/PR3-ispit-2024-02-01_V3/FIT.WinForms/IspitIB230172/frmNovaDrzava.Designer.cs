namespace FIT.WinForms.IspitIB230172
{
    partial class frmNovaDrzava
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
            label1 = new Label();
            textBox1 = new TextBox();
            checkBox1 = new CheckBox();
            btnSacuvaj = new Button();
            err = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // pictureBox1
            // 
            pictureBox1.BorderStyle = BorderStyle.FixedSingle;
            pictureBox1.Location = new Point(12, 12);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(306, 181);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.TabIndex = 0;
            pictureBox1.TabStop = false;
            pictureBox1.Click += pictureBox1_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 196);
            label1.Name = "label1";
            label1.Size = new Size(36, 15);
            label1.TabIndex = 1;
            label1.Text = "Naziv";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(12, 214);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(306, 23);
            textBox1.TabIndex = 2;
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Location = new Point(12, 243);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(66, 19);
            checkBox1.TabIndex = 3;
            checkBox1.Text = "Aktivna";
            checkBox1.UseVisualStyleBackColor = true;
            // 
            // btnSacuvaj
            // 
            btnSacuvaj.Location = new Point(214, 243);
            btnSacuvaj.Name = "btnSacuvaj";
            btnSacuvaj.Size = new Size(104, 23);
            btnSacuvaj.TabIndex = 4;
            btnSacuvaj.Text = "Sacuvaj";
            btnSacuvaj.UseVisualStyleBackColor = true;
            btnSacuvaj.Click += btnSacuvaj_Click;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // frmNovaDrzava
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(335, 288);
            Controls.Add(btnSacuvaj);
            Controls.Add(checkBox1);
            Controls.Add(textBox1);
            Controls.Add(label1);
            Controls.Add(pictureBox1);
            Name = "frmNovaDrzava";
            Text = "frmNovaDrzava";
            Load += frmNovaDrzava_Load;
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pictureBox1;
        private Label label1;
        private TextBox textBox1;
        private CheckBox checkBox1;
        private Button btnSacuvaj;
        private ErrorProvider err;
    }
}