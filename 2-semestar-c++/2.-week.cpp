#include <iostream>
using namespace std;


char* alocirajTekst(const char* source) {
	if (source == nullptr)
		return nullptr;
	int vel = strlen(source) + 1;
	char* tekst = new char[vel];
	strcpy_s(tekst, vel, source);
	return tekst;
}


class Datum {
	int* _dan = nullptr;
	int* _mjesec = nullptr;
	int* _godina = nullptr;

public:

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

// napraviti funkciju koja ce vracati datum, iz tog niza datuma treba da vrati najmladji datum
// azra@fit.ba

Datum* getNajmladjiDatum(Datum niz[], int size) {
	Datum* najmladjiDatum = &niz[0];
	for (int i = 1; i < size; i++) {
		najmladjiDatum = &getMladji(*najmladjiDatum, niz[i]);
	}
	return najmladjiDatum;
}

// i getNajstarijiDatum

Datum* getNajstarijiDatum(Datum niz[], int size) {
	Datum* najstarijiDatum = &niz[0];
	for (int i = 1; i < size; i++) {
		najstarijiDatum = &getStariji(*najstarijiDatum, niz[i]);
	}
	return najstarijiDatum;
}


void Zadatak1() {
	Datum datum1;
	Datum datum2;
	Datum datum3;

	datum1.setDan(1);
	datum2.setDan(2);
	datum3.setDan(3);

	Datum d1, d2;

	d1.unos(29, 2, 2024);
	d2.unos(1, 3, 2024);

	d1.ispis();
	d2.ispis();

	(areEqual(d1, d2)) ? cout << "Datumi su jednaki" << endl : cout << "Datumi nisu jednaki" << endl;
	Datum& starijiDatum = getStariji(d1, d2);
	cout << "Stariji datum je: ";
	starijiDatum.ispis();


	d1.dealociraj();
	d2.dealociraj();
}


class Glumac {
	char _jmbg[14] = "";
	char* _ime = nullptr;
	char* _prezime = nullptr;
	char* _mjestoRodjenja = nullptr;
	Datum* _datumRodjenja = nullptr;
	char _drzava[100] = "";
	bool _spol;	//1 - male, 0 - female
public:

	/* Setteri */

	void setJmbg(const char* jmbg) {
		if (strlen(jmbg) > 14)
			return;
		strcpy_s(_jmbg, 14, jmbg);
	}

	void setIme(const char* ime) {
		if (_ime != nullptr) {
			delete[] _ime;
			_ime = nullptr;
		}
		_ime = alocirajTekst(ime);
	}

	void setPrezime(const char* prezime) {
		if (_prezime != nullptr) {
			delete[] _prezime;
			_prezime = nullptr;
		}
		_prezime = alocirajTekst(prezime);
	}

	void setMjestoRodjenja(const char* mjestoRodjenja) {
		if (_mjestoRodjenja != nullptr) {
			delete[] _mjestoRodjenja;
			_mjestoRodjenja = nullptr;
		}
		_mjestoRodjenja = alocirajTekst(mjestoRodjenja);
	}

	void setDatumRodjenja(Datum& original) {
		if (_datumRodjenja != nullptr) {
			_datumRodjenja->dealociraj();
			delete _datumRodjenja;
			_datumRodjenja = nullptr;
		}

		_datumRodjenja = new Datum;
		_datumRodjenja->unos(original);
	}

	void setDrzava(const char* drzava) {
		if (strlen(drzava) > 100)
			return;
		strcpy_s(_drzava, 100, drzava);
	}

	void setSpol(bool spol) {
		_spol = spol;
	}

	void unos(const char* jmbg, const char* ime, const char* prezime,
		const char* mjestoRodjenja, Datum& datumRodjenja, const char* drzava, bool spol) {

		setJmbg(jmbg);
		setIme(ime);
		setPrezime(prezime);
		setMjestoRodjenja(mjestoRodjenja);
		setDatumRodjenja(datumRodjenja);
		setDrzava(drzava);
		setSpol(spol);
	}

	void unos(Glumac& original) {
		setJmbg(original.getJmbg());
		setIme(original.getIme());
		setPrezime(original.getPrezime());
		setMjestoRodjenja(original.getMjestoRodjenja());
		setDatumRodjenja(original.getDatumRodjenja());
		setDrzava(original.getDrzava());
		setSpol(original.getSpol());
	}

	/* Getteri */

	const char* getJmbg() { return _jmbg; }
	const char* getIme() { return (_ime == nullptr) ? "" : _ime; }
	const char* getPrezime() { return (_prezime == nullptr) ? "" : _prezime; }
	const char* getMjestoRodjenja() { return (_mjestoRodjenja == nullptr) ? "" : _mjestoRodjenja; }
	Datum& getDatumRodjenja() { return *_datumRodjenja; }
	const char* getDrzava() { return _drzava; }
	bool getSpol() { return _spol; }

	void Info() {
		cout << "JMBG: " << getJmbg() << endl;
		cout << "Ime: " << getIme() << endl;
		cout << "Prezime: " << getPrezime() << endl;
		cout << "Mjesto rodjenja: " << getMjestoRodjenja() << endl;
		cout << "Datum rodjenja: ";
		getDatumRodjenja().ispis();
		cout << "Drzava: " << getDrzava() << endl;
		cout << "Spol: ";
		(getSpol()) ? cout << "Musko" << endl : cout << "Zensko" << endl;

	}

	void dealociraj() {
		delete[] _ime;
		delete[] _prezime;
		delete[] _mjestoRodjenja;
		_ime = _prezime = _mjestoRodjenja = nullptr;
		delete _datumRodjenja;
		_datumRodjenja = nullptr;
	}
};


void Zadatak2() {
	Glumac g;
	Datum dr;
	dr.setDan(5);
	dr.setMjesec(8);
	dr.setGodina(1990);

	g.unos("1234567890123", "Cyllian", "Murphy", "Dublin", dr, "Irska", 1);
	g.Info();

	g.dealociraj();
}




class Film {
	char _filmID[50] = "";
	char* _naziv = nullptr;
	char* _zanr = nullptr;
	int _godinaIzlaska;
	Glumac _glumackaPostava[20];
	int* _ocjene = nullptr;
	int _trenutnoGlumaca = 0;
	int _trenutnoOcjena = 0;
public:

	/* Setteri */

	void setGlumackaPostava(Glumac* glumci, int size) {
		if (size > 20)
			return;
		for (int i = 0; i < size; i++) {
			_glumackaPostava[i].unos(glumci[i]);
		}
		_trenutnoGlumaca = size;
	}

	void dodajGlumca(Glumac& glumac) {
		if (_trenutnoGlumaca >= 20)
			return;
		_glumackaPostava[_trenutnoGlumaca].unos(glumac);
		_trenutnoGlumaca++;
	}

	void setOcjene(int* ocjene, int size) {
		_ocjene = new int[size];
		for (int i = 0; i < size; i++) {
			_ocjene[i] = ocjene[i];
		}
		_trenutnoOcjena= size;
	}

	void dodajOcjenu(int ocjena) {

		// Kreiranje temporary niza
		int* temp = _ocjene;	// temp = _ocjene = 0xaaab283f([2])

		// Alokacija memorije
		_ocjene = new int[_trenutnoOcjena + 1];		// _ocjene = 0xaaccff(815023490)
		
		// Kopiranje vrijednosti
		for (int i = 0; i < _trenutnoOcjena; i++) {
			_ocjene[i] = temp[i];	// _ocjene = 0xaaccff([2,4])
		}
		
		// spremanje nove ocjene
		_ocjene[_trenutnoOcjena] = ocjena;
		
		// uvecavanje brojaca
		_trenutnoOcjena++;

		delete[] temp;
	}


};




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
	d1.unos(25, 4, 1940);
	d2.unos(17, 8, 1943);
	Glumac alPacino, deNiro;
	alPacino.unos("123123123", "Alfredo", "Pacino", "Manhattan", d1, "USA", 1);
	deNiro.unos("456456456", "Robert", "De Niro", "NYC", d2, "USA", 1);

	Glumac glumci[2];
	glumci[0].unos(alPacino);
	glumci[1].unos(deNiro);

	Film film;
	film.setGlumackaPostava(glumci, 2);
	film.dodajOcjenu(2);
	film.dodajOcjenu(4);

	glumci[0].dealociraj();
	glumci[1].dealociraj();


	return 0;
}