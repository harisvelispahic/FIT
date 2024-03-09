#include <iostream>
using namespace std;

/*
	The following struct is given:

    struct City 
    {
        char name[20];
        int area_code;
    };

    Write a sortByAreaCode function that receives an array of cities, a size and an area code number.
    It is necessary to rearrange the array so that at the beginning of the array there are cities whose area code is 
    equal to the function parameter, and then come all other array members. 
    Within these two groups (same and different area code number) the order must be unchanged in relation to the received array.

    Write a main function that allows you to enter an array of cities of arbitrary length, then calls the sortByAreaCode function,
    and at the end it prints the rearranged array on the screen.

    Note: It is strictly forbidden to create an auxiliary arrays in the function, and such a solution will be scored with 0 points.
*/

struct City
{
    char name[20];
    int area_code;
    
    void input() {
        cin.ignore();

        cout << "Please enter the name of the city: ";
        char temp[19];
        cin.getline(temp, size(temp));
        strcpy_s(name, strlen(temp) + 1, temp);

        cout << "Please enter the area code: ";
        cin >> area_code;

        cout << endl;
    }

    void print() {
        cout << "The name of the city: " << name << endl;
        cout << "The area code of the city: " << area_code << endl;

        cout << endl;
    }
};

void sortByAreaCode(City* arr, int size, int areaCode) {
    int counter = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i].area_code == areaCode)
            counter++;
    }

    if (counter == 0) {
        cout << "The area code you entered does not exist in the array" << endl;
        cout << endl;
        return;
    }

    counter = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i].area_code == areaCode) {
            City temp = arr[i];
            for (int j = i - 1; j >= counter; j--) {
                arr[j + 1] = arr[j];
            }
            arr[counter] = temp;
            counter++;
        }
    }
}

int main() {

    int size;
    do {
        cout << "Please enter the array size: ";
        cin >> size;
    } while (size < 1);

    cout << endl;

    City* arr = new City[size];

    for (int i = 0; i < size; i++) {
        arr[i].input();
    }

    cout << endl;

    int areaCode;
    cout << "Please enter the area code you want to sort by: ";
    cin >> areaCode;

    cout << endl;

    sortByAreaCode(arr, size, areaCode);

    for (int i = 0; i < size; i++) {
        arr[i].print();
    }

    delete[] arr;
    arr = nullptr;

    return 0;
}