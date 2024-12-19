#include <iostream>
using namespace std;

enum Operation {
	Add,
	Subtract
};

struct Node {
    int value;
    Node* next;

    Node(int value, Node* next) {
        this->value = value;
        this->next = next;
    }
};

class LinkedList {
	int counter = 0;
	Node* HEAD = nullptr;
	Node* TAIL = nullptr;
public:

	bool IsEmpty() {
		return counter == 0;
	}

	void Add(int element) {
		Node* newNode = new Node(element, nullptr);

		if (counter == 0) {
			HEAD = newNode;
			TAIL = newNode;
			counter++;
			return;
		}

		TAIL->next = newNode;
		TAIL = newNode;
		counter++;
	}

	int Remove() {
		if (IsEmpty())
			throw exception("List is empty!");

		int value = HEAD->value;
		HEAD = HEAD->next;
		counter--;

		return value;
	}
};


class BucketSort {
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
		int max = maxMin.first;
		int min = maxMin.second;

		// Add the offset to every element, assuming there will not be an overflow
		OFFSET = abs(min);
		ApplyOffset(Array, size, Add);

		// update maxElement with the offset
		max += OFFSET;

	    int numberOfDigits = log10(max) + 1;
	
        LinkedList buckets[10];

	    for (int i = 0; i < numberOfDigits; i++) {
            for (int j = 0; j < size; j++) {
                int digit = Array[j] / pow(10, i);
                digit %= 10;
                buckets[digit].Add(Array[j]);
            }

            int counter = 0;
            for (int j = 0; j < std::size(buckets); j++) {
                while (!buckets[j].IsEmpty()) {
                    Array[counter++] = buckets[j].Remove();
                }
            }
	    }

		ApplyOffset(Array, size, Subtract);
    }

    static void Print(int* Array, int size) {
        for (int i = 0; i < size; i++) {
            cout << Array[i] << " ";
        }
        cout << endl;
    }
};

int BucketSort::OFFSET = 0;


int main() {
    
    srand(time(0));

	int size = 20;
    int* Array = new int[size];

    for (int i = 0; i < size; i++) {
        Array[i] = rand() % 200 - 100;
    }
    
    cout << "Array before sorting: ";
    BucketSort::Print(Array, size);

    cout << "Sorted array: ";
    BucketSort::Sort(Array, size);
    BucketSort::Print(Array, size);
    

	delete[] Array;

	return 0;
}