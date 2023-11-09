#include <iostream>
#include <ctime>
using namespace std;

void output(char [3][3]);

int main() {
	srand(time(NULL));
	int play;

	do {

	// main code
	char field[3][3]{
		{'1', '2', '3'},
		{'4', '5', '6'},
		{'7', '8', '9'}
	};

	output(field);

	bool xWin = false, oWin = false;
	int decideFirst = rand() % 2;
	char playingChar = ' ';
	bool gameOver = false;
	bool switchChars = true;

	if (decideFirst == 0)
		playingChar = 'O';
	else
		playingChar = 'X';

	cout << "The char that plays first is: " << playingChar << endl;
	cout << endl;


	for (int i = 0; i < 3 && !(xWin || oWin); i++) {
		for (int j = 0; j < 3 && !(xWin || oWin); j++) {
			switchChars = true;

			int xCord, yCord, number;
			cout << "Current player is: " << playingChar << endl;

			cout << "Enter the number where you want to place your char: ";
			do {
				cin >> number;
				if (number < 1 || number > 9)
					cout << "Number out of range. Please enter a number between 1 and 9: ";

			} while (number < 1 || number > 9);

			switch (number) {
			case 1: {
				xCord = 0; yCord = 0; break;
			}
			case 2: {
				xCord = 0; yCord = 1; break;
			}
			case 3: {
				xCord = 0; yCord = 2; break;
			}
			case 4: {
				xCord = 1; yCord = 0; break;
			}
			case 5: {
				xCord = 1; yCord = 1; break;
			}
			case 6: {
				xCord = 1; yCord = 2; break;
			}
			case 7: {
				xCord = 2; yCord = 0; break;
			}
			case 8: {
				xCord = 2; yCord = 1; break;
			}
			case 9: {
				xCord = 2; yCord = 2; break;
			}
			}

			if (field[xCord][yCord] == 'X' || field[xCord][yCord] == 'O') {
				cout << "Illegal move! Please enter again: " << endl;
				j--;
				switchChars = false;
			}
			else
				field[xCord][yCord] = playingChar;

			if (
				(field[0][0] == 'X' && field[1][1] == 'X' && field[2][2] == 'X') ||		//main diagonal
				(field[2][0] == 'X' && field[1][1] == 'X' && field[0][2] == 'X') ||		//secondary diagonal
				(field[0][0] == 'X' && field[0][1] == 'X' && field[0][2] == 'X') ||		//i=0
				(field[1][0] == 'X' && field[1][1] == 'X' && field[1][2] == 'X') ||		//i=1
				(field[2][0] == 'X' && field[2][1] == 'X' && field[2][2] == 'X') ||		//i=2
				(field[0][0] == 'X' && field[1][0] == 'X' && field[2][0] == 'X') ||		//j=0
				(field[0][1] == 'X' && field[1][1] == 'X' && field[2][1] == 'X') ||		//j=1
				(field[0][2] == 'X' && field[1][2] == 'X' && field[2][2] == 'X')		//j=2
				)
			{
				xWin = true;
				gameOver = true;
			}
			else if (
				(field[0][0] == 'O' && field[1][1] == 'O' && field[2][2] == 'O') ||		//main diagonal
				(field[2][0] == 'O' && field[1][1] == 'O' && field[0][2] == 'O') ||		//secondary diagonal
				(field[0][0] == 'O' && field[0][1] == 'O' && field[0][2] == 'O') ||		//i=0
				(field[1][0] == 'O' && field[1][1] == 'O' && field[1][2] == 'O') ||		//i=1
				(field[2][0] == 'O' && field[2][1] == 'O' && field[2][2] == 'O') ||		//i=2
				(field[0][0] == 'O' && field[1][0] == 'O' && field[2][0] == 'O') ||		//j=0
				(field[0][1] == 'O' && field[1][1] == 'O' && field[2][1] == 'O') ||		//j=1
				(field[0][2] == 'O' && field[1][2] == 'O' && field[2][2] == 'O')		//j=2
				)
			{
				oWin = true;
				gameOver = true;
			}

			output(field);


			if (xWin)
				cout << "The winner is " << "X!" << endl;

			else if (oWin)
				cout << "The winner is " << "\033[1;32mO!\033[0m" << endl;

			if (switchChars) {
				if (playingChar == 'X')
					playingChar = 'O';
				else
					playingChar = 'X';
			}

		}
	}
	if (gameOver == false)
		cout << "The game is a " << "DRAW!" << endl;

	cout << endl;

	// end of main code

	cout << "To play the game again, enter a number (number = -1 --> exit): ";
	cin >> play;
	cout << endl;

	} while (play != -1);
	cout << "Thank You for playing!" << endl;
	cout << endl;
	system("pause");

	return 0;
}

void output(char matrix[3][3]) {
	cout << "-------------------" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "|  ";
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == 'X')
				cout << matrix[i][j] << "  |  ";
			else if (matrix[i][j] == 'O') {
				cout <<  matrix[i][j] << "  |  ";
			}
			else
				cout << matrix[i][j] << "  |  ";
		}
		cout << endl;
		cout << "-------------------" << endl;
	}
}