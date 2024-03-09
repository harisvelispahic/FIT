#include <iostream>
using namespace std;

/*
	
	Real divisors of number 220 are: 1, 2, 4, 5, 10, 11, 20, 22, 55, 110, and their sum is equal to 284; 
	Real divisors of number 284 are: 1, 2, 4, 71, 142 i njihova suma je jednaka 220. 
	
	

*/

int sumOfRealDivisors(int);
bool check(int, int);

int main() {
	
	int a = 0, b = 0;
	cout << "Enter the first number: ";
	cin >> a;
	cout << "Enter the second number: ";
	cin >> b;
	a = abs(a);
	b = abs(b);

	if (check(a, b))
		cout << "The numbers " << a << " and " << b << " are a friendly pair." << endl;
	else
		cout << "The numbers " << a << " and " << b << " are not a friendly pair." << endl;


	return 0;
}

int sumOfRealDivisors(int num) {
	int sum = 0;
	for (int i = 1; i < num; i++) {
		if (num % i == 0)
			sum += i;
	}
	
	return sum;
}


bool check(int a, int b) {
	if (a == sumOfRealDivisors(b) && b == sumOfRealDivisors(a))
		return true;
	else
		return false;
}