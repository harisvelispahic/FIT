#include <iostream>
#include <cmath>
using namespace std;

/*
	Program outputs the even digits of a number
	168 -> 68
*/

int takeEvenDigits(int);

int main() {

	int m, n;
	do {
		cout << "Please input the interval bounds [m,n]: ";
		cin >> m >> n;
	} while (m < 0 || n <= m);

	for (int i = m; i <= n; i++) {
		if (takeEvenDigits(i) != 0) {
			cout << i << " -> " << takeEvenDigits(i) << endl;
		}
	}


	return 0;
}

int takeEvenDigits(int num) {
	int newNumber = 0, counter = 0;;
	while (num) {
		if ((num % 10) % 2 == 0) {
			newNumber += (num % 10) * pow(10, counter);
			counter++;
		}
		num /= 10;
	}
	return newNumber;
}