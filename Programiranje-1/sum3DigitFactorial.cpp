#include <iostream>
using namespace std;

int factorial(int);

int main() {
	//output all 3-digit numbers that ABC = A! + B! + C!
	
	for (int i = 100; i < 1000; i++) {
		int lastDigit = i % 10;
		int middleDigit = (i % 100) / 10;
		int firstDigit = (i % 1000) / 100;
		if (i == factorial(lastDigit) + factorial(middleDigit) + factorial(firstDigit)) {
			cout << i << " = " << firstDigit << "! + " << middleDigit << "! + " << lastDigit << "!" << endl;
		}
	}

	return 0;
}

int factorial(int num) {
	int output = 1;
	for (int i = 1; i <= num; i++) {
		output *= i;
	}
	return output;
}