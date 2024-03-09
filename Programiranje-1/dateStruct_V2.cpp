#include <iostream>
using namespace std;

/*
	The following prototype of the struct Date is given:

	struct Date
	{
	 int day;
	 int month;
	 int year;

	 void input();
	 void print();
	 bool isValid();
	 int toInt();
	};
	
	Carry out the implementation of the default functions of the members and, if necessary, define and implement 
	auxiliary global functions (etc.: isLeap, getDaysForMonth, etc.). Then, be sure to implement the following
	global functions:

	Date& min(Date& d1, Date& d2) - Function that returns the older of two dates (by reference).
	Date& max(Date& d1, Date& d2) - Function that returns the newer of two dates (by reference).
	int getDifferenceBetween(Date& d1, Date& d2) - Function that calculates
	the difference (in days) between the two dates. Take care that d1 does not necessarily have to be an older date than d1
	Date* getClosestDate(Date* arr, int size, Date& targetDate)


	In the main function, add the following items:
		• Input of the size which indicates the dimensions of the dynamic array of objects of type Date
		• Creating a dynamic date array
		• Date entry (day, month and year) for each object in the sequence (the entry is repeated if the dates
		invalid)
		• Date printing
		• Creating the object targetDate and entering it (the entry is repeated if the date is invalid)
		• Finding the closest date from the entered string by calling the function getClosestDate
		• Dynamic array deallocation
*/



struct Date
{
	int day;
	int month;
	int year;


	void input() {
		cout << "Please enter the date:" << endl;
		do {
			cout << "D: ";
			cin >> day;
			cout << "M: ";
			cin >> month;
			cout << "Y: ";
			cin >> year;
			if (!isValid()) {
				cout << "Invalid input! Please enter again.";
				cout << endl;
			}
		} while (!isValid());
	}
	void print() {
		cout << day << "." << month << "." << year;
	}

	int toInt() {
		return year * 365.24 + month * 30.43 + day;
	}

	bool isLeap() {
		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}

	bool isValid() {
		if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
			return false;
		if (day > getDaysForMonth())
			return false;
		return true;
	}

	int getDaysForMonth() {
		switch (month) {
		case 4: case 6: case 9: case 11:
			return 30;
			break;
		case 2:
			if (isLeap())
				return 29;
			else
				return 28;
			break;
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
			break;
		}
	}
};



int main() {

	/*
	In the main function, add the following items:
		• Input of the size which indicates the dimensions of the dynamic array of objects of type Date
		• Creating a dynamic date array
		• Date entry (day, month and year) for each object in the sequence (the entry is repeated if the dates
		invalid)
		• Date printing
		• Creating the object targetDate and entering it (the entry is repeated if the date is invalid)
		• Finding the closest date from the entered string by calling the function getClosestDate
		• Dynamic array deallocation
	*/

	int size;
	do
	{
		cout << "Please enter the size of the array: ";
		cin >> size;
	} while (size < 1);
	cout << endl;

	// memory allocation
	Date* dateArray = new Date[size];

	for (int i = 0; i < size; i++) {
		dateArray[i].input();
		cout << endl;
	}

	// dates output
	cout << "The dates you entered: " << endl;
	for (int i = 0; i < size; i++) {
		dateArray[i].print();
		cout << endl;
	}
	cout << endl;

	Date targetDate;
	targetDate.input();

	int difference = INT_MAX;
	Date* closestDate = &dateArray[0];;

	for (int i = 0; i < size; i++) {
		difference = min(difference, abs(targetDate.toInt() - dateArray[i].toInt()));
		if (difference == abs(targetDate.toInt() - dateArray[i].toInt())) {
			closestDate = &dateArray[i];
		}
	}
	cout << endl;

	// memory deallocation
	cout << "The closest date to ";
	targetDate.print();
	cout << " is ";
	closestDate->print();

	return 0;
}