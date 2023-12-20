#include <iostream>
using namespace std;

/*
*	Enable input of two numbers X and Y from the interval from 10 to 5000.
	Create a program that will find and print all numbers from X to Y
	(including limit values) for which it is valid that the inverse number is divisible by its sum of digits.

	For example For the number 144, the sum of its digits is 9 and
	that the number obtained after its digits are reversed is 441, divisible by 9.
*/

int reverse(int);
int sum(int);

int main() {
	int x, y;
	cout << "Please input the interval bounds (10 - 5000): ";
	do {
		cin >> x >> y;
		if (x < 10 || y>5000 || x > y)
			cout << "Improper interval bounds! Please enter again:: ";

	} while (x < 10 || y > 5000);

	for (int i = x; i <= y; i++) {
		if (reverse(i) % sum(i) == 0)
			cout << i << endl;
	}
	
	return 0;
}

int reverse(int number) {
	int newNumber = 0;
	while (number) {
		newNumber = newNumber * 10 + number % 10;
		number /= 10;
	}
	return newNumber;
}

int sum(int number) {
	int sum = 0;
	while (number) {
		sum += number % 10;
		number /= 10;
	}
	return sum;
}