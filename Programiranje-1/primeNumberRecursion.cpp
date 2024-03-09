#include <iostream>
using namespace std;

/*
	Write a recursive function that checks if a number is a prime number
*/

bool isPrime(int n, int i = 2) {
	if (n < 2)
		return false;
	if (i > n / 2)
		return true;
	if (n % i == 0)
		return false;
	isPrime(n, i + 1);
}

int main() {

	int n;
	cout << "Please enter a number: ";
	cin >> n;

	(isPrime(n)) ? cout << "The number is a prime" << endl : cout << "The number is not a prime" << endl;

	return 0;
}