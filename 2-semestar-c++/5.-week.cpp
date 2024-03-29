#include <iostream>
using namespace std;

char* alocirajTekst(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int size = strlen(tekst) + 1;
	char* temp = new char[size];
	strcpy_s(temp, size, tekst);
	return temp;
}

class Datum {
	int* _dan = nullptr;
	int* _mjesec = nullptr;
	int* _godina = nullptr;
public:

	Datum() {
		setDan(1);
		setMjesec(1);
		setGodina(1970);
	}

	Datum(int dan, int mjesec, int godina) {
		setDan(dan);
		setMjesec(mjesec);
		setGodina(godina);
	}

	Datum(const Datum& datum) {
		setDan(datum.getDan());
		setMjesec(datum.getMjesec());
		setGodina(datum.getGodina());
	}

	~Datum() {
		delete _dan, delete _mjesec, delete _godina;
		_dan = _mjesec = _godina = nullptr;
	}
	
	int getDan() const { return(_dan == nullptr) ? 1 : *_dan; }
	int getMjesec() const { return(_mjesec == nullptr) ? 1 : *_mjesec; }
	int getGodina() const { return(_godina == nullptr) ? 1970 : *_godina; }


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


	void unos(Datum& datum) {
		setDan(datum.getDan());
		setMjesec(datum.getMjesec());
		setGodina(datum.getGodina());
	}

	void ispis() const {
		cout << getDan() << "." << getMjesec() << "." << getGodina() << endl;
	}
	
};

class Glumac {
	char* _ime{ nullptr };
	char* _prezime{ nullptr };
	char* _zemljaPorijekla{ nullptr };
	Datum* _datumRodjenja{ nullptr };
	bool* _spol{ nullptr };	// 1-Muski, 0-Zenski
public:

	Glumac() {
		setIme("Ime");
		setPrezime("Prezime");
		setZemljaPorijekla("BiH");
		setDatumRodjenja(Datum());
		setSpol(1);
	}

	Glumac(const Glumac& glumac) {
		setIme(glumac.getIme());
		setPrezime(glumac.getPrezime());
		setZemljaPorijekla(glumac.getZemljaPorijekla());
		setDatumRodjenja(glumac.getDatumRodjenja());
		setSpol(glumac.getSpol());
	}

	~Glumac() {
		delete[] _ime, delete[] _prezime, delete[] _zemljaPorijekla;
		_ime = _prezime = _zemljaPorijekla = nullptr;
		delete _datumRodjenja;
		_datumRodjenja = nullptr;
		delete _spol;
		_spol = nullptr;
	}


	const char* getIme() const { return (_ime == nullptr) ? "" : _ime; }
	const char* getPrezime() const { return (_prezime == nullptr) ? "" : _prezime; }
	const char* getZemljaPorijekla() const { return (_zemljaPorijekla == nullptr) ? "" : _zemljaPorijekla; }
	bool getSpol() const { return (_spol == nullptr) ? 1 : *_spol; }
	Datum getDatumRodjenja() const { return (_datumRodjenja == nullptr) ? Datum() : *_datumRodjenja; }


	void setIme(const char* ime) {
		delete[] _ime;
		_ime = alocirajTekst(ime);
	}
	void setPrezime(const char* prezime) {
		delete[] _prezime;
		_prezime = alocirajTekst(prezime);
	}
	void setZemljaPorijekla(const char* zemljaPorijekla) {
		delete[] _zemljaPorijekla;
		_zemljaPorijekla = alocirajTekst(zemljaPorijekla);
	}
	void setSpol(bool spol) {
		if (_spol == nullptr)
			_spol = new bool;
		*_spol = spol;
	}
	void setDatumRodjenja(Datum datum) {
		if (_datumRodjenja == nullptr)
			_datumRodjenja = new Datum;
		_datumRodjenja->unos(datum);
	}

	void unos(const Glumac& glumac) {
		setIme(glumac.getIme());
		setPrezime(glumac.getPrezime());
		setZemljaPorijekla(glumac.getZemljaPorijekla());
		setDatumRodjenja(glumac.getDatumRodjenja());
		setSpol(glumac.getSpol());
	}


};


class Epizoda {
	char* _naziv{ nullptr };
	int* _trajanje{ nullptr };
	char _kratakSadrzaj[100] = "";
	Datum _datumPremijere;

	int _maxOcjena = 0;
	int _trenutnoOcjena = 0;
	int* _ocjene{ nullptr };
public:

	Epizoda() {
		setOcjene(10);
	}

	Epizoda(const Epizoda& epizoda) {
		setNaziv(epizoda.getNaziv());
		setTrajanje(*epizoda._trajanje);
		setKratakSadrzaj(epizoda._kratakSadrzaj);
		setDatumPremijere(epizoda._datumPremijere);
		setOcjene(epizoda._maxOcjena, epizoda._ocjene, epizoda._trenutnoOcjena);
	}

	void unos(int maxOcjena) {
		setOcjene(maxOcjena);
	}

	const char* getNaziv() const { return(_naziv == nullptr) ? "" : _naziv; }

	void setNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = alocirajTekst(naziv);
	}
	void setTrajanje(int trajanje) {
		if (_trajanje == nullptr)
			_trajanje = new int;
		*_trajanje = trajanje;
	}
	void setKratakSadrzaj(const char* kratakSadrzaj) {
		strcpy_s(_kratakSadrzaj, strlen(kratakSadrzaj) + 1, kratakSadrzaj);
	}
	void setDatumPremijere(Datum datumPremijere) {
		_datumPremijere.unos(datumPremijere);
	}

	void setOcjene(int maxOcjena = 10, int* ocjene = nullptr, int trenutnoOcjena = 0) {
		delete[] _ocjene;
		// alokacija
		_ocjene = new int[maxOcjena];
		_maxOcjena = maxOcjena;

		// kopiranje (neobavezno, ako se ne posalje niz)
		if (ocjene != nullptr) {								// za prebacivanje starih vrijednosti
			for (int i = 0; i < trenutnoOcjena; i++) {
				_ocjene[i] = ocjene[i];
			}
			_trenutnoOcjena = trenutnoOcjena;
		}
	}
	void dodajOcjenu(int ocjena, int vel = 3) {
		if (_trenutnoOcjena >= _maxOcjena)
			expandOcjene(vel);
		_ocjene[_trenutnoOcjena++] = ocjena;
	}
	void expandOcjene(int vel) {
		int* temp = _ocjene;
		_ocjene = new int[_maxOcjena + vel];
		for (int i = 0; i < _trenutnoOcjena; i++) {
			_ocjene[i] = temp[i];
		}
		delete[] temp;
		_maxOcjena += vel;
	}
};

int main() {


	//Datum d1;	// poziva se ctor
	//Datum* d2;	// ne poziva se ctor
	//Datum* d3 = new Datum;	// poziva se ctor

	//Datum d1;
	//Datum& d2 = d1;
	//Datum d3(d1);

	//// l-value
	//int a = 3;	// r-value
	//const int& b = 5;	// ?????


	return 0;
}