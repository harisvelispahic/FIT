#include <iostream>
#include <iomanip>
using namespace std;

/*
	Create a dynamic two-dimensional array whose elements are vehicle-type objects
    (a vehicle is a structure whose characteristics are given below).
    Allow the user to enter the dimensions of the array.

    struct vehicle
    {
         char* vehicleBrand;
        char* vin;
        char* vehicleType; // allow input of "A", "B", or "C" values only
        double* engineVolume;
    };

    The rows of the two-dimensional array represent different companies, and the columns represent different vehicles in those companies.
    (for the sake of simplicity, assume that each company has the same number of vehicles).
    Allow the user to enter all data for all vehicles.

    Write and test a function that will find (the company) that has the largest average cubic capacity of vehicles
    (average value of engineVolume).

    Then write and test a function that will find and print the average cubic capacity of the vehicle
    (average value of engineVolume) of all vehicles of type "A" and especially of all vehicles of type "B" in the entire matrix.

    (In this task, it is forbidden to index array elements with square brackets.
    Must use pointer arithmetic.)
*/


struct vehicle {

    char* vehicleBrand;
    char* vin;
    char* vehicleType; // allow input of "A", "B", or "C" values only
    double* engineVolume;

    vehicle() {
        vehicleBrand = new char[20];
        vin = new char[20];
        vehicleType = new char[2];
        engineVolume = new double;
    }

    ~vehicle() {
        delete vehicleBrand;
        delete vin;
        delete vehicleType;
        delete engineVolume;
        vehicleBrand = vin = vehicleType = nullptr;
        engineVolume = nullptr;
    }
};

vehicle** createMatrix(int rows, int columns) {
    vehicle** matrix = new vehicle * [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new vehicle[columns];
    }
    return matrix;
}


void fillMatrix(vehicle** matrix, int rows, int columns) {
    double engineVolumesArray[] = { 1.2, 1.4, 1.6, 1.9, 2.0, 2.5, 3.0, 4.0, 4.2, 5.0, 5.2 };

    cout << "Please enter the vehicle characteristics: " << endl;
    cout << endl; cout << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << "Vehicle " << i * rows + j + 1 << ": " << endl;
            *(*(*(matrix + i) + j)).engineVolume = engineVolumesArray[rand() % 11];

            char* temp = new char;
            do {
                cout << "Enter the vehicle type: ";
                cin >> *temp;
                *(*(*(matrix + i) + j)).vehicleType = *temp;
                cin.clear();
            } while (*temp != 'A' && *temp != 'B' && *temp != 'C');
            (*(*(matrix + i) + j)).vehicleType[1] = '\0';

            cout << "Enter the vehicle brand: ";
            cin >> (*(*(matrix + i) + j)).vehicleBrand;
            cin.clear();
            cout << "Enter the VIN: ";
            cin >> (*(*(matrix + i) + j)).vin;
            cin.clear();

            cout << endl; cout << endl;
        }
    }
}

void printMatrix(vehicle** matrix, int rows, int columns) {
    cout << "The vehicles: " << endl;
    cout << endl; cout << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << "Vehicle " << i * rows + j + 1 << ": " << endl;
            cout << endl;
            cout << "Vehicle type: " << (*(*(matrix + i) + j)).vehicleType << endl;
            cout << "Vehicle brand: " << (*(*(matrix + i) + j)).vehicleBrand << endl;
            cout << "Vehicle engine volume: " << *(*(*(matrix + i) + j)).engineVolume << endl;
            cout << "Vehicle VIN: " << (*(*(matrix + i) + j)).vin << endl;
            
            cout << endl; cout << endl;
        }
    }
}

void deleteMatrix(vehicle** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}

//Write and test a function that will find(the company) that has the largest average cubic capacity of vehicles
//(average value of engineVolume).

int highestAverageEngineVolume(vehicle** matrix, int rows, int columns) {
    double maxVolume = INT_MIN, company = 0;
    for (int i = 0; i < rows; i++) {
        double sum = 0;
        for (int j = 0; j < columns; j++) {
            sum += *(*(*(matrix + i) + j)).engineVolume;
        }
        maxVolume = max(maxVolume, sum);
        if (sum == maxVolume) {
            company = i;
        }
    }
    return company;
}

//Then write and test a function that will find and print the average cubic capacity of the vehicle
//(average value of engineVolume) of all vehicles of type "A" and especially of all vehicles of type "B" in the entire matrix.

double averageEngineVolumeA(vehicle** matrix, int rows, int columns) {
    double sum = 0;
    int counter = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (*(*(*(matrix + i) + j)).vehicleType == 'A') {
                sum += *(*(*(matrix + i) + j)).engineVolume;
                counter++;
            }
        }
    }
    return sum / counter;
}

double averageEngineVolumeB(vehicle** matrix, int rows, int columns) {
    double sum = 0;
    int counter = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (*(*(*(matrix + i) + j)).vehicleType == 'B') {
                sum += *(*(*(matrix + i) + j)).engineVolume;
                counter++;
            }
        }
    }
    return sum / counter;
}

double averageEngineVolumeC(vehicle** matrix, int rows, int columns) {
    double sum = 0;
    int counter = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (*(*(*(matrix + i) + j)).vehicleType == 'C') {
                sum += *(*(*(matrix + i) + j)).engineVolume;
                counter++;
            }
        }
    }
    return sum / counter;
}

int main() {
    
    int numberOfCompanies, numberOfVehicles;
    do {
        cout << "Please enter the number of companies: ";
        cin >> numberOfCompanies;
        cin.clear();
    } while (numberOfCompanies < 1);

    do {
        cout << "Please enter the number of vehicles: ";
        cin >> numberOfVehicles;
        cin.clear();
    } while (numberOfVehicles < 1);

    cout << endl; cout << endl;

    vehicle** matrix = createMatrix(numberOfCompanies, numberOfVehicles);

    fillMatrix(matrix, numberOfCompanies, numberOfVehicles);
    printMatrix(matrix, numberOfCompanies, numberOfVehicles);

    cout << endl; cout << endl;
    
    cout << "The company with the highest average engine volume is company " <<
        highestAverageEngineVolume(matrix, numberOfCompanies, numberOfVehicles) + 1 << endl;

    cout << endl;

    cout << "The average engine volume for cars that are of type 'A' is: " <<
        averageEngineVolumeA(matrix, numberOfCompanies, numberOfVehicles) << endl;
    cout << "The average engine volume for cars that are of type 'B' is: " <<
        averageEngineVolumeB(matrix, numberOfCompanies, numberOfVehicles) << endl;
    cout << "The average engine volume for cars that are of type 'C' is: " <<
        averageEngineVolumeC(matrix, numberOfCompanies, numberOfVehicles) << endl;

    deleteMatrix(matrix, numberOfCompanies);

    return 0;
}
