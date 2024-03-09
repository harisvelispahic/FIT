#include <iostream>
using namespace std;

/*
	Write a program that loads the natural number n.
	The program should print the smallest natural number m, greater than or equal to n,
	which is a power of some natural number, i.e. m = k^l, where k and l ≥ 2 are natural numbers.

	In this task, it is forbidden to use the pow function for power calculations.
	Calculate the power using a recursive function that is passed k and l i
	in which only the multiplication operation is allowed.

	To facilitate the solution, you can choose the function prototype as desired

	15 -> 16
	16 -> 16

*/

// ideja, n*n niz u koji smjestamo sve potencije koje dobijemo, zatim uzmemo samo kvadrate koji su veci jednaki n
// ako je potencija jedan n, ispisujemo ga, ako je veci, trazimo distancu koja je najmanja i ispisujemo taj kvadrat

int power(int base, int exp) {
	if (exp > 0)
		return base * power(base, exp - 1);
	return 1;
}

void powerOfNumber(int arr[], int n, int k = 2, int l = 2, int i = 0) {
	if (n == power(k, l)) {						// if n is a power, it immediately outputs it
		*(arr + i) = n;
		return;
	}
	if (n >= 1 && n < 4) {						// if n>=1 && n<4 we know the closest is 4
		*(arr + i) = 4;
		return;
	}
	if (k == n && l == n) {
		*(arr + (n - 1) * (n - 1) - 1) = power(k, l);
		return;
	}
	int m = power(k, l);
	if (m > n) {
		*(arr + i) = power(k, l);
	}
	else {
		i--;
	}
	if (k < n && l < n) {
		powerOfNumber(arr, n, k + 1, l, i + 1);
	}
	else if (k == n && l < n) {
		powerOfNumber(arr, n, k = 2, l + 1, i + 1);
	}
	else if (k < n && l == n) {
		powerOfNumber(arr, n, k + 1, l, i + 1);
	}
}



int main() {

	int n;
	do {
		cout << "Please enter the number you want to find the closest square of (n > 0): ";
		cin >> n;
	} while (n <= 0);

	int size = (n - 1) * (n - 1);
	if (n == 1)
		size = 1;

	int* arr = new int[size] {0};
	powerOfNumber(arr, n);


	int difference = INT_MAX;
	bool found = false;
	for (int i = 0; i < size; i++) {
		if (n == *(arr + i)) {
			found = true;
			cout << "The number you provided is a power itself: " << n << endl;
			break;
		}
		if (n < *(arr + i)) {
			difference = min(difference, abs(n - *(arr + i)));
		}
	}
	
	if (!found)
		cout << "The closest power to the number you provided is: " << n + difference << endl;

	return 0;
}