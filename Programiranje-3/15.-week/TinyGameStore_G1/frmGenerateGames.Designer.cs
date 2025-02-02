namespace TinyGameStore_G1
{
    partial class frmGenerateGames
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
            dtpGame = new DateTimePicker();
            txtNumberOfGames = new TextBox();
            label1 = new Label();
            rtbGame = new RichTextBox();
            btnGenerate = new Button();
            SuspendLayout();
            // 
            // dtpGame
            // 
            dtpGame.Location = new Point(12, 83);
            dtpGame.Name = "dtpGame";
            dtpGame.Size = new Size(200, 23);
            dtpGame.TabIndex = 0;
            // 
            // txtNumberOfGames
            // 
            txtNumberOfGames.Location = new Point(136, 112);
            txtNumberOfGames.Name = "txtNumberOfGames";
            txtNumberOfGames.Size = new Size(76, 23);
            txtNumberOfGames.TabIndex = 1;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(12, 115);
            label1.Name = "label1";
            label1.Size = new Size(106, 15);
            label1.TabIndex = 2;
            label1.Text = "Number of games:";
            // 
            // rtbGame
            // 
            rtbGame.Location = new Point(227, 10);
            rtbGame.Name = "rtbGame";
            rtbGame.Size = new Size(427, 312);
            rtbGame.TabIndex = 3;
            rtbGame.Text = "";
            // 
            // btnGenerate
            // 
            btnGenerate.Location = new Point(71, 152);
            btnGenerate.Name = "btnGenerate";
            btnGenerate.Size = new Size(75, 23);
            btnGenerate.TabIndex = 4;
            btnGenerate.Text = "Generate";
            btnGenerate.UseVisualStyleBackColor = true;
            btnGenerate.Click += btnGenerate_Click;
            // 
            // frmGenerateGames
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(666, 334);
            Controls.Add(btnGenerate);
            Controls.Add(rtbGame);
            Controls.Add(label1);
            Controls.Add(txtNumberOfGames);
            Controls.Add(dtpGame);
            Name = "frmGenerateGames";
            Text = "frmGenerateGames";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DateTimePicker dtpGame;
        private TextBox txtNumberOfGames;
        private Label label1;
        private RichTextBox rtbGame;
        private Button btnGenerate;
    }
}