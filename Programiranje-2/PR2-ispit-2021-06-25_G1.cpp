#include <iostream>
#include <iomanip>
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
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

mutex mrPoliceman;

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };                                       // PRVI = 1
ostream& operator<<(ostream& COUT, const eRazred& obj) {
    switch (obj) {
    case PRVI: COUT << "PRVI"; break;
    case DRUGI: COUT << "DRUGI"; break;
    case TRECI: COUT << "TRECI"; break;
    case CETVRTI: COUT << "CETVRTI"; break;
    default:
        break;
    }
    return COUT;
}

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1 = nullptr;
    T2* _elementi2 = nullptr;
    int _trenutno;
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _omoguciDupliranje = omoguciDupliranje;
        _trenutno = 0;
        setElementi();
    }
    Kolekcija(const Kolekcija& obj) {
        _omoguciDupliranje = obj._omoguciDupliranje;
        _trenutno = obj._trenutno;
        setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if(this!=&obj){
            _omoguciDupliranje = obj._omoguciDupliranje;
            _trenutno = obj._trenutno;
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        }
        return *this;
    }
    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() const { return _trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << /*obj.getElement2(i) <<*/ endl;
        return COUT;
    }

    // moje metode

    T1* getElementi1() const { return _elementi1; }
    T2* getElementi2() const { return _elementi2; }

    void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
        delete[]_elementi1;
        delete[]_elementi2;
        _elementi1 = new T1[_trenutno];
        _elementi2 = new T2[_trenutno];
        _trenutno = 0;

        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                AddElement(elementi1[i], elementi2[i]);
            }
        }
    }

    bool postojiDuplikat(const T1& el1) {
        for (int i = 0; i < _trenutno; i++) {
            if (_elementi1[i] == el1)
                return true;
        }
        return false;
    }

    void AddElement(const T1& el1, const T2& el2) {
        if (_omoguciDupliranje == false && postojiDuplikat(el1))
            throw exception("Dupliranje je zabranjeno!");
        expand();
        _elementi1[_trenutno] = el1;
        _elementi2[_trenutno++] = el2;
    }

    void expand() {
        T1* temp1 = new T1[_trenutno + 1];
        T2* temp2 = new T2[_trenutno + 1];
        for (int i = 0; i < _trenutno; i++) {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }
        delete[]_elementi1;
        delete[]_elementi2;
        _elementi1 = temp1;
        _elementi2 = temp2;
    }

    Kolekcija<T1, T2> operator()(int from, int to) {
        if (from < 0 || to >= getTrenutno())
            throw exception("Granice van opsega!");
        Kolekcija<T1, T2> temp;
        for (int i = from; i <= to; i++) {
            temp.AddElement(getElement1(i), getElement2(i));
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
    
    int toInt() const { return *_dan + (*_mjesec) * 30.41 + (*_godina) * 365.24; }

    friend bool operator==(const Datum& d1, const Datum& d2) { return d1.toInt() == d2.toInt(); }
    friend bool operator!=(const Datum& d1, const Datum& d2) { return !(d1 == d2); }
    friend bool operator>(const Datum& d1, const Datum& d2) { return d1.toInt() > d2.toInt(); }
    friend bool operator<(const Datum& d1, const Datum& d2) { return d1.toInt() < d2.toInt(); }
};

class Predmet {
    char* _naziv = nullptr;
    Kolekcija<Datum*, int>* _ocjene = nullptr;
public:
    Predmet(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<Datum*, int>(false);
        if (ocjena > 0)
            AddOcjena(datum, ocjena);
    }
    Predmet(const Predmet& obj) {
        _naziv = GetNizKaraktera(obj.GetNaziv());
        _ocjene = new Kolekcija<Datum*, int>(*obj._ocjene);
    }
    Predmet& operator=(const Predmet& obj) {
        if(this!=&obj){
            _naziv = GetNizKaraktera(obj.GetNaziv());
            _ocjene = new Kolekcija<Datum*, int>(*obj._ocjene);
        }
        return *this;
    }
    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
    }
    const char* GetNaziv() const { return _naziv; }
    Kolekcija<Datum*, int>& GetOcjene() const { return *_ocjene; }

    void AddOcjena(Datum& datum, int ocjena) {
        _ocjene->AddElement(new Datum(datum), ocjena);
    }

    float getProsjecnaOcjena() const {
        if (_ocjene->getTrenutno() == 0)
            return 0.0f;
        float suma = 0.0f;
        for (int i = 0; i < _ocjene->getTrenutno(); i++) {
            suma += _ocjene->getElement2(i);
        }
        return suma / _ocjene->getTrenutno();
    }

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti jednaka 0
    friend ostream& operator<<(ostream& COUT, const Predmet& obj) {
        COUT << "Naziv predmeta: " << obj.GetNaziv() << endl;
        COUT << "Ocjene: \n";
        for (int i = 0; i < obj.GetOcjene().getTrenutno(); i++) {
            COUT << "\t" << *obj.GetOcjene().getElement1(i) << " : " << obj.GetOcjene().getElement2(i) << endl;
        }
        COUT << "Prosjek ocjena: " << obj.getProsjecnaOcjena() << endl;
        return COUT;
    }
    friend bool operator==(const Predmet& p1, const Predmet& p2) {
        if (strcmp(p1.GetNaziv(), p2.GetNaziv()) != 0 || p1.GetOcjene().getTrenutno() != p2.GetOcjene().getTrenutno())
            return false;
        for (int i = 0; i < p1.GetOcjene().getTrenutno(); i++) {
            if (*p1.GetOcjene().getElement1(i) != *p2.GetOcjene().getElement1(i) ||
                p1.GetOcjene().getElement2(i) != p2.GetOcjene().getElement2(i))
                return false;
        }
        return true;
    }
};
class Uspjeh {
    eRazred _razred;
    //char* se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet*, const char*> _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI) {
        _razred = razred;
    }
    Uspjeh(const Uspjeh& obj) {
        _razred = obj._razred;
        _polozeniPredmeti = obj._polozeniPredmeti;
    }
    Uspjeh& operator=(const Uspjeh& obj) {
        if(this!=&obj){
            _razred = obj._razred;
            _polozeniPredmeti = obj._polozeniPredmeti;
        }
        return *this;
    }
    Kolekcija<Predmet*, const char*>& GetPredmeti() { return _polozeniPredmeti; }
    eRazred GetERazred() { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << crt << "Razred: " << obj._razred << "\n";
        for (int i = 0; i < obj._polozeniPredmeti.getTrenutno(); i++) {
            cout << *obj._polozeniPredmeti.getElement1(i) << "\nNapomena: " << obj._polozeniPredmeti.getElement2(i) << endl;
        }
        return COUT;
    }
};

/*
    broj telefona mora biti u formatu
    - znak +
    - pozivni broj drzave (2 ili 3 cifre)
    - pozivni broj operatera (2 cifre) npr. 063, 061, 065 pri cemu je broj 0 opcionalan
    - prvi dio broja (2 ili 3 cifre)
    - razmak ili crtica, oboje opcionalno tj. broj telefona ne mora sadrzavati niti jedno niti drugo
     - drugi dio broja (2 ili 3 cifre)

    ukoliko broj telefona nije u validnom formatu, njegova vrijednost se postavlja na NOT VALID
    */


bool ValidirajBrojTelefona(string brojTelefona) {
    return regex_match(brojTelefona, regex("\\+\\d{2,3}0?\\d{2}\\d{2,3}[\\s\\-]?\\d{2,3}"));
}

class Kandidat {
    char* _imePrezime = nullptr;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh> _uspjeh;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _brojTelefona = ValidirajBrojTelefona(brojTelefona) ? brojTelefona : "NOT VALID";
        for (int i = 0; i < 4; i++) {
            _uspjeh.push_back(Uspjeh((eRazred)(i + 1)));
        }
    }
    Kandidat(const Kandidat& obj) {
        delete[] _imePrezime;
        _imePrezime = GetNizKaraktera(obj.GetImePrezime());
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
        _uspjeh = obj._uspjeh;
    }
    Kandidat& operator=(const Kandidat& obj) {
        if (this != &obj) {
            delete[] _imePrezime;
            _imePrezime = GetNizKaraktera(obj.GetImePrezime());
            _emailAdresa = obj._emailAdresa;
            _brojTelefona = obj._brojTelefona;
            _uspjeh = obj._uspjeh;
        }
        return *this;
    }
    ~Kandidat() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << "Ime i prezime kandidata: " << obj._imePrezime << "\nEmail adresa: " << obj._emailAdresa << "\nBroj telefona: " 
            << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << obj._uspjeh[i];
        return COUT;
    }
    vector<Uspjeh>& GetUspjeh() { return _uspjeh; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    const char* GetImePrezime() const { return _imePrezime; }

    // moje metode

    float getUkupniProsjek() {
        /*if (_uspjeh.size() == 0)
            return 0.0f;*/
        float suma = 0.0f; int brojac = 0;
        for (int i = 0; i < _uspjeh.size(); i++) {
            for (int j = 0; j < _uspjeh[i].GetPredmeti().getTrenutno(); j++) {
                for (int k = 0; k < _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getTrenutno(); k++) {
                    suma += _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getElement2(k);
                    brojac++;
                }
            }
        }
        return brojac == 0 ? 0 : suma / brojac;
    }

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova tipa Predmet) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    Metoda vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    bool AddPredmet(eRazred razred, Predmet& predmet, const char* napomena) {
        if (_uspjeh[razred - 1].GetPredmeti().getTrenutno() >= 5)
            return false;       // najvise 5 predmeta na nivou jednog razreda
        if (predmet.getProsjecnaOcjena() < 2.5)
            return false;       // prosjecna ocjena manja od 2.5
        for (int i = 0; i < _uspjeh[razred - 1].GetPredmeti().getTrenutno(); i++) {
            if (*_uspjeh[razred - 1].GetPredmeti().getElement1(i) == predmet)
                return false;   // ne smije biti isti predmet u jednom razredu
        }

        _uspjeh[razred - 1].GetPredmeti().AddElement(new Predmet(predmet), GetNizKaraktera(napomena));

        thread SlanjeEmaila(&Kandidat::PosaljiEmail, this, /*eRazred(razred - 1)*/ razred, predmet.getProsjecnaOcjena(), getUkupniProsjek());
        SlanjeEmaila.join();
        if (_brojTelefona != "NOT VALID" && predmet.getProsjecnaOcjena() > 4.5) {
            thread SlanjeSMS(&Kandidat::PosaljiSMS, this, predmet.getProsjecnaOcjena(), /*eRazred(razred - 1)*/razred);
            SlanjeSMS.join();
        }

        return true;
    }

    void PosaljiEmail(eRazred razred, float prosjekZaRazred, float ukupniProsjek) {
        mrPoliceman.lock();
        this_thread::sleep_for(chrono::seconds(2));
        cout << "FROM: info@fit.ba\nTO: " << GetEmail() << endl;
        cout << "Postovani " << GetImePrezime() << ", evidentirali ste uspjeh za " << razred << " razred.\n";
        cout << "Dosadasnji prosjek na nivou " << razred << " razreda iznosi "<< setprecision(3) << prosjekZaRazred << "." << endl;
        cout << "Ukupni prosjek u toku skolovanja iznosi " << ukupniProsjek << endl;
        cout << "\nPozdrav.\nFIT Team.\n";
        mrPoliceman.unlock();
    }

    void PosaljiSMS(float uspjeh, eRazred razred) {
        mrPoliceman.lock();
        this_thread::sleep_for(chrono::seconds(1));
        cout << "SMS: Svaka cast za uspjeh " << uspjeh << " u " << razred << " razredu.\n";
        mrPoliceman.unlock();
    }

    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    FROM:info@fit.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    Pozdrav.
    FIT Team.

    ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu". Slanje SMS-a izvrsiti samo u slucaju da je broj telefona validna, u protivnom ispisati poruku „BROJ TELEFONA NIJE VALIDAN“


    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu

    Kolekcija<Predmet, float> operator()(Datum* fromDatum, Datum* toDatum){
        Kolekcija<Predmet, float> temp;
        for (int i = 0; i < _uspjeh.size(); i++) {
            for (int j = 0; j < _uspjeh[i].GetPredmeti().getTrenutno(); j++) {
                for (int k = 0; k < _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getTrenutno(); k++) {
                    if (*_uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getElement1(k) > *fromDatum &&
                        *_uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getElement1(k) < *toDatum) {
                        temp.AddElement(*_uspjeh[i].GetPredmeti().getElement1(j), _uspjeh[i].GetPredmeti().getElement1(j)->getProsjecnaOcjena());
                        break;
                    }
                }
            }
        }
        return temp;
    }
};

//const char* GetOdgovorNaPrvoPitanje() {
//    cout << "Pitanje -> Pojasnite ulogu i nacin koristenja generickog tipa future<>?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
//const char* GetOdgovorNaDrugoPitanje() {
//    cout << "Pitanje -> Ukratko opisite na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}

void main() {

    /*cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();*/

    Datum
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(false);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    /*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu kolekcija1 nalaze na lokacijama 1 - 4
    ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa vrijednostima: 1 1 2 2 3 3 4 4*/
    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
    cout << kolekcija2 << crt;
    try {
        //primjeri u kojima opseg nije validan, te bi funkcija trebala baciti izuzetak
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    //parametri: nazivPredmeta, datum, prva ocjena
    Predmet Matematika("Matematika", datum19062021, 5),
        Fizika("Fizika", datum20062021, 5),
        Hemija("Hemija", datum30062021, 2),
        Engleski("Engleski", datum05072021, 5);

    Matematika.AddOcjena(datum05072021, 3);
    Matematika.AddOcjena(datum05072021, 3);

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti jednaka 0
    cout << Matematika << endl;


    /*
    broj telefona mora biti u formatu
    - znak +
    - pozivni broj drzave (2 ili 3 cifre)
    - pozivni broj operatera (2 cifre) npr. 063, 061, 065 pri cemu je broj 0 opcionalan
    - prvi dio broja (2 ili 3 cifre)
    - razmak ili crtica, oboje opcionalno tj. broj telefona ne mora sadrzavati niti jedno niti drugo
     - drugi dio broja (2 ili 3 cifre)

    ukoliko broj telefona nije u validnom formatu, njegova vrijednost se postavlja na NOT VALID
    */

    if (ValidirajBrojTelefona("+38761222333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+38761222-333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+38761222 333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+387061222 333"))
        cout << "Broj telefona validan" << crt;
    if (!ValidirajBrojTelefona("+38761 222 333"))
        cout << "Broj NIJE telefona validan" << crt;
    if (!ValidirajBrojTelefona("+387 61222 333"))
        cout << "Broj NIJE telefona validan" << crt;


    Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "+38761222333");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "+387061222 333");
    Kandidat brojTelefonaNotValid("Ime Prezime", "korisnik@klix.ba", "+387 61222 333");

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova tipa Predmet) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    Metoda vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
        cout << "Predmet uspjesno dodan!" << crt;
    //Matematiku je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
        cout << "Predmet uspjesno dodan!" << crt;

    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    FROM:info@fit.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    Pozdrav.
    FIT Team.

    ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu". Slanje SMS-a izvrsiti samo u slucaju da je broj telefona validna, u protivnom ispisati poruku „BROJ TELEFONA NIJE VALIDAN“


    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << jasmin << crt;

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    Kolekcija<Predmet, float> jasminUspjeh = jasmin(new Datum(18, 06, 2021), new  Datum(21, 06, 2021));
    cout << jasminUspjeh << crt;

    cin.get();
    system("pause>0");
}