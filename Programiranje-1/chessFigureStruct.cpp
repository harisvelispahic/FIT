#include <iostream>
using namespace std;

/*
	Create a 2D dynamic array whose elements are object type figures
	(the figure is a structure whose characteristics are given below).

	struct Figure
	{
		int ID;
		char* name;
		float* height;
	};
	
	
	Allow the user to enter the dimensions of the array and allow the entry of elements in such a way that on each
	the black field is entered by a figure whose height is greater than 5 cm, and on each white field a figure 
	whose height is smaller than 5 cm. If the entered height is equal to 5cm, the field should remain empty or 
	you can enter the height of the figure set to 0. Automate input using random values.


	It is necessary to create a function that will calculate the average height of all the figures that are on the 
	black fields below side diagonals. 
	The function should return a pointer to the memory location where that value was written.
*/

struct Figure
{
	int ID;
	char* name;
	float* height;
	
	Figure() {
		ID = 0;
		name = new char[30];
		height = new float{ 0.0f };
	}

	~Figure() {
		delete name;
		name = nullptr;
		delete height;
		height = nullptr;
	}

	void input(bool color) {				// black - 0,	white - 1
		ID = rand() % 100 + 1;
		
		char temp[29];
		cout << "Please enter the figure's name: ";
		cin.getline(temp, size(temp));
		strcpy_s(name, strlen(temp) + 1, temp);

		float figHeight;
		if (!color) {
			do {
				figHeight = float((rand() % 90 + 10)) / 10;
			} while (figHeight < 5);
		}
		else {
			do {
				figHeight = float((rand() % 90 + 10)) / 10;
			} while (figHeight > 5);
		}

		if (figHeight == 5)
			*height = 0.0f;
		else {
			*height = figHeight;
		}

		cout << endl;
	}

	void print() {
		cout << "Figure's ID: " << ID << endl;
		cout << "Figure's name: " << name << endl;
		cout << "Figure's height: " << *height << " cm" << endl;
		cout << endl;
	}
};


Figure** createMatrix(int rows, int columns) {
	Figure** matrix = new Figure * [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new Figure[columns];
	}
	return matrix;
}

void enterMatrix(Figure** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		cout << "Rank " << i + 1 << endl;
		cout << "-------------------------------------------------" << endl;
		for (int j = 0; j < columns; j++) {
			cout << "File " << j + 1 << endl;
			cout << "-------------------------------------------------" << endl;
			
			if ((i + j) % 2 == 0)
				(*(matrix + i) + j)->input(0);
			else
				(*(matrix + i) + j)->input(1);
		}
		cout << endl;
	}
}

void printMatrix(Figure** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		cout << "Rank " << i + 1 << endl;
		cout << "-------------------------------------------------" << endl;
		for (int j = 0; j < columns; j++) {
			cout << "File " << j + 1 << endl;
			cout << "-------------------------------------------------" << endl;
			(*(matrix + i) + j)->print();
		}
	}
}

void deleteMatrix(Figure** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

/*
	It is necessary to create a function that will calculate the average height of all the figures that are on the 
	black fields below side diagonals. 
	The function should return a pointer to the memory location where that value was written.
*/

float* getAverageHeight(Figure** matrix, int rows, int columns) {
	float sumHeight = 0.0f;
	int countHeight = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i + j > rows - 1 && (i + j) % 2 == 0) {
				sumHeight += *(*(matrix + i) + j)->height;
				countHeight++;
			}
		}
	}
	return new float{ sumHeight / countHeight };
}


int main() {
	srand(time(0));

	int ranks = 0, files = 0;
	do {
		do {
			cout << "Please enter the number of ranks: ";
			cin >> ranks;
		} while (ranks < 1);

		do {
			cout << "Please enter the number of files: ";
			cin >> files;
		} while (files < 1);

		cout << endl;

	} while (ranks != files);

	cin.ignore(); cout << endl;

	Figure** chessBoard = createMatrix(ranks, files);
	
	enterMatrix(chessBoard, ranks, files);
	system("cls");

	printMatrix(chessBoard, ranks, files);

	float* result = getAverageHeight(chessBoard, ranks, files);
	cout << "The average height for the figures on the black fields under the secondary diagonal is equal to "
		<< *result << endl;

	deleteMatrix(chessBoard, ranks);

	return 0;
}