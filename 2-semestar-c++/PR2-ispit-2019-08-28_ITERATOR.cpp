#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

mutex MUTEX_OBJ;

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
ostream& operator<<(ostream& COUT, const eRazred& obj) {
	switch (obj) {
	case PRVI: COUT << "PRVI"; break;
	case DRUGI: COUT << "DRUGI"; break;
	case TRECI: COUT << "TRECI"; break;
	case CETVRTI: COUT << "CETVRTI"; break;
	default:
		break;
	}
	return COUT;
}
enum SortirajPo { T1, T2 };

char* Alociraj(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
/*
	email adresa mora biti u formatu: text@outlook.com ili text@edu.fit.ba
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@edu.fit.ba
	za provjeru koristiti regex
	*/
bool ValidirajEmail(string email) {
	string uzorak = "\w+@(\w+\.)?\w+\.\w+";
	regex regObj(uzorak);
	return regex_match(email, regObj);
}
template<class T1, class T2>
class Kolekcija {
	T1* _elementi1 = nullptr;
	T2* _elementi2 = nullptr;
	int _trenutno;
	bool _omoguciDupliranje;
public:
	Kolekcija(bool omoguciDupliranje = true) {
		_omoguciDupliranje = omoguciDupliranje;
		_trenutno = 0;
		setElementi();
	}
	Kolekcija(const Kolekcija& obj) {
		_omoguciDupliranje = obj._omoguciDupliranje;
		_trenutno = obj.getTrenutno();
		setElementi(obj.getTrenutno(), obj.GetElementi1(), obj.GetElementi2());
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if(this!=&obj) {
			_omoguciDupliranje = obj._omoguciDupliranje;
			_trenutno = obj.getTrenutno();
			setElementi(obj.getTrenutno(), obj.GetElementi1(), obj.GetElementi2());
		}
		return *this;
	}
	~Kolekcija() {
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
	}
	T1& getElement1(int lokacija) const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) const { return _elementi2[lokacija]; }
	T1* GetElementi1() const { return _elementi1; }
	T2* GetElementi2() const { return _elementi2; }
	int getTrenutno() const { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
		delete[] _elementi1;
		delete[] _elementi2;
		
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];

		_trenutno = 0;

		if (elementi1 != nullptr && elementi2 != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				AddElement(elementi1[i], elementi2[i]);
			}
		}
	}

	bool postojiDuplikat(const T1& el1) {
		for (int i = 0; i < _trenutno; i++) {
			if (_elementi1[i] == el1)
				return true;
		}
		return false;
	}

	void AddElement(const T1& el1, const T2& el2) {
		if (_omoguciDupliranje == false && postojiDuplikat(el1))
			throw exception("Dupliranje elemenata nije dozvoljeno!");
		expand();
		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno++] = el2;
	}

	void expand() {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];

		for (int i = 0; i < _trenutno; i++) {
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}

		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = temp1;
		_elementi2 = temp2;
	}

	// kolekcija1.SortirajRastuci(SortirajPo::T2);
	
	void SortirajRastuci(SortirajPo kriterij) {
		bool desilaSePromjena = true;
		int size = _trenutno - 1;

		if (kriterij == SortirajPo::T1) {
			while (desilaSePromjena) {
				desilaSePromjena = false;
				for (int i = 0; i < size; i++) {
					if (_elementi1[i] > _elementi1[i + 1]) {
						desilaSePromjena = true;
						swap(_elementi1[i], _elementi1[i + 1]);
						swap(_elementi2[i], _elementi2[i + 1]);
					}
				}
				size--;
			}
		}
		else {
			while (desilaSePromjena) {
				desilaSePromjena = false;
				for (int i = 0; i < size; i++) {
					if (_elementi2[i] > _elementi2[i + 1]) {
						desilaSePromjena = true;
						swap(_elementi1[i], _elementi1[i + 1]);
						swap(_elementi2[i], _elementi2[i + 1]);
					}
				}
				size--;
			}
		}
	}
};

class DatumVrijeme {
	int* _dan = nullptr, * _mjesec = nullptr, * _godina = nullptr, * _sati = nullptr, * _minuti = nullptr;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	DatumVrijeme(const DatumVrijeme& obj) {
		setDan(obj.getDan());
		setMjesec(obj.getMjesec());
		setGodina(obj.getGodina());
		setSati(obj.getSati());
		setMinuti(obj.getMinuti());
	}
	DatumVrijeme& operator=(const DatumVrijeme& obj) {
		if(this!=&obj) {
			setDan(obj.getDan());
			setMjesec(obj.getMjesec());
			setGodina(obj.getGodina());
			setSati(obj.getSati());
			setMinuti(obj.getMinuti());
		}
		return *this;
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
	// moje funckije
	int getDan() const { return _dan == nullptr ? 1 : *_dan; }
	int getMjesec() const { return _mjesec == nullptr ? 1 : *_mjesec; }
	int getGodina() const { return _godina == nullptr ? 2000 : *_godina; }
	int getSati() const { return _sati == nullptr ? 0 : *_sati; }
	int getMinuti() const { return _minuti == nullptr ? 0 : *_minuti; }

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
	void setSati(int sati) {
		if (_sati == nullptr)
			_sati = new int;
		*_sati = sati;
	}
	void setMinuti(int minuti) {
		if (_minuti == nullptr)
			_minuti = new int;
		*_minuti = minuti;
	}

	int satiUMinute() const {
		return getSati() * 60 + getMinuti();
	}

	int DMGtoInt() const {
		return getGodina() * 365.24 + getMjesec() * 30.41 + getDan();
	}
};

bool razmakManjiOdPetMinuta(const DatumVrijeme& d1, const DatumVrijeme& d2) {
	// samo ako je u pitanju isti datum
	if (d1.getDan() == d2.getDan() && d1.getMjesec() == d2.getMjesec() && d1.getGodina() == d2.getGodina()) {
		if (abs(d1.satiUMinute() - d2.satiUMinute()) < 5)
			return true;
	}
	return false;
}

bool operator==(const DatumVrijeme& d1, const DatumVrijeme& d2) {
	return d1.getDan() == d2.getDan() &&
		d1.getMjesec() == d2.getMjesec() &&
		d1.getGodina() == d2.getGodina() &&
		d1.getSati() == d2.getSati() &&
		d1.getMinuti() == d2.getMinuti();
}

bool operator>(const DatumVrijeme& d1, const DatumVrijeme& d2) {
	if (d1.DMGtoInt() < d2.DMGtoInt())
		return false;
	else if (d1.DMGtoInt() == d2.DMGtoInt()) {
		if (d1.satiUMinute() <= d2.satiUMinute())
			return false;
	}
	return true;
}
bool operator<(const DatumVrijeme& d1, const DatumVrijeme& d2) {
	return !(d1 == d2 || d1 > d2);
}

class Predmet {
	char* _naziv = nullptr;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}
	Predmet(const Predmet& obj) {
		setNaziv(obj.GetNaziv());
		_ocjena = obj._ocjena;
		_napomena = obj._napomena;
	}
	Predmet& operator=(const Predmet& obj) {
		if(this!=&obj) {
			setNaziv(obj.GetNaziv());
			_ocjena = obj._ocjena;
			_napomena = obj._napomena;
		}
		return *this;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() const { return _napomena; }
	char* GetNaziv() const { return _naziv; }
	int GetOcjena() const { return _ocjena; }

	void setNaziv(const char* source) {
		delete[] _naziv;
		_naziv = Alociraj(source);
	}

	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
};

bool operator==(const Predmet& p1, const Predmet& p2) {
	return strcmp(p1.GetNaziv(), p2.GetNaziv()) == 0 && p1.GetOcjena() == p2.GetOcjena() && 
		p1.GetNapomena() == p2.GetNapomena();
}

class Uspjeh {
	eRazred* _razred = nullptr;
	//formalni argument DatumVrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(eRazred razred) {
		_razred = new eRazred(razred);
	}
	Uspjeh(const Uspjeh& obj) {
		setRazred(*obj.GetERazred());
		_predmeti = obj._predmeti;
	}
	Uspjeh& operator=(const Uspjeh& obj) {
		if(this!=&obj) {
			setRazred(*obj.GetERazred());
			_predmeti = obj._predmeti;
		}
		return *this;
	}
	~Uspjeh() { delete _razred; _razred = nullptr; }

	Kolekcija<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	eRazred* GetERazred() const { return _razred; }
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << *obj._razred << " " << obj._predmeti << endl;
		return COUT;
	}

	void setRazred(eRazred razred) {
		if (_razred == nullptr)
			_razred = new eRazred;
		*_razred = razred;
	}

	float getProsjekZaRazred() {
		if (_predmeti.getTrenutno() == 0)
			return 0;
		float suma = 0.0f;
		for (int i = 0; i < _predmeti.getTrenutno(); i++) {
			suma += _predmeti.getElement1(i).GetOcjena();
		}
		return suma / _predmeti.getTrenutno();
	}
};

class Kandidat {
	char* _imePrezime = nullptr;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);
		_emailAdresa = ValidirajEmail(emailAdresa) ? emailAdresa : "notSet@edu.fit.ba";
		_brojTelefona = brojTelefona;
	}
	Kandidat(const Kandidat& obj) {
		setImePrezime(obj.GetImePrezime());
		_emailAdresa = obj._emailAdresa;
		_brojTelefona = obj._brojTelefona;
		_uspjeh = obj._uspjeh;
	}
	Kandidat& operator=(const Kandidat& obj) {
		if(this!=&obj) {
			setImePrezime(obj.GetImePrezime());
			_emailAdresa = obj._emailAdresa;
			_brojTelefona = obj._brojTelefona;
			_uspjeh = obj._uspjeh;
		}
		return *this;
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		return COUT;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() const { return _imePrezime; }

	void setImePrezime(const char* source) {
		delete[] _imePrezime;
		_imePrezime = Alociraj(source);
	}

	DatumVrijeme getZadnjiDatum(eRazred razred) {
		DatumVrijeme temp;
		for (int i = 0; i < _uspjeh.size(); i++) {
			if (razred == *_uspjeh[i].GetERazred()) {
				for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++) {
					temp = _uspjeh[i].GetPredmeti()->getElement2(j);
				}
			}
		}
		return temp;
	}

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 5 minuta).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	

	bool AddPredmet(eRazred razred, Predmet& predmet, DatumVrijeme& datum) {
		bool razredPronadjen = false;
		for (int i = 0; i < _uspjeh.size(); i++) {
			if (razred == *_uspjeh[i].GetERazred())
				razredPronadjen = true;
		}
		if (!razredPronadjen)
			_uspjeh.push_back(Uspjeh(razred));

		// ne smije se dodati istoimeni predmet u jedan razred
		for (int i = 0; i < _uspjeh.size(); i++) 
		{
			if (razred == *_uspjeh[i].GetERazred()) 
			{
				for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++) 
				{
					if (_uspjeh[i].GetPredmeti()->getElement1(j) == predmet)
						return false;		// ne moze se dodati duplikat

					if (razmakManjiOdPetMinuta(getZadnjiDatum(razred), datum))
						return false;		// razmak manji od pet minuta
				}
			}
		}

		// pronalazimo razred i dodajemo mu predmet
		float prosjekZaOvajRazred = 0.0f;
		for (int i = 0; i < _uspjeh.size(); i++) {
			if (razred == *_uspjeh[i].GetERazred()) {
				_uspjeh[i].GetPredmeti()->AddElement(predmet, datum);
				prosjekZaOvajRazred = _uspjeh[i].getProsjekZaRazred();
				break;
			}
		}


		// u svakom slucaju treba poslati email

		thread posalji(&Kandidat::Slanje, this, razred, prosjekZaOvajRazred);


		posalji.join();
		return true;
	}
	
	void PosaljiEmail(eRazred razred) {
		cout << "FROM: info.edu.fit.ba\n";
		cout << "TO: " << _emailAdresa << "\n";
		cout << "Postovani " << GetImePrezime() << ", evidentirali ste uspjeh za " << razred << " razred.\n";
		cout << "Pozdrav.\nFIT Team.\n";
	}

	void PosaljiSMS(eRazred razred, float prosjek) {
		cout << "Svaka cast za uspjeh " << prosjek << " u " << razred << " razredu.\n";
	}

	void Slanje(eRazred razred, float prosjek) {
		MUTEX_OBJ.lock();
		this_thread::sleep_for(chrono::seconds(2));
		PosaljiEmail(razred);
		if (prosjek > 4.5) {
			this_thread::sleep_for(chrono::seconds(1));
			PosaljiSMS(razred, prosjek);
		}
		MUTEX_OBJ.unlock();
	}

	/*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
	FROM:info@edu.fit.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirali ste uspjeh za X razred.
	Pozdrav.
	FIT Team.

	ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh X.X u X razredu".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/

	
	int BrojPonavljanjaRijeci(string rijec) {
		//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
		string recenica = "aksdnsalfksjfjskldfnsdkjhdskjfsf";
		string::iterator it = recenica.begin();
		//sregex_iterator()
	}


	/*
	class Uspjeh {
		eRazred* _razred = nullptr;
		//formalni argument DatumVrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
		Kolekcija<Predmet, DatumVrijeme> _predmeti;

		class Kandidat {
			vector<Uspjeh> _uspjeh;
	*/

	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	//vector<Predmet> jasminUspjeh = jasmin(DatumVrijeme(18, 06, 2019, 10, 15), DatumVrijeme(21, 06, 2019, 10, 10));
	
	vector<Predmet> operator()(const DatumVrijeme& d1, const DatumVrijeme& d2) {
		vector<Predmet> temp;
		for (int i = 0; i < _uspjeh.size(); i++) {
			for (int j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++) {
				if (_uspjeh[i].GetPredmeti()->getElement2(j) > d1 &&
					_uspjeh[i].GetPredmeti()->getElement2(j) < d2)
					temp.push_back(_uspjeh[i].GetPredmeti()->getElement1(j));
			}
		}
		return temp;
	}


	// Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
	
	Uspjeh* operator[](eRazred razred) {
		for (int i = 0; i < _uspjeh.size(); i++) {
			if (razred == *_uspjeh[i].GetERazred())
				return &_uspjeh[i];
		}
		return nullptr;
	}
};

void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR AE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEEILO GUBLJENJE URA?ENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKO?ER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIENI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUEAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOANE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAEENO.
	7. IMATE POTPUNU SLOBODU DA U MAIN FUNKCIJI, ZA POTREBE TESTIRANJA, DODAJETE VISE POZIVA ILI SALJETE DRUGE VRIJEDNOSTI PARAMETARA
	****************************************************************************/

	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);

	const int kolekcijaTestSize = 9;
	Kolekcija<int, int> kolekcija1(false);
	for (size_t i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, 20 - i);

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata, metoda AddElement baca izuzetak
		kolekcija1.AddElement(6, 15);
	}
	catch (exception& err) {
		cout << err.what() << endl;
	}
	cout << kolekcija1 << endl;

	//na osnovu vrijednosti parametra sortira clanove kolekcije u rastucem redoslijedu 
	kolekcija1.SortirajRastuci(SortirajPo::T2);
	cout << kolekcija1 << endl;


	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;

	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	cout << kolekcija3 << crt;

	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
		Fizika("Fizika", 5),
		Hemija("Hemija", 2),
		Engleski("Engleski", 5);
	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << Matematika << endl;

	/*
	email adresa mora biti u formatu: text@outlook.com ili text@edu.fit.ba
	u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@edu.fit.ba
	za provjeru koristiti regex
	*/
	Kandidat jasmin("Jasmin Azemovic", "jasmin@outlook.com", "033 281 172");
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
	Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

	/*
	uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	tom prilikom onemoguciti:
	- dodavanje istoimenih predmeta na nivou jednog razreda,
	- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 5 minuta).
	razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!1" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062019_1215))
		cout << "Predmet uspjesno dodan!2" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062019_1015))
		cout << "Predmet uspjesno dodan!3" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!4" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072019_1231))
		cout << "Predmet uspjesno dodan!5" << crt;
	//ne treba dodati Fiziku jer nije proslo 5 minuta od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!6" << crt;
	/*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
	FROM:info@edu.fit.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirali ste uspjeh za X razred.
	Pozdrav.
	FIT Team.

	ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh X.X u X razredu".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
	*/
	//cout << "USPJEH ISPISATI KORISTECI OSTREAM_ITERATOR" << endl;
	//cout << jasmin << endl;
	/*std::ostream_iterator<Kandidat, jasmin>;*/
	////vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;
	
	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(DatumVrijeme(18, 06, 2019, 10, 15), DatumVrijeme(21, 06, 2019, 10, 10));
	for (size_t i = 0; i < jasminUspjeh.size(); i++)
		cout << jasminUspjeh[i] << endl;

	Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
	if (uspjeh_Irazred != nullptr)
		cout << *uspjeh_Irazred << endl;

	//cin.get();
	system("pause>0");
}