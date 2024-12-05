#include <iostream>
using namespace std;

enum SortingMode {
	ascending,
	descending
};

class SelectionSort {
public:

	static void Sort(int* Array, int size, SortingMode Mode) {
		if (Mode == ascending) {

			for (int i = 0; i < size - 1; i++) {
				int minIndex = i;
				for (int j = i + 1; j < size; j++) {
					if (Array[j] < Array[minIndex]) {
						minIndex = j;
					}
				}
				if (minIndex != i) {
					swap(Array[i], Array[minIndex]);
				}
			}
		}

		else {
			for (int i = 0; i < size - 1; i++) {
				int minIndex = i;
				for (int j = i + 1; j < size; j++) {
					if (Array[j] > Array[minIndex]) {
						minIndex = j;
					}
				}
				if (minIndex != i) {
					swap(Array[i], Array[minIndex]);
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
	SelectionSort::Sort(Array, size(Array), ascending);
	SelectionSort::Print(Array, size(Array));

	cout << "Descending:\t";
	SelectionSort::Sort(Array, size(Array), descending);
	SelectionSort::Print(Array, size(Array));

	return 0;
}