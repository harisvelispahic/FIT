#include <iostream>
using namespace std;

enum SortingMode {
	ascending,
	descending
};

class InsertionSort {
public:

	static void Sort(int* Array, int size, SortingMode Mode) {
		
		int j;
		if (Mode == ascending) {

			for (int i = 1; i < size; i++) {
				j = i;
				while (j > 0 && Array[j] > Array[j - 1]) {
					swap(Array[j], Array[j - 1]);
					j--;
				}
			}
		}

		else {
			for (int i = 1; i < size; i++) {
				j = i;
				while (j > 0 && Array[j] < Array[j - 1]) {
					swap(Array[j], Array[j - 1]);
					j--;
				}
			}
		}
	}

	static void Print(int* Array, int size) {
		for (int i = 0; i < size; i++) {
			cout << Array[i];
			cout << ((i < size - 1) ? ", " : " ");
		}
		cout << endl;
	}
};



void Randomize(int* Array, int size) {
	for (int i = 0; i < size; i++) {
		Array[i] = rand() % 200 - 100;
	}
}


int main() {

	int Array[20];
	Randomize(Array, size(Array));

	cout << "Ascending:\t";
	InsertionSort::Sort(Array, size(Array), ascending);
	InsertionSort::Print(Array, size(Array));

	cout << "Descending:\t";
	InsertionSort::Sort(Array, size(Array), descending);
	InsertionSort::Print(Array, size(Array));

	return 0;
}