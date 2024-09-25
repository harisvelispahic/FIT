#include <iostream>
using namespace std;

const char* crt = "\n-------------------------------\n";

// Z0.1 
char* alociraj(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, tekst);
    return temp;
}
// Z0.2 :: funkcija za prebrojavanje broja znamenki [voditi racuna i o negativnim vrijednostima]
int countDigits(int broj) {
    return (broj == 0) ? 1 : log10(abs(broj)) + 1;
}
// Z0.3 :: pretvoriti (int) u (char*) :: koristiti funkciju _itoa_s
char* intToStr(int broj) {
    int size = countDigits(broj) + 1;
    char* temp = new char[size];
    _itoa_s(broj, temp, size, 10);      // prima broj, buffer u koji cemo kopirati, velicinu i na kraju bazu sistema (10)
    return temp;
}

// Z0.4 :: funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char[]> alocirajUnique(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    unique_ptr<char[]> temp = make_unique<char[]>(size);
    strcpy_s(temp.get(), size, tekst);
    return temp;
}
// Z0.5:: Provjeriti da li su dva niza karaktera ista (po vrijednosti)
bool areEqual(const char* tekst1, const char* tekst2) {
    return strcmp(tekst1, tekst2) == 0;
}

class Uredjaj {
    const char* _id = nullptr; // pointer
    unique_ptr<char[]> _naziv; // default vrijednost = NULL
    int _godinaProizvodnje;
    unique_ptr<float> _cijena; // default vrijednost = NULL
    int* _garancija = nullptr;
    int _trenutnoOcjena = 0;
    int* _ocjene[100] = { nullptr };
public:

    // Z1.0 :: getteri
    const char* getId() const { return (_id == nullptr) ? "" : _id; }
    const char* getNaziv() const { return (_naziv == nullptr) ? "" : _naziv.get(); }
    int getGodinaProizvodnje() const { return _godinaProizvodnje; }
    float getCijena() const { return (_cijena == nullptr) ? 0.0f : *_cijena; }
    int getGarancija() const { return (_garancija == nullptr) ? 0 : *_garancija; }
    int getTrenutnoOcjena() const { return _trenutnoOcjena; }
    int** getOcjene() const { return (int**)_ocjene; }
    int getOcjena(int index) const {
        if (index < 0 || index >= getTrenutnoOcjena())
            return -1;
        return *_ocjene[index];
    }

    // Z1.1 :: staticka funkcija koja vraca niz karaktera (brojeva) u opsegu "10000" do "99999"
    static const char* getRandomId() {
        int vrijednost = rand() % 89999 + 10000;
        return intToStr(vrijednost);
    }
    // Z1.2 :: setteri
    void setId() {
        _id = alociraj(getRandomId());
    }
    void setId(const char* id) {
        _id = alociraj(id);
    }
    void setNaziv(const char* naziv) {
        _naziv = alocirajUnique(naziv);
    }
    void setGodinaProizvodnje(int godinaProizvodnje) {
        _godinaProizvodnje = godinaProizvodnje;
    }
    void setCijena(float cijena) {
        if (_cijena == nullptr)
            _cijena = make_unique<float>();
        *_cijena = cijena;
    }
    void setGarancija(int garancija) {
        if (_garancija == nullptr)
            _garancija = new int;
        *_garancija = garancija;
    }
    void setOcjene(int trenutno, int** ocjene = nullptr) {
        for (int i = 0; i < _trenutnoOcjena; i++) {
            delete _ocjene[i];
            _ocjene[i] = nullptr;
        }
        _trenutnoOcjena = 0;
        if (_ocjene != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodajOcjenu(*ocjene[i]);
            }
        }
        
    }

    // Z1.3 :: metoda za dodavanje ocjena [obavezno uraditi alokaciju]
    bool dodajOcjenu(int ocjena) {
        if (_trenutnoOcjena >= size(_ocjene))
            return false;
        _ocjene[_trenutnoOcjena++] = new int(ocjena);
        return true;
    }

    // Z1.4 :: postaviti '_id' na random vrijednost
    
    Uredjaj() {
        setId();
        setNaziv("---");
        setGodinaProizvodnje(0);
        setCijena(0);
        setGarancija(0);
        setOcjene(0);
    }
    // Z1.5 :: postaviti '_id' na random vrijednost
    Uredjaj(const char* naziv, int godinaProizvodnje, float cijena, int garancija) {
        setId();
        setNaziv(naziv);
        setGodinaProizvodnje(godinaProizvodnje);
        setCijena(cijena);
        setGarancija(garancija);
        setOcjene(0);
    }
    // Z1.6 :: postaviti '_id' na vrijednost '_id' iz drugog objekta
    Uredjaj(const Uredjaj& obj) {
        setId(obj.getId());
        setNaziv(obj.getNaziv());
        setGodinaProizvodnje(obj.getGodinaProizvodnje());
        setCijena(obj.getCijena());
        setGarancija(obj.getGarancija());
        setOcjene(obj.getTrenutnoOcjena(), obj.getOcjene());
    }

    // Z1.7 :: postaviti '_id' na vrijednost '_id' iz drugog objekta
    Uredjaj& operator =(const Uredjaj& obj) {
        if (this != &obj) {
            setId(obj.getId());
            setNaziv(obj.getNaziv());
            setGodinaProizvodnje(obj.getGodinaProizvodnje());
            setCijena(obj.getCijena());
            setGarancija(obj.getGarancija());
            setOcjene(obj.getTrenutnoOcjena(), obj.getOcjene());
        }
        return *this;
    }
    // Z1.10 :: virtuelni desktruktor
    virtual ~Uredjaj() {
        delete _id;
        delete _garancija;
        for (int i = 0; i < _trenutnoOcjena; i++) {
            delete _ocjene[i];
            _ocjene[i] = nullptr;
        }
    }
    // Z1.8 :: izracunati aritmeticku sredinu
    float izracunajProsjek() {
        float suma = 0.0f;
        for (int i = 0; i < _trenutnoOcjena; i++) {
            suma += *_ocjene[i];
        }
        return suma / _trenutnoOcjena;
    }
    // Z1.9 :: virtuelna metoda za ispisivanje
    virtual void ispis() {
        cout << "Uredjaj" << crt;
        cout << "ID: " << getId() << endl;
        cout << "Naziv: " << getNaziv() << endl;
        cout << "Godina proizvodnje: " << getGodinaProizvodnje() << endl;
        cout << "Cijena: " << getCijena() << endl;
        cout << "Garancija: " << getGarancija() << endl;
        cout << "Ocjene: " << endl << "\t";
        for (int i = 0; i < _trenutnoOcjena; i++) {
            cout << *_ocjene[i] << ", ";
        }
    }
    
};

// Z1.11 :: porediti samo obiljezje 'Id'
bool operator == (const Uredjaj& u1, const Uredjaj& u2) {
    /*
    const char* _id = nullptr; // pointer
    unique_ptr<char[]> _naziv; // default vrijednost = NULL
    int _godinaProizvodnje;
    unique_ptr<float> _cijena; // default vrijednost = NULL
    int* _garancija = nullptr;
    int _trenutnoOcjena = 0;
    int* _ocjene[100] = { nullptr };
    */
    if (!areEqual(u1.getId(), u2.getId()) ||
        !areEqual(u1.getNaziv(), u2.getNaziv()) ||
        u1.getGodinaProizvodnje() != u2.getGodinaProizvodnje() ||
        u1.getCijena() != u2.getCijena() ||
        u1.getGarancija() != u2.getGarancija() ||
        u1.getTrenutnoOcjena() != u2.getTrenutnoOcjena())
        return false;
    for (int i = 0; i < u1.getTrenutnoOcjena(); i++) {
        if (u1.getOcjena(i) != u2.getOcjena(i))
            return false;
    }
    return true;
}
bool operator != (const Uredjaj& u1, const Uredjaj& u2) {
    return !(u1 == u2);
}

class Mobitel : public Uredjaj {
    char _operativniSistem[50] = "";
    unique_ptr<float> _velicinaEkrana; // u incima Npr. 6.1
    int* _memorija = nullptr; // in GB
public:
    // Z2.1 :: getteri
    const char* getOperativniSistem() const { return _operativniSistem; }
    float getVelicinaEkrana() const { return (_velicinaEkrana == nullptr) ? 0.0f : *_velicinaEkrana; }
    int getMemorija() const { return (_memorija == nullptr) ? 0 : *_memorija; }

    // Z2.2 :: setteri
    void setOperativniSistem(const char* operativniSistem) {
        strcpy_s(_operativniSistem, strlen(operativniSistem) + 1, operativniSistem);
    }
    void setVelicinaEkrana(float velicinaEkrana) {
        if (_velicinaEkrana == nullptr)
            _velicinaEkrana = make_unique<float>();
        *_velicinaEkrana = velicinaEkrana;
    }
    void setMemorija(int memorija) {
        if (_memorija == nullptr)
            _memorija = new int;
        *_memorija = memorija;
    }

    // Z2.3 :: dflt ctor
    Mobitel() : Uredjaj(){
        setOperativniSistem("");
        setVelicinaEkrana(0);
        setMemorija(0);
    }
    // Z2.4 :: user-defined ctor
    Mobitel(const char* naziv, int godinaP, float cijena, int garancija, const char* operativniS, float velicinaE, int memorija) 
        :Uredjaj(naziv, godinaP, cijena, garancija)
    {
        setOperativniSistem(operativniS);
        setVelicinaEkrana(velicinaE);
        setMemorija(memorija);
    }
    // Z2.5 :: copy ctor
    Mobitel(const Mobitel& obj) : Uredjaj(obj){
        setOperativniSistem(obj.getOperativniSistem());
        setVelicinaEkrana(obj.getVelicinaEkrana());
        setMemorija(obj.getMemorija());
    }

    // Z2.6 :: operator '='
    Mobitel& operator = (const Mobitel& obj) {
        if (this != &obj) {
            (Uredjaj&)(*this) = obj;    // poziva se copy-ctor, da nema reference, ovdje bi nastao samo temporary objekat koji bi nestao sa zavrsetkom ove funkcije
            setOperativniSistem(obj.getOperativniSistem());
            setVelicinaEkrana(obj.getVelicinaEkrana());
            setMemorija(obj.getMemorija());
        }
        return *this;
    }
    // Z2.7 :: metoda za ispis atributa
    // ispisati id, naziv mobitela, velicinu ekrana, operativni sistem, kolicinu memorije, cijenu te broj godina garancije
    void ispis() {
        cout << "Mobitel" << crt;
        cout << "Id: " << getId() << endl;
        cout << "Naziv: " << getNaziv() << endl;
        cout << "Velicina ekrana: " << getVelicinaEkrana() << endl;
        cout << "Operativni sistem: " << getOperativniSistem() << endl;
        cout << "Kolicina memorije: " << getMemorija() << endl;
        cout << "Cijena: " << getCijena() << endl;
        cout << "Broj godina garancije: " << getGarancija() << endl;

    }
    // Z2.8 :: dtor
    ~Mobitel() {
        delete _memorija; _memorija = nullptr;
    }
};

// Z2.9 :: porediti na osnovu obiljezja 'Id'
bool operator == (const Mobitel& m1, const Mobitel& m2) {
    return (Uredjaj&)m1 == (Uredjaj&)m2 && 
        areEqual(m1.getOperativniSistem(), m2.getOperativniSistem()) &&
        m1.getVelicinaEkrana() == m2.getVelicinaEkrana() &&
        m1.getMemorija() == m2.getMemorija();
}
bool operator != (const Mobitel& m1, const Mobitel& m2) {
    return !(m1 == m2);
}

class Televizor : public Uredjaj {
    unique_ptr<float> _velicinaEkrana;
    unique_ptr<char[]> _tipEkrana;
    pair<int, int> _rezolucija;
    int _trenutnoPrikljucaka = 0;
    const char* _prikljucci[20] = { nullptr }; // niz tekstova
public:
    // Z3.1 :: getteri
    float getVelicinaEkrana() const { return (_velicinaEkrana == nullptr) ? 0.0f : *_velicinaEkrana; }
    const char* getTipEkrana() const { return (_tipEkrana == nullptr) ? "" : _tipEkrana.get(); }
    pair<int, int> getRezolucija() const { return _rezolucija; }
    int getTrenutnoPrikljucaka() const { return _trenutnoPrikljucaka; }
    const char** getPrikljucci() const { return (const char**)_prikljucci; }
    const char* getPrikljucak(int index) const {
        return (index < 0 || index >= getTrenutnoPrikljucaka()) ? "" : _prikljucci[index];
    }
    // Z3.2 :: setteri
    void setVelicinaEkrana(float velicinaEkrana) {
        if (_velicinaEkrana == nullptr)
            _velicinaEkrana = make_unique<float>();
        *_velicinaEkrana = velicinaEkrana;
    }
    void setTipEkrana(const char* tipEkrana) {
        _tipEkrana = alocirajUnique(tipEkrana);
    }
    void setRezolucija(pair<int, int> rezolucija) {
        _rezolucija = rezolucija;
    }
    void setPrikljucci(int trenutno, const char** prikljucci = nullptr) {
        for (int i = 0; i < _trenutnoPrikljucaka; i++) {
            delete[] _prikljucci[i];
            _prikljucci[i] = nullptr;
        }
        _trenutnoPrikljucaka = 0;
        
        if (prikljucci != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodajPrikljucak(prikljucci[i]);
            }
        }
    }

    // Z3.3 :: metoda za dodavanje novog prikljucka za TV [obavezno uraditi alokaciju dinamickog niza]
    bool dodajPrikljucak(const char* prikljucak) {
        if (_trenutnoPrikljucaka >= 20)
            return false;
        _prikljucci[_trenutnoPrikljucaka++] = alociraj(prikljucak);
        return true;
    }

    // Z3.4 :: dflt ctor
    Televizor() : Uredjaj() {
        setVelicinaEkrana(0);
        setTipEkrana("");
        setRezolucija(make_pair<int, int>(0, 0));
        _trenutnoPrikljucaka = 0;
        setPrikljucci(0);
    }
    // Z3.5 :: user-defined ctor
    Televizor(const char* naziv, int godinaP, float cijena, int garancija, float velicinaEkrana, const char* tipEkrana, pair<int, int> rezolucija) 
        :Uredjaj(naziv, godinaP, cijena, garancija)
    {
        setVelicinaEkrana(velicinaEkrana);
        setTipEkrana(tipEkrana);
        setRezolucija(rezolucija);
        setPrikljucci(0);
    }
    // Z3.6 :: copy ctor
    Televizor(const Televizor& obj) : Uredjaj(obj) {
        setVelicinaEkrana(obj.getVelicinaEkrana());
        setTipEkrana(obj.getTipEkrana());
        setRezolucija(obj.getRezolucija());
        setPrikljucci(obj.getTrenutnoPrikljucaka(), obj.getPrikljucci());
    }

    // Z3.7 :: operator '='
    Televizor& operator = (const Televizor& obj) {
        if (this != &obj) {
            (Uredjaj&)(*this) = obj;
            setVelicinaEkrana(obj.getVelicinaEkrana());
            setTipEkrana(obj.getTipEkrana());
            setRezolucija(obj.getRezolucija());
            setPrikljucci(obj.getTrenutnoOcjena(), obj.getPrikljucci());
        }
        return *this;
    }
    // Z3.8 :: ispisati id, naziv TV-a, velicinu ekrana, tip ekrana, rezoluciju, cijenu, broj godina garancije, te sve prikljucke
    void ispis() {
        cout << "Televizor " << crt;
        cout << "Id: " << getId() << endl;
        cout << "Naziv: " << getNaziv() << endl;
        cout << "Velicina ekrana: " << getVelicinaEkrana() << endl;
        cout << "Tip ekrana: " << getTipEkrana() << endl;
        cout << "Rezolucija: " << getRezolucija().first << " x " << getRezolucija().second << endl;
        cout << "Cijena: " << getCijena() << endl;
        cout << "Broj godina garancije: " << getGarancija() << endl;
        cout << "Prikljucci: " << endl;
        for (int i = 0; i < getTrenutnoPrikljucaka(); i++) {
            cout << "\t" << getPrikljucak(i) << endl;
        }

    }
    // Z3.9 :: dtor
    ~Televizor() {
        for (int i = 0; i < getTrenutnoPrikljucaka(); i++) {
            delete[] _prikljucci[i];
            _prikljucci[i] = nullptr;
        }
    }
};

// Z3.10 :: porediti po obiljezju 'id'
bool operator == (const Televizor& t1, const Televizor& t2) {
    
    if ((Uredjaj&)t1 != (Uredjaj&)t2 ||
        t1.getVelicinaEkrana() != t2.getVelicinaEkrana() ||
        !areEqual(t1.getTipEkrana(), t2.getTipEkrana()) ||
        t1.getRezolucija() != t2.getRezolucija() ||
        t1.getTrenutnoPrikljucaka() != t2.getTrenutnoPrikljucaka())
        return false;
    for (int i = 0; i < t1.getTrenutnoPrikljucaka(); i++) {
        if (!areEqual(t1.getPrikljucak(i), t2.getPrikljucak(i)))
            return false;
    }
    return true;
}
bool operator != (const Televizor& t1, const Televizor& t2) {
    return !(t1 == t2);
}

class Printer : public Uredjaj {
    int* _brzinaPrintanja = nullptr; // br. str. po minuti
public:

    // Z4.1 :: getteri
    int getBrzinaPrintanja() const { return (_brzinaPrintanja == nullptr) ? 0 : *_brzinaPrintanja; }
    // Z4.2 :: setteri
    void setBrzinaPrintanja(int brzina) {
        if (_brzinaPrintanja == nullptr)
            _brzinaPrintanja = new int;
        *_brzinaPrintanja = brzina;
    }

    // 4.3 :: dflt ctor
    Printer() : Uredjaj() {
        setBrzinaPrintanja(0);
    }
    // 4.4 :: user-defined ctor
    Printer(const char* naziv, int godinaP, float cijena, int garancija, int brzinaPrintanja) 
        : Uredjaj(naziv, godinaP, cijena, garancija)
    {
        setBrzinaPrintanja(brzinaPrintanja);
    }
    // Z4.5 :: copy ctor
    Printer(const Printer& obj) :Uredjaj(obj) {
        setBrzinaPrintanja(obj.getBrzinaPrintanja());
    }

    // Z4.6 :: operator '='
    Printer& operator= (const Printer& obj) {
        if (this != &obj) {
            (Uredjaj&)(*this) = obj;
            setBrzinaPrintanja(obj.getBrzinaPrintanja());
        }
        return *this;
    }
    // Z4.7 :: ispisati id, naziv, brzinu printanja, cijenu te broj godina garancije
    void ispis() {
        cout << "Printer" << crt;
        cout << "Id: " << getId() << endl;
        cout << "Naziv: " << getNaziv() << endl;
        cout << "Brzina printanja: " << getBrzinaPrintanja() << endl;
        cout << "Cijena: " << getCijena() << endl;
        cout << "Broj godina garancije: " << getGarancija() << endl;
    }
    // Z4.8
    ~Printer() {
        delete _brzinaPrintanja; _brzinaPrintanja = nullptr;
    }
};
// Z4.9 :: porediti po obiljezju 'id'
bool operator == (const Printer& p1, const Printer& p2) {
    return (Uredjaj&)p1 == (Uredjaj&)p2 && p1.getBrzinaPrintanja() == p2.getBrzinaPrintanja();
}
bool operator != (const Printer& p1, const Printer& p2) {
    return !(p1 == p2);
}

class WebShop {
    char* _naziv = nullptr;
    char _emailAdresa[100] = "";
    int _trenutnoUredjaja = 0;
    Uredjaj* _uredjaji[100] = { nullptr }; // niz pokazivaca tipa 'Uredjaj' [niz mobitela, televizora, printera i drugih uredjaja]
public:
    // Z5.1 :: getteri
    const char* getNaziv() const { return (_naziv == nullptr) ? "" : _naziv; }
    const char* getEmail() const { return _emailAdresa; }
    int getTrenutno() const { return _trenutnoUredjaja; }
    Uredjaj* getUredjaj(int index) const { return _uredjaji[index]; }
    Uredjaj** getUredjaji() const { return (Uredjaj**)_uredjaji; }

    // Z5.2 :: setteri
    void setNaziv(const char* naziv) {
        delete[] _naziv;
        _naziv = alociraj(naziv);
    }
    void setEmailAdresa(const char* emailAdresa) {
        strcpy_s(_emailAdresa, strlen(emailAdresa) + 1, emailAdresa);
    }
    // u sljedecoj metodi koristiti dinamičko kastiranje (dynamic_cast) prilikom kopiranja i alokacije pokazivaca tipa 'Uredjaji'
    void setUredjaji(int trenutno, Uredjaj** uredjaji = nullptr) {
        for (int i = 0; i < _trenutnoUredjaja; i++) {
            delete _uredjaji[i];
            _uredjaji[i] = nullptr;
        }
        _trenutnoUredjaja = 0;

        if (uredjaji != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                //dodajUredjaj(*uredjaji[i]);
                Mobitel* mobitel = dynamic_cast<Mobitel*>(uredjaji[i]);
                if (mobitel != nullptr) {
                    dodajUredjaj(*mobitel);
                    continue;
                }

                Televizor* televizor = dynamic_cast<Televizor*>(uredjaji[i]);
                if (televizor != nullptr) {
                    dodajUredjaj(*televizor);
                    continue;
                }

                Printer* printer = dynamic_cast<Printer*>(uredjaji[i]);
                if (printer != nullptr) {
                    dodajUredjaj(*printer);
                    continue;
                }

                Uredjaj* uredjaj = dynamic_cast<Uredjaj*>(uredjaji[i]);
                if (uredjaj != nullptr) {
                    dodajUredjaj(*uredjaj);
                    continue;
                }
            }
        }
    }

    // Z5.3 :: genericka metoda za dodavanje uredjaja
    template <class T>
    bool dodajUredjaj(T uredjaj) {
        if (_trenutnoUredjaja >= 100)
            return false;
        _uredjaji[_trenutnoUredjaja++] = new T(uredjaj);
        return true;
    }
    // Z5.4 :: dflt ctor
    WebShop() {
        setNaziv("-");
        setEmailAdresa("");
        _trenutnoUredjaja = 0;
        setUredjaji(0);
    }
    // Z5.5 :: user-defined ctor
    WebShop(const char* naziv, const char* emailAdresa) {
        setNaziv(naziv);
        setEmailAdresa(emailAdresa);
        setUredjaji(0);
    }
    // Z5.6 :: copy-ctor
    WebShop(const WebShop& obj) {
        setNaziv(obj.getNaziv());
        setEmailAdresa(obj.getEmail());
        setUredjaji(obj.getTrenutno(), obj.getUredjaji());
    }
    // Z5.7 :: operator '='
    WebShop& operator = (const WebShop& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setEmailAdresa(obj.getEmail());
            setUredjaji(obj.getTrenutno(), obj.getUredjaji());
        }
        return *this;
    }
    // Z5.8 :: dtor
    ~WebShop() {
        delete[] _naziv; _naziv = nullptr;
        for (int i = 0; i < _trenutnoUredjaja; i++) {
            delete _uredjaji[i];
            _uredjaji[i] = nullptr;
        }
    }
};
// Z5.9 :: preklopiti operator '<<' za ispis podataka o webshopu
ostream& operator << (ostream& COUT, const WebShop& obj) {
    COUT << "Webshop" << crt;
    COUT << "Naziv: " << obj.getNaziv() << endl;
    COUT << "Email: " << obj.getEmail() << endl;
    COUT << "Uredjaji: " << endl;
    for (int i = 0; i < obj.getTrenutno(); i++) {

        obj.getUredjaji()[i]->ispis() ;
    }
    return COUT;
}

void zadatak1() {
    // testiranje klase 'Uredjaj'
    Uredjaj tm;
    tm.setNaziv("Google Time Machine");
    tm.setGodinaProizvodnje(2020);
    tm.setCijena(19999.99f);
    tm.setGarancija(42);
    // dodavanje ocjena
    tm.dodajOcjenu(10);
    tm.dodajOcjenu(9);
    tm.dodajOcjenu(7);
    tm.dodajOcjenu(9);
    tm.dodajOcjenu(10);
    tm.dodajOcjenu(8);
    // pokazivac na objekt
    Uredjaj* p = new Uredjaj(tm);
    p->ispis(); // poziv virtuelne metode 'ispis'
    delete p; // dealokacija + poziv virtuelnog destruktora
    cout << endl << "Dealokacija..." << endl;
}
void zadatak2() {
    Mobitel starPhone("Samsung Galaxy S23 Ultra", 2023, 2500, 3, "Android", 6.0, 32);
    starPhone.dodajOcjenu(9);
    starPhone.dodajOcjenu(10);
    starPhone.dodajOcjenu(10);
    starPhone.dodajOcjenu(10);
    // ilustracija koristenja pokazivackog polimorfizma
    Uredjaj* p = new Mobitel(starPhone); // pokazivac bazne klase cuva adresu objekta izvedene klase 
    p->ispis(); // poziva se metoda 'Mobitel::ispis'
    cout << "Prosjecna ocjena: " << p->izracunajProsjek() << endl; // poziva se metoda 'Uredjaj::izracunajProsjek'
    delete p;
}
void zadatak3() {
    Televizor chrometius("Chrometius Smart TV", 2023, 1499, 3, 65.5, "LED", { 3840, 2160 });
    chrometius.dodajOcjenu(10);
    chrometius.dodajOcjenu(10);
    chrometius.dodajOcjenu(9);
    chrometius.dodajOcjenu(10);
    chrometius.dodajOcjenu(10);
    chrometius.dodajPrikljucak("HDMI");
    chrometius.dodajPrikljucak("Scart");
    // ilustracija koristenja pokazivackog polimorfizma
    Uredjaj* p = new Televizor(chrometius); // pokazivac bazne klase cuva adresu objekta izvedene klase 
    p->ispis(); // poziva se metoda 'Televizor::ispis'
    cout << "Prosjecna ocjena: " << p->izracunajProsjek() << endl; // poziva se metoda 'Uredjaj::izracunajProsjek'
    delete p;
}
void zadatak4() {
    Printer optomec("Optomec X-40", 2023, 550, 2, 30);
    optomec.dodajOcjenu(10);
    optomec.dodajOcjenu(8);
    optomec.dodajOcjenu(9);
    optomec.dodajOcjenu(9);
    optomec.dodajOcjenu(10);
    // ilustracija koristenja pokazivackog polimorfizma
    Uredjaj* p = new Printer(optomec); // pokazivac bazne klase cuva adresu objekta izvedene klase 
    p->ispis(); // poziva se metoda 'Printer::ispis'
    cout << "Prosjecna ocjena: " << p->izracunajProsjek() << endl; // poziva se metoda 'Uredjaj::izracunajProsjek'
    delete p;
}
void zadatak5() {
    WebShop bosnianVortex("Bosnian Vortex", "bosnian.vortex@gmail.com");
    // Uredjaji ...
    Uredjaj napojna("Corsair Napojna jedinica", 2022, 159.0, 2);
    Mobitel wikkoJerry("WIKO JERRY 3 ANTHRACITE", 2021, 149.0, 2, "Android 8.1", 5.45f, 16);
    Televizor phillipsTV("PHILIPS LED TV AMBILIGHT", 2023, 899.0, 3, 43.0, "LED", { 3840, 2160 });
    Printer officeJet("B-HP OFFICEJET 202", 2020, 549.0, 2, 20);
    //Dodavanje razlicitih tipova uredjaja
    bosnianVortex.dodajUredjaj<Uredjaj>(napojna); //Mozete izostaviti naziv generickog tipa tj: bosnianVortex.DodajUredjaj(napojna);
    bosnianVortex.dodajUredjaj<Mobitel>(wikkoJerry);
    bosnianVortex.dodajUredjaj<Televizor>(phillipsTV);
    bosnianVortex.dodajUredjaj<Printer>(officeJet);
    // copy ctor
    WebShop cc(bosnianVortex);
    cout << cc << endl;
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
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 5);
        switch (izbor) {
        case 1: zadatak1(); cout << "Zadatak 1. Done." << endl; break;
        case 2: zadatak2(); cout << "Zadatak 2. Done." << endl; break;
        case 3: zadatak3(); cout << "Zadatak 3. Done." << endl; break;
        case 4: zadatak4(); cout << "Zadatak 4. Done." << endl; break;
        case 5: zadatak5(); cout << "Zadatak 5. Done." << endl; break;
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