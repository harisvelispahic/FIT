#include <iostream>
#include <vector>
#include <regex>

using namespace std;


class Datum;
class Izuzetak;
const char* crt = "\n---------------------------------------\n";

char* alocirajTekst(const char* source) {
    if (source == nullptr) {
        return nullptr;
    }
    int size = strlen(source) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, source);
    return temp;
}

template<class T1, class T2, int max>
class Kolekcija
{
    T1 _elementi1[max];
    T2 _elementi2[max];
    int* _trenutno = nullptr;
public:
    Kolekcija() {
        setElementi();
    }
    Kolekcija(const Kolekcija& obj) {
        setElementi(obj.GetTrenutno(), obj.getElementi1(), obj.getElementi2());
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj)
            setElementi(obj.GetTrenutno(), obj.getElementi1(), obj.getElementi2());
        return *this;
    }
    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
    }

    T1* getElementi1() const { return (T1*)_elementi1; }
    T2* getElementi2() const { return (T2*)_elementi2; }
    int GetTrenutno() const { return (_trenutno == nullptr) ? 0 : *_trenutno; }
    int size() const { return (_trenutno == nullptr) ? 0 : *_trenutno; }
    int GetMax() const { return max; }
    T1 GetElement1(int index) const {
        if (index < 0 || index >= GetTrenutno()) {
            //throw exception("Element na toj lokaciji ne postoji!");
            throw Izuzetak(Datum(), __FUNCTION__, __LINE__, "Element na toj lokaciji ne postoji!");
        }
        return _elementi1[index];
    }
    T2 GetElement2(int index) const {
        if (index < 0 || index >= GetTrenutno()) {
            //throw exception("Indeks van granica!");
            throw Izuzetak(Datum(), __FUNCTION__, __LINE__, "Element na toj lokaciji ne postoji!");
        }
        return _elementi2[index];
    }


    void setTrenutno(int trenutno) {
        if (_trenutno == nullptr)
            _trenutno = new int;
        *_trenutno = trenutno;
    }
    void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
        setTrenutno(0);
        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
            AddElement(elementi1[i], elementi2[i]);
            }
        }
    }

    void AddElement(const T1& el1, const T2& el2) {
        if (GetTrenutno() >= max) {
            //throw exception("Nema vise mjesta za dodavanja novih elemenata!");
            //throw Izuzetak(__DATE__,__FUNCTION__, __LINE__)
            throw Izuzetak(Datum(), __FUNCTION__, __LINE__, "Nema vise mjesta za dodavanja novih elemenata!");
        }
        _elementi1[GetTrenutno()] = el1;
        _elementi2[GetTrenutno()] = el2;
        setTrenutno(GetTrenutno() + 1);
    }
    // u kontekstu ove implementacije, brisu se elementi prvog niza
    T1& operator[](int index) {
        if (index < 0 || index >= GetTrenutno())
            throw Izuzetak(Datum(), __FUNCTION__, __LINE__, "Element na toj lokaciji ne postoji!");
        return _elementi1[index];
    }

    bool RemoveElement() {
        if (GetTrenutno() <= 0)
            return false;
        setTrenutno(GetTrenutno() - 1);
        return true;
    }

    friend ostream& operator<<(ostream& COUT, const Kolekcija<T1, T2, max>& obj) {
        for (int i = 0; i < obj.GetTrenutno(); i++) {
            COUT << obj.GetElement1(i) << " " << obj.GetElement2(i) << endl;
        }
        return COUT;
    }
};

class Datum
{
    int* _dan = nullptr;
    int* _mjesec = nullptr;
    int* _godina = nullptr;
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
    Datum& operator=(const Datum& obj) {
        if(this!=&obj) {
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

    int toInt() const {
        return getDan() * getMjesec() * 30.41 + getGodina() * 365.24;
    }

    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina();
        return COUT;
    }
};

bool operator==(const Datum& d1, const Datum& d2) {
    return d1.getDan() == d2.getDan() &&
        d1.getMjesec() == d2.getMjesec() &&
        d1.getGodina() == d2.getGodina();
}

class Izuzetak :public exception
{
    Datum _datum;//KORISTITE DANASNJI DATUM
    string _funkcija;//FUNKCIJA U KOJOJ JE NASTAO IZUZETAK
    int _linija;//LINIJA CODE-A U KOJOJ JE NASTAO IZUZETAK
public:

    Izuzetak(Datum datum, string funkcija, int linija, const char* sadrzaj) : exception(sadrzaj) {
        _datum = datum;
        _funkcija = funkcija;
        _linija = linija;
    }

    friend ostream& operator<<(ostream& COUT, const Izuzetak& obj) {
        COUT << obj._datum << "\nFunkcija " << obj._funkcija << " je na liniji " << obj._linija 
            << " napravila exception:\n" << obj.what() << endl;
        return COUT;
    }
};

enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
ostream& operator<<(ostream& COUT, const enumKursevi& obj) {
    switch (obj) {
    case HtmlCSSJavaScript:
        COUT << "HtmlCSSJavaScript";
        break;
    case SoftwareEngeneeringFundamentals:
        COUT << "SoftwareEngeneeringFundamentals";
        break;
    case MasteringSQL:
        COUT << "MasteringSQL";
        break;
    case WindowsSecurity:
        COUT << "WindowsSecurity";
        break;
    default:
        break;
    }
    return COUT;
}
class Kurs
{
    enumKursevi _kurs;
    Datum _pocetak;
    Datum _kraj;
    char* _imePredavaca = nullptr;
public:

    Kurs(enumKursevi kurs = HtmlCSSJavaScript, const char* imePredavaca = "", Datum pocetak = Datum(), Datum kraj = Datum()) {
        setKurs(kurs);
        setDatumPocetka(pocetak);
        setDatumKraja(kraj);
        setImePredavaca(imePredavaca);
    }
    Kurs(const Kurs& obj) {
        setKurs(obj.getKurs());
        setDatumPocetka(obj.getDatumPocetka());
        setDatumKraja(obj.getDatumKraja());
        setImePredavaca(obj.getImePredavaca());
    }
    Kurs& operator=(const Kurs& obj) {
        if(this!=&obj){
            setKurs(obj.getKurs());
            setDatumPocetka(obj.getDatumPocetka());
            setDatumKraja(obj.getDatumKraja());
            setImePredavaca(obj.getImePredavaca());
        }
        return *this;
    }
    ~Kurs() {
        delete[] _imePredavaca; _imePredavaca = nullptr;
    }

    enumKursevi getKurs() const { return _kurs; }
    Datum getDatumPocetka() const { return _pocetak; }
    Datum getDatumKraja() const { return _kraj; }
    const char* getImePredavaca() const { return(_imePredavaca == nullptr) ? "" : _imePredavaca; }

    void setKurs(enumKursevi kurs) {
        _kurs = kurs;
    }
    void setDatumPocetka(Datum datumPocetka) {
        _pocetak = datumPocetka;
    }
    void setDatumKraja(Datum datumKraja) {
        _kraj = datumKraja;
    }
    void setImePredavaca(const char* ime) {
        delete[] _imePredavaca;
        _imePredavaca = alocirajTekst(ime);
    }

    friend ostream& operator<<(ostream& COUT, const Kurs& obj) {
        COUT << "Naziv kursa: " << obj.getKurs() << endl;
        COUT << "Pocetak - Kraj: " << obj.getDatumPocetka() << " - " << obj.getDatumKraja() << endl;
        COUT << "Ime predavaca: " << obj.getImePredavaca() << endl;
        return COUT;
    }

    bool ProvjeriJeLiDatumIzmedjuDvaDatuma(const Datum& DATUM) {
        return(DATUM.toInt() > _pocetak.toInt() && DATUM.toInt() < _kraj.toInt());
    }
};
bool operator==(const Kurs& k1, const Kurs& k2) {
    if (k1.getKurs() == k2.getKurs() &&
        k1.getDatumPocetka() == k2.getDatumPocetka() &&
        k1.getDatumKraja() == k2.getDatumKraja() &&
        strcmp(k1.getImePredavaca(), k2.getImePredavaca()) == 0)
        return true;
    return false;
}
bool operator!=(const Kurs& k1, const Kurs& k2) {
    return !(k1 == k2);
}


class Polaznik
{
    static int ID;
    const int _polaznikID;
    //SVAKOM NOVOM POLAZNIKU AUTOMATSKI DODIJELITI NOVI ID (AUTOINCREMENT) POCEVSI OD BROJA 1
    char* _imePrezime = nullptr;
    string _kontaktTelefon; //BROJ TELEFONA TREBA BITI U FORMATU (06X)XXX-XXX 
    Kolekcija<Kurs*, int, 10> _uspjesnoOkoncaniKursevi;
    //INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
public:
    Polaznik(const char* imePrezime, string telefon) : _polaznikID(ID++)
    {
        setImePrezime(imePrezime);
        setKontaktTelefon(telefon);
    }
    Polaznik(const Polaznik& obj) : _polaznikID(ID) {
        setImePrezime(obj.getImePrezime());
        setKontaktTelefon(obj.getKontaktTelefon());
        setUspjesnoOkoncaniKursevi(obj.getUspjesnoOkoncaniKursevi());
    }
    Polaznik& operator=(const Polaznik& obj) {
        if (this != &obj) {
            setImePrezime(obj.getImePrezime());
            setKontaktTelefon(obj.getKontaktTelefon());
            setUspjesnoOkoncaniKursevi(obj.getUspjesnoOkoncaniKursevi());
        }
        return *this;
    }
    ~Polaznik()
    {
        delete[] _imePrezime; _imePrezime = nullptr;
        for (size_t i = 0; i < _uspjesnoOkoncaniKursevi.size(); i++)
        {
            delete _uspjesnoOkoncaniKursevi[i];
            _uspjesnoOkoncaniKursevi[i] = nullptr;
        }
    }
    int getPolaznikID() const { return _polaznikID; }
    const char* getImePrezime() const { return (_imePrezime == nullptr) ? "" : _imePrezime; }
    string getKontaktTelefon() const { return _kontaktTelefon; }
    Kolekcija<Kurs*, int, 10> getUspjesnoOkoncaniKursevi() const { return _uspjesnoOkoncaniKursevi; }

    void setImePrezime(const char* imePrezime) {
        delete[] _imePrezime;
        _imePrezime = alocirajTekst(imePrezime);
    }
    void setKontaktTelefon(string kontaktTelefon) {
        _kontaktTelefon = kontaktTelefon;
    }
    void setUspjesnoOkoncaniKursevi(Kolekcija<Kurs*, int, 10> kursevi) {
        _uspjesnoOkoncaniKursevi = kursevi;
    }
    
    friend ostream& operator<<(ostream& COUT, const Polaznik& obj) {
        //COUT << "ID: " << obj.getPolaznikID() << endl;
        COUT << "Ime i prezime: " << obj.getImePrezime() << endl;
        COUT << "Kontakt telefon: " << obj.getKontaktTelefon() << endl;
        for (int i = 0; i < obj.getUspjesnoOkoncaniKursevi().GetTrenutno(); i++) {
            COUT << obj.getUspjesnoOkoncaniKursevi()[i] << endl;
        }
        return COUT;
    }
};
int Polaznik::ID = 1;
bool operator==(const Polaznik& p1, const Polaznik& p2) {
    if (strcmp(p1.getImePrezime(), p2.getImePrezime()) != 0 ||
        p1.getUspjesnoOkoncaniKursevi().GetTrenutno() != p2.getUspjesnoOkoncaniKursevi().GetTrenutno())
        return false;
    for (int i = 0; i < p1.getUspjesnoOkoncaniKursevi().GetTrenutno(); i++) {
        if (*p1.getUspjesnoOkoncaniKursevi().GetElement1(i) != *p2.getUspjesnoOkoncaniKursevi().GetElement1(i) ||
            p1.getUspjesnoOkoncaniKursevi().GetElement2(i) != p2.getUspjesnoOkoncaniKursevi().GetElement2(i))
            return false;
    }
    return true;
}

class SkillsCentar
{
    string _nazivCentra;
    vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
    Kolekcija<Kurs, Polaznik*, 150> _aplikanti;
public:
    SkillsCentar(string naziv) { 
        setNazivCentra(naziv);
    }
    SkillsCentar(const SkillsCentar& obj) :_kursevi(obj._kursevi), _aplikanti(obj._aplikanti)
    {
        setNazivCentra(obj.getNazivCentra());
    }
    ~SkillsCentar() {
        // ako se pokazivaci polaznici salju iz maina, NE SMIJU SE BRISATI
    }

    string getNazivCentra() const { return _nazivCentra; }
    vector<Kurs> getKursevi() const { return _kursevi; }
    Kolekcija<Kurs, Polaznik*, 150> getAplikanti() const { return _aplikanti; }

    void setNazivCentra(string naziv) {
        _nazivCentra = naziv;
    }
    void setKursevi(vector<Kurs> kursevi) {
        _kursevi = kursevi;
    }
    void setAplikanti(Kolekcija<Kurs, Polaznik*, 150> aplikanti) {
        _aplikanti = aplikanti;
    }



    //JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA I KURSA SE NE SMIJE POKLAPAT
    bool ProvjeriKoliziju(Kurs kurs) {
        for (int i = 0; i < _kursevi.size(); i++) {
            if (_kursevi[i].ProvjeriJeLiDatumIzmedjuDvaDatuma(kurs.getDatumPocetka()))
                return false;
        }
        return true;
    }

    void AddKurs(Kurs sef) {
        for (int i = 0; i < _kursevi.size(); i++) {
            if (_kursevi[i] == sef)
                throw Izuzetak(Datum(), __FUNCTION__, __LINE__, "Predmet koji pokusavate dodati vec se nalazi u listi!");
        }
        _kursevi.push_back(sef);
    }

    void AddAplikaciju(Kurs kurs, Polaznik& polaznik) {
        //ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
        bool kursRegistrovan = false;
        for (int i = 0; i < _kursevi.size(); i++) {
            if (_kursevi[i] == kurs)
                kursRegistrovan = true;
        }
        if (kursRegistrovan == false)
            return;

        //ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
        for (int i = 0; i < _aplikanti.GetTrenutno(); i++) {
            if (_aplikanti.GetElement1(i) == kurs && *_aplikanti.GetElement2(i) == polaznik)
                throw Izuzetak(Datum(), __FUNCTION__, __LINE__, "Aplikacija za kurs je vec poslana!");
        }

        _aplikanti.AddElement(kurs, &polaznik);
    }

    //ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
    bool RemoveKurs(Kurs kurs) {
        for (int i = 0; i < _aplikanti.GetTrenutno(); i++) {
            if (_aplikanti.GetElement1(i) == kurs)
                return false;
        }
        _aplikanti.RemoveElement();
        return true;
    }

    bool DaLiJePolaznikApliciraoZaKurs(Polaznik polaznik, Kurs kurs) {
        for (int i = 0; i < _aplikanti.GetTrenutno(); i++) {
            if (_aplikanti.GetElement1(i) == kurs && *_aplikanti.GetElement2(i) == polaznik) {
                return true;
            }
        }
        return false;
    }

    Polaznik& GetPolaznikByID(int id) {
        for (int i = 0; i < _aplikanti.GetTrenutno(); i++) {
            if (_aplikanti.GetElement2(i)->getPolaznikID() == id)
                return *_aplikanti.GetElement2(i);
        }
    }
    
    // BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU 
    // DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR. PREDUSLOV ZA DODAVANJE JE DA JE 
    // POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
    void DodajUspjesnoOkoncanKurs(int id, Kurs& kurs, int bodovi) {
        // Kolekcija<Kurs*, int, 10> _uspjesnoOkoncaniKursevi;
        // INT PREDSTAVLJA OSTVARENI PROCENAT NA ISPITU, A JEDAN POLAZNIK MOZE POLOZITI NAJVISE 10 KURSEVA
        Polaznik nasPolaznik = GetPolaznikByID(id);
        if (DaLiJePolaznikApliciraoZaKurs(nasPolaznik, kurs) && bodovi > 55) {
            nasPolaznik.getUspjesnoOkoncaniKursevi().AddElement(&kurs, bodovi);
        }
    }

    //vector<Polaznik> listaPolaznika = mostar.GetPolazniciByPredavac("Jasmin Azemovic", SoftwareEngeneeringFundamentals);
    //VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS
    vector<Polaznik> GetPolazniciByPredavac(const char* imePrezime, enumKursevi kurs) {
        vector<Polaznik> polaznici;
        for (int i = 0; i < _aplikanti.GetTrenutno(); i++) {
            if (strcmp(_aplikanti.GetElement1(i).getImePredavaca(), imePrezime) == 0 && _aplikanti.GetElement1(i).getKurs() == kurs) {
                polaznici.push_back(*_aplikanti.GetElement2(i));
            }
        }
        return polaznici;
    }
};

ostream& operator<<(ostream& COUT, const SkillsCentar& obj) {
    /*
        string _nazivCentra;
    vector<Kurs> _kursevi;//KURSEVI KOJE NUDI ODREDJENI CENTAR
    Kolekcija<Kurs, Polaznik*, 150> _aplikanti;
    */
    COUT << "Naziv centra: " << obj.getNazivCentra() << endl;
    COUT << "Kursevi koje nudi centar" << crt;
    for (int i = 0; i < obj.getKursevi().size(); i++) {
        COUT << obj.getKursevi()[i] << endl;
    }
    COUT << crt << "\n";
    COUT << "Aplikanti centra: " << crt;
    //COUT << obj.getAplikanti() << endl;
    for (int i = 0; i < obj.getAplikanti().GetTrenutno(); i++) {
        COUT << obj.getAplikanti().GetElement1(i) << " " << *obj.getAplikanti().GetElement2(i) << endl;
    }
    return COUT;
}

bool ProvjeriFormatTelefona(string broj) {
    //BROJ TELEFONA TREBA BITI U FORMATU (06X)XXX-XXX 
    string stringUzorak = "\\(06\\d\\)\\d{3}\\-\\d{3}";
    regex regexUzorak(stringUzorak);
    return regex_match(broj, regexUzorak);
}


void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU
    //    RUNTIME ERROR �E BITI OZNACENO KAO "RE"
    // 3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJE�ILO GUBLJENJE URA�ENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKO�ER NALAZI U FAJLU CODE.TXT
    // 5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U
    //    TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE,
    //    POMO�NE FUNKCIJE MO�ETE IMENOVATI I DODAVATI PO �ELJI.
    // 6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNA�ENO.
    ****************************************************************************/

#pragma region TestiranjeDatuma
    Datum danas(26, 11, 2015);
    Datum sutra(danas);
    Datum prekosutra;
    prekosutra = danas;
    cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
    Kolekcija<int, int, 10> kolekcija1;
    try
    {
        for (size_t i = 0; i < kolekcija1.GetMax(); i++)
            kolekcija1.AddElement(i, i + 2);
        //FUNKCIJA TREBA BACITI IZUZETAK U SLUCAJ DA NEMA VISE PROSTORA ZA DODAVANJE NOVIH ELEMENATA
        cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
        //cout << kolekcija1.GetElement1(20) << " " << kolekcija1.GetElement2(20) << endl;
        //FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO ELEMENT NA ZAHTIJEVANOJ LOKACIJI NE POSTOJI
    }
    catch (Izuzetak& err)
    {
        cout << "Greska -> " << err << endl;
    }

    cout << kolekcija1 << endl;
    Kolekcija<int, int, 10> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;
    Kolekcija<int, int, 10> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeKursa
    Kurs sef(SoftwareEngeneeringFundamentals, "Jasmin Azemovic", Datum(28, 1, 2016), Datum(15, 2, 2016));
    cout << sef << endl;
    Kurs msql(MasteringSQL, "Adel Handzic", Datum(28, 2, 2016), Datum(15, 3, 2016));
    sef = msql;
    if (sef == msql)//KURSEVI SU ISTI AKO POSJEDUJU IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA
        cout << "ISTI SU KURSEVI" << endl;
    Kurs msql2(msql);
    cout << msql2 << endl;
#pragma endregion

#pragma region TestiranjePolaznika
    string telefon1 = "(061)111-111";
    string telefon2 = "(061)111222";
    string telefon3 = "(061)111-333";

    if (!ProvjeriFormatTelefona(telefon1))
        cout << "Broj " << telefon1 << " nije validan" << endl;
    if (!ProvjeriFormatTelefona(telefon2))
        cout << "Broj " << telefon2 << " nije validan" << endl;
    if (!ProvjeriFormatTelefona(telefon3))
        cout << "Broj " << telefon3 << " nije validan" << endl;


    Polaznik denis("Denis Music", telefon1);
    Polaznik denis2("Denis2 Music2", telefon3);

#pragma endregion

#pragma region TestiranjeCentra
    try
    {
        SkillsCentar mostar("Skills Center Mostar");
        if (mostar.ProvjeriKoliziju(sef)) //JEDAN KURS NE SMIJE POCETI DOK DRUGI TRAJE TJ. VRIJEME ODRZAVANJA I
            mostar.AddKurs(sef);          //KURSA SE NE SMIJE POKLAPAT
        if (mostar.ProvjeriKoliziju(msql))
            mostar.AddKurs(msql);
        if (mostar.ProvjeriKoliziju(msql2))
            mostar.AddKurs(msql2);
        //ONEMOGUCITI DODAVANJE IDENTICNIH KURSEVA. FUNKCIJA TREBA DA BACI IZUZETAK UKOLIKO SE POKUSA DODATI IDENTICAN KURS
        mostar.AddAplikaciju(sef, denis);
        //ONEMOGUCITI APLICIRANJE ZA KURSEVE KOJI NISU REGISTROVANI U CENTRU
        mostar.AddAplikaciju(msql, denis);
        mostar.AddAplikaciju(msql, denis);
        //ONEMOGUCITI APLICIRANJE ZA ISTI KURS. FUNKCIJA BAZA IZUZETAK
        cout << denis2 << endl;
        denis2 = denis;
        if (denis == denis2) //POLAZNICI SU ISTI AKO POSJEDUJU ISTO IME I AKO SU POHADJALI ISTE KURSEVE
            cout << "ISTI SU" << endl;

        mostar.DodajUspjesnoOkoncanKurs(1, sef, 60);
        // BROJ 1 OZNACAVA ID POLAZNIKA. FUNKCIJA JE ZADUZENA DA POLAZNIKU 
        // DODA INFORMACIJU O USPJESNO POLOZENOM KURSU KOJI JE POSLAN KAO PARAMETAR. PREDUSLOV ZA DODAVANJE JE DA JE 
        // POLAZNIK PRETHODNO APLICIRAO ZA TAJ KURS, TE DA JE NA ISPITU OSTVARIO VISE OD 55%
        mostar.DodajUspjesnoOkoncanKurs(1, msql, 83);
        vector<Polaznik> listaPolaznika = mostar.GetPolazniciByPredavac("Jasmin Azemovic", SoftwareEngeneeringFundamentals);
        //VRACA INFORMACIJE O POLAZNICIMA KOJI SU KOD ODREDJENOG PREDAVACA USPJESNO OKONCALI ODREDJENI KURS

        if (mostar.RemoveKurs(sef))//ONEMOGUCITI UKLANJANJE KURSA KOJI SU VEC PRIJAVILI NEKI OD POLAZNIKA
            cout << "Kurs " << sef << " uspjesno uklonjen iz centra " << mostar << endl;

        SkillsCentar sarajevo = mostar;
        cout << sarajevo << endl;
    }
    catch (Izuzetak& err)
    {
        cout << err << endl;
    }
#pragma endregion
    system("pause");
}
