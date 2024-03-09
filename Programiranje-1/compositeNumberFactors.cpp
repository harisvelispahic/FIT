#include <iostream>
using namespace std;

/*
	Program enables input of a number n, and if n is not a prime number, output are the factors of the number n.
	
	For example:

	48  = 2 * 2 * 2 * 2 * 3
	100 = 2 * 2 * 5 * 5
	60  = 2 * 2 * 3 * 5

*/

bool isPrime(int);

int main() {
	
	int n = 0;
	cout << "Input a number (n>0): ";
	do {
		cin >> n;
		if (n <= 0) {
			cout << "Improper input! Please enter again: ";
		}
	} while (n <= 0);

	if (isPrime(n)) {
		cout << n << " is a prime number!" << endl;
	}

	else if (n == 1) {										//specical condition for 1
		cout << "1 = 1";
	}

	else {
		int divisor = 0;
		cout << n << " = ";
		while (!isPrime(n)) {
			for (int i = 2; i < (n / 2) + 1; i++) {			//(n / 2) + 1 - optimized, + 1 for the conditon of '4'
				if (n % i == 0) {
					divisor = i;
					cout << i << " * ";
					break;
				}
			}
			n /= divisor;
		}
		cout << n << endl;
	}

	return 0;
}

bool isPrime(int number) {
	if (number <= 1)
		return false;
	bool isPrime = true;
	for (int i = 2; i <= number / 2; i++) {
		if (number % i == 0) {
			isPrime = false;
			break;
		}
	}
	return isPrime;
}