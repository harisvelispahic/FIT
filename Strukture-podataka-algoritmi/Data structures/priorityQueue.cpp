#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct Node {
    T value;
    Node* next;

    Node(T value, Node* next) {
        this->value = value;
        this->next = next;
    }
};

template <class T>
class PriorityQueue {
public:
    virtual bool IsEmpty() = 0;
    virtual void Push(T element) = 0;
    virtual T Pop() = 0;
    virtual void Print() = 0;

    virtual int Count() = 0;
};



template <class T>
class LinkedPriorityQueue : public PriorityQueue<T> {
public:
    Node<T>* Head = nullptr;
    Node<T>* Tail = nullptr;
    int counter = 0;

    int Count() {
        return counter;
    }

    bool IsEmpty() {
        return counter == 0;
    }

    void Push(T value) {

        Node<T>* newNode = new Node<T>(value, nullptr);
        
        if (Head == nullptr) {
            Head = newNode;
            Tail = newNode;
        }

        else if (value > Head->value) {
            newNode->next = Head;
            Head = newNode;
        }

        else {
            Node<T>* currentNode = Head;

            while (currentNode->next != nullptr) {
                if (currentNode->next->value < value) {
                    newNode->next = currentNode->next;
                    currentNode->next = newNode;
                    break;
                }
                currentNode = currentNode->next;
            }
            if (currentNode->next == nullptr) {
                currentNode->next = newNode;
            }
        }

        counter++;
    }

    T Pop() {
        if (IsEmpty())
            throw runtime_error("The queue is empty!");

        T value = Head->value;

        Node<T>* deleteNode = Head;
        Head = Head->next;

        delete deleteNode;
        counter--;

        return value;
    }

    void Print() {
        cout << "Number of elements: " << counter << ":\t\t";
        Node<T>* currentNode = Head;
        while (currentNode != nullptr) {
            cout << currentNode->value << ", ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }

    ~LinkedPriorityQueue() {
        Node<T>* deleteNode = Head;
        while (deleteNode != nullptr) {
            Node<T>* nextNode = deleteNode->next;
            delete deleteNode;
            deleteNode = nextNode;
        }

        cout << "<-- LINKED LIST DESTRUCTOR -->" << endl;
    }
};

template <class T>
class ArrayPriorityQueue : public PriorityQueue<T> {
public:
    int max = 5;
    T* Array = new T[max];
    int counter = 0;

    int Count() {
        return counter;
    }

    bool IsEmpty() {
        return counter == 0;
    }

    void expand() {
        T* newArray = new T[max * 2];

        for (int i = 0; i < counter; i++) {
            newArray[i] = Array[i];
        }
        
        max = max * 2;
        delete[] Array;
        Array = newArray;
    }

    void Push(T element) {
        if (counter == max)
            expand();

        Array[counter++] = element;
    }

    T Pop() {
        if (IsEmpty())
            throw runtime_error("The queue is empty!");

        int maxElement = 0;
        int maxIndex = 0;

        for (int i = 0; i < counter; i++) {
            maxElement = std::max(maxElement, Array[i]);

            if (maxElement == Array[i])
                maxIndex = i;
        }

        T value = Array[maxIndex];
        Array[maxIndex] = Array[--counter];
        
        return value;
    }

    void Print() {
        cout << "Number of elements: " << counter << "\t\t";
        for (int i = 0; i < counter; i++) {
            cout << Array[i];
            (i < counter - 1) ? cout << ", " : cout << " "
                ;
        }
        cout << endl;
    }

    ~ArrayPriorityQueue() {
        delete[] Array;
        cout << "<-- SEQUENCE LIST DESTRUCTOR -->" << endl;
    }
};

template <class T>
class HeapPriorityQueue : public PriorityQueue<T> {
public:
    int max = 7;
    int counter = 0;
    T* Array = new T[max];

    int Count() {
        return counter;
    }

    bool IsEmpty() {
        return counter == 0;
    }

    void expand() {
        max = max * 2 + 1;
        T* newArray = new T[max];

        for (int i = 0; i < counter; i++) {
            newArray[i] = Array[i];
        }

        delete[] Array;
        Array = newArray;
    }
    
    void bubbleDown(int n, int root) {

        int largest = root;
        int leftChild = root * 2 + 1;
        int rightChild = root * 2 + 2;

        if (leftChild < n && Array[leftChild] > Array[largest]) {
            largest = leftChild;
        }

        if (rightChild < n && Array[rightChild] > Array[largest]) {
            largest = rightChild;
        }

        if (largest != root) {
            swap(Array[largest], Array[root]);
            bubbleDown(n, largest);
        }
    }

    void bubbleUp(int childIndex) {

        if (childIndex == 0)
            return;

        int parentIndex = (childIndex - 1) / 2;
        if (Array[childIndex] > Array[parentIndex]) {
            swap(Array[childIndex], Array[parentIndex]);
            bubbleUp(parentIndex);
        }
    }

    void Push(T element) {
        if (counter == max)
            expand();

        Array[counter] = element;
        bubbleUp(counter++);
    }

    T Pop() {
        if (IsEmpty())
            throw exception("Priority queue is empty!");

        T value = Array[0];
        swap(Array[0], Array[--counter]);
        bubbleDown(counter, 0);

        return value;
    }

    void Print() {
        int oldNewLine = 1;
        int newLine = 1;
        cout << "\n";
        for (int i = 0; i < counter; i++) {
            if (newLine == 2 * oldNewLine) {
                oldNewLine *= 2;
                cout << "\n";
            }
            cout << Array[i] << " ";
            newLine++;
        }
        cout << endl;
    }
    
    ~HeapPriorityQueue() {
        delete[] Array;
        Array = nullptr;
    }
};


template <class T>
void queueTester(PriorityQueue<T>& queue) {
    cout << "Starting Priority Queue Test...\n";

    // 1. Test popping from an empty queue
    cout << "Trying to pop from an empty queue..." << endl;
    try {
        queue.Pop();
    }
    catch (const std::exception& err) {
        cout << "Caught exception: " << err.what() << endl;
    }
    cout << endl;

    // 2. Test pushing elements into the queue
    cout << "Pushing elements into the queue: 5, 10, 20, 15, 30" << endl;
    vector<T> elements = { 5, 10, 20, 15, 30 };
    for (const T& el : elements) {
        queue.Push(el);
        cout << "Pushed: " << el << " | Current state: ";
        queue.Print();
    }
    cout << endl;

    // 3. Test popping elements in order of priority
    cout << "Popping all elements (in order of priority):" << endl;
    while (!queue.IsEmpty()) {
        cout << "Popped: " << queue.Pop() << " | Current state: ";
        queue.Print();
    }
    cout << endl;

    // 4. Test adding elements after clearing the queue
    cout << "Adding elements again: 100, 50, 200, 25" << endl;
    vector<T> newElements = { 100, 50, 200, 25 };
    for (const T& el : newElements) {
        queue.Push(el);
        cout << "Pushed: " << el << " | Current state: ";
        queue.Print();
    }
    cout << endl;

    // 5. Test handling edge cases: Pop all except one
    cout << "Popping all elements except the last one:" << endl;
    while (queue.Count() > 1) { // `counter` tracks the number of elements
        cout << "Popped: " << queue.Pop() << " | Current state: ";
        queue.Print();
    }
    cout << endl;

    // 6. Verify the last element
    cout << "The last remaining element is: " << queue.Pop() << endl;
    cout << "Queue should now be empty: ";
    queue.Print();
    cout << endl;

    // 7. Stress test: Push a large number of elements
    cout << "Stress testing with 20 elements..." << endl;
    for (int i = 1; i <= 20; ++i) {
        queue.Push(i * 3);
    }
    queue.Print();

    // Popping half of the elements
    cout << "Popping 10 elements..." << endl;
    for (int i = 0; i < 10; ++i) {
        cout << "Popped: " << queue.Pop() << " | Current state: ";
        queue.Print();
    }

    cout << "Queue testing complete!\n\n";
}

int main() {

    LinkedPriorityQueue<int> linkedPriorityQueue;
    queueTester(linkedPriorityQueue);

    ArrayPriorityQueue<int> ArrayPriorityQueue;
    queueTester(ArrayPriorityQueue);

    HeapPriorityQueue<int> HeapPriorityQueue;
    queueTester(HeapPriorityQueue);

    return 0;
}