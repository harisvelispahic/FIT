#include <iostream>
#include <vector>
using namespace std;

class MergeSort {
public:

	static void Sort(int* Array, int size) {
		// Base case - since merge sort splits arrays up until they're 1-sized, the base case exits when it finds that array size is 1
		if (size <= 1)
			return;

		// Variables for splitting the arrays in two (un)equal halves
		int middle = size / 2;
		
		int leftSize = middle;
		int rightSize = size - leftSize;

		// Declaring two new arrays
		int* leftArray = new int[leftSize];
		int* rightArray = new int[rightSize];

		// Copying the array into two half-sized arrays - because of this merge sort is heavy on memory since it uses additional memory
		int counter = 0;
		for (int i = 0; i < leftSize; i++) {
			leftArray[i] = Array[counter++];
		}
		for (int i = 0; i < rightSize; i++) {
			rightArray[i] = Array[counter++];
		}

		// This part is the actual sorting part
		// We can think of this like traversing a binary tree in PreOrder (root - left - right)
		// When it comes down to the most left node, base case is activated and it goes one step back with left child "in mind"
		// Then it accesses the right child, also activating base case and goes to their parent
		// And then the Merge method is called, and it combines them into one Array which is placed into the parent's place
		// Then, as the PreOrder traversal goes, it visits the next left-most leaf and repeats this process until all leaves are gone
		// After that the process is repeated until it sorts the whole Array, using the 2-Way-Merge
		
		Sort(leftArray, leftSize);
		Sort(rightArray, rightSize);
		Merge(Array, size, leftArray, leftSize, rightArray, rightSize);

		// After the merge is complete, we can safely deallocate this memory, since it has been merged into their parent 
		// and we are sure that it will never again be accessed/needed

		delete[] leftArray;
		delete[] rightArray;
	}

	static void Merge(int* Array, int Array_Size, int* A, int A_Size, int* B, int B_Size) {

		int i = 0, j = 0;

		int counter = 0;
		while (i < A_Size && j < B_Size) {
			if (A[i] <= B[j]) {
				Array[counter++] = A[i];
				i++;
			}
			else {
				Array[counter++] = B[j];
				j++;
			}
		}

		while (i < A_Size) {
			Array[counter++] = A[i];
			i++;
		}
		while (j < B_Size) {
			Array[counter++] = B[j];
			j++;
		}		
	}

};

void Print(int* Array, int size) {
	for (int i = 0; i < size; i++) {
		cout << Array[i];
		cout << ((i < size - 1) ? ", " : "\n");
	}
}

int main() {
	
	int StaticArray[] = { 2,3,45,6,2,4,67,8,3,0,-125,-25,-15,-4,2,5,7,2,6 };
	MergeSort::Sort(StaticArray, size(StaticArray));
	Print(StaticArray, size(StaticArray));


	int* DynamicArray = new int[20];
	for (int i = 0; i < 20; i++) {
		DynamicArray[i] = rand() % 40 - 20;
	}

	MergeSort::Sort(DynamicArray, 20);
	Print(DynamicArray, 20);
	
	return 0;
}