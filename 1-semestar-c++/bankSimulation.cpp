#include <iostream>
using namespace std;

void deposit(float&, float);
void withdraw(float&, float);
void checkBalance(float);

int main() {
	
	float balance = 0.0f;
	int choice;
	int ongoingProgram = true;
	while (ongoingProgram) {

		system("cls");
		cout << "	Menu	" << endl;
		cout << "1. Deposit" << endl;
		cout << "2. Withdrawal" << endl;
		cout << "3. Balance" << endl;
		cout << "4. Exit" << endl;
		cout << endl;
		cout << "Please enter an option: ";
		cin >> choice;

		float amountToDeposit = 0.0f;
		float amountToWithdraw = 0.0f;
		switch (choice)
		{
		case 1:
			amountToDeposit = 0.0f;
			cout << "Please enter the amount you want to deposit: ";
			cin >> amountToDeposit;
			deposit(balance, amountToDeposit);
			break;

		case 2:
			amountToWithdraw = 0.0f;
			cout << "Please enter the amount you want to withdraw: ";
			cin >> amountToWithdraw;
			withdraw(balance, amountToWithdraw);
			break;

		case 3:
			checkBalance(balance);
			break;

		case 4: ongoingProgram = false;
			break;

		default:
			cout << "You have enter an improper number! " << endl;
			break;
		}
		cout << endl;
		system("pause");
	}

	cout << "Goodbye!" << endl;

	return 0;
}

void deposit(float& balance, float amount) {
	balance += amount;
	cout << "New balance is on your account " << balance << " $." << endl;
}

void withdraw(float& balance, float amount) {
	if (amount <= balance) {
		balance -= amount;
		cout << "New balance is on your account " << balance << " $." << endl;
	}
	else {
		cout << "You do not have enough funds on your account to complete this transaction!" << endl;
	}
}

void checkBalance(float balance) {
	cout << "The balance on your account is " << balance << " $" << endl;
}
