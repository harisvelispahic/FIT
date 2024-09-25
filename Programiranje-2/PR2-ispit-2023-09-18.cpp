#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <thread>
#include <mutex>
using namespace std;

const char* PORUKA = "\n-----------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. METODE KOJE NISU VOID, MORAJU VRACATI NEKU VRIJEDNOST!\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11. ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA (POZIVA FUNKCIJA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12. ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022!\n"
"13. RJESENJE TESTIRAJTE U OBA MODA (F5 i Ctrl+F5)\n"
"------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
ostream& operator<< (ostream& COUT, const Predmet& obj) {
    switch (obj) {
    case UIT: COUT << "UIT"; break;
    case PRI: COUT << "PRI"; break;
    case PRII: COUT << "PRII"; break;
    case PRIII: COUT << "PRIII"; break;
    case RSI: COUT << "RSI"; break;
    case RSII: COUT << "RSII"; break;
    default:
        break;
    }
    return COUT;
}

const int MaxBrojRjesenja = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

/*
    za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
    -   najmanje 7 znakova
    -   velika i mala slova
    -   najmanje jedan broj
    -   najmanje jedan specijalni znak
    */
bool ValidirajLozinku(string lozinka) {
    string min7znakova = "(?=.*.{7,})",
        velikaSlova = "(?=.*[A-Z])",
        malaSlova = "(?=.*[a-z])",
        broj = "(?=.*\\d)",
        specijalanZnak = "(?=.*\\W)";
    string uzorak = min7znakova + velikaSlova + malaSlova + broj + specijalanZnak;
    regex regObj(uzorak);
    return regex_search(lozinka, regObj);
}

mutex mutexObj;

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
        if(this!=&obj) {
            setTrenutno(obj.getTrenutno());
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        }
        return *this;
    }
    ~Kolekcija() {
        for (size_t i = 0; i < getTrenutno(); i++) {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
        delete _trenutno; _trenutno = nullptr;
    }
    T1 getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    T1** getElementi1() const { return (T1**)_elementi1; }
    T2** getElementi2() const { return (T2**)_elementi2; }
    int getTrenutno() const { return _trenutno == nullptr ? 0 : *_trenutno; }
    friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
        for (size_t i = 0; i < obj.getTrenutno(); i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    void setTrenutno(int trenutno) {
        if (_trenutno == nullptr)
            _trenutno = new int;
        *_trenutno = trenutno;
    }

    void Dealociraj() {
        for (int i = 0; i < getTrenutno(); i++) {
            delete _elementi1[i];
            delete _elementi2[i];
            _elementi1[i] = nullptr;
            _elementi2[i] = nullptr;
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

    bool AddElement(const T1& el1, const T2& el2, int lokacija = INT_MIN){
        if (getTrenutno() >= max)
            throw exception("Niz je popunjen!");
        if (lokacija == INT_MIN)
            lokacija = getTrenutno();
        if (lokacija < 0 || lokacija > getTrenutno())
            throw exception("Indeks van opsega!");

        _elementi1[getTrenutno()] = new T1(el1);
        _elementi2[getTrenutno()] = new T2(el2);

        setTrenutno(getTrenutno() + 1);

        for (int i = getTrenutno() - 1; i > lokacija; i--) {
            swap(_elementi1[i], _elementi1[i - 1]);
            swap(_elementi2[i], _elementi2[i - 1]);
        }
        return true;
    }

    T2& operator[](const T1& el1) {
        for (int i = 0; i < getTrenutno(); i++) {
            if (getElement1(i) == el1)
                return *_elementi2[i];
        }
    }

    /*kolekcija3 treba sadrzavati sve elemente koji se u kolekciji1 nalaze na lokacijama sa proslijedjenim indeksima,
    u ovom primjeru na lokacijama sa indeksom od 1 do 3, npr.ako unutar kolekcije1 postoje elementi:
       0 0
       9 9
       1 1
       2 2
       3 3
       sadrzaj kolekcije3 ce biti sljedeci
       9 9
       1 1
       2 2

       u slucaju da se zahtijevaju lokacije koje ne postoje u kolekciji, funkcija vraca samo one elemente koje postoje
       u zahtijevanom opsegu (bez bacanja izuzetaka).
    */
    Kolekcija<T1, T2>* operator()(int from, int to) {
        Kolekcija<T1, T2> temp;
        for (int i = from; i <= to; i++) {
            temp.AddElement(getElement1(i), getElement2(i));
        }
        return new Kolekcija<T1, T2>(temp);
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
        setDan(obj.getDan());
        setMjesec(obj.getMjesec());
        setGodina(obj.getGodina());
    }
    Datum& operator=(const Datum& obj) {
        if(this!=&obj) {
            setDan(obj.getDan());
            setMjesec(obj.getMjesec());
            setGodina(obj.getGodina());
        }
        return *this;
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina();
        return COUT;
    }

    int getDan() const { return _dan == nullptr ? 1 : *_dan; }
    int getMjesec() const { return _mjesec == nullptr ? 1 : *_mjesec; }
    int getGodina() const { return _godina == nullptr ? 2000 : *_godina; }

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

    int toInt() const { return getDan() + getMjesec() * 30.41 + getGodina() * 365.24; }
};

bool operator==(const Datum& d1, const Datum& d2) { return d1.toInt() == d2.toInt(); }
bool operator!=(const Datum& d1, const Datum& d2) { return !(d1 == d2); }
bool operator>(const Datum& d1, const Datum& d2) { return d1.toInt() > d2.toInt(); }
bool operator>=(const Datum& d1, const Datum& d2) { return d1.toInt() >= d2.toInt(); }
bool operator<(const Datum& d1, const Datum& d2) { return d1.toInt() < d2.toInt(); }
bool operator<=(const Datum& d1, const Datum& d2) { return d1.toInt() <= d2.toInt(); }

bool datumIzmedju(Datum& OD, Datum& DO, Datum& trazeniDatum) {
    return trazeniDatum.toInt() >= OD && trazeniDatum <= DO;
}

/*na odredjeno pitanje kandidat je duzan postaviti vise odgovora/rjesenja od kojih ce svako biti ocijenjeno*/
class Pitanje {
    char* _sadrzaj = nullptr;
    //int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
    Kolekcija<int, Datum*, MaxBrojRjesenja> _ocjeneRjesenja;
public:
    Pitanje(const char* sadrzaj = "") {
        _sadrzaj = GetNizKaraktera(sadrzaj);
    }
    Pitanje(const Pitanje& obj) {
        setSadrzaj(obj.GetSadrzaj());
        _ocjeneRjesenja = obj._ocjeneRjesenja;
    }
    Pitanje& operator=(const Pitanje& obj) {
        if(this!=&obj){
            setSadrzaj(obj.GetSadrzaj());
            _ocjeneRjesenja = obj._ocjeneRjesenja;
        }
        return *this;
    }
    ~Pitanje() {
        delete[] _sadrzaj; _sadrzaj = nullptr;
    }
    char* GetSadrzaj() const { return _sadrzaj; }
    Kolekcija<int, Datum*, MaxBrojRjesenja> GetOcjene() const { return _ocjeneRjesenja; }

    void setSadrzaj(const char* source) {
        delete[] _sadrzaj;
        _sadrzaj = GetNizKaraktera(source);
    }

    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */

    bool AddOcjena(Datum& datum, int ocjena) {
        Datum zadnjiDatum;
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); i++) {
            zadnjiDatum = *_ocjeneRjesenja.getElement2(i);
            if (datum < *_ocjeneRjesenja.getElement2(i))
                return false;
        }
        if (abs(datum.toInt() - zadnjiDatum.toInt()) < 3)
            return false;
        
        return _ocjeneRjesenja.AddElement(ocjena, &datum);
    }

    float getProsjecnaOcjena() const {
        if (_ocjeneRjesenja.getTrenutno() == 0)
            return 0;
        float suma = 0.0f;
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); i++) {
            suma += _ocjeneRjesenja.getElement1(i);
        }
        return suma / _ocjeneRjesenja.getTrenutno();
    }

    int getZadnjaOcjena() const {
        int ocjena = 0;
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); i++) {
            ocjena = _ocjeneRjesenja.getElement1(i);
        }
        return ocjena;
    }

    // ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
    // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    friend ostream& operator<< (ostream& COUT, const Pitanje& obj) {
        COUT << crt << "Pitanje: " << obj.GetSadrzaj() << endl;
        COUT << "Ocjene: " << endl;
        for (int i = 0; i < obj.GetOcjene().getTrenutno(); i++) {
            COUT << "\t" << obj.GetOcjene().getElement1(i) << " : " << *obj.GetOcjene().getElement2(i) << endl;
        }
        COUT << "Prosjek ocjena: " << obj.getProsjecnaOcjena() << crt;
        return COUT;
    }  
};


bool operator==(const Pitanje& p1, const Pitanje& p2) {
    if (strcmp(p1.GetSadrzaj(), p2.GetSadrzaj()) != 0 || p1.GetOcjene().getTrenutno() != p2.GetOcjene().getTrenutno())
        return false;
    for (int i = 0; i < p1.GetOcjene().getTrenutno(); i++) {
        if (p1.GetOcjene().getElement1(i) != p2.GetOcjene().getElement1(i) ||
            *p2.GetOcjene().getElement2(i) != *p2.GetOcjene().getElement2(i))
            return false;
    }
    return true;
}


class Ispit {
    Predmet* _predmet = nullptr;
    vector<Pitanje> _pitanjaOdgovori;
public:
    Ispit(Predmet predmet = UIT) {
        _predmet = new Predmet(predmet);
    }
    Ispit(const Ispit& obj) {
        setPredmet(obj.GetPredmet());
        _pitanjaOdgovori = obj._pitanjaOdgovori;
    }
    Ispit& operator=(const Ispit& obj) {
        if(this!=&obj){
            setPredmet(obj.GetPredmet());
            _pitanjaOdgovori = obj._pitanjaOdgovori;
        }
        return *this;
    }
    ~Ispit() {
        delete _predmet; _predmet = nullptr;
    }
    vector<Pitanje>& GetPitanjaOdgovore() { return _pitanjaOdgovori; }
    vector<Pitanje> constGetPitanjaOdgovore() const { return _pitanjaOdgovori; }
    Predmet GetPredmet() const { return *_predmet; }
    void setPredmet(Predmet predmet) {
        if (_predmet == nullptr)
            _predmet = new Predmet();
        *_predmet = predmet;
    }
    friend ostream& operator<< (ostream& COUT, const Ispit& obj) {
        COUT << obj.GetPredmet() << endl;
        for (size_t i = 0; i < obj._pitanjaOdgovori.size(); i++)
            COUT << obj.constGetPitanjaOdgovore()[i];
        return COUT;
    }
};

class Korisnik {
protected:
    char* _imePrezime = nullptr;
    string _emailAdresa;
    string _lozinka;
    bool _aktivan;
public:
    Korisnik(const char* imePrezime, string emailAdresa, string lozinka) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
        _aktivan = true;
    }
    Korisnik(const Korisnik& obj) {
        setImePrezime(obj.GetImePrezime());
        _emailAdresa = obj._emailAdresa;
        _lozinka = obj._lozinka;
        _aktivan = obj._aktivan;
    }
    Korisnik& operator=(const Korisnik& obj) {
        if(this!=&obj){
            setImePrezime(obj.GetImePrezime());
            _emailAdresa = obj._emailAdresa;
            _lozinka = obj._lozinka;
            _aktivan = obj._aktivan;
        }
        return *this;
    }
    virtual ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
    string GetEmail() { return _emailAdresa; }
    string GetLozinka() { return _lozinka; }
    char* GetImePrezime() const { return _imePrezime; }
    bool GetAktivan() const { return _aktivan; }
    void SetAktivan(bool aktivan) { _aktivan = aktivan; }
    virtual void Info() = 0;

    void setImePrezime(const char* source) {
        delete[] _imePrezime;
        _imePrezime = GetNizKaraktera(source);
    }

    friend ostream& operator<<(ostream& COUT, const Korisnik& obj) {
        COUT << "Ime i prezime: " << obj.GetImePrezime() << "\nEmail: " << obj._emailAdresa << "\nLozinka: " << obj._lozinka;
        COUT << "Aktivan: " << boolalpha << obj.GetAktivan() << endl;
        return COUT;
    }
};
class Kandidat : public Korisnik{
    vector<Ispit*> _polozeniPredmeti;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka) : Korisnik(imePrezime, emailAdresa, lozinka) {
    }
    Kandidat(const Kandidat& obj) : Korisnik(obj) {
        _polozeniPredmeti = obj._polozeniPredmeti;
    }
    Kandidat& operator=(const Kandidat& obj) {
        if (this != &obj) {
            (Korisnik&)(*this) = obj;
            _polozeniPredmeti = obj._polozeniPredmeti;
        }
        return *this;
    }
    ~Kandidat() {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i], _polozeniPredmeti[i] = nullptr;
        cout << crt << "KANDIDAT :: DESTRUKTOR" << crt;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << (Korisnik&)obj << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++)
            COUT << "Polozeni predmeti: " <<  *obj._polozeniPredmeti[i];
        return COUT;
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }

    void Info(){}

    float getProsjecnaOcjenaZaSvePredmete() {
        int brojac = 0;
        float suma = 0.0f;
        for (int i = 0; i < _polozeniPredmeti.size(); i++) {
            for (int j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().size(); j++) {
                for (int k = 0; k < _polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getTrenutno(); k++) {
                    suma += _polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getElement1(k);
                    brojac++;
                }
            }
        }
        return (brojac == 0) ? 0 : suma / brojac;
    }

    

    void PosaljiEmail(Pitanje& pitanje) {
        mutexObj.lock();
        this_thread::sleep_for(chrono::seconds(2));
        cout << "FROM: info@kursevi.ba\nTO: emailKorisnika\n\n";
        cout << "Postovani ime i prezime, evidentirana vam je ocjena " << pitanje.getZadnjaOcjena() << " za odgovor na pitanje \"" << 
            pitanje.GetSadrzaj() << "\". Dosadasnji uspjeh(prosjek ocjena)";
        cout << " za pitanje \"" << pitanje.GetSadrzaj() << "\" iznosi " << pitanje.getProsjecnaOcjena() <<
            ", a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi " << getProsjecnaOcjenaZaSvePredmete() << ".\n";
        cout << "Pozdrav.\n\nEDUTeam.\n\n\n";
        mutexObj.unlock();
    }

    bool AddPitanje(Predmet predmet, Pitanje& pitanje) {
        if (!GetAktivan())
            return false;
        // pronalazenje predmeta
        bool pronadjen = false;
        for (int i = 0; i < _polozeniPredmeti.size(); i++) {
            if (_polozeniPredmeti[i]->GetPredmet() == predmet) {
                pronadjen = true;
            }
        }
        if (!pronadjen) {
            _polozeniPredmeti.push_back(new Ispit(predmet));
        }


        for (int i = 0; i < _polozeniPredmeti.size(); i++) 
        {
            if (_polozeniPredmeti[i]->GetPredmet() == predmet) 
            {
                for (int j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().size(); j++) 
                {
                    if (_polozeniPredmeti[i]->GetPitanjaOdgovore()[j] == pitanje)
                        return false;   // ako je pitanje vec u vektoru, ne treba ga dodati
                }
            }
        }

        if (predmet != UIT) {
            for (int i = 0; i < _polozeniPredmeti.size(); i++)
            {
                if (_polozeniPredmeti[i]->GetPredmet() == predmet - 1) 
                {
                    if (_polozeniPredmeti[i]->GetPitanjaOdgovore().size() < 3)
                        return false;   // manje od 3 pitanja

                    float prosjecnaOcjenaSvihPitanjaNaNivouPredmeta = 0.0f;
                    if (_polozeniPredmeti[i]->GetPitanjaOdgovore().size() == 0)
                        prosjecnaOcjenaSvihPitanjaNaNivouPredmeta = 0;
                    else {
                        for (int j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().size(); j++) {
                            prosjecnaOcjenaSvihPitanjaNaNivouPredmeta += _polozeniPredmeti[i]->GetPitanjaOdgovore()[j].getProsjecnaOcjena();
                        }
                        prosjecnaOcjenaSvihPitanjaNaNivouPredmeta /= _polozeniPredmeti[i]->GetPitanjaOdgovore().size();
                    }

                    if (prosjecnaOcjenaSvihPitanjaNaNivouPredmeta < 3.5)
                        return false;   // prosjek manji od 3.5

                }
            }
        }

        for (int i = 0; i < _polozeniPredmeti.size(); i++) 
        {
            if (_polozeniPredmeti[i]->GetPredmet() == predmet) 
            {
                _polozeniPredmeti[i]->GetPitanjaOdgovore().push_back(pitanje);
                break;
            }
        }

        thread SlanjeEmaila(&Kandidat::PosaljiEmail, this, std::ref(pitanje));

        SlanjeEmaila.detach();

        return true;
    }

    

    /*nakon evidentiranja ocjene na bilo kojem odgovoru, AKTIVNOM kandidatu se salje email sa porukom:

    FROM:info@kursevi.ba
    TO: emailKorisnika

    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.

    EDUTeam.

    slanje email poruka implemenitrati koristeci zasebne thread-ove na nacin da se jedna poruka salje svako 2 sekunde.
    */

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za viši predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    //onemoguciti dodavanje pitanja korisnicima koji nisu aktivni


    /*koristeci adekvatan operator osigurati pretragu pozitivno ocijenjenih odgovora u okviru pitanja u proslijedjenom vremenskom opsegu OD - DO.
    rezultat pretrage trebaju biti ona pitanja kojima je, u definisanom periodu, najmanje jedan odgovor ocijenjen pozitivno.drugi formalni
    argument tipa float predstavlja prosjecnu ocjenu odgovora na pronadjenom pitanju
    */
    
    Kolekcija<Pitanje, float> operator()(Datum OD, Datum DO) {
        Kolekcija<Pitanje, float> temp;
        for (int i = 0; i < _polozeniPredmeti.size(); i++) {
            for (int j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().size(); j++) {
                bool pozitivnaOcjena = false;
                bool naVrijeme = true;
                for (int k = 0; k < _polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getTrenutno(); k++) {
                    if (_polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getElement1(k) >= 2) {
                        pozitivnaOcjena = true;
                    }
                    if (!datumIzmedju(OD, DO, *_polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getElement2(k)))
                        naVrijeme = false;
                }
                if (pozitivnaOcjena && naVrijeme) {
                    temp.AddElement(_polozeniPredmeti[i]->GetPitanjaOdgovore()[j], 
                        _polozeniPredmeti[i]->GetPitanjaOdgovore()[j].getProsjecnaOcjena());
                }
            }
        }
        return temp;
    }
    /*

    class Kandidat : public Korisnik{
        vector<Ispit*> _polozeniPredmeti;

        class Ispit {
            Predmet* _predmet = nullptr;
            vector<Pitanje> _pitanjaOdgovori;

            class Pitanje {
                char* _sadrzaj = nullptr;
                //int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
                Kolekcija<int, Datum*, MaxBrojRjesenja> _ocjeneRjesenja;
                float getProsjecnaOcjena();

    */
};
 
 
//const char* GetOdgovorNaPrvoPitanje() {
//    cout << "Pitanje -> Pojasnite STACK i HEAP dio memorije, za šta su namijenjeni, te na koji način se trebaju koristiti (prednosti i nedostaci pojedinih slučajeva).\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
//const char* GetOdgovorNaDrugoPitanje() {
//    cout << "Pitanje -> Pojasnite preduslove za realizaciju polimorfizma, te koje su prednosti njegovog korištenja?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
void main() {

    /*cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();*/

    Datum   datum19062023(19, 6, 2023),
        datum20062023(20, 6, 2023),
        datum30062023(30, 6, 2023),
        datum05072023(5, 7, 2023);

    int kolekcijaTestSize = 10;

    Kolekcija<int, int> kolekcija1;
    for (int i = 0; i < kolekcijaTestSize - 2; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1 << endl;

    try {
        /*metoda AddElement baca izuzetak u slucaju da se pokusa
        dodati vise od maksimalnog broja elemenata. Ako zelite da testirate
izuzetak, uklonite -2 iz prethodne for petlje*/
        kolekcija1.AddElement(11, 11);
    }
    catch (exception& err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    kolekcija1.AddElement(9, 9, 2);
    /*funkciji AddElement se, kao treci parametar, moze proslijediti i lokacija na koju se dodaju
    nove vrijednosti pri cemu treba zadrzati postojece vrijednosti pomjerene za jedno mjesto unaprijed
    u odnosu na definisanu lokaciju npr. ako unutar kolekcije postoje elementi
    0 0
    1 1
    2 2
    3 3
    nakon dodavanja vrijednosti 9 i 9 na lokaciju 1, sadrzaj kolekcije ce biti sljedeci
    0 0
    9 9
    1 1
    2 2
    3 3
    */

    cout << kolekcija1 << crt;

    Kolekcija<int, int> kolekcija2 = kolekcija1;
    cout << kolekcija1 << crt;

    //na osnovu vrijednosti T1 mijenja vrijednost T2. 
    kolekcija1[9] = 2;
    /* npr.ako unutar kolekcije postoje elementi:
    0 0
    9 9
    1 1
    2 2
    3 3
    nakon promjene vrijednosti sadrzaj kolekcije ce biti sljedeci
    0 0
    9 2
    1 1
    2 2
    3 3
    */

    Kolekcija<int, int>* kolekcija3 = kolekcija1(1, 3);
    /*kolekcija3 treba sadrzavati sve elemente koji se u kolekciji1 nalaze na lokacijama sa proslijedjenim indeksima,
    u ovom primjeru na lokacijama sa indeksom od 1 do 3, npr.ako unutar kolekcije1 postoje elementi:
       0 0
       9 9
       1 1
       2 2
       3 3
       sadrzaj kolekcije3 ce biti sljedeci
       9 9
       1 1
       2 2

       u slucaju da se zahtijevaju lokacije koje ne postoje u kolekciji, funkcija vraca samo one elemente koje postoje
       u zahtijevanom opsegu (bez bacanja izuzetaka).
    */
    cout << *kolekcija3 << endl;
    delete kolekcija3;

    Pitanje sortiranjeNiza("Navedite algoritme za sortiranje clanova niza?"),
        dinamickaMemorija("Navedite pristupe za upravljanje dinamickom memorijom?"),
        visenitnoProgramiranje("Na koji se sve nacin moze koristiti veci broj niti tokom izvrsenja programa?"),
        regex("Navedite par primjera regex validacije podataka?"),
        polimorfizam("Na koji nacin se realizuje polimorfizam?");

    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    if (sortiranjeNiza.AddOcjena(datum19062023, 1))
        cout << "Ocjena evidentirana!" << endl;
    if (!sortiranjeNiza.AddOcjena(datum20062023, 5))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (sortiranjeNiza.AddOcjena(datum30062023, 5))
        cout << "Ocjena evidentirana!" << endl;

    if (polimorfizam.AddOcjena(datum19062023, 5))
        cout << "Ocjena evidentirana!" << endl;

    // ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
    // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    cout << sortiranjeNiza << endl;

    if (ValidirajLozinku("john4Do*e"))
        cout << "Lozinka :: OK :)" << crt;
    if (!ValidirajLozinku("john4Doe"))
        cout << "Lozinka :: Specijalni znak?" << crt;
    if (!ValidirajLozinku("jo*4Da"))
        cout << "Lozinka :: 7 znakova?" << crt;
    if (!ValidirajLozinku("4jo-hnoe"))
        cout << "Lozinka :: Veliko slovo?" << crt;
    if (ValidirajLozinku("@john2Doe"))
        cout << "Lozinka :: OK :)" << crt;

    /*
    za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
    -   najmanje 7 znakova
    -   velika i mala slova
    -   najmanje jedan broj
    -   najmanje jedan specijalni znak

    za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    */

    Korisnik* jasmin = new Kandidat("Jasmin Azemovic", "jasmin@kursevi.ba", "j@sm1N*");
    Korisnik* adel = new Kandidat("Adel Handzic", "adel@edu.kursevi.ba", "4Ade1*H");
    Korisnik* lozinkaNijeValidna = new Kandidat("John Doe", "john.doe@google.com", "johndoe");

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za viši predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od .5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    Kandidat* jasminPolaznik = dynamic_cast<Kandidat*>(jasmin);

    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija))
            cout << "Pitanje uspjesno dodano1!" << crt;
        //ne treba dodati visenitnoProgramiranje jer ne postoje evidentirana 3 pitanja za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRII, visenitnoProgramiranje))
            cout << "Pitanje NIJE uspjesno dodano2!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, visenitnoProgramiranje))
            cout << "Pitanje uspjesno dodano3!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, regex))
            cout << "Pitanje uspjesno dodano4!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje uspjesno dodano5!" << crt;
        //ne treba dodati sortiranjeNiza jer je vec dodana za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje NIJE uspjesno dodano6!" << crt;

        //onemoguciti dodavanje pitanja korisnicima koji nisu aktivni
        jasmin->SetAktivan(false);
        if (!jasminPolaznik->AddPitanje(PRII, polimorfizam))
            cout << "Pitanje NIJE uspjesno dodano7!" << crt;

        //ispisuje sve dostupne podatke o kandidatu
        cout << *jasminPolaznik << crt;
    }

    /*nakon evidentiranja ocjene na bilo kojem odgovoru, AKTIVNOM kandidatu se salje email sa porukom:

    FROM:info@kursevi.ba
    TO: emailKorisnika

    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.

    EDUTeam.

    slanje email poruka implemenitrati koristeci zasebne thread-ove na nacin da se jedna poruka salje svako 2 sekunde.
    */

    //osigurati da se u narednim linijama poziva i destruktor klase Kandidat

    Datum ocijenjenOD(19, 6, 2023), ocijenjenDO(1, 7, 2023);
    /*
    koristeci adekvatan operator osigurati pretragu pozitivno ocijenjenih odgovora u okviru pitanja u proslijedjenom vremenskom opsegu OD - DO.
    rezultat pretrage trebaju biti ona pitanja kojima je, u definisanom periodu, najmanje jedan odgovor ocijenjen pozitivno. drugi formalni
    argument tipa float predstavlja prosjecnu ocjenu odgovora na pronadjenom pitanju
    */
    Kolekcija<Pitanje, float> pretraga = (*jasminPolaznik)(ocijenjenOD, ocijenjenDO);
    cout << "U periodu od " << ocijenjenOD << " - " << ocijenjenDO << " ocijenjeno " << pretraga.getTrenutno() << " pitanja." << endl;
    for (size_t i = 0; i < pretraga.getTrenutno(); i++)
        cout << pretraga.getElement1(i) << endl << pretraga.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete lozinkaNijeValidna;

    cin.get();
    system("pause>0");
}