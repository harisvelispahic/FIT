namespace loginForm
{
    partial class frmLogin
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
            if (disposing && (components != null)) {
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
            components = new System.ComponentModel.Container();
            txtUsername = new TextBox();
            txtPassword = new TextBox();
            lblUsername = new Label();
            lblPassword = new Label();
            btnLogin = new Button();
            label1 = new Label();
            btnClose = new Button();
            btnMinimize = new Button();
            errorUsername = new ErrorProvider(components);
            errorPassword = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)errorUsername).BeginInit();
            ((System.ComponentModel.ISupportInitialize)errorPassword).BeginInit();
            SuspendLayout();
            // 
            // txtUsername
            // 
            txtUsername.Font = new Font("Segoe UI", 15F);
            txtUsername.Location = new Point(307, 240);
            txtUsername.Name = "txtUsername";
            txtUsername.Size = new Size(326, 34);
            txtUsername.TabIndex = 0;
            txtUsername.TextChanged += txtUsername_TextChanged;
            // 
            // txtPassword
            // 
            txtPassword.Font = new Font("Segoe UI", 15F);
            txtPassword.Location = new Point(307, 324);
            txtPassword.Name = "txtPassword";
            txtPassword.PasswordChar = '•';
            txtPassword.Size = new Size(326, 34);
            txtPassword.TabIndex = 1;
            txtPassword.TextChanged += txtPassword_TextChanged;
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.BackColor = Color.Transparent;
            lblUsername.Font = new Font("Segoe UI", 13F, FontStyle.Bold);
            lblUsername.ForeColor = SystemColors.ButtonHighlight;
            lblUsername.Location = new Point(307, 202);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(97, 25);
            lblUsername.TabIndex = 2;
            lblUsername.Text = "Username";
            // 
            // lblPassword
            // 
            lblPassword.AutoSize = true;
            lblPassword.BackColor = Color.Transparent;
            lblPassword.Font = new Font("Segoe UI", 13F, FontStyle.Bold);
            lblPassword.ForeColor = SystemColors.ButtonHighlight;
            lblPassword.Location = new Point(307, 293);
            lblPassword.Name = "lblPassword";
            lblPassword.Size = new Size(92, 25);
            lblPassword.TabIndex = 3;
            lblPassword.Text = "Password";
            // 
            // btnLogin
            // 
            btnLogin.BackColor = Color.Transparent;
            btnLogin.FlatAppearance.BorderSize = 2;
            btnLogin.FlatStyle = FlatStyle.Flat;
            btnLogin.Font = new Font("Segoe UI", 12F, FontStyle.Bold);
            btnLogin.ForeColor = SystemColors.ButtonFace;
            btnLogin.Location = new Point(501, 407);
            btnLogin.Name = "btnLogin";
            btnLogin.Size = new Size(132, 40);
            btnLogin.TabIndex = 4;
            btnLogin.Text = "PRIJAVI SE";
            btnLogin.UseVisualStyleBackColor = false;
            btnLogin.Click += btnLogin_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.Transparent;
            label1.Font = new Font("Segoe UI", 40F, FontStyle.Bold);
            label1.ForeColor = SystemColors.ButtonHighlight;
            label1.Location = new Point(340, 74);
            label1.Name = "label1";
            label1.Size = new Size(264, 72);
            label1.TabIndex = 5;
            label1.Text = "Welcome";
            // 
            // btnClose
            // 
            btnClose.BackColor = Color.Crimson;
            btnClose.FlatAppearance.BorderSize = 0;
            btnClose.FlatStyle = FlatStyle.Flat;
            btnClose.Font = new Font("Segoe UI", 15F, FontStyle.Bold);
            btnClose.ForeColor = SystemColors.ButtonHighlight;
            btnClose.Location = new Point(898, -6);
            btnClose.Name = "btnClose";
            btnClose.Size = new Size(44, 38);
            btnClose.TabIndex = 6;
            btnClose.Text = "x";
            btnClose.UseVisualStyleBackColor = false;
            btnClose.Click += btnClose_Click;
            // 
            // btnMinimize
            // 
            btnMinimize.BackColor = Color.Transparent;
            btnMinimize.FlatAppearance.BorderSize = 0;
            btnMinimize.FlatStyle = FlatStyle.Flat;
            btnMinimize.Font = new Font("Segoe UI", 15F, FontStyle.Bold);
            btnMinimize.ForeColor = SystemColors.ButtonHighlight;
            btnMinimize.Location = new Point(854, -6);
            btnMinimize.Name = "btnMinimize";
            btnMinimize.Size = new Size(44, 38);
            btnMinimize.TabIndex = 7;
            btnMinimize.Text = "–";
            btnMinimize.UseVisualStyleBackColor = false;
            btnMinimize.Click += btnMinimize_Click;
            // 
            // errorUsername
            // 
            errorUsername.ContainerControl = this;
            // 
            // errorPassword
            // 
            errorPassword.ContainerControl = this;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackgroundImage = Properties.Resources.login1;
            BackgroundImageLayout = ImageLayout.Stretch;
            ClientSize = new Size(937, 550);
            Controls.Add(btnMinimize);
            Controls.Add(btnClose);
            Controls.Add(label1);
            Controls.Add(btnLogin);
            Controls.Add(lblPassword);
            Controls.Add(lblUsername);
            Controls.Add(txtPassword);
            Controls.Add(txtUsername);
            FormBorderStyle = FormBorderStyle.None;
            Name = "Form1";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)errorUsername).EndInit();
            ((System.ComponentModel.ISupportInitialize)errorPassword).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox txtUsername;
        private TextBox txtPassword;
        private Label lblUsername;
        private Label lblPassword;
        private Button btnLogin;
        private Label label1;
        private Button btnClose;
        private Button btnMinimize;
        private ErrorProvider errorUsername;
        private ErrorProvider errorPassword;
    }
}
