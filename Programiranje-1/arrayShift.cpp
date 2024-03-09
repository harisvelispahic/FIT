#include <iostream>
using namespace std;

/*
*	Program enables input of at least 3-digit numbers into an array[20].
	Elements with first digit even are removed.
	Array is also sorted.
*/

const int arrSize = 20;

void input(int[]);
bool isFirstDigitEven(int);

int main(){
		int arr[arrSize] = {0};
	input(arr);
	int upperBound = arrSize;

	for (int i = 0; i < upperBound; i++) {
		if (isFirstDigitEven(arr[i])) {
			for (int j = i; j < upperBound - 1; j++) {
				arr[j] = arr[j + 1];
			}
			upperBound--;
			i--;
		}
	}

	for (int i = 0; i < upperBound; i++) {
		cout << arr[i] << "\t";
	}
	
	/*															//izbacivanje elementa iz niza
	int niz[] = { 1,2,3,4,5,6,7,8,9,10 };
	int velicinaNiza = 10;
	for (int i = 0; i < velicinaNiza; i++) {
		if (niz[i] == 5) {
			for (int j = i; j < velicinaNiza - 1; j++) {
				niz[j] = niz[j + 1];
			}
			velicinaNiza--;
		}
	}

	for (int i = 0; i < velicinaNiza; i++) {
		cout << niz[i] << "\t";
	}
	*/

	return 0;
}

void input(int arr[arrSize]) {
	for (int i = 0; i < arrSize; i++) {
		int num;
		cout << "Enter " << i+1 << ". element of the array: ";
		cin >> num;
		while (num < 100) {
			cout << "Array elements cannot be less than 100. Please enter again: ";
			cin >> num;
		}
		arr[i] = num;
	}
}


bool isFirstDigitEven(int num) {
	while (num > 10) {
		num /= 10;
	}
	
	return num % 2 == 0;
}
