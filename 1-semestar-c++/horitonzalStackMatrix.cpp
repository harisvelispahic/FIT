#include <iostream>
#include <iomanip>
using namespace std;

/*
	Write a program that allows the user to enter the dimensions of two matrices M1 and M2.
	Fill matrices M1 and M2 with random values in the range [1-20]
	Write a function:
	-> hstack [a function that receives as input parameters two matrices M1 and M2 and returns a new matrix M3
	which is formed by horizontal stacking of matrices M1 and M2
	Example:
	Let M1 be:
	1 2 3
	4 5 6
	7 8 9

	Let M2 be:
	4 10
	7 8
	1 1

	The resulting matrix M3 should look like this:
	1 2 3 4 10
	4 5 6 7 8
	7 8 9 1 1
*/

int** createMatrix(int rows, int columns) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[columns] {0};
	}
	return matrix;
}

int getRandomValue(int from, int to) {
	return rand() % (to - from + 1) + from;
}

void setRandomValues(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = getRandomValue(1, 20);
		}
	}
}

void printMatrix(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << setw(4) << matrix[i][j];
		}
		cout << endl;
	}
}
void deleteMatrix(int** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

int main() {

	int rows, columns1, columns2;

	cout << "Matrix 1: " << endl;
	do {
		cout << "Please enter the number of rows: ";
		cin >> rows;
		cin.clear();
		cout << "Please enter the number of columns: ";
		cin >> columns1;
		cin.clear();
	} while (rows < 1 || columns1 < 1);

	cout << endl;

	int** matrix1 = createMatrix(rows, columns1);
	setRandomValues(matrix1, rows, columns1);

	cout << "Matrix 2: " << endl;
	do {
		cout << "Please enter the number of columns: ";
		cin >> columns2;
		cin.clear();
	} while (columns2 < 1);

	cout << endl; cout << endl;

	int** matrix2 = createMatrix(rows, columns2);
	setRandomValues(matrix2, rows, columns2);

	cout << "Matrix 1: " << endl;
	printMatrix(matrix1, rows, columns1);
	cout << endl;
	cout << "Matrix 2: " << endl;
	printMatrix(matrix2, rows, columns2);

	int** matrix3 = createMatrix(rows, columns1 + columns2);


	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns1; j++) {
			matrix3[i][j] = matrix1[i][j];
		}
	}
	
	for (int i = 0; i < rows; i++) {
		for (int j = columns1; j < columns1 + columns2; j++) {
			matrix3[i][j] = matrix2[i][j - columns1];
		}
	}

	cout << "Matrix 1 and matrix 2, stacked horionzontaly: " << endl;
	printMatrix(matrix3, rows, columns1 + columns2);

	deleteMatrix(matrix3, rows);
	deleteMatrix(matrix2, rows);
	deleteMatrix(matrix1, rows);

	return 0;
}