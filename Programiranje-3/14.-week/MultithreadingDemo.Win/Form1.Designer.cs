namespace MultithreadingDemo.Win
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            btnDownload = new Button();
            rtResult = new RichTextBox();
            btnSimulateMultiAccess = new Button();
            SuspendLayout();
            // 
            // btnDownload
            // 
            btnDownload.Location = new Point(759, 478);
            btnDownload.Name = "btnDownload";
            btnDownload.Size = new Size(75, 23);
            btnDownload.TabIndex = 0;
            btnDownload.Text = "Download";
            btnDownload.UseVisualStyleBackColor = true;
            btnDownload.Click += btnDownload_Click;
            // 
            // rtResult
            // 
            rtResult.Location = new Point(12, 12);
            rtResult.Name = "rtResult";
            rtResult.Size = new Size(822, 460);
            rtResult.TabIndex = 1;
            rtResult.Text = "";
            // 
            // btnSimulateMultiAccess
            // 
            btnSimulateMultiAccess.Location = new Point(678, 478);
            btnSimulateMultiAccess.Name = "btnSimulateMultiAccess";
            btnSimulateMultiAccess.Size = new Size(75, 23);
            btnSimulateMultiAccess.TabIndex = 2;
            btnSimulateMultiAccess.Text = "Simulate";
            btnSimulateMultiAccess.UseVisualStyleBackColor = true;
            btnSimulateMultiAccess.Click += btnSimulateMultiAccess_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(846, 513);
            Controls.Add(btnSimulateMultiAccess);
            Controls.Add(rtResult);
            Controls.Add(btnDownload);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
        }

        #endregion

        private Button btnDownload;
        private RichTextBox rtResult;
        private Button btnSimulateMultiAccess;
    }
}
