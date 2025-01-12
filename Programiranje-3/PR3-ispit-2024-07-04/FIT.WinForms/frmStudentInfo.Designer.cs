namespace FIT.WinForms
{
    partial class frmStudentInfo
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
            pbStudent = new PictureBox();
            lblImePrezime = new Label();
            lblProsjek = new Label();
            ((System.ComponentModel.ISupportInitialize)pbStudent).BeginInit();
            SuspendLayout();
            // 
            // pbStudent
            // 
            pbStudent.Location = new Point(12, 12);
            pbStudent.Name = "pbStudent";
            pbStudent.Size = new Size(264, 265);
            pbStudent.SizeMode = PictureBoxSizeMode.StretchImage;
            pbStudent.TabIndex = 0;
            pbStudent.TabStop = false;
            // 
            // lblImePrezime
            // 
            lblImePrezime.AutoSize = true;
            lblImePrezime.Location = new Point(122, 300);
            lblImePrezime.Name = "lblImePrezime";
            lblImePrezime.Size = new Size(38, 15);
            lblImePrezime.TabIndex = 1;
            lblImePrezime.Text = "label1";
            // 
            // lblProsjek
            // 
            lblProsjek.AutoSize = true;
            lblProsjek.Location = new Point(122, 327);
            lblProsjek.Name = "lblProsjek";
            lblProsjek.Size = new Size(38, 15);
            lblProsjek.TabIndex = 2;
            lblProsjek.Text = "label2";
            // 
            // frmStudentInfo
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(288, 372);
            Controls.Add(lblProsjek);
            Controls.Add(lblImePrezime);
            Controls.Add(pbStudent);
            Name = "frmStudentInfo";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmStudentInfo";
            Load += frmStudentInfo_Load;
            ((System.ComponentModel.ISupportInitialize)pbStudent).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pbStudent;
        private Label lblImePrezime;
        private Label lblProsjek;
    }
}