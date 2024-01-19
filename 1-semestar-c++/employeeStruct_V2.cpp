#include <iostream>
using namespace std;

/*
	Create a two-dimensional dynamic array whose elements are employee type objects
	(an employee is a structure whose characteristics are given below).
	
	struct uposlenik
	{
		int ID;
		char* fullName;
		char* type;		//allow only letters D, Q, A (developer, quality assurance and architect)
		float* salary;
	};

	Allow the user to enter the dimensions of the array and allow the entry of elements.
	The rows of the series represent different IT companies, and the columns represent different employees.
	For the sake of simplicity, assume that each company has the same number of employees.

	Depending on the entered type (D, Q or A), it is identified which employee performs which duty in the 
	company.
	Different companies may have different numbers of developers, quality assurance or architects.
	(For example, company 1 can have 10 developers, 3 quality assurance and 5 architects,
	while another company may have 12 developers, 2 quality assurance and 6 architects, etc.)

	Calculate and print average salaries in companies by type of employee.
	Then allow the user to choose one type of employee (D, Q or A) and
	according to the user's choice, find the company that has the best average salary for that type of employee.
	(e.g. if the letter D is entered for company 1, the average for 10 developers is calculated
	while for company 2, the average of 12 developers is calculated and these averages are compared).

	In this task, it is forbidden to index array elements with square brackets.
	Must use pointer arithmetic.
	Be sure to take care of deallocating dynamically allocated memory.
*/

char getValidJobType(char c) {
	do {
		cout << "Please enter the job type (D, Q, A): ";
		cin >> c;
	} while (c != 'D' && c != 'Q' && c != 'A'
		&& c != 'd' && c != 'q' && c != 'a');
	return c;
}

struct Employee
{
	int ID;
	char* fullName;
	char* type;		//allow only letters D, Q, A (developer, quality assurance i architect)
	float* salary;

	Employee() {
		ID = rand() % 100 + 1;
		fullName = new char[30];
		type = new char{ '/' };
		salary = new float{ 0.0f };
	}

	~Employee() {
		delete[] fullName;
		fullName = nullptr;
		delete type;
		type = nullptr;
		delete salary;
		salary = nullptr;
	}

	void input() {
		cin.ignore();
		cout << "Please enter the full name: ";
		char tempArr[29];
		cin.getline(tempArr, size(tempArr));
		strcpy_s(fullName, strlen(tempArr) + 1, tempArr);

		char tempCh = '/';
		*type = getValidJobType(tempCh);

		cout << "Please enter the salary: ";
		cin >> *salary;
	}

	void print() {
		cout << "Employee's ID: " << ID << endl;
		cout << "Employee's full name: " << fullName << endl;
		cout << "Employee's job type: " << *type << endl;
		cout << "Employee's salary: " << *salary << endl;
	}
};


int main() {

	int companies, employees;
	
	do {
		cout << "Please enter the number of companies: ";
		cin >> companies;
	} while (companies < 1);

	do {
		cout << "Please enter the number of employees: ";
		cin >> employees;
	} while (employees < 1);

	cout << endl; cout << endl;

	// dynamic allocation
	Employee** matrix = new Employee * [companies];
	for (int i = 0; i < companies; i++) {
		matrix[i] = new Employee[employees];
	}

	// enter matrix
	for (int i = 0; i < companies; i++) {
		cout << "Company " << i + 1 << endl;
		cout << "--------------------------------------------------" << endl;
		for (int j = 0; j < employees; j++) {
			cout << "Employee " << j + 1 << endl;
			cout << "--------------------------------------------------" << endl;
			(*(matrix + i) + j)->input();
			cout << endl;
		}
	}
	system("cls");

	// print matrix
	for (int i = 0; i < companies; i++) {
		cout << "Company " << i + 1 << endl;
		cout << "--------------------------------------------------" << endl;
		for (int j = 0; j < employees; j++) {
			cout << "Employee " << j + 1 << endl;
			cout << "--------------------------------------------------" << endl;
			(*(matrix + i) + j)->print();
			cout << endl;
		}
	}


/*
	Calculate and print average salaries in companies by type of employee.

	Then allow the user to choose one type of employee (D, Q or A) and
	according to the user's choice, find the company that has the best average salary for that type of employee.
	(e.g. if the letter D is entered for company 1, the average for 10 developers is calculated
	while for company 2, the average of 12 developers is calculated and these averages are compared).
*/

	for (int i = 0; i < companies; i++) {
		int dCounter = 0, aCounter = 0, qCounter = 0;
		float dSalary = 0.0f, aSalary = 0.0f, qSalary = 0.0f;
		for (int j = 0; j < employees; j++) {

			switch (*(*(matrix + i) + j)->type) {
			case 'D':case'd':
				dCounter++;
				dSalary += *(*(matrix + i) + j)->salary;
				break;
			case 'A':case'a':
				aCounter++;
				aSalary += *(*(matrix + i) + j)->salary;
				break;
			case 'Q':case'q':
				qCounter++;
				qSalary += *(*(matrix + i) + j)->salary;
				break;
			}
		}
		(dCounter > 0) ? cout << "The average salary for a developer in company " << i + 1 << " is: "
			<< dSalary / dCounter << endl : cout << "There are no developers in company " << i + 1 << endl;
		(qCounter > 0) ? cout << "The average salary for a quality assurance engineer in company " << i + 1 << " is: "
			<< qSalary / qCounter << endl : cout << "There are no quality assurance engineers in company " << i + 1 << endl;
		(aCounter > 0) ? cout << "The average salary for an architect in company " << i + 1 << " is: "
			<< aSalary / aCounter << endl : cout << "There are no architects in company " << i + 1 << endl;
		
		cout << endl;
	}
	cout << endl;

	char choice = '/';
	choice = getValidJobType(choice);

	int bestCompanyIndex = 0;
	bool employeeExists = true;
	int totalCounter = 0;
	float maxSalary = INT_MIN;

	for (int i = 0; i < companies && employeeExists; i++) {
	int choiceCounter = 0;
	float choiceSalary = 0.0f;
	float avgSalary = 0.0f;

		for (int j = 0; j < employees; j++) {
			if (*(*(matrix + i) + j)->type == choice) {
				choiceSalary += *(*(matrix + i) + j)->salary;
				choiceCounter++;
				totalCounter++;
			}
		}
		avgSalary = choiceSalary / choiceCounter;
		if (choiceCounter == 0) {
			break;
		}
		else {
			if (avgSalary > maxSalary) {
				maxSalary = avgSalary;
				bestCompanyIndex = i;
			}
		}
	}

	employeeExists = bool(totalCounter);

	if (employeeExists) {
		cout << "The company where ";
		if (choice == 'A' || choice == 'a')
			cout << "architects";
		else if (choice == 'D' || choice == 'd')
			cout << "developers";
		else if (choice == 'Q' || choice == 'q')
			cout << "quality assurance engineers";
	
		cout << " have the highest average salary is company: " << bestCompanyIndex + 1 << endl;
	}
	else {
		cout << "No such employee exists in any company!" << endl;
	}

	// dynamic deallocation
	for (int i = 0; i < companies; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;

	return 0;
}