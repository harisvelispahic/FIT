#include <iostream>
using namespace std;

/*
	Enable the input of an integer value that is the size of a dynamic array of integers
	Enable the input of a either "s" or "p" characters
	With a recursive function, fill the array with the fibonacci elements. 

	If the chosen character is "s", fill the array without leaving skipping a step. 
	If the choice character is "p", you should leave out the even values.
	
	If there is integer overflow, stop the array entering.
*/

int enterFibonacciS(int* arr, int size, int i = 0) {
	int n = 0;
	if (i == 0)
		n = 0;
	if (i == 1)
		n = 1;
	
	if (i >= 2)
		n = *(arr + i - 1) + *(arr + i - 2);

	if (i >= size || n < 0) {
		return i;
	}

	*(arr + i) = n;
	enterFibonacciS(arr, size, i + 1);
}

int enterFibonacciP(int* arr, int size, int i = 0) {
	int n = 0;
	if (i == 0)
		n = 0;
	if (i == 1)
		n = 1;

	if (i >= 2)
		n = *(arr + i - 1) + *(arr + i - 2);

	if (i >= size || n < 0) {
		return i;
	}

	if (i == size - 1 && n % 2 == 0)	
		return i - 1;		// check if the last element is even since it cannot be checked by the condition below

	if (*(arr + i - 1) % 2 == 0) {
		*(arr + i - 1) = n;
		i--;
	}
	else
		*(arr + i) = n;

	enterFibonacciP(arr, size, i + 1);
}

int main() {

	int size;
	do {
		cout << "Please input the size of the array: ";
		cin >> size;
	} while (size < 1);
	
	int* arr = new int[size];

	char choice;
	do {
		cout << "Please enter a choice character (s or p): ";
		cin >> choice;
	} while (choice != 'p' && choice != 's');
	
	int upperBound = 0;

	if (choice == 's')
		upperBound = enterFibonacciS(arr, size);

	else if (choice == 'p')
		upperBound = enterFibonacciP(arr, size);

	cout << "The fibonacci array: " << endl;
	for (int i = 0; i < upperBound; i++) {
		cout << *(arr + i) << " ";
	}


	delete[] arr;
	arr = nullptr;

	return 0;
}