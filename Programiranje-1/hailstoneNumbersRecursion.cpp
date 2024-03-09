#include<iostream>
using namespace std;

/*
	1. Enable the input of a natural number N (N > 0).
	After that, generate Hailstone numbers (sequence) for the entered N i
	count how many steps are needed until the sequence reaches the value 1.

	Note: To solve the problem, you must use the recursive function.
	
	if Xn is even : Xn+1 = Xn / 2
	if Xn is odd  : Xn+1 = 3Xn + 1

	Input : N = 7
	Output : 
	Hailstone Numbers: 7, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
	No. of steps Required: 17
	Explanation:
	For N = 7.
	The numbers will be calculated as follows:
	7 // initial value
	3 * 7 + 1 = 22 // Since it's an odd number
	22 / 2 = 11 // Even number
	3 * 11 + 1 = 34 // Odd number
	// .... and so on until 1

*/

int hailstoneNumbers(int arr[], int size, int n, int i = 0) {
	int temp = n;
	if (i == 0) {
		*(arr) = n;
	}
	else {
		if (n % 2 == 0)
			temp /= 2;
		else {
			temp = 3 * temp + 1;
		}

		*(arr + i) = temp;

		if (temp == 1)
			return i;
	}
	hailstoneNumbers(arr, size, temp, i + 1);
}

int main() {

	int n;
	do {
		cout << "Please enter a number (n>0): ";
		cin >> n;
	} while (n < 0);

	cout << endl;

	int arr[10000];

	int sequenceLength = hailstoneNumbers(arr, size(arr), n) + 1;
	cout << "The hailstone numbers sequence length for the number [" << n << "]: " << sequenceLength << endl;

	cout << endl;
	cout << "The hailstone numbers sequence: " << endl;

	for (int i = 0; i < sequenceLength; i++) {
		cout << *(arr + i) << " ";
	}
	
	cout << endl;

	return 0;
}