#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<regex>
#include<thread>
#include<mutex>
using namespace std;

mutex mrPoliceman;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/

const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";

enum Sortiranje { ASC, DESC };
enum Predmet { MATEMATIKA, FIZIKA, HEMIJA, GEOGRAFIJA, NOT_SET };
ostream& operator<<(ostream& COUT, const Predmet& obj) {
	switch (obj) {
	case MATEMATIKA: COUT << "MATEMATIKA"; break;
	case FIZIKA: COUT << "FIZIKA"; break;
	case HEMIJA: COUT << "HEMIJA"; break;
	case GEOGRAFIJA: COUT << "GEOGRAFIJA"; break;
	case NOT_SET: COUT << "NOT_SET"; break;
	default:
		break;
	}
	return COUT;
}
enum Razred { I = 1, II, III, IV };

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

bool ValidirajTelefon(string telefon) {
	/*
	koristeci regex, osigurati sljedeci format za broj telefona: +387(6X)XXX-XXX ili +387 6X XXX-XXX
	onemoguciti pojavljivanje samo jedne zagrade, a ukoliko format nije adekvatna koristiti vrijednost not_set
	*/
	string uzorak = "\\+\\d{3}[\\(\\s]6\\d[\\)\\s]\\d{3}\\-\\d{3}";
	regex regObj(uzorak);
	return regex_match(telefon, regObj);
}

template <class T1, class T2, int max>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int _trenutnoElemenata;
	bool _dozvoliDupliranje;
	Sortiranje _sortiranje;
public:
	Kolekcija(Sortiranje sortiranje = ASC, bool dozvoliDupliranje = true) {
		_trenutnoElemenata = 0;
		_sortiranje = sortiranje;
		_dozvoliDupliranje = dozvoliDupliranje;
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutnoElemenata = obj._trenutnoElemenata;
		_sortiranje = obj._sortiranje;
		_dozvoliDupliranje = obj._dozvoliDupliranje;
		setElementi(obj._trenutnoElemenata, obj.getElementi1(), obj.getElementi2());
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if(this != &obj) {
			_trenutnoElemenata = obj._trenutnoElemenata;
			_sortiranje = obj._sortiranje;
			_dozvoliDupliranje = obj._dozvoliDupliranje;
			setElementi(obj._trenutnoElemenata, obj.getElementi1(), obj.getElementi2());
		}
		return *this;
	}
	~Kolekcija() {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}
	int GetTrenutno() const { return _trenutnoElemenata; }
	int GetMax() const { return max; }

	T1& GetElement1(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi1[lokacija];
	}
	T2& GetElement2(int lokacija) const {
		if (lokacija < 0 || lokacija >= _trenutnoElemenata)
			throw exception(nedozvoljena_operacija);
		return *_elementi2[lokacija];
	}
	void SetElement2(int lokacija, T2 ele2) {
		_elementi2[lokacija] = ele2;
	}
	friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) << endl;
		return COUT;
	}

	// moje metode

	T1** getElementi1() const { return (T1**)_elementi1; }
	T2** getElementi2() const { return (T2**)_elementi2; }

	void Dealociraj() {
		for (size_t i = 0; i < _trenutnoElemenata; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}

	void setElementi(int trenutno = 0, T1** elementi1 = nullptr, T2** elementi2 = nullptr) {
		Dealociraj();
		_trenutnoElemenata = 0;

		if (elementi1 != nullptr && elementi2 != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				AddElement(*elementi1[i], *elementi2[i]);
			}
		}
	}

	bool sadrziDuplikat(const T1& el1) {
		for (int i = 0; i < _trenutnoElemenata; i++) {
			if (*_elementi1[i] == el1)
				return true;
		}
		return false;
	}

	void AddElement(const T1& el1, const T2& el2) {
		if (_trenutnoElemenata >= max) {
			throw exception("Kolekcija je popunjena!");
		}
		if (sadrziDuplikat(el1) && _dozvoliDupliranje == false)
			throw exception("Dupliranje nije dozvoljeno!");
		_elementi1[_trenutnoElemenata] = new T1(el1);
		_elementi2[_trenutnoElemenata++] = new T2(el2);
		Sortiraj();
	}

	void Sortiraj() {
		bool desilaSePromjena = true;
		int size = _trenutnoElemenata - 1;
		if (_sortiranje == ASC) {
			while (desilaSePromjena) {
				desilaSePromjena = false;
				for (int i = 0; i < size; i++) {
					if (*_elementi1[i] > *_elementi1[i + 1]) {
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
					if (*_elementi1[i] < *_elementi1[i + 1]) {
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

class Aktivnost {
	shared_ptr<Razred> _razred;
	string _opis;
	int _ocjena;//1-5
public:
	Aktivnost(Razred razred = I, int ocjena = 0, string opis = not_set) {
		_ocjena = ocjena;
		_opis = opis;
		_razred = make_shared<Razred>(razred);
	}
	Aktivnost(const Aktivnost& obj) {
		_ocjena = obj._ocjena;
		_opis = obj._opis;
		_razred = obj._razred;
	}
	Aktivnost& operator=(const Aktivnost& obj) {
		if(this!=&obj){
			_ocjena = obj._ocjena;
			_opis = obj._opis;
			_razred = obj._razred;
		}
		return *this;
	}
	int GetOcjenu() const { return _ocjena; }
	string GetOpis() const { return _opis; }
	Razred GetRazred() const { return *_razred; }

	friend ostream& operator<<(ostream& COUT, const Aktivnost& obj) {
		COUT << obj.GetRazred() << " " << obj._ocjena << " " << obj._opis << endl;
		return COUT;
	}
};

bool operator == (const Aktivnost & a1, const Aktivnost & a2) {
	return a1.GetOcjenu() == a2.GetOcjenu() && a1.GetOpis() == a2.GetOpis() && a1.GetRazred() == a2.GetRazred();
}

class Polaznik {
protected:
	char* _imePrezime = nullptr;
	string _brojTelefona;
public:
	Polaznik() {
		_imePrezime = AlocirajNizKaraktera("");
		_brojTelefona = not_set;
	}
	Polaznik(string imePrezime, string brojTelefona) : _imePrezime(AlocirajNizKaraktera(imePrezime.c_str())) {
		_brojTelefona = ValidirajTelefon(brojTelefona) ? brojTelefona : not_set;
	}
	Polaznik(const Polaznik& obj) {
		delete[] _imePrezime;
		_imePrezime = AlocirajNizKaraktera(obj.GetImePrezime());
		_brojTelefona = obj._brojTelefona;
	}
	Polaznik& operator=(const Polaznik& obj) {
		if(this!=&obj){
			delete[] _imePrezime;
			_imePrezime = AlocirajNizKaraktera(obj.GetImePrezime());
			_brojTelefona = obj._brojTelefona;
		}
		return *this;
	}
	~Polaznik() { delete[] _imePrezime; }
	const char* GetImePrezime() const { return _imePrezime; }
	string GetTelefon() const { return _imePrezime; }
	virtual void PredstaviSe() = 0;

	friend ostream& operator<<(ostream& COUT, const Polaznik& obj){
		COUT << "Ime i prezime: " << obj.GetImePrezime() << endl;
		COUT << "Broj telefona: " << obj.GetTelefon() << endl;
		return COUT;
	}
};

class Ucenik : public Polaznik{
	Kolekcija<Predmet, Aktivnost, 16>* _aktivnosti;

public:
	Ucenik(){}
	Ucenik(const char* imePrezime, string brojTelefona) : Polaznik(imePrezime, brojTelefona)
	{
		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>();
	}
	Ucenik(const Ucenik& obj) : Polaznik(obj) {
		//delete _aktivnosti;
		_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>(obj.constGetAktivnosti());
	}
	Ucenik& operator=(const Ucenik& obj) {
		if (this != &obj) {
			(Polaznik&)(*this) = obj;
			//delete _aktivnosti;
			_aktivnosti = new Kolekcija<Predmet, Aktivnost, 16>(obj.constGetAktivnosti());
		}
		return *this;
	}
	~Ucenik() {
		delete _aktivnosti; _aktivnosti = nullptr;
	}
	Kolekcija<Predmet, Aktivnost, 16>& GetAktivnosti() { return *_aktivnosti; };
	Kolekcija<Predmet, Aktivnost, 16> constGetAktivnosti() const { return *_aktivnosti; };
	friend ostream& operator<<(ostream& COUT, Ucenik& n) {
		COUT << (Polaznik&)(n);
		for (int i = 0; i < n.GetAktivnosti().GetTrenutno(); i++) {
			COUT << n.GetAktivnosti().GetElement1(i) << " : " << n.GetAktivnosti().GetElement2(i) << endl;
		}
		return COUT;
	}

	void PredstaviSe() {  }

	float getProsjekUcenika() {
		if (_aktivnosti->GetTrenutno() == 0)
			return 0.0f;
		float suma = 0.0f;
		for (int i = 0; i < _aktivnosti->GetTrenutno(); i++) {
			suma += _aktivnosti->GetElement2(i).GetOcjenu();
		}
		return suma / _aktivnosti->GetTrenutno();
	}
};
class Skola {
	char* _naziv = nullptr;
	vector<Ucenik> _ucenici;
public:
	Skola(const char* naziv = nullptr) {
		_naziv = AlocirajNizKaraktera(naziv);
	}
	Skola(const Skola& obj) {
		delete[] _naziv;
		_naziv = AlocirajNizKaraktera(obj.GetNaziv());
		_ucenici = obj._ucenici;
	}
	Skola& operator=(const Skola& obj) {
		if(this!=&obj){
			delete[] _naziv;
			_naziv = AlocirajNizKaraktera(obj.GetNaziv());
			_ucenici = obj._ucenici;
		}
		return *this;
	}
	~Skola() {
		delete[] _naziv; _naziv = nullptr;
	}
	const char* GetNaziv()const { return _naziv; }
	vector<Ucenik>& GetUcenici() { return _ucenici; };

	friend ostream& operator<<(ostream& COUT, Skola& obj) {
		COUT << "Skola: " << obj._naziv << endl;
		COUT << "Ucenici: " << endl;
		for (size_t i = 0; i < obj._ucenici.size(); i++)
			COUT << obj._ucenici[i] << endl;
		return COUT;
	}

	// moje metode 
	
	void operator()(const char* imePrezime, string brojTelefona) {
		for (int i = 0; i < _ucenici.size(); i++) {
			if (strcmp(_ucenici[i].GetImePrezime(), imePrezime) == 0 || _ucenici[i].GetTelefon() == brojTelefona)
				throw exception("Dupliranje je zabranjeno!");
		}
		_ucenici.push_back(Ucenik(imePrezime, brojTelefona));
	}

	// if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Priprema za takmicenje iz Matematike koje se odrzava u Konjicu 07.02.2019")))
	/*na nivou svakog razreda se mogu evidentirati maksimalno 4 aktivnosti, a takodjer, na nivou razreda se ne smiju ponavljati aktivnosti iz istog predmeta*/

	bool DodajAktivnost(const char* imePrezime, Predmet predmet, Aktivnost aktivnost) {
		int brojAktivnostiZaRazred = 0;
		float ocjena = 0.0f; int brojac = 0;
		int indeksUcenika = 0;
		for (int i = 0; i < _ucenici.size(); i++) {
			if (strcmp(_ucenici[i].GetImePrezime(), imePrezime) == 0) {
				indeksUcenika = i;
				for (int j = 0; j < _ucenici[i].GetAktivnosti().GetTrenutno(); j++) {
					if (_ucenici[i].GetAktivnosti().GetElement2(j).GetRazred() == aktivnost.GetRazred()) {
						brojAktivnostiZaRazred++;
						ocjena += _ucenici[i].GetAktivnosti().GetElement2(j).GetOcjenu();
						brojac++;
						if (_ucenici[i].GetAktivnosti().GetElement1(j) == predmet)
							return false;
					}
				}
			}
		}
		if (brojAktivnostiZaRazred >= 4)
			return false;

		for (int i = 0; i < _ucenici.size(); i++) {
			if (strcmp(_ucenici[i].GetImePrezime(), imePrezime) == 0) {
				_ucenici[i].GetAktivnosti().AddElement(predmet, aktivnost);
			}
		}

		// ocjena na nivou razreda
		ocjena = (brojac == 0) ? 0 : ocjena / brojac;
		
		if (ocjena > 1 && _ucenici[indeksUcenika].GetTelefon() != not_set) {
			thread slanjeSMS(&Skola::PosaljiSMS, this, aktivnost.GetRazred(), ocjena);
			slanjeSMS.join();
		}

		return true;
	}

	void PosaljiSMS(Razred razred, float ocjena) {
		mrPoliceman.lock();
		this_thread::sleep_for(chrono::seconds(2));
		cout << "Uspjesno ste okoncali aktivnosti u okviru " << razred << " razreda sa prosjecnom ocjenom " << ocjena << "." << endl;
		mrPoliceman.unlock();
	}


	//pair<Polaznik*, float> par = gimnazijaMostar.GetNajboljegUcenika();
	pair<Polaznik*, float> GetNajboljegUcenika() {
		Ucenik temp;
		float prosjek = 0.0f;
		for (int i = 0; i < _ucenici.size(); i++) {
			prosjek = max(prosjek, _ucenici[i].getProsjekUcenika());
			if (prosjek == _ucenici[i].getProsjekUcenika())
				temp = _ucenici[i];
		}
		return make_pair(new Ucenik(temp), prosjek);
	}


	/*U fajl (npr. Gimnazija.txt) upisati podatke (podatke upisati kao obicni tekst) o skoli i svim ucenicima.
	Nakon upisa, potrebno je ispisati sadrzaj fajla. Parametar tipa bool oznacava da li ce ranije dodani sadrzaj fajla prethodno biti pobrisan*/


	bool SpasiUFajl(string imeFajla, bool prepisi = false) {
		if (prepisi) {
			ofstream fajlUpis(imeFajla);
			fajlUpis << "Skola: " << GetNaziv() << endl;
			fajlUpis << "Ucenici: " << endl;
			for (size_t i = 0; i < _ucenici.size(); i++)
				fajlUpis << _ucenici[i] << endl;
			cout << *this;
			fajlUpis.close();
		}
		else {
			ofstream fajlUpis(imeFajla, ios::app);
			fajlUpis << "Skola: " << GetNaziv() << endl;
			fajlUpis << "Ucenici: " << endl;
			for (size_t i = 0; i < _ucenici.size(); i++)
				fajlUpis << _ucenici[i] << endl;
			cout << *this;
			fajlUpis.close();
		}
		return true;
	}
};


/*u slucaju da je ucenik uspjesno (ocjenom vecom od 1) realizovao aktivnosti na nivou odredjenog razreda, te posjeduje validan broj telefona,
	u okviru zasebnog thread-a se salje SMS sa sadrzajem "Uspjesno ste okoncali aktivnosti u okviru X razreda sa prosjecnom ocjenom X.X"*/

int main() {
	Kolekcija<int, int, 10> kolekcija1(DESC, false);
	try {
		kolekcija1.AddElement(1, 2);
		//dupliranje elemenata nije dozvoljeno
		kolekcija1.AddElement(1, 2);
	}
	catch (exception& ex) {
		cout << ex.what();
	}

	/*nakon svakog dodavanja, elemente sortirati prema T1 i vrijednosti atributa _sortiranje*/
	for (size_t i = 1; i < kolekcija1.GetMax() - 1; i++)
		kolekcija1.AddElement(rand() % 30, rand() % 30);

	cout << kolekcija1 << endl;

	try {
		//prekoracen maksimalan broj elemenata
		kolekcija1.AddElement(rand() % 30, rand() % 30);
	}
	catch (exception& ex) {
		cout << ex.what();
	}
	cout << kolekcija1 << endl;

	Kolekcija<int, int, 10> kolekcija2(kolekcija1);
	cout << kolekcija2 << endl;

	Skola gimnazijaMostar("GIMNAZIJA MOSTAR");
	//dodaje novog ucenika u skolu
	gimnazijaMostar("Jasmin Azemovic", "+387(61)111-222");
	gimnazijaMostar("Adel Handzic", "+387(61)333-444");

	/*
	koristeci regex, osigurati sljedeci format za broj telefona: +387(6X)XXX-XXX ili +387 6X XXX-XXX
	onemoguciti pojavljivanje samo jedne zagrade, a ukoliko format nije adekvatna koristiti vrijednost not_set
	*/
	gimnazijaMostar("Telefon NotValidFormat", "387 61)333-444");

	try {
		/*onemoguciti dodavanje ucenika sa istim imenom i prezimenom ili brojem telefona*/
		gimnazijaMostar("Adel Handzic", "+387(61)333-444");
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Priprema za takmicenje iz Matematike koje se odrzava u Konjicu 07.02.2019")))
		cout << "Aktivnost uspjesno dodana1" << endl;
	/*na nivou svakog razreda se mogu evidentirati maksimalno 4 aktivnosti, a takodjer, na nivou razreda se ne smiju ponavljati aktivnosti iz istog predmeta*/
	if (!gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", MATEMATIKA, Aktivnost(I, 4, "Aktivnosti iz matematike")))
		cout << "Aktivnost nije uspjesno dodana2" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", HEMIJA, Aktivnost(I, 5, "Priprema otopina za vjezbe iz predmeta Hemija")))
		cout << "Aktivnost uspjesno dodana3" << endl;
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", FIZIKA, Aktivnost(I, 4, "Analiza stepena apsorpcije materijala ")))
		cout << "Aktivnost uspjesno dodana4" << endl;
	/*u slucaju da je ucenik uspjesno (ocjenom vecom od 1) realizovao aktivnosti na nivou odredjenog razreda, te posjeduje validan broj telefona,
	u okviru zasebnog thread-a se salje SMS sa sadrzajem "Uspjesno ste okoncali aktivnosti u okviru X razreda sa prosjecnom ocjenom X.X"*/
	if (gimnazijaMostar.DodajAktivnost("Jasmin Azemovic", GEOGRAFIJA, Aktivnost(I, 4, "Izrada 5 reljefa Mostara")))
		cout << "Aktivnost uspjesno dodana5" << endl;
	if (gimnazijaMostar.DodajAktivnost("Adel Handzic", MATEMATIKA, Aktivnost(I, 5, "Izrada skripte na temu integralni racun")))
		cout << "Aktivnost uspjesno dodana6" << endl;

	//ispisuje sve ucenike i njihove aktivnosti
	cout << gimnazijaMostar << endl;


	pair<Polaznik*, float> par = gimnazijaMostar.GetNajboljegUcenika();
	cout << "Najbolji ucenik je " << par.first->GetImePrezime() << " sa prosjekom " << par.second << endl;

	/*U fajl (npr. Gimnazija.txt) upisati podatke (podatke upisati kao obicni tekst) o skoli i svim ucenicima.
	Nakon upisa, potrebno je ispisati sadrzaj fajla. Parametar tipa bool oznacava da li ce ranije dodani sadrzaj fajla prethodno biti pobrisan*/

	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt"))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;
	if (gimnazijaMostar.SpasiUFajl("Gimnazija.txt", true))
		cout << "Podaci o ucenicima uspjesno pohranjeni u fajl" << endl;

	cin.get();
	system("pause>0");
	return 0;
}