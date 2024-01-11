#include <iostream>
using namespace std;

/*
	Write a program in which it is necessary to enter a selected number of digits
	starting with the digit of the highest weight value, then assemble and print a natural number from them.
	Digit entry is interrupted when a number less than 0 or greater than 9 is entered.
	Print a message if the received number is perfect. The output should be of the form:

	Example output:
	Enter the digit: 2
	Enter the digit: 8
	Enter the digit:-1
	...
	Input: str = “0145”
	Output: 145

	For example, 28 is a perfect number, his divisors are 1,2,4,7 and 14, and 1 + 2 + 4 + 7 + 14 = 28
	The number made up of the given digits is 28.
	The number is perfect.

*/

long long int constructNumber(int size, long long int n = 0, int i = 0) {
	if (i == size) {
		return n;
	}
	int temp = 0;
	cout << "Please enter the [" << i << "] digit: ";
	cin >> temp;
	if (temp < 0 || temp > 9) {
		return n;
	}
	n = n * 10 + temp;

	if (n < 0) {
		cout << "The number you are trying to construct exceeds the limits of LLONG_MAX" << endl;
		return -404;

	}
	constructNumber(size, n, i + 1);
}

bool isPerfect(long long int n) {
	if (log10(n) > 10) {
		cout << "Number is too big for the calculation of perfect number!" << endl;
		return false;
	}
	long long int result = 0;
	for (int i = 1; i <= n / 2; i++) {
		(n % i == 0) ? result += i : 1;
	}
	return n == result;
}


int main() {

	int n = 19;			// The max number of digits for LLONG_MAX

	long long int result = constructNumber(n);
	(result == -404) ? cout << "" :
		cout << "The number you constructed is: " << result << endl;

	(isPerfect(result)) ? cout << "The number is perfect" << endl : cout << "The number is not perfect" << endl;

	return 0;
}