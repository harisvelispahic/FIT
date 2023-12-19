#include <iostream>
#include <cmath>
using namespace std;

/*
	Program that outputs all numbers whose digits are equal to the last digits of their squares
	For example:

	6^2=36, 25^2=625

	Check for first 150 numbers
*/

bool check(int);

int main() {

	for (int i = 1; i <= 150; i++) {
		if (check(i)) {
			cout << i << "\t" << i*i << endl;
		}
	}

	
	return 0;
}

bool check(int number) {
	int squareOfNumber = number * number;
	int numberOfDigits = log10(number) + 1;
	int powerOfTen = pow(10, numberOfDigits);

	int numberWithin = squareOfNumber % powerOfTen;
	return number == numberWithin;
}