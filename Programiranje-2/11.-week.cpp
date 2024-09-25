#include <iostream>
using namespace std;


// Z0.1 
char* alociraj(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    char* novi = new char[strlen(tekst) + 1];
    strcpy_s(novi, strlen(tekst) + 1, tekst);
    return novi;
}

// Z0.2 :: Funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char[]> alocirajUnique(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    unique_ptr<char[]> novi(new char[strlen(tekst) + 1]);
    strcpy_s(novi.get(), strlen(tekst) + 1, tekst);
    return novi;
}
// Z0.3:: Provjeriti da li su dva niza karaktera ista (po vrijednosti)
bool areEqual(const char* tekst1, const char* tekst2) {
    if (tekst1 == nullptr || tekst2 == nullptr)
        return false;
    return strcmp(tekst1, tekst2) == 0;
}

// simulacija ratne stateske igre
enum class Moral { Nizak = 1, Srednji, Visok };
ostream& operator<<(ostream& COUT, const Moral& obj) {
    switch (obj) {
    case Moral::Nizak:
        COUT << "Nizak";
        break;
    case Moral::Srednji:
        COUT << "Srednji";
        break;
    case Moral::Visok:
        COUT << "Visok";
        break;
    default:
        break;
    }
    return COUT;
}
class Vojnik {
    unique_ptr<int> _zdravlje; //[0-100] 
    unique_ptr<int> _izdrzljivost; //[0-100]
    Moral* _moral = nullptr;
    bool _statusZiv;
    int _trenutnoOruzja = 0;
    const char* _oruzja[10] = { nullptr };
public:

    // Z1.1 :: getteri
    int getZdravlje() const { return (_zdravlje == nullptr) ? 100 : *_zdravlje; }
    int getIzdrzljivost() const { return (_izdrzljivost == nullptr) ? 100 : *_izdrzljivost; }
    Moral getMoral() const { return (_moral == nullptr) ? Moral::Visok : *_moral; }
    int getTrenutnoOruzja() const { return _trenutnoOruzja; }
    bool getStatus() const { return _statusZiv; }
    const char* getOruzje(int index) const {
        return (index < 0 || index >= getTrenutnoOruzja()) ? "" : _oruzja[index];
    }
    const char** getOruzja() const { return (const char**)_oruzja; }

    // Z1.2 :: setteri
    void setZdravlje(int zdravlje) {
        if (_zdravlje == nullptr)
            _zdravlje = make_unique<int>();
        *_zdravlje = zdravlje;
    }
    void setIzdrzljivost(int izdrzljivost) {
        if (_izdrzljivost == nullptr)
            _izdrzljivost = make_unique<int>();
        *_izdrzljivost = izdrzljivost;
    }
    void setMoral(Moral moral) {
        if (_moral == nullptr)
            _moral = new Moral();
        *_moral = moral;
    }
    void setStatus(bool statusZiv) {
        _statusZiv = statusZiv;
    }
    void setOruzja(int trenutno, const char** oruzja = nullptr) {
        for (int i = 0; i < _trenutnoOruzja; i++) {
            delete[] _oruzja[i];
            _oruzja[i] = nullptr;
        }
        _trenutnoOruzja = 0;
        if (oruzja != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodajOruzje(oruzja[i]);
            }
        }
    }
    // Z1.3 :: metoda 'dodajOruzje'
    bool dodajOruzje(const char* oruzje) {
        if (_trenutnoOruzja >= size(_oruzja))
            return false;
        _oruzja[_trenutnoOruzja++] = alociraj(oruzje);
        return true;
    }

    // Z1.4 :: def ctor/user-def ctor
    Vojnik(int zdravlje = 100, int izdrzljivost = 100, Moral moral = Moral::Visok, bool statusZiv = true) {
        setZdravlje(zdravlje);
        setIzdrzljivost(izdrzljivost);
        setMoral(moral);
        setStatus(statusZiv);
    }
    // Z1.5 :: copy ctor
    Vojnik(const Vojnik& obj) {
        setZdravlje(obj.getZdravlje());
        setIzdrzljivost(obj.getIzdrzljivost());
        setMoral(obj.getMoral());
        setStatus(obj.getStatus());
        setOruzja(obj.getTrenutnoOruzja(), obj.getOruzja());
    }

    // Z1.6 :: operator '='
    Vojnik& operator = (const Vojnik& obj) {
        if (this != &obj) {
            setZdravlje(obj.getZdravlje());
            setIzdrzljivost(obj.getIzdrzljivost());
            setMoral(obj.getMoral());
            setStatus(obj.getStatus());
            setOruzja(obj.getTrenutnoOruzja(), obj.getOruzja());
        }
        return *this;
    }
    // Z1.7 :: virtuelna metoda 'ispis'
    virtual void ispis() {
        cout << "Zdravlje: " << getZdravlje() << "/100" << endl;
        cout << "Izdrzljivost: " << getIzdrzljivost() << "/100" << endl;
        cout << "Moral: " << getMoral() << endl;
        cout << "Vojnik je ziv: " << boolalpha << getStatus() << endl;
        cout << "Oruzja vojnika: " << endl;
        for (int i = 0; i < getTrenutnoOruzja(); i++) {
            cout << "\t" << getOruzja()[i] << endl;
        }
    }
    // Z1.8 :: virtuelni destruktor
    virtual ~Vojnik() {
        delete _moral; _moral = nullptr;
        for (int i = 0; i < _trenutnoOruzja; i++) {
            delete[] _oruzja[i];
            _oruzja[i] = nullptr;
        }
    }
};
// Z1.9 :: porediti po svim obiljezjima (ukljucujuci i niz 'oruzja')
bool operator == (const Vojnik& v1, const Vojnik& v2) {
    if (v1.getZdravlje() != v2.getZdravlje() ||
        v1.getIzdrzljivost() != v2.getIzdrzljivost() ||
        v1.getMoral() != v2.getMoral() ||
        v1.getStatus() != v2.getStatus() ||
        v1.getTrenutnoOruzja() != v2.getTrenutnoOruzja())
        return false;
    for (int i = 0; i < v1.getTrenutnoOruzja(); i++) {
        if (!areEqual(v1.getOruzje(i), v2.getOruzje(i)))
            return false;
    }
    return true;
}
bool operator != (const Vojnik& v1, const Vojnik& v2) {
    return !(v1 == v2);
}

// simuliramo interfejs pomocu abstraktne klase
class IPonasanje {
public:
    virtual void oglasiSe() = 0;
    virtual void oporavljajSe() = 0;
    virtual void napadaj(Vojnik* drugiVojnik) = 0;
};

enum class Kategorija { Laka = 1, Srednja, Teska };
ostream& operator<<(ostream& COUT, const Kategorija& obj) {
    switch (obj) {
    case Kategorija::Laka:
        COUT << "Laka";
        break;
    case Kategorija::Srednja:
        COUT << "Srednja";
        break;
    case Kategorija::Teska:
        COUT << "Teska";
        break;
    }
    return COUT;
}
class Pjesak : public Vojnik, public IPonasanje {
    Kategorija _kategorija;
    unique_ptr<char[]> _oklop;
public:
    // Z2.1 :: getteri
    Kategorija getKategorija() const { return _kategorija; }
    const char* getOklop() const { return (_oklop == nullptr) ? "" : _oklop.get(); }
    // Z2.2 :: setteri
    void setKategorija(Kategorija kategorija) {
        _kategorija = kategorija;
    }
    void setOklop(const char* oklop) {
        _oklop = alocirajUnique(oklop);
    }
    // Z2.3 :: user-def ctor
    Pjesak(Kategorija kategorija = Kategorija::Srednja, const char* oklop = "metalni") 
        :Vojnik()
    {
        setKategorija(kategorija);
        setOklop(oklop);
    }
    // Z2.4 :: copy ctor
    Pjesak(const Pjesak& obj) : Vojnik(obj) {
        setKategorija(obj.getKategorija());
        setOklop(obj.getOklop());
    }
    // Z2.5 :: operator '='
    Pjesak& operator = (const Pjesak& obj) {
        if (this != &obj) {
            (Vojnik&)(*this) = obj;
            setKategorija(obj.getKategorija());
            setOklop(obj.getOklop());
        }
        return *this;
    }
    // Z2.6 :: metoda 'ispis'
    void ispis() {
        Vojnik::ispis();
        cout << "Kategorija: " << getKategorija() << endl;
        cout << "Oklop: " << getOklop() << endl;
    }
    // Z2.7 :: ispisati poruku "Ja sam tipa <Tip Podatka>" :: za utvrdjivanje tipa podatka, koristiti funkciju 'typeid'
    void oglasiSe() {
        //cout << "Ja sam tipa <Pjesak>\n";
        cout << "Ja sam tipa <" << typeid(*this).name() << ">\n";
    }
    // Z2.8 :: povecati vrijednost atributa '_zdravlje' za slucajnu vrijednost izmedju [0-25]
    void oporavljajSe() {
        setZdravlje(getZdravlje() + rand() % 25 + 1);
    }
    // Z2.9 :: dtor
    ~Pjesak() {
    }
    void napadaj(Vojnik* drugiVojnik); // prototip metode koju cemo implementirati izvan scope-a
};

// Z2.10
bool operator == (const Pjesak& p1, const Pjesak& p2) {
    return (Vojnik&)p1 == (Vojnik&)p2 &&
        p1.getKategorija() == p2.getKategorija() &&
        p1.getOklop() == p2.getOklop();

}
bool operator != (const Pjesak& p1, const Pjesak& p2) {
    return !(p1 == p2);
}

class Strijelac : public Vojnik {
    int* _municija = nullptr;
public:
    // Z3.1 :: getteri
    int getMunicija() const { return (_municija == nullptr) ? 0 : *_municija; }
    // Z3.2 :: setteri
    void setMunicija(int municija) {
        if (_municija == nullptr)
            _municija = new int;
        *_municija = municija;
    }
    // Z3.3 :: dflt /user-def ctor
    Strijelac(int municija = 50) : Vojnik() {
        setMunicija(municija);
    }
    // Z3.4 :: copy ctor
    Strijelac(const Strijelac& obj) : Vojnik(obj) {
        setMunicija(obj.getMunicija());
    }

    // Z3.5 :: operator '='
    Strijelac& operator =(const Strijelac& obj) {
        if (this != &obj) {
            (Vojnik&)(*this) = obj;
            setMunicija(obj.getMunicija());
        }
        return *this;
    }
    // Z3.6 :: metoda 'ispis'
    void ispis() {
        Vojnik::ispis();
        cout << "Municija: " << getMunicija() << endl;
    }

    // Z3.7 :: ispisati poruku "Ja sam tipa <Tip Podatka>" ... 
    void oglasiSe() {
        cout << "Ja sam tipa <" << typeid(*this).name() << ">\n";
    }

    // Z3.8 :: povecati vrijednost atributa '_zdravlje' za slucajnu vrijednost izmedju [0-35]
    void oporavljajSe() {
        setZdravlje(getZdravlje() + rand() % 35 + 1);
    }
    // Z3.9 :: dtor
    ~Strijelac() {
        delete _municija; _municija = nullptr;
    }
    void napadaj(Vojnik* drugiVojnik); // prototip metode koju cemo implementirati izvan scope-a
};
// Z3.10 :: operator '=='
bool operator == (const Strijelac& s1, const Strijelac& s2) {
    // Implementirati funkciju
    return false;
}
bool operator != (const Strijelac& s1, const Strijelac& s2) {
    return !(s1 == s2);
}


class Konjanik : public Vojnik {
    unique_ptr<char[]> _oklop;
    const char* _vrstaKonja = nullptr;
public:
    // Z4.1 :: getteri
    const char* getOklop() const { return (_oklop == nullptr) ? "" : _oklop.get(); }
    const char* getVrstaKonja() const { return (_vrstaKonja == nullptr) ? "" : _vrstaKonja; }
    // Z4.2 :: setteri
    void setOklop(const char* oklop) {
        _oklop = alocirajUnique(oklop);
    }
    void setVrstaKonja(const char* vrstaKonja) {
        delete[] _vrstaKonja;
        _vrstaKonja = alociraj(vrstaKonja);
    }

    // Z4.3 :: dflt ctor/ user-def ctor
    Konjanik(const char* oklop = "metalni", const char* vrstaKonja = "") : Vojnik() {
        setOklop(oklop);
        setVrstaKonja(vrstaKonja);
    }
    // Z4.4 :: copy ctor
    Konjanik(const Konjanik& obj) : Vojnik(obj) {
        setOklop(obj.getOklop());
        setVrstaKonja(obj.getVrstaKonja());
    }

    // Z4.5 :: operator '='
    Konjanik& operator = (const Konjanik& obj) {
        if (this != &obj) {
            (Vojnik&)(*this) = obj;
            setOklop(obj.getOklop());
            setVrstaKonja(obj.getVrstaKonja());
        }
        return *this;
    }

    // Z4.6 :: metoda 'ispis'  
    void ispis() {
        Vojnik::ispis();
        cout << "Oklop: " << getOklop() << endl;
        cout << "Vrsta konja: " << getVrstaKonja() << endl;
    }
    // Z4.7 :: ispisati poruku "Ja sam tipa <Tip Podatka>" ... 
    void oglasiSe() {
        cout << "Ja sam tipa <" << typeid(*this).name() << ">\n";
    }
    // Z4.8 :: povecati vrijednost atributa zdravlje za slucajnu vrijednost izmedju [0-15]
    void oporavljajSe() {
        setZdravlje(getZdravlje() + rand() % 15 + 1);
    }
    // Z4.9 :: dtor
    ~Konjanik() {
        delete[] _vrstaKonja; _vrstaKonja = nullptr;
    }
    void napadaj(Vojnik* drugiVojnik); // prototip metode koju cemo implementirati izvan scope-a
};
// Z4.10 :: operator '=='
bool operator == (const Konjanik& k1, const Konjanik& k2) {
    return (Vojnik&)k1 == (Vojnik&)k2 &&
        areEqual(k1.getOklop(), k2.getOklop()) &&
        areEqual(k1.getVrstaKonja(), k2.getVrstaKonja());
}
bool operator != (const Konjanik& k1, const Konjanik& k2) {
    return !(k1 == k2);
}

// Z4.11 :: implementacija
//  Pjesak ima vjerovatnocu od 50% da ce uspjesno sprovesti napad
//  Utvrditi tip mete koristenjem 'dynamic_cast'
//  U slucaju da je napad uspjesan, steta koja se nanosi je:
//   ->30 (ukoliko je meta drugi pjesak)
//   ->50 (ukoliko je meta strijelac)
//   ->10 (ukoliko je meta konjanik)
//  Umanjiti zdravlje mete za nacinjenu stetu
//  Ukoliko je zdravlje mete palo na 0, proglasiti metu nezivom (status = false)

void Pjesak::napadaj(Vojnik* meta) {
    bool napad = bool(rand() % 2);
    if (napad == false)
        return;
    Pjesak* pjesak = dynamic_cast<Pjesak*>(meta);
    if (pjesak != nullptr) {
        pjesak->setZdravlje(pjesak->getZdravlje() - 30);
        if (pjesak->getZdravlje() <= 0)
            pjesak->setStatus(false);
        return;
    }

    Strijelac* strijelac = dynamic_cast<Strijelac*>(meta);
    if (strijelac != nullptr) {
        strijelac->setZdravlje(strijelac->getZdravlje() - 50);
        if (strijelac->getZdravlje() <= 0)
            strijelac->setStatus(false);
        return;
    }

    Konjanik* konjanik = dynamic_cast<Konjanik*>(meta);
    if (konjanik != nullptr) {
        konjanik->setZdravlje(konjanik->getZdravlje() - 10);
        if (konjanik->getZdravlje() <= 0)
            konjanik->setStatus(false);
        return;
    }
}

// Z4.12 :: implementacija
//  Strijelac ima vjerovatnocu od 50% da ce uspjesno sprovesti napad
//  Utvrditi tip mete koristenjem 'dynamic_cast'
//  U slucaju da je napad uspjesan, steta koja se nanosi je:
//  ->35 (ukoliko je meta pjesak)
//  ->50 (ukoliko je meta drugi strijelac)
//  ->65 (ukoliko je meta konjanik)
//  Umanjiti zdravlje mete za nacinjenu stetu
//  Ukoliko je zdravlje mete palo na 0, proglasiti metu nezivom (StatusAlive = false)
void Strijelac::napadaj(Vojnik* meta) {
    bool napad = bool(rand() % 2);
    if (napad == false)
        return;
    Pjesak* pjesak = dynamic_cast<Pjesak*>(meta);
    if (pjesak != nullptr) {
        pjesak->setZdravlje(pjesak->getZdravlje() - 35);
        if (pjesak->getZdravlje() <= 0)
            pjesak->setStatus(false);
        return;
    }

    Strijelac* strijelac = dynamic_cast<Strijelac*>(meta);
    if (strijelac != nullptr) {
        strijelac->setZdravlje(strijelac->getZdravlje() - 50);
        if (strijelac->getZdravlje() <= 0)
            strijelac->setStatus(false);
        return;
    }

    Konjanik* konjanik = dynamic_cast<Konjanik*>(meta);
    if (konjanik != nullptr) {
        konjanik->setZdravlje(konjanik->getZdravlje() - 65);
        if (konjanik->getZdravlje() <= 0)
            konjanik->setStatus(false);
        return;
    }
}
// Z4.13 :: implementacija
//  Konjanik ima vjerovatnocu od 50% da ce uspjesno sprovesti napad
//  Utvrditi tip mete koristenjem 'dynamic_cast'
//  U slucaju da je napad uspjesan, steta koja se nanosi je:
//  ->50 (ukoliko je meta pjesak)
//  ->80 (ukoliko je meta strijelac)
//  ->20 (ukoliko je meta konjanik)
//  Umanjiti zdravlje mete za nacinjenu stetu
//  Ukoliko je zdravlje mete palo na 0, proglasiti metu nezivom (StatusAlive = false)
void Konjanik::napadaj(Vojnik* meta) {
    bool napad = bool(rand() % 2);
    if (napad == false)
        return;
    Pjesak* pjesak = dynamic_cast<Pjesak*>(meta);
    if (pjesak != nullptr) {
        pjesak->setZdravlje(pjesak->getZdravlje() - 50);
        if (pjesak->getZdravlje() <= 0)
            pjesak->setStatus(false);
        return;
    }

    Strijelac* strijelac = dynamic_cast<Strijelac*>(meta);
    if (strijelac != nullptr) {
        strijelac->setZdravlje(strijelac->getZdravlje() - 80);
        if (strijelac->getZdravlje() <= 0)
            strijelac->setStatus(false);
        return;
    }

    Konjanik* konjanik = dynamic_cast<Konjanik*>(meta);
    if (konjanik != nullptr) {
        konjanik->setZdravlje(konjanik->getZdravlje() - 20);
        if (konjanik->getZdravlje() <= 0)
            konjanik->setStatus(false);
        return;
    }
}

template<class T>
class VojnaJedinica {
    const char* _naziv = nullptr;
    unique_ptr<float> _cijenaObuke;
    unique_ptr<float> _cijenaOdrzavanja;
    int _trenutnoPripadnika = 0;
    T _pripadnici[100];
public:
    // Z5.1 :: getteri
    const char* getNaziv() const { return (_naziv == nullptr) ? "" : _naziv; }
    float getCijenaObuke() const { return  (_cijenaObuke == nullptr) ? 0.0f : *_cijenaObuke; }
    float getCijenaOdrzavanja() const { return  (_cijenaOdrzavanja == nullptr) ? 0.0f : *_cijenaOdrzavanja; }
    int getTrenutnoPripadnika() const { return _trenutnoPripadnika; }
    T& getPripadnik(int index)const { return _pripadnici[index]; }
    T* getPripadnici() const { return (T*)_pripadnici; }
    // Z5.2 :: setteri
    void setNaziv(const char* naziv) {
        _naziv = alociraj(naziv);
    }
    void setCijenaObuke(float cijenaObuke) {
        if (_cijenaObuke == nullptr)
            _cijenaObuke = make_unique<float>();
        *_cijenaObuke = cijenaObuke;
    }
    void setCijenaOdrzavanja(float cijenaOdrzavanja) {
        if (_cijenaOdrzavanja == nullptr)
            _cijenaOdrzavanja = make_unique<float>();
        *_cijenaOdrzavanja = cijenaOdrzavanja;
    }
    void setPripadnici(int trenutno, T* pripadnici = nullptr) {
        _trenutnoPripadnika = 0;
        if (pripadnici != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                addPripadnik(pripadnici[i]);
            }
        }
    }
    // Z5.3 :: metoda 'addPripadnik'
    bool addPripadnik(T pripadnik) {
        if (_trenutnoPripadnika >= 100/*size(_pripadnici)*/)
            return false;
        _pripadnici[_trenutnoPripadnika++] = pripadnik;
        return true;
    }

    // Z5.4 :: dflt ctor / user-def ctor
    VojnaJedinica(const char* naziv = "", float cijenaObuke = 500, float cijenaOdrzavanja = 110) {
        setNaziv(naziv);
        setCijenaObuke(cijenaObuke);
        setCijenaOdrzavanja(cijenaOdrzavanja);
    }
    // Z5.5 :: copy ctor
    VojnaJedinica(const VojnaJedinica<T>& obj) {
        setNaziv(obj.getNaziv());
        setCijenaObuke(obj.getCijenaObuke());
        setCijenaOdrzavanja(obj.getCijenaOdrzavanja());
        setPripadnici(obj.getTrenutnoPripadnika(), obj.getPripadnici());
    }

    // Z5.6 :: operator '='
    VojnaJedinica<T>& operator = (const VojnaJedinica<T>& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setCijenaObuke(obj.getCijenaObuke());
            setCijenaOdrzavanja(obj.getCijenaOdrzavanja());
            setPripadnici(obj.getTrenutnoPripadnika(), obj.getPripadnici());
        }
        return *this;
    }
    // Z5.7 :: ispisati naziv, vojni red [tip T], broj pripadnika, cijenu obuke i cijenu odrzavanja
    void ispis() {
        cout << "\tVOJNA JEDINICA" << endl;
        cout << "Ime vojne jedinice: " << getNaziv() << endl;
        cout << typeid(T).name() << endl;
        cout << "Broj pripadnika: " << getTrenutnoPripadnika() << endl;
        cout << "Cijena obuke: " << getCijenaObuke() << endl;
        cout << "Cijena odrzavanja: " << getCijenaOdrzavanja() << endl;
    }
    // Z5.8 :: dtor
    ~VojnaJedinica() {
        delete[] _naziv; _naziv = nullptr;
    }
};

class Armija {
    const char* _ime = nullptr;
    int _brojacP = 0, _brojacS = 0, _brojacK = 0;
    VojnaJedinica<Pjesak> _pjesadija[100];
    VojnaJedinica<Strijelac> _strijelci[50];
    VojnaJedinica<Konjanik> _konjica[20];
public:
    // Z6.1 :: getteri
    const char* getIme() const { return (_ime == nullptr) ? "" : _ime; }
    int getBrojPjesackihJedinica() const { return _brojacP; }
    int getBrojStreljackihJedinica() const { return _brojacS; }
    int getBrojKonjickihJedinica() const { return _brojacK; }

    // getteri za dohvacanje odredjene vojne jedinice
    VojnaJedinica<Pjesak> getPjesackaJedinica(int index) const { return _pjesadija[index]; }
    VojnaJedinica<Strijelac> getStreljackaJedinica(int index) const { return _strijelci[index]; }
    VojnaJedinica<Konjanik> getKonjickaJedinica(int index) const { return _konjica[index]; }
    // getteri za dohvacanje vojnog roda
    VojnaJedinica<Pjesak>* getPjesadija() const { return (VojnaJedinica<Pjesak>*)_pjesadija; }
    VojnaJedinica<Strijelac>* getStrijelci() const { return (VojnaJedinica<Strijelac>*)_strijelci; }
    VojnaJedinica<Konjanik>* getKonjica() const { return (VojnaJedinica<Konjanik>*)_konjica; }

    // Z6.2 :: setteri
    void setIme(const char* ime) {
        _ime = alociraj(ime);
    }
    void setPjesadija(int trenutno, VojnaJedinica<Pjesak>* pjesadija = nullptr) {
        _brojacP = 0;
        if (pjesadija != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodajJedinicu(pjesadija[i]);
            }
        }
    }
    void setStrijelci(int trenutno, VojnaJedinica<Strijelac>* strijelci = nullptr) {
        _brojacS = 0;
        if (strijelci != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodajJedinicu(strijelci[i]);
            }
        }
    }
    void setKonjica(int trenutno, VojnaJedinica<Konjanik>* konjica = nullptr) {
        _brojacK = 0;
        if (konjica != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodajJedinicu(konjica[i]);
            }
        }
    }

    // Z6.3 :: metode za dodavanje jedinica
    bool dodajJedinicu(VojnaJedinica<Pjesak> jedinica) {
        if (_brojacP >= size(_pjesadija))
            return false;
        _pjesadija[_brojacP++] = jedinica;
        return true;
    }
    bool dodajJedinicu(VojnaJedinica<Strijelac> jedinica) {
        if (_brojacS >= size(_strijelci))
            return false;
        _strijelci[_brojacS++] = jedinica;
        return true;
    }
    bool dodajJedinicu(VojnaJedinica<Konjanik> jedinica) {
        if (_brojacK >= size(_konjica))
            return false;
        _konjica[_brojacK++] = jedinica;
        return true;
    }

    // Z6.4 :: dflt / user-def. ctor
    Armija(const char* ime = "") {
        setIme(ime);
    }
    // Z6.5 :: copy ctor
    Armija(const Armija& obj) {
        setIme(obj.getIme());
        setPjesadija(obj.getBrojPjesackihJedinica(), obj.getPjesadija());
        setStrijelci(obj.getBrojStreljackihJedinica(), obj.getStrijelci());
        setKonjica(obj.getBrojKonjickihJedinica(), obj.getKonjica());
    }

    // Z6.6 :: operator '='
    Armija& operator =(const Armija& obj) {
        if (this != &obj) {
            setIme(obj.getIme());
            setPjesadija(obj.getBrojPjesackihJedinica(), obj.getPjesadija());
            setStrijelci(obj.getBrojStreljackihJedinica(), obj.getStrijelci());
            setKonjica(obj.getBrojKonjickihJedinica(), obj.getKonjica());
        }
        return *this;
    }

    // Z6.7 :: metoda 'ispis'
    void ispis() {
        cout << "Naziv armije: " << getIme() << endl;
        cout << "----------------------------------\n";
        cout << "Pjesadija:" << endl;
        cout << "----------------------------------\n";
        for (int i = 0; i < getBrojPjesackihJedinica(); i++) {
            getPjesackaJedinica(i).ispis();
            cout << endl;
        }

        cout << "----------------------------------\n";
        cout << "Strijelci:" << endl;
        cout << "----------------------------------\n";
        for (int i = 0; i < getBrojStreljackihJedinica(); i++) {
            getStreljackaJedinica(i).ispis();
            cout << endl;
        }
        cout << "----------------------------------\n";
        cout << "Konjica:" << endl;
        cout << "----------------------------------\n";
        for (int i = 0; i < getBrojKonjickihJedinica(); i++) {
            getKonjickaJedinica(i).ispis();
            cout << endl;
        }
        cout << "----------------------------------\n";
    }
    // Z6.8 :: dtor
    ~Armija() {
        delete[] _ime; _ime = nullptr;
    }
};

void zadatak1() {
    const char* oruzja[] = { "mac", "dugi mac", "ratna sjekira", "buzdovan", "helebarda", "koplje" };
    Vojnik univerzalniVojnik;
    univerzalniVojnik.setZdravlje(95);
    univerzalniVojnik.setIzdrzljivost(95);
    univerzalniVojnik.setMoral(Moral::Visok);
    univerzalniVojnik.setOruzja((int)size(oruzja), oruzja);
    univerzalniVojnik.setStatus(true);
    Vojnik arnieSvarceneger(univerzalniVojnik);
    arnieSvarceneger.ispis();
    cout << endl << "Dealokacija..." << endl;
}
void zadatak2() {
    const char* oruzja[] = { "velika ratna sjekira",  "mac za dvije ruke" };
    Pjesak gimly;
    gimly.setOruzja((int)size(oruzja), oruzja);;
    gimly.setOklop("teski celicni oklop");
    gimly.setKategorija(Kategorija::Teska);
    Pjesak thorin(gimly);
    thorin.oglasiSe();
    thorin.ispis();
    cout << endl << "Dealokacija..." << endl;
}
void zadatak3() {
    const char* oruzja[] = { "velski dugacki luk", "samostrijel", "kratki mac" };
    Strijelac legolas;
    legolas.setOruzja((int)size(oruzja), oruzja);
    legolas.setMunicija(150);
    Strijelac vasilijZajcev(legolas);
    vasilijZajcev.setMoral(Moral::Visok);
    vasilijZajcev.setMunicija(55);
    vasilijZajcev.oglasiSe();
    vasilijZajcev.ispis();
    cout << endl << "Dealokacija..." << endl;
}
void zadatak4() {
    const char* oruzja[] = { "dugacko koplje", "buzdovan" };
    Konjanik eomer;
    eomer.setOruzja((int)size(oruzja), oruzja);
    eomer.setOklop("celicni oklop");
    eomer.setVrstaKonja("frizijski konj");
    Konjanik ghostRider(eomer);
    ghostRider.setZdravlje(75);
    ghostRider.setIzdrzljivost(80);
    ghostRider.setMoral(Moral::Visok);
    ghostRider.oglasiSe();
    ghostRider.ispis();
    cout << "\n\n";
    // testiranje metoda 'napadaj'
    Pjesak p1, p2, p3, p4, p5;
    Strijelac s1, s2, s3, s4, s5;
    Konjanik k1, k2, k3, k4, k5;
    cout << "Bitka pocinje: -->" << endl;
    p1.napadaj(&s1); // Pjesak napada strijelca (50% vjerovatnoca da uspije)
    p2.napadaj(&p1); // Pjesak napada pjesaka (50% vjerovatnoca da uspije)
    p1.napadaj(&k1); // Pjesak napada konjanika (50% vjerovatnoca da uspije)
    s1.napadaj(&s2); // Strijelac napada strijelca (50% vjerovatnoca da uspije)
    s2.napadaj(&k5); // Strijelac napada konjanika (50% vjerovatnoca da uspije)
    s4.napadaj(&p5); // Strijelac napada pjesaka (50% vjerovatnoca da uspije)
    k4.napadaj(&p3); // Konjanika napada pjesaka (50% vjerovatnoca da uspije)
    k4.napadaj(&k3); // Konjanik napada konjanika (50% vjerovatnoca da uspije)
    k4.napadaj(&s4); // Konjanik napada strijelca (50% vjerovatnoca da uspije)
    cout << endl << "Dealokacija..." << endl;
}
void zadatak5() {
    VojnaJedinica<Pjesak>* svicarskaGarda = new VojnaJedinica<Pjesak>("Svicarska garda", 560.5f, 120.5f);
    svicarskaGarda->setNaziv("Svicarska Garda");
    svicarskaGarda->setCijenaObuke(570.0f);
    svicarskaGarda->setCijenaOdrzavanja(120.0f);
    for (int i = 0; i < 150; i++)
        svicarskaGarda->addPripadnik(Pjesak(Kategorija::Srednja, "lagani oklop"));
    svicarskaGarda->ispis();
    cout << endl;

    VojnaJedinica<Pjesak>* vitezoviTemplari = new VojnaJedinica<Pjesak>(*svicarskaGarda);
    vitezoviTemplari->setNaziv("Vitezovi templari");
    for (int i = 0; i < 25; i++)
        vitezoviTemplari->addPripadnik(Pjesak(Kategorija::Teska, "teski metalni oklop"));
    vitezoviTemplari->setCijenaObuke(1180.0f);
    vitezoviTemplari->setCijenaOdrzavanja(1555.0f);
    vitezoviTemplari->ispis();
    delete svicarskaGarda;
    delete vitezoviTemplari;
    cout << endl << "Dealokacija..." << endl;
}
void zadatak6() {
    // pjesacka vojna jedinica :: 'Svicarska garda' [kreiramo pokazivac na genericki objekt]
    auto svicarskaGarda = new VojnaJedinica<Pjesak>("Svicarska garda", 550.0f, 130.0f);
    // pjesacka vojna jedinica :: 'varangijanska garda' [kreiramo pokazivac na genericki objekt]
    auto varangijanskaGarda = new VojnaJedinica<Pjesak>("Varangijanska garda", 670.0f, 160.0f);
    // pjesacka vojna jedinica :: 'Man At Arms' [kreiramo pokazivac na genericki objekt]
    auto manAtArms = new VojnaJedinica<Pjesak>("Man At Arms", 520.0f, 110.0f);
    // streljacka vojna jedinica :: 'englishLongbowman' [kreiramo pokazivac na genericki objekt]
    auto englishLongbowman = new VojnaJedinica<Strijelac>("Enlish Longbowman", 350.0f, 110.0f);
    // konjicka vojna jedinica :: 'bosanskaElitnaKonjica' [kreiramo pokazivac na genericki objekt]
    auto bosanskaElitnaKonjica = new VojnaJedinica<Konjanik>("Bosanska elitna konjica", 950.0f, 250.0f);
    // konjicka vojna jedinica :: 'katafrakte' [kreiramo pokazivac na genericki objekt]
    auto katafrakte = new VojnaJedinica<Konjanik>("Katafrakte", 850.0f, 230.0f);
    // konjicka vojna jedinica :: 'katafrakte' [kreiramo pokazivac na genericki objekt]
    auto viteska505 = new VojnaJedinica<Konjanik>("505. buzimska viteska brigada", 850.0f, 230.0f);

    for (int i = 0; i < 60; i++)
        svicarskaGarda->addPripadnik(Pjesak(Kategorija::Srednja, "lagani oklop"));
    for (int i = 0; i < 15; i++)
        varangijanskaGarda->addPripadnik(Pjesak(Kategorija::Teska, "celicni oklop"));
    for (int i = 0; i < 50; i++)
        manAtArms->addPripadnik(Pjesak(Kategorija::Srednja, "lagani oklop"));
    for (int i = 0; i < 60; i++)
        englishLongbowman->addPripadnik(Strijelac(100));
    for (int i = 0; i < 15; i++)
        bosanskaElitnaKonjica->addPripadnik(Konjanik("celicni oklop", "bosanski brdski konj"));
    for (int i = 0; i < 20; i++)
        katafrakte->addPripadnik(Konjanik("teski celicni oklop", "teski bizantijski konj"));
    for (int i = 0; i < 10; i++)
        viteska505->addPripadnik(Konjanik("teski celicni oklop sa ljiljanima", "bosanski bijeli konj"));

    // kreiranje armije sa sjevera
    Armija* sjevernaArmija = new Armija("Army Of The North");
    sjevernaArmija->dodajJedinicu(*svicarskaGarda);
    sjevernaArmija->dodajJedinicu(*varangijanskaGarda);
    sjevernaArmija->dodajJedinicu(*manAtArms);
    sjevernaArmija->dodajJedinicu(*englishLongbowman);
    sjevernaArmija->dodajJedinicu(*bosanskaElitnaKonjica);
    sjevernaArmija->dodajJedinicu(*katafrakte);
    sjevernaArmija->dodajJedinicu(*viteska505);
    sjevernaArmija->ispis();
    delete svicarskaGarda;
    delete varangijanskaGarda;
    delete manAtArms;
    delete englishLongbowman;
    delete bosanskaElitnaKonjica;
    delete katafrakte;
    delete viteska505;
    delete sjevernaArmija;
    cout << endl << "Dealokacija..." << endl;
}
void menu() {
    int nastaviDalje = 1;
    while (nastaviDalje == 1) {
        int izbor = 0;
        do {
            system("cls");
            cout << "::Zadaci::" << endl;
            cout << "(1) Zadatak 1" << endl;
            cout << "(2) Zadatak 2" << endl;
            cout << "(3) Zadatak 3" << endl;
            cout << "(4) Zadatak 4" << endl;
            cout << "(5) Zadatak 5" << endl;
            cout << "(6) Zadatak 6" << endl;
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 6);
        switch (izbor) {
        case 1: zadatak1(); cout << "Zadatak 1. Done." << endl; break;
        case 2: zadatak2(); cout << "Zadatak 2. Done." << endl; break;
        case 3: zadatak3(); cout << "Zadatak 3. Done." << endl; break;
        case 4: zadatak4(); cout << "Zadatak 4. Done." << endl; break;
        case 5: zadatak5(); cout << "Zadatak 5. Done." << endl; break;
        case 6: zadatak6(); cout << "Zadatak 6. Done." << endl; break;
        default:break;
        }
        do {
            cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
            cin >> nastaviDalje;
        } while (nastaviDalje != 0 && nastaviDalje != 1);
    }
}
int main() {
    menu();
    return 0;
}