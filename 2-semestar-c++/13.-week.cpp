#include <iostream>
#include <exception>
#include <functional>
using namespace std;

// Z0.1 :: funkcija 'alociraj'
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



class Greska : public exception {
    int _linija;
    const char* _funkcija = nullptr;
public:
    // Z0.4 :: getteri
    const char* getPoruka() const { return what(); }
    int getLinija() const { return _linija; }
    const char* getFunkcija() const { return _funkcija == nullptr ? "" : _funkcija; }

    // Z0.5 :: setteri
    void setLinija(int linija) {
        _linija = linija;
    }
    void setFunkcija(const char* funkcija) {
        _funkcija = alociraj(funkcija);
    }

    // Z0.6 :: user-def. ctor
    Greska(const char* poruka, int linija, const char* funkcija) : exception(poruka) {
        setLinija(linija);
        setFunkcija(funkcija);
    }
    // Z0.7 :: copy ctor
    Greska(const Greska& obj) : exception(obj) {
        setLinija(obj.getLinija());
        setFunkcija(obj.getFunkcija());
    }
    // Z0.8 :: operator '='
    Greska& operator =(const Greska& obj) {
        if (this != &obj) {
            (exception&)(*this) = obj;
            setLinija(obj.getLinija());
            setFunkcija(obj.getFunkcija());
        }
        return *this;
    }
    // Z0.9 :: dtor
    ~Greska() {
        delete[] _funkcija; _funkcija = nullptr;
    }
};
// Z0.10 :: operator '<<' za ispis podataka o Greski
ostream& operator <<(ostream& COUT, const Greska& obj) {
    COUT << "Greska: " << obj.getPoruka() << endl;
    COUT << "Linija: " << obj.getLinija() << endl;
    COUT << "Funkcija: " << obj.getFunkcija() << endl;
    return COUT;
}

// kolekcija elemenata 'Vektor' (tipa T) sa mogucnoscu dinamickog prosirivanja
template<class T>
class Vektor {
    int _trenutno = 0;
    int _maxElemenata;
    T* _elementi = nullptr;
public:
    // Z1.1 :: getteri
    int getTrenutno() const { return _trenutno; }
    int getMaxElemenata() const { return _maxElemenata; }
    T* getElementi() const { return _elementi; }

    // Z1.2 :: setteri (u ovom slucaju imamo samo jednu setter funkciju)
    void setElementi(int trenutno, int maxElemenata, T* elementi = nullptr) {
        delete[] _elementi;
        _elementi = new T[maxElemenata];
        _trenutno = 0;

        if (elementi != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodaj(elementi[i]);
            }
        }
    }
    // Z1.3 :: funkcija za dodavanje elementa tipa 'T'.
    // U slucaju da je brojac dosao do kraja -- uraditi prosirivanje niza za 10 elemenata.
    void dodaj(const T& element) {
        if (_trenutno >= _maxElemenata)
            expandElementi(10);
        _elementi[_trenutno++] = element;
    }

    // Z1.4 :: funkcija za uklanjanje zadnjeg elementa iz niza
    bool removeZadnji() {
        if (_trenutno == 0)
            return false;
        _trenutno--;
        return true;
    }
    // Z1.5 :: funkcija za prosirivanje dinamickog niza
    void expandElementi(int uvecanje) {
        T* temp = new T[_trenutno + uvecanje];
        for (int i = 0; i < _trenutno; i++) {
            temp[i] = _elementi[i];
        }
        delete[] _elementi;
        _elementi = temp;
    }
    // Z1.6 :: dflt ctor
    Vektor(int maxElemenata = 100) {
        _maxElemenata = maxElemenata;
        setElementi(0, maxElemenata);
    }
    // Z1.7 :: copy ctor :: Kopirati vrijednosti jednog vektora u drugi
    Vektor(const Vektor<T>& obj) {
        _maxElemenata = obj.getMaxElemenata();
        _trenutno = obj.getTrenutno();
        setElementi(obj.getTrenutno(), obj.getMaxElemenata(), obj.getElementi());
    }
    // Z1.8 :: operator '='
    Vektor<T>& operator = (const Vektor<T>& obj) {
        if (this != &obj) {
            _maxElemenata = obj.getMaxElemenata();
            _trenutno = obj.getTrenutno();
            setElementi(obj.getTrenutno(), obj.getMaxElemenata(), obj.getElementi());
        }
        return *this;
    }
    // Z1.9 :: operator '[]' za dohvacanje pojedinacne vrijednosti iz niza
    // U slucaju da je vektor prazan, 'baciti' izutetak (objekt klase 'Greska')
    // Postupiti na isti nacin i u slucaju da je 'index' izvan opsega granica vektora
    T& operator [] (int index) const {
        if (_trenutno == 0)
            throw Greska("Vektor je prazan!", __LINE__, __FUNCTION__);
        if (index < 0 || index >= _trenutno)
            throw Greska("Indeks van granica!", __LINE__, __FUNCTION__);
        return _elementi[index];
    }

    // Z1.10 :: funkcija za provjeru postojanosti vrijednosti 'element' u okviru dinamickog niza
    bool checkIfContains(T element) {
        for (int i = 0; i < _trenutno; i++) {
            if (_elementi[i] == element)
                return true;
        }
        return false;
    }

    // Z1.11
    // Map je funkcija viseg reda (higher-order function), koja aplicira datu funkciju 'f' na svaki element niza.
    // Niz :[e1, e2, e3, e4, e5, ..., en]
    // Rezultat => [f(e1), f(e2), f(e3), f(e4), f(e5), ..., f(en)]
    void map(function<void(T&)> f) {
        for (int i = 0; i < _trenutno; i++) {
            f(_elementi[i]);
        }
    }

    // Z1.12
    // Filter je funkcija viseg reda (higher-order function), koja aplicira datu filter funkciju 'f' na svaki element niza.
    // Rezultat aplikacije filter funkcije je niz elemenata koji zadovoljavaju uslov (odredjen tom istom funkcijom)
    // Niz :[e1, e2, e3, e4, e5, ..., en]
    // Rezultat => [svaki element niza za kojeg vazi f(x) == true]
    Vektor<T> filter(function<bool(T&)> f) {
        Vektor<T> temp;

        for (int i = 0; i < _trenutno; i++) {
            if (f(_elementi[i]))
                temp.dodaj(_elementi[i]);
        }

        return temp;
    }
    // Z1.13
    // Reduce (accumulate) je funkcija viseg reda (higher-order function) zaduzena za agregaciju vrijednosti niza. 
    // Funkcija reduce primjenjuje datu funkciju 'f' izmjedju susjednih elemenata i pritom dobija medjurezultate.
    // ----------------------------------------------
    // Primjer: Suma :: f(a,b) = a+b
    // Niz vrijednosti: [5, 1, 3, 4, 2]
    //  f(5, 1), 3, 4, 2 => 6, 3, 4, 2
    //  f(6, 3), 4, 2 => 9, 4, 2
    //  f(9, 4), 2] => 13, 2
    //  f(13, 2) => 15
    // ----------------------------------------------
    // Primjer: Max :: f(a,b) = (a>=b)?a:b;
    // Niz vrijednosti: [5, 6, 3, 8, 2]
    //  f(5, 6), 3, 8, 2 => 6, 3, 8, 2
    //  f(6, 3), 8, 2 => 6, 8, 2
    //  f(6, 8), 2 => 8, 2
    //  f(8, 2) => 8
    // ----------------------------------------------
    T reduce(function<T(T, T)> f) {
        T rezultat = (_trenutno > 0) ? _elementi[0] : T();
        for (int i = 0; i < _trenutno - 1; i++) {
            rezultat = f(_elementi[i], _elementi[i + 1]);
            _elementi[i + 1] = rezultat;
        }

        return rezultat;
    }

    // Z1.14 :: destruktor
    ~Vektor() {
        delete[] _elementi; _elementi = nullptr;
    }
};


// Z1.15 :: funkcija 'ispis' za ispisivanje broja elemenata i svih elemenata (razdvojenih delimiterom)
template<class T>
void ispis(const Vektor<T>& obj, const char* delimiter = " ") {
    for (int i = 0; i < obj.getTrenutno(); i++) {
        cout << obj.getElementi()[i] << delimiter;
    }
    cout << endl;
}
// Z1.16
template<class T>
bool operator == (const Vektor<T>& v1, const Vektor<T>& v2) {
    if (v1.getTrenutno() != v2.getTrenutno())
        return false;
    for (int i = 0; i < v1.getTrenutno(); i++)
        if (v1[i] != v2[i])
            return false;
    return true;
}
// Z1.17
template<class T>
bool operator != (const Vektor<T>& v1, const Vektor<T>& v2) {
    return !(v1 == v2);
}
// Z1.18
template<class T>
bool operator == (const Vektor<const char*>& v1, const Vektor<const char*>& v2) {
    if (v1.getTrenutno() != v2.getTrenutno()) {
        return false;
    }
    for (int i = 0; i < v1.getTrenutno(); i++) {
        if (!areEqual(v1.getElementi()[i], v2.getElementi()[i])) {
            return false;
        }
    }
    return true;
}
// Z1.19
template<class T>
bool operator != (const Vektor<const char*>& v1, const Vektor<const char*>& v2) {
    return !(v1 == v2);
}

enum class Spol { Muski = 1, Zenski = 0 };

ostream& operator << (ostream& COUT, const Spol& obj) {
    if (obj == Spol::Muski)
        cout << "Muski";
    else
        cout << "Zenski";
    return COUT;
}

enum class Boja { Plava, Zelena, Zuta, Crvena, Crna, Bijela, Smedja };
// Z1.20
ostream& operator << (ostream& COUT, const Boja& obj) {
    switch (obj) {
    case Boja::Plava: cout << "Plava"; break;
    case Boja::Zelena: cout << "Zelena"; break;
    case Boja::Zuta: cout << "Zuta"; break;
    case Boja::Crvena: cout << "Crvena"; break;
    case Boja::Crna: cout << "Crna"; break;
    case Boja::Bijela: cout << "Bijela"; break;
    case Boja::Smedja: cout << "Smedja"; break;
    default:
        break;
    }
    return COUT;
}

class Osoba {
    const char* _jmbg = nullptr;
    pair<unique_ptr<char[]>, unique_ptr<char[]>> _imePrezime;
    unique_ptr<Spol> _spol;
    float* _visina = nullptr;
    Boja* _bojaOciju = nullptr;
    Boja* _bojaKose = nullptr;
public:
    // Z3.1 :: getteri
    const char* getJmbg() const { return (_jmbg == nullptr) ? "" : _jmbg; }
    const char* getIme() const { return (_imePrezime.first == nullptr) ? "" : _imePrezime.first.get(); }
    const char* getPrezime() const { return (_imePrezime.second == nullptr) ? "" : _imePrezime.second.get(); }
    Spol getSpol() const { return (_spol == nullptr) ? Spol::Zenski : *_spol; }
    float getVisina() const { return (_visina == nullptr) ? 0.0f : *_visina; }
    Boja getBojaOciju() const { return (_bojaOciju == nullptr) ? Boja::Smedja : *_bojaOciju; }
    Boja getBojaKose() const { return (_bojaKose == nullptr) ? Boja::Smedja : *_bojaKose; }

    // Z3.2 :: setteri
    void setJmbg(const char* jmbg) {
        delete[] _jmbg;
        _jmbg = alociraj(jmbg);
    }
    void setIme(const char* ime) {
        _imePrezime.first = alocirajUnique(ime);
    }
    void setPrezime(const char* prezime) {
        _imePrezime.second = alocirajUnique(prezime);
    }
    void setSpol(Spol spol) {
        if (_spol == nullptr)
            _spol = make_unique<Spol>();
        *_spol = spol;
    }
    void setVisina(float visina) {
        if (_visina == nullptr)
            _visina = new float;
        *_visina = visina;
    }
    void setBojaOciju(Boja bojaOciju) {
        if (_bojaOciju == nullptr)
            _bojaOciju = new Boja();
        *_bojaOciju = bojaOciju;
    }
    void setBojaKose(Boja bojaKose) {
        if (_bojaKose == nullptr)
            _bojaKose = new Boja();
        *_bojaKose = bojaKose;
    }

    // Z3.3 :: dflt ctor
    Osoba() {
        setJmbg("");
        setIme("");
        setPrezime("");
        setSpol(Spol());
        setVisina(0.0f);
        setBojaOciju(Boja());
        setBojaKose(Boja());
    }
    // Z3.4 :: user-def ctor
    Osoba(const char* jmbg, const char* ime, const char* prezime, Spol spol, float visina, Boja bojaOciju, Boja bojaKose) {
        setJmbg(jmbg);
        setIme(ime);
        setPrezime(prezime);
        setSpol(spol);
        setVisina(visina);
        setBojaOciju(bojaOciju);
        setBojaKose(bojaKose);
    }
    // Z3.5 :: copy ctor
    Osoba(const Osoba& obj) {
        setJmbg(obj.getJmbg());
        setIme(getIme());
        setPrezime(obj.getPrezime());
        setSpol(obj.getSpol());
        setVisina(obj.getVisina());
        setBojaOciju(obj.getBojaOciju());
        setBojaKose(obj.getBojaKose());
    }
    // Z3.6 :: operator '='
    Osoba& operator = (const Osoba& obj) {
        if (this != &obj) {
            setJmbg(obj.getJmbg());
            setIme(getIme());
            setPrezime(obj.getPrezime());
            setSpol(obj.getSpol());
            setVisina(obj.getVisina());
            setBojaOciju(obj.getBojaOciju());
            setBojaKose(obj.getBojaKose());
        }
        return *this;
    }
    // Z3.7 :: dtor
    ~Osoba() {
        delete[] _jmbg; _jmbg = nullptr;
        delete[] _visina; _visina = nullptr;
        delete[] _bojaOciju; _bojaOciju = nullptr;
        delete[] _bojaKose; _bojaKose = nullptr;
    }
};
// Z3.8 :: operator '<<'
ostream& operator <<(ostream& COUT, const Osoba& osoba) {
    COUT << "JMBG: " << osoba.getJmbg() << endl;
    COUT << "Ime i prezime: " << osoba.getIme() << " " << osoba.getPrezime() << endl;
    COUT << "Spol: " << osoba.getSpol() << endl;
    COUT << "Visina: " << osoba.getVisina() << endl;
    COUT << "Boja ociju: " << osoba.getBojaOciju() << endl;
    COUT << "Boja kose: " << osoba.getBojaKose() << endl;
    return COUT;
}
// Z3.9 :: porediti sva obiljezja pomocu getter funkcija
bool operator == (const Osoba& o1, const Osoba& o2) {
    return areEqual(o1.getJmbg(), o2.getJmbg())
        && areEqual(o1.getIme(), o2.getIme())
        && areEqual(o1.getPrezime(), o2.getPrezime())
        && o1.getSpol() == o2.getSpol()
        && o1.getBojaOciju() == o2.getBojaOciju()
        && o1.getBojaKose() == o2.getBojaKose();
}
bool operator != (const Osoba& o1, const Osoba& o2) {
    return !(o1 == o2);
}

class Teniser : public Osoba {
    Vektor<const char*> _osvojeniNaslovi;
    unique_ptr<int> _ranking;
public:
    // Z4.1 :: getteri
    Vektor<const char*> getOsvojeniNaslovi() const { return _osvojeniNaslovi; }
    int getRanking() const { return (_ranking == nullptr) ? 0 : *_ranking; }
    // Z4.2 :: setteri
    void setOsvojeniNaslovi(Vektor<const char*> naslovi) {
        //_osvojeniNaslovi = naslovi;
        for (int i = 0; i < naslovi.getTrenutno(); i++) {
            _osvojeniNaslovi.dodaj(alociraj(naslovi[i]));
        }
    }
    void setRanking(int ranking) {
        if (_ranking == nullptr)
            _ranking = make_unique<int>();
        *_ranking = ranking;
    }
    // Z4.3 :: dflt ctor
    Teniser() {
        setRanking(0);
    }
    // Z4.4 :: user-def ctor
    Teniser(const char* jmbg, const char* ime, const char* prezime, Spol spol, float visina, Boja bojaOciju, Boja bojaKose,
        Vektor<const char*> naslovi, int ranking) 
        : Osoba(jmbg, ime, prezime, spol, visina, bojaOciju, bojaKose)
    {
        setOsvojeniNaslovi(naslovi);
        setRanking(ranking);
    }
    // Z4.3 :: copy ctor
    Teniser(const Teniser& obj) : Osoba(obj) {
        setOsvojeniNaslovi(obj.getOsvojeniNaslovi());
        setRanking(obj.getRanking());
    }
    // Z4.4 :: operator '='
    Teniser& operator = (const Teniser& obj) {
        if (this != &obj) {
            (Osoba&)(*this) = obj;
            setOsvojeniNaslovi(obj.getOsvojeniNaslovi());
            setRanking(obj.getRanking());
        }
        return *this;
    }
    // Z4.5 :: dodavanje naslova
    void dodajNaslov(const char* naslov) {
        if (naslov == nullptr)
            return;
        _osvojeniNaslovi.dodaj(naslov);
    }
    // Z4.6 :: dtor
    ~Teniser() {
        for (int i = 0; i < _osvojeniNaslovi.getTrenutno(); i++) {
            delete[] _osvojeniNaslovi.getElementi()[i];
            _osvojeniNaslovi.getElementi()[i] = nullptr;
        }
    }
};
// Z4.7 :: operator '<<'
ostream& operator <<(ostream& COUT, const Teniser& teniser) {
    COUT << (Osoba&)teniser;
    COUT << "Ranking: " << teniser.getRanking() << endl;
    COUT << "Osvojeni naslovi: " << endl;
    for (int i = 0; i < teniser.getOsvojeniNaslovi().getTrenutno(); i++) {
        COUT << "\t" << teniser.getOsvojeniNaslovi()[i] << endl;
    }
    return COUT; 
}
// Z4.8 :: operator '=='
bool operator == (const Teniser& t1, const Teniser& t2) {
    return (Osoba&)t1 == (Osoba&)t2
        && t1.getOsvojeniNaslovi() == t2.getOsvojeniNaslovi()
        && t1.getRanking() == t2.getRanking();
}
bool operator != (const Teniser& t1, const Teniser& t2) {
    return !(t1 == t2);
}
class Mec {
    Teniser* _igrac1 = nullptr;
    Teniser* _igrac2 = nullptr;
    Vektor<pair<int, int>> _setovi;
public:
    // Z5.1 :: getteri
    Teniser getIgrac1() const { return (_igrac1 == nullptr) ? Teniser() : *_igrac1; }
    Teniser getIgrac2() const { return (_igrac2 == nullptr) ? Teniser() : *_igrac2; }
    pair<int, int>& getSet(int index) const {
        // Implementirati funkciju [baciti izutetak u slucaju nevalidnog indeksa]
        if (index < 0 || index >= _setovi.getTrenutno())
            throw Greska("Index van granica!", __LINE__, __FUNCTION__);
        return _setovi[index];
    }
    Vektor<pair<int, int>> getSetovi() const { return _setovi; }
    // Z5.2 :: setteri
    void setIgrac1(Teniser teniser) {
        if (_igrac1 == nullptr)
            _igrac1 = new Teniser();
        *_igrac1 = teniser;
    }
    void setIgrac2(Teniser teniser) {
        if (_igrac2 == nullptr)
            _igrac2 = new Teniser();
        *_igrac2 = teniser;
    }
    void setSetovi(Vektor<pair<int, int>> setovi) {
        _setovi = setovi;
    }
    // Z5.3 :: dflt ctor
    Mec() {
        setIgrac1(Teniser());
        setIgrac2(Teniser());
    }
    // Z5.4 :: user-def ctor
    Mec(Teniser igrac1, Teniser igrac2) {
        setIgrac1(igrac1);
        setIgrac2(igrac2);
    }
    // Z5.5 :: copy ctor
    Mec(const Mec& obj) {
        setIgrac1(obj.getIgrac1());
        setIgrac2(obj.getIgrac2());
        setSetovi(obj.getSetovi());
    }
    // Z5.6 :: metoda za dodavanje seta
    void dodajSet(int bodovi1, int bodovi2) {
        _setovi.dodaj(make_pair(bodovi1, bodovi2));
    }

    // Z5.7 :: operator '='
    Mec& operator = (const Mec& obj) {
        if (this != &obj) {
            setIgrac1(obj.getIgrac1());
            setIgrac2(obj.getIgrac2());
            setSetovi(obj.getSetovi());
        }
        return *this;
    }
    // Z5.8 :: dtor
    ~Mec() {
        delete _igrac1; _igrac1 = nullptr;
        delete _igrac2; _igrac2 = nullptr;
    }
};
// Z5.9 :: operator '<<'
ostream& operator <<(ostream& COUT, const Mec& teniskiMec) {
    COUT << "----------------------------------------------------\n";
    COUT << "Teniser [1]: " << endl; COUT << teniskiMec.getIgrac1().getIme() << " " << teniskiMec.getIgrac1().getPrezime();
    COUT << "\n----------------------------------------------------\n";
    COUT << "Teniser [2]: " << endl;
    COUT << teniskiMec.getIgrac2().getIme() << " " << teniskiMec.getIgrac2().getPrezime();
    COUT << "\n----------------------------------------------------\n";
    COUT << "Rezultat (po setovima):" << endl;
    for (int i = 0; i < teniskiMec.getSetovi().getTrenutno(); i++)
        COUT << "[" << teniskiMec.getSet(i).first << "-" << teniskiMec.getSet(i).second << "] ";
    COUT << endl;
    return COUT;
}

void zadatak1() {
    //operacije [za mapiranje]
    auto pomnoziSa3 = [](int& broj) {broj *= 3; };
    auto modulirajSa10 = [](int& broj) {broj %= 10; };
    //operacije [za primjenu filtera]
    auto veciOd5 = [](int& broj) {return broj > 5; };
    auto onlyEven = [](int& broj) {return broj % 2 == 0; };
    //operacije [za primjenu reduce]
    auto sumaBrojeva = [](int broj1, int broj2) {return broj1 + broj2; };
    auto vratiVeci = [](int broj1, int broj2) {return max(broj1, broj2); };
    auto vratiManji = [](int broj1, int broj2) {return min(broj1, broj2); };

    Vektor<int> slucajniBrojevi;
    for (int i = 0; i < 30; i++)
        slucajniBrojevi.dodaj(rand() % 40);
    cout << "Svi slucajni brojevi: " << endl;
    ispis(slucajniBrojevi, ", ");
    //Uklanjanje zadnjeg elementa
    cout << endl;
    slucajniBrojevi.removeZadnji();
    cout << "Nakon uklanjanja zadnjeg ... " << endl;
    ispis(slucajniBrojevi, ", ");
    cout << endl;

    //:::::::::::::::::: MAP ::::::::::::::::::
    slucajniBrojevi.map(pomnoziSa3);
    cout << "Nakon mnozenja sa 3 ... " << endl;
    ispis(slucajniBrojevi, ", ");
    cout << endl;
    slucajniBrojevi.map(modulirajSa10);
    cout << "Nakon moduliranja sa 10 ... " << endl;
    ispis(slucajniBrojevi, ", ");
    cout << endl;
    ////:::::::::::::::::: FILTER ::::::::::::::::::
    cout << "Filtriranje [veci od 5] ... " << endl;
    ispis(slucajniBrojevi.filter(veciOd5), ", ");
    cout << endl;
    cout << "Filtriranje [veci od 5 i parni] ... " << endl;
    ispis(slucajniBrojevi.filter(veciOd5).filter(onlyEven), ", ");
    cout << endl;
    //:::::::::::::::::: REDUCE ::::::::::::::::::
    cout << "Filtriranje [veci od 5 i parni] --> Reduce [Suma]" << endl;
    cout << "Suma je: " << slucajniBrojevi.filter(veciOd5).filter(onlyEven).reduce(sumaBrojeva) << endl;
    cout << endl;
    cout << "Filtriranje [veci od 5 i parni] --> Reduce [Max]" << endl;
    cout << "Max element je: " << slucajniBrojevi.filter(veciOd5).filter(onlyEven).reduce(vratiVeci) << endl;
    cout << endl;
    cout << "Filtriranje [veci od 5 i parni] --> Reduce [Min]" << endl;
    cout << "Min element je: " << slucajniBrojevi.filter(veciOd5).filter(onlyEven).reduce(vratiManji) << endl;
    cout << endl;
    //:::::::::::::::::: COPY CTOR | OPERATOR '=' ::::::::::::::::::
    Vektor<int> v1;
    v1.dodaj(42);
    v1.dodaj(24);
    v1.dodaj(33);
    v1.dodaj(11);
    Vektor<int> v2(v1);
    Vektor<int> v3;
    v3 = v1;
    cout << "Ispis vektora 'v1': " << endl;
    ispis(v1, ", ");
    cout << "Ispis kopije vektora 'v1' [copy ctor]: " << endl;
    ispis(v2, ", ");
    cout << "Ispis kopije vektora 'v2' [operator '=']: " << endl;
    ispis(v3, ", ");
    cout << endl;
    try {
        cout << "Pokusavamo pristupiti elementu na indexu 10 u vektoru 'v1'" << endl;
        cout << v1[10];
    }
    catch (const Greska& g) {
        cout << g << endl;
    }
    try {
        cout << "Pokusavamo pristupiti elementu na indexu -1 u vektoru 'v1'" << endl;
        cout << v1[-1];
    }
    catch (const Greska& g) {
        cout << g << endl;
    }
    cout << endl << "Dealokacija..." << endl;
}
void zadatak2() {
    Vektor<const char*> rijeci;
    const char* kolekcijaRijeci[] = { "reverenda","podrugljivo", "trgnuti", "zajapuriti",
        "dozlogrditi", "zamajavati", "upravljati", "doskociti", "kalota" };
    for (size_t i = 0; i < size(kolekcijaRijeci); i++)
        rijeci.dodaj(kolekcijaRijeci[i]);
    ispis(rijeci, ", ");
    cout << endl;
    //:::::::::::::::::: FILTER ::::::::::::::::::
    auto pocinjeSaZ = [](const char* rijec) { return rijec[0] == 'z'; };
    cout << "[Filter] Rijeci koje pocinju sa 'Z': " << endl;
    ispis(rijeci.filter(pocinjeSaZ), ", ");
    cout << endl;
    //:::::::::::::::::: REDUCE ::::::::::::::::::
    auto getDuziTekst = [](const char* str1, const char* str2) { return strlen(str1) >= strlen(str2) ? str1 : str2; };
    cout << "[Reduce] Najduzi tekst: " << endl << rijeci.reduce(getDuziTekst) << endl;
    cout << endl << "Dealokacija..." << endl;
}
void zadatak3() {
    Osoba osoba;
    osoba.setJmbg("1505996161113");
    osoba.setIme("Jane");
    osoba.setPrezime("Doe");
    osoba.setSpol(Spol::Zenski);
    osoba.setVisina(170.0f);
    osoba.setBojaOciju(Boja::Plava);
    osoba.setBojaKose(Boja::Crna);
    cout << osoba << endl;
}
void zadatak4() {
    Vektor<const char*> titule;
    titule.dodaj("Australian Open 2020");
    titule.dodaj("Italian Open 2020");
    titule.dodaj("Cincinnati Masters 2020");
    Teniser djole;
    djole.setJmbg("2205986345113");
    djole.setIme("Novak");
    djole.setPrezime("Djokovic");
    djole.setSpol(Spol::Muski);
    djole.setVisina(1.88f);
    djole.setBojaKose(Boja::Crna);
    djole.setBojaOciju(Boja::Zelena);
    djole.setOsvojeniNaslovi(titule);
    djole.setRanking(11063);
    cout << djole << endl;
    try {
        Teniser t2(djole);
        Teniser t4;
        t4 = djole;
    }
    catch (const Greska& greska) {
        cout << greska << endl;
    }
    cout << endl << "Dealokacija..." << endl;
}

void zadatak5() {
    Teniser federer;
    federer.setJmbg("2205983344414");
    federer.setIme("Roger");
    federer.setPrezime("Federer");
    federer.setSpol(Spol::Muski);
    federer.setVisina(187.0f);
    federer.setBojaOciju(Boja::Plava);
    federer.setBojaKose(Boja::Plava);
    federer.setRanking(8800);
    Teniser nadal;
    nadal.setJmbg("2304984344414");
    nadal.setIme("Rafael");
    nadal.setPrezime("Nadal");
    nadal.setSpol(Spol::Muski);
    nadal.setVisina(1.83f);
    nadal.setBojaKose(Boja::Crna);
    nadal.setBojaOciju(Boja::Crna);
    nadal.setRanking(9500);
    Mec mec;
    mec.setIgrac1(federer);
    mec.setIgrac2(nadal);
    mec.dodajSet(6, 1);
    mec.dodajSet(5, 7);
    mec.dodajSet(6, 4);
    cout << mec;
    try {
        Mec m2(mec);
        Mec m4;
        m4 = mec;
    }
    catch (const Greska& greska) {
        cout << greska << endl;
    }
    cout << endl << "Dealokacija..." << endl;

}
int menu() {
    int nastaviDalje = 1;
    while (nastaviDalje) {
        int izbor = 0;
        do {
            system("cls");
            cout << "::Zadaci::" << endl;
            cout << "(1) Zadatak 1" << endl;
            cout << "(2) Zadatak 2" << endl;
            cout << "(3) Zadatak 3" << endl;
            cout << "(4) Zadatak 4" << endl;
            cout << "(5) Zadatak 5" << endl;
            cout << "Unesite broj za testiranje zadatka: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor <= 0 || izbor > 5);
        switch (izbor) {
        case 1: zadatak1(); cout << "Done." << endl; break;
        case 2: zadatak2(); cout << "Done." << endl; break;
        case 3: zadatak3(); cout << "Done." << endl; break;
        case 4: zadatak4(); cout << "Done." << endl; break;
        case 5: zadatak5(); cout << "Done." << endl; break;
        default:
            break;
        }
        do {
            cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
            cin >> nastaviDalje;
        } while (nastaviDalje != 0 && nastaviDalje != 1);
    }
    return 0;
}

int main() {
    menu();
    return 0;
}
