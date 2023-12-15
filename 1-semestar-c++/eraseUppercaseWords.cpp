#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
	Napisati funkciju (i testirati u main funkciji) koja kao parametar prima recenicu
	(niz od najvise 200 karaktera) i iz nje uklanja svaku rijec koja pocinje velikim slovom.

	Npr. ako je data recenica:
	"Stari most u Mostaru spaja obale rijeke Neretve."
	funkcija je treba pretvoriti u:
	"most u spaja obale rijeke"

	Funkcija vraca broj rijeci u polaznoj recenici (prije odsijecanja ostalih rijeci).
	Radi jednostavnosti rjesenja, pretpostavite da je rijec bilo koji niz znakova razdvojen znakom razmak.
*/

string uppercaseErase(string);
string input(string&);

int main() {

	string sentence;
	input(sentence);
	cout << uppercaseErase(sentence);


	return 0;
}

string input(string& input) {
	string check = "";
	cout << "Please enter a sentence (up to 200 characters): " << endl;
	getline(cin, input);
	while (input.length() > 200) {
		cout << "Exceeded the 200 characters limit! Please enter again: " << endl;
		getline(cin, input);
	}
	input += ' ';
	return input;
}

string uppercaseErase(string input) {
	int words = 1;
	vector<string> arr;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ')
			words++;
	}
	
	string temp = "";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ' ')
			temp += input[i];
		else {
			arr.push_back(temp);
			temp = "";
		}

	}
	
	string output = "";
	for (int i = 0; i < words-1; i++) {
		if (islower(arr.at(i)[0]))
			output += arr.at(i) + ' ';
	}
	
	return output;
}