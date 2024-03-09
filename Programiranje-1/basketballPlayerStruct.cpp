#include <iostream>
using namespace std;

/*
    Create a dynamic two-dimensional array whose elements are objects of type basketball 
    (basketball is a structure whose characteristics are given below). 
    Allow the user to enter the dimensions of the array.

    struct basketballPlayer
    {
        char *ID;
        char *fullName;
        int *pointsScored;
    };

    The rows of the two-dimensional array represent different clubs and the columns represent different 
    basketball players.

    Allow the user to enter all data for all basketball players, and create a function that will find the 
    most successful club (the club with the highest number of baskets).

    It is also necessary to find the most successful basketball player in that team (doesn't have to be the 
    most successful in the league) and worst basketball player in the entire league and calculate the 
    difference in the number of points scored by those two basketball players.

    (The function should return a pointer to the memory location where that difference was written.)
*/

char* createTextFrom(const char* source) {
    if (source == nullptr) {
        return nullptr;
    }
    int size = strlen(source) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, source);
    return temp;
}

//  STRUCT

struct basketballPlayer
{
    char* ID;
    char* fullName;
    int* pointsScored;

    //  METHODS

    void setID() {
        char temp[20];
        cin.ignore();
        cin.getline(temp,size(temp));
        ID = createTextFrom(temp);
    }
    void setFullName() {
        char temp[30];
        //cin.ignore();
        cin.getline(temp, size(temp));
        fullName = createTextFrom(temp);
    }
    void setPointsScored() {
        int temp;
        cin >> temp;
        *pointsScored = temp;
        //cin.ignore();
    }

    char* getID() {
        return ID;
    }
    char* getFullName() {
        return fullName;
    }
    int getPointsScored() {
        return *pointsScored;
    }

    basketballPlayer() {
        ID = new char[20];
        fullName = new char[30];
        pointsScored = new int(0);
    }

    ~basketballPlayer() {
        delete[] ID;
        delete[] fullName;
        ID = fullName = nullptr;
        delete pointsScored;
        pointsScored = nullptr;
    }
    
    void input() {
        cout << "-----------------------------" << endl;
        cout << "Please enter the player ID: ";
        setID();
        cout << "Please enter the player's full name: ";
        setFullName();
        cout << "Please enter the number of points the player has scored: ";
        setPointsScored();
        cout << endl;
    }

    void output() {
        cout << "-----------------------------" << endl;
        cout << "The player's ID: " << getID() << endl;
        cout << "The player's full name: " << getFullName() << endl;
        cout << "The number of points the player has scored: " << getPointsScored() << endl;
        cout << endl;
    }
    // END OF METHODS
};

// END OF STRUCT

//  MATRIX FUNCTIONS

basketballPlayer** createMatrix(int rows, int columns) {
    basketballPlayer** matrix = new basketballPlayer * [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new basketballPlayer[columns];
    }
    return matrix;
}

void enterMatrix(basketballPlayer** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        cout << "Club [" << i + 1 << "]: " << endl;
        for (int j = 0; j < columns; j++) {
            cout << endl;
            cout << "Player [" << j + 1 << "]: " << endl;
            matrix[i][j].input();
        }
        system("cls");
    }
}

void printMatrix(basketballPlayer** matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        cout << "Club [" << i + 1 << "]: " << endl;
        for (int j = 0; j < columns; j++) {
            cout << endl;
            cout << "Player [" << j + 1 << "]: " << endl;
            matrix[i][j].output();
        }
    }
}

void deleteMatrix(basketballPlayer** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}

//  END OF MATRIX FUNCTIONS

int* getBestClub(basketballPlayer** matrix, int rows, int columns) {
    int mostPoints = 0, bestClubIndex = 0;
    for (int i = 0; i < rows; i++) {
        int points = 0;
        for (int j = 0; j < columns; j++) {
            points += matrix[i][j].getPointsScored();
        }
        mostPoints = max(mostPoints, points);
        if (mostPoints == points)
            bestClubIndex = i;
    }
    
    cout << "The best basketball club is the club[" << bestClubIndex + 1 << "]" << endl;

    int points = 0; 
    basketballPlayer* bestBasketballPlayer = nullptr;
    for (int i = 0; i < columns; i++) {
        points = max(points, matrix[bestClubIndex][i].getPointsScored());
        if (points == matrix[bestClubIndex][i].getPointsScored())
            bestBasketballPlayer = &matrix[bestClubIndex][i];
    }
    cout << "The best basketball player in the club[" << bestClubIndex + 1 << "] is player: "
        << bestBasketballPlayer->getFullName() << endl;

    points = INT_MAX;
    basketballPlayer* worstBasketballPlayer = nullptr;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            points = min(points, matrix[i][j].getPointsScored());
            if (points == matrix[i][j].getPointsScored())
                worstBasketballPlayer = &matrix[i][j];
        }
    }
    cout << "The worst basketball player in the league is player: " << worstBasketballPlayer->getFullName() 
        << endl;

    int result = bestBasketballPlayer->getPointsScored() - worstBasketballPlayer->getPointsScored();
    int* p = new int(result);
    return p;
}

/*
    Create a function that will find the most successful club (the club that scored the most points).

    It is also necessary to find the most successful basketball player in that team (doesn't have to be the 
    most successful in the league) and worst basketball player in the entire league and 
    calculate the difference in the number of points scored by those two basketball players.
*/

int main() {

    int clubs, players;
    do {
        cout << "Please enter the number of basketball clubs: ";
        cin >> clubs;
    } while (clubs < 1);

    do {
        cout << "Please enter the number of players: ";
        cin >> players;
    } while (players < 1);

    cout << endl;

    basketballPlayer** matrix = createMatrix(clubs, players);
    
    enterMatrix(matrix, clubs, players);
    printMatrix(matrix, clubs, players);

    int* difference = getBestClub(matrix, clubs, players);
    cout << "The difference between the score of the best's team best player and the worst player in the league is: "
        << *difference << endl;

    deleteMatrix(matrix, clubs);
    delete difference;

    return 0;
}