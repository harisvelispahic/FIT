#include <iostream>
using namespace std;

int main() {

	char arrayField[21][60];

	for (int i = 0; i < 21; i++) {			//fill the matrix with blank spaces
		for (int j = 0; j < 60; j++) {
			arrayField[i][j] = ' ';
		}
	}

	for (int i = 0; i < 60; i++) {			//fill in the middle with '-'
		arrayField[10][i] = '-';
	}

	

	int number, limit = 0;
	bool outputNeeded = true;

	for (int i = 0; i < 60; i+=3) {
		cout << "Please enter a number [-10,10] at [" << i/3+1 << "]: ";
		cin >> number;

		if (number == 999) {
			cout << "Abort input!" << endl;
			break;
		}
		if ((number < -10 || number>10) && number != 999) {
			cout << "Number is not in the interval, program end!" << endl;
			outputNeeded = false;
			break;
		}

		if (number > 0) {
			for (int j = 10 - number; j < 10; j++) {
				if (j == 10 - number) {
					arrayField[j][i] = '*';
				}
				else {
					arrayField[j][i] = '|';
				}
			}
		}

		else if (number < 0) {
			for (int j = 10 + abs(number); j > 10; j--) {
				if (j == 10 + abs(number)) {
					arrayField[j][i] = '*';
				}
				else {
					arrayField[j][i] = '|';
				}
			}
		}

		else {
			arrayField[10][i] = '*';
		}

		limit += 3;
	}

	cout << endl;

	if (outputNeeded) {								//output
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < limit; j++) {
				cout << arrayField[i][j];
			}
			cout << endl;
		}
	}
	

	return 0;
}