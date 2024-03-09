#include <iostream>
#include <iomanip>
using namespace std;

/*
	Write a program that will allow the user to enter the size of a one-dimensional dynamic array
	integer values. Write a recursive function that will fill that string with a series of numbers
	2, 4, 8, 16, 32, 64, 128, 256, 512, etc., 
	so that each subsequent number is equal to the previous one multiplied by 2, starting with number 2.

	The recursion is terminated when the entire array is filled or when an overflow occurs on the integer variable.
	In this task, it is forbidden to index an array with square brackets. Must use pointer arithmetic.
*/


void fillArray(int arr[], int arrSize, int i = 1) {
	int n = pow(2, i);
	if (i > arrSize || n < 0)
		return;
	*(arr + i - 1) = n;
	fillArray(arr, arrSize, i + 1);
}


int main() {
	int arrSize = 0;
	
	cout << "Please enter the array size: ";
	do {
		cin >> arrSize;
	} while (arrSize <= 0);

	int* arr = new int[arrSize];

	fillArray(arr, arrSize);

	for (size_t i = 0; i < arrSize; i++) {
		if (*(arr + i) < 0) {
			cout << setw(15) << 0;
		}
		else {
		cout << setw(15) << *(arr + i);
		}
		if ((i + 1) % 4 == 0)
			cout << endl;
	}

	cout << endl;
	cout << endl;

	delete[] arr;

	return 0;
}