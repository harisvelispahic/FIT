#include <iostream>
#include <iomanip>

using namespace std;

const char* crt = "\n----------------------------------------------------\n";

char* alocirajTekst(const char* source) {
    if (source == nullptr)
        return nullptr;
    int size = strlen(source) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, source);
    return temp;
}

template<class T1, class T2>
class Kolekcija
{
    T1* _elementi1 = nullptr;
    T2* _elementi2 = nullptr;
    int* _trenutno = nullptr;
public:
    Kolekcija()
    {
        setElementi();
    }
    Kolekcija(const Kolekcija& obj) {
        setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj)
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        return *this;
    }
    //1. potrebne funkcije	
    ~Kolekcija()
    {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }

    T1* getElementi1() const { return _elementi1; }
    T2* getElementi2() const { return _elementi2; }
    int getTrenutno() const { return (_trenutno == nullptr) ? 0 : *_trenutno; }
    T1& getElement1(int index) const {
        if (index < 0 || index >= getTrenutno())
            throw exception("Indeks van granica!");
        return _elementi1[index];
    }
    T2& getElement2(int index) const {
        if (index < 0 || index >= getTrenutno())
            throw exception("Indeks van granica!");
        return _elementi2[index];
    }

    void setTrenutno(int trenutno = 0) {
        if (_trenutno == nullptr)
            _trenutno = new int;
        *_trenutno = trenutno;
    }

    void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
        delete[] _elementi1;
        delete[] _elementi2;

        setTrenutno();

        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                AddElement(elementi1[i], elementi2[i]);
            }
        }
    }

    void AddElement(const T1& el1, const T2& el2) {
        expand();
        _elementi1[getTrenutno()] = el1;
        _elementi2[getTrenutno()] = el2;
        setTrenutno(getTrenutno() + 1);
    }

    void expand() {
        T1* temp1 = new T1[getTrenutno() + 1];
        T2* temp2 = new T2[getTrenutno() + 1];

        for (int i = 0; i < getTrenutno(); i++) {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }
        
        delete[] _elementi1;
        delete[] _elementi2;
        
        _elementi1 = temp1;
        _elementi2 = temp2;
    }

    friend ostream& operator << (ostream& COUT, const Kolekcija<T1, T2>& obj) {
        for (int i = 0; i < obj.getTrenutno(); i++) {
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        }
        return COUT;
    }

    void zamijeniMjesta(int index) {
        if (index < 0 || index - 1 >= getTrenutno())
            throw exception("Indeks van granica!");
        swap(_elementi1[index], _elementi1[index + 1]);
        swap(_elementi2[index], _elementi2[index + 1]);
    }
};
class Datum
{
    int* _dan = nullptr, * _mjesec = nullptr, * _godina = nullptr;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000)
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
    Datum& operator = (const Datum& obj) {
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
    friend ostream& operator<< (ostream& COUT, const Datum& obj)
    {
        COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
        return COUT;
    }
    //1. potrebne funkcije
    int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
    int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
    int getGodina() const { return (_godina == nullptr) ? 2000 : *_godina; }

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
};
class Osoba
{
protected:
    char* _imePrezime = nullptr;
    Datum* _datumRodjenja = nullptr;
public:
    Osoba(const char* imePrezime, Datum datum)
    {
        setImePrezime(imePrezime);
        setDatumRodjenja(datum);
    }
    Osoba(const Osoba& obj)
    {
        setImePrezime(obj.getImePrezime());
        setDatumRodjenja(obj.getDatumRodjenja());
    }
    Osoba& operator=(const Osoba& obj) {
        if (this != &obj) {
            setImePrezime(obj.getImePrezime());
            setDatumRodjenja(obj.getDatumRodjenja());
        }
        return *this;
    }
    ~Osoba() { 
        delete[]_imePrezime; _imePrezime = nullptr;
        delete _datumRodjenja; _datumRodjenja = nullptr;
    }
    //1. potrebne funkcije
    const char* getImePrezime() const { return (_imePrezime == nullptr) ? "" : _imePrezime; }
    Datum getDatumRodjenja() const { return (_datumRodjenja == nullptr) ? Datum() : *_datumRodjenja; }

    void setImePrezime(const char* imePrezime) {
        delete[] _imePrezime;
        _imePrezime = alocirajTekst(imePrezime);
    }
    void setDatumRodjenja(const Datum& d) {
        if (_datumRodjenja == nullptr)
            _datumRodjenja = new Datum;
        *_datumRodjenja = d;
    }

    friend ostream& operator << (ostream& COUT, const Osoba& obj) {
        COUT << "Ime prezime: " << obj.getImePrezime() << endl;
        COUT << "Datum rodjenja: " << obj.getDatumRodjenja() << endl;
        return COUT;
    }
};


class Kupac : public Osoba
{
    //svaki kupac ima popust koji mu se zaracunava prilikom svake kupovine
    //pocetni popust je 0.10%
    //svaka kupovina u iznosu 100 - 500KM povecava iznos popusta za 0.15%
    //svaka kupovina u iznosu 500 - 1000KM povecava iznos popusta za 0.25%
    //svaka kupovina u iznosu vecem od 1000KM povecava iznos popusta za 0.30%
    float _odobreniPopust;
public:
    Kupac(const char* imePrezime = "", Datum datumRodjenja = Datum()) : Osoba(imePrezime, datumRodjenja)
    {
        _odobreniPopust = 0.10f;
    }
    Kupac(const Kupac& obj) : Osoba(obj){
        setOdobreniPopust(obj.getOdobreniPopust());
    }
    Kupac& operator=(const Kupac& obj) {
        if (this != &obj) {
            setOdobreniPopust(obj.getOdobreniPopust());
        }
        return *this;
    }
    ~Kupac() { }
    //1. potrebne funkcije
    float getOdobreniPopust() const { return _odobreniPopust; }
    void setOdobreniPopust(float odobreniPopust) { _odobreniPopust = odobreniPopust; }
    

};
class Artikal
{
    string _barCode;
    char* _naziv = nullptr;
    float _cijena;
public:
    Artikal(const char* naziv = "", float cijena = 0.0f, string barCode = "")
    {
        setNaziv(naziv);
        setBarCode(barCode);
        setCijena(cijena);
    }
    Artikal(const Artikal& obj) {
        setNaziv(obj.getNaziv());
        setBarCode(obj.getBarCode());
        setCijena(obj.getCijena());
    }
    Artikal& operator=(const Artikal& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setBarCode(obj.getBarCode());
            setCijena(obj.getCijena());
        }
        return *this;
    }
    ~Artikal() { delete[] _naziv; _naziv = nullptr; }
    friend ostream& operator<< (ostream& COUT, const Artikal& obj)
    {
        COUT << obj.getNaziv() << " " << obj.getCijena() << " KM" << endl;
        return COUT;
    }
    //1. potrebne funkcije
    string getBarCode() const { return _barCode; }
    const char* getNaziv() const { return (_naziv == nullptr) ? "" : _naziv; }
    float getCijena() const { return _cijena; }

    void setBarCode(string barCode) {
        _barCode = barCode;
    }
    void setNaziv(const char* naziv) {
        delete[] _naziv;
        _naziv = alocirajTekst(naziv);
    }
    void setCijena(float cijena) {
        _cijena = cijena;
    }
};

bool operator==(const Artikal& obj1, const Artikal& obj2) {
    return strcmp(obj1.getNaziv(), obj2.getNaziv()) == 0 && obj1.getBarCode() == obj2.getBarCode() && 
        obj1.getCijena() == obj2.getCijena();
}
class Racun
{
    //format broja racuna: RN6005491
    //osigurati automatsko generisanje broja racuna pocevsi od RN0000001
    char _brojRacuna[10];
    Datum _datumKreiranja;
    //prvi argument je Artikal, a drugi kolicina/broj artikala koju je kupac uzeo
    Kolekcija<Artikal*, int>* _stavkeRacuna = nullptr;
    Kupac* _kupac = nullptr;
public:
    
    static int brojacRacuna;
    Racun(const char* brojRacuna = "", Datum datumKreiranja = Datum(), Kupac* kupac = nullptr) {
        setBrojRacuna(brojRacuna);
        setDatumKreiranja(datumKreiranja);
        setKupac(kupac);
        _stavkeRacuna = new Kolekcija<Artikal*, int>;
    }

    Racun(const Racun& obj)
    {
        setBrojRacuna(obj.getBrojRacuna());
        setDatumKreiranja(obj.getDatumKreiranja());
        setKupac(obj.getKupac());
        setStavkeRacuna(obj.getStavkeRacuna());
    }
    Racun& operator=(const Racun& obj)
    {
        if(this != &obj) {
            setBrojRacuna(obj.getBrojRacuna());
            setDatumKreiranja(obj.getDatumKreiranja());
            setKupac(obj.getKupac());
            setStavkeRacuna(obj.getStavkeRacuna());
        }
        return *this;
    }
    ~Racun()
    {
        /*for (int i = 0; i < _stavkeRacuna->getTrenutno(); i++) {
            delete _stavkeRacuna->getElementi1()[i];
            _stavkeRacuna->getElementi1()[i] = nullptr;
        }*/
        // obzirom da smo artikle uzeli iz maina, necemo ih ovdje brisati ??????
        delete _stavkeRacuna; _stavkeRacuna = nullptr;
        //delete _kupac; _kupac = nullptr;
        // ni kupca ne treba brisati jer i on takodjer dolazi iz maina
    }

    const char* getBrojRacuna() const { return _brojRacuna; }
    Datum getDatumKreiranja() const { return _datumKreiranja; }
    //Kupac getKupac() const { return (_kupac == nullptr) ? Kupac() : *_kupac; }
    Kupac* getKupac() const { return _kupac; }
    Kolekcija<Artikal*, int> getStavkeRacuna() const {
        return (_stavkeRacuna == nullptr) ? Kolekcija<Artikal*, int>
            () : *_stavkeRacuna;
    }

    void setBrojRacuna(const char* brojRacuna) {
        strcpy_s(_brojRacuna, strlen(brojRacuna) + 1, brojRacuna);
    }
    void setDatumKreiranja(Datum datumKreiranja) {
        _datumKreiranja = datumKreiranja;
    }
    void setKupac(Kupac* kupac) {
        _kupac = kupac;
    }
    void setStavkeRacuna(Kolekcija<Artikal*, int> stavkeRacuna) {
        if (_stavkeRacuna == nullptr)
            _stavkeRacuna = new Kolekcija<Artikal*, int>;
        *_stavkeRacuna = stavkeRacuna;
    }

    // 1. potrebne (de)konstruktor i druge funkcije
    // 2. DodajArtikal - dodaje novi artikal u listu artikala zajedno sa njegovom kolicinom. Onemoguciti ponavljanje 
    //    artikala na nacin da se uvecava samo kolicina ukoliko korisnik vise puta pokusa dodati isti artikal.
    // 3. operator<< - ispisuje racun u formatu prikazanom na slici(nije obavezno da bude identican, ali je svakako pozeljno).
    //    Nakon ispisa svakog racuna, ukoliko su ispunjeni definisani uslovi, kupcu se uvecava popust.
    // 4. Sortiraj - sortira artikle (rastuci) po kolicini novca kojom ucestvuju u ukupnom iznosu racuna

    void DodajArtikal(Artikal& artikal, int kolicina) {
        for (int i = 0; i < _stavkeRacuna->getTrenutno(); i++) {
            if (*_stavkeRacuna->getElementi1()[i] == artikal && _stavkeRacuna->getElementi2()[i] == kolicina) {
                // samo uvecati kolicinu
                _stavkeRacuna->getElementi2()[i]++;
            }
        }
        _stavkeRacuna->AddElement(&artikal, kolicina);
    }

    void Sortiraj() {
        bool desilaSePromjena = true;
        int size = _stavkeRacuna->getTrenutno() - 1;
        while (desilaSePromjena) {
            desilaSePromjena = false;
            for (int i = 0; i < size - 1; i++) {
                if (_stavkeRacuna->getElementi1()[i]->getCijena() > _stavkeRacuna->getElementi1()[i + 1]->getCijena()) {
                    //swap(_stavkeRacuna->getElementi1()[i]->getCijena(), _stavkeRacuna->getElementi1()[i + 1]->getCijena());
                    _stavkeRacuna->zamijeniMjesta(i);
                    desilaSePromjena = true;
                }
                size--;
            }
        }
    }

};

int Racun::brojacRacuna = 1;

int getBrojCifara(int broj) {
    return (broj == 0) ? 1 : log10(abs(broj)) + 1;
}

const char* GenerisiSljedeciBrojRacuna() {
    //format broja racuna: RN6005491
    int sljedeci = Racun::brojacRacuna++;
    string rezultat = "RN";
    for (int i = 0; i < 7 - getBrojCifara(sljedeci); i++) {
        rezultat += '0';
    }
    rezultat += sljedeci + '0';
    // treba ovaj string sad nekako castovati u const char*
    /*return rezultat.c_str();   */                                 // chat.gpt
    char charRezultat[10];
    for (int i = 0; i < 10; i++) {
        charRezultat[i] = rezultat[i];
    }
    charRezultat[9] = '\0';
    return charRezultat;
}

ostream& operator << (ostream& COUT, const Racun& obj) {
    /*
    FITStore::Racun::RN000001
    | RB Artikal Cijena Kolicina Ukupno |
    | 1. Milka Milkins 2.55 15 38.25 |
    | 2. Cappy narandza 2.1 20 42 |
    | 3. Meggle jogurt 2.55 20 51 |
    | Suma:131.25KM
    | Popust : 0.1KM
    | Za platiti : 131.15KM
    */
    
    //svaki kupac ima popust koji mu se zaracunava prilikom svake kupovine
    //pocetni popust je 0.10%
    //svaka kupovina u iznosu 100 - 500KM povecava iznos popusta za 0.15%
    //svaka kupovina u iznosu 500 - 1000KM povecava iznos popusta za 0.25%
    //svaka kupovina u iznosu vecem od 1000KM povecava iznos popusta za 0.30%
    int r = 15;
    COUT << "FITStore::Racun::" << obj.getBrojRacuna() << endl;
    COUT << "|" << setw(r) <<  "RB" << setw(r) << "Artikal" <<setw(r) << "Cijena" << setw(r) << " Kolicina" << setw(r) 
        << " Ukupno" << setw(5) << " |" << endl;
    int suma = 0;
    for (int i = 0; i < obj.getStavkeRacuna().getTrenutno(); i++) {
        int ukupno = obj.getStavkeRacuna().getElement1(i)->getCijena() * obj.getStavkeRacuna().getElementi2()[i];
        COUT << "| " << setw(r) << i + 1 << ". " << setw(r) << obj.getStavkeRacuna().getElement1(i)->getNaziv() << setw(r) <<
            obj.getStavkeRacuna().getElement1(i)->getCijena() << setw(r) <<
            obj.getStavkeRacuna().getElement2(i) << setw(r) <<
            ukupno << " |" << endl;
        suma += ukupno;
    }
    COUT << "| Suma: " << suma << endl;
    float popust = obj.getKupac()->getOdobreniPopust();
    COUT << "| Popust: " << popust << " KM" << endl;
    COUT << "| Za platiti: " << suma * (1.0f - popust/100) << " KM" << endl;        // pozeljna opcija
    //COUT << "| Za platiti: " << suma - popust << endl;

    if (suma >= 100 && suma < 500)
        obj.getKupac()->setOdobreniPopust(popust + 0.15);
    else if (suma >= 500 && suma < 1000)
        obj.getKupac()->setOdobreniPopust(popust + 0.25);
    else if (suma >= 1000)
        obj.getKupac()->setOdobreniPopust(popust + 0.30);
        
    return COUT;
}

void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU
    //    RUNTIME ERROR CE BITI OZNACENO KAO "RE"
    // 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
    // 5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U.
    // 6. NIJE POTREBNO BACATI IZUZETKE.
    ****************************************************************************/
#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion

#pragma region TestiranjeKolekcije
    Kolekcija<int, int> kolekcija1;
    int brojElemenata = 15;
    for (size_t i = 0; i < brojElemenata; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1.getElement1(0) << " " << kolekcija1.getElement2(0) << endl;
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;

    cout << kolekcija2 << crt;
    if (kolekcija1.getTrenutno() == kolekcija2.getTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;

    Kolekcija<int, int> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeKupca
    Kupac jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
    Kupac adel("Adel Handzic", Datum(15, 10, 1981));

    Kupac jasmin2 = jasmin;
    cout << jasmin << endl << jasmin2 << endl;
    jasmin = jasmin2;
    cout << jasmin << endl << jasmin2 << endl;
#pragma endregion

#pragma region TestiranjeArtikla
    Artikal sokCppyNarandza("Cappy narandza", 2.10, "699511236545");
    Artikal cokoladaMilkaMilkins("Milka Milkins", 2.55, "622445875463");
    Artikal jogurtMeggle("Meggle jogurt", 2.55, "155338774458");

    cout << sokCppyNarandza << cokoladaMilkaMilkins << jogurtMeggle << endl;
    sokCppyNarandza = cokoladaMilkaMilkins;
    cout << sokCppyNarandza << endl;

    if (sokCppyNarandza == cokoladaMilkaMilkins)
        cout << "Artikli su isti" << endl;
#pragma endregion

#pragma region TestiranjeRacuna
    /*GenerisiSljedeciBrojRacuna - globalna funkcija koja generise i vraca naredni broj racuna u
    prethodno definisanom formatu*/
    Racun racun1(GenerisiSljedeciBrojRacuna(), danas, &jasmin);

    racun1.DodajArtikal(cokoladaMilkaMilkins, 15);
    racun1.DodajArtikal(sokCppyNarandza, 20);
    racun1.DodajArtikal(jogurtMeggle, 20);

    cout << racun1 << endl;

    Racun racun2(GenerisiSljedeciBrojRacuna(), sutra, &jasmin);
    racun2.DodajArtikal(cokoladaMilkaMilkins, 15);
    racun2.DodajArtikal(sokCppyNarandza, 20);
    racun2.DodajArtikal(jogurtMeggle, 20);
    cout << racun2 << endl;

    Racun racun3(racun2);
    cout << racun3 << endl;
    racun3.Sortiraj();

#pragma endregion

    system("pause");
}
//popust mozete izracunati kao procenat od ukupne sume racuna (pozeljna opcija) 
//ili kao vrijednost u KM-ovima (kao u nastavku)
/*
FITStore::Racun::RN000001
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.1KM
| Za platiti : 131.15KM


FITStore::Racun::RN000002
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.25KM
| Za platiti : 131KM


FITStore::Racun::RN000002
| RB Artikal Cijena Kolicina Ukupno |
| 1. Milka Milkins 2.55 15 38.25 |
| 2. Cappy narandza 2.1 20 42 |
| 3. Meggle jogurt 2.55 20 51 |
| Suma:131.25KM
| Popust : 0.4KM
| Za platiti : 130.85KM
*/