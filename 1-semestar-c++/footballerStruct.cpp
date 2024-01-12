#include <iostream>
using namespace std;

/*
	Create a dynamic two-dimensional array whose elements are objects of type footballer
    (footballer is a structure whose characteristics are given below).
    Allow the user to enter the dimensions of the array.

    struct footballer
    {
        int* yearOfBirth;
        int* playerID;
        int* goals;
    };

   The rows of the two-dimensional array represent the different teams, and the columns represent the players on those teams.

  Allow the user to enter all data for all players, and create (and test in the main function)
  function that will find the team with the highest average.

  Then create (and test in the main function) a function that will find the player with the most goals in the team with
  with the worst goal average.

  For the sake of easier testing of the program, it is mandatory to enable 
  the data entry function to generate the data as follows:

    yearOfBirth: 1980 + rand() % ((2000 + 1) - 1980) // Generates random numbers in the interval 1980 - 2000
    playerID: rand() % 30 + 1
    goals: rand() % 5

    In this task, it is forbidden to index array elements with square brackets. Must use pointer arithmetic.    
*/

struct footballer {
    int* yearOfBirth;
    int* playerID;
    int* goals;

    footballer() {
        yearOfBirth = new int;
        playerID = new int;
        goals = new int;
    }

    ~footballer() {
        delete yearOfBirth;
        delete playerID;
        delete goals;
        yearOfBirth = playerID = goals = nullptr;
    }
};

void footballInput(footballer** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            *matrix[i][j].yearOfBirth = 1980 + rand() % ((2000 + 1) - 1980);
            *matrix[i][j].playerID = rand() % 30 + 1;
            *matrix[i][j].goals = rand() % 5;
        }
    }
}

void printHighestGoalAverage(footballer** matrix, int rows, int columns) {
    int team = 0, maxGoals = 0;
    for (int i = 0; i < rows; i++) {
        int goals = 0;
        for (int j = 0; j < columns; j++) {
            goals += *(matrix[i][j].goals);
            maxGoals = max(maxGoals, goals);

            if (maxGoals == goals) {
                team = i;
            }
        }
    }
    cout << "The team with the highest goal average is TEAM: " << team + 1 << endl;
}

footballer* getWorstTeamHighestScorer(footballer** matrix, int rows, int columns) {
    // team with highest goal percentage
    int minGoals = INT_MAX, worstTeamIndex = 0;
    for (int i = 0; i < rows; i++) {
        int goals = 0;
        for (int j = 0; j < columns; j++) {
            goals += *(matrix[i][j].goals);
        }
        minGoals = min(minGoals, goals);
        if (minGoals == goals) {
            worstTeamIndex = i;
        }
    }

    int mostGoals = INT_MIN;
    for (int i = 0; i < rows; i++) {
        mostGoals = max(*(matrix[worstTeamIndex][i].goals), mostGoals);
    }

    footballer* worstTeamBestStriker = nullptr;
    for (int i = 0; i < rows; i++) {
        if (*(matrix[worstTeamIndex][i].goals) == mostGoals) {
            worstTeamBestStriker = &matrix[worstTeamIndex][i];
        }
    }

    return worstTeamBestStriker;
}


void printMatrix(footballer** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        cout << "TEAM NUMBER " << i + 1 << ":" << endl;
        cout << endl;
        for (int j = 0; j < columns; j++) {
            cout << "The number of the player: " << *(matrix[i][j].playerID) << endl;
            cout << "Date of birth of the player: " << *(matrix[i][j].yearOfBirth) << endl;
            cout << "Number of goals scored by the player: " << *(matrix[i][j].goals) << endl;
            cout << endl;
        }
        cout << endl; cout << endl; cout << endl;
    }
}

void deallocateMemory(footballer**& matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}

int main() {

    int numberOfTeams = 0;      // rows
    int numberOfPlayers = 0;    // columns

    do {
        cout << "Please enter the number of teams: ";
        cin >> numberOfTeams;
        cin.ignore();
    } while (numberOfTeams < 1);

    do {
        cout << "Please enter the number of players: ";
        cin >> numberOfPlayers;
        cin.ignore();
    } while (numberOfPlayers < 1);

    footballer** matrix = new footballer * [numberOfTeams];
    for (int i = 0; i < numberOfTeams; i++) {
        matrix[i] = new footballer[numberOfPlayers];
    }
    cout << endl; cout << endl;

    footballInput(matrix, numberOfTeams, numberOfPlayers);
    printMatrix(matrix, numberOfTeams, numberOfPlayers);
    printHighestGoalAverage(matrix, numberOfTeams, numberOfPlayers);
    
    footballer* bestStrikerInWorstTeam = getWorstTeamHighestScorer(matrix, numberOfTeams, numberOfPlayers);
    cout << "The number of the worst team's best player: " << *(*bestStrikerInWorstTeam).playerID << endl;
    cout << "Date of birth of the worst team's best player: " << *(*bestStrikerInWorstTeam).yearOfBirth << endl;
    cout << "Number of goals scored by the worst team's best player: " << *(*bestStrikerInWorstTeam).goals << endl;

    deallocateMemory(matrix, numberOfTeams);

    return 0;
}