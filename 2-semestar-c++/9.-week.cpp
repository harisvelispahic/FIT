#include <iostream>
using namespace std;

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

	int toInt() const {
		return getGodina() * 365.24 + getMjesec() * 30.4 + getDan();
	}
	
	friend ostream& operator<<(ostream& COUT, const Datum& obj);
};

ostream& operator<<(ostream& COUT, const Datum& obj) {
	COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina();
	return COUT;
}

bool operator==(const Datum& d1, const Datum& d2) {
	return d1.getDan() == d2.getDan() &&
		d1.getMjesec() == d2.getMjesec() &&
		d1.getGodina() == d2.getGodina();
}
bool operator!=(const Datum& d1, const Datum& d2) {
	return !(d1 == d2);
}
bool operator>(const Datum& d1, const Datum& d2) {
	return d1.toInt() > d2.toInt();
}
bool operator>=(const Datum& d1, const Datum& d2) {
	return d1.toInt() == d2.toInt() || d1.toInt() > d2.toInt();
}
bool operator<(const Datum& d1, const Datum& d2) {
	return !(d1.toInt() >= d2.toInt());
}
bool operator<=(const Datum& d1, const Datum& d2) {
	return !(d1.toInt() > d2.toInt());
}


template <class T>
class Vektor {
	T* _niz = nullptr;
	int _trenutno = 0;
	int _max;
public:

	int getTrenutno() const { return _trenutno; }
	int getMax() const { return _max; }
	T* getNiz() const { return _niz; }

	void setElementi(int max, int trenutno = 0, T* clanovi = nullptr) {
		delete[] _niz;			// kompajler ignorira brisanje nullptr-a
		_trenutno = 0;

		_max = max;
		_niz = new T[_max];

		if (clanovi != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				add(clanovi[i]);
			}
			// _trenutno = trenutno;			// vracanje brojaca _trenutno nazad, jer se svakim pozivom "add()" uvecava
		}
		//_trenutno = trenutno;
	}

	void add(const T& clan) {
		if (_trenutno >= _max)
			expand(20);
		_niz[_trenutno++] = clan;
	}

	void expand(int expandBy) {
		_max += expandBy;
		T* temp = new T[_max];
		for (int i = 0; i < _trenutno; i++) {
			temp[i] = _niz[i];
		}
		delete[] _niz;
		_niz = temp;
	}

	bool removeLast() {
		if (_trenutno <= 0) {
			return false;
		}
		_trenutno--;
		return true;
	}

	Vektor(int max = 20) {
		setElementi(max);
	}

	Vektor(const Vektor<T>& obj) {
		setElementi(obj.getMax(), obj.getTrenutno(), obj.getNiz());
	}

	Vektor<T>& operator=(const Vektor<T>& obj) {
		if (this != &obj)
			setElementi(obj.getMax(), obj.getTrenutno(), obj.getNiz());
		return *this;
	}

	T& operator[](int index) {
		if (index >= 0 && index < _trenutno)
			return _niz[index];
		// else {exception}
	}

	~Vektor() {
		delete[] _niz;
		_niz = nullptr;
	}

	template <class T>
	friend ostream& operator<<(ostream& COUT, Vektor<T>& obj);
};

template <class T>
ostream& operator<<(ostream& COUT, Vektor<T>& obj) {
	for (int i = 0; i < obj.getTrenutno(); i++) {
		COUT << i + 1 << " -> " << obj.getNiz()[i] << endl;
	}
	return COUT;
}


template <class T, int max>
class Array {
	int _trenutno = 0;
	T* _elementi[max];				// niz pokazivaca
public:

	int getTrenutno() const { return _trenutno; }
	T** getElementi() const { return (T**)_elementi; }				// ????????????

	void setElementi(int trenutno = 0, T** elementi = nullptr) {
		for (int i = 0; i < _trenutno; i++) {				// brisanje starog niza
			delete _elementi[i];
			_elementi[i] = nullptr;
		}
		_trenutno = 0;
		if (elementi != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				add(*elementi[i]);					// x
				//_elementi[i] = elementi[i];
			}
			//_trenutno = trenutno;
		}
		//_trenutno = trenutno;			// ne treba jer se na liniji 'x' iznad svaki put uvecava "_trenutno", tj ako ima elemenata uvecavat ce se svakim korakom, a ako nema po defaultu je _trenutno = 0
	}

	bool add(const T& element) {
		if (_trenutno >= max)
			return false;
		_elementi[_trenutno++] = new T(element);		// mora biti implementiran copy constructor
		return true;
	}

	bool removeLast() {
		if (_trenutno < 0)
			return false;

		delete _elementi[--_trenutno];						// jedna lokacija unazad se brise, pa je --trenutno
		_elementi[_trenutno] = nullptr;
		return true;
	}

	Array() {
		setElementi();
	}
	Array(const Array<T, max>& obj) {
		setElementi(obj.getTrenutno(), obj.getElementi());
	}

	Array<T, max>& operator=(const Array<T, max>& obj) {
		if (*this != obj)
			setElementi(obj.getTrenutno(), obj.getElementi());
		return *this;
	}

	T& operator[](int index) {
		if (index >= 0 && index < _trenutno)
			return *_elementi[index];
	}

	~Array() {
		for (int i = 0; i < _trenutno; i++) {
			delete _elementi[i];
			_elementi[i] = nullptr;
		}
	}

	template<class T, int max>
	friend ostream& operator<<(ostream& COUT, Array<T, max>& obj);
};

template<class T, int max>
ostream& operator<<(ostream& COUT, Array<T, max>& obj) {
	for (int i = 0; i < obj.getTrenutno(); i++) {
		COUT << i + 1 << " -> " << *(obj.getElementi()[i]) << endl;
	}
	return COUT;
}


int main() {

	Datum d1;
	cout << "Datum d1 (defaultni): " << d1 << endl;
	Datum d2(28, 8, 2004);
	cout << "Datum d2: " << d2 << endl << endl;

	Array<Datum, 20> datumiArr;
	datumiArr.add(d1);
	datumiArr.add(d2);
	cout << "Drugi datum iz arraya datuma: " << datumiArr[1] << endl;

	cout << "Array datuma: " << endl;
	cout << datumiArr << endl;


	Vektor<Datum> datumiVek;
	datumiVek.add(d1);
	datumiVek.add(d2);
	cout << "Drugi datum iz vektora datuma: " << datumiVek[1] << endl;

	cout << "Vektor datuma: " << endl;
	cout << datumiVek << endl;


	Vektor<Datum> datumiVekCpy(datumiVek);
	cout << "Kopija vektora datuma: " << endl;
	cout << datumiVekCpy << endl;

	return 0;
}