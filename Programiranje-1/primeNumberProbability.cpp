#include <iostream>
using namespace std;

bool isPrime(int);

int main() {
	srand(time(NULL));

	int arr[100];
	for (int i = 0; i < 100; i++) {
		int num = rand() % 100000 + 1;
		int temp = log10(num) + 1;
		
		if (temp >= 3 && temp % 2 != 0) {		//greater than 100 and odd number of digits 
			arr[i] = num;
		}
		else {
			i--;
		}
	}

	int counter = 0;
	for (int i = 0; i < 100; i++) {
		if (isPrime(arr[i])) counter++;
	}

	cout << "Prime numbers make up " << counter << "% of the array" << endl;

	return 0;
}

bool isPrime(int num) {
	if (num < 2) 
		return false;
	
		for (int i = 2; i <= num / 2; i++) {
			if (num % i == 0)
				return false;
		}
		return true;
}