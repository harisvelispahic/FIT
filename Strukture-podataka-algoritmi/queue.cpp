#include <iostream>
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
class Queue {
public:
    virtual bool IsEmpty() = 0;
    virtual void Push(T element) = 0;
    virtual T Pop() = 0;
    virtual void Print() = 0;
};



template <class T>
class LinkedQueue : public Queue<T> {
public:
    Node<T>* Head = nullptr;
    Node<T>* Tail = nullptr;
    int counter = 0;


    bool IsEmpty() {
        return counter == 0;
    }

    void Push(T element) {
        if (counter == 0) {
            Head = new Node<T>(element, nullptr);
            Tail = Head;
            counter++;
            return;
        }
        Node<T>* lastNode = Tail;
        lastNode->next = new Node<T>(element, nullptr);
        Tail = lastNode->next;

        counter++;
    }

    T Pop() {
        if (IsEmpty())
            throw runtime_error("The queue is empty!");

        T value = Head->value;
        Node<T>* temp = Head;
        Head = Head->next;
        delete temp;
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

    ~LinkedQueue() {
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
class ArrayQueue : public Queue<T> {
public:
    int max = 5;            // small number for testing sake, it could be, for example, max = 100 in the beginning
    T* Array = new T[max];
    int counter = 0;
    int start = 0;
    int end = 0;

    bool IsEmpty() {
        return counter == 0;
    }

    void expand() {
        T* newArray = new T[max * 2];

        int innerCounter = 0;
        if (start < end) {
            for (int i = start; i < end; i++) {
                newArray[innerCounter++] = Array[i];
            }
        }
        else {
            for (int i = start; i < max; i++) {
                newArray[innerCounter++] = Array[i];
            }
            for (int i = 0; i < end; i++) {
                newArray[innerCounter++] = Array[i];
            }
        }

        max = max * 2;
        delete[] Array;
        Array = newArray;
    }

    void Push(T element) {
        if (counter == max)
            expand();

        if (end == max) {
            end = 0;
        }
        Array[end++] = element;

        counter++;
    }

    T Pop() {
        if (IsEmpty())
            throw runtime_error("The queue is empty!");

        T value = Array[start++];

        if (start == max)
            start = 0;
            
        counter--;

        //if (start == end && start != 0)     // reset to 0 for understanding simplicity sake
            //start = end = 0;
        
        return value;
    }

    void Print() {
        cout << "Number of elements: " << counter << "\t\t";
        if (start == end)
            return;
        
        if (start < end) {
            for (int i = start; i < end; i++) {
                cout << Array[i] << ", ";
            }
        }
        else {
            for (int i = start; i < max; i++) {
                cout << Array[i] << ", ";
            }
            for (int i = 0; i < end; i++) {
                cout << Array[i] << ", ";
            }
        }
        cout << endl;
    }

    ~ArrayQueue() {
        delete[] Array;
        cout << "<-- SEQUENCE LIST DESTRUCTOR -->" << endl;
    }
};


template <class T>
void queueTester(Queue<T>& queue) {
    cout << "Trying to pop a non-existent element..." << endl;
    try {
        cout << queue.Pop() << endl;
    }
    catch (const std::exception& err) {
        cout << err.what() << endl;
    }
    cout << endl;

    cout << "Pushing an element..." << endl;
    queue.Push(1);
    queue.Print();
    cout << endl;

    cout << "Popping an element..." << endl;
    queue.Pop();
    queue.Print();
    cout << endl;

    cout << "Pushing 5 elements..." << endl;
    for (int i = 1; i <= 5; i++) {
        queue.Push(i * 10);
        queue.Print();
    }

    cout << endl;

    cout << "Removing an element..." << endl;
    queue.Pop();
    queue.Print();
    cout << endl;

    cout << "Removing 3 elements..." << endl;
    queue.Pop();
    queue.Print();
    queue.Pop();
    queue.Print();
    int nextToLastPopped = queue.Pop();
    queue.Print();
    cout << endl;

    cout << "Next to last popped element: " << nextToLastPopped << endl << endl;

    cout << "Popping an element..." << endl;
    int lastPopped = queue.Pop();
    cout << "Last popped element: " << lastPopped << endl;
    queue.Print();
    cout << endl;

    cout << "Pushing 5 elements..." << endl;
    queue.Push(1);
    queue.Push(10);
    queue.Push(100);
    queue.Push(1000);
    queue.Push(10000);
    queue.Print();
    
    cout << "Popping an element..." << endl;
    queue.Pop();
    queue.Print();

    cout << "Pushing an element..." << endl;
    queue.Push(15);
    queue.Print();

    cout << "Popping 3 elements..." << endl;
    queue.Pop();
    queue.Print();
    queue.Pop();
    queue.Print();
    queue.Pop();
    queue.Print();

    cout << "Pushing 10 elements (testing expand method)..." << endl;
    for (int i = 1; i <= 10; i++) {
        queue.Push(i * 5);
    }
    queue.Print();

    cout << "Popping an element: " << endl;
    cout << "The element: " << queue.Pop() << endl;
    queue.Print();

    cout << "\n\n--------------------------------------------------------------\n";

    for (int i = 0; i < 10000000; i++) {
        queue.Push(rand() % 10 + 1);
    }
}

int main() {

    LinkedQueue<int> linkedQueue;
    queueTester(linkedQueue);

    ArrayQueue<int> ArrayQueue;
    queueTester(ArrayQueue);

    return 0;
}