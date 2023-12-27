#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 100;
/*
	9 10 11 12 13
	8 21 22 23 14
	7 20 25	24 15
	6 19 18 17 16
	5  4  3  2  1 

*/
int main() {

	int matrixSize;
	cout << "Please input the size of the matrix: ";
	do {
		cin >> matrixSize;
	} while (matrixSize < 0 || matrixSize>100);

	int matrix[MAX_SIZE][MAX_SIZE] = {};

	int counter = 1;
	int i = matrixSize - 1, j = matrixSize - 1;
	int orientation = 1;

	while(counter <= matrixSize*matrixSize){

		matrix[i][j] = counter;

		if (orientation == 1) {
			if (j - 1 < 0 || matrix[i][j - 1] != 0) {
				orientation = 2;
			}
		}

		if (orientation == 2) {
			if (i - 1 < 0 || matrix[i - 1][j] != 0) {
				orientation = 3;
			}
		}

		if (orientation == 3) {
			if (j + 1 > matrixSize - 1 || matrix[i][j + 1] != 0) {
				orientation = 4;
			}
		}

		if (orientation == 4) {
			if (i + 1 > matrixSize - 1 || matrix[i+1][j] != 0) {
				orientation = 1;
			}
		}
		

		if (orientation == 1) {
			j--;			
		}
		else if (orientation == 2) {
			i--;
		}
		else if (orientation == 3) {
			j++;
		}
		else if (orientation == 4) {
			i++;
		}

		counter++;
	}


	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			cout << setw(4) << matrix[i][j] << " ";
		}
		cout << endl;
	}
}