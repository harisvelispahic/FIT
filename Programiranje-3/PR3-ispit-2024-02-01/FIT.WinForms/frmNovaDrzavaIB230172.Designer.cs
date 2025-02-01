namespace FIT.WinForms
{
    partial class frmNovaDrzavaIB230172
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
            label1 = new Label();
            pbZastava = new PictureBox();
            label2 = new Label();
            txtNaziv = new TextBox();
            cbStatus = new CheckBox();
            btnSacuvaj = new Button();
            err = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)pbZastava).BeginInit();
            ((System.ComponentModel.ISupportInitialize)err).BeginInit();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(50, 15);
            label1.TabIndex = 0;
            label1.Text = "Zastava:";
            // 
            // pbZastava
            // 
            pbZastava.BorderStyle = BorderStyle.FixedSingle;
            pbZastava.Location = new Point(12, 27);
            pbZastava.Name = "pbZastava";
            pbZastava.Size = new Size(313, 167);
            pbZastava.SizeMode = PictureBoxSizeMode.StretchImage;
            pbZastava.TabIndex = 1;
            pbZastava.TabStop = false;
            pbZastava.Click += pbZastava_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(12, 206);
            label2.Name = "label2";
            label2.Size = new Size(39, 15);
            label2.TabIndex = 0;
            label2.Text = "Naziv:";
            // 
            // txtNaziv
            // 
            txtNaziv.Location = new Point(12, 224);
            txtNaziv.Name = "txtNaziv";
            txtNaziv.Size = new Size(313, 23);
            txtNaziv.TabIndex = 2;
            // 
            // cbStatus
            // 
            cbStatus.AutoSize = true;
            cbStatus.Location = new Point(12, 253);
            cbStatus.Name = "cbStatus";
            cbStatus.Size = new Size(66, 19);
            cbStatus.TabIndex = 3;
            cbStatus.Text = "Aktivna";
            cbStatus.UseVisualStyleBackColor = true;
            // 
            // btnSacuvaj
            // 
            btnSacuvaj.Location = new Point(201, 280);
            btnSacuvaj.Name = "btnSacuvaj";
            btnSacuvaj.Size = new Size(124, 23);
            btnSacuvaj.TabIndex = 4;
            btnSacuvaj.Text = "Sačuvaj";
            btnSacuvaj.UseVisualStyleBackColor = true;
            btnSacuvaj.Click += btnSacuvaj_Click;
            // 
            // err
            // 
            err.ContainerControl = this;
            // 
            // frmNovaDrzavaIB230172
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(336, 315);
            Controls.Add(btnSacuvaj);
            Controls.Add(cbStatus);
            Controls.Add(txtNaziv);
            Controls.Add(pbZastava);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "frmNovaDrzavaIB230172";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Podaci o državi";
            Load += frmNovaDrzavaIB230172_Load;
            ((System.ComponentModel.ISupportInitialize)pbZastava).EndInit();
            ((System.ComponentModel.ISupportInitialize)err).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private PictureBox pbZastava;
        private Label label2;
        private TextBox txtNaziv;
        private CheckBox cbStatus;
        private Button btnSacuvaj;
        private ErrorProvider err;
    }
}