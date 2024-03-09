#include <iostream>
using namespace std;

/*
	function "sortLetters" sorts the letters in the char* so that the most common letter in the string is placed at
	the begining of the new string "letters", then the letters are sorted alphabeticaly and the result is the
	uppercase of most to least occuring letters in a string sorted alphabetically
*/

int maxNumberLetterOccurance(const char* str) {
	int MAX = 0;
	for (int i = 0; i < strlen(str); i++) {
		int counter = 0;
		if (str[i] != ' ') {
			for (int j = i; j < strlen(str); j++) {
				if (str[j] == str[i]) {
					counter++;
				}
			}
			MAX = max(counter, MAX);
		}
	}
	return MAX;
}

void sort(char arr[], int size) {
	bool change = true;
	int upperBound = size - 1, iterations = 0;
	while (change)
	{
		change = false;
		for (size_t i = 0; i < upperBound; i++)
		{
			if (arr[i] > arr[i + 1]) {
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				change = true;
				iterations++;
			}
		}
		upperBound--;
	}
}

string sortLetters(char* text, char* letters) {
	int strLength = strlen(text);
	for (int i = 0; i < strLength; i++) {
		if (text[i] == ' ') {
			for (int j = i; j < strLength - 1; j++) {
				text[j] = text[j + 1];
			}
			strLength--;
		}
		text[i] = tolower(text[i]);
	}
	text[strLength] = '\0';

	string finalResult;
	for (int i = maxNumberLetterOccurance(text) - 1; i >= 0; i--) {
		char* arr = new char[strLength] {' '};
		int x = 0, arrLength=0;
		for (int j = 0; j < strLength; j++) {
			int counter = 0;
			char ch = text[j];
			for (int k = 0; k < strLength; k++) {
					if (text[k] == ch) {
						counter++;
					}
			}
			bool isDuplicate = false;
			for (int b = 0; b < strLength; b++) {
				if (arr[b] == ch) {
					isDuplicate = true;
				}
			}
			if(counter == (i + 1) && !isDuplicate) {
				arr[x++] = ch;
				arrLength++;
			}
		}
		sort(arr, arrLength);
		for (int a = 0; a < arrLength; a++) {
			letters[a] = toupper(arr[a]);
		}
		finalResult += letters;
	}
	return finalResult;
}

int main() {
	
	char text[100] = "Ovo je neki primjer";
	char letters[100] = "";
	cout << sortLetters(text, letters);
}