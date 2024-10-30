#include <iostream>
#include <queue>
#include <chrono>

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
    }
};

template <class T>
class ArrayQueue : public Queue<T> {
public:
    int max = 100;
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
    }
};


template <class T>
pair<double, double> queueTester(Queue<T>& queue, int iterations) {
    double resultPush = 0.0;
    double resultPop = 0.0;

    for (int i = 0; i < 10; i++)
    {
        auto startPush = chrono::high_resolution_clock::now();
        
        for (int j = 0; j < iterations; j++) 
        {
            queue.Push(j);
        }
        auto endPush = chrono::high_resolution_clock::now();

        chrono::duration<double> durationPush = endPush - startPush;

        resultPush += durationPush.count();
    }

    
    for (int i = 0; i < 10; i++)
    {
        auto startPop = chrono::high_resolution_clock::now();

        for (int j = 0; j < iterations; j++)
        {
            queue.Pop();
        }
        auto endPop = chrono::high_resolution_clock::now();

        chrono::duration<double> durationPop = endPop - startPop;

        resultPop += durationPop.count();
    }

    return make_pair(resultPush / 10, resultPop / 10);
}

template <class T>
pair<double, double> queueTester(queue<T> queue, int iterations) {
    double resultPush = 0.0;
    double resultPop = 0.0;

    for (int i = 0; i < 10; i++)
    {
        auto startPush = chrono::high_resolution_clock::now();

        for (int j = 0; j < iterations; j++)
        {
            queue.push(j);
        }
        auto endPush = chrono::high_resolution_clock::now();

        chrono::duration<double> durationPush = endPush - startPush;

        resultPush += durationPush.count();
    }


    for (int i = 0; i < 10; i++)
    {
        auto startPop = chrono::high_resolution_clock::now();

        for (int j = 0; j < iterations; j++)
        {
            queue.pop();
        }
        auto endPop = chrono::high_resolution_clock::now();

        chrono::duration<double> durationPop = endPop - startPop;

        resultPop += durationPop.count();
    }

    return make_pair(resultPush / 10, resultPop / 10);
}


const char* divider = "-------------------------------------------------------------------------------------------------";

int main() {

    int iterations = 1000000;

    queue<int> queue;
    pair<double, double> queueResult = queueTester(queue, iterations);
    
    cout << divider << "\n C++ QUEUE -> \t\tAverage push time: " << queueResult.first << "s\t\t Average pop time: " << queueResult.second << "s" << "\n" << divider << endl;

    LinkedQueue<int> linkedQueue;
    pair<double, double> linkedQueueResult = queueTester(linkedQueue, iterations);


    cout << divider << "\n LINKED QUEUE -> \tAverage push time: " << linkedQueueResult.first << "s\t\t Average pop time: " << linkedQueueResult.second << "s" << "\n" << divider << endl;

    ArrayQueue<int> arrayQueue;
    pair<double, double> arrayQueueResult = queueTester(arrayQueue, iterations);


    cout << divider << "\n ARRAY QUEUE -> \tAverage push time: " << arrayQueueResult.first << "s\t\t Average pop time: " << arrayQueueResult.second << "s" << "\n" << divider << endl;

    cout << "\n\nResults were calculated by repeating " << iterations << " iterations, 10 times, and taking the average of that.\n\n";

    return 0;
}