#include <iostream>
using namespace std;

char* toString(int broj) {
	int brojCifara = (broj == 0) ? 0 : int(log10(abs(broj)) + 1);
	char* temp = new char[brojCifara + 1];	// za '\0'
	_itoa_s(broj, temp, brojCifara, 10);
	return temp;
}

class Datum {
	int* _dan{ nullptr };
	int* _mjesec;
	int* _godina;
public:
	int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
	int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
	int getGodina() const { return (_godina == nullptr) ? 1970 : *_godina; }

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
		delete _dan;
		delete _mjesec;
		delete _godina;
		_dan = _mjesec = _godina = nullptr;
	}


	Datum& operator=(const Datum& datum) {
		if (this != &datum) {
			setDan(datum.getDan());
			setMjesec(datum.getMjesec());
			setGodina(datum.getGodina());
		}
		return *this;
	}

	bool isLeapYear() {
		return getGodina() % 400 == 0 || (getGodina() % 4 == 0 || getGodina() % 100 != 0);
	}

	int getBrojDana() {
		switch (getMjesec())
		{
		case 4:case 6:case 9: case 11:
			return 30;
		case 2:
			return isLeapYear() ? 29 : 28;
		default:
			return 31;
		}
	}

	int toInt() {
		return getDan() + getMjesec() * 30.41 + getGodina() * 365.24;
	}

	friend ostream& operator<<(ostream& COUT, Datum& datum);
};

ostream& operator<<(ostream& COUT, Datum& datum) {
	COUT << datum.getDan() << "." << datum.getMjesec() << "." << datum.getGodina() << "." << endl;
	return COUT;
}

bool operator==(Datum& datum1, Datum& datum2) {
	return datum1.getDan() == datum2.getDan() && datum1.getMjesec() == datum2.getMjesec() && datum1.getGodina() == datum2.getGodina();
}

bool operator!=(Datum& datum1, Datum& datum2) {
	return !(datum1 == datum2);
}

Datum operator+(Datum& datum, int uvecanje) {
	int dan = datum.getDan();
	int mjesec = datum.getMjesec();
	int godina = datum.getGodina();

	int brojDanaUMjesecu = datum.getBrojDana();
	for (int i = 0; i < uvecanje; i++) {
		if (dan < brojDanaUMjesecu) {
			dan++;
		}
		else {
			dan = 1;
			if (mjesec < 12) {
				mjesec++;
			}
			else {
				mjesec = 1;
				godina++;
			}
		}
	}
	return Datum(dan, mjesec, godina);
}

bool operator>(Datum& datum1, Datum& datum2) {
	return datum1.toInt() > datum2.toInt();
}

bool operator>=(Datum& datum1, Datum& datum2) {
	return datum1 > datum2 || datum1 == datum2;
}

bool operator<(Datum& datum1, Datum& datum2) {
	return !(datum1 >= datum2);
}

bool operator<=(Datum& datum1, Datum& datum2) {
	return !(datum1 > datum2);
}

int operator-(Datum& datum1, Datum& datum2) {			// razlika (vraca broj dana)
	return abs(datum1.toInt() - datum2.toInt());
}

Datum min(Datum& d1, Datum& d2) {
	return d1 < d2 ? d1 : d2;
}

Datum max(Datum& d1, Datum& d2) {
	return d1 > d2 ? d1 : d2;
}


class Clan {
	const int _clanId;
	char _korisnickoIme[30] = "";
	char _lozinka[20] = "";
	Datum* _datumRegistracije{ nullptr };
	bool* _spol{ nullptr };
	static int _brojClanova;
public:

	int getClanId() const { return _clanId; }
	const char* getKorisnickoIme() const { return (_korisnickoIme == nullptr) ? "" : _korisnickoIme; }
	const char* getLozinka() const { return (_lozinka == nullptr) ? "" : _lozinka; }
	Datum getDatumRegistracije() const { return (_datumRegistracije == nullptr) ? Datum() : *_datumRegistracije; }
	bool getSpol() const { return (_spol == nullptr) ? 0 : *_spol; }

	void setKorisnickoIme(const char* ime) {
		strcpy_s(_korisnickoIme, 30, ime);
	}

	void setLozinka(const char* lozinka) {
		strcpy_s(_lozinka, 20, lozinka);
	}

	void setDatumRegistracije(Datum datum) {
		if (_datumRegistracije != nullptr)
			delete _datumRegistracije;
		_datumRegistracije = new Datum;
		*_datumRegistracije = datum;
	}

	void setSpol(bool spol) {
		if (_spol != nullptr)
			delete _spol;
		_spol = new bool;
		*_spol = spol;
	}

	Clan() : _clanId(_brojClanova++) {

	}

	Clan(const Clan& obj) :_clanId(_brojClanova++) {
		setKorisnickoIme(obj.getKorisnickoIme());
		setLozinka(obj.getLozinka());
		setDatumRegistracije(obj.getDatumRegistracije());
		setSpol(obj.getSpol());
	}

	Clan(const char* ime, const char* lozinka, Datum datumRegistracije, bool spol) : _clanId(_brojClanova++) {
		setKorisnickoIme(ime);
		setLozinka(lozinka);
		setDatumRegistracije(datumRegistracije);
		setSpol(spol);
	}

	Clan& operator=(const Clan& obj) {
		setKorisnickoIme(obj.getKorisnickoIme());
		setLozinka(obj.getLozinka());
		setDatumRegistracije(obj.getDatumRegistracije());
		setSpol(obj.getSpol());
	}

	~Clan() {
		delete _datumRegistracije;
		_datumRegistracije = nullptr;
		delete _spol;
		_spol = nullptr;
	}
};
int Clan::_brojClanova = 1;

bool operator==(Clan& c1, Clan& c2) {
	return !strcmp(c1.getKorisnickoIme(), c2.getKorisnickoIme());
}


class Post {
	char* _postId{ nullptr };
	char* _korisnickoIme{ nullptr };
	char* _sadrzaj{ nullptr };
	Datum _datumObjavljivanja;
	static int _brojPostova;
public:

	void setPostId() {
		int postId = _brojPostova;
		delete[] _postId;
		_postId = toString(_brojPostova++);
	}

	Post() {
		setPostId();
	}

};
int Post::_brojPostova = 1000;

int main() {
	
	//Datum d1;
	//Datum d2(1, 2, 1970);
	//Datum d3(d2);
	//Datum d4 = d3;
	//d4 = d2;
	//cout << d4 << endl;
	//// cout.operator<<(d4);		poziva operator redirekcije vec definisan u ostream klasi
	//
	//bool jednakiDatumi = d2 == d4;
	//cout << jednakiDatumi << endl;

	//Datum d5 = d4 + 170;
	//cout << d5;

	//bool veciDatum = d5 > d4;
	//cout << veciDatum << endl;

	//int razlikaUDanima = d5 - d4;
	//cout << razlikaUDanima << endl;


	Clan clan1;
	Clan clan2;

	bool istaImena = clan1 == clan2;
	cout << istaImena;

	return 0;
}