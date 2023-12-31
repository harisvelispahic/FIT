#include <iostream>
#include <iomanip>
using namespace std;

/*
    Write a program that will allow the user to enter the size of a one-dimensional dynamic array
    integer values. Write a recursive function that will fill that string with random numbers in the range from 
    1 to 100. To generate random numbers, use rand() % 100 + 1.
    Filling the array is stopped when the entire array is filled or when the same random number is obtained 
    three times in a row.

    In this task, it is forbidden to index array elements with square brackets.
    Must use pointer arithmetic.
    It is mandatory to solve everything with one recursive function.
    */

void output(int arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++) {

        if (*(arr + i) <= 0)
            break;

        cout << setw(5) << *(arr + i);
        if ((i + 1) % 5 == 0)
            cout << endl;
    }
}

void fillRandomArray(int arr[], int arrSize, int i = 0) {
    int n = rand() % 100 + 1;
    if (i >= arrSize || i < 0) {
        return;
    }

    *(arr + i) = n;

    if (i >= 2) {
        if (n == *(arr + i - 1) && n == *(arr + i - 2)) {
            return;
        }
    }

    fillRandomArray(arr, arrSize, i + 1);
}

int main() {
    srand(time(NULL));

    int arrSize = 100;
    do {
        cin >> arrSize;
    } while (arrSize <= 0);

    int* arr = new int[arrSize]();

    fillRandomArray(arr, arrSize);
    output(arr, arrSize);

    delete[] arr;

    return 0;
}
