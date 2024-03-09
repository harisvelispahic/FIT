#include <iostream>
using namespace std;

/*
	Create a two-dimensional dynamic array whose elements are figure-type objects
	(the figure is a structure whose characteristics are given below).

	struct Figure
	{
		int ID;
		char* name;
		float* height;
	};

	
	Allow the user to enter the dimensions of the array and allow the entry of elements.
	Ensure that there is the same number of columns and rows.

	It is necessary to create a function that will check whether the white fields are symmetrical
	arranged in height in relation to the black field on the other side of the board in relation to the horizontal 
	axis in the middle of the board as in the following diagram:

	5 1 4 5
	2 5 3 5
	2 5 3 5
	5 1 4 5

	The function should return the pointer to the memory location where the sum of the heights of the figures is written
	if the board is symmetrically arranged, and the number -1 if it is not symmetrically arranged.

*/

struct Figure
{
	int ID;
	char* name;
	float* height;

	Figure() {
		ID = rand() % 1000 + 1;
		name = new char[20];
		height = new float{ 0.0f };
	}

	~Figure() {
		delete[] name;
		name = nullptr;
		delete height;
		height = nullptr;
	}
	
	void input() {
		char temp[20];
		cout << "Please enter the figure's name : ";
		cin.getline(temp, size(temp));
		strcpy_s(name, strlen(temp) + 1, temp);

		do {
			cout << "Please enter the figure's height: ";
			cin >> *height;
		} while (*height <= 0);
		cin.ignore();
	}

	void output() {
		cout << "ID : " << ID << endl;
		cout << "Name : " << name << endl;
		cout << "Height : " << *height << endl;
		cout << endl;
	}
};

float* sumIfSymmetrical(Figure** matrix, int n) {
	float sum = 0.0f;
	for (int j = 0; j < n; j++) {			// columns
		for (int i = n / 2 - 1, k = n / 2; i >= 0 && k < n; i--, k++) {		// rows

			sum += *matrix[i][j].height + *matrix[k][j].height;

			if ((j % 2 != 0 && i % 2 == 0) || (j % 2 == 0 && i % 2 != 0)) {		// white fields
				// the inner loop counters symmetrically go from the middle of the matrix, towards it's ends
				if (*matrix[i][j].height != *matrix[k][j].height) {
					return new float{ -1 };
				}
			}
		}
	}
	return new float{ sum };
}

int main() {

	int boardSize;
	do {
		cout << "Please enter the size of the chess board: ";
		cin >> boardSize;
	} while (boardSize < 1 && boardSize % 2 != 0);		// the board must have an even number of files & ranks

	cin.ignore(); cout << endl;

	// allocation
	Figure** board = new Figure * [boardSize];
	for (int i = 0; i < boardSize; i++) {
		board[i] = new Figure[boardSize];
	}

	// input
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			cout << "[" << i << "][" << j << "]: ";
			board[i][j].input();
			cout << endl;
		}
		cout << endl;
	}

	// output
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			cout << "[" << i << "][" << j << "]: ";
			board[i][j].output();
			cout << endl;
		}
		cout << endl;
	}

	float* result = sumIfSymmetrical(board, boardSize);
	(*result != -1) ?
		cout << "The chess board is symmetrical and the sum of it's figure's heights is equal to " << *result << endl :
		cout << "The chess board is not symmetrical!" << endl;

	// deallocation
	for (int i = 0; i < boardSize; i++) {
		delete[] board[i];
		board[i] = nullptr;
	}
	delete[] board;
	board = nullptr;

	return 0;
}