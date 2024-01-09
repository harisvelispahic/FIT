#include<iostream>
using namespace std;

/*
	2. Write a recursive function that converts a number entered as a string of characters into the data type int.
	Input: str = “1234”
	Output: 1234
	Input: str = “0145”
	Output: 145

*/

bool isValid(char* c) {
	for (int i = 0; i < strlen(c); i++) {
		if (!isdigit(*(c + i)))
			return false;
	}
	return true;
}

long long int charToInt(const char* input, int size, long long int n = 0, int i = 0) {
	if (i == size) {
		return n;
	}
	n = n * 10 + (*(input + i) - '0');
	charToInt(input, size, n, i + 1);
}


int main() {
	
	char characterNumber[100];
	do {
		cout << "Please enter a number: ";
		cin >> characterNumber;

	} while (!isValid(characterNumber));
	*(characterNumber + 19) = '\0';			// considering LLONG_MAX is 20 digits long
	cout << charToInt(characterNumber, strlen(characterNumber));

	return 0;
}