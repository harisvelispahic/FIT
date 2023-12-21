#include <iostream>
#include <cmath>
using namespace std;

bool isValid(int);
int decimalToBinary(int);
int sumOfDigits(int);

int main() {
										  
	int n = 0;
	cout << "Please enter the number of iterations: ";
	do {
		cin >> n;
		if (n <= 0)
			cout << "Improper input! Please enter again: ";
	} while (n <= 0);

	int input, min = INT_MAX;
	for (int i = 0; i < n; i++) {
		do {
			cout << "Please input a decimal number [" << i + 1 << "]: ";
			cin >> input;
			if (input < min)
				min = input;
		} while (input < 0);
	}
			
	cout << "The least number in the interval is " << min << " and its binary represantation is equal to: " << 
		decimalToBinary(min) << endl;
	cout << "Sum of digits of the binary number is equal to: " << sumOfDigits(decimalToBinary(min)) << endl;
		  
	return 0;							  
}										  
		
bool isValid(int number) {
	number = abs(number);
	while (number) {
		if (number % 10 != 0 && number % 10 != 1)
			return false;
		number /= 10;
	}
	return true;
}

int decimalToBinary(int number) {
	number = abs(number);
	int binaryNumber = 0, counter=0;
	while (number) {
		binaryNumber += (number % 2) * pow(10, counter);
		counter++;
		number /= 2;
	}
	return binaryNumber;
}

int sumOfDigits(int number) {
	number = abs(number);
	int sum = 0;
	while (number) {
		sum += number % 10;
		number /= 10;
	}
	return sum;
}