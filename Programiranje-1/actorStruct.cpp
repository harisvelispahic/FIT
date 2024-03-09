#include <iostream>
#include <iomanip>
using namespace std;

/*
	The following prototype of the struct Actor is given:

	struct Actor 
	{
	char* name = nullptr;
	char* surname = nullptr;
	char country[40] = "";
	int numberOfMovies = 0;		// number of rows in the dynamic matrix
	int numberOfUsers = 0;		// number of columns in the dynamic matrix
	int** ratings = nullptr;	// matrix with dimensions (numberOfMovies × numberOfUsers)
 
	void input(); // method for allocation and input
	float* getAveragesByUsers();
	void print();
	void deallocation();
	};

	Carry out the implementation of the default functions of the members and, if necessary, define and implement auxiliary ones
	global functions.

	Then, in the main function, add the following things:
	• Creation of an object of type Actor
	• Member function call input (functions that do allocation and console input)
	• Call member function print
	• Retrieve an array of average actor ratings for each user (use dynamic memory)
	• Function call for object deallocation
	• Deallocation of the array of average grades.

	Note: The use of constructors and destructors is not allowed.
*/

struct Actor
{
	char* name = nullptr;
	char* surname = nullptr;
	char country[40] = "";
	int numberOfMovies = 0;		// number of rows in the dynamic matrix
	int numberOfUsers = 0;		// number of columns in the dynamic matrix
	int** ratings = nullptr;	// matrix with dimensions (numberOfMovies × numberOfUsers)

	void input() {				// method for allocation and input
		char temp[40];
		cout << "Please enter the actor's name: ";
		cin.getline(temp, size(temp));
		name = new char[strlen(temp) + 1];
		strcpy_s(name, strlen(temp) + 1, temp);

		cout << "Please enter the actor's surname: ";
		cin.getline(temp, size(temp));
		surname = new char[strlen(temp) + 1];
		strcpy_s(surname, strlen(temp) + 1, temp);

		cout << "Please enter the actor's country of origin: ";
		cin.getline(temp, size(temp));
		strcpy_s(country, strlen(temp) + 1, temp);

		cout << "Please enter the number of movies in which the actor played: ";
		cin >> numberOfMovies;
		cout << "Please enter the number of users the actor is being rated by: ";
		cin >> numberOfUsers;
		cin.ignore(); cout << endl;

		// dynamic memory allocation
		ratings = new int* [numberOfMovies];
		for (int i = 0; i < numberOfMovies; i++) {
			ratings[i] = new int[numberOfUsers];
		}

		// ratings input
		for (int i = 0; i < numberOfMovies; i++) {
			cout << "Please input the ratings for the movie " << i + 1 << ":" << endl;
			cout << "---------------------------------------------" << endl;
			for (int j = 0; j < numberOfUsers; j++) {
				cout << "Please input the rating by the user " << j + 1 << ":" << endl;
				cout << "---------------------------------------------" << endl;
				cin >> ratings[i][j];
				cout << endl;
			}
			cout << endl;
		}
	} 

	void print() {
		cout << "The actor's name: " << name << endl;
		cout << "The actor's surname: " << surname << endl;
		cout << "The actor's country of origin: " << country << endl;
		cout << "The ratings for the actor's movies: " << endl;
		for (int i = 0; i < numberOfMovies; i++) {
			for (int j = 0; j < numberOfUsers; j++) {
				cout << setw(3) << ratings[i][j] << " ";
			}
			cout << endl;
		}
	}

	float* getAveragesByUsers() {
		float* averagesArr = new float[numberOfUsers];
		for (int j = 0; j < numberOfUsers; j++) {
			float averageRating = 0.0f;
			for (int i = 0; i < numberOfMovies; i++) {
				averageRating += ratings[i][j];
			}
			averagesArr[j] = averageRating / numberOfMovies;
		}
		return averagesArr;
	}


	void deallocation() {
		delete name;
		delete surname;
		name = surname = nullptr;
		for (int i = 0; i < numberOfMovies; i++) {
			delete[] ratings[i];
			ratings[i] = nullptr;
		}
		delete[] ratings;
		ratings = nullptr;
	}
};


int main() {

	Actor person;
	person.input();
	system("cls");
	person.print();
	float* averageGrades = person.getAveragesByUsers();
	
	for (int i = 0; i < person.numberOfUsers; i++) {
		cout << "The average grade for user " << i + 1 << " is: " << averageGrades[i] << endl;
	}
	
	// memory deallocation
	delete[] averageGrades;
	averageGrades = nullptr;

	person.deallocation();

	return 0;
}