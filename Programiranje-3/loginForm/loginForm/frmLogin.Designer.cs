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
            lblLogin = new Label();
            btnClose = new Button();
            btnMinimize = new Button();
            errorUsername = new ErrorProvider(components);
            errorPassword = new ErrorProvider(components);
            btnSignUp = new Button();
            lblSignUp = new Label();
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
            btnLogin.Location = new Point(526, 407);
            btnLogin.Name = "btnLogin";
            btnLogin.Size = new Size(107, 40);
            btnLogin.TabIndex = 4;
            btnLogin.Text = "LOGIN";
            btnLogin.UseVisualStyleBackColor = false;
            btnLogin.Click += btnLogin_Click;
            // 
            // lblLogin
            // 
            lblLogin.AutoSize = true;
            lblLogin.BackColor = Color.Transparent;
            lblLogin.Font = new Font("Segoe UI", 40F, FontStyle.Bold);
            lblLogin.ForeColor = SystemColors.ButtonHighlight;
            lblLogin.Location = new Point(374, 82);
            lblLogin.Name = "lblLogin";
            lblLogin.Size = new Size(196, 72);
            lblLogin.TabIndex = 5;
            lblLogin.Text = "LOGIN";
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
            // btnSignUp
            // 
            btnSignUp.BackColor = Color.White;
            btnSignUp.FlatAppearance.BorderSize = 2;
            btnSignUp.FlatStyle = FlatStyle.Flat;
            btnSignUp.Font = new Font("Segoe UI", 12F, FontStyle.Bold);
            btnSignUp.ForeColor = Color.Black;
            btnSignUp.Location = new Point(307, 407);
            btnSignUp.Name = "btnSignUp";
            btnSignUp.Size = new Size(132, 40);
            btnSignUp.TabIndex = 8;
            btnSignUp.Text = "SIGN UP";
            btnSignUp.UseVisualStyleBackColor = false;
            btnSignUp.Click += btnSignUp_Click;
            // 
            // lblSignUp
            // 
            lblSignUp.AutoSize = true;
            lblSignUp.BackColor = Color.Transparent;
            lblSignUp.Font = new Font("Segoe UI", 8F, FontStyle.Bold);
            lblSignUp.ForeColor = SystemColors.ButtonHighlight;
            lblSignUp.Location = new Point(307, 391);
            lblSignUp.Name = "lblSignUp";
            lblSignUp.Size = new Size(128, 13);
            lblSignUp.TabIndex = 9;
            lblSignUp.Text = "Don't have an account?";
            // 
            // frmLogin
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackgroundImage = Properties.Resources.login1;
            BackgroundImageLayout = ImageLayout.Stretch;
            ClientSize = new Size(937, 550);
            Controls.Add(lblSignUp);
            Controls.Add(btnSignUp);
            Controls.Add(btnMinimize);
            Controls.Add(btnClose);
            Controls.Add(lblLogin);
            Controls.Add(btnLogin);
            Controls.Add(lblPassword);
            Controls.Add(lblUsername);
            Controls.Add(txtPassword);
            Controls.Add(txtUsername);
            FormBorderStyle = FormBorderStyle.None;
            Name = "frmLogin";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Form1";
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
        private Label lblLogin;
        private Button btnClose;
        private Button btnMinimize;
        private ErrorProvider errorUsername;
        private ErrorProvider errorPassword;
        private Button btnSignUp;
        private Label lblSignUp;
    }
}
