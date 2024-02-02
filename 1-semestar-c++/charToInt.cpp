#include <iostream>
using namespace std;

/*
	Write a recursive function that converts a string literal into an integer variable
	Input: str = “1234” 
	Output: 1234
	Input: str = “0145” 
	Output: 145
*/

int charToInt(char* text, int n = 0, int i = 0) {
	if (i == strlen(text)) {
		return n;
	}
	n = n * 10 + (text[i] - '0');

	charToInt(text, n, i + 1);
}

int main() {

	char number[] = "0145";
	cout << charToInt(number);

	return 0;
}