namespace DLWMS.WinApp.Predavanja
{
    partial class frmNotifikacije
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
            if (disposing && (components != null))
            {
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
            btnPosalji = new Button();
            txtPoruka = new TextBox();
            cbSMS = new CheckBox();
            cbViber = new CheckBox();
            cbEmail = new CheckBox();
            txtIspis = new TextBox();
            SuspendLayout();
            // 
            // btnPosalji
            // 
            btnPosalji.Location = new Point(400, 89);
            btnPosalji.Name = "btnPosalji";
            btnPosalji.Size = new Size(117, 34);
            btnPosalji.TabIndex = 0;
            btnPosalji.Text = "Cudna prijava";
            btnPosalji.UseVisualStyleBackColor = true;
            btnPosalji.Click += btnPosalji_Click;
            // 
            // txtPoruka
            // 
            txtPoruka.Location = new Point(12, 12);
            txtPoruka.Multiline = true;
            txtPoruka.Name = "txtPoruka";
            txtPoruka.Size = new Size(382, 111);
            txtPoruka.TabIndex = 1;
            txtPoruka.Text = "Pokusaj prijave na sistem sa nepoznate IP adrese!";
            // 
            // cbSMS
            // 
            cbSMS.AutoSize = true;
            cbSMS.Location = new Point(400, 14);
            cbSMS.Name = "cbSMS";
            cbSMS.Size = new Size(49, 19);
            cbSMS.TabIndex = 2;
            cbSMS.Text = "SMS";
            cbSMS.UseVisualStyleBackColor = true;
            cbSMS.CheckedChanged += cbSMS_CheckedChanged;
            // 
            // cbViber
            // 
            cbViber.AutoSize = true;
            cbViber.Location = new Point(400, 39);
            cbViber.Name = "cbViber";
            cbViber.Size = new Size(53, 19);
            cbViber.TabIndex = 3;
            cbViber.Text = "Viber";
            cbViber.UseVisualStyleBackColor = true;
            cbViber.CheckedChanged += cbViber_CheckedChanged;
            // 
            // cbEmail
            // 
            cbEmail.AutoSize = true;
            cbEmail.Location = new Point(400, 64);
            cbEmail.Name = "cbEmail";
            cbEmail.Size = new Size(55, 19);
            cbEmail.TabIndex = 4;
            cbEmail.Text = "Email";
            cbEmail.UseVisualStyleBackColor = true;
            cbEmail.CheckedChanged += cbEmail_CheckedChanged;
            // 
            // txtIspis
            // 
            txtIspis.Location = new Point(12, 129);
            txtIspis.Multiline = true;
            txtIspis.Name = "txtIspis";
            txtIspis.Size = new Size(505, 111);
            txtIspis.TabIndex = 5;
            // 
            // frmNotifikacije
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(531, 256);
            Controls.Add(txtIspis);
            Controls.Add(cbEmail);
            Controls.Add(cbViber);
            Controls.Add(cbSMS);
            Controls.Add(txtPoruka);
            Controls.Add(btnPosalji);
            Name = "frmNotifikacije";
            Text = "Notifikacije";
            Load += frmNotifikacije_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnPosalji;
        private TextBox txtPoruka;
        private CheckBox cbSMS;
        private CheckBox cbViber;
        private CheckBox cbEmail;
        private TextBox txtIspis;
    }
}