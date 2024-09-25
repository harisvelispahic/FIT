#include <iostream>
#include <cstring>

using namespace std;

#pragma region Alokatori_i_pomocne_funkcije
// Z0.1 
char* alocirajTekst(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	char* novi = new char[vel];
	strcpy_s(novi, vel, tekst);
	return novi;
}

//Z0.2 :: Funkcija za alokaciju pametnog (shared_ptr) pokazivaca na niz karaktera
shared_ptr<char[]> shared_alokator(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	shared_ptr<char[]> novi(new char[vel], default_delete<char[]>());
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

// Z0.4 :: funkcija za prebrojavanje broja znamenki [voditi racuna i o negativnim vrijednostima]
int countDigits(int broj) {
	return (broj != 0) ? log10(abs(broj)) + 1 : 1;
}
// Z0.5 :: pretvoriti (int) u (char*) :: koristiti funkciju _itoa_s
char* intToStr(int broj) {
	int vel = countDigits(broj) + 1;
	char* tekst = new char[vel];
	_itoa_s(broj, tekst, vel, 10);
	return tekst;
}

// Z0.6 :: funkcija za poredjenje dva niza karaktera
bool areEqual(const char* str1, const char* str2) {
	return  (str1 == nullptr || str2 == nullptr) ? false : strcmp(str1, str2) == 0;
}

#pragma endregion

class Osoba {
protected:
	char* _ime = nullptr;
	unique_ptr<char[]> _prezime;
	char _prebivaliste[100] = "";
	int* _godine = nullptr;

public:
	Osoba() {
		setIme("");
		setPrezime("");
		setGodine(0);
	}
	Osoba(const char* ime, const char* prezime, int godine, const char* prebivaliste) {
		setIme(ime);
		setPrezime(prezime);
		setPrebivaliste(prebivaliste);
		setGodine(godine);
	}
	Osoba(const Osoba& obj) {
		setIme(obj.getIme());
		setPrezime(obj.getPrezime());
		setPrebivaliste(obj.getPrebivaliste());
		setGodine(obj.getGodine());
	}
	Osoba& operator =(const Osoba& obj) {
		if (this != &obj) {
			setIme(obj.getIme());
			setPrezime(obj.getPrezime());
			setPrebivaliste(obj.getPrebivaliste());
			setGodine(obj.getGodine());
		}
		return *this;
	}
	virtual ~Osoba() {
		delete[] _ime;
		delete _godine;
	}

	const char* getIme() const { return _ime; }
	const char* getPrezime() const { return _prezime.get(); }
	const char* getPrebivaliste() const { return _prebivaliste; }
	int getGodine() const { return _godine == nullptr ? 0 : *_godine; }

	void setIme(const char* ime) {
		delete[] _ime;
		_ime = alocirajTekst(ime);
	}
	void setPrezime(const char* prezime) {
		_prezime = unique_alokator(prezime);
	}
	void setPrebivaliste(const char* prebivaliste) {
		strcpy_s(_prebivaliste, strlen(prebivaliste) + 1, prebivaliste);;
	}
	void setGodine(int godine) {
		if (_godine == nullptr)
			_godine = new int;
		*_godine = godine;
	}

	virtual void prikaziInformacije() const {
		cout << "Ime: " << getIme() << endl;
		cout << "Prezime: " << getPrezime() << endl;
		cout << "Godine: " << getGodine() << endl;
		cout << "Prebivaliste: " << getPrebivaliste() << endl;
	}
};

class Student : public Osoba {
private:
	char* _brojIndeksa = nullptr;
	unique_ptr<int> _godinaStudija;
	int _trenutnoOcjena = 0;
	int* _ocjene = nullptr;

public:
	Student() {
		setBrojIndeksa("");
		setGodinaStudija(1);
		setOcjene(0, nullptr);
	}
	Student(const char* ime, const char* prezime, int godine, const char* prebivaliste, const char* brojIndeksa, int godinaStudija/*, double prosjek*/) 
		: Osoba(ime, prezime, godine, prebivaliste)
	{
		setBrojIndeksa(brojIndeksa);
		setGodinaStudija(godinaStudija);
		setOcjene(0, nullptr);
	}
	Student(const Student& obj) :Osoba(obj) {

		setBrojIndeksa(obj.getBrojIndeksa());
		setOcjene(obj.getTrenutnoOcjena(), obj.getOcjene());
		setBrojIndeksa(obj.getBrojIndeksa());
		setGodinaStudija(obj.getGodinaStudija());
	}
	Student& operator=(const Student& obj) {
		if (this != &obj) {
			(Osoba&)(*this) = obj;
			setBrojIndeksa(obj.getBrojIndeksa());
			setOcjene(obj.getTrenutnoOcjena(), obj.getOcjene());
			setBrojIndeksa(obj.getBrojIndeksa());
			setGodinaStudija(obj.getGodinaStudija());
		}
		return *this;
	}
	~Student() {
		delete[] _brojIndeksa;
		delete[] _ocjene;
	}

	const char* getBrojIndeksa() const { return (_brojIndeksa == nullptr) ? "" : _brojIndeksa; }
	int getGodinaStudija() const { return (_godinaStudija == nullptr) ? 1 : *_godinaStudija; }
	int getTrenutnoOcjena()const { return _trenutnoOcjena; }
	int* getOcjene()const { return _ocjene; }
	int getOcjena(int index)const {
		if (index < 0 && index >= getTrenutnoOcjena())
			return -1;
		return _ocjene[index];
	}

	void setBrojIndeksa(const char* brojIndeksa) {
		delete[] _brojIndeksa;
		_brojIndeksa = alocirajTekst(brojIndeksa);
	}
	void setOcjene(int trenutno, int* ocjene) {
		delete[] _ocjene;
		_ocjene = new int[_trenutnoOcjena];

		_trenutnoOcjena = 0;
		
		if (ocjene != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				dodajOcjenu(ocjene[i]);
			}
		}

	}
	void dodajOcjenu(int ocjena) {
		expand();
		_ocjene[_trenutnoOcjena++] = ocjena;
	}

	void expand() {
		int* temp = new int[_trenutnoOcjena + 1];
		for (int i = 0; i < _trenutnoOcjena; i++) {
			temp[i] = _ocjene[i];
		}
		delete[] _ocjene;
		_ocjene = temp;
	}

	void setGodinaStudija(int godinaStudija) {
		if (_godinaStudija == nullptr)
			_godinaStudija = make_unique<int>();
		*_godinaStudija = godinaStudija;
	}

	// Izracunati prosjek ocjena za studenta. Ukoliko student nema ocjena, vratiti nulu.
	float prosjekOcjena() {
		if (_trenutnoOcjena == 0)
			return 0;
		float suma = 0.0f;
		for (int i = 0; i < _trenutnoOcjena; i++) {
			suma += _ocjene[i];
		}
		return suma / _trenutnoOcjena;
	}
	// Ispisati sve atribute klase student i osoba
	void prikaziInformacije() const {
		Osoba::prikaziInformacije();
		cout << "Broj indexa: " << getBrojIndeksa() << endl;
		cout << "Godina studija: " << getGodinaStudija() << endl;
		cout << "Ocjene: ";
		for (int i = 0; i < _trenutnoOcjena; i++) {
			cout << _ocjene[i] << ", ";
		}
		cout << endl;
	}
};

class Profesor : public Osoba {
private:
	char* _titula = nullptr;
	unique_ptr<char[]> _oblast;
	int _brojPublikacija;
	const char* _publikacije[100] = { nullptr };

public:
	Profesor() {
		setTitula("");
		setOblast("");
		_brojPublikacija = 0;
		setPublikacije(0, nullptr);
	}
	Profesor(const char* ime, const char* prezime, int godine, const char* prebivaliste, const char* titula, const char* oblast, int brojPublikacija) 
		: Osoba(ime, prezime, godine, prebivaliste)
	{
		setTitula(titula);
		setOblast(oblast);
		_brojPublikacija = 0;
		setPublikacije(0, nullptr);
	}
	Profesor(const Profesor& obj) : Osoba(obj) {
		setTitula(obj.getTitula());
		setOblast(obj.getOblast());
		setPublikacije(obj.getBrojPublikacija(), obj.getPublikacije());
	}
	Profesor& operator=(const Profesor& obj) {
		if (this != &obj) {
			(Osoba&)(*this) = obj;
			setTitula(obj.getTitula());
			setOblast(obj.getOblast());
			setPublikacije(obj.getBrojPublikacija(), obj.getPublikacije());
		}
		return *this;
	}
	~Profesor() {
		delete[] _titula; _titula = nullptr;
		for (int i = 0; i < _brojPublikacija; i++) {
			delete[] _publikacije[i];
			_publikacije[i] = nullptr;
		}
	}

	const char* getTitula() const { return (_titula == nullptr) ? "" : _titula; }
	const char* getOblast() const { return (_oblast == nullptr) ? "" : _oblast.get(); }
	int getBrojPublikacija() const { return _brojPublikacija; }
	const char** getPublikacije() const { return (const char**)_publikacije; }
	const char* getPublikaciju(int index) const {
		if (index < 0 && index >= getBrojPublikacija())
			return "";
		return _publikacije[index];
	}

	void setTitula(const char* titula) {
		delete[] _titula;
		_titula = alocirajTekst(titula);
	}
	void setOblast(const char* oblast) {
		_oblast = unique_alokator(oblast);
	}
	void setPublikacije(int trenutno, const char** publikacije) {
		for (int i = 0; i < _brojPublikacija; i++) {
			delete[] _publikacije[i];
			_publikacije[i] = nullptr;
		}
				
		_brojPublikacija = 0;

		if (publikacije != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				dodajPublikaciju(publikacije[i]);
			}
		}

	}
	bool dodajPublikaciju(const char* publikacija) {
		if (_brojPublikacija >= size(_publikacije))
			return false;
		_publikacije[_brojPublikacija++] = alocirajTekst(publikacija);
	}
	// Ispisati sve atribute klase profesor i osoba
	void prikaziInformacije() const {
		Osoba::prikaziInformacije();
		cout << "Titula: " << getTitula() << endl;
		cout << "Oblast: " << getOblast() << endl;
		cout << "Publikacije: ";
		for (int i = 0; i < _brojPublikacija; i++) {
			cout << "\t" << _publikacije[i] << endl;
		}
		cout << endl;
	}
};

class Asistent : public Osoba {
private:
	char* _predmet = nullptr;
	int _godinaAngazmana = 0;
	char* _mentor = nullptr;

public:
	Asistent() {
		setPredmet("");
		setGodinaAngazmana(0);
		setMentor("");
	}
	Asistent(const char* ime, const char* prezime, int godine, const char* prebivaliste, const char* predmet, int godinaAngazmana, const char* mentor) 
		: Osoba(ime, prezime, godine, prebivaliste)
	{
		setPredmet(predmet);
		setGodinaAngazmana(godinaAngazmana);
		setMentor(mentor);
	}
	Asistent(const Asistent& obj) : Osoba(obj) {
		setPredmet(obj.getPredmet());
		setGodinaAngazmana(obj.getGodinaAngazmana());
		setMentor(obj.getMentor());
	}
	Asistent& operator=(const Asistent& obj) {
		if (this != &obj) {
			(Osoba&)(*this) = obj;
			setPredmet(obj.getPredmet());
			setGodinaAngazmana(obj.getGodinaAngazmana());
			setMentor(obj.getMentor());
		}
		return *this;
	}
	~Asistent() {
		delete[] _predmet; _predmet = nullptr;
		delete[] _mentor; _mentor = nullptr;
	}

	const char* getPredmet() const { return (_predmet == nullptr) ? "" : _predmet; }
	int getGodinaAngazmana() const { return _godinaAngazmana; }
	const char* getMentor() const { return (_mentor == nullptr) ? "" : _mentor; }

	void setPredmet(const char* predmet) {
		delete[] _predmet;
		_predmet = alocirajTekst(predmet);
	}
	void setGodinaAngazmana(int godinaAngazmana) {
		_godinaAngazmana = godinaAngazmana;
	}
	void setMentor(const char* mentor) {
		delete[] _mentor;
		_mentor = alocirajTekst(mentor);
	}
	// Ispisati sve atribute klase asistent i osoba
	void prikaziInformacije() const override {
		Osoba::prikaziInformacije();
		cout << "Predmet: " << getPredmet() << endl;
		cout << "Godina angazmana: " << getGodinaAngazmana() << endl;
		cout << "Mentor: " << getMentor() << endl;
	}
};
class Fakultet {
	char* _nazivUstanove = nullptr;
	char _datumOsnivanja[100] = "";
	int _trenutnoClanova = 0;
	Osoba* _clanovi[100] = { nullptr }; // Niz koji predstavlja Studente, Profesore i Asistente unutar Fakultetske jedinice
public:
	Fakultet() {
		setNazivUstanove("");
		setDatumOsnivanja("");
		_trenutnoClanova = 0;
		setClanovi(0, nullptr);
	}
	Fakultet(const char* nazivUstanove, const char* datumOsnivanja) {
		setNazivUstanove(nazivUstanove);
		setDatumOsnivanja(datumOsnivanja);
		_trenutnoClanova = 0;
		setClanovi(0, nullptr);
	}
	Fakultet(const Fakultet& obj) {
		setNazivUstanove(obj.getNazivUstanove());
		setDatumOsnivanja(obj.getDatumOsnivanja());
		_trenutnoClanova = obj._trenutnoClanova;
		setClanovi(obj.getTrenutnoClanova(), obj.getClanovi());
	}
	Fakultet& operator=(const Fakultet& obj) {
		if (this != &obj) {
			setNazivUstanove(obj.getNazivUstanove());
			setDatumOsnivanja(obj.getDatumOsnivanja());
			_trenutnoClanova = obj._trenutnoClanova;
			setClanovi(obj.getTrenutnoClanova(), obj.getClanovi());
		}
		return *this;
	}
	const char* getNazivUstanove() const { return _nazivUstanove == nullptr ? "" : _nazivUstanove; }
	const char* getDatumOsnivanja() const { return _datumOsnivanja; }
	int getTrenutnoClanova() const { return _trenutnoClanova; }
	Osoba** getClanovi() const { return (Osoba**)_clanovi; }

	void setNazivUstanove(const char* naziv) {
		delete[] _nazivUstanove;
		_nazivUstanove = alocirajTekst(naziv);
	}
	void setDatumOsnivanja(const char* datumOsnivanja) {
		strcpy_s(_datumOsnivanja, strlen(datumOsnivanja) + 1, datumOsnivanja);
	}

	void setClanovi(int trenutno, Osoba** clanovi) {
		for (int i = 0; i < _trenutnoClanova; i++) {
			delete _clanovi[i];
			_clanovi[i] = nullptr;
		}
		_trenutnoClanova = 0;

		if (clanovi != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				
				Student* student = dynamic_cast<Student*>(clanovi[i]);
				if (student != nullptr) {
					dodajClana(*student);
					continue;
				}

				Profesor* profesor = dynamic_cast<Profesor*>(clanovi[i]);
				if (profesor != nullptr) {
					dodajClana(*profesor);
					continue;
				}

				Asistent* asistent = dynamic_cast<Asistent*>(clanovi[i]);
				if (asistent != nullptr) {
					dodajClana(*asistent);
					continue;
				}

				Osoba* osoba = dynamic_cast<Osoba*>(clanovi[i]);
				if (osoba != nullptr) {
					dodajClana(*osoba);
					continue;
				}

			}
		}

	}

	template <class T>
	bool dodajClana(T clan) {
		if (_trenutnoClanova >= size(_clanovi))
			return false;
		_clanovi[_trenutnoClanova++] = new T(clan);
	}


	~Fakultet() {
		delete[] _nazivUstanove; _nazivUstanove = nullptr;
		for (int i = 0; i < _trenutnoClanova; i++) {
			delete _clanovi[i];
			_clanovi[i] = nullptr;
		}
	}
	// Ispis svih vrijednosti klase fakultet
	void ispis() const {
		cout << "Naziv fakulteta: " << getNazivUstanove() << endl;
		cout << "Datum osnivanja: " << getDatumOsnivanja() << endl;
		cout << "Clanovi: " << endl;
		for (int i = 0; i < _trenutnoClanova; i++) {
			_clanovi[i]->prikaziInformacije();
		}
		cout << "\n";
	}
};

class DlwmsApp {
private:
	int brojacFakulteta = 0;
	Fakultet fakulteti[10];

public:
	void menu() {
		int izbor = 0;
		do {
			system("cls");
			cout << "::ADMIN - meni::" << endl;
			cout << "(0) IZLAZ" << endl;
			cout << "(1) dodaj fakultet" << endl;
			cout << "(2) dodaj profesora u odabrani fakultet" << endl;
			cout << "(3) dodaj studenta u odabrani fakultet" << endl;
			cout << "(4) dodaj asistenta u odabrani fakultet" << endl;
			cout << "(5) kloniraj fakultet" << endl;
			cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
			cin >> izbor;
			cout << endl;

			switch (izbor) {
			case 1:
				dodajFakultet();
				break;
			case 2:
				dodajProfesora();
				break;
			case 3:
				dodajStudenta();
				break;
			case 4:
				dodajAsistenta();
				break;
			case 5:
				klonirajFakultet();
				break;
			default:
				break;
			}

		} while (izbor != 0);
	}

	void dodajFakultet() {
		if (brojacFakulteta >= 10) {
			cout << "Maksimalan broj fakulteta dostignut." << endl;
			return;
		}
		char naziv[100];
		char datum[100];
		cout << "Unesite naziv fakulteta: ";
		cin.ignore();
		cin.getline(naziv, 100);
		cout << "Unesite datum osnivanja: ";
		cin.getline(datum, 100);

		fakulteti[brojacFakulteta++] = Fakultet(naziv, datum);
		cout << "Fakultet dodan." << endl;
	}

	void dodajProfesora() {
		int index = odaberiFakultet();
		if (index == -1) return;

		char ime[100], prezime[100], prebivaliste[100], titula[100], oblast[100];
		int godine;

		cout << "Unesite ime profesora: ";
		cin.ignore();
		cin.getline(ime, 100);
		cout << "Unesite prezime profesora: ";
		cin.getline(prezime, 100);
		cout << "Unesite godine profesora: ";
		cin >> godine;
		cout << "Unesite prebivaliste profesora: ";
		cin.ignore();
		cin.getline(prebivaliste, 100);
		cout << "Unesite titulu profesora: ";
		cin.getline(titula, 100);
		cout << "Unesite oblast profesora: ";
		cin.getline(oblast, 100);

		fakulteti[index].dodajClana(Profesor(ime, prezime, godine, prebivaliste, titula, oblast, 0));
		cout << "Profesor dodan." << endl;
	}

	void dodajStudenta() {
		int index = odaberiFakultet();
		if (index == -1) return;

		char ime[100], prezime[100], prebivaliste[100], brojIndeksa[100];
		int godine, godinaStudija;

		cout << "Unesite ime studenta: ";
		cin.ignore();
		cin.getline(ime, 100);
		cout << "Unesite prezime studenta: ";
		cin.getline(prezime, 100);
		cout << "Unesite godine studenta: ";
		cin >> godine;
		cout << "Unesite prebivaliste studenta: ";
		cin.ignore();
		cin.getline(prebivaliste, 100);
		cout << "Unesite broj indeksa: ";
		cin.getline(brojIndeksa, 100);
		cout << "Unesite godinu studija: ";
		cin >> godinaStudija;

		//Student(const char* ime, const char* prezime, int godine, const char* prebivaliste, const char* brojIndeksa, int godinaStudija, double prosjek)
		fakulteti[index].dodajClana(Student(ime, prezime, godine, prebivaliste, brojIndeksa, godinaStudija));
		cout << "Student dodan." << endl;
	}

	void dodajAsistenta() {
		int index = odaberiFakultet();
		if (index == -1) return;

		char ime[100], prezime[100], prebivaliste[100], predmet[100], mentor[100];
		int godine, godinaAngazmana;

		cout << "Unesite ime asistenta: ";
		cin.ignore();
		cin.getline(ime, 100);
		cout << "Unesite prezime asistenta: ";
		cin.getline(prezime, 100);
		cout << "Unesite godine asistenta: ";
		cin >> godine;
		cout << "Unesite prebivaliste asistenta: ";
		cin.ignore();
		cin.getline(prebivaliste, 100);
		cout << "Unesite predmet asistenta: ";
		cin.getline(predmet, 100);
		cout << "Unesite godinu angazmana: ";
		cin >> godinaAngazmana;
		cout << "Unesite ime mentora: ";
		cin.ignore();
		cin.getline(mentor, 100);

		fakulteti[index].dodajClana(Asistent(ime, prezime, godine, prebivaliste, predmet, godinaAngazmana, mentor));
		cout << "Asistent dodan." << endl;
	}

	void klonirajFakultet() {
		int index = odaberiFakultet();
		if (index == -1) return;

		fakulteti[brojacFakulteta++] = Fakultet(fakulteti[index]);
		cout << "Fakultet dodan." << endl;
	}

	int odaberiFakultet() {
		cout << "Odaberite fakultet: " << endl;
		for (int i = 0; i < brojacFakulteta; i++) {
			cout << i + 1 << ". " << fakulteti[i].getNazivUstanove() << endl;
		}
		int izbor;
		cin >> izbor;
		if (izbor < 1 || izbor > brojacFakulteta) {
			cout << "Neispravan izbor." << endl;
			return -1;
		}
		return izbor - 1;
	}
};


int main() {

	DlwmsApp app;
	app.menu();
	return 0;
}