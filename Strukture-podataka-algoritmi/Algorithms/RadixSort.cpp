#include <iostream>
using namespace std;


enum Operation {
	Add,
	Subtract
};


class RadixSort {

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

	static void AcummulateArray(int* Array, int size) {
		for (int i = 1; i < size; i++) {
			Array[i] += Array[i - 1];
		}
	}

	static void Sort(int*& Array, int size) {
		pair<int, int> maxMin = GetMaxMin(Array, size);
		int maxElement = maxMin.first;
		int minElement = maxMin.second;

		// Add the offset to every element, assuming there will not be an overflow
		OFFSET = abs(minElement);
		ApplyOffset(Array, size, Add);

		// update maxElement with the offset
		maxElement += OFFSET;

		int digits = log10(maxElement) + 1;

		for (int i = 0; i < digits; i++) {
			int countingArray[10]{ 0 };

			for (int j = 0; j < size; j++) {
				int significantDigit = (Array[j] / (int)pow(10, i)) % 10;

				countingArray[significantDigit]++;
			}

			AcummulateArray(countingArray, 10);

			int* tempArray = new int[size] {0};

			for (int j = size - 1; j >= 0; j--) {
				int significantDigit = (Array[j] / (int)pow(10, i)) % 10;

				tempArray[--countingArray[significantDigit]] = Array[j];
			}

			int* deletePtr = Array;
			Array = tempArray;
			delete[] deletePtr;
		}

		ApplyOffset(Array, size, Subtract);
	}

	static void Print(int* Array, int size) {
		for (int i = 0; i < size; i++) {
			cout << Array[i];
			cout << ((i < size - 1) ? ", " : " ");
		}
		cout << endl;
	}
};


int RadixSort::OFFSET = 0;


int main() {

	srand(time(0));

	int size = 10;
	int* Array = new int[size];

	for (int i = 0; i < size; i++) {
		Array[i] = rand() % 200 - 100;
	}

	RadixSort::Print(Array, size);

	RadixSort::Sort(Array, size);

	RadixSort::Print(Array, size);

	delete[] Array;

	return 0;
}