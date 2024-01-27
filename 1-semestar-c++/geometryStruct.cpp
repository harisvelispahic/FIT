#include <iostream>
#include <cmath>
using namespace std;

/*
	The following structs are given:

	struct Point {
	   double x,y;
	};

	struct Circle {
	   struct Point center;
	   double halfDiameter;
	};

	struct Square {
	   struct Point ll;
	   double sideLength;
	};

	Where Square is defined by the point of the lower left corner and the length of the page,
	and all sides are parallel to the coordinate axes.

	Write a function with the following prototype:

	int removeSquares(Circle* c, int csize, Square* s, int ssize)

	The function receives an array of circles and an array of squares, and ejects from the array of squares 
	(while preserving the order of the elements!) all members that are not completely covered by at least one circle.
	A square is considered to be completely enclosed by a circle if all four of its vertices are inside the circle
	or on a circle.

	It is not allowed to create an auxiliary array.
*/

struct Point {
	double x, y;

	void input() {
		cout << "Please enter the coordinates: " << endl;
		cout << "x: ";
		cin >> x;
		cout << "y: ";
		cin >> y;

		cout << endl;
	}

	void print() {
		cout << "(" << x << ", " << y << ")" << endl;
	}
};

struct Circle {
	Point center;
	double halfDiameter;

	void input() {
		center.input();
		cout << "Please enter the halfdiameter of the circle: ";
		cin >> halfDiameter;

		cout << endl;
	}
};

struct Square {
	Point ll;			// lower left point, by which the square is defined
	double sideLength;

	void input() {
		ll.input();
		cout << "Please enter the length of the side: ";
		cin >> sideLength;

		cout << endl;
	}

	void print() {
		cout << "Lower left point coordinates: ";
		ll.print();
		cout << endl;
		cout << "Side length: " << sideLength << endl;

		cout << endl;
	}
};


double twoPointsDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool checkIfItFits(Circle kr, Square kv) {
	bool check = twoPointsDistance(kv.ll.x, kv.ll.y, kr.center.x, kr.center.y) <= kr.halfDiameter
			&& twoPointsDistance(kv.ll.x + kv.sideLength, kv.ll.y, kr.center.x, kr.center.y) <= kr.halfDiameter
			&& twoPointsDistance(kv.ll.x, kv.ll.y + kv.sideLength, kr.center.x, kr.center.y) <= kr.halfDiameter
			&& twoPointsDistance(kv.ll.x + kv.sideLength, kv.ll.y + kv.sideLength, kr.center.x, kr.center.y) <= kr.halfDiameter;

	return check;
}

int removeSquares(Circle* Circles, int circlesLen, Square* Squares, int squaresLen) { 
	int squaresArrayLength = squaresLen;
	for (int i = 0; i < squaresArrayLength; i++) {		// squares
		bool check = false;
		for (int j = 0; j < circlesLen; j++) {			// circles
			if (checkIfItFits(Circles[j], Squares[i])) {
				check = true;
				break;
			}
		}
		if (!check) {
			for (int j = i; j < squaresArrayLength - 1; j++) {
				Squares[j] = Squares[j + 1];
			}
			squaresArrayLength--;
		}
	}

	return squaresArrayLength;
}


int main() {

	int numberOfCircles, numberOfSquares;
	do {
		cout << "Please enter the size of the circles array: ";
		cin >> numberOfCircles;
	} while (numberOfCircles < 1);

	do {
		cout << "Please enter the size of the squares array: ";
		cin >> numberOfSquares;
	} while (numberOfSquares < 1);

	cout << endl;

	Circle* circlesArray = new Circle[numberOfCircles];
	Square* squaresArray = new Square[numberOfSquares];

	// circles input
	for (int i = 0; i < numberOfCircles; i++) {
		cout << "Circle " << i + 1 << endl;
		cout << "-------------------------------------------" << endl;
		circlesArray[i].input();
	}
	cout << endl;

	// squares input
	for (int i = 0; i < numberOfSquares; i++) {
		cout << "Square " << i + 1 << endl;
		cout << "-------------------------------------------" << endl;
		squaresArray[i].input();
	}

	system("cls");

	cout << "The array of squares before the change: " << endl;
	for (int i = 0; i < numberOfSquares; i++) {
		cout << "Square " << i + 1 << endl;
		cout << "-------------------------------------------" << endl;
		squaresArray[i].print();
	}
	
	system("pause");
	system("cls");

	cout << "The array of squares after the change: " << endl;
	int newArrayLength = removeSquares(circlesArray, numberOfCircles, squaresArray, numberOfSquares);
	for (int i = 0; i < newArrayLength; i++) {
		cout << "Square " << i + 1 << endl;
		cout << "-------------------------------------------" << endl;
		squaresArray[i].print();
	}

	return 0;
}