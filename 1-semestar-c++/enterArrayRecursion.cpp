#include <iostream>
using namespace std;

/*
	Write a program that will allow the user to enter the size of a one-dimensional dynamic integer array
	values. Write a recursive function that will fill that string with random numbers in the range from 1 to 100.
	To generate random numbers, use rand() % 100 + 1.
	Filling the array is stopped when the entire array is filled or when the same random number is obtained three 
	times in a row.
	In this task, it is forbidden to index array elements with square brackets.
	Must use pointer arithmetic. It is mandatory to solve everything with one recursive function.
*/

int enterArray(int* arr, int size, int i = 0, int count = 0, int actualSize = 0) {
	if (i == size || count == 3)
		return actualSize;
	int randomNumber = rand() % 100 + 1;
	*(arr + i) = randomNumber;
	if (*(arr + i - 1) == randomNumber) {
		count++;
	}
	else {
		count = 1;
	}
	enterArray(arr, size, i + 1, count, actualSize + 1);
}

void printArray(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << *(arr + i) << " ";
	}
}

int main() {
	srand(time(NULL));

	int n;
	do {
		cout << "Enter the size of the array: ";
		cin >> n;
	} while (n < 1);

	int* arr = new int[n];

	int actualSize = enterArray(arr, n);
	printArray(arr, actualSize);

	return 0;
}