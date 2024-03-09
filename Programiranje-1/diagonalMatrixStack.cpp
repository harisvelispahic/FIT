#include <iostream>
#include <iomanip>
using namespace std;

int getRandomValue(int from, int to) {
	return rand() % (to - from + 1) + from;
}

int** createMatrix(int rows, int columns) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[columns] {0};
	}
	return matrix;
}

void setRandomValues(int** matrix, int rows, int columns, int from, int to) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = getRandomValue(from, to);
		}
	}
}

void printMatrix(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << setw(3) << matrix[i][j];
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

int** diagonalStack(int** matrix1, int rows1, int columns1, int** matrix2, int rows2, int columns2) {
	int** matrix3 = createMatrix(rows1 + rows2, columns1 + columns2);
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns1; j++) {
			matrix3[i][j] = matrix1[i][j];
		}
	}
	for (int i = rows1; i < rows1 + rows2; i++) {
		for (int j = columns1; j < columns1 + columns2; j++) {
			matrix3[i][j] = matrix2[i - rows1][j - columns1];
		}
	}
	return matrix3;
}

int main() {
	int rows1, columns1, rows2, columns2;
	do {
		cout << "Please enter number of rows for the first matrix: ";
		cin >> rows1;
	} while (rows1 < 1);
	do {
		cout << "Please enter number of columns for the first matrix: ";
		cin >> columns1;
	} while (columns1 < 1);

	int** matrix1 = createMatrix(rows1, columns1);
	setRandomValues(matrix1, rows1, columns1, 1, 10);
	cout << "The first matrix: " << endl;
	printMatrix(matrix1, rows1, columns1);

	cout << endl; system("pause"); cout << endl;

	do {
		cout << "Please enter number of rows for the second matrix: ";
		cin >> rows2;
	} while (rows2 < 1);
	do {
		cout << "Please enter number of columns for the second matrix: ";
		cin >> columns2;
	} while (columns2 < 1);

	cout << endl;

	int** matrix2 = createMatrix(rows2, columns2);
	setRandomValues(matrix2, rows2, columns2, 1, 10);
	cout << "The second matrix: " << endl;
	printMatrix(matrix2, rows2, columns2);

	cout << endl; system("pause"); cout << endl;


	int** matrix3 = diagonalStack(matrix1, rows1, columns1, matrix2, rows2, columns2);
	cout << "The matrices stacked diagonaly: " << endl;
	printMatrix(matrix3, rows1 + rows2, columns1 + columns2);


	deleteMatrix(matrix3, rows1 + rows2);
	deleteMatrix(matrix2, rows2);
	deleteMatrix(matrix1, rows1);

	return 0;
}