#include <iostream>
using namespace std;

/*
	function "strictlyIncreasingDigits" checks if digits in the passed string are in the strictly increasing order
	return:	1 -> strictly increasing order
			0 -> not in a strictly increasing order
		   -1 -> no digits in a string
*/

void enterText(char* s, int size) {
	cout << "Please enter a string: ";
	cin.getline(s, size);
}

int strictlyIncreasingDigits(const char* s) {
	int temp = INT_MIN;
	for (int i = 0; i < strlen(s); i++) {
		if (isdigit(*(s + i))) {
			if (temp >= *(s + i)) {
				return 0;
			}
			temp = int(*(s + i));
		}
	}
	if (temp == INT_MIN) {
		return -1;
	}
	return 1;
}

int main() {

	char input[30] = "";
	enterText(input, size(input));

	if (strictlyIncreasingDigits(input) == 1) {
		cout << "The digits in this string are in a strictly increasing order." << endl;
	}
	else if (strictlyIncreasingDigits(input) == 0) {
		cout << "The digits in this string are NOT in a strictly increasing order." << endl;
	}
	else {
		cout << "There are no digits in this string." << endl;
	}



	return 0;
}