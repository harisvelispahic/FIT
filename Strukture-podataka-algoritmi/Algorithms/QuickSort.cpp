#include <iostream>
using namespace std;

class QuickSort {
public:

	// Method for finding a pivot element
	// Pivot element is an element that meets the following terms:
	//		1. Correct position in the final, sorted array
	//		2. Items to the left are smaller
	//		3. Items to the left are larger

	static int Median_Of_Three(int* Array, int lowerBound, int upperBound) {

		int middle = (lowerBound + upperBound) / 2;

		if (Array[lowerBound] > Array[middle]) {
			swap(Array[lowerBound], Array[middle]);
		}
		if (Array[middle] > Array[upperBound]) {
			swap(Array[middle], Array[upperBound]);
		}
		if (Array[lowerBound] > Array[middle]) {
			swap(Array[lowerBound], Array[middle]);
		}

		return middle;
	}

	static int Partition(int* Array, int lowerBound, int upperBound) {

		int pivotIndex = Median_Of_Three(Array, lowerBound, upperBound);
		swap(Array[pivotIndex], Array[upperBound]);

		pivotIndex = upperBound;

		int i = lowerBound - 1, j = lowerBound;
		while (j != upperBound) {
			if (Array[j] <= Array[pivotIndex]) {
				i++;
				swap(Array[i], Array[j]);
			}
			j++;
		}

		i++;
		swap(Array[i], Array[pivotIndex]);

		return i;
	}

	static void Sort(int* Array, int lowerBound, int upperBound) {

		if (lowerBound < upperBound) {
			int pivotIndex = Partition(Array, lowerBound, upperBound);

			// +- 1 offset because the pivot element is already sorted
			Sort(Array, lowerBound, pivotIndex - 1);
			Sort(Array, pivotIndex + 1, upperBound);
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


int main() {
	srand(time(0));

	int size = 20;
	int* Array = new int[size];

	for (int i = 0; i < size; i++) {
		Array[i] = rand() % 200 - 100;
	}

	cout << "Array before sorting: ";
	QuickSort::Print(Array, size);

	QuickSort::Sort(Array, 0, size - 1);
	cout << "Sorted array: ";
	QuickSort::Print(Array, size);

	delete[] Array;


	return 0;
}