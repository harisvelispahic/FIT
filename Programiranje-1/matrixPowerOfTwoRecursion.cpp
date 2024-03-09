#include <iostream>
#include <iomanip>
using namespace std;

/*
	Let a 2D array of type int with dimensions 10x10 be given. Create, and then test in the main program,
    following functions:

    a) A function that generates data in a 2D array in such a way that in the element with index [0][0]
    enter the value 1 and each subsequent element to have the value of the previous element multiplied by 2
    like on the picture. Generation is interrupted if an overflow occurs on the int variable.

    b) The function that transposes the completed matrix from sub-task a) by replacing its rows and columns.

    c) A function that calculates the arithmetic mean of the elements on the "black fields" 
    above the main diagonal as in the picture

     +------+------+------+------+------+------+------+------+------+------+
     |  1   |  2   |  4   |  8   |  16  |  32  |  64  | 128  | 256  | 512  |
     +------+------+------+------+------+------+------+------+------+------+
     | 1024 | 2048 | etc. | etc. | etc. | etc. | etc. | etc. | etc. | etc. |
     +------+------+------+------+------+------+------+------+------+------+
     |      |      |      |      |      |      |      |      |      |      |
     +------+------+------+------+------+------+------+------+------+------+
     |      |      |      |      |      |      |      |      |      |      |
     +------+------+------+------+------+------+------+------+------+------+
     |      |      |      |      |      |      |      |      |      |      |
     +------+------+------+------+------+------+------+------+------+------+
     |      |      |      |      |      |      |      |      |      |      |
     +------+------+------+------+------+------+------+------+------+------+
     |      |      |      |      |      |      |      |      |      |      |
     +------+------+------+------+------+------+------+------+------+------+
     |      |      |      |      |      |      |      |      |      |      |
     +------+------+------+------+------+------+------+------+------+------+
     |      |      |      |      |      |      |      |      |      |      |
     +------+------+------+------+------+------+------+------+------+------+
     |      |      |      |      |      |      |      |      |      |      |
     +------+------+------+------+------+------+------+------+------+------+
*/

long long int** createMatrix(int size) {
    long long int** matrix = new long long int* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new long long int[size] {0};
    }
    return matrix;
}

/*
    a) A function that generates data in a 2D array in such a way that in the element with index [0][0]
    enter the value 1 and each subsequent element to have the value of the previous element multiplied by 2
    like on the picture. Generation is interrupted if an overflow occurs on the int variable.
*/

void enterMatrix(long long int** matrix, int size, int i = 0, int j = 0) {
    if (j == size) {
        i++;
        j = 0;
    }
    long long int temp = pow(2, i * size + j);
    if (i == size || temp <= 0)
        return;
    *(*(matrix + i) + j) = temp;

    enterMatrix(matrix, size, i, j + 1);
}

void printMatrix(long long int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(20) << matrix[i][j];
        }
        cout << endl;
    }
}

//  b) A function that transposes the completed matrix from sub-task a) by replacing its rows and columns.

long long int** transposeMatrix(long long int** matrix, long long int** transposedMatrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            transposedMatrix[i][j] = matrix[j][i];
        }
    }
    return transposedMatrix;
}

    //c) A function that calculates the arithmetic mean of the elements on the "black squares" 
    //above the main diagonal

long long int getArithmeticMean(long long int** matrix, int size) {
    long long int sum = 0;
    int counter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i < j && ((i + j) % 2 != 0)) {
                sum += matrix[i][j];
                counter++;
            }
        }
    }
    return double(sum) / counter;
}


void deleteMatrix(long long int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}

int main() {

    int size = 0;
    do {
        cout << "Please enter the size of the field: ";
        cin >> size;
    } while (size < 1);

    long long int** field = createMatrix(size);

    enterMatrix(field, size);
    cout << "The matrix filled with powers of two: " << endl;
    printMatrix(field, size);
    
    cout << endl; cout << endl;

    long long int** transposedField = createMatrix(size);

    transposeMatrix(field, transposedField, size);
    cout << "The matrix [rows switched switched with columns]: " << endl;
    printMatrix(transposedField, size);

    cout << endl; cout << endl;

    cout << "The arithmetic mean of the black squares above the main diagonal: " <<
        getArithmeticMean(field, size) << endl;

    deleteMatrix(transposedField, size);
    deleteMatrix(field, size);

    return 0;
}