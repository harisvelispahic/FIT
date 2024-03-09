#include <iostream>
using namespace std;

bool isLeap(int);
int getDaysTotal(int, int);
bool isValid(int, int, int);
int sumOfDays(int, int, int);
bool isOlder(int, int, int, int, int, int);


int main() {

	int d, m, y, oDay = 31, oMonth = 12, oYear = 10000;
	for (int i = 0; i < 3; i++) {
		do {
			cout << "Please input a date [" << i + 1 << "]: ";
			cin >> d >> m >> y;
			if (!isValid(d, m, y))
				cout << "Imroper date! Please enter again: " << endl;
			else {
				if (isOlder(d, m, y, oDay, oMonth, oYear)) {
					oDay = d;
					oMonth = m;
					oYear = y;
				}
			}
		} while (!isValid(d, m, y));
	}

	cout << "The oldest of the three dates is " << oDay << ". " << oMonth << ". " << oYear << "." << endl;

	return 0;
}

bool isLeap(int y) {
	return (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0));
}

int getDaysTotal(int m, int y) {
	int d = 0;
	switch (m) {
	case 2: isLeap(y) ? d = 29 : d = 28;
		break;
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		d = 31;
		break;
	case 4: case 6: case 9: case 11:
		d = 30;
		break;
	}
	return d;
}

bool isValid(int d, int m, int y) {
	if (d < 1 || d > getDaysTotal(m, y) || m < 1 || m > 12 || y < 1)
		return false;
	return true;
}

int sumOfDays(int d, int m, int y) {
	return y * 365 + (m - 1) * 30 + d;
}


bool isOlder(int d1, int m1, int y1, int d2, int m2, int y2) {
	int dSum1 = sumOfDays(d1, m1, y1);
	int dSum2 = sumOfDays(d2, m2, y2);
	return dSum1 < dSum2;
}