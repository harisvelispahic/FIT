#include <iostream>
#include <iomanip>
using namespace std;

/*
	Create a dynamic two-dimensional array whose elements are weather objects
	(weather is a structure whose characteristics are given below).
	Allow the user to enter the dimensions of the array.
	
	struct weather
	{
		float *temperature;
		float *airHumidity;
		bool *precipitation;
 		char *precipitationType;	
		float *precipitationAmount;	
	};

	The rows of the two-dimensional array represent the days and the columns the hours of the day.
	Allow the user to enter all data for all hours and days,

1   Create a function that will find and print the day with the highest and the day with the lowest average 
	temperature.
2   Create a function that will calculate the percentage of hours with a temperature higher than 25.5 °C
	and in which there was precipitation in relation to the total number of hours with a temperature higher than 
	25.5 °C.
3   Create a function that will find the hour with the highest temperature during all the entered days.

	In this task, it is forbidden to index array elements with square brackets.
	Must use pointer arithmetic
*/

struct weather
{
	float* temperature;
	float* airHumidity;
	bool* precipitation;
	char* precipitationType;
	float* precipitationAmount;

	weather() {
		temperature = new float{ 0.0f };
		airHumidity = new float{ 0.0f };
		precipitation = new bool{ false };
		precipitationType = new char[30];
		precipitationAmount = new float{ 0.0f };
	}

	~weather() {
		delete temperature;
		delete airHumidity;
		delete precipitationAmount;
		temperature = airHumidity = precipitationAmount = nullptr;
		delete precipitation;
		precipitation = nullptr;
		delete[] precipitationType;
		precipitationType = nullptr;
	}

	void input() {
		cout << "Please enter the temperature: ";
		cin >> *temperature;
		cout << "Please enter the air humidity: ";
		cin >> *airHumidity;
		char tempPrecipitation;
		do {
			cout << "Please enter if there is precipitation [y/n]: ";
			cin >> tempPrecipitation;
		} while (tempPrecipitation != 'y' && tempPrecipitation != 'n'
			&& tempPrecipitation != 'Y' && tempPrecipitation != 'N');
		if (tempPrecipitation == 'y' || tempPrecipitation == 'Y')
			*precipitation = true;
		else if (tempPrecipitation == 'n' || tempPrecipitation == 'N')
			*precipitation = false;
		if (*precipitation) {
			cin.ignore();
			cout << "Please enter precipitation type (e.g rain, snow): ";
			char tempChArr[29];
			cin.getline(tempChArr, size(tempChArr));
			strcpy_s(precipitationType, strlen(tempChArr) + 1, tempChArr);

			cout << "Please enter the precipitation amount: ";
			cin >> *precipitationAmount;
		}
	}

	void print() {
		cout << "The temperature is: " << *temperature << " C" << endl;
		cout << "The air humidity is: " << *airHumidity << " %" << endl;
		cout << "Precipitation: "; 
		(*precipitation) ? cout << "True" << endl : cout << "False" << endl;
		if (*precipitation) {
			cout << "The precipitation type: " << precipitationType << endl;
			cout << "The precipitation amount: " << *precipitationAmount << " mm" << endl;
		}
		cout << endl;
	}
};

// FUNCTIONS DECLARATIONS

weather** createMatrix(int, int);
void enterMatrix(weather**, int, int);
void printMatrix(weather**, int, int);
void deleteMatrix(weather**, int);


//1 Create a function that will find and print the day with the highest and the day with the 
// lowest average temperature.
void printHighestLowestAverageTemperature(weather**, int, int);

//2 Create a function that will calculate the percentage of hours with a temperature higher than 25.5 °C
// and in which there was precipitation in relation to the total number of hours with a temperature higher than 
// 25.5 °C.
void printPrecipitationPercentage(weather**, int, int);

//3	Create a function that will find the hour with the highest temperature during all entered days.
void printHighestAverageTemperatureDay(weather**, int, int);

int main() {

	// The rows of the two-dimensional array represent the days and the columns the hours of the day.
	int days, hours;
	do {
		cout << "Please enter the number of days: ";
		cin >> days;
	} while (days < 1);
	do {
		cout << "Please enter the number of hours per day in which testing occurs: ";
		cin >> hours;
	} while (hours < 1);

	cout << endl; cout << endl;

	weather** weatherForecast = createMatrix(days, hours);

	enterMatrix(weatherForecast, days, hours);
	printMatrix(weatherForecast, days, hours);

	printHighestLowestAverageTemperature(weatherForecast, days, hours);
	printPrecipitationPercentage(weatherForecast, days, hours);
	printHighestAverageTemperatureDay(weatherForecast, days, hours);

	deleteMatrix(weatherForecast, days);

	return 0;
}

//FUNCTIONS DEFINITIONS

weather** createMatrix(int rows, int columns) {
	weather** matrix = new weather * [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new weather[columns];
	}
	return matrix;
}

void enterMatrix(weather** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		cout << "Day: " << i + 1 << endl;
		cout << "-------------------------------------------" << endl;
		for (int j = 0; j < columns; j++) {
			cout << "Hour: " << j + 1 << endl;
			cout << "-------------------------------------------" << endl;
			(*(matrix + i) + j)->input();
			cout << "-------------------------------------------" << endl;
			cout << endl;
		}
	}
}

void printMatrix(weather** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		cout << "Day: " << i + 1 << endl;
		cout << "-------------------------------------------" << endl;
		for (int j = 0; j < columns; j++) {
			cout << "Hour: " << j + 1 << endl;
			cout << "-------------------------------------------" << endl;
			(*(matrix + i) + j)->print();
			cout << "-------------------------------------------" << endl;
			cout << endl;
		}
	}
}

void deleteMatrix(weather** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;
}

void printHighestLowestAverageTemperature(weather** matrix, int rows, int columns) {
	float highestTemperature = INT_MIN, lowestTemperature = INT_MAX;
	int higestDayIndex = 0, lowestDayIndex = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			highestTemperature = max(highestTemperature, *(*(*(matrix + i) + j)).temperature);
			lowestTemperature = min(lowestTemperature, *(*(*(matrix + i) + j)).temperature);
			
			if (highestTemperature == *(*(*(matrix + i) + j)).temperature) {
				higestDayIndex = i;
			}
			if (lowestTemperature == *(*(*(matrix + i) + j)).temperature) {
				lowestDayIndex = i;
			}
		}
	}
	cout << "The day with the highest average temperature is day " << higestDayIndex + 1 << endl;
	cout << "The day with the lowest average temperature is day " << lowestDayIndex + 1 << endl;
}

void printPrecipitationPercentage(weather** matrix, int rows, int columns) {
	int temperatureCounter = 0, temperaturePrecipitationCounter = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (*(*(*(matrix + i) + j)).temperature > 25.5) {
				temperatureCounter++;
				if (*(*(*(matrix + i) + j)).precipitation) {
					temperaturePrecipitationCounter++;
				}
			}
		}
	}
	cout << std::setprecision(4)
		<< "The ratio of days that are hotter than 25.5 C and simulaneously have precipitation is: "
		<< (double(temperaturePrecipitationCounter) / double(temperatureCounter)) * 100 << " %" << endl;
}

void printHighestAverageTemperatureDay(weather** matrix, int rows, int columns) {
	float highestTemperature = 0.0f;
	int dayIndex = 0, hourIndex = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			highestTemperature = max(highestTemperature, *(*(*(matrix + i) + j)).temperature);
			if (highestTemperature == *(*(*(matrix + i) + j)).temperature) {
				dayIndex = i;
				hourIndex = j;
			}
		}
	}
	cout << "Day " << dayIndex + 1 << ", hour " << hourIndex + 1 << " had the highest temperature of " <<
		highestTemperature << endl;
}