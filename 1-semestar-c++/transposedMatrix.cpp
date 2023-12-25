#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

/*
	Program that transposes a matrix (of random values [1 - 10])
	
	For example:

	1 2 3				1 4 7
	4 5 6		-->		2 5 8
	7 8 9				3 6 9
*/

const int MAX_ROWS = 50;
const int MAX_COLUMNS = 50;

int generateRandomValue(int from, int to) {
	return rand() % (to - from + 1) + from;
}

void generateMatrix(int matrix[][MAX_COLUMNS], const int rows, const int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = generateRandomValue(1, 10);
		}
	}
}

void printMatrix(int matrix[][MAX_COLUMNS], const int rows, const int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << setw(4) << matrix[i][j];
		}
		cout << endl;
	}
}

bool isSquare(int matrix[][MAX_COLUMNS], const int rows, const int columns) {
	return rows == columns;
}

void transposeMatrix(int matrix[][MAX_COLUMNS], const int rows, const int columns) {
	if (rows != columns) {
		cout << "Matrix must be a square!" << endl;
		return;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (j >= i) {
				int temp = matrix[i][j];
				matrix[i][j] = matrix[j][i];
				matrix[j][i] = temp;
			}
		}
	}
	printMatrix(matrix, rows, columns);
}

int main() {
	srand(time(NULL));

	int r, c;
	int matrix[MAX_ROWS][MAX_COLUMNS];
	cout << "Please input the number of rows: ";
	cin >> r;
	cout << "Please input the number of columns: ";
	cin >> c;

	generateMatrix(matrix, r, c);
	cout << "The initial matrix: " << endl;
	printMatrix(matrix, r, c);
	
	cout << endl;

	if (isSquare(matrix, r, c)) {
		cout << "The transposed matrix: " << endl;
		transposeMatrix(matrix, r, c);
	}

	return 0;
}