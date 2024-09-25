#include <iostream>
using namespace std;

const char* separator = "----------------------------------------\n";

//Z0.1
char* alocirajTekst(const char* izvor) {
    if (izvor == nullptr)
        return nullptr;
    char* destinacija = new char[strlen(izvor) + 1];
    strcpy_s(destinacija, strlen(izvor) + 1, izvor);
    return destinacija;
}

class Datum {

    int* _dan = nullptr;
    int* _mjesec = nullptr;
    int* _godina = nullptr;
public:
    // Z1.1 :: getteri
    int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
    int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
    int getGodina() const { return (_godina == nullptr) ? 2023 : *_godina; }

    // Z1.2 :: setteri
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

    // Z1.3 :: dflt. ctor 
    Datum() {
        setDan(1);
        setMjesec(1);
        setGodina(2023);
    }
    // Z1.4 :: user-def. ctor
    Datum(int d, int m, int g) {
        setDan(d);
        setMjesec(m);
        setGodina(g);
    }
    // Z1.5 :: copy ctor
    Datum(const Datum& obj) {
        setDan(obj.getDan());
        setMjesec(obj.getMjesec());
        setGodina(obj.getGodina());
    }

    // Z1.6 :: operator = 
    Datum& operator =(const Datum& obj) {
        if (this != &obj) {
            setDan(obj.getDan());
            setMjesec(obj.getMjesec());
            setGodina(obj.getGodina());
        }
        return *this;
    }
    // Z1.7 :: destruktor
    ~Datum() {
        delete _dan, delete _mjesec, delete _godina;
        _dan = _mjesec = _godina = nullptr;
    }

};

int dateToInt(const Datum& obj) {
    return obj.getGodina() * 365.24 + obj.getMjesec() * 30.41 + obj.getDan();

}

// Z1.8 ::ispisati datum
ostream& operator << (ostream& COUT, const Datum& obj) {
    COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina();
    return COUT;
}
// Z1.9 :: porediti dva datuma po vrijednostima atributa
bool operator == (const Datum& d1, const Datum& d2) {
    return d1.getDan() == d2.getDan() &&
        d1.getMjesec() == d2.getMjesec() &&
        d1.getGodina() == d2.getGodina();
}
bool operator != (const Datum& d1, const Datum& d2) {
    return !(d1 == d2);
}

// Z1.10
bool operator > (const Datum& d1, const Datum& d2) {
    return dateToInt(d1) > dateToInt(d2);
}
bool operator >= (const Datum& d1, const Datum& d2) {
    return d1 > d2 || d1 == d2;
}
bool operator <(const Datum& d1, const Datum& d2) {
    return !(d1 >= d2);
}
bool operator <=(const Datum& d1, const Datum& d2) {
    return !(d1 > d2);
}

// kolekcija elemenata 'Vektor' (tipa T) sa mogucnoscu dinamickog prosirivanja
template<class T>
class Vektor {
    int _trenutno = 0;
    int _maxElemenata;  
    T* _elementi = nullptr;
public:
    // Z2.1 :: getteri
    int getTrenutno() const { return _trenutno; }
    int getMaxElemenata() const { return _maxElemenata; }
    T* getElementi() const { return _elementi; }

    // Z2.2 :: setteri (u ovom slucaju imamo samo jednu setter funkciju)
    void setElementi(int trenutno, int maxElemenata, T* elementi = nullptr) {
        delete[] _elementi;

        _maxElemenata = maxElemenata;
        _elementi = new T[_maxElemenata];

        _trenutno = 0;

        if (elementi != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                add(elementi[i]);
            }
        }
    }
    // Z2.3 :: funkcija za dodavanje elementa tipa 'T'.
    // U slucaju da je brojac dosao do kraja -- uraditi prosirivanje niza za 10 elemenata.
    void add(const T& element) {
        if (_trenutno >= _maxElemenata)
            expandElementi();
        _elementi[_trenutno++] = element;
    }

    // Z2.4 :: funkcija za uklanjanje zadnjeg elementa iz niza
    bool removeZadnji() {
        if (_trenutno <= 0)
            return false;
        _trenutno--;
        return true;
    }

    // Z2.5 :: funkcija za prosirivanje dinamickog niza
    void expandElementi(int uvecanje = 10) {
        _maxElemenata += uvecanje;
        T* temp = new T[_maxElemenata];
        for (int i = 0; i < _trenutno; i++) {
            temp[i] = _elementi[i];
        }
        delete[] _elementi;
        _elementi = temp;
        temp = nullptr;
    }

    // Z2.6 :: dflt ctor
    Vektor(int maxElemenata = 100) {
        setElementi(0, maxElemenata);
    }
    // Z2.6 :: copy ctor :: Kopirati vrijednosti jednog vektora u drugi
    Vektor(const Vektor<T>& obj) {
        setElementi(obj.getTrenutno(), obj.getMaxElemenata(), obj.getElementi());
    }
    // Z2.7 :: operator '='
    Vektor<T>& operator = (const Vektor<T>& obj) {
        if (this != &obj)
            setElementi(obj.getTrenutno(), obj.getMaxElemenata(), obj.getElementi());
        return *this;
    }
    // Z2.8 :: operator '[]' za dohvacanje pojedinacne vrijednosti iz niza
    T& operator [] (int index) const {
        if (index >= 0 && index < _trenutno)
            return _elementi[index];
    }

    // Konkatenacija dva vektora u jedan rezultujući
    Vektor<T> operator+(const Vektor<T>& obj) const {
        Vektor<T> concatVektor(*this);          // kopiranje trenutnog vektora
        for (int i = 0; i < obj.getTrenutno(); i++) {
            concatVektor.add(obj.getElementi()[i]);
        }
        return concatVektor;
    }

    // Brisanje svih elemenata 
    void clear() {
        _trenutno = 0;
    }

    // Z2.11 :: operator '==' za provjeru jednakosti vektora
    bool operator==(const Vektor<T>& obj) const {
        if (_trenutno != obj.getTrenutno())
            return false;
        for (int i = 0; i < _trenutno; i++) {
            if (_elementi[i] != obj.getElementi()[i])
                return false;
        }
        return true;
    }

    // Z2.12 :: operator '!=' za provjeru nejednakosti vektora
    bool operator!=(const Vektor<T>& obj) const {
        return !(*this == obj);
    }
    // Z2.9 :: destruktor
    ~Vektor() {
        delete[] _elementi;
        _elementi = nullptr;
    }

    template <class T>
    friend ostream& operator << (ostream& COUT, const Vektor<T>& obj);
};

// Z2.10 :: ispisuje elemente vektora. Za pristup elementima koristiti preklopljeni operator '[]'
template<class T>
ostream& operator << (ostream& COUT, const Vektor<T>& obj) {
    for (int i = 0; i < obj.getTrenutno(); i++) {
        COUT << obj[i] << endl;
    }
    return COUT;
}


class Model {
    char* _naziv = nullptr;
    char* _karakteristike = nullptr;
    Datum* _datumIzlaska = nullptr;
    char _proizvodjac[50] = "";

public:
    Model() {
        setNaziv("-");
        setKarakteristike("-");
        setDatumIzlaska(Datum());
        setProizvodjac("-");
    }
    Model(const char* naziv, const char* karakteristike, Datum d, const char* proizvodjac) {
        setNaziv(naziv);
        setKarakteristike(karakteristike);
        setDatumIzlaska(d);
        setProizvodjac(proizvodjac);
    }
    Model(const Model& obj) {
        setNaziv(obj.getNaziv());
        setKarakteristike(obj.getKarakteristike());
        setDatumIzlaska(obj.getDatumIzlaska());
        setProizvodjac(obj.getProizvodjac());
    }
    Model& operator=(const Model& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setKarakteristike(obj.getKarakteristike());
            setDatumIzlaska(obj.getDatumIzlaska());
            setProizvodjac(obj.getProizvodjac());
        }
        return *this;
    }
    const char* getKarakteristike() const { return  _karakteristike == nullptr ? "" : _karakteristike; }
    const char* getNaziv() const { return  _naziv == nullptr ? "" : _naziv; }
    const char* getProizvodjac() const { return  _proizvodjac; }
    // Implementirati getter
    Datum getDatumIzlaska() const { return (_datumIzlaska == nullptr) ? Datum() : *_datumIzlaska; }

    void setNaziv(const char* naziv) {
        _naziv = alocirajTekst(naziv);
    }
    void setKarakteristike(const char* karakteristike) {
        _karakteristike = alocirajTekst(karakteristike);
    }
    void setProizvodjac(const char* proizvodjac) {
        strcpy_s(_proizvodjac, strlen(proizvodjac) + 1, proizvodjac);
    }

    void setDatumIzlaska(Datum datum) {
        if (_datumIzlaska == nullptr)
            _datumIzlaska = new Datum;
        *_datumIzlaska = datum;
    }

    // Ispis svih atributa klase model
    friend ostream& operator << (ostream& COUT, const Model& obj) {
        COUT << "\t" << separator;
        COUT << "\t" << "Naziv modela: " << obj.getNaziv() << endl;
        COUT << "\t" << "Karakteristike modela: " << obj.getKarakteristike() << endl;
        COUT << "\t" << "Datum izlaska modela: " << obj.getDatumIzlaska() << endl;
        COUT << "\t" << "Proizvodjac modela: " << obj.getProizvodjac() << endl;
        COUT << "\t" << separator;
        return COUT;
    }
    //Poredi da li dva modela imaju isti naziv
    bool operator == (const Model& obj) {
        return !(strcmp(this->getNaziv(), obj.getNaziv()));
    }

    //Poredi da li dva modela nemaju isti naziv
    bool operator != (const Model& obj) {
        return !(*this == obj);
    }
    ~Model() {
        delete[] _naziv, delete[] _karakteristike;
        _naziv = _karakteristike = nullptr;
        delete _datumIzlaska;
        _datumIzlaska = nullptr;
    }
};


class Telefon {
    char* _naziv = nullptr;
    Datum* _godinaProizvodnje = nullptr;    // pokazivač na jednu instancu tipa datum
    Vektor<Model> _modeli;
public:
    Telefon() {
        setNaziv("-");
        setGodinaProizvodnje(Datum());
        Vektor<Model> temp;                             // saljemo prazan vektor modela
        setModeli(temp);
    }
    Telefon(const char* naziv, Datum d, Vektor<Model> modeli) {
        setNaziv(naziv);
        setGodinaProizvodnje(d);
        setModeli(modeli);
    }
    Telefon(const Telefon& obj) {
        setNaziv(obj.getNaziv());
        setGodinaProizvodnje(obj.getGodinaProizvodnje());
        setModeli(obj.getModeli());
    }
    Telefon& operator= (const Telefon& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setGodinaProizvodnje(obj.getGodinaProizvodnje());
            setModeli(obj.getModeli());
        }
        return *this;
    }
    //Dva telefona su jednaka ako su im jednaki nazivi;
    bool operator == (const Telefon& obj) {
    }
    bool operator != (const Telefon& obj) {
    }
    const char* getNaziv() const { return  _naziv == nullptr ? "" : _naziv; }
    Datum getGodinaProizvodnje() const { return (_godinaProizvodnje == nullptr) ? Datum() : *_godinaProizvodnje; }
    Vektor<Model> getModeli() const { return  _modeli; }

    void setNaziv(const char* naziv) {
        _naziv = alocirajTekst(naziv);
    }

    void setGodinaProizvodnje(Datum datum) {
        if (_godinaProizvodnje == nullptr)
            _godinaProizvodnje = new Datum;
        *_godinaProizvodnje = datum;
    }

    void setModeli(Vektor<Model> modeli) {
        _modeli = modeli;
    }

    // Operator treba da doda model u dinamički niz modela
    void operator+=(Model model) {
        _modeli.add(model);
        // return true;                                    // da je funkcija add bool, vratili bismo taj rezultat
    }

    ~Telefon() {
        delete[] _naziv;
        _naziv = nullptr;
        delete _godinaProizvodnje;
        _godinaProizvodnje = nullptr;
    }
};

// Ispis svih atributa klase Telefon
ostream& operator<<(ostream& COUT, const Telefon& telefon) {
    COUT << separator;
    COUT << "Naziv telefona: " << telefon.getNaziv() << endl;
    COUT << "Godina proizvodnje telefona: " << telefon.getGodinaProizvodnje().getGodina() << endl;
    COUT << "Modeli telefona: " << endl;
    COUT << telefon.getModeli() << endl;
    COUT << separator;
    return COUT;
}

class Trgovina {
    char* _nazivTrgovine = nullptr;
    Vektor<Telefon>* _telefoni = nullptr;

public:
    Trgovina() {
        setNazivTrgovine("-");
        Vektor<Telefon> temp;
        setTelefoni(temp);
    }

    Trgovina(const char* nazivTrgovine, Vektor<Telefon> telefoni) {
        setNazivTrgovine(nazivTrgovine);
        setTelefoni(telefoni);
    }

    Trgovina(const Trgovina& obj) {
        setNazivTrgovine(obj.getNazivTrgovine());
        setTelefoni(obj.getTelefoni());
    }

    Trgovina& operator= (const Trgovina& obj) {
        if (this != &obj) {
            setNazivTrgovine(obj.getNazivTrgovine());
            setTelefoni(obj.getTelefoni());
        }
        return *this;
    }

    const char* getNazivTrgovine() const { return  _nazivTrgovine == nullptr ? "" : _nazivTrgovine; }
    Vektor<Telefon> getTelefoni() const { 
        if (_telefoni == nullptr) {
            Vektor<Telefon> temp;
            return temp;
        }
        return *_telefoni;
    }

    void setNazivTrgovine(const char* naziv) {
        _nazivTrgovine = alocirajTekst(naziv);
    }
    void setTelefoni(Vektor<Telefon> telefoni) {
        if (_telefoni == nullptr)
            _telefoni = new Vektor<Telefon>;
        *_telefoni = telefoni;
    }

    bool dodajTelefon(const Telefon& obj) {
        _telefoni->add(obj);
    }

    ~Trgovina() {
        delete[] _nazivTrgovine;
        _nazivTrgovine = nullptr;
        delete _telefoni;
        _telefoni = nullptr;
    }
};

// Ispis svih atributa klase Trgovina
ostream& operator<<(ostream& COUT, const Trgovina& trgovina) {
    COUT << separator;
    COUT << "Naziv trgovine: " << trgovina.getNazivTrgovine() << endl;
    COUT << "Telefoni: " << endl;
    for (int i = 0; i < trgovina.getTelefoni().getTrenutno(); i++) {
        COUT << trgovina.getTelefoni()[i] << endl;
    }
    COUT << separator;
    return COUT;
}

void zadatak1() {
    Datum aprilFoolsDay;
    Datum laborDay(1, 5, 2023);
    Datum newYearsEve(31, 12, 2023);
    aprilFoolsDay.setDan(1);
    aprilFoolsDay.setMjesec(4);
    aprilFoolsDay.setGodina(2023);

    Datum d1(aprilFoolsDay);
    Datum d2;
    d2 = newYearsEve;
    cout << d1 << endl;
    cout << d2 << endl;
    cout << "Dealokacija..." << endl;
}

void zadatak2() {
    Vektor<int> v1;
    for (int i = 0; i < 30; i++) {
        v1.add(i);
    }
    cout << v1 << endl;
    
    Vektor<int> v2;
    v2.add(15);
    cout << v2 << endl;

    cout << ((v1 == v2) ? "Vektori su isti" : "Vektori su razliciti") << endl;

    Vektor<int> concatVektor = v1 + v2;
    cout << concatVektor << endl;
}

void zadatak3() {
    Model m1;
    cout << m1 << endl;
    Model m2("Samsung Galaxy S9", "Biometrija, heart sensor, face recognition", Datum(5, 5, 2019), "Samsung");
    cout << m2;

    Model m2Copy(m2);
    cout << ((m2 == m2Copy) ? "Modeli se isto zovu" : "Modeli se ne zovu isto") << endl;
}

void zadatak4() {
    Telefon t1;
    cout << t1 << endl;

    Vektor<Model> modeli;
    modeli.add(Model("Naziv m1", "Karakteristike m1", Datum(), "Proizvodjac m1"));
    modeli.add(Model("Naziv m2", "Karakteristike m2", Datum(), "Proizvodjac m2"));
    modeli.add(Model("Naziv m3", "Karakteristike m3", Datum(), "Proizvodjac m3"));
    Telefon t2("Telefon", Datum(5, 5, 2019), modeli);

    cout << t2 << endl;
}

void zadatak5() {
    Trgovina trgovina1;
    cout << trgovina1 << endl;


    Vektor<Model> modeli;
    modeli.add(Model("Naziv m1", "Karakteristike m1", Datum(), "Proizvodjac m1"));
    modeli.add(Model("Naziv m2", "Karakteristike m2", Datum(), "Proizvodjac m2"));
    modeli.add(Model("Naziv m3", "Karakteristike m3", Datum(), "Proizvodjac m3"));
    
    Vektor<Telefon> telefoni;
    telefoni.add(Telefon("Samsung", Datum(), modeli));

    Trgovina trgovina2("Univerzalno Grbavica", telefoni);
    cout << trgovina2 << endl;
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