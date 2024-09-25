#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <mutex>
#include <thread>

using namespace std;

mutex mrPoliceman;

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
ostream& operator<<(ostream& COUT, const Pojas& obj) {
	switch (obj) {
	case BIJELI: COUT << "BIJELI"; break;
	case ZUTI: COUT << "ZUTI"; break;
	case NARANDZASTI: COUT << "NARANDZASTI"; break;
	case ZELENI: COUT << "ZELENI"; break;
	case PLAVI: COUT << "PLAVI"; break;
	case SMEDJI: COUT << "SMEDJI"; break;
	case CRNI: COUT << "CRNI"; break;
	default:
		break;
	}
	return COUT;
}
const int brojTehnika = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";
char* GetNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
template<class T1, class T2, int max = 10>
class Kolekcija {
	T1* _elementi1[max] = { nullptr };
	T2* _elementi2[max] = { nullptr };
	int* _trenutno = nullptr;
public:
	Kolekcija() {
		_trenutno = new int(0);
		setElementi();
	}
	Kolekcija(const Kolekcija& obj) {
		setTrenutno(obj.getTrenutno());
		setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this != &obj)
		{
			setTrenutno(obj.getTrenutno());
			setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
		}
		return *this;
	}
	~Kolekcija() {
		for (size_t i = 0; i < *_trenutno; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}

	// moje metode

	T1** getElementi1() const { return (T1**)_elementi1; }
	T2** getElementi2() const { return (T2**)_elementi2; }

	void setTrenutno(int tren) {
		if (_trenutno == nullptr)
			_trenutno = new int;
		*_trenutno = tren;
	}

	void Dealociraj() {
		for (size_t i = 0; i < *_trenutno; i++) {
			delete _elementi1[i]; _elementi1[i] = nullptr;
			delete _elementi2[i]; _elementi2[i] = nullptr;
		}
	}

	void setElementi(int trenutno = 0, T1** elementi1 = nullptr, T2** elementi2 = nullptr) {
		Dealociraj();
		setTrenutno(0);

		if (elementi1 != nullptr && elementi2 != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				AddElement(*elementi1[i], *elementi2[i]);
			}
		}
	}

	void AddElement(const T1& el1, const T2& el2, int lokacija = -1) {
		if (getTrenutno() >= max)
			throw exception("Kolekcija je popunjena!");
		_elementi1[getTrenutno()] = new T1(el1);
		_elementi2[getTrenutno()] = new T2(el2);
		if (lokacija != -1) {
			for (int i = getTrenutno(); i > lokacija; i--) {
				swap(_elementi1[i], _elementi1[i - 1]);
				swap(_elementi2[i], _elementi2[i - 1]);
			}
		}
		setTrenutno(getTrenutno() + 1);
	}

	void RemoveAt(int lokacija) {
		for (int i = lokacija; i < getTrenutno() - 1; i++) {
			swap(_elementi1[i], _elementi1[i + 1]);
			swap(_elementi2[i], _elementi2[i + 1]);
		}
		setTrenutno(getTrenutno() - 1);
		delete _elementi1[getTrenutno()]; _elementi1[getTrenutno()] = nullptr;
		delete _elementi2[getTrenutno()]; _elementi2[getTrenutno()] = nullptr;
	}

	T1& operator[](const T2& el2) {
		for (int i = 0; i < getTrenutno(); i++) {
			if (getElement2(i) == el2)
				return getElement1(i);
		}
	}
};
class Datum {
	int* _dan = nullptr, * _mjesec = nullptr, * _godina = nullptr;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}
	Datum(const Datum& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}
	Datum& operator=(const Datum& obj) {
		if (this != &obj)
		{
			_dan = new int(*obj._dan);
			_mjesec = new int(*obj._mjesec);
			_godina = new int(*obj._godina);
		}
		return *this;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Datum& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
		return COUT;
	}

	int toInt() const { return *_dan + (*_mjesec) * 30.41 + (*_godina) * 365.24; }

};

bool operator==(const Datum& d1, const Datum& d2) { return d1.toInt() == d2.toInt(); }
bool operator!=(const Datum& d1, const Datum& d2) { return !(d1 == d2); }
bool operator>(const Datum& d1, const Datum& d2) { return d1.toInt() > d2.toInt(); }
bool operator<(const Datum& d1, const Datum& d2) { return d1.toInt() < d2.toInt(); }
int getDateDiff(const Datum& d1, const Datum& d2) {
	return abs(d1.toInt() - d2.toInt());
}
class Tehnika {
	char* _naziv = nullptr;
	//int se odnosi na ocjenu u opsegu od 1 - 5, a Datum na datum kada je ocijenjena odredjena tehnika
	Kolekcija<int, Datum*, brojTehnika> _ocjene;
public:
	Tehnika(const char* naziv) {
		_naziv = GetNizKaraktera(naziv);
	}
	Tehnika(const Tehnika& obj) {
		delete[] _naziv;
		_naziv = GetNizKaraktera(obj.GetNaziv());
		_ocjene = obj._ocjene;
	}
	Tehnika& operator=(const Tehnika& obj) {
		if (this != &obj)
		{
			delete[] _naziv;
			_naziv = GetNizKaraktera(obj.GetNaziv());
			_ocjene = obj._ocjene;
		}
		return *this;
	}
	~Tehnika() {
		delete[] _naziv; _naziv = nullptr;
	}
	const char* GetNaziv() const { return _naziv; }
	Kolekcija<int, Datum*, brojTehnika>& GetOcjene() { return _ocjene; }
	Kolekcija<int, Datum*, brojTehnika> constGetOcjene() const { return _ocjene; }

	friend ostream& operator<<(ostream& COUT, const Tehnika& obj) {
		COUT << crt << "Naziv tehnike: " << obj.GetNaziv() << endl;
		COUT << "Ocjene:\n";
		for (int i = 0; i < obj._ocjene.getTrenutno(); i++) {
			COUT << "\t" << obj._ocjene.getElement1(i) << " : " << *obj._ocjene.getElement2(i) << endl;
		}
		COUT << "Prosjecna ocjena: " << obj.getProsjecnaOcjenaZaTehniku() << crt;
		return COUT;
	}

	float getProsjecnaOcjenaZaTehniku() const {
		if (_ocjene.getTrenutno() == 0)
			return 0.0f;
		float suma = 0.0f;
		for (int i = 0; i < _ocjene.getTrenutno(); i++) {
			suma += _ocjene.getElement1(i);
		}
		return suma / _ocjene.getTrenutno();
	}

	/*svaka tehnika moze imati vise ocjena tj. moze se polagati u vise
   navrata.
	- razmak izmedju polaganja dvije tehnike mora biti najmanje 3 dana
	- nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec
   evidentirane (bez obzira sto je stariji od 3 dana)
	*/

	bool AddOcjena(int ocjena, Datum& datum) {
		if (_ocjene.getTrenutno() > 0) {
			if (getDateDiff(*_ocjene.getElement2(_ocjene.getTrenutno() - 1), datum) < 3)
				return false;
		}
		for (int i = 0; i < _ocjene.getTrenutno(); i++) {
			if (datum < *_ocjene.getElement2(i))
				return false;
		}
		_ocjene.AddElement(ocjena, new Datum(datum));
		return true;
	}
};

bool operator==(const Tehnika& t1, const Tehnika& t2) {
	if (strcmp(t1.GetNaziv(), t2.GetNaziv()) != 0 || t1.constGetOcjene().getTrenutno() != t2.constGetOcjene().getTrenutno())
		return false;
	for (int i = 0; i < t1.constGetOcjene().getTrenutno(); i++) {
		if (t1.constGetOcjene().getElement1(i) != t2.constGetOcjene().getElement1(i) ||
			*t1.constGetOcjene().getElement2(i) != *t2.constGetOcjene().getElement2(i))
			return false;
	}
	return true;
}

class Polaganje {
	Pojas _pojas;
	vector<Tehnika*> _polozeneTehnike;
public:
	Polaganje(Pojas pojas = BIJELI) {
		_pojas = pojas;
	}
	Polaganje(const Polaganje& obj) {
		_pojas = obj._pojas;
		_polozeneTehnike = obj._polozeneTehnike;	// moguce pucanje	?
	}
	~Polaganje() {
		for (size_t i = 0; i < _polozeneTehnike.size(); i++) {
			delete _polozeneTehnike[i];
			_polozeneTehnike[i] = nullptr;
		}
	}
	vector<Tehnika*>& GetTehnike() { return _polozeneTehnike; }
	Pojas GetPojas() { return _pojas; }
	friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
		COUT << obj._pojas << endl;
		for (size_t i = 0; i < obj._polozeneTehnike.size(); i++)
			COUT << *obj._polozeneTehnike[i];
		return COUT;
	}

	float getProsjecnaOcjenaZaPolaganje() const {
		if (_polozeneTehnike.size() == 0)
			return 0.0f;
		float suma = 0.0f; int brojac = 0;
		for (int i = 0; i < _polozeneTehnike.size(); i++) {
			for (int j = 0; j < _polozeneTehnike[i]->GetOcjene().getTrenutno(); j++) {
				suma += _polozeneTehnike[i]->GetOcjene().getElement1(j);
				brojac++;
			}
		}
		return brojac == 0 ? 0 : suma / brojac;
	}
};

/*
za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
- najmanje 7 znakova
- velika i mala slova
- najmanje jedan broj
- najmanje jedan specijalni znak
 za provjeru validnosti lozinke koristiti globalnu funkciju
ValidirajLozinku, a unutar nje regex metode.
 validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u
slucaju da nije validna
 postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
 */

bool ValidirajLozinku(string lozinka) {
	return regex_search(lozinka, regex("(?=.*.{7,})(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)(?=.*\\W)"));
}

class Korisnik {
	char* _imePrezime = nullptr;
	string _emailAdresa;
	string _lozinka;
public:
	Korisnik(const char* imePrezime, string emailAdresa, string lozinka) {
		_imePrezime = GetNizKaraktera(imePrezime);
		_emailAdresa = emailAdresa;
		_lozinka = (ValidirajLozinku(lozinka)) ? lozinka : NIJE_VALIDNA;
	}
	Korisnik(const Korisnik& obj) {
		delete[] _imePrezime;
		_imePrezime = GetNizKaraktera(obj.GetImePrezime());
		_emailAdresa = obj._emailAdresa;
		_lozinka = obj._lozinka;
	}
	Korisnik& operator=(const Korisnik& obj) {
		if (this != &obj)
		{
			delete[] _imePrezime;
			_imePrezime = GetNizKaraktera(obj.GetImePrezime());
			_emailAdresa = obj._emailAdresa;
			_lozinka = obj._lozinka;
		}
		return *this;
	}
	virtual ~Korisnik() { 
		cout << crt << "DESTRUKTOR -> Korisnik" << crt;
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	string GetEmail() { return _emailAdresa; }
	string GetLozinka() { return _lozinka; }
	const char* GetImePrezime() const { return _imePrezime; }
};

class KaratePolaznik : public Korisnik {
	vector<Polaganje*> _polozeniPojasevi;
public:
	KaratePolaznik(const char* imePrezime, string emailAdresa, string
		lozinka) :Korisnik(imePrezime, emailAdresa, lozinka) {
		for (int i = 0; i < brojTehnika; i++) {
			_polozeniPojasevi.push_back(new Polaganje((Pojas)i));
		}
	}
	KaratePolaznik(const KaratePolaznik& obj) : Korisnik(obj) {
		for (int i = 0; i < brojTehnika; i++) {
			_polozeniPojasevi.push_back(new Polaganje(*obj._polozeniPojasevi[i]));		// kopira pojaseve, moguce pucanje	?
		}
	}
	KaratePolaznik& operator=(const KaratePolaznik& obj) {
		if (this != &obj) {
			(Korisnik&)(*this) = obj;
			for (int i = 0; i < brojTehnika; i++) {
				_polozeniPojasevi.push_back(new Polaganje(*obj._polozeniPojasevi[i]));		// kopira pojaseve, moguce pucanje	?
			}
		}
		return *this;
	}
	~KaratePolaznik() {
		cout << crt << "DESTRUKTOR -> KaratePolaznik" << crt;
		for (size_t i = 0; i < _polozeniPojasevi.size(); i++) {
			delete _polozeniPojasevi[i];
			_polozeniPojasevi[i] = nullptr;
		}
	}
	friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
		COUT << "Ime i prezime polaznika: " << obj.GetImePrezime() << "\nEmail polaznika: " << obj.GetEmail() << "\nLozinka polaznika: " <<
			obj.GetLozinka() << endl;
		for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
			COUT << *obj._polozeniPojasevi[i] << endl;
		return COUT;
	}
	vector<Polaganje*>& GetPolozeniPojasevi() { return _polozeniPojasevi; }

	// moje metode
	
	float getUkupniProsjek() const {
		float suma = 0.0f; int brojac = 0;
		for (int i = 0; i < _polozeniPojasevi.size(); i++) {
			for (int j = 0; j < _polozeniPojasevi[i]->GetTehnike().size(); j++) {
				for (int k = 0; k < _polozeniPojasevi[i]->GetTehnike()[j]->GetOcjene().getTrenutno(); k++) {
					suma += _polozeniPojasevi[i]->GetTehnike()[j]->GetOcjene().getElement1(k);
					brojac++;
				}
			}
		}
		return brojac == 0 ? 0 : suma / brojac;
	}

	/*
	svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju tehnike)
	sve tehnike na nivou jednog pojasa (ZUTI, ZELENI ... ) se evidentiraju unutar istog objekta tipa Polaganje, tom prilikom onemoguciti:

	- dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
	- dodavanje tehnika za visi pojas ako prethodni pojas nema evidentirane najmanje 3 tehnike ili nema prosjecnu ocjenu svih tehnika vecu od 3.5
	(onemoguciti dodavanje tehnike za NARANDZASTI ako ne postoji najmanje 3 tehnike za ZUTI pojas i njihov prosjek je veci od 3.5)

	funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/

	bool AddTehniku(Pojas pojas, Tehnika& tehnika) {
		for (int i = 0; i < _polozeniPojasevi[pojas]->GetTehnike().size(); i++) {
			if (*_polozeniPojasevi[pojas]->GetTehnike()[i] == tehnika)
				return false;	// ne smiju biti iste tehnike na nivou jednog pojasa
		}
		if (pojas != ZUTI) {
			if (_polozeniPojasevi[pojas - 1]->GetTehnike().size() < 3)
				return false;	// moraju biti bar 3 tehnike na prethodnom pojasu
			if (_polozeniPojasevi[pojas - 1]->getProsjecnaOcjenaZaPolaganje() < 3.5)
				return false;	// prosjecna ocjena veca od 3.5
		}

		_polozeniPojasevi[pojas]->GetTehnike().push_back(new Tehnika(tehnika));		// &

		thread SlanjeEmaila(&KaratePolaznik::PosaljiEmail, this, tehnika.GetNaziv(), pojas, _polozeniPojasevi[pojas]->getProsjecnaOcjenaZaPolaganje(), getUkupniProsjek());
		SlanjeEmaila.join();

		return true;
	}

	void PosaljiEmail(const char* nazivTehnike, Pojas pojas, float prosjekZaPojas, float ukupniProsjek) {
		mrPoliceman.lock();
		this_thread::sleep_for(chrono::seconds(2));
		cout << crt << "FROM: info@karate.ba\nTO: " << GetEmail() << "\n";
		cout << "Postovani " << GetImePrezime() << ", evidentirana vam je " << nazivTehnike << " za " << pojas << " pojas.\n";
		cout << "Dosadasnji uspjeh (prosjek ocjena) na pojasu " << pojas << " iznosi " << prosjekZaPojas
			<< ", a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi " << ukupniProsjek  << ".\n";
		cout << "Fakultet informacijskih tehnologija\nPozdrav\nKARATE Team." << crt;
		mrPoliceman.unlock();
	}

	/*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje
   email sa porukom:
	FROM:info@karate.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirana vam je thenika X za Y pojas.
   Dosadasnji uspjeh (prosjek ocjena) na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima
   iznosi Z.
   Fakultet informacijskih tehnologija
   Pismeni dio ispita
   Pozdrav.
	KARATE Team.
	slanje email poruka implemenitrati koristeci zasebne thread-ove.
	*/
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite ulogu operatora const_cast?\n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Ukratko opisite redoslijed kreiranja objekta bazne klase u slucaju visestrukog nasljedjivanja(prilikom instanciranja objekta najizvedenije klase), te koja su moguca rjesenja najznacajnijih problema u tom kontekstu ? \n";
	return "Odgovor -> Kod visestrukog nasljedjivanja, postoji problem koji se tice moguceg dupliranja podataka koji pripadaju baznoj klasi. Npr. ako imamo baznu klasu A i izvedene klase B i C, koje nasljedjuju klasu A, te na kraju klasu D koja nasljedjuje izvedene klase B i C, doci ce do dupliranja podataka bazne klase, jer klase B i C, svaka posebno, kreiraju u sklopu sebe podobjekat klase A. Nasljedjivanjem klasa B i C, od strane klase D, taj objekat onda ima duple podatke. Redoslijed je dakle sljedeci: objekat A u sklopu B, ostatak B, objekat A u sklopu C, ostatak C, objekat A u sklopu D, objekat B u sklopu D, objekat C u sklopu D, ostatak D. Moguce rjesenje ovog problema je virtuelno nasljedjivanje. Klase B i C bi prema tome virtuelno naslijedile klasu A. Na taj nacin, moze se izbjeci dupliranje podataka. Obaveza kreiranja baznog objekta A se u tom slucaju predaje najizvedenijem objektu, tj. objektu D, tako da u header-u konstruktora D navodimo konstruktore A, B i C.";
}
void main() {
	//cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
	Datum datum19062020(19, 6, 2020),
		datum20062020(20, 6, 2020),
		datum30062020(30, 6, 2020),
		datum05072020(5, 7, 2020);
	int kolekcijaTestSize = 10;
	Kolekcija<int, int> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);
	cout << kolekcija1 << endl;
	try {
		/*metoda AddElement baca izuzetak u slucaju da se pokusa
		dodati vise od maksimalnog broja elemenata*/
		kolekcija1.AddElement(11, 11);
	}
	catch (exception& err) {
		cout << crt << "Greska -> " << err.what() << crt;
	}
	cout << kolekcija1 << crt;
	kolekcija1.RemoveAt(2);
	/*uklanja par (T1 i T2) iz kolekcije koji se nalazi na lokaciji sa
   proslijedjenim indeksom.
	nakon uklanjanja vrijednosti onemoguciti pojavu praznog prostora unutar
   kolekcije tj.
	pomjeriti sve elemente koji se nalaze nakon proslijedjene lokacije za
   jedno mjesto unazad
	npr. ako unutar kolekcije postoje elementi
	0 0
	1 1
	2 2
	3 3
	nakon uklanjanja vrijednosti na lokaciji 1, sadrzaj kolekcije ce biti
   sljedeci
	0 0
	2 2
	3 3
	*/
	cout << kolekcija1 << crt;
	kolekcija1.AddElement(9, 9, 2);
	/*funkciji AddElement se, kao treci parametar, moze proslijediti i
   lokacija na koju se dodaju
	nove vrijednosti pri cemu treba zadrzati postojece vrijednosti pomjerene
   za jedno mjesto unaprijed
	u odnosu na definisanu lokaciju npr. ako unutar kolekcije postoje
   elementi
	0 0
	1 1
	2 2
	3 3
	nakon dodavanja vrijednosti 9 i 9 na lokaciju 1, sadrzaj kolekcije ce
   biti sljedeci
	0 0
	9 9
	1 1
	2 2
   3 3
	*/
	cout << kolekcija1 << crt;
	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija1 << crt;
	//na osnovu vrijednosti T2 mijenja vrijednost T1.
	kolekcija1[9] = 2;
	/* npr.ako unutar kolekcije postoje elementi:
	0 0
	9 9
	1 1
	2 2
	3 3
	nakon promjene vrijednosti sadrzaj kolekcije ce biti sljedeci
	0 0
	2 9
	1 1
	2 2
	3 3
	*/
	Tehnika choku_zuki("choku_zuki"),
		gyaku_zuki("gyaku_zuki"),
		kizami_zuki("kizami_zuki"),
		oi_zuki("oi_zuki");
	/*svaka tehnika moze imati vise ocjena tj. moze se polagati u vise
   navrata.
	- razmak izmedju polaganja dvije tehnike mora biti najmanje 3 dana
	- nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec
   evidentirane (bez obzira sto je stariji od 3 dana)
	*/
	if (choku_zuki.AddOcjena(1, datum19062020))
		cout << "Ocjena evidentirana!" << endl;
	if (!choku_zuki.AddOcjena(5, datum20062020))
		cout << "Ocjena NIJE evidentirana!" << endl;
	if (choku_zuki.AddOcjena(5, datum30062020))
		cout << "Ocjena evidentirana!" << endl;
	// ispisuje: naziv tehnike, ocjene (zajedno sa datumom) i prosjecnu ocjenu za tu tehniku
		// ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0
	cout << choku_zuki << endl;
	if (ValidirajLozinku("john4Do*e"))
		cout << "OK" << crt;
	if (!ValidirajLozinku("john4Doe"))
		cout << "Specijalni znak?" << crt;
	if (!ValidirajLozinku("jo*4Da"))
		cout << "7 znakova?" << crt;
	if (!ValidirajLozinku("4jo-hnoe"))
		cout << "Veliko slovo?" << crt;
	if (ValidirajLozinku("@john2Doe"))
		cout << "OK" << crt;
	/*
	za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
	- najmanje 7 znakova
	- velika i mala slova
	- najmanje jedan broj
   - najmanje jedan specijalni znak
	za provjeru validnosti lozinke koristiti globalnu funkciju
   ValidirajLozinku, a unutar nje regex metode.
	validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u
   slucaju da nije validna
	postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
	*/

	Korisnik* jasmin = new KaratePolaznik("Jasmin Azemovic",
		"jasmin@karate.ba", "j@sm1N*");
	Korisnik* adel = new KaratePolaznik("Adel Handzic", "adel@edu.karate.ba",
		"4Ade1*H");
	Korisnik* lozinkaNijeValidna = new KaratePolaznik("John Doe",
		"john.doe@google.com", "johndoe");
	
	/*
	svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju tehnike)
	sve tehnike na nivou jednog pojasa (ZUTI, ZELENI ... ) se evidentiraju unutar istog objekta tipa Polaganje, tom prilikom onemoguciti:
	
	- dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
	- dodavanje tehnika za visi pojas ako prethodni pojas nema evidentirane najmanje 3 tehnike ili nema prosjecnu ocjenu svih tehnika vecu od 3.5
	(onemoguciti dodavanje tehnike za NARANDZASTI ako ne postoji najmanje 3 tehnike za ZUTI pojas i njihov prosjek je veci od 3.5)

	funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	*/

	//doraditi klase da nacin da omoguce izvrsenje naredne linije koda
	KaratePolaznik* jasminPolaznik = dynamic_cast<KaratePolaznik*>(jasmin);
	if (jasminPolaznik != nullptr) {
		if (jasminPolaznik->AddTehniku(ZUTI, gyaku_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		//ne treba dodati kizami_zuki jer ne postoje evidentirane 3 tehnike za ZUTI pojas
		if (!jasminPolaznik->AddTehniku(NARANDZASTI, kizami_zuki))
			cout << "Tehnika NIJE uspjesno dodana!" << crt;
		if (jasminPolaznik->AddTehniku(ZUTI, kizami_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		if (jasminPolaznik->AddTehniku(ZUTI, oi_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		if (jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
			cout << "Tehnika uspjesno dodan!" << crt;
		//ne treba dodati choku_zuki jer je vec dodana za zuti pojas
		if (!jasminPolaznik->AddTehniku(ZUTI, choku_zuki))
			cout << "Tehnika NIJE uspjesno dodana!" << crt;
		//ispisuje sve dostupne podatke o karate polazniku
		cout << *jasminPolaznik << crt;
	}

	/*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje
   email sa porukom:
	FROM:info@karate.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirana vam je thenika X za Y pojas.
   Dosadasnji uspjeh (prosjek ocjena)
	na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima
   iznosi Z.
   Fakultet informacijskih tehnologija
   Pismeni dio ispita
   Pozdrav.
	KARATE Team.
	slanje email poruka implemenitrati koristeci zasebne thread-ove.
	*/
	
	//osigurati da se u narednim linijama poziva i destruktor klase KaratePolaznik
	delete jasmin;
	delete adel;
	delete lozinkaNijeValidna;
	cin.get();
	system("pause>0");
}