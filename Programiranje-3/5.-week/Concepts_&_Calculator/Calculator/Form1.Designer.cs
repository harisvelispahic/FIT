namespace Calculator
{
    partial class frmCalculator
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
            button1 = new Button();
            button2 = new Button();
            button3 = new Button();
            button4 = new Button();
            button5 = new Button();
            button6 = new Button();
            button7 = new Button();
            button8 = new Button();
            button9 = new Button();
            btnDivision = new Button();
            btnMultiplication = new Button();
            btnSubtraction = new Button();
            btnAddition = new Button();
            button0 = new Button();
            btnDot = new Button();
            btnEquals = new Button();
            txtOutput = new TextBox();
            lblBuffer = new Label();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button1.Location = new Point(12, 390);
            button1.Name = "button1";
            button1.Size = new Size(75, 75);
            button1.TabIndex = 0;
            button1.Text = "1";
            button1.UseVisualStyleBackColor = true;
            button1.Click += NumberButtonsHandler;
            // 
            // button2
            // 
            button2.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button2.Location = new Point(93, 390);
            button2.Name = "button2";
            button2.Size = new Size(75, 75);
            button2.TabIndex = 1;
            button2.Text = "2";
            button2.UseVisualStyleBackColor = true;
            button2.Click += NumberButtonsHandler;
            // 
            // button3
            // 
            button3.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button3.Location = new Point(174, 390);
            button3.Name = "button3";
            button3.Size = new Size(75, 75);
            button3.TabIndex = 2;
            button3.Text = "3";
            button3.UseVisualStyleBackColor = true;
            button3.Click += NumberButtonsHandler;
            // 
            // button4
            // 
            button4.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button4.Location = new Point(12, 309);
            button4.Name = "button4";
            button4.Size = new Size(75, 75);
            button4.TabIndex = 3;
            button4.Text = "4";
            button4.UseVisualStyleBackColor = true;
            button4.Click += NumberButtonsHandler;
            // 
            // button5
            // 
            button5.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button5.Location = new Point(93, 309);
            button5.Name = "button5";
            button5.Size = new Size(75, 75);
            button5.TabIndex = 4;
            button5.Text = "5";
            button5.UseVisualStyleBackColor = true;
            button5.Click += NumberButtonsHandler;
            // 
            // button6
            // 
            button6.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button6.Location = new Point(174, 309);
            button6.Name = "button6";
            button6.Size = new Size(75, 75);
            button6.TabIndex = 5;
            button6.Text = "6";
            button6.UseVisualStyleBackColor = true;
            button6.Click += NumberButtonsHandler;
            // 
            // button7
            // 
            button7.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button7.Location = new Point(12, 228);
            button7.Name = "button7";
            button7.Size = new Size(75, 75);
            button7.TabIndex = 6;
            button7.Text = "7";
            button7.UseVisualStyleBackColor = true;
            button7.Click += NumberButtonsHandler;
            // 
            // button8
            // 
            button8.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button8.Location = new Point(93, 228);
            button8.Name = "button8";
            button8.Size = new Size(75, 75);
            button8.TabIndex = 7;
            button8.Text = "8";
            button8.UseVisualStyleBackColor = true;
            button8.Click += NumberButtonsHandler;
            // 
            // button9
            // 
            button9.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button9.Location = new Point(174, 228);
            button9.Name = "button9";
            button9.Size = new Size(75, 75);
            button9.TabIndex = 8;
            button9.Text = "9";
            button9.UseVisualStyleBackColor = true;
            button9.Click += NumberButtonsHandler;
            // 
            // btnDivision
            // 
            btnDivision.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            btnDivision.Location = new Point(255, 228);
            btnDivision.Name = "btnDivision";
            btnDivision.Size = new Size(75, 75);
            btnDivision.TabIndex = 13;
            btnDivision.Text = "÷";
            btnDivision.UseVisualStyleBackColor = true;
            btnDivision.Click += btnDivision_Click;
            // 
            // btnMultiplication
            // 
            btnMultiplication.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            btnMultiplication.Location = new Point(255, 309);
            btnMultiplication.Name = "btnMultiplication";
            btnMultiplication.Size = new Size(75, 75);
            btnMultiplication.TabIndex = 14;
            btnMultiplication.Text = "×";
            btnMultiplication.UseVisualStyleBackColor = true;
            btnMultiplication.Click += btnMultiplication_Click;
            // 
            // btnSubtraction
            // 
            btnSubtraction.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            btnSubtraction.Location = new Point(255, 390);
            btnSubtraction.Name = "btnSubtraction";
            btnSubtraction.Size = new Size(75, 75);
            btnSubtraction.TabIndex = 15;
            btnSubtraction.Text = "−";
            btnSubtraction.UseVisualStyleBackColor = true;
            btnSubtraction.Click += btnSubtraction_Click;
            // 
            // btnAddition
            // 
            btnAddition.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            btnAddition.Location = new Point(255, 471);
            btnAddition.Name = "btnAddition";
            btnAddition.Size = new Size(75, 75);
            btnAddition.TabIndex = 16;
            btnAddition.Text = "+";
            btnAddition.UseVisualStyleBackColor = true;
            btnAddition.Click += btnAddition_Click;
            // 
            // button0
            // 
            button0.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            button0.Location = new Point(12, 471);
            button0.Name = "button0";
            button0.Size = new Size(156, 75);
            button0.TabIndex = 17;
            button0.Text = "0";
            button0.UseVisualStyleBackColor = true;
            button0.Click += NumberButtonsHandler;
            // 
            // btnDot
            // 
            btnDot.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            btnDot.Location = new Point(174, 471);
            btnDot.Name = "btnDot";
            btnDot.Size = new Size(75, 75);
            btnDot.TabIndex = 18;
            btnDot.Text = ".";
            btnDot.UseVisualStyleBackColor = true;
            btnDot.Click += NumberButtonsHandler;
            // 
            // btnEquals
            // 
            btnEquals.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            btnEquals.Location = new Point(12, 553);
            btnEquals.Name = "btnEquals";
            btnEquals.Size = new Size(318, 75);
            btnEquals.TabIndex = 20;
            btnEquals.Text = "=";
            btnEquals.UseVisualStyleBackColor = true;
            btnEquals.Click += btnEquals_Click;
            // 
            // txtOutput
            // 
            txtOutput.Font = new Font("Segoe UI", 25F, FontStyle.Regular, GraphicsUnit.Point);
            txtOutput.Location = new Point(12, 49);
            txtOutput.Multiline = true;
            txtOutput.Name = "txtOutput";
            txtOutput.ReadOnly = true;
            txtOutput.RightToLeft = RightToLeft.Yes;
            txtOutput.Size = new Size(318, 170);
            txtOutput.TabIndex = 21;
            // 
            // lblBuffer
            // 
            lblBuffer.AutoSize = true;
            lblBuffer.Font = new Font("Segoe UI", 20F, FontStyle.Regular, GraphicsUnit.Point);
            lblBuffer.Location = new Point(12, 9);
            lblBuffer.Name = "lblBuffer";
            lblBuffer.Size = new Size(0, 37);
            lblBuffer.TabIndex = 22;
            // 
            // frmCalculator
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(348, 636);
            Controls.Add(lblBuffer);
            Controls.Add(txtOutput);
            Controls.Add(btnEquals);
            Controls.Add(btnDot);
            Controls.Add(button0);
            Controls.Add(btnAddition);
            Controls.Add(btnSubtraction);
            Controls.Add(btnMultiplication);
            Controls.Add(btnDivision);
            Controls.Add(button9);
            Controls.Add(button8);
            Controls.Add(button7);
            Controls.Add(button6);
            Controls.Add(button5);
            Controls.Add(button4);
            Controls.Add(button3);
            Controls.Add(button2);
            Controls.Add(button1);
            FormBorderStyle = FormBorderStyle.FixedDialog;
            Name = "frmCalculator";
            Text = "FIT Calculator";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private Button button2;
        private Button button3;
        private Button button4;
        private Button button5;
        private Button button6;
        private Button button7;
        private Button button8;
        private Button button9;
        private Button btnDivision;
        private Button btnMultiplication;
        private Button btnSubtraction;
        private Button btnAddition;
        private Button button0;
        private Button btnDot;
        private Button btnEquals;
        private TextBox txtOutput;
        private Label lblBuffer;
    }
}