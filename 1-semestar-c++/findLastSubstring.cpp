#include <iostream>
using namespace std;

/*
	
	Data je funkcija

	const char* findLastSubstring (const char *str, const char *substr)

	koja traži tekst "substr" unutar proslijeđenog stringa "str".
	Funkcija treba da vrati pokazivač na poziciju u string str gdje se nalazi findLastSubstring. 
	Ukoliko ima više takvih stringova funkcija treba vratiti indeks koji predstavlja početak prvog stringa, 
	a ako se findLastSubstring ne nalazi u stringu treba vratiti nul-pokazivač.

	Napisati novu funkciju findLastSubstring koja slično funkciji findLastSubstring pronalazi tekst unutar stringa 
	ali ovaj put vraća indeks posljednjeg pojavljivanja. 
	
	Primjeri:

	const char *n = "Danas je divan dan!";
	cout << findLastSubstring(n, "divan"); 	//9
	cout << findLastSubstring(n, "Divan"); 	//-1 (nema)
	cout << findLastSubstring(n, "Danas"); 	//0
	cout << findLastSubstring(n, "an");    	//16
	cout << findLastSubstring(n, "an!");   	//16
	cout << findLastSubstring("abc cde abc", "abc"); 	//8

	Napomena: Pri rješavanju ovog zadatka za
*/

bool isSubstring(const char* str, const char* substr) {
	int stringLength = 0;
	while (str[stringLength] != '\0')
		stringLength++;

	int substringLength = 0;
	while (substr[substringLength] != '\0')
		substringLength++;

	int finalLength = 0;
	char firstSubstringChar = substr[0];
	bool found = false;

	for (int i = 0; i < stringLength && !found; i++) {
		if (str[i] == firstSubstringChar) {
			int counter = 0;
			for (int j = i, k = 0; k < substringLength; j++, k++) {
				if (str[j] == substr[k]) {
					counter++;
				}
			}
			if (counter == substringLength) {
				finalLength = counter;
				found = true;
				break;
			}
		}
	}
	return finalLength == substringLength;
}

int findLastSubstring(const char* str, const char* substr) {
	int stringLength = 0;
	while (str[stringLength] != '\0')
		stringLength++;

	if (!isSubstring(str, substr)) {
		return -1;
	}

	int lastOccurence = 0;
	for (int i = 0; i < stringLength; i++) {
		if (isSubstring(str + i, substr)) {
			lastOccurence = i;
		}
	}
	return lastOccurence;
}

int main() {

	const char* n = "Today is a great day!";
	
	cout << findLastSubstring(n, "great");
	

	return 0;
}