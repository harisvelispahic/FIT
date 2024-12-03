#include <iostream>
#include <vector>
using namespace std;

// MAX-HEAP is implemented


void bubbleDown(vector<int>& elements, int root) {
	int largest = root;
	int leftChild = root * 2 + 1;
	int rightChild = root * 2 + 2;

	// leftChild < elements.size()	-	leftChild actually exists, since the tree can be complete but not full
	if (leftChild < elements.size() && elements[leftChild] > elements[largest]) {
		largest = leftChild;
	}

	// elements[largest] is checked and not elements[root], because if the first condition is true and elements[rightChild] > elements[root], elements[rightChild] might also be greater than elements[leftChild] and that information is lost
	if (rightChild < elements.size() && elements[rightChild] > elements[largest]) {
		largest = rightChild;
	}

	// if after both checks the largest element doesn't happen to be in the root, we need to swap these two elements and propagate the bubbleDown method deeper in the tree
	if (largest != root) {
		swap(elements[largest], elements[root]);
		// propagate the bubbleDown recursively down the path where the values of the largest and root were swapped, so that it can find it's place deeper in the corresponding branch
		bubbleDown(elements, largest);
	}
}

void heapify(vector<int>& elements) {

	for (int i = elements.size() / 2 - 1; i >= 0; i--) {
		bubbleDown(elements, i);
	}
}

void Print(vector<int> elements) {
	int oldNewLine = 1;
	int newLine = 1;
	for (int i = 0; i < elements.size(); i++) {
		if (newLine == 2 * oldNewLine) {
			oldNewLine *= 2;
			cout << "\n";
		}
		cout << elements[i] << " ";
		newLine++;
	}
	cout << endl << endl;
}

int main() {

	vector<int> numbers;

	for (int i = 1; i <= 31; i++) {
		numbers.push_back(i);
	}

	Print(numbers);

	//bubbleDown(arr, n, 2);
	heapify(numbers);

	Print(numbers);


	return 0;
}