#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include<mutex>
#include<future>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
****************************************************************************/

const char* crt = "\n-------------------------------------------\n";
const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";
const int min_polgavlja = 3;
const int min_karaktera_po_poglavlju = 30;

char* AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1* _elementi1 = nullptr;
	T2* _elementi2 = nullptr;
	int _trenutno;
public:
	Kolekcija() {
		_trenutno = 0;
		setElementi();
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutno = obj._trenutno;
		setElementi(obj.getTrenutno(), obj.getElementi1Pok(), obj.getElementi2Pok());
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if(this!=&obj){
			_trenutno = obj._trenutno;
			setElementi(obj.getTrenutno(), obj.getElementi1Pok(), obj.getElementi2Pok());
		}
		return *this;
	}
	~Kolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi1 = nullptr;
	}
	T1* getElementi1Pok() const { return _elementi1; }
	T2* getElementi2Pok() const { return _elementi2; }
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() const { return _trenutno; }

	friend ostream& operator<<(ostream& COUT, Kolekcija<T1, T2>& obj) {
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

	void AddElement(const T1& el1, const T2& el2) {
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
};
class Poglavlje {
	char* _naslov = nullptr;
	char* _sadrzaj = nullptr;
	bool _prihvaceno;
	int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
public:
	Poglavlje(const char* naslov = nullptr, const char* sadrzaj = nullptr)
		:_ocjena(0), _prihvaceno(false) {
		_naslov = AlocirajNizKaraktera(naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
	}
	Poglavlje(const Poglavlje& obj) {
		setNaslov(obj.GetNaslov());
		setSadrzaj(obj.GetSadrzaj());
		_prihvaceno = obj._prihvaceno;
		_ocjena = obj._ocjena;
	}
	Poglavlje& operator=(const Poglavlje& obj) {
		if(this!=&obj){
			setNaslov(obj.GetNaslov());
			setSadrzaj(obj.GetSadrzaj());
			_prihvaceno = obj._prihvaceno;
			_ocjena = obj._ocjena;
		}
		return *this;
	}
	Poglavlje() {
		delete[] _naslov; _naslov = nullptr;
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	friend ostream& operator<<(ostream& COUT, Poglavlje& obj) {
		if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
			return COUT;
		COUT << endl << obj._naslov << endl << obj._sadrzaj << endl;
		if (obj._prihvaceno)
			COUT << "Ocjena: " << obj._ocjena << endl;;
		return COUT;
	}
	char* GetNaslov() const { return _naslov; }
	char* GetSadrzaj() const { return _sadrzaj; }
	bool GetPrihvaceno() const { return _prihvaceno; }
	int GetOcjena() const { return _ocjena; }

	void setNaslov(const char* source) {
		delete[] _naslov;
		_naslov = AlocirajNizKaraktera(source);
	}
	void setSadrzaj(const char* source) {
		delete[] _sadrzaj;
		_sadrzaj = AlocirajNizKaraktera(source);
	}

	void setOcjena(int ocjena) {
		_ocjena = ocjena;
	}

	void setPrihvaceno(bool prihv) {
		_prihvaceno = prihv;
	}
};

class ZavrsniRad {
	char* _tema = nullptr;
	vector<Poglavlje> _poglavljaRada;
	string _datumOdbrane;
	float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
public:
	ZavrsniRad(const char* nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
		_tema = AlocirajNizKaraktera(nazivTeme);
	}

	ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
		_tema = AlocirajNizKaraktera(org._tema);
	}

	ZavrsniRad& operator=(const ZavrsniRad& org) {
		if(this!=&org){
			setTema(org.GetNazivTeme());
			_poglavljaRada = org._poglavljaRada;
			_datumOdbrane = org._datumOdbrane;
			_konacnaOcjena = org._konacnaOcjena;
		}
		return *this;
	}

	~ZavrsniRad() {
		delete[] _tema; _tema = nullptr;
	}
	char* GetNazivTeme() const { return _tema; }
	vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
	string GetDatumOdbrane() const { return _datumOdbrane; }
	float GetOcjena() const { return _konacnaOcjena; }

	void SetDatumOdbrane(string datumOdbrane) { _datumOdbrane = datumOdbrane; }
	void setPoglavljaRada(vector<Poglavlje> poglavlja) {
		_poglavljaRada = poglavlja;
	}
	void setKonacnaOcjena(float kOcjena) {
		_konacnaOcjena = kOcjena;
	}

	friend ostream& operator<<(ostream& COUT, ZavrsniRad& obj) {
		COUT << "Tema rada: " << obj._tema << endl;
		COUT << "Sadrzaj: " << endl;
		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
			COUT << obj._poglavljaRada[i] << endl;
		COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Ocjena: " << obj._konacnaOcjena << endl;
		return COUT;
	}

	void setTema(const char* source) {
		delete[] _tema;
		_tema = AlocirajNizKaraktera(source);
	}

	float formirajKonacnuOcjenu() {
		if (_poglavljaRada.size() == 0)
			return 0;
		float suma = 0.0f;
		for (int i = 0; i < _poglavljaRada.size(); i++) {
			suma += _poglavljaRada[i].GetOcjena();
		}
		return suma / _poglavljaRada.size();
	}

	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
	//parametri: nazivPoglavlja, sadrzajPoglavlja

	pair<bool,int> postojiNaslov(const char* naslov) {
		for (int i = 0; i < _poglavljaRada.size(); i++) {
			if (strcmp(_poglavljaRada[i].GetNaslov(), naslov) == 0)
				return make_pair(true,i);
		}
		return make_pair(false, -1);
	}

	void DodajPoglavlje(const char* nazivPoglavlja = "Haris", const char* sadrzajPoglavlja = "Velispahic") {
		if (postojiNaslov(nazivPoglavlja).first) {
			int index = postojiNaslov(nazivPoglavlja).second;
			int size = strlen(_poglavljaRada[index].GetSadrzaj()) + strlen(sadrzajPoglavlja) + 2;
			char* temp = new char[size];
			strcpy_s(temp, size, _poglavljaRada[index].GetSadrzaj());
			strcat_s(temp, size, " ");
			strcat_s(temp, size, sadrzajPoglavlja);
			_poglavljaRada[index].setSadrzaj(temp);
		}
		else {
			_poglavljaRada.push_back(Poglavlje(nazivPoglavlja, sadrzajPoglavlja));
		}
	}

	/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja, dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10) onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji, funkcija baca izuzetak sa odgovarajucom porukom*/
		//parametri:nazivPoglavlja, ocjena

	// multimedijalni.OcijeniPoglavlje("Uvod", 8);

	void OcijeniPoglavlje(const char* naslov, int ocjena) {
		if (ocjena < 1 || ocjena > 10)
			throw exception("Ocjena nije validna!");
		bool postojiPoglavlje = false;
		for (int i = 0; i < _poglavljaRada.size(); i++) {
			if (strcmp(naslov, _poglavljaRada[i].GetNaslov()) == 0) {
				postojiPoglavlje = true;
				_poglavljaRada[i].setOcjena(ocjena);
				if (ocjena < 6)
					_poglavljaRada[i].setPrihvaceno(false);
				else
					_poglavljaRada[i].setPrihvaceno(true);
			}
		}
		if (!postojiPoglavlje)
			throw exception("Uneseno poglavlje ne postoji!");
	}

	

};

class Osoba {
protected:
	string _imePrezime;
public:
	Osoba(string imePrezime) : _imePrezime(imePrezime) {}
	Osoba(const Osoba& obj) : _imePrezime(obj._imePrezime) {}
	Osoba& operator=(const Osoba& obj) {
		if(this!=&obj){
			_imePrezime = obj._imePrezime;
		}
		return *this;
	}
	string GetImePrezime() { return _imePrezime; }
	virtual void Info() = 0;
};

class Nastavnik : public Osoba{
	//Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog nastavnika
	Kolekcija<string, ZavrsniRad> _teme;
public:

	Nastavnik(string imePrezime) : Osoba(imePrezime){}
	Nastavnik(const Nastavnik& obj) : Osoba(obj) {
		_teme = obj._teme;
	}
	Nastavnik& operator=(const Nastavnik& obj) {
		if(this!=&obj){
			(Osoba&)(*this) = obj;
			_teme = obj._teme;
		}
		return *this;
	}

	Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };

	void Info() {
		cout << "Ime prezime: " << GetImePrezime() << endl;
		cout << "Mentorstva: " << endl;
		for (int i = 0; i < _teme.getTrenutno(); i++) {
			cout << _teme.getElement1(i) << " : " << _teme.getElement2(i) << endl;
		}
	}

	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu. zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
	sprijeciti dodavanje zavrsnih radova sa istom temom*/
	//parametri: brojIndeksa, zavrsniRad
	//if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))

	bool DodajZavrsniRad(string indeks, ZavrsniRad& zavrsniRad) {
		for (int i = 0; i < _teme.getTrenutno(); i++) {
			if (strcmp(zavrsniRad.GetNazivTeme(), _teme.getElement2(i).GetNazivTeme()) == 0)
				return false;
			if (_teme.getElement1(i) == indeks)
				return false;
		}
		_teme.AddElement(indeks, zavrsniRad);
		return true;
	}


	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
		1. zavrsni rad ima broj poglavlja veci od minimalnog
		2. svako poglavlje ima broj karaktera veci od minimalnog
		3. svako poglavlje je prihvaceno/odobreno
	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
*/

//parametri: brojIndeksa, datumOdbrane
	//ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");

	ZavrsniRad* ZakaziOdbranuRada(string indeks, string datum) {
		ZavrsniRad temp;
		bool prijavioRad = false, poglavljaPrihvacena = true, svakoPoglavljePrekoMinKaraktera = true;;
		for (int i = 0; i < _teme.getTrenutno(); i++) {
			if (indeks == _teme.getElement1(i)) {

				if (_teme.getElement2(i).GetPoglavlja().size() < min_polgavlja)
					return nullptr;

				temp.setTema(_teme.getElement2(i).GetNazivTeme());
				temp.setPoglavljaRada(_teme.getElement2(i).GetPoglavlja());
				temp.SetDatumOdbrane(datum);

				prijavioRad = true;
				float suma = 0.0f;
				for (int j = 0; j < _teme.getElement2(i).GetPoglavlja().size(); j++) {
					suma += _teme.getElement2(i).GetOcjena();
					if (!_teme.getElement2(i).GetPoglavlja()[j].GetPrihvaceno())
						poglavljaPrihvacena = false;
					if (strlen(_teme.getElement2(i).GetPoglavlja()[j].GetSadrzaj()) < min_karaktera_po_poglavlju)
						svakoPoglavljePrekoMinKaraktera = false;
				}
				if (_teme.getElement2(i).GetPoglavlja().size() == 0)
					temp.setKonacnaOcjena(0);
				else
					temp.setKonacnaOcjena(suma / _teme.getElement2(i).GetPoglavlja().size());

			}
		}
		if (!prijavioRad || !poglavljaPrihvacena || !svakoPoglavljePrekoMinKaraktera)
			return nullptr;

		return new ZavrsniRad(temp);
	}
	/*
	class ZavrsniRad {
		char* _tema = nullptr;
		vector<Poglavlje> _poglavljaRada;
		string _datumOdbrane;
		float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
	*/
};

mutex mutexObj;

string PosaljiEmail(string index, string imeMentora, float ocjena) {
	mutexObj.lock();
	this_thread::sleep_for(chrono::seconds(2));
	string sadrzajEmaila = "FROM: info@fit.ba\nTO: " + index + "@edu.fit.ba\n\nPostovani " + index + " uzimajuci u obzir cinjenicu da ste kod mentora " + imeMentora + " uspjesno odbranili rad sa ocjenom " + to_string(ocjena) + " cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzanu u na FIT - u 03.07.2019.godine.";
	/*cout << "FROM: info@fit.ba\nTO: " << index << "@edu.fit.ba\n\n";
	cout << "Postovani " << index << " uzimajuci u obzir cinjenicu da ste kod mentora " << imeMentora << " uspjesno odbranili rad sa ocjenom " <<
		ocjena << " cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzanu u na FIT - u 03.07.2019.godine." << endl;*/
	cout << sadrzajEmaila;
	mutexObj.unlock();
	return sadrzajEmaila;
}

string PosaljiPozivZaDodjeluNagrada(Nastavnik** nastavnici, int max, float ocjena) {
	bool mentorstvo = false;
	string sadrzajSvihEmailova;
	for (int i = 0; i < max; i++) {
		if (nastavnici[i]->GetTeme().getTrenutno() > 0)
			mentorstvo = true;
		for (int j = 0; j < nastavnici[i]->GetTeme().getTrenutno(); j++) {
			if (nastavnici[i]->GetTeme().getElement2(j).formirajKonacnuOcjenu() > ocjena) {
				string index = nastavnici[i]->GetTeme().getElement1(j);
				string imeMentora = nastavnici[i]->GetImePrezime();
				float ocjena = nastavnici[i]->GetTeme().getElement2(j).formirajKonacnuOcjenu();
				std::future<string> email = std::async(std::launch::async, PosaljiEmail, index, imeMentora, ocjena);
				sadrzajSvihEmailova += crt + email.get();
			}
		}
	}
	sadrzajSvihEmailova += crt;
	if (!mentorstvo)
		return not_set;
	return sadrzajSvihEmailova;
}

int main() {
	/*cout << crt << "UPLOAD RADA OBAVEZNO IZVRSITI U ODGOVARAJUCI FOLDER NA FTP SERVERU" << endl;
	cout << "U slucaju da je Upload folder prazan pritisnite tipku F5" << crt;*/

	const int max = 4;
	Nastavnik* nastavnici[max];

	nastavnici[0] = new Nastavnik("Denis Music");
	nastavnici[1] = new Nastavnik("Zanin Vejzovic");
	nastavnici[2] = new Nastavnik("Jasmin Azemovic");
	nastavnici[3] = new Nastavnik("Emina Junuz");
	//parametri: naziv zavrsnog rada
	ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
	ZavrsniRad podrsa_operaterima("Sistem za podršku rada kablovskog operatera");
	ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti bežičnih računarskih mreža");
	ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih ključeva");

	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
	//parametri: nazivPoglavlja, sadrzajPoglavlja
	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");
	multimedijalni.DodajPoglavlje("Zakljucak", "U ovom radu su predstavljeni osnovni koncepti i prakticna primjena...");

	try {
		/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja, dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10) onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji, funkcija baca izuzetak sa odgovarajucom porukom*/
		//parametri:nazivPoglavlja, ocjena

		multimedijalni.OcijeniPoglavlje("Uvod", 8);
		multimedijalni.OcijeniPoglavlje("Vrste multimedijalnih sistema", 8);
		multimedijalni.OcijeniPoglavlje("Teorija multimedije", 9);
		multimedijalni.OcijeniPoglavlje("Zakljucak", 7);
		multimedijalni.OcijeniPoglavlje("Naziv poglavlja ne postoji", 8);
	}
	catch (exception& err) {
		cout << "Greska -> " << err.what() << endl;
	}

	/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu. zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
	sprijeciti dodavanje zavrsnih radova sa istom temom*/
	//parametri: brojIndeksa, zavrsniRad
	if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
		cout << "Zavrsni rad nije dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
		cout << "Zavrsni rad nije dodat!" << endl;
	if (nastavnici[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[2]->DodajZavrsniRad("IB140002", kriptografija))
		cout << "Zavrsni rad uspjesno dodat!" << endl;

	/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
	datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
		1. zavrsni rad ima broj poglavlja veci od minimalnog
		2. svako poglavlje ima broj karaktera veci od minimalnog
		3. svako poglavlje je prihvaceno/odobreno
	ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
	u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
*/

//parametri: brojIndeksa, datumOdbrane
	ZavrsniRad* zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130111", "25.09.2018");//student sa brojem indeksa IB130111 jos uvijek nije prijavio rad
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	//ispisuje sve podatke o nastavniku i njegovim mentorstvima
	nastavnici[0]->Info();

	/*Funkcija PosaljiPozivZaDodjeluNagrada ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod odredjenog nastavnika/mentora
	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem:
	"Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzanu u na FIT-u 03.07.2019. godine."	.
	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/
	cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 6) << endl;

	for (int i = 0; i < max; i++) {
		delete nastavnici[i];
		nastavnici[i] = nullptr;
	}
	system("pause>0");
	return 0;
}

