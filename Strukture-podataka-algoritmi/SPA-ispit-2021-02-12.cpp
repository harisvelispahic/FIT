//Elementi prioritetnog reda predstavljaju kružnice u koordinatnom sistemu(u 2D prostoru).
//Kružnica se sastoji od sljedećih atributa :
//x i y koordinate centra kružnice
//poluprečnikom r
//
//
//struct Kruznica
//{
//	float x;
//	float y;
//	float r;
//};
//
//
//Implementirajte kompletan Prioriteni red(povezana reprezentacija).Funkcija ukloni treba da ukloni kružnicu sa najvećom površinom  P = r2 Pi.

#include <iostream>
using namespace std;

const double PI = 3.14;

struct Kruznica
{
	float x;
	float y;
	float r;

	Kruznica() {

	}

	Kruznica(float x, float y, float r) {
		this->x = x;
		this->y = y;
		this->r = r;
	}

	Kruznica(const Kruznica& obj) {
		this->x = obj.x;
		this->y = obj.y;
		this->r = obj.r;
	}

	float GetPovrsina() const {
		return pow(r, 2) * PI;
	}

	friend ostream& operator<<(ostream& COUT, const Kruznica& obj) {
		COUT << "Povrsina: " << obj.GetPovrsina() << endl;
		return COUT;
	}
};

struct Node {
	Kruznica kruznica;
	Node* next = nullptr;

	Node(Kruznica kruznica, Node* next) {
		this->kruznica = kruznica;
		this->next = next;
	}
};

class PrioritetniRedPovezani {
public:
	Node* Head = nullptr;
	int counter = 0;

	bool isEmpty() {
		return counter == 0;
	}

	void Push(Kruznica kruznica) {

		Node* newNode = new Node(kruznica, nullptr);

		if (Head == nullptr) {
			Head = newNode;
		}
		else if (kruznica.GetPovrsina() > Head->kruznica.GetPovrsina()) {
			newNode->next = Head;
			Head = newNode;
		}
		else {
			Node* traversal = Head;

			while (traversal->next != nullptr) {
				if (traversal->next->kruznica.GetPovrsina() < kruznica.GetPovrsina()) {
					newNode->next = traversal->next;
					traversal->next = newNode;
					break;
				}

				traversal = traversal->next;
			}
			if (traversal->next == nullptr) {
				traversal->next = newNode;
			}
		}
		counter++;
	}

	Kruznica Pop() {
		if (isEmpty())
			throw exception("Prazan queue");

		Kruznica kruznica = Head->kruznica;

		Node* deleteNode = Head;

		Head = Head->next;

		delete deleteNode;
		counter--;

		return kruznica;
	}

	void Print() {
		Node* traversal = Head;
		while (traversal != nullptr) {
			cout << traversal->kruznica;
			traversal = traversal->next;
		}
		cout << endl;
	}

	~PrioritetniRedPovezani() {
		Node* traversal = Head;
		while (traversal != nullptr) {
			Node* deleteNode = traversal;
			traversal = traversal->next;
			delete deleteNode;
		}
		cout << "--- DESTRUKTOR ---" << endl;
	}
};

int main() {

	Kruznica nizKruznica[5];
	for (int i = 0; i < 5; i++) {
		/*cout << "Kruznica " << i + 1 << ": " << endl;
		cout << "x: ";
		cin >> nizKruznica[i].x;
		cout << "y: ";
		cin >> nizKruznica[i].y;
		cout << "r: ";
		cin >> nizKruznica[i].r;
		cout << endl;*/
		nizKruznica[i].x = (rand() % 100 + 1) / 5.234235;
		nizKruznica[i].y = (rand() % 100 + 1) / 5.234235;
		nizKruznica[i].r = (rand() % 100 + 1) / 5.234235;
	}
	cout << "--------------------------------------\n";

	PrioritetniRedPovezani red;

	cout << "Dodavanje 5 kruznica: " << endl << endl;
	for (int i = 0; i < 5; i++) {
		red.Push(nizKruznica[i]);
	}

	red.Print();

	cout << "Brisanje 5 kruznica: ";
	for (int i = 0; i < 5; i++) {
		red.Pop();
		cout << "\n--------------------------------------\n";
		red.Print();
	}

	return 0;
}