#include <iostream>
using namespace std;

enum Operation {
	Add,
	Subtract
};

class CountingSort {

public:

	static int OFFSET;


	static pair<int, int> GetMaxMin(int* Array, int size) {
		int max = INT_MIN, min = INT_MAX;
		for (int i = 0; i < size; i++) {
			max = std::max(max, Array[i]);
			min = std::min(min, Array[i]);
		}
		return make_pair(max, min);
	}

	static void ApplyOffset(int* Array, int size, Operation operation) {
		if (operation == Add) {
			for (int i = 0; i < size; i++) {
				Array[i] += OFFSET;
			}
		}
		else {
			for (int i = 0; i < size; i++) {
				Array[i] -= OFFSET;
			}
		}
	}

	static void Sort(int* Array, int size) {
		pair<int, int> maxMin = GetMaxMin(Array, size);
		int maxElement = maxMin.first;
		int minElement = maxMin.second;

		// Add the offset to every element, assuming there will not be an overflow
		OFFSET = abs(minElement);
		ApplyOffset(Array, size, Add);

		// update maxElement with the offset
		maxElement += OFFSET;

		int* countingArray = new int[maxElement + 1] {0};

		for (int i = 0; i < size; i++) {
			countingArray[Array[i]]++;
		}

		int counter = 0;
		for (int i = 0; i <= maxElement; i++) {
			while (countingArray[i] > 0) {
				Array[counter++] = i;
				countingArray[i]--;
			}
		}

		ApplyOffset(Array, size, Subtract);

		delete[] countingArray;
	}

	static void Print(int* Array, int size) {
		for (int i = 0; i < size; i++) {
			cout << Array[i];
			cout << ((i < size - 1) ? ", " : " ");
		}
		cout << endl;
	}
};

int CountingSort::OFFSET = 0;


int main() {
	srand(time(0));

	int size = 10;
	int* Array = new int[size];

	for (int i = 0; i < size; i++) {
		Array[i] = rand() % 200 - 100;
	}

	CountingSort::Print(Array, size);

	CountingSort::Sort(Array, size);

	CountingSort::Print(Array, size);
	
	delete[] Array;

	return 0;
}