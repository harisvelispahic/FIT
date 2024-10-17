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
class List {
public:
    virtual bool IsEmpty() = 0;
    virtual void Add(T element) = 0;
    virtual void InsertAtPosition(T value, int position) = 0;
    virtual T Remove() = 0;
    virtual T RemoveFromPosition(int position) = 0;
    virtual void Print() = 0;
};

template <class T>
class LinkedList : public List<T> {
public:
    Node<T>* Head = nullptr;
    Node<T>* Tail = nullptr;
    int counter = 0;


    bool IsEmpty() {
        return counter == 0;
    }

    Node<T>* getLastNode() {
        Node<T>* currentNode = Head;
        while (currentNode->next != nullptr) {
            currentNode = (*currentNode).next;
        }
        return currentNode;
    }

    void Add(T element) {
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

    T Remove() {
        if (IsEmpty())
            throw runtime_error("The list is empty!");
        if (counter == 1) {
            T value = Head->value;
            delete Head;
            Head = nullptr;
            counter--;
            return value;
        }

        Node<T>* nextToLastNode = Head;
        for (int i = 0; i < counter - 2; i++) {
            nextToLastNode = nextToLastNode->next;
        }

        Node<T>* lastNode = nextToLastNode->next;
        T value = lastNode->value;

        delete lastNode;
        nextToLastNode->next = nullptr;

        counter--;
        return value;
    }

    void InsertAtPosition(T value, int position) {
        if (position < 0 || position > counter)
            throw out_of_range("Position is out of bounds!");
        if (position == 0) {
            Node<T>* middleNode = new Node<T>(value, Head);
            Head = middleNode;
            counter++;
            return;
        }
        Node<T>* beforeNode = Head;
        for (int i = 0; i < position - 1; i++) {
            beforeNode = beforeNode->next;
        }
        Node<T>* afterNode = beforeNode->next;

        Node<T>* middleNode = new Node<T>(value, afterNode);

        beforeNode->next = middleNode;

        counter++;
    }

    T RemoveFromPosition(int position) {
        if (IsEmpty())
            throw runtime_error("The list is empty!");
        if (position < 0 || position >= counter)
            throw out_of_range("Position is out of bounds!");
        if (position == counter - 1) {
            return Remove();
        }
        if (position == 0) {
            Node<T>* deleteNode = Head;
            T value = deleteNode->value;

            Head = Head->next;
            delete deleteNode;

            counter--;
            return value;
        }

        Node<T>* beforeNode = Head;
        for (int i = 0; i < position - 1; i++) {
            beforeNode = beforeNode->next;
        }
        Node<T>* deleteElement = beforeNode->next;

        beforeNode->next = deleteElement->next;
        T value = deleteElement->value;

        delete deleteElement;
        counter--;

        return value;
    }

    void Print() {
        cout << "Number of elements: " << counter << ":\t\t";
        Node<T>* currentNode = Head;
        while (currentNode != nullptr) {
            cout << (*currentNode).value << ", ";
            currentNode = (*currentNode).next;
        }
        cout << endl;
    }

    ~LinkedList() {
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
class ArrayList : public List<T> {
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

    void Add(T element) {
        if (counter >= max)
            expand();
        Array[counter++] = element;
    }

    void InsertAtPosition(T value, int position) {
        if (position < 0 || position > counter)
            throw out_of_range("Position is out of bounds!");
        if (counter >= max)
            expand();
        for (int i = counter; i > position; i--) {
            Array[i] = Array[i - 1];
        }
        Array[position] = value;
        counter++;
    }

    T Remove() {
        if (IsEmpty())
            throw runtime_error("The list is empty!");
        T value = Array[counter - 1];
        counter--;

        return value;
    }

    T RemoveFromPosition(int position) {
        if (position < 0 || position >= counter)
            throw out_of_range("Position is out of bounds!");

        T value = Array[position];

        for (int i = position; i < counter - 1; i++) {
            Array[i] = Array[i + 1];
        }

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

    ~ArrayList() {
        delete[] Array;
        cout << "<-- SEQUENCE LIST DESTRUCTOR -->" << endl;
    }
};


template <class T>
void listTester(List<T>& list) {
    cout << "Trying to remove a non-existent element..." << endl;
    try {
        cout << list.Remove() << endl;
    }
    catch (const std::exception& err) {
        cout << err.what() << endl;
    }
    cout << endl;

    cout << "Adding an element..." << endl;
    list.Add(1);
    list.Print();
    cout << endl;

    cout << "Removing an element..." << endl;
    list.Remove();
    list.Print();
    cout << endl;

    cout << "Adding 5 elements..." << endl;
    list.Add(10);
    list.Add(20);
    list.Add(30);
    list.Add(40);
    list.Add(50);
    list.Print();
    cout << endl;

    cout << "Removing an element..." << endl;
    list.Remove();
    list.Print();
    cout << endl;

    cout << "Trying to insert an element at position 500..." << endl;
    try {
        list.InsertAtPosition(100, 500);
    }
    catch (const std::exception& err) {
        cout << err.what() << endl;
    }
    cout << endl;

    cout << "Inserting an element at position 2..." << endl;
    list.InsertAtPosition(100, 2);
    list.Print();
    cout << endl;

    cout << "Inserting an element at position 0..." << endl;
    list.InsertAtPosition(500, 0);
    list.Print();
    cout << endl;

    cout << "Trying to remove an element from position 100..." << endl;
    try {
        list.RemoveFromPosition(100);
    }
    catch (const std::exception& err) {
        cout << err.what() << endl;
    }
    cout << endl;

    cout << "Removing an element from position 5..." << endl;
    list.RemoveFromPosition(5);
    list.Print();
    cout << endl;

    cout << "Removing 3 elements..." << endl;
    list.Remove();
    list.Remove();
    int nextToLastRemoved = list.Remove();
    list.Print();
    cout << endl;

    cout << "Next to last removed element: " << nextToLastRemoved << endl << endl;

    cout << "Removing an element..." << endl;
    list.RemoveFromPosition(1);
    list.Print();
    cout << endl;

    cout << "Removing an element..." << endl;
    int lastRemoved = list.Remove();
    cout << "Last removed element: " << lastRemoved << endl;
    list.Print();
    cout << endl;

    cout << "Testing destructor..." << endl;
    list.Add(1);
    list.Add(10);
    list.Add(100);
    list.Add(1000);
    list.Add(10000);

    for (int i = 0; i < 10000000; i++) {
        list.Add(rand() % 10 + 1);
    }
}

int main() {

    LinkedList<int> linkList;
    listTester(linkList);

    ArrayList<int> ArrayList;
    listTester(ArrayList);

    return 0;
}