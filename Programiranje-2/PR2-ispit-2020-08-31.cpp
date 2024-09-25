#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <thread>
#include <mutex>

using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
ostream& operator<<(ostream& COUT, const Predmet& obj) {
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
enum Dupliranje { SA_DUPLIKATIMA, BEZ_DUPLIKATA };
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

mutex mrPoliceman;

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[] sadrzaj;
    return temp;
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1 = nullptr;
    T2* _elementi2 = nullptr;
    int* _trenutno = nullptr;
    Dupliranje _dupliranje;
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _dupliranje = dupliranje;
        _trenutno = new int(0);
        setElementi();
    }
    Kolekcija(const Kolekcija& obj) {
        _dupliranje = obj._dupliranje;
        setTrenutno(obj.getTrenutno());
        setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if(this!=&obj){
            _dupliranje = obj._dupliranje;
            setTrenutno(obj.getTrenutno());
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        }
        return *this;
    }
    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
        delete[] _elementi1; _elementi1 = nullptr;
        delete[] _elementi2; _elementi2 = nullptr;
    }
    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // moje metode

    T1* getElementi1() const { return _elementi1; }
    T2* getElementi2() const { return _elementi2; }

    void setTrenutno(int tren) {
        if (_trenutno == nullptr)
            _trenutno = new int;
        *_trenutno = tren;
    }

    void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
        delete[] _elementi1;
        delete[] _elementi2;
        _elementi1 = new T1[getTrenutno()];
        _elementi2 = new T2[getTrenutno()];
        setTrenutno(0);

        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                AddElement(elementi1[i], elementi2[i]);
            }
        }
    }

    bool sadrziDuplikat(const T1& el1) {
        for (int i = 0; i < getTrenutno(); i++) {
            if (_elementi1[i] == el1)
                return true;
        }
        return false;
    }

    void AddElement(const T1& el1, const T2& el2) {
        if (_dupliranje == BEZ_DUPLIKATA && sadrziDuplikat(el1))
            throw exception("Dupliranje nije dozvoljeno!");
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

    Kolekcija<T1, T2> operator[](const T1& el1) {
        Kolekcija<T1, T2> temp;
        for (int i = 0; i < getTrenutno(); i++) {
            if (_elementi1[i] == el1)
                temp.AddElement(_elementi1[i], _elementi2[i]);
        }
        return temp;
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
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if(this!=&obj){
            _dan = new int(*obj._dan);
            _mjesec = new int(*obj._mjesec);
            _godina = new int(*obj._godina);
        }
        return *this;
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
    int toInt() const { return (*_dan) + (*_mjesec) * 30.41 + (*_godina) * 365.24; }
};

bool operator==(const Datum& d1, const Datum& d2) { return d1.toInt() == d2.toInt(); }
bool operator!=(const Datum& d1, const Datum& d2) { return !(d1 == d2); }
bool operator<(const Datum& d1, const Datum& d2) { return d1.toInt() < d2.toInt(); }
bool operator>(const Datum& d1, const Datum& d2) { return d1.toInt() > d2.toInt(); }

int getDateDiff(const Datum& d1, const Datum& d2) {
    return abs(d1.toInt() - d2.toInt());
}

class Pitanje {
    char* _sadrzaj = nullptr;
    //int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
    Kolekcija<int, Datum*> _ocjeneRjesenja;
public:
    Pitanje(const char* sadrzaj = "") {
        _sadrzaj = GetNizKaraktera(sadrzaj);
    }
    Pitanje(const Pitanje& obj) {
        //delete[] _sadrzaj;
        _sadrzaj = GetNizKaraktera(obj.GetSadrzaj());
        _ocjeneRjesenja = obj.constGetOcjene();
    }
    Pitanje& operator=(const Pitanje& obj) {
        if(this!=&obj){
            //delete[] _sadrzaj;
            _sadrzaj = GetNizKaraktera(obj.GetSadrzaj());
            _ocjeneRjesenja = obj.constGetOcjene();
        }
        return *this;
    }
    ~Pitanje() {
        delete[] _sadrzaj; _sadrzaj = nullptr;
    }
    const char* GetSadrzaj() const { return _sadrzaj == nullptr ? "" : _sadrzaj; }
    Kolekcija<int, Datum*>& GetOcjene() { return _ocjeneRjesenja; }
    Kolekcija<int, Datum*> constGetOcjene() const { return _ocjeneRjesenja; }

    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */

    bool AddOcjena(int ocjena, Datum& datum) {
        if (_ocjeneRjesenja.getTrenutno() > 0) {
            if (getDateDiff(*_ocjeneRjesenja.getElement2(_ocjeneRjesenja.getTrenutno() - 1), datum) < 3)
                return false;   // zadnji
            for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); i++) {
                if (datum < *_ocjeneRjesenja.getElement2(i))
                    return false;
            }
        }
        _ocjeneRjesenja.AddElement(ocjena, new Datum(datum));
        return true;
    }
    
    float getProsjecnaOcjenaZaPitanje() const {
        if (_ocjeneRjesenja.getTrenutno() == 0)
            return 0.0f;
        float suma = 0.0f;
        for (int i = 0; i < _ocjeneRjesenja.getTrenutno(); i++) {
            suma += _ocjeneRjesenja.getElement1(i);
        }
        return suma / _ocjeneRjesenja.getTrenutno();
    }

    // ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
     // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    friend ostream& operator<<(ostream& COUT, const Pitanje& obj) {
        COUT << "Sadrzaj pitanja: " << obj.GetSadrzaj() << endl;
        cout << "Ocjene: " << endl;
        for (int i = 0; i < obj.constGetOcjene().getTrenutno(); i++) {
            COUT << "\t" << obj.constGetOcjene().getElement1(i) << " : " << *obj.constGetOcjene().getElement2(i) << endl;
        }
        COUT << "Prosjecna ocjena: " << obj.getProsjecnaOcjenaZaPitanje() << endl;
        return COUT;
    }
};

bool operator==(const Pitanje& p1, const Pitanje& p2) {
    /*if (strcmp(p1.GetSadrzaj(), p2.GetSadrzaj()) != 0 || p1.constGetOcjene().getTrenutno() != p2.constGetOcjene().getTrenutno())
        return false;

    for (int i = 0; i < p1.constGetOcjene().getTrenutno(); i++) {
        if (p1.constGetOcjene().getElement1(i) != p1.constGetOcjene().getElement1(i) ||
            *p1.constGetOcjene().getElement2(i) != *p2.constGetOcjene().getElement2(i))
            return false;
    }

    return true;*/
    return strcmp(p1.GetSadrzaj(), p2.GetSadrzaj()) == 0;
}

/*
    za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi 6 ili 7 znakova postujuci sljedeca pravila:
    -   pocinje sa znak * (zvjezdica) ili _ (donja crtica), nakon cega slijedi
    -   broj, nakon cega slijedi
    -   malo slovo, nakon cega slijedi
    -   razmak koji NIJE OBAVEZAN, nakon cega slijedi
    -   veliko slovo, nakon cega slijedi
    -   broj, nakon cega slijedi
    -   malo slovo.
    za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    */



class Ispit {
    Predmet _predmet;
    //string se odnosi na napomenu/zapazanje nastavnika
    Kolekcija<Pitanje, string> _pitanjaOdgovori;
public:
    Ispit(Predmet predmet = UIT) {
        _predmet = predmet;
    }
    Ispit(const Ispit& obj) {
        _predmet = obj._predmet;
        _pitanjaOdgovori = obj._pitanjaOdgovori;
    }
    Ispit& operator=(const Ispit& obj) {
        if(this!=&obj){
            _predmet = obj._predmet;
            _pitanjaOdgovori = obj._pitanjaOdgovori;
        }
        return *this;
    }

    Kolekcija<Pitanje, string>& GetPitanjaOdgovore() { return _pitanjaOdgovori; }
    Predmet GetPredmet() { return _predmet; }
    friend ostream& operator<< (ostream& COUT, const Ispit& obj) {
        COUT << obj._predmet << endl;
        for (size_t i = 0; i < obj._pitanjaOdgovori.getTrenutno(); i++)
            COUT << obj._pitanjaOdgovori << endl;
        return COUT;
    }
};


bool ValidirajLozinku(string lozinka) {
return regex_match(lozinka, regex("[\\*_]\\d[a-z]\\s?[A-Z]\\d[a-z]"));
}

class Korisnik {
    char* _imePrezime = nullptr;
    string _emailAdresa;
    string _lozinka;
public:
    Korisnik(const char* imePrezime, string emailAdresa, string lozinka) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
    }
    Korisnik(const Korisnik& obj) {
        //delete[] _imePrezime;
        _imePrezime = GetNizKaraktera(obj.GetImePrezime());
        _emailAdresa = obj._emailAdresa;
        _lozinka = obj._lozinka;
    }
    Korisnik& operator=(const Korisnik& obj) {
        if(this!=&obj){
            //delete[] _imePrezime;
            _imePrezime = GetNizKaraktera(obj.GetImePrezime());
            _emailAdresa = obj._emailAdresa;
            _lozinka = obj._lozinka;
        }
        return *this;
    }
    virtual ~Korisnik() { 
        cout << "KORISNIK :: DESTRUKTOR" << endl;
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    string GetEmail() { return _emailAdresa; }
    string GetLozinka() { return _lozinka; }
    const char* GetImePrezime() const { return _imePrezime; }
    virtual void Info() = 0;
};

class Kandidat : public Korisnik {
    vector<Ispit*> _polozeniPredmeti;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka) : Korisnik(imePrezime, emailAdresa, lozinka) {
        for (int i = 0; i < 6; i++) {
            _polozeniPredmeti.push_back(new Ispit((Predmet)i));
        }
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
        cout << "KANDIDAT :: DESTRUKTOR" << endl;
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i];
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj.GetImePrezime() << " " << obj.GetEmail() << " " << obj.GetLozinka() << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++)
            COUT << *obj._polozeniPredmeti[i];
        return COUT;
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }

    void Info() {}

    float GetUkupniProsjek() {
        if (_polozeniPredmeti.size() == 0)
            return 0.0f;
        float suma = 0.0f; int brojac = 0;
        for (int i = 0; i < _polozeniPredmeti.size(); i++) {
            for (int j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().getTrenutno(); j++) {
                suma += _polozeniPredmeti[i]->GetPitanjaOdgovore().getElement1(j).getProsjecnaOcjenaZaPitanje();
                brojac++;
            }
        }
        return (brojac == 0) ? 0 : suma / brojac;
    }

    

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za visi predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija, "nedostaje operator delete"))
      //  cout << "Pitanje uspjesno dodano!" << crt;

    bool AddPitanje(Predmet predmet, Pitanje& pitanje, string komentar = "") {
        for (int i = 0; i < _polozeniPredmeti[predmet]->GetPitanjaOdgovore().getTrenutno(); i++) {
            if (_polozeniPredmeti[predmet]->GetPitanjaOdgovore().getElement1(i) == pitanje)
                return false;   // ne smiju bit ista pitanja
        }
        if (predmet != PRI) {
            if (_polozeniPredmeti[predmet - 1]->GetPitanjaOdgovore().getTrenutno() < 3)
                return false;   // manje od 3 pitanja
            float prosjek = 0.0f;
            for (int i = 0; i < _polozeniPredmeti[predmet - 1]->GetPitanjaOdgovore().getTrenutno(); i++) {
                prosjek += _polozeniPredmeti[predmet - 1]->GetPitanjaOdgovore().getElement1(i).getProsjecnaOcjenaZaPitanje();
            }
            prosjek /= _polozeniPredmeti[predmet - 1]->GetPitanjaOdgovore().getTrenutno();

            if (prosjek < 3.5)
                return false;   // manji prosjek od 3.5
        }

        _polozeniPredmeti[predmet]->GetPitanjaOdgovore().AddElement(pitanje, komentar);
        
        int ocjena = 0;
        if (pitanje.GetOcjene().getTrenutno() != 0) {
            ocjena = pitanje.GetOcjene().getElement1(pitanje.GetOcjene().getTrenutno() - 1);
        }
        float prosjekPitanje = pitanje.getProsjecnaOcjenaZaPitanje();
        string sadrzajPitanja = GetNizKaraktera(pitanje.GetSadrzaj());
        
        thread SlanjeEmaila(&Kandidat::PosaljiEmail, this, ocjena, sadrzajPitanja, prosjekPitanje, GetUkupniProsjek());
        SlanjeEmaila.join();

        return true;
    }

    void PosaljiEmail(int ocjena, string sadrzajPitanja, float prosjekPitanje, float prosjekSve) {
        mrPoliceman.lock();
        this_thread::sleep_for(chrono::seconds(2));
        cout << "FROM: info@kursevi.ba" << endl;
        cout << "TO: " << GetEmail() << endl;
        cout << "Postovani " << GetImePrezime() << ", evindetirana vam je ocjena " << ocjena << " za odgovor na pitanje " << sadrzajPitanja << ".\n";
        cout << "Dosadasnji uspjeh (prosjek ocjena) za pitanje iznosi " << prosjekPitanje << ", a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi " <<
            prosjekSve << ".\nPozdrav.\n.EDUTeam.\n";
        mrPoliceman.unlock();
    }

    /*nakon evidentiranja ocjene na bilo kojem odgovoru, kandidatu se salje email sa porukom:
    FROM:info@kursevi.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.
    EDUTeam.
    slanje email poruka implemenitrati koristeci zasebne thread-ove.
    */

    
    int operator()(string napomena) {
        int brojac = 0;
        for (int i = 0; i < _polozeniPredmeti.size(); i++) {
            for (int j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().getTrenutno(); j++) {
                if (_polozeniPredmeti[i]->GetPitanjaOdgovore().getElement2(j).find(napomena) != string::npos)
                    brojac++;
            }
        }
        
        return brojac;
    }

};

//const char* GetOdgovorNaPrvoPitanje() {
//    cout << "Pitanje -> Pojasnite na koji nacin tip nasljedjivanja (javno, zasticeno, privatno) utjece na dostupnost atributa bazne klase unutar izvedene klase?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
//const char* GetOdgovorNaDrugoPitanje() {
//    cout << "Pitanje -> Ukratko pojasnite primjenu funkcija seekg i tellg?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
void main() {

    /*cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();*/

    Datum   datum19062020(19, 6, 2020),
        datum20062020(20, 6, 2020),
        datum30062020(30, 6, 2020),
        datum05072020(5, 7, 2020);

    int kolekcijaTestSize = 10;

    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i < kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1 << endl;

    try {
        /*ukoliko dupliranje vrijednosti nije dozvoljeno (BEZ_DUPLIKATA)
        metoda AddElement baca izuzetak u slucaju da se pokusa dodati par sa vrijednostima
        identicnim postojecem paru unutar kolekcije */
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;

    /*na osnovu vrijednosti tip T1 (u primjeru vrijednost 1) pronalazi i vraca iz kolekcije sve parove
    koji kao vrijednost T1 imaju proslijedjenu vrijednost*/
    cout << kolekcija1[1] << crt;
    /* npr. ako unutar kolekcije postoje parovi:
    0 0
    1 9
    1 1
    2 2
    3 3
    ispis dobijenih/vracenih vrijednosti ce biti sljedeci:
    1 9
    1 1
    */

    Pitanje sortiranjeNiza("Navedite algoritme za sortiranje clanova niza."),
        dinamickaMemorija("Navedite pristupe za upravljanje dinamickom memorijom."),
        visenitnoProgramiranje("Na koji se sve nacin moze koristiti veci broj niti tokom izvrsenja programa."),
        regex("Navedite par primjera regex validacije podataka.");

    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    if (sortiranjeNiza.AddOcjena(1, datum19062020))
        cout << "Ocjena evidentirana!" << endl;
    if (!sortiranjeNiza.AddOcjena(5, datum20062020))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (sortiranjeNiza.AddOcjena(5, datum30062020))
        cout << "Ocjena evidentirana!" << endl;

    // ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
     // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    cout << sortiranjeNiza << endl;

    if (ValidirajLozinku("*2gT2x"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*7aT2x"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("_6gU9z"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*3aB1y"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*1a T2l"))
        cout << "Lozinka validna" << endl;
    if (!ValidirajLozinku("-1a T2l"))
        cout << "Lozinka NIJE validna" << endl;

    /*
    za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi 6 ili 7 znakova postujuci sljedeca pravila:
    -   pocinje sa znak * (zvjezdica) ili _ (donja crtica), nakon cega slijedi
    -   broj, nakon cega slijedi
    -   malo slovo, nakon cega slijedi
    -   razmak koji NIJE OBAVEZAN, nakon cega slijedi
    -   veliko slovo, nakon cega slijedi
    -   broj, nakon cega slijedi
    -   malo slovo.
    za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    */

    Korisnik* jasmin = new Kandidat("Jasmin Azemovic", "jasmin@kursevi.ba", "*2gT2x");
    Korisnik* adel = new Kandidat("Adel Handzic", "adel@edu.kursevi.ba", "_6gU9z");
    Korisnik* lozinkaNijeValidna = new Kandidat("John Doe", "john.doe@google.com", "johndoe");

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za visi predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //ukoliko je potrebno, doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    Kandidat* jasminPolaznik = dynamic_cast<Kandidat*>(jasmin);

    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija, "nedostaje operator delete"))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati visenitnoProgramiranje jer ne postoje evidentirana 3 pitanja za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRII, visenitnoProgramiranje))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, visenitnoProgramiranje))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, regex, "unutar posljednjeg dijela nedostaje opis glavnih operatora"))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati sortiranjeNiza jer je vec dodana za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;

        //ispisuje sve dostupne podatke o kandidatu
        cout << *jasminPolaznik << crt;

        //vraca broj ponavljanja odredjene rijeci unutar napomena nastalih tokom polaganja ispita.
        int brojPonavljanja = (*jasminPolaznik)("nedostaje");
        cout << "Rijec nedostaje se ponavlja " << brojPonavljanja << " puta." << endl;

    }
    /*nakon evidentiranja ocjene na bilo kojem odgovoru, kandidatu se salje email sa porukom:
    FROM:info@kursevi.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.
    EDUTeam.
    slanje email poruka implemenitrati koristeci zasebne thread-ove.
    */
    
    delete jasmin;
    delete adel;
    delete lozinkaNijeValidna;

    cin.get();
    system("pause>0");
    
}