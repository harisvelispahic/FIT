#include <iostream>
using namespace std;

bool isPrime(int);
bool isPalindrome(int);
void palindromeGoldbach(int);

int main() {

	int n1, n2;
	do {
		cout << "Please enter the interval bounds [n1,n2]: ";
		cin >> n1 >> n2;
	} while (n1 < 100 || n2 < n1 + 100);

	(n1 % 2 != 0) ? n1++ : 1;
	(n2 % 2 != 0) ? n2-- : 1;
	for (int i = n1; i <= n2; i += 2) {
		palindromeGoldbach(i);
	}

	return 0;
}

bool isPrime(int number) {
	if (number <= 1)
		return false;
	for (int i = 2; i < number / 2; i++) {
		if (number % i == 0)
			return false;
	}
	return true;
}

bool isPalindrome(int number) {
	int check = number, newNumber = 0;
	while (number) {
		newNumber = newNumber * 10 + number % 10;
		number /= 10;
	}
	return check == newNumber;
}

void palindromeGoldbach(int number) {
	(number % 2 != 0) ? number-- : 1;
	for (int i = number / 2, j = number / 2; i > 0 || j < number; i--, j++) {
		if (isPalindrome(i) && isPalindrome(j) && isPrime(i) && isPrime(j) && i + j == number) {
			cout << number << " = " << i << " + " << j << endl;
			break;
		}
	}
}