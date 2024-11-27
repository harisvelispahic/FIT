using System.CodeDom;
using System.Data;
using System.Net;

namespace Calculator
{
    enum Operations // statically named integers 0,1,2,3,....
    {
        Addition, /*= 10*/
        Subtraction,
        Multiplication,
        Division
    }
    public partial class frmCalculator : Form
    {
        private double Buffer { get; set; } = double.NaN;
        private Stack<Operations> OperationsStack { get; set; }
        public frmCalculator()
        {
            InitializeComponent();
            OperationsStack = new Stack<Operations>();
        }

        private void NumberButtonsHandler(object sender, EventArgs e)
        {
            var btnText = ((Button)sender).Text;
            if (btnText == ".")
            {
                if (!txtOutput.Text.Contains("."))
                {
                    txtOutput.Text += btnText;
                }
            }
            else
            {
                txtOutput.Text += btnText;
            }
        }

        private void btnAddition_Click(object sender, EventArgs e)
        {
            //PerformOperation();
            if (double.IsNaN(Buffer))
            {
                Buffer = double.Parse(txtOutput.Text);
            }
            else if (OperationsStack.Count != 0)
            {
                var operation = OperationsStack.Pop();
                Evaluate(operation);
            }

            OperationsStack.Push(Operations.Addition);
            txtOutput.Clear();
        }

        //private void PerformOperation()
        //{
        //    if (double.IsNaN(Buffer))
        //    {
        //        Buffer = double.Parse(txtOutput.Text);
        //    }
        //    else if (OperationsStack.Count != 0)
        //    {
        //        var operation = OperationsStack.Pop();
        //        Evaluate(operation);
        //    }

        //    OperationsStack.Push(Operations.Addition);
        //    txtOutput.Clear();
        //}

        private void btnSubtraction_Click(object sender, EventArgs e)
        {
            if (double.IsNaN(Buffer))
            {
                Buffer = double.Parse(txtOutput.Text);
            }
            else if (OperationsStack.Count != 0)
            {
                var operation = OperationsStack.Pop();
                Evaluate(operation);
            }

            OperationsStack.Push(Operations.Subtraction);
            txtOutput.Clear();
        }

        private void btnMultiplication_Click(object sender, EventArgs e)
        {
            if (double.IsNaN(Buffer))
            {
                Buffer = double.Parse(txtOutput.Text);
            }
            else if (OperationsStack.Count != 0)
            {
                var operation = OperationsStack.Pop();
                Evaluate(operation);
            }

            OperationsStack.Push(Operations.Multiplication);
            txtOutput.Clear();
        }

        private void btnDivision_Click(object sender, EventArgs e)
        {
            if (double.IsNaN(Buffer))
            {
                Buffer = double.Parse(txtOutput.Text);
            }
            else if (OperationsStack.Count != 0)
            {
                var operation = OperationsStack.Pop();
                Evaluate(operation);
            }

            OperationsStack.Push(Operations.Division);
            txtOutput.Clear();
        }

        private void Evaluate(Operations operation)
        {
            switch (operation)
            {
                case Operations.Addition:
                    Buffer += double.Parse(txtOutput.Text);
                    break;
                case Operations.Subtraction:
                    Buffer -= double.Parse(txtOutput.Text);
                    break;
                case Operations.Multiplication:
                    Buffer *= double.Parse(txtOutput.Text);
                    break;
                case Operations.Division:
                    Buffer /= double.Parse(txtOutput.Text);
                    break;
            }
            txtOutput.Text = Buffer.ToString();
            lblBuffer.Text = Buffer.ToString();
        }

        private void btnEquals_Click(object sender, EventArgs e)
        {
            if(!string.IsNullOrEmpty(txtOutput.Text))
            {
                if(OperationsStack.Count != 0)
                {
                    var operation = OperationsStack.Pop();
                    Evaluate(operation);
                }
            }
            txtOutput.Text = Buffer.ToString();
            lblBuffer.Text = Buffer.ToString();

            OperationsStack.Clear();
        }
    }
}