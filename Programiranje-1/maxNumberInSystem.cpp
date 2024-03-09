#include <iostream>
#include <cmath>
using namespace std;

int maxNumberWithDigits(int, int);
int toDecimal(int, int);

int main() {

	int d = 0;
	do {
		cout << "Please input a number [1,9]: ";
		cin >> d;
	} while (d <= 0 || d > 10);

	for (int i = 2; i <= 10; i++) {
		cout << "Base: " << i << ", greatest number: " << maxNumberWithDigits(i, d) <<
			", decimal representation of the number: " << toDecimal(maxNumberWithDigits(i, d), i) << endl;
	}
		
	return 0;
}

int maxNumberWithDigits(int base, int digits) {
	int highestNumber = 0;
	for (int i = 0; i < digits; i++) {
		highestNumber = highestNumber * 10 + (base - 1);
	}
	return highestNumber;
}

int toDecimal(int number, int base) {
	int decimal = 0, counter = 0;
	while (number) {
		decimal += (number % 10) * pow(base, counter);
		counter++;
		number /= 10;
	}
	return decimal;
}
