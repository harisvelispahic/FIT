#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<mutex>
#include<thread>

using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO RE\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE!\n"
"7. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"-------------------------------------------------------------------------------\n";

mutex mrPoliceman;

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
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

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[]sadrzaj;
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
    }
    Kolekcija(const Kolekcija& obj) {
        _omoguciDupliranje = obj._omoguciDupliranje;
        _trenutno = obj._trenutno;
        setElementi(obj._trenutno, obj.getElementi1(), obj.getElementi2());
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj)
        {
            _omoguciDupliranje = obj._omoguciDupliranje;
            _trenutno = obj._trenutno;
            setElementi(obj._trenutno, obj.getElementi1(), obj.getElementi2());
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
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // moje metode

    T1* getElementi1() const { return _elementi1; }
    T2* getElementi2() const { return _elementi2; }

    void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = new T1[_trenutno];
        _elementi2 = new T2[_trenutno];

        _trenutno = 0;

        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                AddElement(elementi1[i], elementi2[i]);
            }
        }
    }

    void AddElement(const T1& el1, const T2& el2) {
        if (_omoguciDupliranje == false && postojiDuplikat(el1, el2))
            throw exception("Dupliranje nije dozvoljeno!");
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

        delete[] _elementi1;
        delete[] _elementi2;

        _elementi1 = temp1;
        _elementi2 = temp2;
    }

    bool postojiDuplikat(const T1& el1, const T2& el2) {
        for (int i = 0; i < _trenutno; i++) {
            if (_elementi1[i] == el1 && _elementi2[i] == el2)
                return true;
        }
        return false;
    }

    Kolekcija<T1, T2> operator()(int from, int to) {
        Kolekcija<T1, T2> temp;
        if (from < 0 || from >= _trenutno || to < 0 || to >= _trenutno)
            throw exception("Granice van opsega!");
        for (int i = from; i <= to; i++) {
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
        delete _dan;
        delete _mjesec;
        delete _godina;
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj)
        {
            delete _dan;
            delete _mjesec;
            delete _godina;
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
        COUT << *obj._dan << "/" << *obj._mjesec << "/" << *obj._godina;
        return COUT;
    }

    int toint() const { return *_dan + (*_mjesec) * 30.41 + (*_godina) * 365.24; }

    friend bool operator==(const Datum& d1, const Datum& d2) { return d1.toint() == d2.toint(); }
    friend bool operator!=(const Datum& d1, const Datum& d2) { return !(d1 == d2); }
    friend bool operator>(const Datum& d1, const Datum& d2) { return d1.toint() > d2.toint(); }
    friend bool operator<(const Datum& d1, const Datum& d2) { return d1.toint() < d2.toint(); }

    

};

class Predmet {
    char* _naziv = nullptr;
    //int se odnosi na ocjenu u opsegu od 1 – 5, a datum na momenat postizanja ocjene
    Kolekcija<int, Datum> _ocjene;
public:
    Predmet(const char* naziv = "", int ocjena = 0, Datum datum = Datum()) {
        _naziv = GetNizKaraktera(naziv);
        if (ocjena > 0)
            _ocjene.AddElement(ocjena, datum);
    }
    Predmet(const Predmet& obj) {
        delete[] _naziv;
        _naziv = GetNizKaraktera(obj._naziv);
        _ocjene = obj._ocjene;
    }
    Predmet& operator=(const Predmet& obj) {
        if (this != &obj)
        {
            delete[] _naziv;
            _naziv = GetNizKaraktera(obj._naziv);
            _ocjene = obj._ocjene;
        }
        return *this;
    }
    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
    }
    void AddOcjena(int ocjena, Datum& datum) {
        _ocjene.AddElement(ocjena, datum);
    }
    const char* GetNaziv() const { return _naziv; }
    Kolekcija<int, Datum>& GetOcjene() { return _ocjene; }

    // moje metode

    float getProsjecnaOcjenaZaPredmet() const {
        if (_ocjene.getTrenutno() == 0)
            return 0.0f;
        float suma = 0.0f;
        for (int i = 0; i < _ocjene.getTrenutno(); i++) {
            suma += _ocjene.getElement1(i);
        }
        return suma / _ocjene.getTrenutno();
    }

    friend ostream& operator<<(ostream& COUT, const Predmet& obj) {
        COUT << "Naziv: " << obj.GetNaziv() << "\nOcjene:\n";
        for (int i = 0; i < obj._ocjene.getTrenutno(); i++) {
            COUT << "\t" << obj._ocjene.getElement1(i) << " : " << obj._ocjene.getElement2(i) << endl;
        }
        COUT << "Prosjecna ocjena: " << obj.getProsjecnaOcjenaZaPredmet() << endl;
        return COUT;
    }

    friend bool operator==(const Predmet& p1, const Predmet& p2) {
        char* _naziv = nullptr;
        //int se odnosi na ocjenu u opsegu od 1 – 5, a datum na momenat postizanja ocjene
        Kolekcija<int, Datum> _ocjene;

        if (strcmp(p1.GetNaziv(), p2.GetNaziv()) != 0 || p1._ocjene.getTrenutno() != p2._ocjene.getTrenutno())
            return false;
        for (int i = 0; i < p1._ocjene.getTrenutno(); i++) {
            if (p1._ocjene.getElement1(i) != p2._ocjene.getElement1(i) ||
                p1._ocjene.getElement2(i) != p2._ocjene.getElement2(i))
                return false;
        }
        return true;
    }

    float getProsjecnaRazlikaDana() const {
        if (_ocjene.getTrenutno() == 0)
            return 0.0f;
        float suma = 0.0f;
        for (int i = 0; i < _ocjene.getTrenutno() - 1; i++) {
            suma += abs(_ocjene.getElement2(i).toint() - _ocjene.getElement2(i + 1).toint());
        }
        return suma / _ocjene.getTrenutno();
    }

};
class Uspjeh {
    eRazred _razred;
    //string se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet, string>* _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI) {
        _razred = razred;
        _polozeniPredmeti = new Kolekcija<Predmet, string>();
    }
    Uspjeh(const Uspjeh& obj) {
        _razred = obj._razred;
        _polozeniPredmeti = new Kolekcija<Predmet, string>(*obj._polozeniPredmeti);
    }
    Uspjeh& operator=(const Uspjeh& obj) {
        if (this != &obj)
        {
            _razred = obj._razred;
            _polozeniPredmeti = new Kolekcija<Predmet, string>(*obj._polozeniPredmeti);
        }
        return *this;
    }
    ~Uspjeh() { delete _polozeniPredmeti; _polozeniPredmeti = nullptr; }

    Kolekcija<Predmet, string>* GetPredmeti() { return _polozeniPredmeti; }
    Kolekcija<Predmet, string>& refGetPredmeti() const { return *_polozeniPredmeti; }
    eRazred GetERazred() { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << "Razred: " << obj._razred << "\nPolozeni predmeti:\n" << *obj._polozeniPredmeti << endl;
        return COUT;
    }
};


/*
    email adresa mora biti u formatu text.text (sa ili bez tacke),
    dok domena moze biti fit.ba ili edu.fit.ba
    nakon institucije (fit ili edu.fit), osim drzavne (.ba), dozvoljene su domene .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase Kandidat, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.fit.ba
*/

bool ValidirajEmail(string email) {
    return regex_match(email, regex("[A-Za-z]+\\.?[A-Za-z]+@(edu\\.)?fit\\.(ba|com|org)"));
}

class Kandidat {
    char* _imePrezime = nullptr;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh> _uspjeh;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = ValidirajEmail(emailAdresa) ? emailAdresa : "notSet@edu.fit.ba";
        _brojTelefona = brojTelefona;
        for (int i = 0; i < 4; i++) {
            _uspjeh.push_back(Uspjeh((eRazred)i));
        }
    }
    Kandidat(const Kandidat& obj) {
        delete[] _imePrezime;
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
        _uspjeh = obj._uspjeh;
    }
    Kandidat& operator=(const Kandidat& obj) {
        if (this != &obj)
        {
            delete[] _imePrezime;
            _imePrezime = GetNizKaraktera(obj._imePrezime);
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
        COUT << "Ime i prezime: " << obj._imePrezime << "\nEmail adresa: " << obj._emailAdresa << "\nBroj telefona: " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << obj._uspjeh[i];
        return COUT;
    }
    vector<Uspjeh>& GetUspjeh() { return _uspjeh; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }

    // moje metode

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred isl.).
    Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    float getUkupniProsjek() const {
        float suma = 0.0f;
        int brojac = 0;
        for (int i = 0; i < _uspjeh.size(); i++) {
            for (int j = 0; j < _uspjeh[i].refGetPredmeti().getTrenutno(); j++) {
                /*suma += _uspjeh[i].refGetPredmeti().getElement1(j).getProsjecnaOcjenaZaPredmet();
                brojac++;*/
                for (int k = 0; k < _uspjeh[i].refGetPredmeti().getElement1(j).GetOcjene().getTrenutno(); k++) {
                    suma += _uspjeh[i].refGetPredmeti().getElement1(j).GetOcjene().getElement1(k);
                    brojac++;
                }
            }
        }
        return brojac == 0 ? 0.0f : suma / brojac;
    }


    bool AddPredmet(eRazred razred, Predmet& predmet, string napomena) {
        for (int i = 0; i < _uspjeh[razred].GetPredmeti()->getTrenutno(); i++) {
            if (_uspjeh[razred].GetPredmeti()->getElement1(i) == predmet)
                return false;   // ne smiju se dodavati isti predmeti
        }
        if (predmet.getProsjecnaOcjenaZaPredmet() < 2.5)
            return false;       // ne smiju se dodavati predmeti sa prosjecnom ocjenom manjom od 2.5

        if (_uspjeh[razred].GetPredmeti()->getTrenutno() >= 5)
            return false;       // ne smije biti vise od 5 predmeta u razredu


        _uspjeh[razred].GetPredmeti()->AddElement(predmet, napomena);

        thread SlanjeEmaila(&Kandidat::PosaljiEmail, this, razred, predmet.getProsjecnaOcjenaZaPredmet(), getUkupniProsjek());
        SlanjeEmaila.join();

        return true;
    }

    void PosaljiEmail(eRazred razred, float prosjek, float ukupniProsjek) {
        mrPoliceman.lock();
        //this_thread::sleep_for(chrono::seconds(3));
        cout << crt << "FROM: info@fit.ba\nTO: " << GetEmail() << "\nPostovani " << GetImePrezime() << ", evidentirali ste uspjeh za " << razred << " razred.\n";
        cout << "Dosadasnjii uspjeh na nivou " << razred << " razreda iznosi " << prosjek << ", a ukupni uspjeh u toku skolovanja iznosi " << ukupniProsjek << ".\nPozdrav\nFIT Team." << crt;
        mrPoliceman.unlock();
    }

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu

    Kolekcija<Predmet, float> operator()(const Datum& fromDatum, const Datum& toDatum) {
        Kolekcija<Predmet, float> temp;
        for (int i = 0; i < _uspjeh.size(); i++) {
            for (int j = 0; j < _uspjeh[i].refGetPredmeti().getTrenutno(); j++) {
                for (int k = 0; k < _uspjeh[i].refGetPredmeti().getElement1(j).GetOcjene().getTrenutno(); k++) {
                    Datum trenutniDatum = _uspjeh[i].refGetPredmeti().getElement1(j).GetOcjene().getElement2(k);
                    if (trenutniDatum > fromDatum && trenutniDatum < toDatum) {
                        temp.AddElement(_uspjeh[i].refGetPredmeti().getElement1(j), _uspjeh[i].refGetPredmeti().getElement1(j).getProsjecnaRazlikaDana());
                    }
                }
            }
        }
        return temp;
    }

    Uspjeh* operator[](eRazred razred) {
        return &_uspjeh[razred];
    }

};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Na sta se odnosi pojam reprezentacije tipa?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    /*cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();*/

    Datum temp,
        datum19062019(19, 6, 2019),
        datum20062019(20, 6, 2019),
        datum30062019(30, 6, 2019),
        datum05072019(5, 7, 2019);

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

    //parametri: nazivPredmeta, prva ocjena, datum
    Predmet Matematika("Matematika", 5, datum19062019),
        Fizika("Fizika", 5, datum20062019),
        Hemija("Hemija", 2, datum30062019),
        Engleski("Engleski", 5, datum05072019);

    Matematika.AddOcjena(3, datum05072019);
    Matematika.AddOcjena(5, datum05072019);

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti 0
    cout << Matematika << endl;

    if (ValidirajEmail("text.text@edu.fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@edu.fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@fit.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@edu.fit.org"))
        cout << "Email validan" << crt;

    /*
    email adresa mora biti u formatu text.text (sa ili bez tacke),
    dok domena moze biti fit.ba ili edu.fit.ba
    nakon institucije (fit ili edu.fit), osim drzavne (.ba), dozvoljene su domene .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase Kandidat, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.fit.ba
    */

    Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "033 281 172");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
    Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred isl.).
    Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
        cout << "Predmet uspjesno dodan!1" << crt;
    if (!jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2"))
        cout << "Predmet nije uspjesno dodan!2" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
        cout << "Predmet uspjesno dodan!3" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
        cout << "Predmet uspjesno dodan!4" << crt;
    //ne treba dodati Matematiku jer je vec dodana u prvom razredu
    if (!jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
        cout << "Predmet nije uspjesno dodan!5" << crt;

    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    FROM:info@fit.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    Pozdrav.
    FIT Team.
    ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << jasmin << crt;

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    Kolekcija<Predmet, float> jasminUspjeh = jasmin(Datum(18, 06, 2019), Datum(21, 06, 2019));
    cout << jasminUspjeh << crt;

    Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
    if (uspjeh_Irazred != nullptr)
        cout << *uspjeh_Irazred << crt;

    cin.get();
    system("pause>0");
}