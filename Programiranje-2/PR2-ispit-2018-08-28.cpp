#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <thread>
#include <mutex>
#include <regex>
using namespace std;

#pragma warning(disable:4996)
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
const float minimalan_prosjek = 4.5;

char* AlocirajNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

mutex mutexObj;

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1 = nullptr;
    T2* _elementi2 = nullptr;
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
        if(this!=&obj){
            setTrenutno(obj.getTrenutno());
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        }
        return *this;
    }
    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
    int getTrenutno() const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
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

    //kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti

    void SortOpadajuciByT2() {
        bool desilaSePromjena = true;
        int size = getTrenutno() - 1;
        while (desilaSePromjena) {
            desilaSePromjena = false;
            for (int i = 0; i < size; i++) {
                if (_elementi2[i] < _elementi2[i + 1]) {
                    desilaSePromjena = true;
                    swap(_elementi1[i], _elementi1[i + 1]);
                    swap(_elementi2[i], _elementi2[i + 1]);
                }
            }
            size--;
        }
    }
};

class DatumVrijeme {
    int* _dan = nullptr, * _mjesec = nullptr, * _godina = nullptr, * _sati = nullptr, * _minuti = nullptr;
public:
    DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
        _sati = new int(sati);
        _minuti = new int(minuti);
    }
    DatumVrijeme(const DatumVrijeme& obj) {
        setDan(obj.getDan());
        setMjesec(obj.getMjesec());
        setGodina(obj.getGodina());
        setSati(obj.getSati());
        setMinuti(obj.getMinuti());
    }
    DatumVrijeme& operator=(const DatumVrijeme& obj) {
        if(this!=&obj){
            setDan(obj.getDan());
            setMjesec(obj.getMjesec());
            setGodina(obj.getGodina());
            setSati(obj.getSati());
            setMinuti(obj.getMinuti());
        }
        return *this;
    }
    ~DatumVrijeme() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
        delete _sati; _sati = nullptr;
        delete _minuti; _minuti = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, DatumVrijeme& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
        return COUT;
    }

    // moje metode

    int getDan() const { return _dan == nullptr ? 1 : *_dan; }
    int getMjesec() const { return _mjesec == nullptr ? 1 : *_mjesec; }
    int getGodina() const { return _godina == nullptr ? 2000 : *_godina; }
    int getSati() const { return _sati == nullptr ? 0 : *_sati; }
    int getMinuti() const { return _minuti == nullptr ? 0 : *_minuti; }

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
    void setSati(int sati) {
        if (_sati == nullptr)
            _sati = new int;
        *_sati = sati;
    }
    void setMinuti(int minuti) {
        if (_minuti == nullptr)
            _minuti = new int;
        *_minuti = minuti;
    }

    string ToCharArray() {
        string ispis = to_string(getDan()) + "." +
            to_string(getMjesec()) + "." +
            to_string(getGodina()) + " " +
            to_string(getSati()) + ":" + to_string(getMinuti());
        return ispis;
    }

    int toDani() const {
        return getDan() + getMjesec() * 30.41 + getGodina() * 365.24;
    }

    int toMinuti() const {
        //return getMinuti() + getSati() * 60 + getDan() * 1440 + getMjesec() * 1440 * 30.41 + getGodina() * 1440 * 365.24;
        return getSati() * 60 + getMinuti();
    }
};

bool duzeOdMinute(const DatumVrijeme& d1, const DatumVrijeme& d2) {
    if (d1.toDani() != d2.toDani())
        return true;
    if (d1.toMinuti() == d2.toMinuti())
        return false;
    return abs(d1.toMinuti() - d2.toMinuti()) > 1;
}

class Predmet {
    char* _naziv = nullptr;
    int _ocjena;
    string _napomena;
public:
    Predmet(const char* naziv, int ocjena, string napomena = "") :_ocjena(ocjena), _napomena(napomena) {
        _naziv = AlocirajNizKaraktera(naziv);
    }
    Predmet(const Predmet& obj) {
        delete[] _naziv;
        _naziv = AlocirajNizKaraktera(obj.GetNaziv());
        _ocjena = obj._ocjena;
        _napomena = obj.GetNapomena();
    }
    Predmet& operator=(const Predmet& obj) {
        if(this!=&obj){
            delete[] _naziv;
            _naziv = AlocirajNizKaraktera(obj.GetNaziv());
            _ocjena = obj._ocjena;
            _napomena = obj.GetNapomena();
        }
        return *this;
    }
    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, Predmet& obj) {
        COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
        return COUT;
    }
    const char* GetNaziv() const { return _naziv; }
    string GetNapomena() const { return _napomena; }
    int getOcjena() const { return _ocjena; }
    void DodajNapomenu(string napomena) {
        _napomena += " " + napomena;
    }

    // moje metode
};
struct Uspjeh {
    eRazred _razred;
    //datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
    Kolekcija<Predmet*, DatumVrijeme>* _predmeti = nullptr;
public:
    Uspjeh(eRazred razred) :_razred(razred) {
        _predmeti = new Kolekcija<Predmet*, DatumVrijeme>();
    }
    Uspjeh(const Uspjeh& obj) {
        _razred = obj._razred;
        setPredmeti(obj.constGetPredmeti());
    }
    Uspjeh& operator=(const Uspjeh& obj) {
        if(this!=&obj){
            _razred = obj._razred;
            setPredmeti(obj.constGetPredmeti());
        }
        return *this;
    }
    ~Uspjeh() {
        delete _predmeti; _predmeti = nullptr;
    }

    Kolekcija<Predmet*, DatumVrijeme>* GetPredmeti() { return _predmeti; }
    Kolekcija<Predmet*, DatumVrijeme> constGetPredmeti() const { return *_predmeti; }

    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        //COUT << obj._razred << *obj._predmeti << endl;
        COUT << obj._razred << endl;
        for (int i = 0; i < obj._predmeti->getTrenutno(); i++) {
            COUT << "\t" << *obj._predmeti->getElement1(i) << " " << obj._predmeti->getElement2(i) << endl;
        }
        return COUT;
    }

    // moje metode
    void setPredmeti(Kolekcija<Predmet*, DatumVrijeme> predmeti) {
        if (_predmeti == nullptr)
            _predmeti = new Kolekcija<Predmet*, DatumVrijeme>();
        *_predmeti = predmeti;
    }

    eRazred getRazred() const { return _razred; }

    DatumVrijeme getDatumZadnjegPredmeta() {
        DatumVrijeme temp;
        for (int i = 0; i < _predmeti->getTrenutno(); i++) {
            temp = _predmeti->getElement2(i);
        }
        return temp;
    }

    float getProsjecnaOcjenaZaSvePredmete() {
        if (_predmeti->getTrenutno() == 0)
            return 0;
        float suma = 0.0f;
        for (int i = 0; i < _predmeti->getTrenutno(); i++) {
            suma += _predmeti->getElement1(i)->getOcjena();
        }
        return suma / _predmeti->getTrenutno();
    }
};

class Kandidat {
    char* _imePrezime = nullptr;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh*> _uspjeh;
public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona)
        : _emailAdresa(emailAdresa), _brojTelefona(brojTelefona) {
        _imePrezime = AlocirajNizKaraktera(imePrezime);
    }
    Kandidat(const Kandidat& obj) {
        delete[] _imePrezime;
        _imePrezime = AlocirajNizKaraktera(obj.getImePrezime());
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
        //_uspjeh = obj._uspjeh;
        setUspjeh(obj._uspjeh);
    }
    Kandidat& operator=(const Kandidat& obj) {
        if(this!=&obj){
            delete[] _imePrezime;
            _imePrezime = AlocirajNizKaraktera(obj.getImePrezime());
            _emailAdresa = obj._emailAdresa;
            _brojTelefona = obj._brojTelefona;
            //_uspjeh = obj._uspjeh;
            setUspjeh(obj._uspjeh);
        }
        return *this;
    }
    ~Kandidat() {
        delete[] _imePrezime; _imePrezime = nullptr;
        for (size_t i = 0; i < _uspjeh.size(); i++) {
            delete _uspjeh[i];
            _uspjeh[i] = nullptr;
        }
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << *obj._uspjeh[i] << endl;
        return COUT;
    }
    vector<Uspjeh*> GetUspjeh() const { return _uspjeh; }

    // moje metode

    const char* getImePrezime() const { return _imePrezime; }

    void setUspjeh(vector<Uspjeh*> uspjeh) {
        for (int i = 0; i < uspjeh.size(); i++) {
            if (uspjeh[i] != nullptr)
                _uspjeh.push_back(new Uspjeh(*uspjeh[i]));
        }
    }

    /*
    class Predmet {
        char* _naziv = nullptr;
        int _ocjena;
        string _napomena;

        struct Uspjeh {
            eRazred _razred;
            //datumvrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
            Kolekcija<Predmet*, DatumVrijeme>* _predmeti;

            class Kandidat {
                char* _imePrezime = nullptr;
                string _emailAdresa;
                string _brojTelefona;
                vector<Uspjeh*> _uspjeh;
    */

    bool AddPredmet(eRazred razred, Predmet& predmet, DatumVrijeme& datum) {
        bool pronadjenPredmet = false;
        for (int i = 0; i < _uspjeh.size(); i++) {
            if (_uspjeh[i]->getRazred() == razred) {
                pronadjenPredmet = true;
                break;
            }
        }
        
        if (!pronadjenPredmet)
            _uspjeh.push_back(new Uspjeh(razred));



        for (int i = 0; i < _uspjeh.size(); i++)
        {
            if (_uspjeh[i]->getRazred() == razred)                 
            {
                if (_uspjeh[i]->GetPredmeti()->getTrenutno() >= 6)
                    return false;   // ne moze se dodati vise od 6 predmeta na nivou jednog razreda

                bool istoimeniRazred = false;
                for (int j = 0; j < _uspjeh[i]->GetPredmeti()->getTrenutno(); j++) 
                {
                    if (strcmp(_uspjeh[i]->GetPredmeti()->getElement1(j)->GetNaziv(), predmet.GetNaziv()) == 0)
                        return false;   // ne smije biti istoimeni predmet na nivou istog razreda
                }

                if (!duzeOdMinute(datum, _uspjeh[i]->getDatumZadnjegPredmeta()))
                    return false;   // ne smiju se dodavati predmeti u intervalu manjem od minute
            }
        }

        for (int i = 0; i < _uspjeh.size(); i++) {
            if (_uspjeh[i]->getRazred() == razred) {
                //_uspjeh[i]->GetPredmeti()->AddElement(new Predmet(predmet), datum);
                _uspjeh[i]->GetPredmeti()->AddElement(&predmet, datum);
                thread SlanjeEmaila(&Kandidat::PosaljiEmail, this, razred);
                SlanjeEmaila.detach();

                if (_uspjeh[i]->getProsjecnaOcjenaZaSvePredmete() >= minimalan_prosjek) {
                    thread SlanjeSMSa(&Kandidat::PosaljiSMS, this, _uspjeh[i]->getProsjecnaOcjenaZaSvePredmete());
                    SlanjeSMSa.detach();
                }

            }
        }
        return true;
    }

    void PosaljiEmail(eRazred razred) {
        mutexObj.lock();
        this_thread::sleep_for(chrono::seconds(3));
        cout << crt << "Evidentirali ste uspjeh za " << razred << " razred." << crt;
        mutexObj.unlock();
    }

    void PosaljiSMS(float prosjek) {
        mutexObj.lock();
        this_thread::sleep_for(chrono::seconds(2));
        cout << "\t" << crt << "\t" << "Svaka cast za uspjeh " << prosjek << "." << "\t" << crt;
        mutexObj.unlock();
    }

    // pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
    // upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
    // sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od 
    // minimalan_prosjek kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova 
    // implemenitrati koristeci zasebne thread-ove.


    // uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    // tom prilikom onemoguciti:
    // 
        // - dodavanje vise od 6 predmeta za jedan razred
        // - dodavanje istoimenih predmeta na nivou jednog razreda,
        // - dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja 
        //   pojedinih predmeta mora biti najmanje minut).
        // 
    // razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
    // razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    // if (jasmin.AddPredmet(DRUGI, Fizika, datum20062018_1115))


    //Uspjeh* u = jasmin(PRVI);//vraca uspjeh kandidata ostvaren u prvom razredu
    Uspjeh* operator()(eRazred razred) {
        for (int i = 0; i < _uspjeh.size(); i++) {
            if (_uspjeh[i]->getRazred() == razred) {
                return _uspjeh[i];
            }
        }
        return nullptr;
    }

};

void main() {
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR
    // �E BITI OZNACENO KAO "RE"
    // 3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJE�ILO GUBLJENJE URA�ENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKO�ER NALAZI U FAJLU CODE.TXT
    // 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U TESTNOM
    // CODE-U, OSIM U SLU�AJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMO�NE FUNKCIJE
    // MO�ETE IMENOVATI I DODAVATI PO �ELJI.
    // 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNA�ENO.
    ****************************************************************************/

    DatumVrijeme temp,
        datum19062018_1015(19, 6, 2018, 10, 15),
        datum20062018_1115(20, 6, 2018, 11, 15),
        datum30062018_1215(30, 6, 2018, 12, 15),
        datum05072018_1231(5, 7, 2018, 12, 31),
        datum20062018_1115_Copy(datum20062018_1115);
    //funkcija ToCharArray vraca datum i vrijeme kao char *
    cout << datum19062018_1015.ToCharArray() << endl;//treba ispisati: 19.6.2018 10:15
    temp = datum05072018_1231;
    cout << temp.ToCharArray() << endl;//treba ispisati: 5.7.2018 12:31
    cout << datum20062018_1115_Copy.ToCharArray() << endl;//treba ispisati: 20.6.2018 11:15

    const int kolekcijaTestSize = 10;
    Kolekcija<int, int> kolekcija1;
    for (size_t i = 0; i < kolekcijaTestSize; i++)
        kolekcija1.AddElement(i + 1, i * i);
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    Kolekcija<int, int> kolekcija3;
    kolekcija3 = kolekcija1;
    kolekcija3.SortOpadajuciByT2(); //od najvece prema najmanjoj vrijednosti
    cout << kolekcija3 << crt;

    //napomena se moze dodati i prilikom kreiranja objekta
    Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
        Fizika("Fizika", 5),
        Hemija("Hemija", 2),
        Engleski("Engleski", 5);
    Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh"); // dodaje novu napomenu zadrzavajuci ranije dodane
    cout << Matematika << endl;

    Kandidat jasmin("Jasmin Azemovic", "jasmin@gmail.com", "033 281 172");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");

    // uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    // tom prilikom onemoguciti:
    // - dodavanje vise od 6 predmeta za jedan razred
    // - dodavanje istoimenih predmeta na nivou jednog razreda,
    // - dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja 
    // pojedinih predmeta mora biti najmanje minut).
    // razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II
    // razred, pa onda za I razred i sl.). Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    if (jasmin.AddPredmet(DRUGI, Fizika, datum20062018_1115))
        cout << "Predmet uspjesno dodan!1" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, datum30062018_1215))
        cout << "Predmet uspjesno dodan!2" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, datum19062018_1015))
        cout << "Predmet uspjesno dodan!3" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, datum20062018_1115))
        cout << "Predmet uspjesno dodan!4" << crt;
    //ne treba dodati Matematiku jer je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, datum05072018_1231))
        cout << "Predmet uspjesno dodan!5 NE TREBA" << crt;
    if (jasmin.AddPredmet(PRVI, Fizika, datum05072018_1231))
        cout << "Predmet uspjesno dodan!6" << crt;

    // pretpostavka je da na nivou jednog razreda kandidati imaju 6 predmeta.
    // upravo zbog toga, nakon evidentiranja 6 predmeta na nivou jednog razreda kandidatu se salje mail
    // sa porukom: "evidentirali ste uspjeh za X razred". ukoliko je prosjek na nivou tog razreda veci od 
    // minimalan_prosjek kandidatu se salje SMS sa porukom: "svaka cast za uspjeh 4.X". slanje poruka i emailova 
    // implemenitrati koristeci zasebne thread-ove.


    Uspjeh* u = jasmin(PRVI);//vraca uspjeh kandidata ostvaren u prvom razredu
    if (u != nullptr) cout << *u << endl;

    system("pause>0");
}