#include <iostream>
using namespace std;

/*
	The following structs are given:

	struct Date
	{
		int day, month, year;
	};

	struct Student
	{
		int ID;
		char fullName[30];
		Date yearOfBirth;
		float averageGrade;
	};

	Create a two-dimensional dynamic array whose elements are objects of type student.

	Create functions:
	· for entering student characteristics - let the function receive a pointer to the student;
	· to print the student's characteristics - let the function receive a pointer to the student;
	· for validation of the entered date of birth - the function receives a pointer to the date and returns true 
	if the date is valid (eg 2/2/2002) or returns false if the date is not valid (eg 17/23/100000);


	Assuming that rows represent generations and columns represent subjects,
	find the index of the generation with the best average and the index of the subject with the worst average
*/

struct Date {

	int day, month, year;

	bool isLeapYear() {
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}
	int getDays() {
		switch (month) {
		case 4: case 6: case 9: case 11: 
			return 30;
			break;
		case 2:
			if (isLeapYear())
				return 29;
			else
				return 28;
			break;
		default:
			return 31;
 		}
	}

	bool isValid() {
		if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1 || year > 10000)
			return false;
		if (day > getDays())
			return false;
		return true;
	}

	void input() {
		do{
			cout << "Please enter the day: ";
			cin >> day;
			cout << "Please enter the month: ";
			cin >> month;
			cout << "Please enter the year: ";
			cin >> year;
			cout << endl;
			if (!isValid()) {
				cout << "Invalid date! Please enter again: " << endl;
			}
		} while (!isValid());
	}

	void print() {
		cout << day << "." << month << "." << year << endl;
	}
};

// function for validating the entered date of birth - the function receives a pointer to the date and returns 
// true the date is valid (e.g. 2/2/2002) or returns false if the date is not valid (e.g. 17/23/100000)

bool isDateValid(Date* d) {
	if ((d->day) < 1 || (d->day) > 31 || (d->month) < 1 || (d->month) > 12 || (d->year) < 1 || (d->year) > 10000)
		return false;
	if ((d->day) > (d->getDays()))
		return false;
	return true;
}

struct Student {

	int ID;
	char fullName[30];
	Date yearOfBirth;
	float averageGrade;
};

// function for entering student characteristics -  function receives a pointer to a student

void enterStudentData(Student* s) {
	cout << "Please enter the ID: ";
	cin >> s->ID;
	cin.ignore();

	cout << "Please enter the student's full name: ";
	char tempArr[29] = "";
	cin.getline(tempArr, size(tempArr));
	strcpy_s(s->fullName, strlen(tempArr) + 1, tempArr);
	cout << endl;

	cout << "Please enter the date of birth: " << endl;
	s->yearOfBirth.input();

	cout << "Please enter the average grade: ";
	cin >> s->averageGrade;
}

// function for printing the student's characteristics - the function receives a pointer to the student

void printStudentData(Student* s) {
	cout << "Student's ID: " << s->ID << endl;
	cout << "Student's full name: " << s->fullName << endl;
	cout << "Student's date of birth: ";
	s->yearOfBirth.print();
	cout << "Student's average grade: " << s->averageGrade << endl;
}

// 	find the index of the generation with the best average and the index of the subject with the worst average

int getBestGenerationsIndex(Student** matrix, int rows, int columns) {
	int index = 0;
	float grade = 0.0f;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			grade = max(grade, matrix[i][j].averageGrade);
			if (grade == matrix[i][j].averageGrade)
				index = i;
		}
	}
	return index + 1;
}

int getLowestSubjectsGradeIndex(Student** matrix, int rows, int columns) {
	int index = 0;
	float grade = 0.0f, worstGrade = INT_MAX;
	for (int j = 0; j < columns; j++) {
		for (int i = 0; i < rows; i++) {
			grade += matrix[i][j].averageGrade;
		}
		worstGrade = min(worstGrade, grade);
		if (worstGrade == grade)
			index = j;

		grade = 0;
	}
	return index + 1;
}

int main() {

	// Assume that rows represent generations and columns represent subjects

	int generations, subjects;
	do {
		cout << "Please enter the number of generations: ";
		cin >> generations;
		if (generations < 1) {
			cout << "Invalid number of generations! " << endl;
		}
	} while (generations < 1);

	
	do {
		cout << "Please enter the number of subjects: ";
		cin >> subjects;
		if (subjects < 1) {
			cout << "Invalid number of subjects! " << endl;
		}
	} while (subjects < 1);

	cout << endl;

	// allocation
	Student** faculty = new Student * [generations];
	for (int i = 0; i < generations; i++) {
		faculty[i] = new Student[subjects];
	}

	// enter matrix
	for (int i = 0; i < generations; i++) {
		cout << "Generation " << i + 1 << endl;
		cout << "------------------------------------------------------" << endl;
		cout << endl;
		for (int j = 0; j < subjects; j++) {
			cout << "Student " << j + 1 << endl;
			cout << "------------------------------------------------------" << endl;
			enterStudentData(&faculty[i][j]);
			cout << "------------------------------------------------------" << endl;
			cout << endl;
		}
	}
	system("cls");

	// print matrix
	for (int i = 0; i < generations; i++) {
		cout << "Generation " << i + 1 << endl;
		cout << "------------------------------------------------------" << endl;
		cout << endl;
		for (int j = 0; j < subjects; j++) {
			cout << "Student " << j + 1 << endl;
			cout << "------------------------------------------------------" << endl;
			printStudentData(&faculty[i][j]);
			cout << "------------------------------------------------------" << endl;
		}
	}

	cout << "The generation with the highest average grade is generation "
		<< getBestGenerationsIndex(faculty, generations, subjects) << endl;

	cout << "The subject with the lowest average grade is subject "
		<< getLowestSubjectsGradeIndex(faculty, generations, subjects) << endl;


	// deallocation
	for (int i = 0; i < generations; i++) {
		delete[] faculty[i];
		faculty[i] = nullptr;
	}
	delete[] faculty;
	faculty = nullptr;

	return 0;
}