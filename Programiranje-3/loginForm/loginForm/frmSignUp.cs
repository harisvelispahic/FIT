using Data;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace loginForm
{
    public partial class frmSignUp : Form
    {
        public frmSignUp()
        {
            InitializeComponent();
        }
        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }
        private bool isAuthValid(string text)
        {
            return !string.IsNullOrEmpty(text);
        }
        private void btnSignUp_Click(object sender, EventArgs e)
        {
            string firstName = txtFirstName.Text;
            string lastName = txtLastName.Text;
            string username = txtUsername.Text;
            string password = txtPassword.Text;

            if (!isAuthValid(firstName)) {
                errorFirstName.SetError(txtFirstName, "You must fill out this field!");
            }
            else {
                errorFirstName.Clear();
            }
            if (!isAuthValid(lastName)) {
                errorLastName.SetError(txtLastName, "You must fill out this field!");
            }
            else {
                errorLastName.Clear();
            }
            if (!isAuthValid(username)){
                errorUsername.SetError(txtUsername, "You must fill out this field!");
            }
            else {
                errorUsername.Clear();
            }
            if (!isAuthValid(password)) {
                errorPassword.SetError(txtPassword, "You must fill out this field!");
            }
            else {
                errorPassword.Clear();
            }

            if (!isAuthValid(firstName) || !isAuthValid(lastName) ||
                !isAuthValid(username) || !isAuthValid(password)) {
                return;
            }

            foreach (var user in Data.InternalDB.users)
            {
                if (user.Username == username) 
                {
                    MessageBox.Show("This username is not available!");
                    return;
                }
            }

            var newUser = new User(InternalDB.IDCounter++, firstName, lastName, username, password);
            InternalDB.users.Add(newUser);
            InternalDB.SaveUsers(); // Save the updated list

            MessageBox.Show("User signed up successfully!");
            this.Close();
        }

        private void txtFirstName_TextChanged(object sender, EventArgs e)
        {
            errorFirstName.Clear();
        }

        private void txtLastName_TextChanged(object sender, EventArgs e)
        {
            errorLastName.Clear();
        }

        private void txtUsername_TextChanged(object sender, EventArgs e)
        {
            errorUsername.Clear();
        }

        private void txtPassword_TextChanged(object sender, EventArgs e)
        {
            errorPassword.Clear();
        }
    }
}
