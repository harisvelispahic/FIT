#include <iostream>
using namespace std;

template <class T>
struct Node {
    T value;
    Node* next;
    Node* previous;

    Node(T value, Node* next, Node* previous) {
        this->value = value;
        this->next = next;
        this->previous = previous;
    }
};


template <class T>
class DoublyLinkedList {
public:
    Node<T>* Head = nullptr;
    Node<T>* Tail = nullptr;
    int counter = 0;


    bool IsEmpty() {
        return counter == 0;
    }

    void Add(T value) {
        if (counter == 0) {
            Head = new Node<T>(value, nullptr, nullptr);
            Tail = Head;
            counter++;
            return;
        }
        Node<T>* lastNode = Tail;
        lastNode->next = new Node<T>(value, nullptr, lastNode);
        Tail = lastNode->next;

        counter++;
    }

    T Remove() {
        if (IsEmpty())
            throw runtime_error("The list is empty!");
        if (counter == 1) {
            T value = Head->value;
            delete Head;
            Head = Tail = nullptr;
            counter--;
            return value;
        }
        if (counter == 2) {
            T value = Tail->value;
            delete Tail;
            Tail = Head;
            Head->next = nullptr;

            counter--;
            return value;
        }

        T value = Tail->value;
        Node<T>* nextToLastNode = Tail->previous;
        delete Tail;
        Tail = nextToLastNode;
        Tail->next = nullptr;

        counter--;
        return value;
    }

    void InsertAtPosition(T value, int position) {
        if (position < 0 || position > counter)
            throw out_of_range("Position is out of bounds!");
        if (position == counter) {
            Add(value);
        }
        if (position == 0) {
            Node<T>* middleNode = new Node<T>(value, Head, nullptr);
            Head->previous = middleNode;
            Head = middleNode;
            counter++;
            return;
        }
        if (position <= counter / 2) {
            Node<T>* beforeNode = Head;
            for (int i = 0; i < position - 1; i++) {
                beforeNode = beforeNode->next;
            }
            Node<T>* afterNode = beforeNode->next;

            Node<T>* middleNode = new Node<T>(value, afterNode, beforeNode);

            beforeNode->next = middleNode;
            afterNode->previous = middleNode;
        }
        else {
            Node<T>* afterNode = Tail;
            for (int i = 0; i < counter - position - 1; i++) {
                afterNode = afterNode->previous;
            }
            Node<T>* middleNode = new Node<T>(value, afterNode, afterNode->previous);
            afterNode->previous->next = middleNode;
            afterNode->previous = middleNode;
        }

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
            Head->previous = nullptr;

            counter--;
            return value;
        }

        T value;

        if (position <= counter / 2) {
            Node<T>* beforeNode = Head;
            for (int i = 0; i < position - 1; i++) {
                beforeNode = beforeNode->next;
            }
            Node<T>* deleteNode = beforeNode->next;

            beforeNode->next = deleteNode->next;
            deleteNode->next->previous = beforeNode;
            value = deleteNode->value;

            delete deleteNode;
        }
        else {
            Node<T>* deleteNode = Tail;
            for (int i = 0; i < counter - position - 1; i++) {
                deleteNode = deleteNode->previous;
            }
            deleteNode->previous->next = deleteNode->next;
            deleteNode->next->previous = deleteNode->previous;
            value = deleteNode->value;
            delete deleteNode;
        }
        
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

    ~DoublyLinkedList() {
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
void listTester(DoublyLinkedList<T>& list) {
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
    
    cout << "Inserting an element at position 4..." << endl;
    list.InsertAtPosition(1000, 4);
    list.Print();
    cout << endl;

    cout << "Removing an element from position 4..." << endl;
    list.RemoveFromPosition(4);
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

    DoublyLinkedList<int> list;
    listTester(list);

    return 0;
}