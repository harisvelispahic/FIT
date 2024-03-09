#include <iostream>
#include <iomanip>
using namespace std;

/*
	Declare a square matrix of integers of arbitrary dimensions with an even number of rows,
	and implement the following functions:

	• A function for entering and forming matrix elements according to the following pattern: 
	elements of odd rows of the matrix (1., 3., 5. etc.) are at least three-digit numbers entered by the 
	user (in case of entering any number that does not meet the set condition, repeat the entry);
	the elements of the even rows of the matrix are formed based on the elements from the previous row
	in the same column of the matrix in such a way that each newly created element of the matrix is actually
	the middle digit of the number above it in the matrix.

	• To find the middle digit of a number, create a separate function middle_digit,
	and call it in the input function. Form the middle digit of numbers with an even number of digits 
	as the middle digit the value of the two digits in the middle, e.g. number 4213 has two middle digits,
	and the function should return the value of the arithmetic mean of the digits 2 and 1 as the middle digit
	rounded to the next decimal place, in this case the number 2.


	Create a short test program that demonstrates the functionality of the created functions.

	An example of a 4x4 matrix and expected results is given below.

	2163	123		30452	671
	4		2		4		7
	7331	6113	741232	798
	3		1		2		9

*/

int getMiddleDigit(int n) {
	int temp = n;
	int length = int(log10(n) + 1);
	if (length % 2 != 0) {
		for (int i = 0; i < length / 2; i++) {
			temp /= 10;
		}
		return temp % 10;
	}
	else {
		for (int i = 0; i < (length / 2) - 1; i++) {
			temp /= 10;
		}
		return ceil(double((temp % 10 + (temp % 100 / 10))) / 2);
	}
}


void enterMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i % 2 == 0) {
				do {
					cout << "Please enter the element at position [" << i << "][" << j << "]: ";
					cin >> matrix[i][j];
				} while (log10(matrix[i][j]) + 1 < 3);
			}
			else {
				matrix[i][j] = getMiddleDigit(matrix[i - 1][j]);
			}
		}
	}
}

void printMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << setw(4) << matrix[i][j] << " ";
		}
		cout << endl;
	}
}


int main() {

	int size;
	do {
		cout << "Please enter the matrix size: ";
		cin >> size;
	} while (size < 1 || size % 2 != 0);

	// dynamic memory allocation
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}

	enterMatrix(matrix, size);
	cout << endl; cout << endl;
	printMatrix(matrix, size);

	// dynamic memory deallocation
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;

	return 0;
}