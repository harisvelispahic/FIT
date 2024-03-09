#include <iostream>
#include <iomanip>
using namespace std;

int nthFactorialElement(int n) {										//nth factorial element
	if (n == 0 || n == 1)
		return 1;
	return n * nthFactorialElement(n - 1);
}


void factorialArray(long long int arr[], int arrSize, int i = 0) {		//fill the array with factorials
	if (i >= arrSize || i < 0)
		return;
	int n;

	if (i == 0)
		n = 1;
	else {
		n = (i + 1) * *(arr + i - 1);
	}

	if (n < 0)
		return;

	*(arr + i) = n;
	factorialArray(arr, arrSize, i + 1);

}


int main() {

	int n;
	do {
		cin >> n;
	} while (n < 0);

	cout << nthFactorialElement(n) << endl;				//nth factorial element

	long long int* arr = new long long int[n];

	factorialArray(arr, n);

	for (int i = 0; i < n; i++) {
		cout << setw(15) << *(arr + i);
		if ((i + 1) % 5 == 0)
			cout << endl;
	}


	delete[] arr;

	return 0;
}