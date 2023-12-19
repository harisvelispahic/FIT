#include <iostream>
using namespace std;

/*
	Program calculates sum:
	S=3!-6!+9! -....+(-1)n+1(3n)!

*/

int factorial(int);
int sum(int);

int main() {

	int n = 0;
	cout << "Input a number (n>0): ";
	do {
		cin >> n;
	} while (n <= 0);
	
	cout << "The sum is equal to: " << sum(n) << endl;

	return 0;
}

int factorial(int number) {
	int fact = 1;
	for (int i = 2; i <= number; i++) {
		fact *= i;
	}
	return fact;
}

int sum(int bound) {
	int sum = 0;
	for (int i = 3; i <= bound * 3; i += 3) {
		if (i % 2 == 0) {
			sum -= factorial(i);
		}
		else {
			sum += factorial(i);
		}
	}
	return sum;
}