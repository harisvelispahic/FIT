#include <iostream>
using namespace std;

/*
	The following structure is given:

    struct Car
    {
        char* name;                 // character array
        char* model;                // character array
        char* type;                 // character array
        int* productionYear;        // in range 2005 - 2022
        float* consumption100km;
    };

    Create a two-dimensional dynamic array whose elements are Car objects.
    Allow the user to enter array dimensions. 
    
    Create following function:
    · Function to input car features - some function receives a pointer to a car.
        It is mandatory to automate the entry so that random values are entered in all numerical characteristics.
        The task will not be considered correct if this is not done.
    · Function for printing a complete 2D sequence with all the characteristics of all cars,
    · Assume that the rows represent the companies and the columns represent the cars in the company.
    · Find the index of the company with the lowest average car consumption.


    In this task, it is forbidden to index array elements with square brackets.
    Must use pointer arithmetic
*/

struct Car
{
    char* name;                 // character array
    char* model;                // character array
    char* type;                 // character array
    int* productionYear;        // in range 2005 - 2022
    float* consumption100km;

    Car() {
        name = new char[30] {""};
        model = new char[30] {""};
        type = new char[30] {""};
        productionYear = new int{ 0 };
        consumption100km = new float{ 0.0f };
    }

    ~Car() {
        delete name;
        delete model;
        delete type;
        name = model = type = nullptr;
        delete productionYear;
        productionYear = nullptr;
        delete consumption100km;
        consumption100km = nullptr;
    }

    void print() {
        cout << "The car's  name: " << name << endl;
        cout << "The car's model: " << model << endl;
        cout << "The car's  type: " << type << endl;
        cout << "The car's production year: " << *productionYear << endl;
        cout << "The car's fuel consumption per 100km: " << *consumption100km << endl;
    }
};

/*
        Function to input car features - some function receives a pointer to a car.
        It is mandatory to automate the entry so that random values are entered in all numerical characteristics.
        The task will not be considered correct if this is not done.
*/

void input(Car* c) {
    char temp[29];
    cout << "Please enter the car's  name: ";
    cin.getline(temp, size(temp));
    strcpy_s(c->name, strlen(temp) + 1, temp);

    cout << "Please enter the car's model: ";
    cin.getline(temp, size(temp));
    strcpy_s(c->model, strlen(temp) + 1, temp);

    cout << "Please enter the car's  type: ";
    cin.getline(temp, size(temp));
    strcpy_s(c->type, strlen(temp) + 1, temp);

    *c->productionYear = rand() % (2022 - 2005 + 1) + 2005;
    *c->consumption100km = float(rand() % (150 - 40 + 1) + 40) / 10;
}

void printMatrix(Car** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        cout << "Company " << i + 1 << ": " << endl;
        cout << "--------------------------------------------------" << endl;
        for (int j = 0; j < columns; j++) {
            cout << "Car " << j + 1 << ": " << endl;
            cout << "--------------------------------------------------" << endl;
            (*(matrix + i) + j)->print();
            cout << endl;
        }
    }
}

int main() {
    srand(time(0));
    
    // Assume that the rows represent the companies and the columns represent the cars in the company.
    
    int companies, cars;
    do {
        cout << "Please enter the number of companies: ";
        cin >> companies;
    } while (companies < 1);
    do {
        cout << "Please enter the number of cars: ";
        cin >> cars;
    } while (cars < 1);

    cin.ignore(); cout << endl; cout << endl;

    // dynamic memory allocation
    Car** industry = new Car * [companies];
    for (int i = 0; i < companies; i++) {
        industry[i] = new Car[cars];
    }

    
    // enter matrix
    for (int i = 0; i < companies; i++) {
        cout << "Company " << i + 1 << ": " << endl;
        cout << "--------------------------------------------------" << endl;
        for (int j = 0; j < cars; j++) {
            cout << "Car " << j + 1 << ": " << endl;
            cout << "--------------------------------------------------" << endl;
            input((*(industry + i) + j));
            cout << endl;
        }
    }

    system("cls");

    printMatrix(industry, companies, cars);

    // Find the index of the company with the lowest average car consumption.
    int companyIndex = 0;
    float lowestFuelConsumption = INT_MAX;
    for (int i = 0; i < companies; i++) {
        float sumConsumption = 0.0f;
        for (int j = 0; j < cars; j++) {
            sumConsumption += *(*(industry + i) + j)->consumption100km;
        }
        lowestFuelConsumption = min(lowestFuelConsumption, sumConsumption);             // not taking average because the number of cars per company is equal
        if (lowestFuelConsumption == sumConsumption) {
            companyIndex = i;
        }
    }
    cout << "The company with the lowest average fuel consumption is company " << companyIndex + 1 << endl;

    // dynamic memory deallocation
    for (int i = 0; i < companies; i++) {
        delete[] industry[i];
        industry[i] = nullptr;
    }
    delete[] industry;
    industry = nullptr;

    return 0;
}