#include <iostream>
using namespace std;

/*
	Create a two-dimensional dynamic array whose elements are figure-type objects
	(the figure is a structure whose charascteristics are given below). 

	struct Figure
	{
		int ID;
		char* name;
		float* height;
	};


	Allow the user to enter the dimensions of the array and allow the entry of elements.
	Ensure that there is the same number of columns and rows.

	It is necessary to create a function that will check whether the figures on the white fields are symmetrically arranged in height
	in relation to the main diagonal (is the height of the figure at position 0.1 equal to the height of the figure at position 1.0, 
	etc. for all white fields).
	The function should return the pointer to the memory location where the sum of the heights of the figures is written
	if the board is symmetrically arranged, and the number -1 if it is not symmetrically arranged.
*/

struct Figure
{
	int ID;
	char* name;
	float* height;

	Figure() {
		ID = 0;
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
		cout << "Please enter the  ID  of the figure: ";
		cin >> ID;
		cin.ignore();

		char temp[19];
		cout << "Please enter the name of the figure: ";
		cin.getline(temp, size(temp));
		strcpy_s(name, strlen(temp) + 1, temp);

		do {
			cout << "Please enter the height of the figure: ";
			cin >> *height;
		} while (*height < 1);
	}

	void print() {
		cout << "The ID of the figure: " << ID << endl;
		cout << "The name of the figure: " << name << endl;
		cout << "The height of the figure: " << *height << endl;
	}
};


/*
	It is necessary to create a function that will check whether the figures on the white fields are symmetrically arranged in height
	in relation to the main diagonal (is the height of the figure at position 0.1 equal to the height of the figure at position 1.0, 
	etc. for all white fields).
	The function should return the pointer to the memory location where the sum of the heights of the figures is written
	if the board is symmetrically arranged, and the number -1 if it is not symmetrically arranged.
*/

float* isBoardHeightSymmetrical(Figure** matrix, int size) {
	int sum = 0.0f;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (*(*(*(matrix + i) + j)).height != *(*(*(matrix + j) + i)).height) {
				return new float(-1);
			}
			sum += *(*(*(matrix + i) + j)).height;
		}
	}
	return new float(sum);
}

int main() {

	int size;
	do {
		cout << "Please enter the size of the chess board: ";
		cin >> size;
	} while (size < 1);

	cin.ignore(); cout << endl;

	// dynamic memory allocation
	Figure** chessBoard = new Figure * [size];
	for (int i = 0; i < size; i++) {
		chessBoard[i] = new Figure[size];
	}

	// enter matrix
	for (int i = 0; i < size; i++) {
		cout << "Rank " << i + 1 << endl;
		cout << "-----------------------------------------" << endl;
		for (int j = 0; j < size; j++) {
			cout << "File " << j + 1 << endl;
			cout << "-----------------------------------------" << endl;
			(*(chessBoard + i) + j)->input();
			cout << endl;
		}
		cout << endl;
	}

	system("cls");

	// print matrix
	for (int i = 0; i < size; i++) {
		cout << "Rank " << i + 1 << endl;
		cout << "-----------------------------------------" << endl;
		for (int j = 0; j < size; j++) {
			cout << "File " << j + 1 << endl;
			cout << "-----------------------------------------" << endl;
			(*(chessBoard + i) + j)->print();
			cout << endl;
		}
		cout << endl;
	}
	
	float* symmetryResult = isBoardHeightSymmetrical(chessBoard, size);

	if (*symmetryResult != -1) {
		cout << "The chess board is symmetrical according to the heights from the main diagonal" << endl;
		cout << "The sum of all heights on the chess board is: " << *symmetryResult;
	}
	else
		cout << "The chess board is not symmetrical" << endl;

	// dynamic memory deallocation
	delete symmetryResult;

	for (int i = 0; i < size; i++) {
		delete[] chessBoard[i];
		chessBoard[i] = nullptr;
	}
	delete[] chessBoard;
	chessBoard = nullptr;

	return 0;
}