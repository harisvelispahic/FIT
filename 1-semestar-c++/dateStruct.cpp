#include <iostream>
#include <iomanip>
using namespace std;
/*
   
    Create a Date structure with three attributes (day, month and year) and then implement the program
    where it is necessary to enter a series of dates of arbitrary size (size determined by the user),
    after which the program will print the oldest date entered.

    Use the following function prototype to find the oldest date:
    Date* getOldestDate(Date* d, int size);

    Notes: Dates entered must be valid dates [otherwise re-enter]
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

    void input() {
        cout << "-----------------------------" << endl;
        cout << "Please enter the day: " << endl;
        cin >> day;
        cout << "Please enter the month: " << endl;
        cin >> month;
        cout << "Please enter the year: " << endl;
        cin >> year;
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
    do
    {
        cout << "Enter the " << i + 1 << ". date:" << endl;
        d[i].input();
        if (d[i].isValid())
            i++;
        cout << endl;
    } while (i < size);
    cout << endl;
}


Date* getOldestDate(Date* d, int size) {
    int oldestDate = 0;
    int temp = INT_MAX;
    for (int i = 0; i < size; i++) {
        temp = min(temp, d[i].toDays());
        if (temp == d[i].toDays())
            oldestDate = i;
    }
    return d + oldestDate;
}


int main() {
    
    int size;
    do {
        cout << "Enter the number of dates you want to enter: ";
        cin >> size;
    } while (size < 1);

    cout << endl;
    
    Date* arr = new Date[size];
    enterArray(arr, size);

    Date* oldestDate = getOldestDate(arr, size);
    cout << "The oldest date is: ";
        oldestDate->output();


    delete[] arr;
    arr = nullptr;

    return 0;
}