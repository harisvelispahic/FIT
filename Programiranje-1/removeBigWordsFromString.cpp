#include <iostream>
using namespace std;

/*
	Write a function that receives a sentence as a parameter (string of up to 200 characters)
	and removes from it any word that has more than 5 characters.

	E.g. if the sentence is given: "Thursday was a beautiful and sunny day."
	the function should be converted to: "was a and sunny day"
	For the sake of simplicity, assume that word is any string of characters separated by a space character

*/

void removeBigWords(char* text) {
	// count how many words
	int words = 1;
	for (int i = 0; i < strlen(text); i++) {
		(text[i] == ' ') ? words++ : 1;
	}

	int counter = 0;
	char** arrayOfTexts = new char* [words];
	for (int i = 0; i < strlen(text); i++) {
		char* temp = new char[strlen(text) + 1];			// max possible length
		int j = 0;
		while (text[i + j] != ' ' && text[i + j] != '\0') {
			temp[j] = text[i + j];
			j++;
		}
		temp[j] = '\0';
		i = i + j;
		arrayOfTexts[counter] = temp;
		counter++;
	}

	for (int i = 0; i < words; i++) {
		if (strlen(arrayOfTexts[i]) <= 5) {
			cout << arrayOfTexts[i] << " ";
		}
		delete[] arrayOfTexts[i];
		arrayOfTexts[i] = nullptr;
	}
	delete[] arrayOfTexts;
	arrayOfTexts = nullptr;
}


int main() {

	char text[200];
	cin.getline(text, size(text));

	removeBigWords(text);

	return 0;
}
