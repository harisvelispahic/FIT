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
            this.cmbUsers = new System.Windows.Forms.ComboBox();
            this.dgvOwnedGames = new System.Windows.Forms.DataGridView();
            this.btnTestingConfig = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvOwnedGames)).BeginInit();
            this.SuspendLayout();
            // 
            // cmbUsers
            // 
            this.cmbUsers.FormattingEnabled = true;
            this.cmbUsers.Location = new System.Drawing.Point(12, 12);
            this.cmbUsers.Name = "cmbUsers";
            this.cmbUsers.Size = new System.Drawing.Size(317, 23);
            this.cmbUsers.TabIndex = 0;
            this.cmbUsers.SelectedIndexChanged += new System.EventHandler(this.cmbUsers_SelectedIndexChanged);
            // 
            // dgvOwnedGames
            // 
            this.dgvOwnedGames.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvOwnedGames.Location = new System.Drawing.Point(12, 41);
            this.dgvOwnedGames.Name = "dgvOwnedGames";
            this.dgvOwnedGames.RowTemplate.Height = 25;
            this.dgvOwnedGames.Size = new System.Drawing.Size(776, 397);
            this.dgvOwnedGames.TabIndex = 1;
            // 
            // btnTestingConfig
            // 
            this.btnTestingConfig.Location = new System.Drawing.Point(672, 12);
            this.btnTestingConfig.Name = "btnTestingConfig";
            this.btnTestingConfig.Size = new System.Drawing.Size(116, 23);
            this.btnTestingConfig.TabIndex = 2;
            this.btnTestingConfig.Text = "TestingConfig";
            this.btnTestingConfig.UseVisualStyleBackColor = true;
            this.btnTestingConfig.Click += new System.EventHandler(this.btnTestingConfig_Click);
            // 
            // frmAdministration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 448);
            this.Controls.Add(this.btnTestingConfig);
            this.Controls.Add(this.dgvOwnedGames);
            this.Controls.Add(this.cmbUsers);
            this.Name = "frmAdministration";
            this.Text = "frmAdministration";
            this.Load += new System.EventHandler(this.frmAdministration_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvOwnedGames)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private ComboBox cmbUsers;
        private DataGridView dgvOwnedGames;
        private Button btnTestingConfig;
    }
}