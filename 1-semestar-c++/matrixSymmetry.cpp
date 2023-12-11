#include <iostream>
#include <vector>
using namespace std;

/*
    Napisati program koji ce ucitati cijeli broj n (1 <= n <= 10), 
    (ukoliko unesena vrijednost nije unutar intervala, 
    ucitavanje treba ponavljati sve dok se ne unese ispravna vrijednost) 
    i elemente matrice dimenzije n x n te ispisati da li je matrica centralno simetricna 
    s obrzirom na sredisnji element. 
    Ako jeste, program treba ispisati 1, ako nije ispisati 0, 
    a ako je broj redova paran (pa nema sredisnjeg elementa) ispisati -1. 
    Koristite posebne funkcije za unos elemenata i provjeru simetricnosti.
*/

int inputSize();
vector<vector<int>> inputMembers(int);
int checkSymmetry(vector<vector<int>>, int);


int main(){
    
    int matrixSize = inputSize();
    vector<vector<int>> matrix = inputMembers(matrixSize);
    if (checkSymmetry(matrix, matrixSize) == 1)
        cout << "The matrix you entered is SYMMETRICAL!" << endl;
    else if (checkSymmetry(matrix, matrixSize) == 0)
        cout << "The matrix you entered is not symmetrical!" << endl;
    else
        cout << "The matrix you entered has an even number of rows/columns!" << endl;

    return 0;
}

int inputSize() {
    int num;
    cout << "Enter the size of the matrix (1 to 10): ";
    cin >> num;
    while (num < 1 || num > 10) {
        cout << "Disallowed size of the matrix! Please enter again: ";
        cin >> num;
    }
    return num;
}

vector<vector<int>> inputMembers(int num) {
    
    cout << "Enter the members of the matrix: " << endl;
    vector<vector<int>> matrix;
    int temp = 0;
    for (int i = 0; i < num; i++) {
        vector<int> row;
        for (int j = 0; j < num; j++) {
            cin >> temp;
            row.push_back(temp);
        }
        matrix.push_back(row);
    }
    cout << endl;

    for (int i = 0; i < num; i++) {                                     //matrix output
        for (int j = 0; j < num; j++) {
            cout << matrix.at(i).at(j) << " ";
        }
        cout << endl;
    }

    return matrix;
}

int checkSymmetry(vector<vector<int>> matrix, int size) {
    if (size % 2 == 0)
        return -1;
    int symmetric = 0;
    
    int middle = size / 2;
    int max = size - 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (
                (i == j && matrix.at(i).at(j) == matrix.at(max-i).at(max-j)) &&      //main diagonal
                (i + j == size - 1 && matrix.at(i).at(j) == matrix.at(j).at(i)) &&   //secondary diagonal
                (matrix.at(middle).at(j) == matrix.at(middle).at(max-j)) &&          //horizontal middle
                (matrix.at(i).at(middle) == matrix.at(max-i).at(middle))             //vertical middle
                ) {
                symmetric = 1;
            }
        }
    }
    return symmetric;
}