#include <iostream>
#include <iomanip>
using namespace std;

// Write a recursive function to find the sum of digits of a given integer.

int sumOfDigits(int n, int sum = 0) {
	if (log10(n) < 1)
		return n;
	return n % 10 + sumOfDigits(n / 10);
}

int main() {

	int n; 
	cin >> n;
	(n < 0) ? n = -n : 0;
	cout << "Sum of digits of " << n << " is equal to: " << sumOfDigits(n) << endl;
	
	return 0;
}