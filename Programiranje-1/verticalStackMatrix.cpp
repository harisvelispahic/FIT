#include <iostream>
#include <iomanip>
using namespace std;

/*
	Write a program that allows the user to enter the dimensions of two matrices M1 and M2.
	Fill matrices M1 and M2 with random values in the range [1-20]
	Write a function:
	-> vstack [a function that receives as input parameters two matrices M1 and M2 and returns a new matrix M3
	which is formed by vertical stacking of matrices M1 and M2
	
	Example:
	Let M1 be:
	1 2 3
	4 5 6
	7 8 9

	Let M2 be:
	4 10 5
	1 1 2

	The resulting matrix M3 should look like this:
	1 2 3
	4 5 6
	7 8 9
	4 10 5
	1 1 2
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

	int rows1, rows2, columns;

	cout << "Matrix 1: " << endl;
	do {
		cout << "Please enter the number of rows: ";
		cin >> rows1;
		cin.clear();
		cout << "Please enter the number of columns: ";
		cin >> columns;
		cin.clear();
	} while (rows1 < 1 || columns < 1);

	cout << endl;

	int** matrix1 = createMatrix(rows1, columns);
	setRandomValues(matrix1, rows1, columns);

	cout << "Matrix 2: " << endl;
	do {
		cout << "Please enter the number of rows: ";
		cin >> rows2;
		cin.clear();
	} while (rows2 < 1);

	cout << endl; cout << endl;

	int** matrix2 = createMatrix(rows2, columns);
	setRandomValues(matrix2, rows2, columns);

	cout << "Matrix 1: " << endl;
	printMatrix(matrix1, rows1, columns);
	cout << endl;
	cout << "Matrix 2: " << endl;
	printMatrix(matrix2, rows2, columns);

	int** matrix3 = createMatrix(rows1 + rows2, columns);
	
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns; j++) {
			matrix3[i][j] = matrix1[i][j];
		}
	}

	for (int i = rows1; i < rows1 + rows2; i++) {
		for (int j = 0; j < columns; j++) {
			matrix3[i][j] = matrix2[i - rows1][j];
		}
	}
	
	cout << "Matrix 1 and matrix 2, stacked verticaly: " << endl;
	printMatrix(matrix3, rows1 + rows2, columns);


	deleteMatrix(matrix3, rows1 + rows2);
	deleteMatrix(matrix2, rows2);
	deleteMatrix(matrix1, rows1);

	return 0;
}