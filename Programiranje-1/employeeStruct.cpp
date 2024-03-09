#include <iostream>
using namespace std;

/*
	Create a dynamic two-dimensional array whose elements are employee type objects
    (an employee is a structure whose characteristics are given).
    Allow the user to enter the dimensions of the array.

    struct employee
    {
         char *ID;
         char *fullName;
         float *salary;
    };

    The rows of the two-dimensional array represent different departments of the company 
    where different workers work
    (for the sake of simplicity, assume that each department has the same number of workers).

1   Enable the user to enter all data for all employees, and
2   create a function that will find the highest average salary by department of the company and
3   print out the serial number of the department (index of the row with the highest average)
4   and what is the highest average salary.

*/

char* createTextFrom(const char*);

struct employee
{
    char* ID;
    char* fullName;
    float* salary;

    employee() {
        ID = new char[10];
        fullName = new char[30];
        salary = new float(0.0f);
    }

    ~employee() {
        delete ID;
        delete fullName;
        ID = fullName = nullptr;
        delete salary;
        salary = nullptr;
    }

    void setID();
    void setFullName();
    void setSalary();
    
    char* getID();
    char* getFullName();
    float getSalary();

    void input();
    void output();
};

employee** createMatrix(int, int);
void enterMatrix(employee**, int, int);
void printMatrix(employee**, int, int);
void deleteMatrix(employee**, int);

void getHighestSalaryAverage(employee**, int, int);


int main() {
    
    // Rows of the two-dimensional array represent different departments of the company
    // where different workers work
    // (for the sake of simplicity, assume that each department has the same number of workers).

    int numberOfDepartments = 0, numberOfEmployees = 0;
    do
    {
        cout << "Please enter the number of departments: ";
        cin >> numberOfDepartments;
    } while (numberOfDepartments < 1);
    
    do
    {
        cout << "Please enter the number of employees: ";
        cin >> numberOfEmployees;
    } while (numberOfEmployees < 1);

    cout << endl; cout << endl;

    employee** company = createMatrix(numberOfDepartments, numberOfEmployees);

    enterMatrix(company, numberOfDepartments, numberOfEmployees);
    printMatrix(company, numberOfDepartments, numberOfEmployees);
    getHighestSalaryAverage(company, numberOfDepartments, numberOfEmployees);

    deleteMatrix(company, numberOfDepartments);

    return 0;
}

// TEXT FUNCTION

char* createTextFrom(const char* source) {
    int size = strlen(source) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, source);
    return temp;
}

// EMPLOYEE METHODS
void employee::setID() {
    char temp[10];
    cin.ignore();
    cin.getline(temp, size(temp));
    ID = createTextFrom(temp);
}
void employee::setFullName() {
    char temp[30];
    cin.getline(temp, size(temp));
    fullName = createTextFrom(temp);
}
void employee::setSalary() {
    float s;
    cin >> s;
    *salary = s;
    cin.ignore();
}

char* employee::getID() {
    return ID;
}
char* employee::getFullName() {
    return fullName;
}
float employee::getSalary() {
    return *salary;
}

void employee::input() {
    cout << "------------------------------------------" << endl;
    cout << "Please input the ID of the employee: ";
    setID();
    cout << "Please input the full name of the employee: ";
    setFullName();
    cout << "Please input the salary of the employee: ";
    setSalary();
    cout << endl;
}

void employee::output() {
    cout << "------------------------------------------" << endl;
    cout << "The ID of the employee: " << getID() << endl;
    cout << "The full name of the employee: " << getFullName() << endl;
    cout << "The salary of the employee: " << getSalary() << endl;
    cout << endl;
}

// MATRIX FUNCTIONS

employee** createMatrix(int rows, int columns) {
    employee** matrix = new employee * [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new employee[columns];
    }
    return matrix;
}

void enterMatrix(employee** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        cout << "Department [" << i + 1 << "]: " << endl;
        cout << endl;
        for (int j = 0; j < columns; j++) {
            cout << "Employee [" << j + 1 << "]: " << endl;
            matrix[i][j].input();
        }
        cout << endl;
        system("cls");
    }
}

void printMatrix(employee** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        cout << "Department [" << i + 1 << "]: " << endl;
        cout << endl;
        for (int j = 0; j < columns; j++) {
            cout << "Employee [" << j + 1 << "]: " << endl;
            matrix[i][j].output();
        }
        cout << endl;
    }
}

void deleteMatrix(employee** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}

/*
    Create a function that will find the highest average salary by department of the company and
    print out the serial number of the department (index of the row with the highest average)
    and what is the highest average salary.
*/

void getHighestSalaryAverage(employee** matrix, int rows, int columns) {
    int highestSalaryDepartment = 0;
    float highestSalaryAverage = 0.0f;
    for (int i = 0; i < rows; i++) {
        float sumOfSalaries = 0.0f;
        for (int j = 0; j < columns; j++) {
            sumOfSalaries += matrix[i][j].getSalary();
        }
        highestSalaryAverage = max(highestSalaryAverage, sumOfSalaries);
        if (highestSalaryAverage == sumOfSalaries) {
            highestSalaryDepartment = i;
        }
    }

    cout << "The department with the highest average salaries is department [" << highestSalaryDepartment + 1
        << "]" << endl;
    cout << "The average salary in this department is " << highestSalaryAverage / columns << " $" << endl;
}