#include <iostream>
using namespace std;

/*
	Given an integer n, return true if it is a power of two. Otherwise, return false.
	An integer n is a power of two, if there exists an integer x such that n == 2^x.

	Examples:

	Input: n = 1
	Output: true
	Explanation: 2^0 = 1

	Input: n = 16
	Output: true
	Explanation: 2^4 = 16

	Input: n = 3
	Output: false
*/

bool isPowerOfTwo(long long int n) {
	/*cout << n << " ";*/
	if (n == 1)
		return 1;
	if ((((n * 10) / 2) % 10 != 0) || n <= 0)
		return 0;
	return isPowerOfTwo(n / 2);
}

int main() {
	
	int n = 2;
	(isPowerOfTwo(n)) ? cout << "n is a power of two" << endl :
		cout << "n is NOT a power of two" << endl;
}