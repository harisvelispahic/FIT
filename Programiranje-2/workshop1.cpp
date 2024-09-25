#include<iostream>
using namespace std;

// Funkcija treba da kopira vrijednosti poslanog teksta u novoalociranu memoriju pokazivača
char* alocirajTekst(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int size = strlen(tekst) + 1;
	char* temp = new char[size];
	strcpy_s(temp, size, tekst);
	return temp;
}

// Funkcija treba da provjeri da li je godina prestupna 
bool isLeap(int godina) {
	return godina % 400 == 0 || (godina % 4 == 0 && godina % 100 != 0);
}

int getDaysForMonth(int mjesec, int godina) {
	switch (mjesec) {
	case 4: case 6: case 9: case 11: return 30;
	case 2:
		return isLeap(godina) ? 29 : 28;
	default:
		return 31;
	}
}

class Datum {
	int* _dan = nullptr;
	int* _mjesec = nullptr;
	int* _godina = nullptr;
	char* _opis = nullptr;

public:
	int getDan() { return (_dan == nullptr) ? 1 : *_dan; }
	int getMjesec() { return (_mjesec == nullptr) ? 1 : *_mjesec; }
	int getGodina() { return (_godina == nullptr) ? 1900 : *_godina; }
	const char* getOpis() { return (_opis == nullptr) ? nullptr : _opis; }

	void setDan(int d) {
		if (_dan != nullptr)
			delete _dan;
		_dan = new int{ 1 };
		*_dan = d;
	}
	void setMjesec(int m) {
		if (_mjesec != nullptr)
			delete _mjesec;
		_mjesec = new int{ 1 };
		*_mjesec = m;
	}
	void setGodina(int g) {
		if (_godina != nullptr)
			delete _godina;
		_godina = new int{ 1900 };
		*_godina = g;
	}
	void setOpis(const char* opis) {
		_opis = alocirajTekst(opis);
	}

	// Funkcija provjerava da li je datum validan, da li se vrijednosti mjeseca i dana nalaze u validnim opsezima
	bool isValid() {
		if (getDan() < 1 || getDan() > 31 || getMjesec() < 1 || getMjesec() > 12 || getGodina() < 1)
			return false;
		return getDan() <= getDaysForMonth(getMjesec(), getGodina());
	}

	// Funkcija randomizira datum (dan, mjesec i godinu)
	void randomize() {
		setOpis("");
		do {
			setDan(rand() % 31 + 1);
			setMjesec(rand() % 12 + 1);
			setGodina(rand() % 2024 + 1);
		} while (!isValid());
	}


	void setAll(int d, int m, int g, const char* opis = "") {
		setDan(d);
		setMjesec(m);
		setGodina(g);
		setOpis(opis);
	}

	void setAll(Datum& obj) {
		setDan(obj.getDan());
		setMjesec(obj.getMjesec());
		setGodina(obj.getGodina());
		setOpis(obj.getOpis());
	}

	// ispis datuma u formatu opis \n dd.mm.yyy 
	void ispis() {
		cout << getOpis() << " : " << getDan() << "." << getMjesec() << "." << getGodina() << endl;
 	}
	void dealokacija() {
		delete _dan, delete _mjesec, delete _godina;
		_dan = _mjesec = _godina = nullptr;
		delete[] _opis;
		_opis = nullptr;
	}

	// Funkcija vraća broj dana određenog datuma
	int toInt() {
		return getDan() + getMjesec() * 30.436 + getGodina() * 365.242374;
	}
};

// Funkcija provjerava da li su dva datuma ista
bool areEqual(Datum& d1, Datum& d2) {
	return d1.toInt() == d2.toInt();
}

// Funkcija vraća stariji datum od dva datuma
Datum& getStarijiDatum(Datum& d1, Datum& d2) {
	return (d1.toInt() < d2.toInt()) ? d1 : d2;
}

// Funkcija vraća noviji datum od dva datuma
Datum& getNovijiDatum(Datum& d1, Datum& d2) {
	return (d1.toInt() > d2.toInt()) ? d1 : d2;

}

// Funkcija vraća najstariji datum iz niza datuma
Datum& getNajstarijiDatum(Datum* datumi, int size) {
	Datum najstarijiDatum = datumi[0];
	for (int i = 0; i < size; i++) {
		najstarijiDatum = getStarijiDatum(najstarijiDatum, datumi[i]);
	}
	return najstarijiDatum;
}

// Funkcija vraća najnoviji datum iz niza datuma
Datum& getNajnovijiDatum(Datum* datumi, int size) {
	Datum* najnovijiDatum = &datumi[0];
	for (int i = 1; i < size; i++) {
		*najnovijiDatum = getNovijiDatum(*najnovijiDatum, datumi[i]);
	}
	return *najnovijiDatum;

}

// Funkcija vraća razliku između dva datuma izražena u danima
int getDifferenceBetween(Datum& d1, Datum& d2) {
	return abs(d1.toInt() - d2.toInt());
}

class Projekt
{
	const char* _naziv = nullptr;
	Datum _datumPocetka;
	Datum* _krajnjiRok = nullptr;
	int _trenutnoAktivosti = 0;
	Datum _datumiAktivnosti[20];

public:
	const char* getNaziv() { return (_naziv == nullptr) ? nullptr : _naziv; }
	Datum& getDatumPocetka() { return _datumPocetka; }
	Datum& getKrajnjiRok() { return *_krajnjiRok; }
	int getTrenutnoAktivnosti() { return _trenutnoAktivosti; }
	Datum& getDatumAktivnosti(int indeks) { return _datumiAktivnosti[indeks]; }
	Datum* getDatumi() { return _datumiAktivnosti; }


	void setNaziv(const char* naziv) {
		_naziv = alocirajTekst(getNaziv());
	}
	void setDatumPocetka(Datum& datum) {
		_datumPocetka.setAll(datum);
	}
	void setKrajnjiRok(Datum& datum) {
		_krajnjiRok->setAll(datum);
	}

	// Funkcija treba da postavi _datumiAktivnosti na niz datuma koji se šalje kao parametar
	void setDatumiAktivnosti(Datum* datumi, int vel) {
		for (int i = 0; i < vel; i++) {
			_datumiAktivnosti->setAll(datumi[i]);
		}
		_trenutnoAktivosti = vel;
	}

	// Funkcija treba da doda datum aktivnosti u niz _datumiAktivnosti ukoliko niz nije popunjen (ukoliko imamo manje od 20 datuma aktivnosti)
	void dodajAktivnost(Datum& datum) {
		if (_trenutnoAktivosti >= 20)
			return;
		_datumiAktivnosti[_trenutnoAktivosti].setAll(datum);
		_trenutnoAktivosti++;
	}

	void dealokacija() {
		delete[] _naziv;
		_naziv = nullptr;
		_datumPocetka.dealokacija();
		_krajnjiRok->dealokacija();
		delete _krajnjiRok;
		_krajnjiRok = nullptr;
		for (int i = 0; i < _trenutnoAktivosti; i++) {
			_datumiAktivnosti[i].dealokacija();
		}
	}
};


void zadatak1() {
	cout << "Zadatak 1" << endl;
	// test code
}

// testiranje klase Projekt
void zadatak2() {
	cout << "Zadatak 2" << endl;
	// test code
}

void menu() {
	int nastaviDalje = 1;
	while (nastaviDalje == 1) {
		int izbor = 0;
		do {
			system("cls");
			cout << "::Zadaci::" << endl;
			cout << "(1) Zadatak 1" << endl;
			cout << "(2) Zadatak 2" << endl;
			cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
			cin >> izbor;
			cout << endl;
		} while (izbor < 1 || izbor > 3);
		switch (izbor) {
		case 1: zadatak1(); cout << "Done." << endl; break;
		case 2: zadatak2(); cout << "Done." << endl; break;
		default:break;
		}
		do {
			cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
			cin >> nastaviDalje;
		} while (nastaviDalje != 0 && nastaviDalje != 1);
	}
}

int main() {

	menu();

	return 0;
}