#include <iostream>
#include <iomanip>
using namespace std;

/*
	Write a program that calculates the grade point average for each student in a 2D array and the average
	of each object in a 2D array [of arbitrary dimensions]. Students are arranged in rows,
	and subjects by columns. The program should print the average of each student individually and
	the average of each individual subject. Fill the grade matrix with random values [5-10]. 
	If the grade = 5, do not calculate the average for it [because we are guided by the logic that the grade is 5
	indicates that the student did not pass the given subject].
*/

const int MAX_ROWS = 50;
const int MAX_COLUMNS = 50;

int getRandomValue(int from, int to) {
	return rand() % (to - from + 1) + from;
}

void generateMatrix(int matrix[][MAX_COLUMNS], const int rows, const int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = getRandomValue(5, 10);
		}
	}
}

void printMatrix(int matrix[][MAX_COLUMNS], const int rows, const int columns) {
	for (int i = 0; i < rows; i++) {
		cout << "Student [" << i + 1 << "]:  ";
		for (int j = 0; j < columns; j++) {
			cout << setw(3) << matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void studentAverage(int matrix[][MAX_COLUMNS], const int rows, const int columns) {
	for (int i = 0; i < rows; i++) {
		float sum = 0.0;
		int counter = 0;
		for (int j = 0; j < columns; j++) {
			if (matrix[i][j] >= 6 && matrix[i][j] <= 10) {
				sum += matrix[i][j];
				counter++;
			}
		}
		cout << "The average grade of student [" << i + 1 << "] is: " << sum / counter << endl;
	}
	cout << endl;
}

void gradeAverage(int matrix[][MAX_COLUMNS], const int rows, const int columns) {
	for (int i = 0; i < columns; i++) {
		float sum = 0.0;
		int counter = 0;
		for (int j = 0; j < rows; j++) {
			if (matrix[j][i] >= 6 && matrix[j][i] <= 10) {
				sum += matrix[j][i];
				counter++;
			}
		}
		cout << "The average grade of student [" << i + 1 << "] is: " << sum / counter << endl;
	}
	cout << endl;
}

int main() {
	int r, c;
	cout << "Please input the number of students: ";
	cin >> r;
	cout << "Please enter the number of subjects: ";
	cin >> c;
	cout << endl;

	int matrix[MAX_ROWS][MAX_COLUMNS];
	
	generateMatrix(matrix, r, c);
	printMatrix(matrix, r, c);
	studentAverage(matrix, r, c);
	gradeAverage(matrix, r, c);

	return 0;
}