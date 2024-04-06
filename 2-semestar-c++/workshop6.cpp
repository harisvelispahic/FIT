#include <iostream>
using namespace std;

// Kopiranje i alokacija niza karaktera 
char* alocirajTekst(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, tekst);
	return temp;
}

// Boolean vrijednost (true/false) u ovisnosti od toga da li je godina prijestupna ili ne
bool isPrijestupna(int godina) {
	return godina % 400 == 0 || (godina % 4 == 0 && godina % 100 != 0);
}

// Vraca validan broj dana za svaki mjesec
int brojDanaUMjesecu(int mjesec, int godina) {
	switch (mjesec)
	{
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return (isPrijestupna(godina)) ? 29 : 28;
	default:
		return 31;
	}
}

class Datum
{
	int* _dan{ nullptr };
	int* _mjesec{ nullptr };
	int* _godina{ nullptr };

public:
	// Z1.1 :: dflt. ctor
	Datum() {
		setDan(1);
		setMjesec(1);
		setGodina(2024);
	}
	// Z1.2 :: user-def. ctor
	Datum(int d, int m, int g) {
		setDan(d);
		setMjesec(m);
		setGodina(g);
	}
	// Z1.3 :: copy ctor
	Datum(const Datum& obj) {
		setDan(obj.getDan());
		setMjesec(obj.getMjesec());
		setGodina(obj.getGodina());
	}
	// Z1.4 :: getteri i setteri
	int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
	int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
	int getGodina() const { return (_godina == nullptr) ? 2024 : *_godina; }
	void setDan(int dan) {
		if (_dan != nullptr)
			delete _dan;
		_dan = new int;
		*_dan = dan;
	}
	void setMjesec(int mjesec) {
		if (_mjesec != nullptr)
			delete _mjesec;
		_mjesec = new int;
		*_mjesec = mjesec;
	}
	void setGodina(int godina) {
		if (_godina != nullptr)
			delete _godina;
		_godina = new int;
		*_godina = godina;
	}

	// Metoda za kopiranje vrijednosti objekta
	Datum& operator = (const Datum& obj) {
		if (this != &obj) {
		setDan(obj.getDan());
		setMjesec(obj.getMjesec());
		setGodina(obj.getGodina());
		return *this;
		}
	}

	// Operator uvećava datum za jedan dan. Datum treba biti unutar validnih opsega
	const Datum& operator++() {
		if (getDan() == brojDanaUMjesecu(getMjesec(), getGodina())) {
			setDan(1);
			if (getMjesec() == 12) {
				setMjesec(1);
				setGodina(getGodina() + 1);
			}
			else
				setMjesec(getMjesec() + 1);
		}
		else
			setDan(getDan() + 1);
		return *this;
	}

	// Operator umanjuje datum za jedan dan. Datum treba biti unutar validnih opsega (posljednja godina je nulta);
	const Datum& operator--() {
		if (getDan() == 1) {
			if (getMjesec() == 1) {
				setMjesec(12);
				setGodina(getGodina() - 1);
			}
			else {
				setMjesec(getMjesec() - 1);
			}
			setDan(brojDanaUMjesecu(getMjesec(), getGodina()));
		}
		else
			setDan(getDan() - 1);
		return *this;
	}
	// Vraca broj dana svakog datuma
	int toInt() const {
		return getDan() + getMjesec() * 30.41 + getGodina() * 365.24;
	}
	// Z1.7
	~Datum() {
		delete _dan;
		delete _mjesec;
		delete _godina;
		_dan = _mjesec = _godina = nullptr;
	}
};

ostream& operator << (ostream& COUT, const Datum& d) {
	COUT << d.getDan() << "." << d.getMjesec() << "." << d.getGodina() << ".";
	return COUT;
}

// Vratiti razliku izmedju datuma u danima
int operator- (const Datum& d1, const Datum& d2) {
	return abs(d1.toInt() - d2.toInt());
}

// Vratiti rezultat poređenja dva datuma (dva datum su jednaka ako su im jednaki dan mjesec i godina)
bool operator== (const Datum& d1, const Datum& d2) {
	return d1.getDan() == d2.getDan() && d1.getMjesec() == d2.getMjesec() && d1.getGodina() == d2.getGodina();
}

bool operator!= (const Datum& d1, const Datum& d2) {
	return !(d1 == d2);
}

bool operator < (const Datum& d1, const Datum& d2) {
	return d1.toInt() < d2.toInt();
}

bool operator > (const Datum& d1, const Datum& d2) {
	return !(d1 == d2) && !(d1 < d2);
}

bool operator >= (const Datum& d1, const Datum& d2) {
	return !(d1 < d2);
}

bool operator <= (const Datum& d1, const Datum& d2) {
	return !(d1 > d2);
}

class Model {
	char* _naziv = nullptr;
	char* _opis = nullptr;
	char _proizvodjac[50] = "";
	char _drzavaIzlaska[50] = "";
	Datum* _datumIzlaska{ nullptr };

public:
	Model() {
		setNaziv("");
		setOpis("");
		setProizvodjac("");
		setDrzavaIzlaska("");
		setDatumIzlaska(Datum());
	}
	Model(const char* naziv, const char* opis, Datum d, const char* proizvodjac, const char* drzavaIzlaska) {
		setNaziv(naziv);
		setOpis(opis);
		setProizvodjac(proizvodjac);
		setDrzavaIzlaska(drzavaIzlaska);
		setDatumIzlaska(d);
	}
	Model(const Model& obj) {
		setNaziv(obj.getNaziv());
		setOpis(obj.getOpis());
		setProizvodjac(obj.getProizvodjac());
		setDrzavaIzlaska(obj.getDrzavaIzlaska());
		setDatumIzlaska(obj.getDatumIzlaska());
	}
	Model& operator=(const Model& obj) {
		if (this != &obj) {
			setNaziv(obj.getNaziv());
			setOpis(obj.getOpis());
			setProizvodjac(obj.getProizvodjac());
			setDrzavaIzlaska(obj.getDrzavaIzlaska());
			setDatumIzlaska(obj.getDatumIzlaska());
			return *this;
		}
	}

	const char* getNaziv() const { return  _naziv == nullptr ? "" : _naziv; }
	const char* getOpis() const { return  _opis == nullptr ? "" : _opis; }
	const char* getProizvodjac() const { return  _proizvodjac; }
	const char* getDrzavaIzlaska() const { return   _drzavaIzlaska; }
	// Implementirati getter
	Datum getDatumIzlaska() const { return (_datumIzlaska == nullptr) ? Datum() : *_datumIzlaska; }

	void setNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = alocirajTekst(naziv);
	}
	void setOpis(const char* opis) {
		delete[] _opis;
		_opis = alocirajTekst(opis);
	}
	void setProizvodjac(const char* proizvodjac) {
		strcpy_s(_proizvodjac, strlen(proizvodjac) + 1, proizvodjac);
	}
	void setDrzavaIzlaska(const char* drzavaIzlaska) {
		strcpy_s(_drzavaIzlaska, strlen(drzavaIzlaska) + 1, drzavaIzlaska);
	}

	void setDatumIzlaska(Datum datum) {
		if (_datumIzlaska != nullptr)
			delete _datumIzlaska;
		_datumIzlaska = new Datum;
		*_datumIzlaska = datum;
	}

	// Ispis svih atributa klase model
	friend ostream& operator << (ostream& COUT, const Model& d);

	//Poredi da li dva modela imaju isti naziv
	bool operator == (const Model& obj) {
		return strcmp(obj.getNaziv(), this->getNaziv()) == 0;
	}

	//Poredi da li dva modela nemaju isti naziv
	bool operator != (const Model& obj) {
		return !(*this == obj);
	}

	~Model() {
		delete[] _naziv;
		delete[] _opis;
		_naziv = _opis = nullptr;
		delete _datumIzlaska;
		_datumIzlaska = nullptr;
	}
};

ostream& operator << (ostream& COUT, const Model& d) {
	COUT << "Naziv modela: " << d.getNaziv() << endl;
	COUT << "Opis modela: " << d.getOpis() << endl;
	COUT << "Proizvodjac: " << d.getProizvodjac() << endl;
	COUT << "Drzava izlaska: " << d.getDrzavaIzlaska() << endl;
	COUT << "Datum izlaska: " << d.getDatumIzlaska() << endl;
	return COUT;
}


class Automobil {
	char* _naziv{ nullptr };
	Datum* _godisteAutomobila{ nullptr }; // pokazivač na jednu instancu tipa datum
	int _trenutnoModela = 0;
	int _maxModela = 0;
	Model* _modeli = nullptr; // pokazivač na niz modele koji treba biti dinamički proširiv
public:
	Automobil() {
		setNaziv("");
		setGodisteAutomobila(Datum());
		setModeli();
	}
	Automobil(const char* naziv, Datum d, int velicina = 7, Model* modeli = nullptr, int trenutnoClanova = 0) {
		setNaziv(naziv);
		setGodisteAutomobila(d);
		setModeli(velicina, modeli, trenutnoClanova);
	}
	Automobil(const Automobil& obj) {
		setNaziv(obj.getNaziv());
		setGodisteAutomobila(obj.getGodisteAutomobila());
		setModeli(obj.getMaxModela(), obj.getModeli(), obj.getTrenutnoModela());
	}
	Automobil& operator= (const Automobil& obj) {
		if (this != &obj) {
			setNaziv(obj.getNaziv());
			setGodisteAutomobila(obj.getGodisteAutomobila());
			setModeli(obj.getMaxModela(), obj.getModeli(), obj.getTrenutnoModela());
			return *this;
		}
	}
	//Dva automobila su jednaka ako su im jednaki naziv i godiste
	bool operator == (const Automobil& obj) {
		return !(strcmp(getNaziv(), obj.getNaziv())) && getGodisteAutomobila() == obj.getGodisteAutomobila();
	}
	bool operator != (const Automobil& obj) {
		return !(*this == obj);
	}
	const char* getNaziv() const { return  _naziv == nullptr ? "" : _naziv; }
	Datum getGodisteAutomobila() const { return (_godisteAutomobila == nullptr) ? Datum() : *_godisteAutomobila; }
	Model* getModeli() const { return  _modeli; }
	int getTrenutnoModela() const { return _trenutnoModela; }
	int getMaxModela() const { return _maxModela; }

	void setNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = alocirajTekst(naziv);
	}

	void setGodisteAutomobila(Datum datum) {
		if (_godisteAutomobila != nullptr)
			delete _godisteAutomobila;
		_godisteAutomobila = new Datum;
		*_godisteAutomobila = datum;
	}
	// Alokacija memorije niza modela i opcionalno pohranjivanje inicjalnih vrijednosti modela
	void setModeli(int velicina = 7, Model* modeli = nullptr, int trenutnoModela = 0) {
		delete[] _modeli;
		if (velicina == 0)
			return;
		else if (_trenutnoModela >= _maxModela)
			expandModeli();
		
		_modeli = new Model[velicina];
		for (int i = 0; i < trenutnoModela; i++) {
			_modeli[i] = modeli[i];
		}
		_trenutnoModela = trenutnoModela;
	}
	// Operator treba da doda model u dinamički niz modela
	bool operator+=(Model model) {
		if (_trenutnoModela >= _maxModela)
			expandModeli();
		_modeli[_trenutnoModela++] = model;
	}

	bool operator--() {		// ???????????
	}
	// Prosirivanje niza modela za odredjenu velicinu 
	void expandModeli(int velicina = 7) {
		Model* temp = new Model[_trenutnoModela + velicina];
		for (int i = 0; i < _trenutnoModela; i++) {
			temp[i] = _modeli[i];
		}
		_maxModela = _trenutnoModela + velicina;
		delete[] _modeli;
		_modeli = temp;
	}

	~Automobil() {
		delete[] _naziv;
		_naziv = nullptr;
		delete _godisteAutomobila;
		_godisteAutomobila = nullptr;
		delete[] _modeli;
		_modeli = nullptr;
	}

friend ostream& operator<<(ostream& COUT, const Automobil& automobil);

};

ostream& operator<<(ostream& COUT, const Automobil& automobil) {
	COUT << "Naziv automobila: " << automobil.getNaziv() << endl;
	COUT << "Godiste automobila: " << automobil.getGodisteAutomobila() << endl;
	COUT << "Modeli: \n\n";
	for (int i = 0; i < automobil.getTrenutnoModela(); i++) {
		COUT << automobil.getModeli()[i] << endl;
	}
	return COUT;
}


// Ispis svih atributa klase Automobil
void zadatak1() {
	Datum d1(31, 12, 2004);
	++d1;
	cout << d1 << endl;

	Datum d2(1, 1, 1962);
	--d2;
	cout << d2 << endl;
}

void zadatak2() {
	Model m1;
	cout << m1 << endl;

	Model m2("M1", "M1 model", Datum(), "Proizvodjac", "BiH");
	cout << m2 << endl;
}
void zadatak3() {
	Automobil a1;
	cout << a1 << endl;
	Model modeli[3] = {
		Model("Golf 6", "Automobil Golf mk6", Datum(6, 6, 2012), "Volkswagen", "Njemacka"),
		Model("Audi R8", "Automobil Audi R8", Datum(5, 8, 2023), "Audi", "Njemacka"),
		Model("Mercedes S", "Automobil Mercedes S", Datum(1, 4, 2015), "Mercedes", "Njemacka") };

	Automobil a2("Automobil", Datum(), 10, modeli, size(modeli));
	cout << a2;
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
			cout << "(3) Zadatak 3" << endl;
			cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
			cin >> izbor;
			cout << endl;
		} while (izbor < 1 || izbor > 5);
		switch (izbor) {
		case 1: zadatak1(); cout << "Zadatak 1. Done." << endl; break;
		case 2: zadatak2(); cout << "Zadatak 2. Done." << endl; break;
		case 3: zadatak3(); cout << "Zadatak 3. Done." << endl; break;
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