#include <iostream>
#include <iomanip>
using namespace std;

/*
	Write a program for adding matrices of arbitrary dimensions.
	Let two matrices A and B be given, which need to be filled with random values in the range [1-5]
	Form matrix C as the sum of matrices A and B:
	C[i,j] = A[i,j] + B[i,j]
*/

int** createMatrix(int rows, int columns) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		*(matrix + i) = new int[columns] {0};
	}
	return matrix;
}

int getRandomValue(int from, int to) {
	return rand() % (to - from + 1) + from;
}

void setRandomValues(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			*(*(matrix + i) + j) = getRandomValue(1, 5);
		}
	}
}

void printMatrix(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << setw(4) << *(*(matrix + i) + j);
		}
		cout << endl;
	}
}


int** addMatrices(int** matrix1, int** matrix2, int rows, int columns) {
	int** matrix3 = createMatrix(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
	return matrix3;
}


void deleteMatrix(int** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete* (matrix + i);
		*(matrix + i) = nullptr;
	}
	delete* matrix;
	matrix = nullptr;
}

int main() {

	int rows, columns;
	do {
		cout << "Please input the number of rows: ";
		cin >> rows;
		cin.clear();
		cout << "Please input the number of columns: ";
		cin >> columns;
		cin.clear();
	} while (rows < 1 || columns < 1);
	
	cout << endl;

	int** matrix1 = createMatrix(rows, columns);
	setRandomValues(matrix1, rows, columns);
	cout << "The first matrix: " << endl;
	printMatrix(matrix1, rows, columns);

	cout << endl;

	int** matrix2 = createMatrix(rows, columns);
	setRandomValues(matrix2, rows, columns);
	cout << "The second matrix: " << endl;
	printMatrix(matrix2, rows, columns);

	cout << endl;

	int** matrix3 = addMatrices(matrix1, matrix2, rows, columns);
	printMatrix(matrix3, rows, columns);


	deleteMatrix(matrix1, rows);
	deleteMatrix(matrix2, rows);
	deleteMatrix(matrix3, rows);

	return 0;
}