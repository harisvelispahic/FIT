#include <iostream>
#include <iomanip>
using namespace std;

int nthFibonacciElement(int n) {
	if (n == 0 || n == 1)
		return 1;
	return nthFibonacciElement(n - 2) + nthFibonacciElement(n - 1);
}

void fibonacciArray(long long int arr[], int arrSize, int i = 0) {
	
	if (i >= arrSize || i < 0)
		return;

	long long int n;

	if (i == 0 || i == 1)
		n = 1;

	else
		n = *(arr + i - 1) + *(arr + i - 2);

	if (n < 0)
		return;

	*(arr + i) = n;

	fibonacciArray(arr, arrSize, i + 1);
}


int main() {
	
	int arrSize;
	cout << "Please enter the array size: ";
	do {
		cin >> arrSize;
	} while (arrSize <= 0);

	long long int* arr = new long long int[arrSize];

	fibonacciArray(arr, arrSize);
	
	for (int i = 0; i < arrSize; i++) {
		cout << setw(24) << *(arr + i);
		if ((i + 1) % 5 == 0)
			cout << endl;
	}

	delete[] arr;

	return 0;
}