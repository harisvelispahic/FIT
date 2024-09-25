#include <iostream>
using namespace std;

//Z0.1
char* alocirajTekst(const char* izvor) {
	if (izvor == nullptr)
		return nullptr;
	int vel = strlen(izvor) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, izvor);
	return temp;
}
// Z0.2 ::Funkcija za alokaciju pametnog(shared_ptr) pokazivaca na niz karaktera
shared_ptr<char> shared_alokator(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	shared_ptr<char> novi(new char[vel], default_delete<char[]>());
	strcpy_s(novi.get(), vel, tekst);
	return novi;
}
//Z0.3 :: Funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char[]> unique_alokator(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	unique_ptr<char[]> novi(new char[vel]);
	strcpy_s(novi.get(), vel, tekst);
	return novi;
}

class Datum
{
	unique_ptr<int> _dan = nullptr;
	unique_ptr<int> _mjesec = nullptr;
	unique_ptr<int> _godina = nullptr;
public:
	// Z1.1 :: getteri
	int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
	int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
	int getGodina() const { return (_godina == nullptr) ? 2023 : *_godina; }

	// Z1.2 :: setteri
	void setDan(int dan) {
		if (_dan == nullptr)
			_dan = make_unique<int>();
		*_dan = dan;
	}
	void setMjesec(int mjesec) {
		if (_mjesec == nullptr)
			_mjesec = make_unique<int>();
		*_mjesec = mjesec;
	}
	void setGodina(int godina) {
		if (_godina == nullptr)
			_godina = make_unique<int>();
		*_godina = godina;
	}

	// Z1.3 :: dflt. ctor
	Datum() {
		setDan(1);
		setMjesec(1);
		setGodina(2023);
	}
	// Z1.4 :: user-def. ctor
	Datum(int d, int m, int g) {
		setDan(d);
		setMjesec(m);
		setGodina(g);
	}
	// Z1.5 :: copy ctor
	Datum(const Datum& obj) {
		setDan(obj.getDan());
		setMjesec(obj.getMjesec());
		setGodina(obj.getGodina());
	}

	// Z1.6 :: operator =
	Datum& operator =(const Datum& obj) {
		if (this != &obj) {
			setDan(obj.getDan());
			setMjesec(obj.getMjesec());
			setGodina(obj.getGodina());
		}
		return *this;
	}
	int toInt()const {
		return getGodina() * 365.24 + getMjesec() * 30.14 + getDan();
	}
	// Z1.7 :: destruktor
	~Datum() {
	}
};
// Z1.8 ::ispisati datum
ostream& operator << (ostream& COUT, const Datum& obj) {
	COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina();
	return COUT;
}
void ispis(const Datum& obj, const char* delimiter = " ") {
	cout << obj.getDan() << delimiter << obj.getMjesec() << delimiter << obj.getGodina();
}
// Z1.9 :: porediti dva datuma po vrijednostima atributa
bool operator == (const Datum& d1, const Datum& d2) {
	return d1.toInt() == d2.toInt();
}
bool operator != (const Datum& d1, const Datum& d2) {
	return !(d1 == d2);
}

// Z1.10
bool operator > (const Datum& d1, const Datum& d2) {
	return d1.toInt() > d2.toInt();
}
bool operator >= (const Datum& d1, const Datum& d2) {
	return d1.toInt() > d2.toInt() || d1.toInt() == d2.toInt();
}
bool operator <(const Datum& d1, const Datum& d2) {
	return !(d1 >= d2);
}
bool operator <=(const Datum& d1, const Datum& d2) {
	return d1 < d2 || d1 == d2;
}

// kolekcija elemenata 'Vektor' (tipa T) sa mogucnoscu dinamickog prosirivanja
template<class T, int max> //max oznacava velicinu niza
class Array {
	int _trenutno = 0; // trenutno elemenata
	T* _elementi[max] = { nullptr }; // staticki niz pokazivaca
public:
	// Z3.1 :: getteri
	int getTrenutno() const { return _trenutno; }
	T** getElementi() const { return (T**)_elementi; }

	// Z3.2 :: setteri (u ovom slucaju samo jedna setter funkcija)
	void setElementi(int trenutno, T** elementi = nullptr) {
		for (int i = 0; i < _trenutno; i++) {
			delete _elementi[i];
			_elementi[i] = nullptr;
		}
		_trenutno = 0;

		if (elementi != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				add(*elementi[i]);
			}
		}
	}
	// Z3.3 :: funkcija za  dodavanje elementa
	// ukoliko je brojac dosao do kraja niza, onemoguciti dodavanje
	bool add(const T& element) {
		if (_trenutno >= max)
			return false;
		_elementi[_trenutno++] = new T(element);
		return true;
	}

	// Z3.4 :: funkcija za uklanjanje zadnjeg dodanog elementa [ne zaboravite dealokaciju]
	bool removeZadnji() {
		if (_trenutno <= 0)
			return false;
		delete _elementi[--_trenutno];
		_elementi[_trenutno] = nullptr;
		return true;
	}
	// Z3.5 :: dflt ctor
	Array() {
		setElementi(0);
	}
	// Z3.6 :: copy ctor
	Array(const Array<T, max>& obj) {
		setElementi(obj.getTrenutno(), obj.getElementi());
	}
	// Z3.7 :: operator '='
	Array<T, max>& operator = (const Array<T, max>& obj) {
		if (this != &obj) {
			setElementi(obj.getTrenutno(), obj.getElementi());
		}
		return *this;
	}
	// Z3.8 :: operator '[]'
	T& operator [] (int index) const {
		if (index < 0 || index >= _trenutno)
			throw exception("Indeks van granica opsega!");
		return *_elementi[index];
	}

	// Z3.9 :: metoda 'insertAtFirstLocation'.
	// sprijeciti umetanje ukoliko je brojac dosao do kraja
	bool insertAtFirstLocation(T element) {
		if (_trenutno >= max)
			return false;
		add(element);
		for (int i = _trenutno - 1; i > 0; i--) {
			//*(_elementi[i + 1]) = *(_elementi[i]);
			swap(_elementi[i], _elementi[i - 1]);
		}
		//*_elementi[0] = element;
		return true;
	}

	// Z3.10 :: metoda 'removeFromFirstLocation'.
	// sprijeciti uklanjanje ukoliko je brojac jednak 0
	bool removeFromFirstLocation() {
		if (_trenutno <= 0)
			return false;
		for (int i = 0; i < _trenutno - 1; i++) {
			swap(_elementi[i], _elementi[i + 1]);
		}
		removeZadnji();
	}

	// Z3.11 :: destruktor
	~Array() {
		for (int i = 0; i < _trenutno; i++) {
			delete _elementi[i];
			_elementi[i] = nullptr;
		}
	}
};
// Z3.12 :: operator '<<' za genericku klasu 'Array<T>'
template<class T, int max>
ostream& operator << (ostream& COUT, const Array<T, max>& obj) {
	for (int i = 0; i < obj.getTrenutno(); i++) {
		COUT << *obj.getElementi()[i] << ", ";
	}
	return COUT;
}
// Z3.13
template<class T, int max>
void ispis(const Array<T, max>& obj, const char* delimiter = " ") {
	for (int i = 0; i < obj.getTrenutno(); i++) {
		cout << *obj.getElementi()[i] << delimiter;
	}
}
// Z3.14
template<class T, int max>
bool operator == (const Array<T, max>& arr1, const Array<T, max>& arr2) {
	if (arr1.getTrenutno() != arr2.getTrenutno())
		return false;
	for (int i = 0; i < arr1.getTrenutno(); i++) {
		if (arr1.getElementi()[i] != arr2.getElementi()[i])
			return false;
	}
	return true;
}
template<class T, int max>
bool operator != (const Array<T, max>& arr1, const Array<T, max>& arr2) {
	return !(arr1 == arr2);
}



class Vozilo {
	char* _naziv = nullptr;
	unique_ptr<char[]> _karakteristike = nullptr;
	unique_ptr<Datum> _datumIzlaska;
	char _proizvodjac[50] = "";

public:
	Vozilo() {
		setNaziv("---");
		setKarakteristike("---");
		setDatumIzlaska(Datum());
		setProizvodjac("---");
	}
	Vozilo(const char* naziv, const char* karakteristike, Datum d, const char* proizvodjac) {
		setNaziv(naziv);
		setKarakteristike(karakteristike);
		setDatumIzlaska(d);
		setProizvodjac(proizvodjac);
	}
	Vozilo(const Vozilo& obj) {
		setNaziv(obj.getNaziv());
		setKarakteristike(obj.getKarakteristike());
		setDatumIzlaska(obj.getDatumIzlaska());
		setProizvodjac(obj.getProizvodjac());
	}
	Vozilo& operator=(const Vozilo& obj) {
		if (this != &obj) {
			setNaziv(obj.getNaziv());
			setKarakteristike(obj.getKarakteristike());
			setDatumIzlaska(obj.getDatumIzlaska());
			setProizvodjac(obj.getProizvodjac());
		}
		return *this;
	}
	const char* getKarakteristike() const { return  _karakteristike == nullptr ? "" : _karakteristike.get(); }
	const char* getNaziv() const { return  _naziv == nullptr ? "" : _naziv; }
	const char* getProizvodjac() const { return  _proizvodjac; }
	// Implementirati getter
	Datum getDatumIzlaska() const { return (_datumIzlaska == nullptr) ? Datum() : *_datumIzlaska; }

	void setKarakteristike(const char* karakteristike) {
		_karakteristike = unique_alokator(karakteristike);
	}
	void setNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = alocirajTekst(naziv);
	}
	void setProizvodjac(const char* proizvodjac) {
		strcpy_s(_proizvodjac, strlen(proizvodjac) + 1, proizvodjac);
	}

	void setDatumIzlaska(Datum datum) {
		if (_datumIzlaska == nullptr)
			_datumIzlaska = make_unique<Datum>();
		*_datumIzlaska = datum;
	}

	// Ispis svih atributa klase Vozilo
	friend ostream& operator << (ostream& COUT, const Vozilo& d) {
		COUT << "Naziv vozila: " << d.getNaziv() << endl;
		COUT << "Karakteristike vozila: " << d.getKarakteristike() << endl;
		COUT << "Datum izlaska vozila: " << d.getDatumIzlaska() << endl;
		COUT << "Proizvodjac vozila: " << d.getProizvodjac() << endl;
		return COUT;
	}
	//Poredi da li dva modela imaju isti naziv
	bool operator == (const Vozilo& obj) {
		return strcmp(getNaziv(), obj.getNaziv()) == 0;
	}

	//Poredi da li dva vozila nemaju isti naziv
	bool operator != (const Vozilo& obj) {
		return !(*this == obj);
	}
	~Vozilo() {
		delete[] _naziv;
		_naziv = nullptr;
	}
};
class Autobus : public Vozilo {
	/*
	char* _naziv = nullptr;
	unique_ptr<char[]> _karakteristike = nullptr;
	unique_ptr<Datum> _datumIzlaska;
	char _proizvodjac[50] = "";
	*/
	unique_ptr<int> _brojSjedista;
	bool* _imaToalet = nullptr;
	bool* _imaWiFI = nullptr;

public:
	Autobus() :Vozilo() {
		setBrojSedista(0);
		setImaToalet(false);
		setImaToalet(false);
	}
	Autobus(const char* naziv, const char* karakteristike, Datum d, const char* proizvodjac, int brojSedista, bool imaToalet, bool imaWiFI) : Vozilo(naziv, karakteristike, d, proizvodjac){
		setBrojSedista(brojSedista);
		setImaToalet(imaToalet);
		setImaWiFI(imaWiFI);
	}
	Autobus(const Autobus& obj) :Vozilo(obj) {
		setBrojSedista(obj.getBrojSedista());
		setImaToalet(obj.getImaToalet());
		setImaWiFI(obj.getImaWiFI());
	}
	Autobus& operator=(const Autobus& obj) {
		if (this != &obj) {
			(Vozilo&)(*this) = obj;
			setBrojSedista(obj.getBrojSedista());
			setImaToalet(obj.getImaToalet());
			setImaWiFI(obj.getImaWiFI());
		}
		return *this;
	}
	int getBrojSedista() const { return (_brojSjedista == nullptr) ? 0 : *_brojSjedista; }
	bool getImaToalet() const { return (_imaToalet == nullptr) ? false : *_imaToalet; }
	bool getImaWiFI() const { return (_imaWiFI == nullptr) ? false : *_imaWiFI; }

	void setBrojSedista(int brojSedista) {
		if (_brojSjedista == nullptr)
			_brojSjedista = make_unique<int>();
		*_brojSjedista = brojSedista;
	}

	void setImaToalet(bool imaToalet) {
		if (_imaToalet == nullptr)
			_imaToalet = new bool;
		*_imaToalet = imaToalet;
	}

	void setImaWiFI(bool imaWiFI) {
		if (_imaWiFI == nullptr)
			_imaWiFI = new bool;
		*_imaWiFI = imaWiFI;
	}
	~Autobus() {
		delete _imaToalet; _imaToalet = nullptr;
		delete _imaWiFI; _imaWiFI = nullptr;
	}
};

ostream& operator<< (ostream& COUT, const Autobus& obj) {
	COUT << (Vozilo&)obj;
	COUT << "Broj sjedista: " << obj.getBrojSedista() << endl;
	COUT << "Ima toalet: " << boolalpha << obj.getImaToalet() << endl;
	COUT << "Ima WiFI: " << boolalpha << obj.getImaWiFI() << "\n\n";
	return COUT;
}
class Voz : public Vozilo {
	int* _brojVagona = nullptr;
	unique_ptr<bool> _imaRestoran;
	unique_ptr<bool> _imaSpavaceVagone;

public:
	Voz() : Vozilo() {
		setBrojVagona(0);
		setImaRestoran(false);
		setImaSpavaceVagone(false);
	}
	Voz(const char* naziv, const char* karakteristike, Datum d, const char* proizvodjac, int brojVagona, bool imaRestoran, bool imaSpavaceVagone) : Vozilo(naziv, karakteristike, d, proizvodjac) {
		setBrojVagona(brojVagona);
		setImaRestoran(imaRestoran);
		setImaSpavaceVagone(imaSpavaceVagone);
	}
	Voz(const Voz& obj) : Vozilo(obj) {
		setBrojVagona(obj.getBrojVagona());
		setImaRestoran(obj.getImaRestoran());
		setImaSpavaceVagone(obj.getImaSpavaceVagone());
	}
	Voz& operator=(const Voz& obj) {
		if (this != &obj) {
			(Vozilo&)(*this) = obj;
			setBrojVagona(obj.getBrojVagona());
			setImaRestoran(obj.getImaRestoran());
			setImaSpavaceVagone(obj.getImaSpavaceVagone());
		}
		return *this;
	}

	int getBrojVagona() const { return (_brojVagona == nullptr) ? 0 : *_brojVagona; }
	bool getImaRestoran() const { return (_imaRestoran == nullptr) ? false : *_imaRestoran; }
	bool getImaSpavaceVagone() const { return (_imaSpavaceVagone == nullptr) ? false : *_imaSpavaceVagone; }

	void setBrojVagona(int brojVagona) {
		if (_brojVagona == nullptr)
			_brojVagona = new int;
		*_brojVagona = brojVagona;
	}
	void setImaRestoran(bool imaRestoran) {
		if (_imaRestoran == nullptr)
			_imaRestoran = make_unique<bool>();
		*_imaRestoran = imaRestoran;
	}
	void setImaSpavaceVagone(bool imaSpavaceVagone) {
		if (_imaSpavaceVagone == nullptr)
			_imaSpavaceVagone = make_unique<bool>();
		*_imaSpavaceVagone = imaSpavaceVagone;
	}
	~Voz() {
		delete _brojVagona; _brojVagona = nullptr;
	}
};
ostream& operator<< (ostream& COUT, const Voz& obj) {
	COUT << (Vozilo&)obj;
	COUT << "Broj vagona: " << obj.getBrojVagona() << endl;
	COUT << "Ima restoran: " << boolalpha << obj.getImaRestoran() << endl;
	COUT << "Ima spavace vagone: " << boolalpha << obj.getImaSpavaceVagone() << "\n\n";
	return COUT;
}

class Agencija {
	Array<Voz, 20> _Vozovi;
	Array<Autobus, 20> _autobusi;
	unique_ptr<char[]> _naziv;
	unique_ptr<Datum> _datumOsnivanja;
public:
	Agencija() {
		setNaziv("---");
		setDatumOsnivanja(Datum());
	}
	Agencija(const char* naziv, Datum d) {
		setNaziv(naziv);
		setDatumOsnivanja(d);
	}
	Agencija(const Agencija& obj) {
		setNaziv(obj.getNaziv());
		setDatumOsnivanja(obj.getDatumOsnivanja());
		_autobusi = obj.getAutobusi();
		_Vozovi = obj.getVozovi();
	}
	Agencija& operator=(const Agencija& obj) {
		if (this != &obj) {
			setNaziv(obj.getNaziv());
			setDatumOsnivanja(obj.getDatumOsnivanja());
			_autobusi = obj.getAutobusi();
			_Vozovi = obj.getVozovi();
		}
		return *this;
	}
	const char* getNaziv() const { return  _naziv == nullptr ? "" : _naziv.get(); }
	Datum getDatumOsnivanja() const { return  (_datumOsnivanja == nullptr) ? Datum() : *_datumOsnivanja; }
	Array<Voz, 20> getVozovi() const { return _Vozovi; }
	Array<Autobus, 20> getAutobusi() const { return _autobusi; }

	void setNaziv(const char* naziv) {
		_naziv = unique_alokator(naziv);
	}
	void setDatumOsnivanja(const Datum& d) {
		if (_datumOsnivanja == nullptr)
			_datumOsnivanja = make_unique<Datum>();
		*_datumOsnivanja = d;
	}
	bool addAutobus(const Autobus& obj) {
		return _autobusi.add(obj);
	}
	bool addVoz(const Voz& obj) {
		return _Vozovi.add(obj);
	}
	~Agencija() { }
};
ostream& operator<< (ostream& COUT, const Agencija& obj) {
	COUT << "Agencija " << obj.getNaziv() << endl;
	COUT << "----------------------------------------------------\n";
	COUT << "Datum osnivanja: " << obj.getDatumOsnivanja() << endl;
	COUT << "Autobusi: " << endl;
	COUT << obj.getAutobusi();
	COUT << "Vozovi: " << endl;
	COUT << obj.getVozovi();
	return COUT;
}

//void zadatak1() {
//	Datum d1;
//	Datum d2 = d1;
//	Datum d3;
//	d3 = d1;
//	Datum d4(18, 5, 2024);
//	cout << d1 << endl;
//	cout << d4 << endl;
//	cout << boolalpha << (d4 > d1) << endl;
//}

void zadatak1() {
	Array<int, 30> nizBrojeva;
	for (int i = 0; i < 20; i++) {
		nizBrojeva.add(rand() % 100 + 1);
	}
	Array<int, 30> nizBrojeva2 = nizBrojeva;
	cout << "Niz brojeva:\n" << nizBrojeva << endl;
	cout << "Ubacivanje elementa 10 na prvu lokaciju: " << endl;
	nizBrojeva.insertAtFirstLocation(10);
	cout << "Niz brojeva:\n" << nizBrojeva << endl;
	cout << "Brisanje elementa sa prve lokacije: " << endl;
	nizBrojeva.removeFromFirstLocation();
	cout << "Niz brojeva:\n" << nizBrojeva << endl;
	cout << "Drugi clan niza brojeva: " << nizBrojeva[1] << endl;
	try {
		cout << "Pokusavanje da se pristupi 100.-om clanu arraya..." << endl;
		cout << nizBrojeva[100] << endl;
	}
	catch (const std::exception& err){
		cout << err.what() << endl;
	}
}

void zadatak2() {
	Vozilo v1;
	Vozilo v2 = v1;
	Vozilo v3("Audi R8", "Brz", Datum(), "Audi");
	cout << "Vozilo: " << v3 << endl;
}

void zadatak3() {
	Autobus a1;
	Autobus a2 = a1;
	Autobus a3("MAN", "Kapacitet", Datum(), "MAN", 60, false, true);
	cout << "Autobus 1: " << a1 << endl;
	cout << "Autobus 3: " << a3 << endl;
}

void zadatak4() {
	Voz v1;
	Voz v2 = v1;
	Voz v3("Talgo", "Tezak", Datum(), "ZFBiH", 10, 0, 0);
	cout << "Voz 1: " << v1 << endl;
	cout << "Voz 3: " << v3 << endl;
}

void zadatak5() {
	Agencija a1;
	Agencija a2 = a1;

	cout << a1 << endl;

	Agencija a3("CentroTours", Datum());
	Array<Autobus, 5> autobusi;
	for (int i = 0; i < 5; i++) {
		a3.addAutobus(Autobus("Mostar - Sarajevo", "Velik", Datum(rand() % 28, rand() % 12, rand() % 24 + 2000), "MAN", rand() % 10 + 50, rand() % 2, rand() % 2));
	}
	Array<Voz, 5> vozovi;
	for (int i = 0; i < 5; i++) {
		a3.addVoz(Voz("Talgo", "Tezak", Datum(rand() % 28, rand() % 12, rand() % 24 + 2000), "ZFBiH", rand() % 10 + 50, rand() % 2, rand() % 2));
	}

	cout << a3 << endl;
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
			cout << "(4) Zadatak 4" << endl;
			cout << "(5) Zadatak 5" << endl;
			cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
			cin >> izbor;
			cout << endl;
		} while (izbor < 1 || izbor > 5);
		switch (izbor) {
		case 1: zadatak1(); cout << "Zadatak 1. Done." << endl; break;
		case 2: zadatak2(); cout << "Zadatak 2. Done." << endl; break;
		case 3: zadatak3(); cout << "Zadatak 3. Done." << endl; break;
		case 4: zadatak4(); cout << "Zadatak 4. Done." << endl; break;
		case 5: zadatak5(); cout << "Zadatak 5. Done." << endl; break;
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