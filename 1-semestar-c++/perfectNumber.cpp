#include <iostream>
using namespace std;

/*
	Program that calculates the arithmetic mean of all perfect numbers from an interval
	For example, 28 is a perfect number, his divisors are 1,2,4,7 and 14, and 1 + 2 + 4 + 7 + 14 = 28
	The only perfect numbers in the interval [1,100] are 6 and 28


*/
void input(int&, int&);
bool isPerfect(int);

int main() {
	int a, b;
	input(a, b);
	float sum = 0;
	int counter = 0;

	for (int i = a; i < b; i++) {
		if (isPerfect(i)) {
			cout << i << endl;
			sum += i;
			counter++;
		}
	}
	
	cout << "Arithmetic mean of all perfect numbers in the interval is equal to: " << sum / counter << endl;

	return 0;
}

void input(int& a, int& b) {
	int lowerBound = 0, upperBound = 0;
	cout << "Input the lower and upper bound of the interval: ";
	do {
		cin >> lowerBound >> upperBound;
		if (lowerBound > upperBound) {
			cout << "Donja granica < gornja granica. Unesi ponovo: ";
		}

	} while (lowerBound > upperBound);

	a = lowerBound;
	b = upperBound;
}

bool isPerfect(int broj) {
	int sum = 0;
	for (int i = 1; i < broj; i++) {
		if (broj % i == 0) {
			sum += i;
		}
	}
	return broj == sum;
}