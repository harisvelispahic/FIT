#include <iostream>
using namespace std;

/*
	Create a two-dimensional dynamic array whose elements are objects of the type football player
	(footballer is a structure whose features are given below).


	struct footballer {
	int ID;
	char* fullName;
	char* position;		// accept only letters F, D i M (forward, defender i midfielder);
	int* goals;

	};

	Allow the user to enter the dimensions of the array and allow the entry of elements.
	The rows of the 2D array represent different clubs and the columns represent different footballers (players).
	For the sake of simplicity, assume that each club has the same number of football players.
	Depending on the entered position (F, D or M) it is identified whether the given football player is
	striker, defender or midfielder.
	Different clubs may have different numbers of forwards, midfielders or defenders.

	(E.g. club 1 may have 10 midfielders, 3 forwards and 5 defenders,
	while club 2 can have 12 midfielders, 2 forwards and 6 defenders, etc.)

	Calculate and print the average number of goals per player position for all clubs.
	Then allow the user to choose one type of football player (N, O or V) and according to the user's choice
	find the club that has the best goals scored average of that type of player
	(eg if the letter V is entered for club 1 the average of 10 midfielders is calculated 
	while for club 2 the average of 12 midfielders is calculated and these averages are compared).


	(In this task, it is forbidden to index array elements with square brackets.
	Must use pointer arithmetic.
	Be sure to take care of deallocating dynamically allocated memory.)

*/

struct footballer {

	int ID;
	char* fullName;
	char* position;		// accept only letters F, D i M (forward, defender i midfielder);
	int* goals;

	footballer() {
		ID = 0;
		fullName = new char[30] {""};
		position = new char;
		goals = new int;
	}

	~footballer() {
		delete fullName;
		fullName = nullptr;
		delete position;
		position = nullptr;
		delete goals;
		goals = nullptr;
	}

	void input() {
		cout << "Please enter the ID: ";
		cin >> ID;
		cin.ignore();

		char name[29] = "";
		cout << "Please enter the player's full name: ";
		cin.getline(name, size(name));
		strcpy_s(fullName, strlen(name) + 1, name);
		

		char tempPos;
		do {
			cout << "Please enter the player's position: ";
			cin >> tempPos;
		} while (tempPos != 'F' && tempPos != 'M' && tempPos != 'D' 
			&& tempPos != 'f' && tempPos != 'm' && tempPos != 'd');
		*position = tempPos;

		cout << "Please enter the number of goals: ";
		cin >> *goals;
	}

	void print() {
		cout << "Player's ID: " << ID << endl;
		cout << "Player's full name: " << fullName << endl;
		cout << "Player's position: " << *position << endl;
		cout << "Player's goals: " << *goals << endl;
	}
};

footballer** createMatrix(int, int);
void enterMatrix(footballer**, int, int);
void deleteMatrix(footballer**, int);

void printAverageGoalsByPosition(footballer**, int, int);

int main() {

	int numberOfClubs = 0, numberOfPlayers = 0;
	do {
		cout << "Please enter the number of clubs: ";
		cin >> numberOfClubs;
	} while (numberOfClubs < 1);
	do {
		cout << "Please enter the number of players per club: ";
		cin >> numberOfPlayers;
	} while (numberOfPlayers < 1);

	cout << endl; cout << endl;

	footballer** matrix = createMatrix(numberOfClubs, numberOfPlayers);
	enterMatrix(matrix, numberOfClubs, numberOfPlayers);

	printAverageGoalsByPosition(matrix, numberOfClubs, numberOfPlayers);
	
	deleteMatrix(matrix, numberOfClubs);

	return 0;
}

footballer** createMatrix(int rows, int columns) {
	footballer** matrix = new footballer * [rows];
	for (int i = 0; i < rows; i++) {
		*(matrix + i) = new footballer[columns];
	}
	return matrix;
}

void enterMatrix(footballer** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		cout << "Club " << i + 1 << ": " << endl;
		cout << "--------------" << endl;
		cout << endl;
		for (int j = 0; j < columns; j++) {
			cout << "Player " << j + 1 << ": " << endl;
			cout << "-------------------------------------------------------" << endl;
			(*(matrix + i) + j)->input();
			cout << "-------------------------------------------------------" << endl;
		}
		//system("cls");
		cout << endl; cout << endl;
	}
}

void deleteMatrix(footballer** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] * (matrix + i);
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

void printAverageGoalsByPosition(footballer** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		double fAvg = 0, fcounter = 0, mAvg = 0, mcounter = 0, dAvg = 0, dcounter = 0;
		for (int j = 0; j < columns; j++) {
			switch (*(*(*(matrix + i) + j)).position)
			{
			case 'F': case'f':
				fAvg += *(*(*(matrix + i) + j)).goals;
				fcounter++;
				break;
			case 'M': case'm':
				mAvg += *(*(*(matrix + i) + j)).goals;
				mcounter++;
				break;
			case 'D': case'd':
				dAvg += *(*(*(matrix + i) + j)).goals;
				dcounter++;
				break;

			}

		}
		(fcounter == 0) ? cout << "There are no forwards in club " << i + 1 << endl :
			cout << "FORWARDS:     Club " << i + 1 << " forward's average is = " << fAvg / fcounter << endl;

		(mcounter == 0) ? cout << "There are no midfielders in club " << i + 1 << endl :
			cout << "MIDFIELDERS:  Club " << i + 1 << " midfielder's average is = " << mAvg / mcounter << endl;

		(dcounter==0)? cout << "There are no defenders in club " << i + 1 << endl :
			cout << "DEFENDERS:    Club " << i + 1 << " defender's average is = " << dAvg / dcounter << endl;

		cout << endl;
	}
}