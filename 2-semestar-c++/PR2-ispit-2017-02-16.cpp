#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <mutex>
#include <regex>

using namespace std;

const char* crt = "\n-----------------------------------------------\n";

mutex mrPoliceman;

enum Status { ZAHTJEV_ZAPRIMLJEN, ODUSTAO, ODBIJENA, IZDATA, ISTEKLA, PONISTENA };
ostream& operator<<(ostream& COUT, const Status& obj) {
    switch (obj) {
    case ZAHTJEV_ZAPRIMLJEN: COUT << "ZAHTJEV_ZAPRIMLJEN"; break;
    case ODUSTAO: COUT << "ODUSTAO"; break;
    case ODBIJENA: COUT << "ODBIJENA"; break;
    case IZDATA: COUT << "IZDATA"; break;
    case ISTEKLA: COUT << "ISTEKLA"; break;
    case PONISTENA: COUT << "PONISTENA"; break;
    default:
        break;
    }
    return COUT;
}
enum Sortiranje { RASTUCI, OPADAJUCI };
enum Drzava { SAD, AUSTRALIJA, ENGLESKA };
ostream& operator<<(ostream& COUT, const Drzava& obj) {
    switch (obj) {
    case SAD: COUT << "SAD"; break;
    case AUSTRALIJA: COUT << "AUSTRALIJA"; break;
    case ENGLESKA: COUT << "ENGLESKA"; break;
    default:
        break;
    }
    return COUT;
}

char* alocirajTekst(const char* source) {
    if (source == nullptr)
        return nullptr;
    int size = strlen(source) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, source);
    return temp;
}

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
    friend ostream& operator<< (ostream& COUT, Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }

    int getGodina() const { return *_godina; }

    int toInt() const { return *_dan + (*_mjesec) * 30.41 + (*_godina) * 365.24; }

    bool isLeapYear(int godina) const { return (godina % 4 == 0 && godina % 100 != 0) || godina % 400 == 0; }

    int getDayForMonth(int mjesec) const {
        switch (mjesec) {
        case 1:case 3:case 5: case 7: case 8: case 10: case 12: 
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(*_godina) ? 29 : 28;
        default:
            return -1;
        }
    }

    Datum operator++() {
        if (*_dan == getDayForMonth(*_mjesec)) {
            *_dan = 1;
            if (*_mjesec == 12) {
                *_mjesec = 1;
                (*_godina)++;
            }
            (*_mjesec)++;
        }
        else {
            (*_dan)++;
        }
        return Datum(*_dan, *_mjesec, *_godina);
    }
};

bool operator==(const Datum& d1, const Datum& d2) { return d1.toInt() == d2.toInt(); }
bool operator!=(const Datum& d1, const Datum& d2) { return d1.toInt() != d2.toInt(); }
bool operator>(const Datum& d1, const Datum& d2) { return d1.toInt() > d2.toInt(); }
bool operator<(const Datum& d1, const Datum& d2) { return d1.toInt() < d2.toInt(); }

template<class T1, class T2, int max>
class FITKolekcija {
    T1* _elementi1[max] = { nullptr };
    T2* _elementi2[max] = { nullptr };
    int _trenutno;
public:
    FITKolekcija() {
        for (size_t i = 0; i < max; i++) {
            _elementi1[i] = nullptr;
            _elementi2[i] = nullptr;
        }
        _trenutno = 0;
        setElementi();
    }
    FITKolekcija(const FITKolekcija& obj) {
        _trenutno = obj._trenutno;
        setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
    }
    FITKolekcija& operator=(const FITKolekcija& obj) {
        if (this != &obj)
        {
            _trenutno = obj._trenutno;
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        }
        return *this;
    }
    ~FITKolekcija() {
        for (size_t i = 0; i < max; i++) {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
    }
    T1** getElementi1() const { return (T1**)_elementi1; }
    T2** getElementi2() const { return (T2**)_elementi2; }
    int getTrenutno() const { return _trenutno; }

    friend ostream& operator<< (ostream& COUT, FITKolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << *obj._elementi1[i] << " " << *obj._elementi2[i] << endl;
        return COUT;
    }

    // moje metode

    void setElementi(int trenutno = 0, T1** elementi1 = nullptr, T2** elementi2 = nullptr) {
        for (size_t i = 0; i < max; i++) {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
        _trenutno = 0;

        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                Dodaj(*elementi1[i], *elementi2[i]);
            }
        }
    }

    void Dodaj(const T1& el1, const T2& el2) {
        if (getTrenutno() >= max)
            throw exception("Kolekcija je popunjena!");
        _elementi1[_trenutno] = new T1(el1);
        _elementi2[_trenutno++] = new T2(el2);
    }
    
    void Sortiraj(Sortiranje sortMode) {
        int size = getTrenutno() - 1;
        bool desilaSePromjena = true;
        while (desilaSePromjena) {
            desilaSePromjena = false;
            if (sortMode == RASTUCI) {
                for (int i = 0; i < size; i++) {
                    if (*_elementi1[i] > *_elementi1[i + 1]) {
                        desilaSePromjena = true;
                        swap(_elementi1[i], _elementi1[i + 1]);
                        swap(_elementi2[i], _elementi2[i + 1]);
                    }
                }
                size--;
            }
            else {
                for (int i = 0; i < size; i++) {
                    if (*_elementi1[i] < *_elementi1[i + 1]) {
                        desilaSePromjena = true;
                        swap(_elementi1[i], _elementi1[i + 1]);
                        swap(_elementi2[i], _elementi2[i + 1]);
                    }
                }
                size--;
            }
        }
    }
};


class Viza {
protected:
    Drzava _drzava;
    Datum _vazenjeOD;
    Datum _vazenjeDO;
    char* _napomena = nullptr;
    // string se odnosi na razlog promjene statusa, a mogu�e je samo 10 izmjena statusa
    FITKolekcija<Status, string, 10> _statusi;
public:
    Viza(Drzava drzava, Datum _OD, Datum _DO, const char* napomena = "") :_vazenjeDO(_DO), _vazenjeOD(_OD) {
        _napomena = alocirajTekst(napomena);
        _drzava = drzava;
    }
    Viza(const Viza& obj) {
        _drzava = obj._drzava;
        _vazenjeOD = obj._vazenjeOD;
        _vazenjeDO = obj._vazenjeDO;
        delete[] _napomena;
        _napomena = alocirajTekst(obj.GetNapomena());
    }
    Viza& operator=(const Viza& obj) {
        if (this != &obj)
        {
            _drzava = obj._drzava;
            _vazenjeOD = obj._vazenjeOD;
            _vazenjeDO = obj._vazenjeDO;
            delete[] _napomena;
            _napomena = alocirajTekst(obj.GetNapomena());
        }
        return *this;
    }
    ~Viza() { delete[] _napomena; _napomena = nullptr; }
    Datum GetVazenjeOD() const { return _vazenjeOD; }
    Datum GetVazenjeDO() const { return _vazenjeDO; }
    const char* GetNapomena() const { return /*_napomena == nullptr ? "" :*/ _napomena; }
    FITKolekcija<Status, string, 10>& GetStatuse() { return _statusi; }
    Drzava getDrzava() const { return _drzava; }
    virtual void Info() = 0;

    friend ostream& operator << (ostream& COUT, Viza& obj) {
        COUT << "Drzava: " << obj._drzava << "\nVazi od: " << obj._vazenjeOD << "\nVazi do: " << obj._vazenjeDO <<  endl;
        COUT << ((obj._napomena != nullptr) ? obj._napomena : "") << endl;
        COUT << "STATUSI -> " << obj._statusi << endl;
        return COUT;
    }

    void setNapomena(const char* napomena) {
        _napomena = alocirajTekst(napomena);
    }

};

bool operator==(const Viza& v1, const Viza& v2) {
    return v1.getDrzava() == v2.getDrzava() && v1.GetVazenjeOD() == v2.GetVazenjeOD() && v1.GetVazenjeDO() == v2.GetVazenjeDO() && 
        strcmp(v1.GetNapomena(), v2.GetNapomena()) == 0;
}

class PoslovnaViza :public Viza {
    string _kompanija; //naziv kompanije koja potvr�uje da posluje sa aplikantom
public:
    PoslovnaViza(Drzava drzava, Datum _OD, Datum _DO, string kompanija, const char* napomena = "") : Viza(drzava, _OD, _DO, napomena) {
        _kompanija = kompanija;
    }
    PoslovnaViza(const PoslovnaViza& obj): Viza(obj) {
        _kompanija = obj._kompanija;
    }
    PoslovnaViza& operator=(const PoslovnaViza& obj) {
        if (this != &obj) {
            (Viza&)(*this) = obj;
            _kompanija = obj._kompanija;
        }
        return *this;
    }
    friend ostream& operator << (ostream& COUT, PoslovnaViza& obj) {
        COUT << (Viza&)obj;
        COUT << "Kompanija: " << obj._kompanija;
        return COUT;
    }

    string getKompanija() const { return _kompanija; }

    void Info(){}

};

bool operator==(const PoslovnaViza& v1, const PoslovnaViza& v2) {
    return (Viza&)v1 == (Viza&)v2 && v1.getKompanija() == v2.getKompanija();
}

class TuristickaViza : public Viza {
    string _adresa; //adresa hotele ili drugog smje�taja na kojoj �e aplikant boraviti
public:
    TuristickaViza(Drzava drzava, Datum _OD, Datum _DO, string adresa, const char* napomena = "") : Viza(drzava, _OD, _DO, napomena) {
        _adresa = adresa;
    }
    TuristickaViza(const TuristickaViza& obj) : Viza(obj) {
        _adresa = obj._adresa;
    }
    TuristickaViza& operator=(const TuristickaViza& obj) {
        if (this != &obj) {
            (Viza&)(*this) = obj;
            _adresa = obj._adresa;
        }
        return *this;
    }
    friend ostream& operator << (ostream& COUT, TuristickaViza& obj) {
        COUT << (Viza&)obj;
        COUT << "Kompanija: " << obj._adresa;
        return COUT;
    }

    string getAdresa() const { return _adresa; }

    void Info() {}

};

bool operator==(const TuristickaViza& v1, const TuristickaViza& v2) {
    return (Viza&)v1 == (Viza&)v2 && v1.getAdresa() == v2.getAdresa();
}

class Aplikant {
    char* _imePrezime = nullptr;
    Datum* _datumRodjenja = nullptr;
    char* _brojPasosa = nullptr;
    vector<Viza*> _vize;
public:
    Aplikant(const char* imePrezime, const Datum& datumRodjenja, const char* brPasosa) {
        int vel = strlen(imePrezime) + 1;
        _imePrezime = new char[vel];
        strcpy_s(_imePrezime, vel, imePrezime);
        vel = strlen(brPasosa) + 1;
        _brojPasosa = new char[vel];
        strcpy_s(_brojPasosa, vel, brPasosa);
        _datumRodjenja = new Datum(datumRodjenja);
    }
    Aplikant(const Aplikant& obj) {
        delete[] _imePrezime;
        _imePrezime = alocirajTekst(obj.getImePrezime());
        _datumRodjenja = new Datum(*obj._datumRodjenja);
        delete[] _brojPasosa;
        _brojPasosa = alocirajTekst(obj.getBrojPasosa());
        for (int i = 0; i < obj._vize.size(); i++) {
            PoslovnaViza* pViza = dynamic_cast<PoslovnaViza*>(obj._vize[i]);
            if (pViza != nullptr) {
                _vize.push_back(new PoslovnaViza(*pViza));
            }
            TuristickaViza* tViza = dynamic_cast<TuristickaViza*>(obj._vize[i]);
            if (tViza != nullptr) {
                _vize.push_back(new TuristickaViza(*tViza));
            }
        }
    }
    Aplikant& operator=(const Aplikant& obj) {
        if (this != &obj)
        {
            delete[] _imePrezime;
            _imePrezime = alocirajTekst(obj.getImePrezime());
            _datumRodjenja = new Datum(*obj._datumRodjenja);
            delete[] _brojPasosa;
            _brojPasosa = alocirajTekst(obj.getBrojPasosa());
            for (int i = 0; i < obj._vize.size(); i++) {
                PoslovnaViza* pViza = dynamic_cast<PoslovnaViza*>(obj._vize[i]);
                if (pViza != nullptr) {
                    _vize.push_back(new PoslovnaViza(*pViza));
                }
                TuristickaViza* tViza = dynamic_cast<TuristickaViza*>(obj._vize[i]);
                if (tViza != nullptr) {
                    _vize.push_back(new TuristickaViza(*tViza));
                }
            }
        }
        return *this;
    }
    ~Aplikant() {
        delete[]_imePrezime; _imePrezime = nullptr;
        delete[]_brojPasosa; _brojPasosa = nullptr;
        delete _datumRodjenja; _datumRodjenja = nullptr;
        for (size_t i = 0; i < _vize.size(); i++) {
            delete _vize[i]; _vize[i] = nullptr;
        }
    }
    friend ostream& operator << (ostream& COUT, Aplikant& obj) {
        COUT << "\nIme i prezime: " << obj._imePrezime << "\nDatum rodjenja: " << *obj._datumRodjenja << "\nBroj pasosa: " << obj._brojPasosa << endl;
        COUT << "VIZE -> " << endl;
        for (size_t i = 0; i < obj._vize.size(); i++)
            COUT << "\t" << * obj._vize[i] << endl;
        return COUT;
    }
    vector<Viza* > GetVize() { return _vize; }
    const char* getImePrezime() const { return _imePrezime; }
    const char* getBrojPasosa() const { return _brojPasosa; }

    // moje metode

    // NOVA VIZA SE NE MOZE DODATI UKOLIKO:
    // -	JE APLIKANT MLADJI OD 10 GODINA
    // -	U TOM PERIODU (ODNOSI SE NA PERIOD VIZE OD - DO) NE POSTOJI VAZECA (POJAM VAZECA PODRAZUMIJEVA DA JE POSLJEDNJI STATUS VIZE BIO IZDATA TJ. DA VIZA NIJE PONISTENA ILI ISTEKLA) VIZA ZA TU DRZAVU, BEZ OBZIRA NA NJENU VRSTU.	
    // -	JE NEKA OD RANIJIH VIZA PONISTENA (OVO SE ODNOSI SAMO NA VIZE ZA DRZAVU: SAD)


    /*
    * Viza: 
    Drzava _drzava;
    Datum _vazenjeOD;
    Datum _vazenjeDO;
    char* _napomena = nullptr;
    // string se odnosi na razlog promjene statusa, a mogu�e je samo 10 izmjena statusa
    FITKolekcija<Status, string, 10> _statusi;
    */

    bool DodajVizu(Viza* viza) {
        if (abs(_datumRodjenja->getGodina() - 2017) < 10)
            return false;   // mladji od 10 godina
        if (viza->getDrzava() == SAD) {
            for (int i = 0; i < _vize.size(); i++) {
                for (int j = 0; j < _vize[i]->GetStatuse().getTrenutno(); j++) {
                    if (*_vize[i]->GetStatuse().getElementi1()[j] == PONISTENA)
                        return false;   // SAD ne prihvata ponistene vize
                }
            }
        }

        for (int i = 0; i < _vize.size(); i++) {
            if (viza->GetVazenjeOD() > _vize[i]->GetVazenjeOD() && viza->GetVazenjeDO() < _vize[i]->GetVazenjeDO()) {
                if (*_vize[i]->GetStatuse().getElementi1()[_vize[i]->GetStatuse().getTrenutno() - 1] == IZDATA)
                    return false;   // pretpostavljam da ovo treba u drugom uslovu  ?
            }
        }


        PoslovnaViza* pViza = dynamic_cast<PoslovnaViza*>(viza);
        if (pViza != nullptr) {
            _vize.push_back(new PoslovnaViza(*pViza));
        }
        TuristickaViza* tViza = dynamic_cast<TuristickaViza*>(viza);
        if (tViza != nullptr) {
            _vize.push_back(new TuristickaViza(*tViza));
        }

        return true;
    }

    // STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
   // -	NIJE MOGU�E ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
   // -	NIJE MOGU�E PONI�TITI VIZU KOJA PRETHODNO NIJE IZDATA

    // ZAHTJEV_ZAPRIMLJEN, ODUSTAO, ODBIJENA, IZDATA, ISTEKLA, PONISTENA

    bool DodajStatus(Viza* viza, Status status, const char* napomena = "") {
        for (int i = 0; i < _vize.size(); i++) {
            if (*viza == *_vize[i]) {

                if (status > 0) {
                    //if (status - *_vize[i]->GetStatuse().getElementi1()[_vize[i]->GetStatuse().getTrenutno() - 1] > 1)
                    //    return false;   // postuje se redoslijed
                    if ((status == IZDATA || status == ODBIJENA || status == ODUSTAO) && *_vize[i]->GetStatuse().getElementi1()[0] != ZAHTJEV_ZAPRIMLJEN)
                        return false;
                    else if (status > IZDATA) {
                        if (status - *_vize[i]->GetStatuse().getElementi1()[_vize[i]->GetStatuse().getTrenutno() - 1] > 1)
                            return false;
                    }
                }

                _vize[i]->GetStatuse().Dodaj(status, alocirajTekst(napomena));


                return true;
            }
        }
        return false;
    }

    void PrintajVizu(Viza* viza) {
        thread Printanje(&Aplikant::PrintanjeVize, this, viza);
        Printanje.join();
    }

    void PrintanjeVize(Viza* viza) {
        mrPoliceman.lock();
        this_thread::sleep_for(chrono::seconds(2));
        cout << *viza;
        mrPoliceman.unlock();
    }


    vector<Viza*> GetVizeByDrzava(Drzava drzava, Status status) {
        vector<Viza*> temp;
        for (int i = 0; i < _vize.size(); i++) {
            for (int j = 0; j < _vize[i]->GetStatuse().getTrenutno(); j++) {
                if (*_vize[i]->GetStatuse().getElementi1()[j] == status && _vize[i]->getDrzava() == drzava) {
                    temp.push_back(_vize[i]);
                    break;
                }
            }
        }
        return temp;
    }

    void ZamijeniRijec(string toReplace, string replaceWith) {
        regex pravilo(toReplace);
        for (int i = 0; i < _vize.size(); i++) {
            for (int j = 0; j < _vize[i]->GetStatuse().getTrenutno(); j++) {
                cout << "\t" << *_vize[i]->GetStatuse().getElementi2()[j] << " -> ";
                *_vize[i]->GetStatuse().getElementi2()[j] = regex_replace(*_vize[i]->GetStatuse().getElementi2()[j], pravilo, replaceWith);
                cout << *_vize[i]->GetStatuse().getElementi2()[j] << endl;
            }
        }
    }

};

void main() {

    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME
    //    ERROR �E BITI OZNACENO KAO "RE"
    // 3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJE�ILO GUBLJENJE URA�ENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKO�ER NALAZI U FAJLU CODE.TXT
    // 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U,
    //    OSIM U SLU�AJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMO�NE FUNKCIJE MO�ETE IMENOVATI
    //    I DODAVATI PO �ELJI.
    // 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNA�ENO.
    ****************************************************************************/

    Datum danas(15, 2, 2017);
    Datum sutra(++danas); // inkrementiranjem se uvecava dan za 1
    Datum prekosutra;
    Datum dat15022017(15, 2, 2017), dat18082017(18, 8, 2017), dat11052018(11, 5, 2018), dat11122017(11, 12, 2017);


    prekosutra = danas;
    if (prekosutra == danas)
        cout << "Datumi su jednaki" << endl;
    cout << danas << endl << sutra << endl << prekosutra << crt;

    int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;

    FITKolekcija<int, int, 7> brojevi;
    brojevi.Dodaj(v196, v6);
    brojevi.Dodaj(v13, v32);
    brojevi.Dodaj(v98, v196);
    brojevi.Dodaj(v63, v13);
    brojevi.Dodaj(v98, v196);
    brojevi.Dodaj(v196, v6);

    cout << brojevi << crt;
    //NA KOJI NA�IN �E SE VR�ITI SORTIRANJE PRVENSTVENO ZAVISI OD VRIJEDNOSTI PARAMETRA, A VR�I SE NA OSNOVU VRIJEDNOSTI TIPA T1
    brojevi.Sortiraj(RASTUCI);
    cout << brojevi << crt;
    brojevi.Sortiraj(OPADAJUCI);
    cout << brojevi << crt;

    try {
        //U SLU�AJU PREKORA�ENJA DEFINISANE VELI�INE KOLEKCIJE, POTREBNO JE BACITI IZUZETAK
        brojevi.Dodaj(v13, v196);
    }
    catch (exception& err) {
        cout << "Error -> " << err.what() << endl;
    }

    Aplikant jasmin("Jasmin Azemovic", Datum(15, 5, 1979), "BS6985645");
    PoslovnaViza poslovna(SAD, dat15022017, dat18082017, "Microsoft");


    // NOVA VIZA SE NE MO�E DODATI UKOLIKO:
    // -	JE APLIKANT MLA�I OD 10 GODINA
    // -	U TOM PERIODU (ODNOSI SE NA PERIOD VIZE OD - DO) NE POSTOJI VA�E�A (POJAM VA�E�A PODRAZUMIJEVA DA JE POSLJEDNJI STATUS VIZE BIO IZDATA TJ. DA VIZA NIJE 	PONI�TENA ILI ISTEKLA) VIZA ZA TU DR�AVU, BEZ OBZIRA NA NJENU VRSTU.	
    // -	JE NEKA OD RANIJIH VIZA PONI�TENA (OVO SE ODNOSI SAMO NA VIZE ZA DR�AVU: SAD)

    if (jasmin.DodajVizu(&poslovna))
        cout << "Podaci o vizi uspjesno zaprimljeni" << endl;

    // STATUSI SE MOGU DODAVATI SAMO U REDOSLIJEDU U KOJEM SE NALAZE U ENUMERACIJI NPR.
    // -	NIJE MOGU�E ODBITI VIZU AKO PRETHODNO NIJE IMALA STATUS DA JE ZAHTJEV_ZAPRIMLJEN;
    // -	NIJE MOGU�E PONI�TITI VIZU KOJA PRETHODNO NIJE IZDATA

    if (jasmin.DodajStatus(&poslovna, ZAHTJEV_ZAPRIMLJEN, "provjeriti navode sa predstavnicima kompanije Microsoft"))
        cout << "Status vize uspijesno promijenjen" << endl;
    else
        cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;


    if (jasmin.DodajStatus(&poslovna, PONISTENA, "predstavnicima kompanije Microsoft nemaju informaciju o posjeti navedenog aplikanta"))
        cout << "Status vize uspijesno promijenjen" << endl;
    else
        cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

    TuristickaViza turisticka(ENGLESKA, dat18082017, dat11122017, "Whitehall Pl, London SW1A 2BD, UK");
   
    if (jasmin.DodajVizu(&turisticka))
        cout << "Podaci o vizi uspjesno zaprimljeni" << endl;

    if (jasmin.DodajStatus(&turisticka, ZAHTJEV_ZAPRIMLJEN))
        cout << "Status vize uspijesno promijenjen" << endl;
    else
        cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;

    if (jasmin.DodajStatus(&turisticka, IZDATA)) {
        cout << "Status vize uspijesno promijenjen" << endl;
        //U ZASEBNOJ NITI URADITI PRINTANJE VIZE...KORISTITI METODU SLEEP_FOR
        jasmin.PrintajVizu(&turisticka);
    }
    else
        cout << "Aplikant " << jasmin << " ne posjeduje evidentiranu trazenu vizu ili status vize nema odgovarajucu vrijednost" << endl;
    //VRA�A PODATKE O SVIM VIZAMA KOJE SU IZDATE ZA ODRE�ENU DR�AVU, A KOJE SU IMALE ODRE�ENI STATUS
    vector<Viza*> jasminVize = jasmin.GetVizeByDrzava(SAD, PONISTENA);

    //UNUTAR NAPOMENE MIJENJA SADR�AJ "provjeriti" SA "ispitati" - KORISTITI REGEX
    jasmin.ZamijeniRijec("provjeriti", "ispitati");
}