#include <iostream>
#include <iomanip>
using namespace std;


// Write a recursive function to find the GCD (greates common divisor) of two numbers using Euclidean Algorithm.
// 1180 = 482 * 2 + 216
// 482 = 216 * 2 + 50
// 216 = 50 * 4 + 16
// 50 = 16 * 3 + ### 2 ###
// 16 = 2 * 4 + 0

int greatestCommonDivisor(int a, int b) {
	if (a == b)
		return a;
	if (a == 1 || b == 1)
		return 1;
	int n = a % b;
	if (n == 0)
		return 0;
	if (a % n == 0 && b % n == 0)
		return n;

	return greatestCommonDivisor(b, a % b);
}

int main() {

	int n1, n2;
	do {
		cin >> n1 >> n2;
	} while (n1 <= 0 || n2 <= 0);
	if (n1 < n2) {
		int temp = n1;
		n1 = n2;
		n2 = temp;
	}

	cout << "The greates common divisor of numbers [" << n1 << "," << n2 << "] is equal to: " << 
		greatestCommonDivisor(n1, n2);


	return 0;
}