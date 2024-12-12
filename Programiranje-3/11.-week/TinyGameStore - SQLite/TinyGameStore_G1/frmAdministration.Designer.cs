namespace TinyGameStore_G1
{
    partial class frmAdministration
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
            cmbUsers = new ComboBox();
            dgvOwnedGames = new DataGridView();
            btnTestingConfig = new Button();
            ((System.ComponentModel.ISupportInitialize)dgvOwnedGames).BeginInit();
            SuspendLayout();
            // 
            // cmbUsers
            // 
            cmbUsers.FormattingEnabled = true;
            cmbUsers.Location = new Point(12, 12);
            cmbUsers.Name = "cmbUsers";
            cmbUsers.Size = new Size(317, 23);
            cmbUsers.TabIndex = 0;
            cmbUsers.SelectedIndexChanged += cmbUsers_SelectedIndexChanged;
            // 
            // dgvOwnedGames
            // 
            dgvOwnedGames.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvOwnedGames.Location = new Point(12, 41);
            dgvOwnedGames.Name = "dgvOwnedGames";
            dgvOwnedGames.RowTemplate.Height = 25;
            dgvOwnedGames.Size = new Size(776, 397);
            dgvOwnedGames.TabIndex = 1;
            // 
            // btnTestingConfig
            // 
            btnTestingConfig.Location = new Point(672, 12);
            btnTestingConfig.Name = "btnTestingConfig";
            btnTestingConfig.Size = new Size(116, 23);
            btnTestingConfig.TabIndex = 2;
            btnTestingConfig.Text = "TestingConfig";
            btnTestingConfig.UseVisualStyleBackColor = true;
            btnTestingConfig.Click += btnTestingConfig_Click;
            // 
            // frmAdministration
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(btnTestingConfig);
            Controls.Add(dgvOwnedGames);
            Controls.Add(cmbUsers);
            Name = "frmAdministration";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "frmAdministration";
            Load += frmAdministration_Load;
            ((System.ComponentModel.ISupportInitialize)dgvOwnedGames).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private ComboBox cmbUsers;
        private DataGridView dgvOwnedGames;
        private Button btnTestingConfig;
    }
}