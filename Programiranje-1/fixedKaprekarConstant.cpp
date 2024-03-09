#include <iostream>
using namespace std;

const int NUMBER_OF_DIGITS = 4;
const int KAPREKAR4 = 6174;
/*
*  6174
*/

void input(int&);
int ascendingOrder(int);
int descendingOrder(int);

int main() {
	
	int number = 0;
	input(number);
	
	do {
		cout << descendingOrder(number) << " - " << ascendingOrder(number) << " = " << descendingOrder(number) - ascendingOrder(number) << endl;
		number = descendingOrder(number) - ascendingOrder(number);
	} while (number != KAPREKAR4);
	
	return 0;
}

void input(int& number) {
	cout << "Please input " << NUMBER_OF_DIGITS << "-digit (with at least one digit different from the others): ";
	bool uniqueDigit;
	do {
		uniqueDigit = false;
		cin >> number;
		int check = number;
		int arr[NUMBER_OF_DIGITS] = {};
		for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
			arr[i] = check % 10;
			check /= 10;
		}
		int firstElement = arr[0];
		for (int i = 1; i < NUMBER_OF_DIGITS; i++) {
			if (firstElement != arr[i]) {
				uniqueDigit = true;
				break;
			}
		}
		if (number < 1000 || number>9999 || !uniqueDigit) {
			cout << "Improper input! Please enter again: ";
		}

	} while (number < 1000 || number>9999 || !uniqueDigit);

	cout << endl;
}

int ascendingOrder(int number) {
	int arr[NUMBER_OF_DIGITS] = {};
	int arrSize = NUMBER_OF_DIGITS;
	for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
		arr[i] = number % 10;
		number /= 10;
	}

	bool shiftOccurance = true;
	while (shiftOccurance) {
		shiftOccurance = false;

		for (int i = 0; i < arrSize-1; i++) {
			if (arr[i] > arr[i + 1]) {
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				shiftOccurance = true;
			}
		}
		arrSize--;
	}
	int result = 0;
	for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
		result = result * 10 + arr[i];
	}
	return result;
}

int descendingOrder(int number) {
	int temp = ascendingOrder(number), result = 0;
	for (int i = 0; i < NUMBER_OF_DIGITS; i++) {
		result = result * 10 + temp % 10;
		temp /= 10;
	}
	return result;
}