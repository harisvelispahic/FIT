// 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
// 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
// 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
#include <iostream>
using namespace std;

char* alocirajTekst(const char* izvor) {
    if (izvor == nullptr)
        return nullptr;
    int size = strlen(izvor) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, izvor);
    return temp;
}

template<class T1, class T2>
class Kolekcija
{
    T1* _elementi1 = nullptr;
    T2* _elementi2 = nullptr;
    int _trenutnoElemenata = 0;
public:

    int getTrenutno() const { return _trenutnoElemenata; }
    T1* getElementi1() const { return _elementi1; }
    T2* getElementi2() const { return _elementi2; }

    
    void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
        T1* _elementi1 = new T1[trenutno];
        T2* _elementi2 = new T2[trenutno];

        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                AddElement(elementi1[i], elementi2[i]);
            }
        }
    }

    void expandElementi() {
        T1* temp1 = new T1[_trenutnoElemenata + 1];
        T2* temp2 = new T2[_trenutnoElemenata + 1];

        for (int i = 0; i < _trenutnoElemenata; i++) {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = temp1;
        _elementi2 = temp2;
    }

    bool AddElement(const T1& element1, const T2& element2) {
        for (int i = 0; i < _trenutnoElemenata; i++) {
            if (_elementi1[i] == element1)
                return false;
        }

        expandElementi();
        _elementi1[_trenutnoElemenata] = element1;
        _elementi2[_trenutnoElemenata++] = element2;
        
        return true;
    }

    bool RemoveElement(int index) {
        if (index >= 0 && index < _trenutnoElemenata) {
            for (int i = index; i < _trenutnoElemenata - 1; i++) {
                _elementi1[i] = _elementi1[i + 1];
                _elementi2[i] = _elementi2[i + 1];
            }
            _trenutnoElemenata--;
            return true;
        }
        return false;
    }

    Kolekcija() {
        setElementi();
    }

    Kolekcija(int trenutno, T1* elementi1, T2* elementi2) {
        setElementi(trenutno, elementi1, elementi2);
    }

    Kolekcija(const Kolekcija& obj) {
        setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
    }

    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj)
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        return *this;
    }

    template <class T1, class T2>
    friend ostream& operator<<(ostream& COUT, const Kolekcija<T1, T2>& obj);
};
template <class T1, class T2>
ostream& operator<<(ostream& COUT, const Kolekcija<T1, T2>& obj) {
    for (int i = 0; i < obj.getTrenutno(); i++) {
        COUT << "<" << (obj.getElementi1())[i] << ", " << (obj.getElementi2())[i] << ">" << endl;
    }
    return COUT;
}

class Datum
{
    int* _dan = nullptr;
    int* _mjesec = nullptr;
    int* _godina = nullptr;
public:

    int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
    int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
    int getGodina() const { return (_godina == nullptr) ? 1970 : *_godina; }

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

    Datum(int dan = 1, int mjesec = 1, int godina = 1970)
    {
        setDan(dan);
        setMjesec(mjesec);
        setGodina(godina);
    }

    Datum(const Datum& obj) {
        setDan(obj.getDan());
        setMjesec(obj.getMjesec());
        setGodina(obj.getGodina());
    }

    Datum& operator=(const Datum& obj) {
        if (this != &obj) {
            setDan(obj.getDan());
            setMjesec(obj.getMjesec());
            setGodina(obj.getGodina());
        }
        return *this;
    }

    ~Datum()
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj);
};

ostream& operator<< (ostream& COUT, const Datum& obj)
{
    COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina();
    return COUT;
}

bool operator==(const Datum& d1, const Datum& d2) {
    return d1.getDan() == d2.getDan() &&
        d1.getMjesec() == d2.getMjesec() &&
        d1.getGodina() == d2.getGodina();
}

class Student
{
    char* _imePrezime = nullptr;
    Datum* _datumRodjenja = nullptr;
public:

    const char* getImePrezime() const { return (_imePrezime == nullptr) ? "" : _imePrezime; }
    Datum getDatumRodjenja() const { return(_datumRodjenja == nullptr) ? Datum() : *_datumRodjenja; }

    void setImePrezime(const char* imePrezime) {
        _imePrezime = alocirajTekst(imePrezime);
    }

    void setDatumRodjenja(const Datum& datum) {
        if (_datumRodjenja == nullptr)
            _datumRodjenja = new Datum;
        *_datumRodjenja = datum;
    }
    
    Student(const char* imePrezime = "---", Datum d = Datum())
    {
        setImePrezime(imePrezime);
        setDatumRodjenja(d);
    }

    Student(const Student& obj) {
        setImePrezime(obj.getImePrezime());
        setDatumRodjenja(obj.getDatumRodjenja());
    }

    Student& operator=(const Student& obj) {
        if (this != &obj) {
            setImePrezime(obj.getImePrezime());
            setDatumRodjenja(obj.getDatumRodjenja());
        }
        return *this;
    }

    ~Student() { 
        delete[] _imePrezime;
        _imePrezime = nullptr;
        delete _datumRodjenja;
        _datumRodjenja = nullptr;
    }
};

ostream& operator << (ostream& COUT, const Student& obj) {
    COUT << "Ime i prezime studenta: " << obj.getImePrezime() << endl;
    COUT << "Datum rodjenja studenta: " << obj.getDatumRodjenja() << endl;
    return COUT;
}

bool operator==(const Student& obj1, const Student& obj2) {
    //return !(strcmp(obj1.getImePrezime(), obj2.getImePrezime())) && obj1.getDatumRodjenja() == obj2.getDatumRodjenja();
    return strcmp(obj1.getImePrezime(), obj2.getImePrezime()) == 0
        && obj1.getDatumRodjenja() == obj2.getDatumRodjenja();
}

class Ispit
{
    Datum _datumOdrzavanja;
    char* _opisIspita = nullptr;
    Kolekcija<Student, Datum> _prijave;
    Kolekcija<Student, int> _rezultati;
    bool _zakljuceniRezultati = false;

public:

    Datum getDatumOdrzavanja() const { return _datumOdrzavanja; }
    const char* getOpisIspita() const { return (_opisIspita == nullptr) ? "" : _opisIspita; }
    Kolekcija<Student, Datum> getPrijave() const { return _prijave; }
    Kolekcija<Student, int> getRezultati() const { return _rezultati; }
    bool getZakljuceniRezultati() const { return _zakljuceniRezultati; }

    void setDatumOdrzavanja(Datum datumOdrzavanja) {
        _datumOdrzavanja = datumOdrzavanja;
    }
    void setOpisIspita(const char* opisIspita) {
        _opisIspita = alocirajTekst(opisIspita);
    }
    void setPrijave(Kolekcija<Student, Datum> prijave) {
        _prijave = prijave;
    }
    void setRezultati(Kolekcija<Student, int> rezultati) {
        _rezultati = rezultati;
    }


    Ispit(const char* opisIspita = "---", Datum datumOdrzavanja = Datum()) {
        setDatumOdrzavanja(datumOdrzavanja);
        setOpisIspita(opisIspita);
        setPrijave(Kolekcija<Student, Datum>());
        setRezultati(Kolekcija<Student, int>());
    }


    bool DodajPrijavu(Student student, Datum datum) {
        return _prijave.AddElement(student, datum);
    }

    void DodajRezultat(Student student, int ocjena) {
        bool pronadjen = false;
        for (int i = 0; i < _prijave.getTrenutno(); i++) {
            if (_prijave.getElementi1()[i] == student)
                pronadjen = true;
        }
        if (pronadjen) {
            _rezultati.AddElement(student, ocjena);
        }
    }

    void Sortiraj() {
        bool desilaSePromjena = true;
        int brojRezultata = _rezultati.getTrenutno() - 1;
        while (desilaSePromjena) {
            desilaSePromjena = false;
            for (int i = 0; i < brojRezultata; i++) {
                if (_rezultati.getElementi2()[i] < _rezultati.getElementi2()[i + 1]) {
                    swap(_rezultati.getElementi1()[i], _rezultati.getElementi1()[i + 1]);
                    swap(_rezultati.getElementi2()[i], _rezultati.getElementi2()[i + 1]);
                    desilaSePromjena = true;
                }
            }
            brojRezultata--;
        }
    }

    void ZakljuciRezultate() {
        for (int i = 0; i < _prijave.getTrenutno(); i++) {
            Student neocijenjen = _prijave.getElementi1()[i];
            bool pronadjen = false;
            for (int j = 0; j < _rezultati.getTrenutno(); j++) {
                if (neocijenjen == _rezultati.getElementi1()[j]) {
                    pronadjen = true;
                }
            }
            if (pronadjen == false) {
                _rezultati.AddElement(neocijenjen, 5);      // settuje mu ocjenu 5, ako nije pronadjen
                //_prijave.getElementi2()[i] = 5;
            }
        }
        _zakljuceniRezultati = true;
    }
};

ostream& operator<< (ostream& COUT, const Ispit& obj) {
    if (obj.getZakljuceniRezultati()) {
        for (int i = 0; i < obj.getRezultati().getTrenutno(); i++) {
            COUT << obj.getRezultati().getElementi1()[i];
            COUT << "Ocjena: ";
            COUT << obj.getRezultati().getElementi2()[i] << endl << endl;
        }
    }
    return COUT;
}

const char* crt = "\n--------------------------------------------------\n";

int main()
{
    //REGIONI olaksavaju organizaciju programskog code-a, te ih mozete ukloniti ukoliko vam otezavaju preglednost

#pragma region TestiranjeKolekcije
    Kolekcija<int, double> kolekcija1;
    for (size_t i = 0; i < 50; i++)
        kolekcija1.AddElement(i, i + 0.3);
    cout << kolekcija1 << endl;
    cout << crt;

    Kolekcija<int, double> kolekcija2;
    kolekcija2 = kolekcija1;
    kolekcija1.RemoveElement(2);//UMANJITI VELICINU NIZA
    cout << kolekcija2 << crt;

    if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;

    Kolekcija<int, double> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeStudenta
    Student denis("Denis Music", Datum(26, 11, 1990));
    Student jasmin("Jasmin Azemovic", Datum(22, 11, 1990));
    Student goran;
    goran = jasmin;
    Student adel("Adel Handzic", Datum(25, 8, 1990));
    Student marija("Marija Herceg", Datum(15, 6, 1990));
#pragma endregion

#pragma region TestiranjeIspita
    Ispit prIII("PRIII::26.11.2015", danas);
    //DodajPrijavu - dodaje novog studenta u listu prijavljenih za ispit. 
    //onemoguciti dodavanje dva ista studenta
    if (prIII.DodajPrijavu(denis, danas))
        cout << denis << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(jasmin, danas))
        cout << jasmin << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(goran, danas))                           // goran nije dodat jer je kopija jasmina
        cout << goran << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(adel, danas))
        cout << adel << " DODAT na spisak" << endl;
    if (prIII.DodajPrijavu(marija, danas))
        cout << marija << " DODAT na spisak" << endl;

    cout << crt << endl;
    /*DodajRezultat - dodaje ocjenu koju je student ostvario na ispitu.
    za dodavanje ocjene student je prethodno trebao biti prijavljen na ispit
    */
    prIII.DodajRezultat(goran, 7);
    prIII.DodajRezultat(jasmin, 6);                     // jasmin ce imat 7, jer je goran = jasmin, a zabranjeno je ponovno dodavanje, tako da 6 nece bit primijenjeno
    prIII.DodajRezultat(adel, 8);
    prIII.DodajRezultat(marija, 9);

    /*Sortiraj - sortira rezultate ispita prema ocjeni*/
    prIII.Sortiraj();
    /*ZakljuciRezultate - dodaje ocjenu 5 svim studentima koji su prijavili ispit
    a nije im evidentirana ocjena*/
    prIII.ZakljuciRezultate();
    //rezultati ispita se smiju ispisivati jedino ukoliko su prethodno zakljuceni
    cout << prIII << crt;

    Ispit prIII_2(prIII);
    cout << prIII_2 << crt;
#pragma endregion

    return 0;
}