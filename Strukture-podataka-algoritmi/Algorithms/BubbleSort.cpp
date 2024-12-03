#include <iostream>
using namespace std;

enum SortingMode {
	ascending,
	descending
};

class BubbleSort {
public:

	static void Sort(int* Array, int size, SortingMode Mode) {
		bool change = true;
		int j = size - 1;

		if (Mode == ascending) {

			while (change) {
				change = false;
				for (int i = 0; i < j; i++) {
					if (Array[i] > Array[i + 1]) {
						swap(Array[i], Array[i + 1]);
						change = true;
					}
				}
				j--;
			}
		}

		else {

			while (change) {
				change = false;
				for (int i = 0; i < j; i++) {
					if (Array[i] < Array[i + 1]) {
						swap(Array[i], Array[i + 1]);
						change = true;
					}
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
	BubbleSort::Sort(Array, size(Array), ascending);
	BubbleSort::Print(Array, size(Array));
	
	cout << "Descending:\t";
	BubbleSort::Sort(Array, size(Array), descending);
	BubbleSort::Print(Array, size(Array));

	return 0;
}