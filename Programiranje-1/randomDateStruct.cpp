#include <iostream>
#include <iomanip>
using namespace std;
/*

    Create a Date structure with three attributes (day, month and year) and then implement the program
    where it is necessary to generate a series of random (random) dates of arbitrary size
    (of the size determined by the user), after which the program will print the latest date entered.

    Use the following function prototype to find the oldest date:
    Date* getNewestDate(Date* d, int size);
   
    Notes: Generated random dates must be valid dates [otherwise repeat generation]
    To check date validity use 'isValid' member function
          Mandatory to deallocate a series of dates at the end of the program.
 */

struct Date {
    int day;
    int month;
    int year;

    void setDay(int d) {
        day = d;
    }
    void setMonth(int m) {
        month = m;
    }
    void setYear(int y) {
        year = y;
    }

    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }

    int getRandomDay() {
        return rand() % 30 + 1;
    }
    int getRandomMonth() {
        return rand() % 11 + 1;
    }
    int getRandomYear() {
        return rand() % 2024 + 1;
    }

    void input() {
        day = getRandomDay();
        month = getRandomMonth();
        year = getRandomYear();
    }

    void output() {
        cout << getDay() << "." << getMonth() << "." << getYear() << endl;
    }

    int getDays() {
        switch (month) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return ((year % 100 != 0 && year % 4 == 0) || (year % 400 == 0)) ? 29 : 28;
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        default:
            cout << "Invalid date!" << endl;
        }
    }

    bool isValid() {
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
            return false;
        return getDays() >= day;
    }

    int toDays() {
        return year * 365 + month * getDays() + day;
    }
};

void enterArray(Date* d, int size) {
    int i = 0;
    do {
        d[i].input();
        if (d[i].isValid())
            i++;
    } while (i < size);
}

void printArray(Date* d, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Date " << i + 1 << ": ";
        d[i].output();
        cout << endl;
    }
}

Date* getNewestDate(Date* d, int size) {
    int newestDate = 0;
    int temp = INT_MIN;
    for (int i = 0; i < size; i++) {
        temp = max(temp, d[i].toDays());
        if (temp == d[i].toDays())
            newestDate = i;
    }
    return d + newestDate;
}


int main() {
    srand(time(0));

    int size;
    do {
        cout << "Enter the number of dates you want to enter: ";
        cin >> size;
    } while (size < 1);

    cout << endl;

    Date* arr = new Date[size];
    enterArray(arr, size);
    printArray(arr, size);

    Date* newestDate = getNewestDate(arr, size);
    cout << "The newest date is: ";
    newestDate->output();


    delete[] arr;
    arr = nullptr;

    return 0;
}