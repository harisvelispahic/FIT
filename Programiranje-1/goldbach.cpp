#include <iostream>
using namespace std;

int ITERATION_COUNTER = 0;
/*
*	Every even number can be represented as the sum of two prime numbers (the so-called Goldbach rule).
	Write a program that will first load two natural numbers n1 and n2 (n2 > n1).
	Then display all even numbers in the interval from n1 to n2 as the sum of two prime numbers.
	In the main program, just enter the two natural numbers and call the function
	which performs the assigned work.

	

*/
void input(int&, int&);
bool isPrime(int);
void goldbach(int);

int main() {
	
	int n1 = 0, n2 = 0;
	input(n1, n2);
	
	(n1 % 2 != 0) ? n1++ : 1;
	(n2 % 2 != 0) ? n2-- : 1;

	for (int i = n1; i <= n2; i += 2) {
		goldbach(i);
	}
	
	cout << "The program performed " << ITERATION_COUNTER << " iterations." << endl;

	return 0;
}

void input(int& n1, int& n2) {
	int temp1 = 0, temp2 = 0;
	cout << "Please input the interval bounds (a > 100 , b > a + 100): ";
	do {
		cin >> temp1 >> temp2;
		if (temp1 < 100 || temp2 < temp1 + 100 || temp1 > temp2) {
			cout << "Improper input! Please enter again: ";
		}

	} while (temp1 < 0 || temp2 < 0 || temp1 > temp2);

	n1 = temp1;
	n2 = temp2;
}

bool isPrime(int number) {
	if (number <= 1)
		return false;
	for (int i = 2; i <= number / 2; i++) {
		if (number % i == 0)
			return false;
	}
	return true;
}

void goldbach(int number) {
	/*(number % 2 != 0) ? number-- : 1;*/
	for (int i = number / 2, j = number / 2; i > 0 || j < number; i--, j++) {
		ITERATION_COUNTER++;
		if (isPrime(i) && isPrime(j) && number == i + j) {
			cout << number << " = " << i << " + " << j << endl;
			break;
		}
	}
}