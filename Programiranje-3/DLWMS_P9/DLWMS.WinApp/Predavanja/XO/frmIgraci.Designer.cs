namespace DLWMS.WinApp
{
    partial class frmIgraci
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmIgraci));
            pictureBox1 = new PictureBox();
            txtIgrac1 = new TextBox();
            txtIgrac2 = new TextBox();
            pictureBox2 = new PictureBox();
            pictureBox3 = new PictureBox();
            btnStart = new Button();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox2).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox3).BeginInit();
            SuspendLayout();
            // 
            // pictureBox1
            // 
            pictureBox1.Image = Properties.Resources._3177440;
            pictureBox1.Location = new Point(21, 30);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(205, 211);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.TabIndex = 0;
            pictureBox1.TabStop = false;
            // 
            // txtIgrac1
            // 
            txtIgrac1.Font = new Font("Segoe UI", 15F, FontStyle.Bold);
            txtIgrac1.Location = new Point(21, 247);
            txtIgrac1.Name = "txtIgrac1";
            txtIgrac1.Size = new Size(205, 34);
            txtIgrac1.TabIndex = 1;
            txtIgrac1.TextAlign = HorizontalAlignment.Center;
            // 
            // txtIgrac2
            // 
            txtIgrac2.Font = new Font("Segoe UI", 15F, FontStyle.Bold);
            txtIgrac2.Location = new Point(407, 247);
            txtIgrac2.Name = "txtIgrac2";
            txtIgrac2.Size = new Size(205, 34);
            txtIgrac2.TabIndex = 3;
            txtIgrac2.TextAlign = HorizontalAlignment.Center;
            // 
            // pictureBox2
            // 
            pictureBox2.Image = (Image)resources.GetObject("pictureBox2.Image");
            pictureBox2.Location = new Point(407, 30);
            pictureBox2.Name = "pictureBox2";
            pictureBox2.Size = new Size(205, 211);
            pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox2.TabIndex = 2;
            pictureBox2.TabStop = false;
            // 
            // pictureBox3
            // 
            pictureBox3.Image = (Image)resources.GetObject("pictureBox3.Image");
            pictureBox3.Location = new Point(269, 108);
            pictureBox3.Name = "pictureBox3";
            pictureBox3.Size = new Size(91, 84);
            pictureBox3.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox3.TabIndex = 4;
            pictureBox3.TabStop = false;
            // 
            // btnStart
            // 
            btnStart.Font = new Font("Segoe UI", 20F, FontStyle.Bold);
            btnStart.Location = new Point(244, 218);
            btnStart.Name = "btnStart";
            btnStart.Size = new Size(144, 63);
            btnStart.TabIndex = 5;
            btnStart.Text = "START";
            btnStart.UseVisualStyleBackColor = true;
            btnStart.Click += btnStart_Click;
            // 
            // frmIgraci
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(649, 295);
            Controls.Add(btnStart);
            Controls.Add(pictureBox3);
            Controls.Add(txtIgrac2);
            Controls.Add(pictureBox2);
            Controls.Add(txtIgrac1);
            Controls.Add(pictureBox1);
            Name = "frmIgraci";
            Text = "Igraci";
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox2).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox3).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pictureBox1;
        private TextBox txtIgrac1;
        private TextBox txtIgrac2;
        private PictureBox pictureBox2;
        private PictureBox pictureBox3;
        private Button btnStart;
    }
}