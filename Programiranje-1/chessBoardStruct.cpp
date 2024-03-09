#include <iostream>
using namespace std;

/*
	Create a dynamic two-dimensional array whose elements are shape objects
    (figure is a structure whose characteristics are given below). Allow the user to enter the dimensions of the 
    array, and enable input of elements. Ensure that there is the same number of columns and rows.

    It is necessary to create a function that will check whether the figures on the white fields are 
    symmetrically distributed by height in relation to the main diagonal (is the height of the figure at 
    position 0.1 equal to the height of the figure at position 1.0 etc. for all white fields).

    The function should return a pointer to the memory location where the sum of the heights of the figure is 
    written if it is a table symmetrically distributed, and the number -1 if not symmetrically distributed.

    struct figure
    {
        int ID;
        char *figureName;
        float *figureHeight;
    };
*/

struct figure
{
    int ID;
    char* figureName;  //K - king, Q - queen, B - bishop, N - knight, R - rook, P - pawn
    float* figureHeight;

    figure() {
        ID = 0;
        figureName = new char;
        figureHeight = new float;
    }

    ~figure() {
        delete figureName;
        delete figureHeight;
    }
};

bool isMatrixHeightSymmetrical(figure** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((i + j) % 2 != 0) {
                if (*(matrix[i][j].figureHeight) != *(matrix[j][i].figureHeight)) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {

    int rows, columns;
    do {
        cout << "Please enter the size of the chess board (rows = columns): " << endl;
        cout << "Enter rows: ";
        cin >> rows;
        cout << "Enter columns: ";
        cin >> columns;
    } while (rows < 1 || columns < 1 || rows != columns);
    cout << endl;

    figure** matrix = new figure*[rows];

    for (int i = 0; i < rows; i++) {
        matrix[i] = new figure[columns];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j].ID = i * rows + j;
            do {
                char tempChar;
                cout << "Please input the name of the " << i * rows + j + 1 << ". figure: ";
                cin >> tempChar;
                *(matrix[i][j].figureName) = tempChar;
            } while (*(matrix[i][j].figureName) != 'K' && *(matrix[i][j].figureName) != 'Q'
                && *(matrix[i][j].figureName) != 'B' && *(matrix[i][j].figureName) != 'N'
                && *(matrix[i][j].figureName) != 'R' && *(matrix[i][j].figureName) != 'P'
                && *(matrix[i][j].figureName) != 'k' && *(matrix[i][j].figureName) != 'q'
                && *(matrix[i][j].figureName) != 'b' && *(matrix[i][j].figureName) != 'n'
                && *(matrix[i][j].figureName) != 'r' && *(matrix[i][j].figureName) != 'p');

            float tempFloat = 0.0f;
            cout << "Please input the height of the " << i * rows + j + 1 << ". figure: ";
            cin >> tempFloat;
            *(matrix[i][j].figureHeight) = tempFloat;
            cout << endl;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << "ID of the " << i * rows + j + 1 << ". figure: " << matrix[i][j].ID << endl;
            cout << "Name of the " << i * rows + j + 1 << ". figure: " << *(matrix[i][j].figureName) << endl;
            cout << "Height of the " << i * rows + j + 1 << ". figure: " << *(matrix[i][j].figureHeight) << endl;
            cout << endl;
        }
        cout << endl;
    }

    (isMatrixHeightSymmetrical(matrix, rows, columns)) ? cout << "The matrix is symmetrical according to figure height." << endl :
        cout << "The matrix is not symmetrical according to figure height." << endl;




    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;

    return 0;
}