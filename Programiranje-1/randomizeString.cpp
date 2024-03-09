#include <iostream>
using namespace std;

char* randomizeCharacterArray(char* source, int size) {
	for (int i = 0; i < size - 1; i++) {
		source[i] = char(rand() % 26 + 65);
	}
	source[size - 1] = '\0';
	return source;
}

bool isValid(const char* text, int size) {
	for (int i = 0; i < size; i++) {
		if (!isalpha(text[i]))
			return false;
	}
	return true;
}

int main() {
	srand(time(0));

	char name[40];
	do {
		cout << "Please enter your name: ";
		cin.getline(name, size(name));
	} while (!isValid(name, strlen(name)));

	for (int i = 0; i < strlen(name); i++) {
		name[i] = toupper(name[i]);
	}
	char* randomText = new char[strlen(name) + 1];

	int counter = 0;
	while (strcmp(randomizeCharacterArray(randomText, strlen(name) + 1), name)) {
		counter++;
	}
	cout << "It took " << counter << " tries before your name got randomly generated!" << endl;

	delete[] randomText;
	randomText = nullptr;
	
	return 0;
}