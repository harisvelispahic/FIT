#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

/*
	NE RADI:
	
	MOGUCE JE ZMIJU POSLAT U RIKVERC				CHECK
	NE BRISE SE OSTATAK ZMIJE						CHECK
	NE RADE POENI KAKO TREBA						CHECK
	HRANA SE SPAWNA U ZMIJI							CHECK
	PONEKAD NEKO C IZLETI IZ ZMIJE
	STACK OVERFLOW ZA VELIKE BROJEVE
*/

using namespace std;
using namespace std::chrono;

const int MATRIX_SIZE_X = 15;											// initialize global variables
const int MATRIX_SIZE_Y = 30;
const char playingChar = 'o';
const char reward = 'x';
char lastMove = '╩';
const int numberOfRewards = 1;
int rewardsAvailable = numberOfRewards;


void printMatrix(char[][MATRIX_SIZE_Y]);
void constructMatrix(char[][MATRIX_SIZE_Y]);
int spawnRewardX(); 
int spawnRewardY();

int main() {
	srand(time(NULL));
	
	int difficulty = 200;												// set difficulty, speed of the game

	char field[MATRIX_SIZE_X][MATRIX_SIZE_Y] = { ' ' };					// initialized a matrix, the playing field
	int xRemember[100000], yRemember[100000], moveCounter = 0;			// two arrays, which "remember" where the snake was
	int snakeLength = 1;
	
	constructMatrix(field);												// function that constructs the field
	int x = rand() % (MATRIX_SIZE_X - 2) + 1;							//generating random values inside the field
	int y = rand() % (MATRIX_SIZE_Y - 2) + 1;
	
	int xLast = MATRIX_SIZE_X + 1, yLast = MATRIX_SIZE_X + 1;			// initializing last cycle coords to impossible values
	field[x][y] = playingChar;											// setting the "playingChar" to the coords
	
	printMatrix(field);													// print the field

	field[x][y] = ' ';

	bool gameOver = false;												// flag to decide when the game is over
	char input = _getch();												// non blocking input function

	int xRewardArr[1000] = {}, yRewardArr[1000] = {};					// declared two arrays, for the reward system

	do {
	xRemember[moveCounter] = x;											// arrays remember where the snake was
	yRemember[moveCounter] = y;

	for (int i = 0; i < moveCounter - snakeLength; i++) {				// loop for deleting the rest of the snake		
		field[xRemember[i]][yRemember[i]] = ' ';
		xRemember[i] = MATRIX_SIZE_X + 1;
		yRemember[i] = MATRIX_SIZE_X + 1;
	}


	while (rewardsAvailable) {											// spawning rewards
		int xRewardCoord = spawnRewardX(), yRewardCoord = spawnRewardY();
		for (int i = moveCounter - snakeLength; i < snakeLength; i++) {	// reward should not spawn inside the snake
			for (int j = moveCounter - snakeLength; j < snakeLength; j++) {
				if (xRewardArr[i] == xRemember[j] && yRewardArr[i] == yRemember[j]) {
					continue;
				}
			}
			
		}
		field[xRewardCoord][yRewardCoord] = reward;
		xRewardArr[snakeLength - 1] = xRewardCoord;
		yRewardArr[snakeLength - 1] = yRewardCoord;
		rewardsAvailable--;
	}
	
	for (int i = 0; i < size(yRewardArr); i++) {						// updating the points, enlargening the snake
		if (x == xRewardArr[i] && y == yRewardArr[i]) {
			snakeLength++;
			// system("pause");											// check if points is added
			rewardsAvailable = numberOfRewards;
			break;
		}
		
	}

	auto start_time = high_resolution_clock::now();

	
	while (duration_cast<milliseconds>(high_resolution_clock::now() - start_time).count() < difficulty - snakeLength) {
		if (_kbhit()) {
			input = _getch();
		}

		std::this_thread::sleep_for(milliseconds(10));
	}
	//	wait for input, if time for input exceeds "difficulty", then the snake moves another step to the last direction

	switch (input) {													// check for input, move the snake
		case 'W': case 'w':
			if (lastMove == 'S' || lastMove == 's')
				continue;
			x--;
			break;
		case 'S': case 's':
			if (lastMove == 'W' || lastMove == 'w')
				continue;
			x++;
			break;
		case 'A': case 'a':
			if (lastMove == 'D' || lastMove == 'd')
				continue;
			y--;
			break;
		case 'D': case 'd':
			if (lastMove == 'A' || lastMove == 'a')
				continue;
			y++;
			break;
	}

	
	field[x][y] = playingChar;											// place the char at (x,y) coords
	field[xLast][yLast] = 'c';
	system("cls");
	printMatrix(field);

	for (int i = 0; i < 100000; i++) {									//check if game is over
		if ((x == xRemember[i] && y == yRemember[i]) ||
			x == 0 || y == 0 || x == MATRIX_SIZE_X - 1 || y == MATRIX_SIZE_Y - 1) {
			gameOver = true;
			break;
		}
	}

	moveCounter++;
	xLast = x, yLast = y;
	lastMove = input;

	} while (!gameOver);

	cout << endl;
	cout << "You have collected " << snakeLength - 1 << " points." << endl;
	
	system("pause");

	return 0;
}


void constructMatrix(char matrix[][MATRIX_SIZE_Y]) {
	for (int i = 0; i < MATRIX_SIZE_X; i++) {
		for (int j = 0; j < MATRIX_SIZE_Y; j++) {
			if ((i == 0 && j == 0) || (i == MATRIX_SIZE_X - 1 && j == MATRIX_SIZE_Y - 1) || (i == 0 && j == MATRIX_SIZE_Y - 1) || (i == MATRIX_SIZE_X - 1 && j == 0)) {
				matrix[i][j] = '+';
			}
			else if (i == 0 || i == MATRIX_SIZE_X - 1) {
				matrix[i][j] = '-';
			}
			else if (j == 0 || j == MATRIX_SIZE_Y - 1) {
				matrix[i][j] = '|';
			}
			else {
				matrix[i][j] = ' ';
			}
		}
	}
}

void printMatrix(char matrix[MATRIX_SIZE_X][MATRIX_SIZE_X*2]) {
	for (int i = 0; i < MATRIX_SIZE_X; i++) {
		for (int j = 0; j < MATRIX_SIZE_X*2; j++) {
			if (matrix[i][j] == reward) {
				cout << "\033[1;31m" << reward << "\033[0m";			// colours dont work propperly on .exe run
			}
			else if (matrix[i][j] == playingChar) {
				cout << "\033[1;32m" << playingChar << "\033[0m";
			}
			else {
				cout << matrix[i][j];
			}

			/*cout << matrix[i][j];*/
		}
		cout << endl;
	}
}

int spawnRewardX() {
	return rand() % (MATRIX_SIZE_X - 2) + 1;
}

int spawnRewardY() {
	return rand() % (MATRIX_SIZE_Y - 2) + 1;
}