#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <regex>
#include <mutex>
#include <thread>
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
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
ostream& operator<<(ostream& COUT, const Pojas& obj) {
    switch (obj) {
    case BIJELI: COUT << "BIJELI"; break;
    case ZUTI: COUT << "ZUTI"; break;
    case NARANDZASTI: COUT << "NARANDZASTI"; break;
    case ZELENI: COUT << "ZELENI"; break;
    case PLAVI: COUT << "PLAVI"; break;
    case SMEDJI: COUT << "SMEDJI"; break;
    case CRNI: COUT << "CRNI"; break;
    default:
        break;
    }
    return COUT;
}
enum Dupliranje { BEZ_DUPLIKATA, SA_DUPLIKATIMA };

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}
template<class T1, class T2, int max = 15>
class Kolekcija {
    T1 _elementi1[max];
    T2 _elementi2[max];
    int* _trenutno = nullptr;
    Dupliranje _dupliranje;
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int(0);
        _dupliranje = dupliranje;
    }
    Kolekcija(const Kolekcija& obj) {
        setTrenutno(obj.getTrenutno());
        _dupliranje = obj._dupliranje;
        setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj)
        {
            setTrenutno(obj.getTrenutno());
            _dupliranje = obj._dupliranje;
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        }
        return *this;
    }
    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
    }

    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    T1* getElementi1() const { return (T1*)_elementi1; }
    T2* getElementi2() const { return (T2*)_elementi2; }

    void setTrenutno(int tren) {
        if (_trenutno == nullptr)
            _trenutno = new int;
        *_trenutno = tren;
    }

    void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
        setTrenutno(0);
        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                _elementi1[i] = elementi1[i];
                _elementi2[i] = elementi2[i];
            }
        }
    }

    bool postojiDuplikat(const T1& el1) {
        for (int i = 0; i < getTrenutno(); i++) {
            if (_elementi1[i] == el1)
                return true;
        }
        return false;
    }

    void AddElement(const T1& el1, const T2& el2) {
        if (_dupliranje == BEZ_DUPLIKATA && postojiDuplikat(el1))
            throw exception("Dupliranje je zabranjeno!");
        if (getTrenutno() >= max)
            throw exception("Prekoracen maximum!");
        _elementi1[getTrenutno()] = el1;
        _elementi2[getTrenutno()] = el2;
        setTrenutno(getTrenutno() + 1);
    }

    Kolekcija<T1, T2> operator()(int from, int to) {
        if (from < 0 || to >= getTrenutno())
            throw exception("Granice van opsega!");
        Kolekcija<T1, T2> temp;
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
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj)
        {
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
};

bool operator==(const Datum& d1, const Datum& d2) { return d1.toInt() == d2.toInt(); }
bool operator!=(const Datum& d1, const Datum& d2) { return !(d1 == d2); }
bool operator>(const Datum& d1, const Datum& d2) { return d1.toInt() > d2.toInt(); }
bool operator<(const Datum& d1, const Datum& d2) { return d1.toInt() < d2.toInt(); }

class Tehnika {
    char* _naziv = nullptr;
    //int se odnosi na ocjenu u opsegu od 1 - 5, a datum na momenat postizanja ocjene
    Kolekcija<Datum, int>* _ocjene = nullptr;

public:
    Tehnika(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<Datum, int>;
        if (ocjena > 0)
            AddOcjena(&datum, ocjena);
    }
    Tehnika(const Tehnika& obj) {
        delete[] _naziv;
        _naziv = GetNizKaraktera(obj.GetNaziv());
        _ocjene = new Kolekcija<Datum, int>(obj.GetOcjene());
    }
    Tehnika& operator=(const Tehnika& obj) {
        if (this != &obj)
        {
            delete[] _naziv;
            _naziv = GetNizKaraktera(obj.GetNaziv());
            _ocjene = new Kolekcija<Datum, int>(obj.GetOcjene());
        }
        return *this;
    }
    ~Tehnika() {
        delete[] _naziv; _naziv = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
   const char* GetNaziv() const { return _naziv; }
    Kolekcija<Datum, int>& GetOcjene() const { return *_ocjene; }

    void AddOcjena(Datum* datum, int ocjena) {
        _ocjene->AddElement(*datum, ocjena);
    }

    float getProsjecnaOcjenaZaTehniku() const {
        if (_ocjene->getTrenutno() == 0)
            return 0.0f;
        float suma = 0.0f;
        for (int i = 0; i < _ocjene->getTrenutno(); i++) {
            suma += _ocjene->getElement2(i);
        }
        return suma / _ocjene->getTrenutno();
    }

    // ispisuje: naziv tehnike, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu za tu tehniku
    // ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0

    friend ostream& operator<< (ostream& COUT, const Tehnika& obj) {
        COUT << "Naziv tehnike: " << obj.GetNaziv() << endl;
        COUT << "Ocjene: " << endl;
        for (int i = 0; i < obj._ocjene->getTrenutno(); i++) {
            COUT << "\t" << obj._ocjene->getElement1(i) << " : " << obj._ocjene->getElement2(i) << endl;
        }
        COUT << "Prosjecna ocjena: " << obj.getProsjecnaOcjenaZaTehniku() << endl;
        return COUT;
    }
};

bool operator==(const Tehnika& t1, const Tehnika& t2) {
    if (strcmp(t1.GetNaziv(), t2.GetNaziv()) != 0 || t1.GetOcjene().getTrenutno() != t2.GetOcjene().getTrenutno())
        return false;
    for (int i = 0; i < t1.GetOcjene().getTrenutno(); i++) {
        if (t1.GetOcjene().getElement1(i) != t2.GetOcjene().getElement1(i) ||
            t1.GetOcjene().getElement2(i) != t2.GetOcjene().getElement2(i))
            return false;
    }
    return true;
}


class Polaganje {
    Pojas _pojas;
    //string se odnosi na napomenu o polozenoj tehnici
    Kolekcija<Tehnika*, string> _polozeneTehnike;
public:
    Polaganje(Pojas pojas = BIJELI) {
        _pojas = pojas;
    }
    Polaganje(const Polaganje& obj) {
        _pojas = obj._pojas;
        _polozeneTehnike = obj._polozeneTehnike;
    }
    Polaganje& operator=(const Polaganje& obj) {
        if (this != &obj)
        {
            _pojas = obj._pojas;
            _polozeneTehnike = obj._polozeneTehnike;
        }
        return *this;
    }
    Kolekcija<Tehnika*, string>& GetTehnike() { return _polozeneTehnike; }
    Pojas GetPojas() { return _pojas; }
    friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
        COUT << "Pojas: " << obj._pojas << endl;
        COUT << "Polozene tehnike:\n" << crt << endl;
        for (int i = 0; i < obj._polozeneTehnike.getTrenutno(); i++) {
            COUT << *obj._polozeneTehnike.getElement1(i);
            COUT << obj._polozeneTehnike.getElement2(i) << endl;
        }
        return COUT;
    }

    float getProsjecnaOcjenaZaPojas() {
        if (_polozeneTehnike.getTrenutno() == 0)
            return 0;
        float suma = 0.0f; int brojac = 0;
        for (int i = 0; i < _polozeneTehnike.getTrenutno(); i++) {
            suma += _polozeneTehnike.getElement1(i)->getProsjecnaOcjenaZaTehniku();
        }
        return suma / _polozeneTehnike.getTrenutno();
        /*for (int i = 0; i < _polozeneTehnike.getTrenutno(); i++) {
            for (int j = 0; j < _polozeneTehnike.getElement1(i)->GetOcjene().getTrenutno(); j++) {
                suma += _polozeneTehnike.getElement1(i)->GetOcjene().getElement2(j);
                brojac++;
            }
        }
        return brojac == 0 ? 0.0f : suma / brojac;*/
    }
};

/*
    email adresa treba biti u sljedecem formatu 3_ime.prezime@karate.ba tj. zadovoljavati sljedeca pravila:
    - poceti sa jednim brojem nakon cega slijedi donja crtica
    - u imenu posjedovati najmanje 3 karaktera
    - izmedju imena i prezimena moze biti tacka ili donja crtica ili nista od navedenog
    - u prezimenu posjedovati najmanje 3 karaktera
    - znak @
    - domenu karate.ba ili edu.karate.ba. Pored drzavne(.ba), dozvoljene su oznake .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase KaratePolaznik, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.karate.ba
    */

bool ValidirajEmail(string email) {
    return regex_match(email, regex("\\d_[A-Za-z]{3,}[\\._]?[A-Za-z]{3,}@(edu\\.)?karate\\.(ba|com|org)"));
}
class KaratePolaznik {
    char* _imePrezime = nullptr;
    string _emailAdresa;
    string _brojTelefona;
    vector<Polaganje> _polozeniPojasevi;
public:
    KaratePolaznik(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = ValidirajEmail(emailAdresa) ? emailAdresa : "notSet@edu.karate.ba";
        _brojTelefona = brojTelefona;
        for (int i = 0; i < 7; i++) {
            _polozeniPojasevi.push_back(Polaganje((Pojas)i));
        }
    }
    KaratePolaznik(const KaratePolaznik& obj) {
        delete[] _imePrezime;
        _imePrezime = GetNizKaraktera(obj.GetImePrezime());
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
        _polozeniPojasevi = obj._polozeniPojasevi;
    }
    KaratePolaznik& operator=(const KaratePolaznik& obj) {
        if (this != &obj)
        {
            delete[] _imePrezime;
            _imePrezime = GetNizKaraktera(obj.GetImePrezime());
            _emailAdresa = obj._emailAdresa;
            _brojTelefona = obj._brojTelefona;
            _polozeniPojasevi = obj._polozeniPojasevi;
        }
        return *this;
    }
    ~KaratePolaznik() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
        COUT << "Ime i prezime polaznika: " << obj._imePrezime << "\nEmail adresa: " << obj._emailAdresa << "\nBroj telefona: " << obj._brojTelefona << endl;
        COUT << "Polozeni pojasevi: " << endl;
        for (size_t i = 0; i < obj._polozeniPojasevi.size(); i++)
            COUT << obj._polozeniPojasevi[i];
        return COUT;
    }
    vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    const char* GetImePrezime() const { return _imePrezime; }

    // moje metode

    float getUkupniProsjek() {
        if (_polozeniPojasevi.size() == 0)
            return 0.0f;
        float suma = 0.0f;
        for (int i = 0; i < _polozeniPojasevi.size(); i++) {
            suma += _polozeniPojasevi[i].getProsjecnaOcjenaZaPojas();
        }
        return suma / _polozeniPojasevi.size();
    }

    /*
    svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju tehnike)
    uspjeh se dodaje za svaku tehniku na nivou pojasa (ZUTI, ZELENI ... ).
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    - dodavanje tehnika za vise pojaseve ako ne postoji najmanje jedna tehnika za nizi pojas (ne mozemo dodati tehniku za NARANDZASTI ako ne postoji niti jedna tehnika za ZUTI pojas)
    - dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    bool AddTehniku(Pojas pojas, Tehnika& tehnika, string napomena) {
        for (int i = 0; i < _polozeniPojasevi[pojas].GetTehnike().getTrenutno(); i++) {
            if (*_polozeniPojasevi[pojas].GetTehnike().getElement1(i) == tehnika)
                return false;   // ne moze biti ista tehnika u jednom pojasu
        }
        if (pojas != ZUTI) {
            if (_polozeniPojasevi[pojas - 1].GetTehnike().getTrenutno() == 0)
                return false;   // mora postojati bar jedna tehnika za prethodni pojas
        }
        if (tehnika.getProsjecnaOcjenaZaTehniku() < 3.5)
            return false;       // prosjecna ocjena manja od 3.5


        _polozeniPojasevi[pojas].GetTehnike().AddElement(&tehnika, napomena);

        thread SlanjeEmaila(&KaratePolaznik::PosaljiEmail, this, ref(tehnika), pojas, _polozeniPojasevi[pojas].getProsjecnaOcjenaZaPojas(), getUkupniProsjek());
        SlanjeEmaila.join();

        return true;
    }


    void PosaljiEmail(Tehnika& tehnika, Pojas pojas, float prosjekZaPojas, float ukupniProsjek) {
        mrPoliceman.lock();
        //this_thread::sleep_for(chrono::seconds(2));
        cout << "FROM: info@karate.ba\nTO: " << GetEmail() << "\n";
        cout << "Postovani " << GetImePrezime() << ", evidentirana vam je tehnika \"" << tehnika.GetNaziv() << "\" za " << pojas << " pojas.";
        cout << "Dosadasnji prosjek na pojasu " << pojas << " iznosi " << setprecision(3) << prosjekZaPojas
            << ", a ukupni prosjek na svim pojasevima iznosi " << setprecision(3) << ukupniProsjek << ".\nPozdrav.\nKARATE Team.\n";
        mrPoliceman.unlock();
    }

    //vraca kolekciju tehnika koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na tehnici
    Kolekcija<Tehnika*, float> operator()(const Datum& fromDatum, const Datum& toDatum){
        Kolekcija<Tehnika*, float> temp;
        for (int i = 0; i < _polozeniPojasevi.size(); i++) {
            for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().getTrenutno(); j++) {
                for (int k = 0; k < _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getTrenutno(); k++) {
                    if (_polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k) > fromDatum &&
                        _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k) < toDatum)
                        temp.AddElement(_polozeniPojasevi[i].GetTehnike().getElement1(j), _polozeniPojasevi[i].GetTehnike().getElement1(j)->getProsjecnaOcjenaZaTehniku());
                }
            }
        }
        return temp;
    }
};


/*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
    FROM:info@karate.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
    na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
    Pozdrav.
    KARATE Team.
    ukoliko je prosjek na nivou tog pojasa veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.D na X pojasu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */

//const char* GetOdgovorNaPrvoPitanje() {
//    cout << "Pitanje -> Za sta se koriste modovi ios::ate i ios::trunc ?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
//const char* GetOdgovorNaDrugoPitanje() {
//    cout << "Pitanje -> Pojasniti ulogu i nacin koristenja iteratora?\n";
//    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
void main() {

   /* cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();*/

    Datum temp,
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        //takodjer, izuzetak se baca i u slucaju da se prekoraci maksimalan broj elemenata
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
    //svaka tehnika moze imati vise ocjena i polaze se u vise navrata (istog ili drugog dana)
    // parametri: nazivTehnike, prva ocjena, datum polaganja
    Tehnika choku_zuki("choku_zuki", datum19062021, 5),
        gyaku_zuki("gyaku_zuki", datum20062021, 5),
        kizami_zuki("kizami_zuki", datum30062021, 2),
        oi_zuki("oi_zuki", datum05072021, 5);

    choku_zuki.AddOcjena(&datum05072021, 3);
    choku_zuki.AddOcjena(&datum05072021, 5);

    // ispisuje: naziv tehnike, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu za tu tehniku
    // ukoliko tehnika nema niti jednu ocjenu prosjecna treba biti 0
    cout << choku_zuki << endl;

    /*
    email adresa treba biti u sljedecem formatu 3_ime.prezime@karate.ba tj. zadovoljavati sljedeca pravila:
    - poceti sa jednim brojem nakon cega slijedi donja crtica
    - u imenu posjedovati najmanje 3 karaktera
    - izmedju imena i prezimena moze biti tacka ili donja crtica ili nista od navedenog
    - u prezimenu posjedovati najmanje 3 karaktera
    - znak @
    - domenu karate.ba ili edu.karate.ba. Pored drzavne(.ba), dozvoljene su oznake .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase KaratePolaznik, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.karate.ba
    */

    if (ValidirajEmail("2_ime.prezime@edu.karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("3_ime_prezime@karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("4_imeprezime@karate.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("8_imeprezime@karate.org"))
        cout << "Email validan" << crt;
    if (!ValidirajEmail("2ime.prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;
    if (!ValidirajEmail("5_ime prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;


    KaratePolaznik* jasmin = new KaratePolaznik("Jasmin Azemovic", "1_jasmin.azemovic@karate.ba", "033 281 172");
    KaratePolaznik* adel = new KaratePolaznik("Adel Handzic", "2_adel_handzic@edu.karate.ba", "033 281 170");
    KaratePolaznik* emailNotValid = new KaratePolaznik("Ime Prezime", "korisnik@karate.ru", "033 281 170");

    /*
    svi kandidati podrazumijevano imaju BIJELI pojas (za njega se ne dodaju tehnike)
    uspjeh se dodaje za svaku tehniku na nivou pojasa (ZUTI, ZELENI ... ).
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) tehnika na nivou jednog pojasa,
    - dodavanje tehnika za vise pojaseve ako ne postoji najmanje jedna tehnika za nizi pojas (ne mozemo dodati tehniku za NARANDZASTI ako ne postoji nitijedna tehnika za ZUTI pojas)
    - dodavanje tehnika kod kojih je prosjecna ocjena manja od 3.5
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //ne treba dodati kizami_zuki jer ne postoji niti jedna tehnika za ZUTI pojas
    if (jasmin->AddTehniku(NARANDZASTI, kizami_zuki, "Napomena 0"))
        cout << "Tehnika uspjesno dodana!1  NE TREBA" << crt;
    if (jasmin->AddTehniku(ZUTI, gyaku_zuki, "Napomena 1"))
        cout << "Tehnika uspjesno dodana!2" << crt;
    if (jasmin->AddTehniku(ZUTI, kizami_zuki, "Napomena 2"))
        cout << "Tehnika uspjesno dodana!3  NE TREBA" << crt;
    if (jasmin->AddTehniku(ZUTI, oi_zuki, "Napomena 3"))
        cout << "Tehnika uspjesno dodana!4" << crt;
    if (jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 4"))
        cout << "Tehnika uspjesno dodana!5" << crt;
    //ne treba dodati choku_zuki jer je vec dodana za zuti pojas
    if (!jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 5"))
        cout << "Tehnika NIJE uspjesno dodana!6" << crt;

    /*nakon evidentiranja tehnike na bilo kojem pojasu kandidatu se salje email sa porukom:
    FROM:info@karate.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je thenika X za Y pojas. Dosadasnji uspjeh (prosjek ocjena)
    na pojasu Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim pojasevima iznosi Z.
    Pozdrav.
    KARATE Team.
    ukoliko je prosjek na nivou tog pojasa veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.D na X pojasu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << *jasmin << crt;

    //vraca kolekciju tehnika koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na tehnici
    Kolekcija<Tehnika*, float> jasminUspjeh = (*jasmin)(Datum(18, 06, 2021), Datum(21, 06, 2021));
    for (size_t i = 0; i < jasminUspjeh.getTrenutno(); i++)
        cout << *jasminUspjeh.getElement1(i) << " " << jasminUspjeh.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete emailNotValid;

    cin.get();
    system("pause>0");
}