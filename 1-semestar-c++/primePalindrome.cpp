#include <iostream>
using namespace std;

/*
	Write a program that allows the user to enter an integer value greater than 100.
	Write a function that will check whether the entered number is both a prime and a "palindrome" at the same time.
	that is, whether the number is the same when all the digits are reversed. If necessary, use additional functions.

	For example numbers 383, 727, 757, 787, 797, 919, 929 are both prime numbers and "palindromes" at the same time.
*/

void input(int&);
bool isPrime(int);
bool isPalindrome(int);

int main() {

	int number = 0;
	input(number);
	
	if (isPrime(number) && isPalindrome(number)) {
		cout << number << " is both prime and a palindrome." << endl;
	}

	return 0;
}

void input(int& number) {
	int temp = 0;
	cout << "Input a number (n>100): ";
	do {
		cin >> temp;
		if (temp <= 100) {
			cout << "Improper input! Please input again: ";
		}
		
	} while (temp <= 100);

	number = temp;
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

bool isPalindrome(int number) {
	int check = number;
	int newNumber = 0;
	while (number) {
		newNumber = newNumber * 10 + number % 10;
		number /= 10;
	}
	return check == newNumber;
}