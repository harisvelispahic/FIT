#include <iostream>
#include <iomanip>
using namespace std;

/*
	Create a dynamic two-dimensional array whose elements are objects of type weather_forecast
    (a forecast is a structure whose characteristics are given below).
    Allow the user to enter the dimensions of the array.

    struct weather_forecast
    {
         char* precipation;      // allow word entry "rain" or "snow"
        float* temperature;
        float* air_humidity;
    };

    The rows of the two-dimensional array represent different meteorologists, and the columns represent different days.
    Allow the user to enter all forecasts for all meteorologists.

    Additionally, create a one-dimensional dynamic array whose size will be the entered number of days
    in which you will enable the input of actual measured values for days.

    Create a function that will find and print the meteorologist's index
    whose daily temperature forecast was the most accurate, i.e. which had the smallest error
    in estimating temperatures.
    
    Help: sum of all differences between forecast and actual temperature for one meteorologist
    represents its total error.
*/

struct weather_forecast {

    char* precipation;      // allow word entry "rain" or "snow"
    float* temperature;
    float* air_humidity;

    weather_forecast() {
        precipation = new char[30];
        temperature = new float;
        air_humidity = new float;
    }

    ~weather_forecast() {
        delete[] precipation;
        delete temperature;
        delete air_humidity;
        precipation = nullptr;
        temperature = air_humidity = nullptr;
    }

};

weather_forecast** createMatrix(int rows, int columns) {
    weather_forecast** matrix = new weather_forecast * [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new weather_forecast[columns];
    }
    return matrix;
}

void enterWeatherMatrix(weather_forecast** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
            cout << i + 1 << ". Meteorologist: " << endl;
        for (int j = 0; j < columns; j++) {
            
            cout << "Day " << j + 1 << ":" << endl;

            char temp[30];
            do {
                cout << "Please enter the precipation: ";
                cin >> temp;
                strcpy_s(matrix[i][j].precipation, strlen(temp) + 1, temp);     // strlen(temp) + 1 -> ____ + '\0'
                cin.clear();
            } while (strcmp("rain", matrix[i][j].precipation) && strcmp("snow", matrix[i][j].precipation));
            matrix[i][j].precipation[strlen(temp)] = '\0';

            cout << "Please enter the temperature: ";
            cin >> *matrix[i][j].temperature;
            cin.clear();

            do {
                cout << "Please enter the air humidity: ";
                cin >> *matrix[i][j].air_humidity;
                cin.clear();
            } while (*matrix[i][j].air_humidity < 0 || *matrix[i][j].air_humidity > 100);

            cout << endl;
            system("cls");
        }
    }
}

void printWeatherMatrix(weather_forecast** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
            cout << i + 1 << ". Meteorologist: " << endl;
        for (int j = 0; j < columns; j++) {
            cout << "Day " << j + 1 << ":" << endl;

            cout << "Day " << j + 1 << " precipation: " << matrix[i][j].precipation << endl;
            cout << "Day " << j + 1 << " temperature: " << *matrix[i][j].temperature << endl;
            cout << "Day " << j + 1 << " air humidity: " << *matrix[i][j].air_humidity << " %" << endl;
            cout << endl;
        }
    }
}

int getMostAccurateMeteorologist(weather_forecast** matrix, weather_forecast* arr, int rows, int columns) {
    /*
        Create a function that will find and print the meteorologist's index
        whose daily temperature forecast was the most accurate, i.e. which had the smallest error
        in estimating temperatures.
    
        Help: sum of all differences between forecast and actual temperature for one meteorologist
        represents its total error.
    */
    int meteorologistIndex = 0;
    float mistake = INT_MAX;
    for (int i = 0; i < rows; i++) {
        float diff = 0;
        for (int j = 0; j < columns; j++) {
            diff += abs(*matrix[i][j].temperature - *arr[j].temperature);
        }
        mistake = min(mistake, diff);
        if (mistake == diff) {
            meteorologistIndex = i;
        }
    }
    return meteorologistIndex + 1;
}

void deleteMatrix(weather_forecast** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}

void enterWeatherArray(weather_forecast* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Day " << i + 1 << endl;


        char temp[30];
        do {
            cout << "Please enter the precipation: ";
            cin >> temp;
            strcpy_s(arr[i].precipation, strlen(temp) + 1, temp);     // strlen(temp) + 1 -> ____ + '\0'
            cin.clear();
        } while (strcmp("rain", arr[i].precipation) && strcmp("snow", arr[i].precipation));
        arr[i].precipation[strlen(temp)] = '\0';

        cout << "Please enter the temperature: ";
        cin >> *arr[i].temperature;
        cin.clear();

        do {
            cout << "Please enter the air humidity: ";
            cin >> *arr[i].air_humidity;
            cin.clear();
        } while (*arr[i].air_humidity < 0 || *arr[i].air_humidity > 100);

        cout << endl;
        system("cls");
    }
}

void printWeatherArray(weather_forecast* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Day " << i + 1 << ":" << endl;
                          
        cout << "Day " << i + 1 << " precipation: " << arr[i].precipation << endl;
        cout << "Day " << i + 1 << " temperature: " << *arr[i].temperature << endl;
        cout << "Day " << i + 1 << " air humidity: " << *arr[i].air_humidity << " %" << endl;
        cout << endl;
    }
}


int main() {
    
    int meteorologists,     // rows
        days;               // columns

    do {
        cout << "Enter the number of meteorologists: ";
        cin >> meteorologists;
        cin.clear();
    } while (meteorologists < 1);
    
    do {
        cout << "Enter the number of days: ";
        cin >> days;
        cin.clear();
    } while (days < 1);

    weather_forecast** weatherMatrix = createMatrix(meteorologists, days);
    cout << endl; cout << endl;

/*  Additionally, create a one-dimensional dynamic array whose size will be the entered number of days
     in which you will enable the input of actual measured values for days  */

    weather_forecast* actualWeatherArr = new weather_forecast[days];

    cout << "Please enter the weather forecast for each meteorologist: " << endl;
    enterWeatherMatrix(weatherMatrix, meteorologists, days);
    cout << "Please enter the actual weather conditions: " << endl;
    enterWeatherArray(actualWeatherArr, days);

    cout << "The weather forecast according to the meteorologists: " << endl;
    printWeatherMatrix(weatherMatrix, meteorologists, days);
    cout << endl;
    cout << "The actual weather conditions: " << endl;
    printWeatherArray(actualWeatherArr, days);

    cout << endl; cout << endl;

    cout << "The most accurate meteorologist is meteorologist number " <<
        getMostAccurateMeteorologist(weatherMatrix, actualWeatherArr, meteorologists, days) << endl;

    deleteMatrix(weatherMatrix, meteorologists);
    delete[] actualWeatherArr;
    actualWeatherArr = nullptr;

    return 0;
}