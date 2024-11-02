namespace loginForm
{
    partial class frmSignUp
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmSignUp));
            btnClose = new Button();
            label1 = new Label();
            lblLastName = new Label();
            lblFirstName = new Label();
            txtLastName = new TextBox();
            txtFirstName = new TextBox();
            lblPassword = new Label();
            lblUsername = new Label();
            txtPassword = new TextBox();
            txtUsername = new TextBox();
            btnSignUp = new Button();
            errorFirstName = new ErrorProvider(components);
            errorLastName = new ErrorProvider(components);
            errorUsername = new ErrorProvider(components);
            errorPassword = new ErrorProvider(components);
            ((System.ComponentModel.ISupportInitialize)errorFirstName).BeginInit();
            ((System.ComponentModel.ISupportInitialize)errorLastName).BeginInit();
            ((System.ComponentModel.ISupportInitialize)errorUsername).BeginInit();
            ((System.ComponentModel.ISupportInitialize)errorPassword).BeginInit();
            SuspendLayout();
            // 
            // btnClose
            // 
            btnClose.BackColor = Color.Crimson;
            btnClose.FlatAppearance.BorderSize = 0;
            btnClose.FlatStyle = FlatStyle.Flat;
            btnClose.Font = new Font("Segoe UI", 15F, FontStyle.Bold);
            btnClose.ForeColor = SystemColors.ButtonHighlight;
            btnClose.Location = new Point(550, -7);
            btnClose.Name = "btnClose";
            btnClose.Size = new Size(44, 38);
            btnClose.TabIndex = 8;
            btnClose.Text = "x";
            btnClose.UseVisualStyleBackColor = false;
            btnClose.Click += btnClose_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.Transparent;
            label1.Font = new Font("Segoe UI", 40F, FontStyle.Bold);
            label1.ForeColor = SystemColors.ButtonHighlight;
            label1.Location = new Point(176, 60);
            label1.Name = "label1";
            label1.Size = new Size(245, 72);
            label1.TabIndex = 9;
            label1.Text = "SIGN UP";
            // 
            // lblLastName
            // 
            lblLastName.AutoSize = true;
            lblLastName.BackColor = Color.Transparent;
            lblLastName.Font = new Font("Segoe UI", 13F, FontStyle.Bold);
            lblLastName.ForeColor = SystemColors.ButtonHighlight;
            lblLastName.Location = new Point(137, 264);
            lblLastName.Name = "lblLastName";
            lblLastName.Size = new Size(98, 25);
            lblLastName.TabIndex = 13;
            lblLastName.Text = "Last name";
            // 
            // lblFirstName
            // 
            lblFirstName.AutoSize = true;
            lblFirstName.BackColor = Color.Transparent;
            lblFirstName.Font = new Font("Segoe UI", 13F, FontStyle.Bold);
            lblFirstName.ForeColor = SystemColors.ButtonHighlight;
            lblFirstName.Location = new Point(137, 173);
            lblFirstName.Name = "lblFirstName";
            lblFirstName.Size = new Size(100, 25);
            lblFirstName.TabIndex = 12;
            lblFirstName.Text = "First name";
            // 
            // txtLastName
            // 
            txtLastName.Font = new Font("Segoe UI", 15F);
            txtLastName.Location = new Point(137, 295);
            txtLastName.Name = "txtLastName";
            txtLastName.Size = new Size(326, 34);
            txtLastName.TabIndex = 11;
            txtLastName.TextChanged += this.txtLastName_TextChanged;
            // 
            // txtFirstName
            // 
            txtFirstName.Font = new Font("Segoe UI", 15F);
            txtFirstName.Location = new Point(137, 211);
            txtFirstName.Name = "txtFirstName";
            txtFirstName.Size = new Size(326, 34);
            txtFirstName.TabIndex = 10;
            txtFirstName.TextChanged += this.txtFirstName_TextChanged;
            // 
            // lblPassword
            // 
            lblPassword.AutoSize = true;
            lblPassword.BackColor = Color.Transparent;
            lblPassword.Font = new Font("Segoe UI", 13F, FontStyle.Bold);
            lblPassword.ForeColor = SystemColors.ButtonHighlight;
            lblPassword.Location = new Point(137, 482);
            lblPassword.Name = "lblPassword";
            lblPassword.Size = new Size(92, 25);
            lblPassword.TabIndex = 17;
            lblPassword.Text = "Password";
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.BackColor = Color.Transparent;
            lblUsername.Font = new Font("Segoe UI", 13F, FontStyle.Bold);
            lblUsername.ForeColor = SystemColors.ButtonHighlight;
            lblUsername.Location = new Point(137, 391);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(97, 25);
            lblUsername.TabIndex = 16;
            lblUsername.Text = "Username";
            // 
            // txtPassword
            // 
            txtPassword.Font = new Font("Segoe UI", 15F);
            txtPassword.Location = new Point(137, 513);
            txtPassword.Name = "txtPassword";
            txtPassword.PasswordChar = '•';
            txtPassword.Size = new Size(326, 34);
            txtPassword.TabIndex = 15;
            txtPassword.TextChanged += this.txtPassword_TextChanged;
            // 
            // txtUsername
            // 
            txtUsername.Font = new Font("Segoe UI", 15F);
            txtUsername.Location = new Point(137, 429);
            txtUsername.Name = "txtUsername";
            txtUsername.Size = new Size(326, 34);
            txtUsername.TabIndex = 14;
            txtUsername.TextChanged += this.txtUsername_TextChanged;
            // 
            // btnSignUp
            // 
            btnSignUp.BackColor = Color.Transparent;
            btnSignUp.FlatAppearance.BorderSize = 2;
            btnSignUp.FlatStyle = FlatStyle.Flat;
            btnSignUp.Font = new Font("Segoe UI", 12F, FontStyle.Bold);
            btnSignUp.ForeColor = SystemColors.ButtonFace;
            btnSignUp.Location = new Point(193, 614);
            btnSignUp.Name = "btnSignUp";
            btnSignUp.Size = new Size(207, 58);
            btnSignUp.TabIndex = 18;
            btnSignUp.Text = "SIGN UP";
            btnSignUp.UseVisualStyleBackColor = false;
            btnSignUp.Click += btnSignUp_Click;
            // 
            // errorFirstName
            // 
            errorFirstName.ContainerControl = this;
            // 
            // errorLastName
            // 
            errorLastName.ContainerControl = this;
            // 
            // errorUsername
            // 
            errorUsername.ContainerControl = this;
            // 
            // errorPassword
            // 
            errorPassword.ContainerControl = this;
            // 
            // frmSignUp
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackgroundImage = (Image)resources.GetObject("$this.BackgroundImage");
            BackgroundImageLayout = ImageLayout.Stretch;
            ClientSize = new Size(590, 710);
            Controls.Add(btnSignUp);
            Controls.Add(lblPassword);
            Controls.Add(lblUsername);
            Controls.Add(txtPassword);
            Controls.Add(txtUsername);
            Controls.Add(lblLastName);
            Controls.Add(lblFirstName);
            Controls.Add(txtLastName);
            Controls.Add(txtFirstName);
            Controls.Add(label1);
            Controls.Add(btnClose);
            FormBorderStyle = FormBorderStyle.None;
            Name = "frmSignUp";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)errorFirstName).EndInit();
            ((System.ComponentModel.ISupportInitialize)errorLastName).EndInit();
            ((System.ComponentModel.ISupportInitialize)errorUsername).EndInit();
            ((System.ComponentModel.ISupportInitialize)errorPassword).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnClose;
        private Label label1;
        private Label lblLastName;
        private Label lblFirstName;
        private TextBox txtLastName;
        private TextBox txtFirstName;
        private Label lblPassword;
        private Label lblUsername;
        private TextBox txtPassword;
        private TextBox txtUsername;
        private Button btnSignUp;
        private ErrorProvider errorFirstName;
        private ErrorProvider errorLastName;
        private ErrorProvider errorUsername;
        private ErrorProvider errorPassword;
    }
}