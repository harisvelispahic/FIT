#include <iostream>
#include <string>
using namespace std;

int main(){
   
	string input;
	int shift;
	cout << "Type in a word or a sentence you would like to encrypt: ";
	getline(cin, input);														//input
	cout << "Enter the shift: ";
	cin >> shift;

	while (shift < 0) {															//in case shift is negative
		shift += 26;
	}

	shift %= 26;																//shift greater than 26 can be used as shift%26
	
	
	string output="";
	for (int i = 0; i < input.length(); i++) {
		if (isupper(input[i])) {																//change for uppercase letters
			if (input[i] + shift > 'Z') output += char('A' - ('Z' - input[i]) + shift - 1);
			else output += char(input[i] + shift);
			
		}
		else if (islower(input[i])) {															//change for lowercase letters
			if (input[i] + shift > 'z') output += char('a' - ('z' - input[i]) + shift - 1);
			else output += char(input[i] + shift);

		}
		else {
			output += input[i];													//all other special chars, e.g. a blankspace are just appended
		}
	}

	cout << "The word/sentence you encrypted is: " << output << endl;

	return 0;
}
