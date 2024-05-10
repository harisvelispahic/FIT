#include <iostream>
#include <functional>
#include <memory>
using namespace std;

enum Mjesec { Januar = 1, Februar, Mart, April, Maj, Juni, Juli, August, Septembar, Oktobar, Novembar, Decembar };
enum class Spol { Muski = 1, Zenski = 0 };

ostream& operator << (ostream& COUT, const Spol& obj) {
    if (obj == Spol::Muski)
        COUT << "Muski";
    else
        COUT << "Zenski";
    return COUT;
}

// Z0.1 
char* alocirajTekst(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, tekst);
    return temp;
}

class Vrijeme {
    int* _sati = nullptr;
    int* _minute = nullptr;
    int* _sekunde = nullptr;
public:
    // Z1.1 :: getteri
    int getSati() const { return (_sati == nullptr) ? 0 : *_sati; }
    int getMinute() const { return (_minute == nullptr) ? 0 : *_minute; }
    int getSekunde() const { return (_sekunde == nullptr) ? 0 : *_sekunde; }

    // Z1.2 :: setteri
    void setSati(int sati) {
        if (_sati == nullptr)
            _sati = new int;
        *_sati = sati;
    }
    void setMinute(int minute) {
        if (_minute == nullptr)
            _minute = new int;
        *_minute = minute;
    }
    void setSekunde(int sekunde) {
        if (_sekunde == nullptr)
            _sekunde = new int;
        *_sekunde = sekunde;
    }

    // Z1.3 :: dflt ctor
    Vrijeme(int sati = 0, int minute = 0, int sekunde = 0) {
        setSati(sati);
        setMinute(minute);
        setSekunde(sekunde);
    }
    // Z1.4 :: copy ctor
    Vrijeme(const Vrijeme& obj) {
        setSati(obj.getSati());
        setMinute(obj.getMinute());
        setSekunde(obj.getSekunde());
    }

    // Z1.6 :: operator '='
    Vrijeme& operator =(const Vrijeme& obj) {
        if (this != &obj) {
            setSati(obj.getSati());
            setMinute(obj.getMinute());
            setSekunde(obj.getSekunde());
        }
        return *this;
    }

    // Z1.7 :: metoda za provjeru validnosti vrijednosti vremena
    bool isValid() {
        return getSati() >= 0 && getSati() <= 23 && getMinute() >= 0 && getMinute() <= 59 && getSekunde() >= 0 && getSekunde() <= 59;
    }

    // Z1.8 :: metoda za generisanje slucajnog vremena
    static Vrijeme getRandomVrijeme() {
        int sati = rand() % 24;
        int minute = rand() % 60;
        int sekunde = rand() % 60;
        return Vrijeme(sati, minute, sekunde);
    }
    // Z1.9 :: dtor
    ~Vrijeme() {
        delete _sati;
        delete _minute;
        delete _sekunde;
        _sati = _minute = _sekunde = nullptr;
    }


    int toInt() const {
        return getSati() * 3600 + getMinute() * 60 + getSekunde();
    }
};

// Z1.10 :: operator '<<'
ostream& operator << (ostream& COUT, const Vrijeme& obj) {
    if (obj.getSati() < 10)
        COUT << "0";
    COUT << obj.getSati() << ":";

    if (obj.getMinute() < 10)
        COUT << "0";
    COUT << obj.getMinute() << ":";

    if (obj.getSekunde() < 10)
        COUT << "0";
    COUT << obj.getSekunde();
    return COUT;
}
// Z1.11 :: logicki operatori
bool operator == (const Vrijeme& v1, const Vrijeme& v2) {
    return v1.toInt() == v2.toInt();
}
bool operator != (const Vrijeme& v1, const Vrijeme& v2) {
    return !(v1 == v2);
}
bool operator > (const Vrijeme& v1, const Vrijeme& v2) {
    return v1.toInt() > v2.toInt();
}
bool operator >= (const Vrijeme& v1, const Vrijeme& v2) {
    return (v1 > v2) || (v1 == v2);
}
bool operator < (const Vrijeme& v1, const Vrijeme& v2) {
    return !(v1 >= v2);
}
bool operator <= (const Vrijeme& v1, const Vrijeme& v2) {
    return !(v1 > v2);
}

// unique_ptr:
// 1. oni su automatski anulirani
// 2. sami rade dealokaciju
// 3. unikatni su kao sto samo ime kaze, tj. 2 unique_ptr ne mogu imati istu memorijsku adresu

// metoda reset() koja alocira/dealocira
// prebacivanje jednog unique_ptr u drugi unique_ptr moze se uraditi pomocu move semantike
// Na primjer:

/*
unique_ptr<int> p;
p = make_unique<int>(4501);

unique_ptr<int> q;
q = move(p);

cout << q << endl;
cout << *q << endl;
*/

// prvi se anulirao, a drugi je primio njegovu adresu, tj. "samo preko mene mrtvog"


//cout << q << endl;            // isto
//cout << q.get() << endl;      // kao ovo
//cout << *q << endl;

//int* p = q.release();         //q.release() ispušta adresu pokazivaca, anulira ga, i predaje vraca adresu koja moze biti ovako npr predana pokazivacu p, slicno kao move() sematnika


// ali na primjer int * a = q.get();    - svojstvo je prekrseno, medjutim unique_ptr osigurava da vise unique_ptr-a ne mogu pokazivati na istu adresu, ali ne i vise raw pointera.

// swap() - metoda mijenja adresu dva pokazivaca, swappuje ih



// klasa 'DatumVrijeme' javno naslijedjuje klasu 'Vrijeme'
class DatumVrijeme : public Vrijeme {
    unique_ptr<int> _dan = nullptr;
    unique_ptr<int> _mjesec = nullptr;
    unique_ptr<int> _godina = nullptr;
public:
    // Z2.1 :: getteri
    int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
    int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
    int getGodina() const { return (_godina == nullptr) ? 2023 : *_godina; }

    // Z2.2 :: setteri 
    void setDan(int dan) {
        if (_dan == nullptr)
            _dan = make_unique<int>();
        *_dan = dan;
    }
    void setMjesec(int mjesec) {
        if (_mjesec == nullptr)
            _mjesec = make_unique<int>();
        *_mjesec = mjesec;
    }
    void setGodina(int godina) {
        if (_godina == nullptr)
            _godina = make_unique<int>();
        *_godina = godina;
    }
    // Z2.3 :: dflt ctor
    DatumVrijeme() : Vrijeme() {                  // u predprocesorskom vremenu invociramo konstruktore, konstante itd, medjutim konstruktor bazne klase MORA BITI KAKO TREBA NASLIJEDJEN, odnosno mora biti nasljedjivanje public ili protected
        
        setDan(1);
        setMjesec(1);
        setGodina(2023);

        /*setSati(0);
        setMinute(0);
        setSekunde(0);*/
    }
    // Z2.4 :: user-def ctor
    DatumVrijeme(int dan, int mjesec, int godina, int sati, int minute, int sekunde) : Vrijeme(sati,minute,sekunde) {
        // ne nasljedjuje direktno atribute, sat, min, sek, nego njihove gettere koje konstruktorom koristi kako bi incijalizarila njih same
        setDan(dan);
        setMjesec(mjesec);
        setGodina(godina);

        /*setSati(sati);
        setMinute(minute);
        setSekunde(sekunde);*/
    }
    // Z2.5 :: copy ctor
    DatumVrijeme(const DatumVrijeme& obj) : Vrijeme(obj) {
        // ne mozemo napraviti objekat izvedene klase na osnovu objekta bazne klase, medjutim mozemo napraviti objekat bazne klase na osnovu objekta izvedene klase, pa ce ovaj pristup u zaglavlju raditi, jer se dio obj "otkida" i daje konstruktoru za vrijeme, sto ce on iskoristiti za inicijalizaciju
        setDan(obj.getDan());
        setMjesec(obj.getMjesec());
        setGodina(obj.getGodina());

        /*setSati(obj.getSati());
        setMinute(obj.getMinute());
        setSekunde(obj.getSekunde());*/
    }
    // Z2.6 :: operator '='
    DatumVrijeme& operator =(const DatumVrijeme& obj) {
        if (this != &obj) {
            
            // 1. nacin
            // (Vrijeme&)(*this) = obj;    
            
            // 2. nacin
            Vrijeme::operator=(obj);

            setDan(obj.getDan());
            setMjesec(obj.getMjesec());
            setGodina(obj.getGodina());

            /*setSati(obj.getSati());
            setMinute(obj.getMinute());
            setSekunde(obj.getSekunde());*/
        }
        return *this;
    }
    // Z2.7 :: funkcija za provjeru validnosti objekta DatumVrijeme

    static bool isLeapYear(int godina) {
        return godina % 400 == 0 || (godina % 4 == 0 && godina % 100 != 0);
    }

    static int brojDanaUMjesecu(int mjesec, int godina) {
        switch (mjesec)
        {
        case Januar: case Mart: case Maj: case Juli: case August: case Oktobar: case Decembar:
            return 31;
        case April: case Juni: case Septembar: case Novembar:
            return 30;
        case Februar:
            if (isLeapYear(godina))
                return 29;
            else
                return 28;
        default:
            return 0;
        }
    }

    bool isValid() {
        if (!Vrijeme::isValid() || getDan() < 1 || getDan() > brojDanaUMjesecu(getMjesec(), getGodina()) || getMjesec() < Januar || getMjesec() > Decembar || getGodina() < 0)
            return false;               // rijesen problem vise funkcija sa istim imenom, koristenjem scope operatora

#pragma region LambdaFunkcijaZaPrijestupnuGodinu
        // koristicemo lambda expression za leap year
        function<bool(int)> isLeap = [](int godina) { return godina % 400 == 0 || (godina % 4 == 0 && godina % 100 != 0); };
        // "brutalni overkill"
        // pametnije napraviti kao globalnu varijablu
        
        isLeap(getGodina());
        // i sad ovo mozemo dalje raditi, da provjerimo za sve mjesece koliko dana imaju, medjutim to je implementirano sa:
        // getDan() > brojDanaUMjesecu(getMjesec()
#pragma endregion
    }
    // Z2.8 Obratiti paznju na validnost novokreiranog objekta (DatumVrijeme) sa slucajnim vrijednostima
    static DatumVrijeme getRandomDatumVrijeme() {
        int godina = rand() % 20 + 2004;
        int mjesec = rand() % 12 + 1;
        int dan = rand() % DatumVrijeme::brojDanaUMjesecu(mjesec, godina) + 1;

        Vrijeme temp = Vrijeme::getRandomVrijeme();
        int sati = temp.getSati();
        int minute = temp.getMinute();
        int sekunde = temp.getSekunde();

        return DatumVrijeme(dan, mjesec, godina, sati, minute, sekunde);
    }

    int toInt() const {
        return getDan() + getMjesec() * 30.41 + getGodina() * 365.24;
    }

    // Z2.9 :: dtor
    ~DatumVrijeme() {
        // radimo sa unique_ptr, pa ce se oni sami dealocirati, ali ako bas hocemo rucno, mada ne moramo, radimo ovako:
        _dan.reset();
        _mjesec.reset();
        _godina.reset();
    }
};

#pragma region staticCtor
// statikci konstruktori, staticki operatori, nece biti na ispitu, ali zanimljivo
#pragma endregion

// Z2.10 :: operator '<<' :: ispisati podatke o datumu i vremenu
ostream& operator << (ostream& COUT, const DatumVrijeme& obj) {
    COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina() << "\n";
    COUT << (Vrijeme&)obj;          // uzima "Vrijeme" dio od obj, i to po referenci, da bi se izbjeglo kopiranje
    return COUT;
}
// Z2.11 :: operator '==' :: uporediti datume i vremena
bool operator == (const DatumVrijeme& d1, const DatumVrijeme& d2) {
    return d1.Vrijeme::toInt() == d2.Vrijeme::toInt() && d1.DatumVrijeme::toInt() == d2.DatumVrijeme::toInt();
}
bool operator !=(const DatumVrijeme& d1, const DatumVrijeme& d2) {
    return !(d1 == d2);
}
// Z2.12 :: operatori '>', '>=', '<', '<='
bool operator >(const DatumVrijeme& d1, const DatumVrijeme& d2) {
    if (d1.DatumVrijeme::toInt() > d2.DatumVrijeme::toInt())
        return true;
    else if (d1.DatumVrijeme::toInt() == d2.DatumVrijeme::toInt()) {
        return d1.Vrijeme::toInt() > d2.Vrijeme::toInt();
    }
    return false;
}
bool operator >= (const DatumVrijeme& d1, const DatumVrijeme& d2) {
    return (d1 > d2) || (d1 == d2);
}
bool operator < (const DatumVrijeme& d1, const DatumVrijeme& d2) {
    return !(d1 >= d2);
}
bool operator <= (const DatumVrijeme& d1, const DatumVrijeme& d2) {
    return !(d1 > d2);
}

template<class T, int max> //max oznacava velicinu niza
class Array {
    int _trenutno = 0; // trenutno elemenata 
    T* _elementi[max] = { nullptr }; // staticki niz pokazivaca
public:
    // Z3.1 :: getteri
    int getTrenutno() const { return _trenutno; }
    T** getElementi() const { return (T**)_elementi; }

    // Z3.2 :: setteri (u ovom slucaju samo jedna setter funkcija)
    void setElementi(int trenutno = 0, T** elementi = nullptr) {
        for (int i = 0; i < _trenutno; i++) {
            delete _elementi[i];
            _elementi[i] = nullptr;
        }

        if (elementi != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                add(*elementi[i]);
            }
        }
    }
    // Z3.3 :: funkcija za  dodavanje elementa
    // ukoliko je brojac dosao do kraja niza, onemoguciti dodavanje
    bool add(const T& element) {
        if (_trenutno >= max)
            return false;
        _elementi[_trenutno++] = new T(element);
        return true;
    }

    // Z3.4 :: funkcija za uklanjanje zadnjeg dodanog elementa [ne zaboravite dealokaciju]
    bool removeZadnji() {
        if (_trenutno < 0)
            return false;
        delete _elementi[--_trenutno];
        _elementi[_trenutno] = nullptr;
        return true;
    }
    // Z3.5 :: dflt ctor
    Array() {
        setElementi();
    }
    // Z3.6 :: copy ctor
    Array(const Array<T, max>& obj) {
        setElementi(obj.getTrenutno(), obj.getElementi());
    }
    // Z3.7 :: operator '='
    Array<T, max>& operator = (const Array<T, max>& obj) {
        if (this != &obj)
            setElementi(obj.getTrenutno(), obj.getElementi());
        return *this;
    }
    // Z3.8 :: operator '[]'
    T& operator [] (int index) const {
        if (index >= 0 && index < getTrenutno())
            return *_elementi[index];
    }

    // Z3.9 :: metoda 'insertAt'.
    // sprijeciti umetanje ukoliko je brojac dosao do kraja
    // index ne smije biti izvan dozvoljenog opsega vrijednosti
    bool insertAt(int index, T element) {
        if (_trenutno >= max || index < 0 || index >= max)
            return false;
        if (_trenutno == 0)
            add(element);

        _elementi[_trenutno] = new T;   // potrebno je prosiriti ovaj niz prije nego sto pokusamo pristupiti lokaciji na _trenutno jer ta memorija nije incijalizirana
        for (int i = _trenutno; i > index; i--) {
            *(_elementi[i]) = *(_elementi[i - 1]);
        }

        _elementi[index] = new T(element);
        _trenutno++;
    }

    // Z3.10 :: metoda 'removeAt'.
    // sprijeciti uklanjanje ukoliko je brojac jednak 0
    // index ne smije biti izvan dozvoljenog opsega vrijednosti
    bool removeAt(int index) {
        if (_trenutno == 0 || index < 0 || index >= max)
            return false;
        for (int i = index; i < _trenutno - 1; i++) {
            *(_elementi[i]) = *(_elementi[i + 1]);
        }
        _trenutno--;
    }

    // Z3.11 :: destruktor
    ~Array() {
        for (int i = 0; i < _trenutno; i++) {
            delete _elementi[i];
            _elementi[i] = nullptr;
        }
    }
};
// Z3.12 :: operator '<<' za genericku klasu 'Array<T>'
template<class T, int max>
ostream& operator << (ostream& COUT, const Array<T, max>& obj) {
    if (obj.getTrenutno() == 0)
        return COUT;

    for (int i = 0; i < obj.getTrenutno() - 1; i++) {
        COUT << obj[i] << ", ";
    }
    COUT << obj[obj.getTrenutno() - 1];
    return COUT;
}
// Z3.13
template<class T, int max>
void ispis(const Array<T, max>& obj, const char* delimiter = " ") {
    for (int i = 0; i < obj.getTrenutno() - 1; i++) {
        cout << obj[i] << delimiter;
    }
    cout << obj[obj.getTrenutno() - 1];
}
// Z3.14
template<class T, int max>
bool operator == (const Array<T, max>& arr1, const Array<T, max>& arr2) {
    if (arr1.getTrenutno() != arr2.getTrenutno())
        return false;
    for (int i = 0; i < arr1.getTrenutno(); i++) {
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}
template<class T, int max>
bool operator != (const Array<T, max>& arr1, const Array<T, max>& arr2) {
    return !(arr1 == arr2);
}
// Z4.0 :: Funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char[]> alocirajUnique(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    unique_ptr<char[]> temp = make_unique<char[]>(size);
    strcpy_s(temp.get(), size, tekst);
    return temp;
}

class Osoba {
    unique_ptr<char[]> _ime = nullptr;
    unique_ptr<char[]> _prezime = nullptr;
    unique_ptr<DatumVrijeme> _datumRodjenja = nullptr;
    Spol _spol;
public:
    // Z4.1 :: getteri [za preuzimanje vrijednosti pametnog pokazivaca koristiti funkciju 'get']
    const char* getIme() const { return (_ime.get() == nullptr) ? "" : _ime.get(); }
    const char* getPrezime() const { return (_prezime.get() == nullptr) ? "" : _prezime.get(); }
    DatumVrijeme getDatumRodjenja() const { return (_datumRodjenja == nullptr) ? DatumVrijeme() : *_datumRodjenja; }
    Spol getSpol() const { return _spol; }

    // Z4.2 :: setteri
    void setIme(const char* ime) {
        _ime = alocirajUnique(ime);
    }
    void setPrezime(const char* prezime) {
        _prezime = alocirajUnique(prezime);
    }
    void setDatumRodjenja(DatumVrijeme datumRodjenja) {
        if (_datumRodjenja == nullptr)
            _datumRodjenja = make_unique<DatumVrijeme>();
        *_datumRodjenja = datumRodjenja;
    }
    void setSpol(Spol spol) {
        _spol = spol;
    }

    // Z4.2 :: dflt ctor / user-defined ctor
    Osoba(const char* ime = "Jane", const char* prezime = "Doe",
        DatumVrijeme datumRodjenja = DatumVrijeme(), Spol spol = Spol::Zenski) {
        setIme(ime);
        setPrezime(prezime);
        setDatumRodjenja(datumRodjenja);
        setSpol(spol);
    }
    // Z4.3 :: copy ctor
    Osoba(const Osoba& obj) {
        setIme(obj.getIme());
        setPrezime(obj.getPrezime());
        setDatumRodjenja(obj.getDatumRodjenja());
        setSpol(obj.getSpol());
    }
    // Z4.4 :: operator '='
    Osoba& operator = (const Osoba& obj) {
        if (this != &obj) {
            setIme(obj.getIme());
            setPrezime(obj.getPrezime());
            setDatumRodjenja(obj.getDatumRodjenja());
            setSpol(obj.getSpol());
        }
        return *this;
    }
    // Z4.5 :: dtor
    ~Osoba() {
    }
};
// Z4.6 :: operator '<<'
ostream& operator << (ostream& COUT, const Osoba& osoba) {
    COUT << "Ime i prezime: " << osoba.getIme() << " " << osoba.getPrezime() << endl;
    COUT << "Datum rodjenja: " << osoba.getDatumRodjenja() << endl;
    COUT << "Spol: " << osoba.getSpol() << endl;
    return COUT;
}

// Z4.7 :: operator '==' -- poredjenje
bool operator == (const Osoba& o1, const Osoba& o2) {
    return strcmp(o1.getIme(), o2.getIme()) == 0 &&
        strcmp(o1.getPrezime(), o2.getPrezime()) == 0 &&
        o1.getDatumRodjenja() == o2.getDatumRodjenja() &&
        o1.getSpol() == o2.getSpol();
}
bool operator != (const Osoba& o1, const Osoba& o2) {
    return !(o1 == o2);
}

class Pjevac : public Osoba {
    // _ime, _prezime, _datumRodjenja, _spol
    const char* _zanr = nullptr;
    Array<const char*, 10> _instrumenti; // niz tekstova
    unique_ptr<char[]> _aktivan; // pokazivac na niz karaktera Npr. "1978 - present"
public:
    // Z5.1 :: getteri
    const char* getZanr() const { return (_zanr == nullptr) ? "" : _zanr; }
    Array<const char*, 10> getInstrumenti() const { return _instrumenti; }
    const char* getAktivan()const { return (_aktivan.get() == nullptr) ? "" : _aktivan.get(); }

    // 5.2 :: setteri
    void setZanr(const char* zanr) {
        delete[] _zanr;
        _zanr = alocirajTekst(zanr);
    }
    void setInstrumenti(Array<const char*, 10> instrumenti) {
        _instrumenti = instrumenti;
    }
    void setAktivan(const char* aktivan) {
        _aktivan = alocirajUnique(aktivan);
    }
    // Z5.3 :: dflt ctor
    Pjevac() {
        setIme("---");
        setPrezime("---");
        setDatumRodjenja(DatumVrijeme());
        setSpol(Spol::Zenski);

        setZanr("---");
        setInstrumenti(Array<const char*, 10>());
        setAktivan("---");
    }
    // Z5.4 :: user-defined ctor
    Pjevac(const char* ime, const char* prezime, DatumVrijeme dv, Spol sp, const char* zanr, const char* aktivan)
    {
        setIme(ime);
        setPrezime(prezime);
        setDatumRodjenja(dv);
        setSpol(sp);

        setZanr(zanr);
        setInstrumenti(Array<const char*, 10>());
        setAktivan(aktivan);
    }
    // Z5.5 :: copy ctor
    Pjevac(const Pjevac& obj) {
        setIme(obj.getIme());
        setPrezime(obj.getPrezime());
        setDatumRodjenja(obj.getDatumRodjenja());
        setSpol(obj.getSpol());

        setZanr(obj.getZanr());
        setInstrumenti(obj.getInstrumenti());
        setAktivan(obj.getAktivan());
    }
    // Z5.6 :: operator '='
    Pjevac& operator = (const Pjevac& obj) {
        if (this != &obj) {
            setIme(obj.getIme());
            setPrezime(obj.getPrezime());
            setDatumRodjenja(obj.getDatumRodjenja());
            setSpol(obj.getSpol());

            setZanr(obj.getZanr());
            setInstrumenti(obj.getInstrumenti());
            setAktivan(obj.getAktivan());
        }
        return *this;
    }
    // Z5.7 :: metoda za dodavanje instrumenta (niz karaktera) u Array
    bool dodajInstrument(const char* instrument) {
        return _instrumenti.add(instrument);
    }
    // Z5.8 :: dtor
    ~Pjevac() {
        delete[] _zanr;
        _zanr = nullptr;
    }
};
// Z5.9 :: operator '<<' za ispis podataka o pjevacu
ostream& operator << (ostream& COUT, const Pjevac& pjevac) {
    COUT << "Ime i prezime: " << pjevac.getIme() << " " << pjevac.getPrezime() << endl;
    COUT << "Datum rodjenja: " << pjevac.getDatumRodjenja() << endl;
    COUT << "Spol: " << pjevac.getSpol() << endl;
    COUT << "Zanr: " << pjevac.getZanr() << endl;
    COUT << "Instrumenti: " << pjevac.getInstrumenti() << endl;                 // puca
    COUT << "Aktivan: " << pjevac.getAktivan() << endl;;
    return COUT;
}
// Z5.10 :: operator '==' za poredjenje objekata tipa 'Pjevac' po svim vrijednostima
bool operator == (const Pjevac& p1, const Pjevac& p2) {
    return strcmp(p1.getIme(), p2.getIme()) == 0 &&
        strcmp(p1.getPrezime(), p2.getPrezime()) == 0 &&
        p1.getSpol() == p2.getSpol() &&
        strcmp(p1.getZanr(), p2.getZanr()) == 0 &&
        p1.getInstrumenti() == p2.getInstrumenti() &&
        strcmp(p1.getAktivan(), p2.getAktivan()) == 0;
}
bool operator != (const Pjevac& p1, const Pjevac& p2) {
    return !(p1 == p2);
}

class Pjesma {
    const char* _naziv = nullptr;
    char* _tekst = nullptr;
    pair<int, int> _trajanje; // <minute, sekunde> [Po defaultu postaviti na <0,0>]
    unique_ptr<char[]> _tekstopisac; // pokazivac na niz karaktera
    int _trenutnoZanrova = 0;
    char* _zanrovi[5] = { nullptr };
public:
    // Z6.1 :: getteri
    const char* getNaziv() const { return (_naziv == nullptr) ? "" : _naziv; }
    const char* getTekst() const { return (_tekst == nullptr) ? "" : _tekst; }
    pair<int, int> getTrajanje()const { return _trajanje; }
    const char* getTekstopisac()const { return (_tekstopisac.get() == nullptr) ? "" : _tekstopisac.get(); }
    int getTrenutno()const { return _trenutnoZanrova; }
    char** getZanrovi() const { return (char**)_zanrovi; }
    const char* getZanr(int index) const {
        if (index >= 0 && index < size(_zanrovi))
            return _zanrovi[index];
        return nullptr;
    }

    // Z6.2 :: setteri
    void setNaziv(const char* naziv) {
        delete[] _naziv;
        _naziv = alocirajTekst(naziv);
    }
    void setTekst(const char* tekst) {
        delete[] _tekst;
        _tekst = alocirajTekst(tekst);
    }
    void setTrajanje(pair<int, int> trajanje) {
        _trajanje = trajanje;
    }
    void setTekstopisac(const char* tekstopisac) {
        _tekstopisac = alocirajUnique(tekstopisac);
    }
    void setZanrovi(int trenutno = 0, char** zanrovi = nullptr) {
        for (int i = 0; i < _trenutnoZanrova; i++) {
            delete[] _zanrovi[i];
            _zanrovi[i] = nullptr;
        }

        if (zanrovi != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodajZanr(zanrovi[i]);
            }
        }

    }
    // Z6.3 :: metoda za dodavanje novog zanra u niz '_zanrovi'
    bool dodajZanr(const char* zanr) {
        if (_trenutnoZanrova < 0 || _trenutnoZanrova >= size(_zanrovi))
            return false;
        _zanrovi[_trenutnoZanrova++] = alocirajTekst(zanr);
        return true;
    }

    // Z6.4 :: dflt ctor [postaviti '_trajanje' na vrijednosti <0,0>]
    Pjesma() {
        setNaziv("---");
        setTekst("---");
        setTrajanje(make_pair(0, 0));
        setTekstopisac("---");
        setZanrovi();
    }
    // Z6.5 :: user-defined ctor
    Pjesma(const char* naziv, const char* tekst, pair<int, int> trajanje, const char* tekstopisac) {
        setNaziv(naziv);
        setTekst(tekst);
        setTrajanje(trajanje);
        setTekstopisac(tekstopisac);
        setZanrovi();
    }
    // Z6.6 :: copy ctor
    Pjesma(const Pjesma& obj) {
        setNaziv(obj.getNaziv());
        setTekst(obj.getTekst());
        setTrajanje(obj.getTrajanje());
        setTekstopisac(obj.getTekstopisac());
        setZanrovi(obj.getTrenutno(), obj.getZanrovi());
    }
    // Z6.7 :: operator '='
    Pjesma& operator = (const Pjesma& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setTekst(obj.getTekst());
            setTrajanje(obj.getTrajanje());
            setTekstopisac(obj.getTekstopisac());
            setZanrovi(obj.getTrenutno(), obj.getZanrovi());
        }
        return *this;
    }
    // Z6.8 :: dtor
    ~Pjesma() {
        delete[] _naziv;
        delete[] _tekst;
        _naziv = _tekst = nullptr;

        for (int i = 0; i < _trenutnoZanrova; i++) {
            delete[] _zanrovi[i];
            _zanrovi[i] = nullptr;
        }
    }
};
// Z6.9 :: operator '<<' za ispid podataka o objektu tipa 'Pjesma'
ostream& operator << (ostream& COUT, const Pjesma& obj) {
    COUT << "Naziv pjesme: " << obj.getNaziv() << endl;
    COUT << "Tekst pjesme: " << obj.getTekst() << endl;
    COUT << "Trajanje pjesme: " << obj.getTrajanje().first << "min " << obj.getTrajanje().second << "sec" << endl;
    COUT << "Tekstopisac pjesme: " << obj.getTekstopisac() << endl;
    COUT << "Zanrovi: ";
    for (int i = 0; i < obj.getTrenutno() - 1; i++) {
        COUT << obj.getZanrovi()[i] << ", ";
    }
    COUT << obj.getZanrovi()[obj.getTrenutno() - 1] << endl;
    return COUT;
}
// Z6.10 :: operator '==' za poredjenje objekata tipa 'Pjesma' po svim vrijednostima
bool operator == (const Pjesma& p1, const Pjesma& p2) {
    if (strcmp(p1.getNaziv(), p2.getNaziv()) != 0 ||
        strcmp(p1.getTekst(), p2.getTekst()) != 0 ||
        strcmp(p1.getTekstopisac(), p2.getTekstopisac()) != 0 ||
        p1.getTrajanje().first != p2.getTrajanje().first || p1.getTrajanje().second != p2.getTrajanje().second ||
        p1.getTrenutno() != p2.getTrenutno())
        return false;
    for (int i = 0; i < p1.getTrenutno(); i++) {
        if (strcmp(p1.getZanrovi()[i], p2.getZanrovi()[i]) != 0)
            return false;
    }
    return true;
}
bool operator != (const Pjesma& p1, const Pjesma& p2) {
    return !(p1 == p2);
}

class Album {
    char* _naziv = nullptr;
    Pjevac* _pjevac = nullptr;
    Array<Pjesma, 100> _pjesme;
    Array<const char*, 10> _izdavackeKuce;
public:
    // Z7.1 :: getteri
    const char* getNaziv() const { return (_naziv == nullptr) ? "" : _naziv; }
    Pjevac getPjevac()const { return (_pjevac == nullptr) ? Pjevac() : *_pjevac; }
    Array<Pjesma, 100> getPjesme() const { return _pjesme; }
    Array<const char*, 10> getIzdavackeKuce() const { return _izdavackeKuce; }

    // Z7.2 :: setteri
    void setNaziv(const char* naziv) {
        _naziv = alocirajTekst(naziv);
    }
    void setPjevac(Pjevac pjevac) {
        if (_pjevac == nullptr)
            _pjevac = new Pjevac;
        *_pjevac = pjevac;
    }
    void setPjesme(Array<Pjesma, 100> pjesme) {
        _pjesme = pjesme;
    }
    void setIzdavackeKuce(Array<const char*, 10> izdavackeKuce) {
        _izdavackeKuce = izdavackeKuce;
    }

    // Z7.3 :: dflt ctor
    Album() {
        setNaziv("---");
        setPjevac(Pjevac());
        setPjesme(Array<Pjesma, 100>());
        setIzdavackeKuce(Array<const char*, 10>());
    }
    // Z7.4 :: user-defined ctor
    Album(const char* naziv, Pjevac pjevac) {
        setNaziv(naziv);
        setPjevac(pjevac);
        setPjesme(Array<Pjesma, 100>());
        setIzdavackeKuce(Array<const char*, 10>());
    }
    // Z7.5 :: copy ctor
    Album(const Album& obj) {
        setNaziv(obj.getNaziv());
        setPjevac(obj.getPjevac());
        setPjesme(obj.getPjesme());
        setIzdavackeKuce(obj.getIzdavackeKuce());
    }
    // Z7.6 :: operator '='
    Album& operator =(const Album& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setPjevac(obj.getPjevac());
            setPjesme(obj.getPjesme());
            setIzdavackeKuce(obj.getIzdavackeKuce());
        }
        return *this;
    }
    // Z7.7 :: operator '+=' za dodavanje pjesme u niz
    bool operator+= (Pjesma novaPjesma) {
        return _pjesme.add(novaPjesma);
    }
    // Z7.8 :: operator '+=' za dodavanje izdavackeKuce u niz
    bool operator+= (const char* izdavackaKuca) {
        return _izdavackeKuce.add(izdavackaKuca);
    }
    // Z7.9 :: dtor
    ~Album() {
        delete[] _naziv;
        _naziv = nullptr;
        delete _pjevac;
        _pjevac = nullptr;
    }
};
// Z7.10 :: operator '<<' za ispis podataka o albumu
ostream& operator <<(ostream& COUT, const Album& obj) {
    COUT << "Naziv albuma: " << obj.getNaziv() << endl;
    COUT << "Pjevac: ";
    COUT << obj.getPjevac() << endl;
    COUT << "Pjesme: " << obj.getPjesme() << endl;
    COUT << "Izdavacke kuce: " << obj.getIzdavackeKuce() << endl;
    return COUT;
}
// Z7.11 :: operator '==' za poredjenje objekata tipa 'Album'
bool operator == (const Album& a1, const Album& a2) {
    if (strcmp(a1.getNaziv(), a2.getNaziv()) != 0 ||
        a1.getPjevac() != a2.getPjevac() ||
        a1.getPjesme().getTrenutno() != a2.getPjesme().getTrenutno() ||
        a1.getIzdavackeKuce().getTrenutno() != a2.getIzdavackeKuce().getTrenutno())
        return false;
    for (int i = 0; i < a1.getPjesme().getTrenutno(); i++) {
        if (a1.getPjesme().getElementi()[i] != a2.getPjesme().getElementi()[i])
            return false;
    }
    for (int i = 0; i < a1.getIzdavackeKuce().getTrenutno(); i++) {
        if (a1.getIzdavackeKuce().getElementi()[i] != a2.getIzdavackeKuce().getElementi()[i])
            return false;
    }
    return true;
}
bool operator !=(const Album& a1, const Album& a2) {
    return !(a1 == a2);
}
void zadatak1() {
    cout << "Generisanje slucajnog vremena: " << endl;
    Vrijeme vrijeme = Vrijeme::getRandomVrijeme();
    cout << vrijeme << endl;
    cout << "User-def ctor: " << endl;
    Vrijeme vrijeme2(vrijeme.getSati(), vrijeme.getMinute(), vrijeme.getSekunde());
    cout << vrijeme2 << endl;
    cout << "Copy ctor: " << endl;
    Vrijeme vrijeme3(vrijeme);
    cout << vrijeme3 << endl;
    cout << "Operator '=': " << endl;
    Vrijeme vrijeme4;
    vrijeme4 = vrijeme;
    cout << vrijeme4 << endl;

    cout << "Testiranje validnosti..." << endl;
    Vrijeme izlazakSunca(5, 48, 0);
    cout << izlazakSunca << " => " << (izlazakSunca.isValid() ? "validno vrijeme" : "nevalidno vrijeme") << endl;
    Vrijeme podne(12, 47, 0);
    cout << podne << " => " << (podne.isValid() ? "validno vrijeme" : "nevalidno vrijeme") << endl;
    Vrijeme zalazakSunca(19, 50, 0);
    cout << zalazakSunca << " => " << (zalazakSunca.isValid() ? "validno vrijeme" : "nevalidno vrijeme") << endl;
    cout << "\nDealokacija" << endl;
}
void zadatak2() {
    cout << "Generisanje slucajnog datuma i vremena: " << endl;
    DatumVrijeme dv = DatumVrijeme::getRandomDatumVrijeme();
    cout << dv << endl;
    cout << "User-def ctor: " << endl;
    DatumVrijeme dv2(dv.getDan(), dv.getMjesec(), dv.getGodina(), dv.getSati(), dv.getMinute(), dv.getSekunde());
    cout << dv2 << endl;
    cout << "Copy ctor: " << endl;
    DatumVrijeme dv3(dv2);
    cout << dv3 << endl;
    cout << "Operator '=': " << endl;
    DatumVrijeme dv4;
    dv4 = dv;
    cout << dv4 << endl;
    cout << endl;
    cout << "Ispis slucajnih vrijednosti: -->" << endl;
    for (int i = 0; i < 15; i++)
        cout << DatumVrijeme::getRandomDatumVrijeme() << "\n\n";
}
void zadatak3() {
    cout << ":::::::::: Array<int,30> :::::::::::\n";
    Array<int, 30> ocjene;
    for (int i = 0; i < 20; i++)
        ocjene.add(rand() % 10 + 1);

    cout << "\nIspis elemenata niza (array-a)." << endl;
    ispis(ocjene, ", ");

    cout << "\nUklanjanje zadnjeg elementa. " << endl;
    ocjene.removeZadnji();
    ispis(ocjene, ", ");

    cout << "\nInsertovanje elementa 10 na lokaciju [1]. " << endl;
    ocjene.insertAt(1, 10);
    ispis(ocjene, ", ");

    cout << "\nInsertovanje elementa 9 na lokaciju [1]. " << endl;
    ocjene.insertAt(1, 9);
    ispis(ocjene, ", ");

    cout << "\nBrisanje elementa na lokaciji [1]. " << endl;
    ocjene.removeAt(1);
    ispis(ocjene, ", ");

    cout << "\nBrisanje elementa na lokaciji [1]. " << endl;
    ocjene.removeAt(1);
    ispis(ocjene, ", ");

    Array<int, 30> ocjene2(ocjene);
    Array<int, 30> ocjene3;
    ocjene3 = ocjene;
    cout << "\nDealokacija..." << endl;
}
void zadatak4() {
    Osoba realDonaldTrump;
    realDonaldTrump.setIme("Donald J.");
    realDonaldTrump.setPrezime("Trump");
    realDonaldTrump.setDatumRodjenja(DatumVrijeme::getRandomDatumVrijeme());
    realDonaldTrump.setSpol(Spol::Muski);
    cout << ">>> Printanje objekta 'realDonaldTrump' <<<" << endl;
    cout << realDonaldTrump << endl;

    Osoba borisJohnson(realDonaldTrump);
    borisJohnson.setIme("Boris");
    borisJohnson.setPrezime("Johnson");
    borisJohnson.setDatumRodjenja(DatumVrijeme::getRandomDatumVrijeme());
    borisJohnson.setSpol(Spol::Muski);
    cout << ">>> Printanje objekta 'borisJohnson' <<<" << endl;
    cout << borisJohnson << endl;
    cout << "Dealokacija" << endl;
}
void zadatak5() {
    Pjevac theRocketMan;
    theRocketMan.setIme("Kim");
    theRocketMan.setPrezime("Jong-un");
    theRocketMan.setDatumRodjenja(DatumVrijeme(32, 12, 1940, 01, 00, 00));
    theRocketMan.setSpol(Spol::Muski);
    theRocketMan.setZanr("K-pop");
    theRocketMan.setAktivan("2011-present");
    theRocketMan.dodajInstrument("bubnjevi");
    theRocketMan.dodajInstrument("bongo");
    theRocketMan.dodajInstrument("klavir");
    cout << ">>> Printanje objekta 'theRocketMan' <<<" << endl;
    cout << theRocketMan << endl;

    cout << ">>> Kreiranje kopije objekta 'kPopPrince'... <<<" << endl;
    Pjevac kPopPrince(theRocketMan);
    cout << "Done." << endl;
    Pjevac sendMeNukes;
    cout << ">>> Kreiranje kopije objekta 'sendMeNukes'... <<<" << endl;
    sendMeNukes = theRocketMan;
    cout << "Done." << endl;
    cout << endl;
    cout << "Dealokacija" << endl;
}
void zadatak6() {
    Pjesma horseWithNoName;
    horseWithNoName.setNaziv("America - A Horse With No Name");
    horseWithNoName.setTekst("On the first part of the journey I was looking at all the life");
    horseWithNoName.setTrajanje(make_pair(4, 7));
    horseWithNoName.setTekstopisac("Dewey Bunnell");
    horseWithNoName.dodajZanr("folk rock");
    horseWithNoName.dodajZanr("soft rock");
    horseWithNoName.dodajZanr("country rock");
    cout << ">>> Printanje objekta 'horseWithNoName' <<< " << endl;
    cout << horseWithNoName << endl;

    cout << ">>> Kreiranje kopije objekta 'gtaSaSong'... <<< " << endl;
    Pjesma gtaSaSong(horseWithNoName.getNaziv(), horseWithNoName.getTekst(), horseWithNoName.getTrajanje(), horseWithNoName.getTekstopisac());
    gtaSaSong.dodajZanr("folk rock");
    gtaSaSong.dodajZanr("soft rock");
    gtaSaSong.dodajZanr("country rock");
    cout << "Done." << endl;

    cout << ">>> Kreiranje kopije objekta 'breakingBadSong'... <<<" << endl;
    Pjesma breakingBadSong(horseWithNoName);
    cout << "Done." << endl;

    cout << ">>> Kreiranje kopije objekta 'joeysFailedAudition'... <<<" << endl;
    Pjesma joeysFailedAudition;
    joeysFailedAudition = horseWithNoName;
    cout << "Done." << endl;
    cout << "Dealokacija" << endl;
}
void zadatak7() {
    Album finalHour;
    finalHour.setNaziv("Face to face");
    finalHour.setPjevac(
        Pjevac("Phil", "Collins", DatumVrijeme(13, 5, 1951, 14, 30, 00), Spol::Muski, "Pop", "1963-2011")
    );
    // Pjesme
    Pjesma inTheAirTonight("In the air tonight", "I can feel it coming in the air tonight...", make_pair(5, 34), "Phil Collins");
    inTheAirTonight.dodajZanr("Experimental pop");
    inTheAirTonight.dodajZanr("Soft rock");
    Pjesma anotherDay("Another day in paradise", "She calls out to the man on the street...", make_pair(4, 40), "Phil Collins");
    anotherDay.dodajZanr("Soft rock");
    Pjesma rainItDown("I Wish It Would Rain Down", "You know I never meant to see you again...", make_pair(4, 11), "Phil Collins");
    rainItDown.dodajZanr("Pop");

    // Dodavanje
    finalHour += inTheAirTonight;
    finalHour += anotherDay;
    finalHour += rainItDown;
    finalHour += "Atlas Music Publishing";
    finalHour += "Concord Music Publising";
    finalHour += "Big Deal Music";
    finalHour += "Bluewater Music";
    cout << finalHour << endl;

    cout << ">>> Kreiranje kopije objekta 'copycat'... <<<" << endl;
    Album copycat(finalHour);
    cout << "Done." << endl;

    cout << ">>> Kreiranje kopije objekta 'imaginationLevelZero'... <<<" << endl;
    Album imaginationLevelZero;
    imaginationLevelZero = finalHour;
    cout << "Done." << endl;
    cout << "Dealokacija" << endl;
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
            cout << "(7) Zadatak 7" << endl;
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 7);
        switch (izbor) {
        case 1: zadatak1(); cout << "Zadatak 1. Done." << endl; break;
        case 2: zadatak2(); cout << "Zadatak 2. Done." << endl; break;
        case 3: zadatak3(); cout << "Zadatak 3. Done." << endl; break;
        case 4: zadatak4(); cout << "Zadatak 4. Done." << endl; break;
        case 5: zadatak5(); cout << "Zadatak 5. Done." << endl; break;
        case 6: zadatak6(); cout << "Zadatak 6. Done." << endl; break;
        case 7: zadatak7(); cout << "Zadatak 7. Done." << endl; break;
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