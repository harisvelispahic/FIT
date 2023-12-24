#include <iostream>
using namespace std;

/*	KAPREKAR
*	four-digit number, all digits are not the same
*	difference descendingSort - ascendingSort
*	until the same number starts repeating itself
*/

bool differentDigits(int);
int descendingSort(int);
int ascendingSort(int);

int main() {

	int input = 0, lastNumber = 0, counter = 0;
	
	cout << "Please enter a 4-digit number: ";

	do {
		cin >> input;
		if (!differentDigits(input) || input < 1000 || input > 9999)
			cout << "Improper input! Please enter again: ";

	} while (!differentDigits(input) || input < 1000 || input>9999);
	
	cout << endl;
	cout << "You have enter the number " << input << endl;
	
	while (true) {
		counter++;
		cout << descendingSort(input) - ascendingSort(input) << " = " << descendingSort(input) << " - " << ascendingSort(input) << endl;
		input = descendingSort(input) - ascendingSort(input);
		if (lastNumber == descendingSort(input) - ascendingSort(input)) {
			break;
		}
		lastNumber = descendingSort(input) - ascendingSort(input);
	}
	
	cout << endl;
	cout << "The kaprekar constant has been found in " << counter << " iterations!" << endl;

	return 0;
}

bool differentDigits(int number) {
	int firstDigit = number % 10;
	number /= 10;
	while (number) {
		if (number % 10 != firstDigit) {
			return true;
		}
		number /= 10;
	}
	return false;
}

int ascendingSort(int number) {
	int newNumber = 0, arr[4] = {};

	for (int i = 0; i < 4; i++) {
		arr[i] = number % 10;
		number /= 10;
	}

	bool switchOccured = true;
	int arrSize = 4;
	while(switchOccured) {
		switchOccured = false;
		for (int i = 0; i < arrSize - 1; i++) {
			if (arr[i] < arr[i + 1]) {
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				switchOccured = true;
			}
		}
		arrSize--;
	}

	for (int i = 3; i >= 0; i--) {
		newNumber = newNumber * 10 + arr[i];
	}
	return newNumber;
}

int descendingSort(int number) {
	number = ascendingSort(number);
	int newNumber = 0;
	for (int i = 0; i < 4; i++) {
		newNumber = newNumber * 10 + number % 10;
		number /= 10;
	}
	return newNumber;
}