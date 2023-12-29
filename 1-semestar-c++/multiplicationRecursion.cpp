#include <iostream>
using namespace std;

/*
*	Write a program that will allow the user to enter the size n of a one-dimensional dynamic array
	integer values (n > 2). Write a recursive function that will fill that string with a series of numbers
	1, 3, 3, 9, 27, ..., so that each subsequent number is equal to the product of the two previous numbers
	(The first two elements are 1 and 3.) 
	The recursion stops when the entire array is filled or when an overflow occurs.
	on an integer variable. 
	Then make another recursive function that will calculate the sum of all elements of that array 
	(Take care of the data type due to the size of the number).

	In this task, it is forbidden to index array elements with square brackets.
	Must use pointer arithmetic.
*/

void fillArray(long long int arr[], int arrSize, int i = 0) {
	
	long long int n;

	if (i == 0) {
		n = 1;
		*(arr + i) = 1;
	}
	else if (i == 1) {
		n = 3;
		*(arr + i) = 3;
	}

	else {
		n = *(arr + i - 1) * *(arr + i - 2);
	}

	if (i > arrSize || n < 0)
		return;

	*(arr + i) = n;

	fillArray(arr, arrSize, i + 1);
}

long long int sumArray(long long int arr[], int arrSize, int i = 0, long long int suma = 0) {
	suma = *(arr + i);
	if (i >= arrSize || suma < 0)
		return 0;
	return suma + sumArray(arr, arrSize, i + 1);
}

int main() {

	int arrSize;
	cout << "Please enter the array size: ";
	
	do {
		cin >> arrSize;
	} while (arrSize < 2);

	long long int* arr = new long long int[arrSize];

	fillArray(arr, arrSize);

	for (size_t i = 0; i < arrSize; i++) {
		cout << *(arr + i) << "  ";
	}
	cout << endl;

	cout << "The sum of all array elements is: " << sumArray(arr, arrSize) << endl;

	delete[] arr;
	
	return 0;
}