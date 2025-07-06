#include <iostream>
#include <cstring>

using namespace std;

// Z0.1
char *alociraj(const char *tekst)
{
	if (tekst == nullptr)
		return nullptr;
	int size = strlen(tekst) + 1;
	char *temp = new char[size];
	strcpy_s(temp, size, tekst);
	return temp;
}

// Z0.2 :: Funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char[]> alocirajUnique(const char *tekst)
{
	if (tekst == nullptr)
		return nullptr;
	int size = strlen(tekst) + 1;
	unique_ptr<char[]> temp = make_unique<char[]>(size);
	strcpy_s(temp.get(), size, tekst);
	return temp;
}
// Z0.3:: Provjeriti da li su dva niza karaktera ista (po vrijednosti)
bool areEqual(const char *tekst1, const char *tekst2)
{
	return strcmp(tekst1, tekst2) == 0;
}

class Greska : public exception
{
	int _linija;
	const char *_funkcija = nullptr;

public:
	// Z0.4 :: getteri
	const char *getPoruka() const { return what(); }
	int getLinija() const { return _linija; }
	const char *getFunkcija() const { return _funkcija; }

	// Z0.5 :: setteri
	void setLinija(int linija)
	{
		_linija = linija;
	}
	void setFunkcija(const char *funkcija)
	{
		delete[] _funkcija;
		_funkcija = alociraj(funkcija);
	}

	// Z0.6 :: user-def. ctor
	Greska(const char *poruka, int linija, const char *funkcija) : exception(poruka)
	{
		setLinija(linija);
		setFunkcija(funkcija);
	}
	// Z0.7 :: copy ctor
	Greska(const Greska &obj) : exception(obj)
	{
		setLinija(obj.getLinija());
		setFunkcija(obj.getFunkcija());
	}
	// Z0.8 :: operator '='
	Greska &operator=(const Greska &obj)
	{
		if (this != &obj)
		{
			(exception &)(*this) = obj;
			setLinija(obj.getLinija());
			setFunkcija(obj.getFunkcija());
		}
		return *this;
	}
	// Z0.9 :: dtor
	~Greska()
	{
		delete[] _funkcija;
		_funkcija = nullptr;
	}
};

// kolekcija elemenata 'Vektor' (tipa T) sa mogucnoscu dinamickog prosirivanja
template <class T>
class Vektor
{
	int _trenutno = 0;
	int _maxElemenata;
	T *_elementi = nullptr;

public:
	// Z1.1 :: getteri
	int getTrenutno() const { return _trenutno; }
	int getMaxElemenata() const { return _maxElemenata; }
	T *getElementi() const { return _elementi; }

	// Z1.2 :: setteri (u ovom slucaju imamo samo jednu setter funkciju)
	void setElementi(int trenutno, int maxElemenata, T *elementi = nullptr)
	{
		delete[] _elementi;

		_maxElemenata = maxElemenata;
		_elementi = new T[_maxElemenata];

		_trenutno = 0;
		if (elementi != nullptr)
		{
			for (int i = 0; i < trenutno; i++)
			{
				dodaj(elementi[i]);
			}
		}
	}
	// Z1.3 :: funkcija za dodavanje elementa tipa 'T'.
	// U slucaju da je brojac dosao do kraja -- uraditi prosirivanje niza za 10 elemenata.
	/*void dodaj(const T& element) {
		if (_trenutno >= _maxElemenata)
			expandElementi(10);
		_elementi[_trenutno++] = element;
	}*/

	void dodaj(const T &element)
	{
		if (_trenutno >= _maxElemenata)
			expandElementi(10);
		if constexpr (is_same_v<T, const char *>)
		{
			_elementi[_trenutno] = alociraj(element);
		}
		else
		{
			_elementi[_trenutno++] = element;
		}
	}

	// Z1.4 :: funkcija za uklanjanje zadnjeg elementa iz niza
	bool removeZadnji()
	{
		if (_trenutno < 0)
			return false;
		_trenutno--;
		return true;
	}
	// Z1.5 :: funkcija za prosirivanje dinamickog niza
	void expandElementi(int uvecanje)
	{
		T *temp = new T[_trenutno + uvecanje];
		for (int i = 0; i < _trenutno; i++)
		{
			temp[i] = _elementi[i];
		}
		delete[] _elementi;
		_elementi = temp;
	}
	// Z1.6 :: dflt ctor
	Vektor(int maxElemenata = 100)
	{
		setElementi(0, maxElemenata);
	}
	// Z1.7 :: copy ctor :: Kopirati vrijednosti jednog vektora u drugi
	Vektor(const Vektor<T> &obj)
	{
		setElementi(obj.getTrenutno(), obj.getMaxElemenata(), obj.getElementi());
	}
	// Z1.8 :: operator '='
	Vektor<T> &operator=(const Vektor<T> &obj)
	{
		if (this != &obj)
			setElementi(obj.getTrenutno(), obj.getMaxElemenata(), obj.getElementi());
		return *this;
	}
	// Z1.9 :: operator '[]' za dohvacanje pojedinacne vrijednosti iz niza
	// U slucaju da je vektor prazan, 'baciti' izutetak (objekt klase 'Greska')
	// Postupiti na isti nacin i u slucaju da je 'index' izvan opsega granica vektora
	T &operator[](int index) const
	{
		if (_trenutno == 0)
			throw Greska("Vektor je prazan!", __LINE__, __FUNCTION__);
		if (index < 0 || index >= _trenutno)
			throw Greska("Indeks van opsega!", __LINE__, __FUNCTION__);
		return _elementi[index];
	}

	// Z1.10 :: funkcija za provjeru postojanosti vrijednosti 'element' u okviru dinamickog niza
	bool checkIfContains(T element)
	{
		for (int i = 0; i < _trenutno; i++)
		{
			if (_elementi[i] == element)
				return true;
		}
		return false;
	}

	// Z1.14 :: destruktor
	~Vektor()
	{
		delete[] _elementi;
		_elementi = nullptr;
	}
};

// Z1.15 :: funkcija 'ispis' za ispisivanje broja elemenata i svih elemenata (razdvojenih delimiterom)
template <class T>
void ispis(const Vektor<T> &obj, const char *delimiter = " ")
{
	for (int i = 0; i < obj.getTrenutno(); i++)
	{
		cout << obj.getElementi()[i] << delimiter;
	}
	cout << endl;
}
// Z1.16
template <class T>
bool operator==(const Vektor<T> &v1, const Vektor<T> &v2)
{
	if (v1.getTrenutno() != v2.getTrenutno())
		return false;
	for (int i = 0; i < v1.getTrenutno(); i++)
		if (v1[i] != v2[i])
			return false;
	return true;
}
// Z1.17
template <class T>
bool operator!=(const Vektor<T> &v1, const Vektor<T> &v2)
{
	return !(v1 == v2);
}

// Z1.19
template <class T>
bool operator!=(const Vektor<const char *> &v1, const Vektor<const char *> &v2)
{
	return !(v1 == v2);
}

// Klasa Zaposlenik
class Zaposlenik
{
	const char *_ime = nullptr;
	unique_ptr<char[]> _pozicija = nullptr;
	unique_ptr<int> _godineStaza = nullptr;

public:
	const char *getIme() const { return (_ime == nullptr) ? "" : _ime; }
	const char *getPozicija() const { return _pozicija.get(); }
	int getGodineStaza() const { return *_godineStaza; }

	void setIme(const char *ime)
	{
		delete[] _ime;
		_ime = alociraj(ime);
	}
	void setPozicija(const char *pozicija)
	{
		_pozicija = alocirajUnique(pozicija);
	}
	void setGodineStaza(int godineStaza)
	{
		if (_godineStaza == nullptr)
			_godineStaza = make_unique<int>();
		*_godineStaza = godineStaza;
	}

	Zaposlenik() {}

	Zaposlenik(const char *ime, const char *pozicija, int godineStaza)
	{
		setIme(ime);
		setPozicija(pozicija);
		setGodineStaza(godineStaza);
	}
	Zaposlenik(const Zaposlenik &obj)
	{
		setIme(obj.getIme());
		setPozicija(obj.getPozicija());
		setGodineStaza(obj.getGodineStaza());
	}
	Zaposlenik &operator=(const Zaposlenik &obj)
	{
		if (this != &obj)
		{
			setIme(obj.getIme());
			setPozicija(obj.getPozicija());
			setGodineStaza(obj.getGodineStaza());
		}
		return *this;
	}
	~Zaposlenik()
	{
		delete[] _ime;
		_ime = nullptr;
	}

	void ispisiInformacije()
	{
		cout << "Ime: " << getIme() << endl;
		cout << "Pozicija: " << getPozicija() << endl;
		cout << "Godine staza: " << getGodineStaza() << endl;
	}
};

class Firma
{
	const char *_naziv = nullptr;
	unique_ptr<char[]> _adresa = nullptr;
	char *_vlasnik = nullptr;
	Vektor<Zaposlenik> _zaposlenici;

public:
	const char *getNaziv() const { return (_naziv == nullptr) ? "" : _naziv; }
	const char *getVlasnik() const { return (_vlasnik == nullptr) ? "" : _vlasnik; }
	const char *getAdresa() const { return _adresa.get(); }
	Vektor<Zaposlenik> getZaposlenici() const { return _zaposlenici; }

	void setNaziv(const char *naziv)
	{
		delete[] _naziv;
		_naziv = alociraj(naziv);
	}
	void setVlasnik(const char *vlasnik)
	{
		delete[] _vlasnik;
		_vlasnik = alociraj(vlasnik);
	}
	void setAdresa(const char *adresa)
	{
		_adresa = alocirajUnique(adresa);
	}
	void setZaposlenici(Vektor<Zaposlenik> zaposlenici)
	{
		_zaposlenici = zaposlenici;
	}
	void dodajUposlenika(Zaposlenik &zaposlenik)
	{
		_zaposlenici.dodaj(zaposlenik);
	}
	Firma(const char *naziv, const char *adresa, const char *vlasnik)
	{
		setNaziv(naziv);
		setAdresa(adresa);
		setVlasnik(vlasnik);
	}
	Firma(const Firma &obj)
	{
		setNaziv(obj.getNaziv());
		setAdresa(obj.getAdresa());
		setVlasnik(obj.getVlasnik());
		setZaposlenici(obj.getZaposlenici());
	}
	Firma &operator=(const Firma &obj)
	{
		if (this != &obj)
		{
			setNaziv(obj.getNaziv());
			setAdresa(obj.getAdresa());
			setVlasnik(obj.getVlasnik());
			setZaposlenici(obj.getZaposlenici());
		}
		return *this;
	}

	virtual ~Firma()
	{
		delete[] _naziv;
		_naziv = nullptr;
		delete[] _vlasnik;
		_vlasnik = nullptr;
	}

	virtual void ispisiInformacije()
	{
		cout << "Naziv: " << getNaziv() << endl;
		cout << "Adresa: " << getAdresa() << endl;
		cout << "Vlasnik: " << getVlasnik() << endl;
		cout << "Zaposlenici: " << endl;
		for (int i = 0; i < _zaposlenici.getTrenutno(); i++)
		{
			_zaposlenici[i].ispisiInformacije();
			cout << endl;
		}
	}
};

class Cvjecara : public Firma
{
	const char *_vrsteCvijeca[20] = {nullptr};
	int _brojVrstaCvijeca;

public:
	int getBrojVrstaCvijeca() const { return _brojVrstaCvijeca; }
	const char **getVrsteCvijeca() const { return (const char **)_vrsteCvijeca; }
	// Baciti exception tipa Greska u slucaju da je index van granica niza
	const char *getVrstaCvijeca(int index)
	{
		if (index < 0 || index >= _brojVrstaCvijeca)
			throw Greska("Indeks van opsega!", __LINE__, __FUNCTION__);
		return _vrsteCvijeca[index];
	}
	void setVrsteCvijeca(int trenutno, const char **vrsteCvijeca = nullptr)
	{
		for (int i = 0; i < _brojVrstaCvijeca; i++)
		{
			delete[] _vrsteCvijeca[i];
			_vrsteCvijeca[i] = nullptr;
		}
		_brojVrstaCvijeca = 0;

		if (vrsteCvijeca != nullptr)
		{
			for (int i = 0; i < trenutno; i++)
			{
				dodajVrstu(vrsteCvijeca[i]);
			}
		}
	}
	// Baciti exception tipa Greška ukoliko je niz popunjen
	void dodajVrstu(const char *vrsta)
	{
		if (_brojVrstaCvijeca >= size(_vrsteCvijeca))
			throw Greska("Niz je popunjen!", __LINE__, __FUNCTION__);
		_vrsteCvijeca[_brojVrstaCvijeca++] = alociraj(vrsta);
	}

	Cvjecara() : Firma("-", "-", "-") {}

	Cvjecara(const char *naziv, const char *adresa, const char *vlasnik)
		: Firma(naziv, adresa, vlasnik)
	{
		_brojVrstaCvijeca = 0;
	}
	Cvjecara(const Cvjecara &obj) : Firma(obj)
	{
		setVrsteCvijeca(obj.getBrojVrstaCvijeca(), obj.getVrsteCvijeca());
	}
	Cvjecara &operator=(const Cvjecara &obj)
	{
		if (this != &obj)
			setVrsteCvijeca(obj.getBrojVrstaCvijeca(), obj.getVrsteCvijeca());
		return *this;
	}

	~Cvjecara()
	{
		for (int i = 0; i < _brojVrstaCvijeca; i++)
		{
			delete[] _vrsteCvijeca[i];
			_vrsteCvijeca[i] = nullptr;
		}
	}

	void ispisiInformacije() override
	{
		Firma::ispisiInformacije();
		cout << "Vrste cvijeca: " << endl;
		for (int i = 0; i < _brojVrstaCvijeca; i++)
		{
			cout << "\t" << _vrsteCvijeca[i] << endl;
		}
	}
};

class Praonica : public Firma
{
	unique_ptr<int> _brojVesMasina;
	bool *_nudiHemijskoCiscenje = nullptr;

public:
	int getBrojVesMasina() const { return *_brojVesMasina; }
	bool getNudiHemijskoCiscenje() const { return *_nudiHemijskoCiscenje; }

	void setBrojVesMasina(int brojVesMasina)
	{
		if (_brojVesMasina == nullptr)
			_brojVesMasina = make_unique<int>();
		*_brojVesMasina = brojVesMasina;
	}
	void setNudiHemijskoCiscenje(bool nudiHemijskoCiscenje)
	{
		if (_nudiHemijskoCiscenje == nullptr)
			_nudiHemijskoCiscenje = new bool;
		*_nudiHemijskoCiscenje = nudiHemijskoCiscenje;
	}

	Praonica() : Firma("-", "-", "-") {}

	Praonica(const char *naziv, const char *adresa, const char *vlasnik, int brojZaposlenih, int brojVesMasina, bool nudiHemijskoCiscenje)
		: Firma(naziv, adresa, vlasnik)
	{
		setBrojVesMasina(brojVesMasina);
		setNudiHemijskoCiscenje(nudiHemijskoCiscenje);
	}
	Praonica(const Praonica &obj) : Firma(obj)
	{
		setBrojVesMasina(obj.getBrojVesMasina());
		setNudiHemijskoCiscenje(obj.getNudiHemijskoCiscenje());
	}
	Praonica &operator=(const Praonica &obj)
	{
		if (this != &obj)
		{
			(Firma &)(*this) = obj;
			setBrojVesMasina(obj.getBrojVesMasina());
			setNudiHemijskoCiscenje(obj.getNudiHemijskoCiscenje());
		}
		return *this;
	}
	~Praonica()
	{
		delete _nudiHemijskoCiscenje;
		_nudiHemijskoCiscenje = nullptr;
	}

	void ispisiInformacije()
	{
	}
};
class Korporacija
{
	unique_ptr<char[]> _naziv = nullptr;
	Vektor<Cvjecara> _cvjecare;
	Vektor<Praonica> _praonice;

public:
	const char *getNaziv() const { return _naziv.get(); }
	Vektor<Cvjecara> getCvjecare() const { return _cvjecare; }
	Vektor<Praonica> getPraonice() const { return _praonice; }

	void setNaziv(const char *naziv)
	{
		_naziv = alocirajUnique(naziv);
	}
	void setCvjecare(Vektor<Cvjecara> cvjecare)
	{
		_cvjecare = cvjecare;
	}
	void setPraonice(Vektor<Praonica> praonice)
	{
		_praonice = praonice;
	}

	Korporacija(const char *naziv)
	{
		setNaziv(naziv);
	}
	Korporacija(const Korporacija &obj)
	{
		setNaziv(obj.getNaziv());
		setCvjecare(obj.getCvjecare());
		setPraonice(obj.getPraonice());
	}
	Korporacija &operator=(const Korporacija &obj)
	{
		if (this != &obj)
		{
			setNaziv(obj.getNaziv());
			setCvjecare(obj.getCvjecare());
			setPraonice(obj.getPraonice());
		}
		return *this;
	}
	void dodajCvjecaru(Cvjecara &obj)
	{
		_cvjecare.dodaj(obj);
	}
	void dodajPraonicu(Praonica &obj)
	{
		_praonice.dodaj(obj);
	}
};

int main()
{

	try
	{
		// Test Greska
		try
		{
			Vektor<int> prazan;
			cout << prazan[0]; // should throw
		}
		catch (const Greska &g)
		{
			cout << "Greska: " << g.getPoruka() << " u funkciji: " << g.getFunkcija() << " na liniji: " << g.getLinija() << endl;
		}

		// Test Zaposlenik
		Zaposlenik z1("Amir", "Manager", 10);
		Zaposlenik z2("Belma", "Florist", 5);

		// Test Vektor<Zaposlenik>
		Vektor<Zaposlenik> vektorZaposlenika;
		vektorZaposlenika.dodaj(z1);
		vektorZaposlenika.dodaj(z2);

		// Test Firma
		Firma f1("Cvjetna Dolina", "Marsala Tita 5", "Jasmina");
		f1.dodajUposlenika(z1);
		f1.dodajUposlenika(z2);
		f1.ispisiInformacije();

		// Test Cvjecara
		Cvjecara c1("Cvjecara Ljepota", "Zmaja od Bosne", "Elma");
		c1.dodajUposlenika(z1);
		c1.dodajVrstu("Ruze");
		c1.dodajVrstu("Ljiljani");
		c1.dodajVrstu("Orhideje");

		// provoke exception in Cvjecara
		try
		{
			c1.getVrstaCvijeca(10); // out of bounds
		}
		catch (const Greska &g)
		{
			cout << "Greska: " << g.getPoruka() << " u funkciji: " << g.getFunkcija() << " na liniji: " << g.getLinija() << endl;
		}

		c1.ispisiInformacije();

		// Test Praonica
		Praonica p1("Praonica Cisto", "Ulica bb", "Haris", 2, 4, true);
		Zaposlenik z3("Selma", "Radnica", 3);
		p1.dodajUposlenika(z3);
		p1.ispisiInformacije();

		// Test Korporacija
		Korporacija k1("MojaKorp");
		k1.dodajCvjecaru(c1);
		k1.dodajPraonicu(p1);

		cout << "\nKorporacija: " << k1.getNaziv() << endl;
		cout << "Cvjecare u korporaciji: " << k1.getCvjecare().getTrenutno() << endl;
		cout << "Praonice u korporaciji: " << k1.getPraonice().getTrenutno() << endl;

		// Final test of equality operators
		Vektor<int> v1, v2;
		v1.dodaj(1);
		v1.dodaj(2);
		v1.dodaj(3);
		v2.dodaj(1);
		v2.dodaj(2);
		v2.dodaj(3);
		cout << "Vektori su isti? " << (v1 == v2 ? "DA" : "NE") << endl;

		Vektor<const char *> vs1, vs2;
		vs1.dodaj("A");
		vs1.dodaj("B");
		vs2.dodaj("A");
		vs2.dodaj("B");
		cout << "String vektori su isti? " << (vs1 == vs2 ? "DA" : "NE") << endl;
	}
	catch (const exception &ex)
	{
		cout << "Neocekivana greska: " << ex.what() << endl;
	}

	return 0;
}