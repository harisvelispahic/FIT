#include <iostream>
using namespace std;

/*
	Write a function

	char* removeExcessWhiteSpaces (char *str)
	which strips out any multiple spaces from the passed string.
	Additionally, the function should remove any spaces before the first word and after the last word.
	E.g. if the string is "  I like   programming  ", after calling the function the string should have the 
	following text "I like programming".
	The function should return a pointer to the beginning of the string.

	Note: It is not allowed to create other strings in a function or globally.
*/

char* removeExcessWhiteSpace(char* str) {
	if (strlen(str) == 0)
		return nullptr;

	int wordLength = strlen(str);
	// CHECK FOR THE BEGINNING OF STRING LITERAL
	int numberOfLeadingSpaces = 0, i = 0;							// number of blank spaces at the beginning
	while (str[i] == ' ' || str[i] == '\t') {
		numberOfLeadingSpaces++;
		i++;
	}

	for (int j = 0; j < numberOfLeadingSpaces; j++) {
		for (int k = 0; k < wordLength - 1; k++) {
			str[k] = str[k + 1];
		}
		wordLength--;
	}
	str[wordLength] = '\0';
	// END OF CHECK FOR THE BEGINNING OF STRING LITERAL


	// CHECK FOR THE END OF STRING LITERAL
	int lastLetterIndex = 0, numberOfTrailingSpaces = 0;			// number of blank spaces at the end
	for (int j = 0; j < wordLength; j++) {
		if (str[j] != ' ' && str[j] != '\t')
			lastLetterIndex = j;
	}
	//cout << lastLetterIndex << endl;
	
	str[lastLetterIndex + 1] = '\0';
	// END OF CHECK FOR THE END OF STRING LITERAL
	

	bool changeOccured = true;
	while (changeOccured) {
		changeOccured = false;
		for (int j = 0; j < wordLength - 1; j++) {
			if (str[j] == ' ' && str[j + 1] == ' ') {
				for (int k = j; k < wordLength - 1; k++) {
					str[k] = str[k + 1];
				}
				changeOccured = true;
				wordLength--;
			}
		}
	}

	/*for (int i = 0; i < wordLength; i++) {					// visualize blank spaces with dots
		if (str[i] == ' ' || str[i] == '\t')
			str[i] = '.';
	}*/

	return str;
}


int main() {
	
	char text[] = "        volim      UUP      ";
	cout << removeExcessWhiteSpace(text);
	cout << strlen(text);

	return 0;
}