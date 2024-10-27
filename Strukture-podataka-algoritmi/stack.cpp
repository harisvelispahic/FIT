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
class Stack {
public:
    virtual bool IsEmpty() = 0;
    virtual void Push(T element) = 0;
    virtual T Pop() = 0;
    virtual void Print() = 0;
};



template <class T>
class LinkedStack : public Stack<T> {
public:
    Node<T>* Head = nullptr;
    int counter = 0;


    bool IsEmpty() {
        return counter == 0;
    }

    void Push(T element) {
        Head = new Node<T>(element, Head);
        counter++;
    }

    T Pop() {
        if (IsEmpty())
            throw runtime_error("The stack is empty!");

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

    ~LinkedStack() {
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
class ArrayStack : public Stack<T> {
public:
    int counter = 0;
    int max = 100;
    T* Array = new T[max];

    bool IsEmpty() {
        return counter == 0;
    }

    void expand() {
        max = max + max / 2;
        T* newArray = new T[max];

        for (int i = 0; i < counter; i++) {
            newArray[i] = Array[i];
        }

        delete[] Array;
        Array = newArray;
    }

    void Push(T element) {
        if (counter >= max)
            expand();
        Array[counter++] = element;
    }

    T Pop() {
        if (IsEmpty())
            throw runtime_error("The stack is empty!");
        T value = Array[counter - 1];
        counter--;

        return value;
    }

    void Print() {
        cout << "Number of elements: " << counter << ":\t\t";
        for (int i = 0; i < counter; i++) {
            cout << Array[i] << ", ";
        }
        cout << endl;
    }

    ~ArrayStack() {
        delete[] Array;
        cout << "<-- SEQUENCE LIST DESTRUCTOR -->" << endl;
    }
};


template <class T>
void stackTester(Stack<T>& stack) {
    cout << "Trying to pop a non-existent element..." << endl;
    try {
        cout << stack.Pop() << endl;
    }
    catch (const std::exception& err) {
        cout << err.what() << endl;
    }
    cout << endl;

    cout << "Pushing an element..." << endl;
    stack.Push(1);
    stack.Print();
    cout << endl;

    cout << "Popping an element..." << endl;
    stack.Pop();
    stack.Print();
    cout << endl;

    cout << "Pushing 5 elements..." << endl;
    for (int i = 1; i <= 5; i++) {
        stack.Push(i * 10);
        stack.Print();
    }

    cout << endl;

    cout << "Removing an element..." << endl;
    stack.Pop();
    stack.Print();
    cout << endl;

    cout << "Removing 3 elements..." << endl;
    stack.Pop();
    stack.Print();
    stack.Pop();
    stack.Print();
    int nextToLastPopped = stack.Pop();
    stack.Print();
    cout << endl;

    cout << "Next to last popped element: " << nextToLastPopped << endl << endl;

    cout << "Popping an element..." << endl;
    int lastPopped = stack.Pop();
    cout << "Last popped element: " << lastPopped << endl;
    stack.Print();
    cout << endl;

    cout << "Testing destructor..." << endl;
    stack.Push(1);
    stack.Push(10);
    stack.Push(100);
    stack.Push(1000);
    stack.Push(10000);

    for (int i = 0; i < 10000000; i++) {
        stack.Push(rand() % 10 + 1);
    }
}

int main() {

    LinkedStack<int> linkedStack;
    stackTester(linkedStack);

    ArrayStack<int> ArrayStack;
    stackTester(ArrayStack);

    return 0;
}