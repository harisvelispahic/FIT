#include <iostream>
#include <iomanip>
using namespace std;

/*
	Write a program that will generate the Fibonacci sequence and place it in a one-dimensional array of 20 elements.
	(The Fibonacci sequence is a sequence of numbers that starts with the numbers 0 and 1, and each subsequent number in the sequence is obtained
	by adding the previous two: F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)).

	Then create a function that will sort the array in ascending order by the middle digit.
	(For numbers with an even number, use the arithmetic mean of the middle two digits).
*/

void fillFibonacciArray(int* arr, int i = 0) {
	int n = 0;
	if (i == 0)
		n = 0;
	else if (i == 1)
		n = 1;
	else {
		n = *(arr + i - 1) + *(arr + i - 2);
	}
	if (i == 20)
		return;
	*(arr + i) = n;
	fillFibonacciArray(arr, i + 1);
}

void printArray(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << setw(5) << *(arr + i);
	}
}

float getMiddleDigit(int n) {
	int middleDigit = 0, size = 0, dividend = n;
	while (dividend) {
		size++;
		dividend /= 10;
	}
	if (size % 2 != 0) {
		return int(n / pow(10, size / 2)) % 10;
	}
	else {
		return float(int(n / pow(10, size / 2)) % 10 + int(n / pow(10, (size / 2) - 1)) % 10) / 2;
	}
}

void sortFibonacciArray(int* arr, int size) {
	int upperBound = size;
	for (int i = 0; i < upperBound; i++) {
		bool changeOccured = true;
		while (changeOccured) {
			changeOccured = false;
			for (int j = 0; j < upperBound - 1; j++) {
				if (getMiddleDigit(arr[j]) > getMiddleDigit(arr[j + 1])) {
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
					changeOccured = true;
				}
			}
		}
		upperBound--;
	}
}

int main() {

	int arr[20];

	cout << "Fibonacci array up to the 20th element: ";
	cout << endl;
	fillFibonacciArray(arr);
	printArray(arr, size(arr));

	cout << endl;
	cout << endl;

	cout << "Fibonacci array after sorting: ";
	cout << endl;
	sortFibonacciArray(arr, size(arr));
	printArray(arr, size(arr));
	cout << endl;


	return 0;
}