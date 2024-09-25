#include <iostream>
using namespace std;

char* alocirajTekst(const char* txt) {
	int txtLen = strlen(txt) + 1;
	char* temp = new char[txtLen];
	strcpy_s(temp, txtLen, txt);
	return temp;
}

class Datum {
	int* _dan = nullptr;
	int* _mjesec = nullptr;
	int* _godina = nullptr;
public:

	int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
	int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
	int getGodina() const { return (_godina == nullptr) ? 1970 : *_godina; }

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

	Datum() {
		setDan(1);
		setMjesec(1);
		setGodina(1970);
	}

	Datum(int d, int m, int g) {
		setDan(d);
		setMjesec(m);
		setGodina(g);
	}
	Datum(const Datum& obj) {
		setDan(obj.getDan());
		setMjesec(obj.getMjesec());
		setGodina(obj.getGodina());
	}
	~Datum() {
		delete _dan, delete _mjesec, delete _godina;
		_dan = _mjesec = _godina = nullptr;
	}

	Datum& operator=(const Datum& obj) {
		if (&obj != this) {
			setDan(obj.getDan());
			setMjesec(obj.getMjesec());
			setGodina(obj.getGodina());
		}
		return *this;
	}

	friend ostream& operator<<(ostream& COUT, const Datum& obj);
};

ostream& operator<<(ostream& COUT, const Datum& obj) {
	COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina();
	return COUT;
}

class Ispit {
	char* _nazivPredmeta = nullptr;
	Datum* _datumPolaganja = nullptr;
	int _ECTS;
	double _osvojeniPostotak;
	bool* _prolaz = nullptr;
public:
	const char* getNazivPredmeta() const { return (_nazivPredmeta == nullptr) ? "" : _nazivPredmeta; }
	Datum getDatumPolaganja() const { return (_datumPolaganja == nullptr) ? Datum() : *_datumPolaganja; }
	int getECTS() const { return _ECTS; }
	double getOsvojeniPostotak() const { return _osvojeniPostotak; }
	bool getProlaz() const { return (_prolaz == nullptr) ? 0 : *_prolaz; }

	void setNazivPredmeta(const char* nazivPredmeta){
		_nazivPredmeta = alocirajTekst(nazivPredmeta);
	}
	void setDatumPolaganja(const Datum& datumPolaganja) {
		if (_datumPolaganja == nullptr)
			_datumPolaganja = new Datum;
		*_datumPolaganja = datumPolaganja;
	}
	void setECTS(int ECTS) {
		_ECTS = ECTS;
	}
	void setOsvojeniPostotak(double osvojeniPostotak) {
		_osvojeniPostotak = osvojeniPostotak;
	}
	void setProlaz() {
		if (_prolaz == nullptr)
			_prolaz = new bool;
		*_prolaz = (_osvojeniPostotak >= 55) ? true : false;
	}

	Ispit(const char* nazivPredmeta = "", Datum datumPolaganja = Datum(), int ECTS=0, double osvojeniPostotak = 0) {
		setNazivPredmeta(nazivPredmeta);
		setDatumPolaganja(datumPolaganja);
		setECTS(ECTS);
		setOsvojeniPostotak(osvojeniPostotak);
		setProlaz();
	}

	Ispit(const Ispit& obj) {
		setNazivPredmeta(obj.getNazivPredmeta());
		setDatumPolaganja(obj.getDatumPolaganja());
		setECTS(obj.getECTS());
		setOsvojeniPostotak(obj.getOsvojeniPostotak());
		setProlaz();
	}

	Ispit& operator=(const Ispit& obj) {
		if (this != &obj) {
			setNazivPredmeta(obj.getNazivPredmeta());
			setDatumPolaganja(obj.getDatumPolaganja());
			setECTS(obj.getECTS());
			setOsvojeniPostotak(obj.getOsvojeniPostotak());
			setProlaz();
		}
		return *this;
	}

	~Ispit() {
		delete[] _nazivPredmeta;
		_nazivPredmeta = nullptr;
		delete _datumPolaganja;
		_datumPolaganja = nullptr;
		delete _prolaz;
		_prolaz = nullptr;
	}

	friend ostream& operator<<(ostream& COUT, const Ispit& obj);
};

ostream& operator<<(ostream& COUT, const Ispit& obj) {
	COUT << "Naziv predmeta: " << obj.getNazivPredmeta() << endl;
	COUT << "Datum polaganja: " << obj.getDatumPolaganja() << endl;
	COUT << "ECTS bodovi: " << obj.getECTS() << endl;
	COUT << "Osvojeni postotak: " << obj.getOsvojeniPostotak() << endl;
	COUT << "Rezultat: " << ((obj.getProlaz()) ? "Polozili ste :)" : "Pali ste :(") << endl;

	return COUT;
}


int main() {

	Ispit pr2("Programiranje II", Datum(18, 4, 2024), 7, 49.14);
	cout << pr2 << endl;

    return 0;
}