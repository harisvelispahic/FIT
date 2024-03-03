#include <iostream>
using namespace std;

struct Datum {
	int* _dan = nullptr;
	int* _mjesec = nullptr;
	int* _godina = nullptr;

	/*Datum() {
		_dan = new int;
		_mjesec = new int;
		_godina = new int;
	}*/

	/* Setteri */

	void setDan(int dan) {
		if (_dan == nullptr)
			_dan = new int;
		*_dan = dan;
	}

	void setMjesec(int mjesec) {
		if (_mjesec == nullptr)
			_mjesec = new int;
		*_mjesec = mjesec;
	}

	void setGodina(int godina) {
		if (_godina == nullptr)
			_godina = new int;
		*_godina = godina;
	}

	/* Getteri */

	int getDan() { return (_dan == nullptr) ? 1 : *_dan; }
	int getMjesec() { return (_mjesec == nullptr) ? 1 : *_mjesec; }
	int getGodina() { return (_godina == nullptr) ? 1970 : *_godina; }

	/*~Datum() {
		delete _dan;
		delete _mjesec;
		delete _godina;
		_dan = _mjesec = _godina = nullptr;
	}*/

	void unos(int dan, int mjesec, int godina) {
		setDan(dan);
		setMjesec(mjesec);
		setGodina(godina);
	}

	void unos(Datum& d) {
		setDan(d.getDan());
		setMjesec(d.getMjesec());
		setGodina(d.getGodina());
		// nema ga potrebe dealocirati jer ce se u mainu dealocirati, buduci da ga saljemo po referenci, pa je to isti objekat
	}

	void ispis() {
		cout << getDan() << "." << getMjesec() << "." << getGodina() << "." << endl;
	}

	int toInt() {
		return getDan() + getMjesec() * 30.4 + getGodina() * 365.24;
	}

	void dealociraj() {
		delete _dan;
		delete _mjesec;
		delete _godina;
		_dan = _mjesec = _godina = nullptr;
	}
};

/* funkcije za manipulaciju datumom */

bool areEqual(Datum& d1, Datum& d2) {
	return d1.getDan() == d2.getDan() && d1.getMjesec() == d2.getMjesec() && d1.getGodina() == d2.getGodina();
}

Datum& getStariji(Datum& d1, Datum& d2) {
	if (d1.toInt() < d2.toInt())
		return d1;
	else
		return d2;
}

Datum& getMladji(Datum& d1, Datum& d2) {
	if (d1.toInt() > d2.toInt())
		return d1;
	else
		return d2;
}

// azra@fit.ba


// napraviti funkciju koja ce vracati datum, iz tog niza datuma treba da vrati najmladji datum

Datum& getNajmladjiDatum(Datum niz[], int size) {
	Datum najmladjiDatum = niz[0];
	int maxVrijednost = 0;
	for (int i = 0; i < size; i++) {
		if (niz[i].toInt() > maxVrijednost) {
			najmladjiDatum = niz[i];
			maxVrijednost = niz[i].toInt();
		}
	}
	return najmladjiDatum;
}

Datum& getNajstarijiDatum(Datum niz[], int size) {
	Datum najstarijiDatum = niz[0];
	int minVrijednost = INT_MAX;
	for (int i = 0; i < size; i++) {
		if (niz[i].toInt() < minVrijednost) {
			najstarijiDatum = niz[i];
			minVrijednost = niz[i].toInt();
		}
	}
	return najstarijiDatum;
}

// i getNajstarijiDatum

void Zadatak1() {
	Datum datum1;
	Datum datum2;
	Datum datum3;

	datum1.setDan(1);
	datum2.setDan(2);
	datum3.setDan(3);


}

void Zadatak2() {
	cout << "Zadatak 2" << endl;
}

void Zadatak3() {
	cout << "Zadatak 3" << endl;
}

void Menu() {
	cout << "::Zadaci::" << endl;
	cout << "(1)Zadatak 1" << endl;
	cout << "(2)Zadatak 2" << endl;
	cout << "(3)Zadatak 3" << endl;
	cout << endl;
	int unos = 0;

	int ponovnoPokretanje = 0;

	do {
		cout << "Unesite broj zadatka kojeg zelite pokrenuti: ";
		cin >> unos;

		switch (unos)
		{
		case 1:
			Zadatak1();
			cout << "Zavrseno" << endl;
			break;
		case 2:
			Zadatak2();
			cout << "Zavrseno" << endl;
			break;
		case 3:
			Zadatak3();
			cout << "Zavrseno" << endl;
			break;
		default:
			cout << "Nepostojeci izbor" << endl;
			break;
		}

		cout << endl;
		do {
			cout << "Zelite li pokrenuti novi zadatak? (1/0): ";
			cin >> ponovnoPokretanje;
			cout << endl;
		} while (ponovnoPokretanje < 0 || ponovnoPokretanje>1);

	} while (unos < 1 || unos > 3 || ponovnoPokretanje);
}


int main() {

	//Menu();
	Datum d1, d2;

	d1.unos(29, 2, 2024);
	d2.unos(1, 3, 2024);

	d1.ispis();
	d2.ispis();

	(areEqual(d1, d2)) ? cout << "Datumi su jednaki" << endl : cout << "Datumi nisu jednaki" << endl;
	Datum& starijiDatum = getStariji(d1, d2);
	cout << "Stariji datum je: ";
	starijiDatum.ispis();

	// niz datuma
	Datum niz[6];
	niz[0].unos(5, 7, 1991);
	niz[1].unos(6, 7, 1991);
	niz[2].unos(1, 7, 1991);
	niz[3].unos(5, 7, 1990);
	niz[4].unos(3, 3, 2000);
	niz[5].unos(5, 7, 1990);

	Datum najmladjiDatum = getNajmladjiDatum(niz, size(niz));
	cout << "Od niza datuma, najmladji datum je: ";
	najmladjiDatum.ispis();

	Datum najstarijiDatum = getNajstarijiDatum(niz, size(niz));
	cout << "Od niza datuma, najstariji datum je: ";
	najstarijiDatum.ispis();

	d1.dealociraj();
	d2.dealociraj();


	return 0;
}