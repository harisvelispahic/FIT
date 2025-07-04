#include <iostream>
#include <vector>
#include <regex>

using namespace std;

char* alocirajTekst(const char* source) {
    if (source == nullptr)
        return nullptr;
    int size = strlen(source) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, source);
    return temp;
}

bool ProvjeriValidnostBrojaTelefona(string telefon)//globalna funkcija
{
    //broj telefona treba biti u formatu: +387(61)-222-333
    string pattern = "\\+\\d{3}\\(\\d{2}\\)-\\d{3}-\\d{3}";
    regex regexPattern(pattern);
    return regex_match(telefon, regexPattern);
}

enum Predmeti { Matematika, Historija, Geografija, Hemija, Biologija, Engleski, Muzicko, Fizicko };
int brojaciZaPredmete[8] = { 0 };

enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
const char* ispisPredmeti[] = { "Matematika", "Historija", "Geografija", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
const char* ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };

const char* crt = "\n--------------------------------------\n";
template<class T1, class T2>
class Kolekcija
{
    T1* _elementi1 = nullptr;
    T2* _elementi2 = nullptr;
    int _trenutno;
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
    ~Kolekcija()
    {
        delete[] _elementi1; _elementi1 = nullptr;
        delete[] _elementi2; _elementi2 = nullptr;
    }

    T1* getElementi1() const { return _elementi1; }
    T2* getElementi2() const { return _elementi2; }
    int GetTrenutno() const { return _trenutno; }

    void setElementi(int trenutno=0,T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
        delete[] _elementi1;
        delete[] _elementi2;

        _trenutno = 0;

        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                AddElement(elementi1[i], elementi2[i]);
            }
        }
    }

    void AddElement(const T1& el1, const T2& el2) {
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

    void RemoveElement(int index) {
        if (index < 0 || index >= _trenutno) {
            throw exception("Indeks van granica");
            return;
        }
        for (int i = index; i < _trenutno - 1; i++) {
            _elementi1[i] = _elementi1[i + 1];
            _elementi2[i] = _elementi2[i + 1];
        }
        _trenutno--;
    }
    
    T1& GetElement1(int index) const {
        if (index < 0 || index >= _trenutno) {
            throw exception("Indeks van granica");
            //return;
        }
        return _elementi1[index];
    }
    T2& GetElement2(int index) const {
        if (index < 0 || index >= _trenutno) {
            throw exception("Indeks van granica");
            //return;
        }
        return _elementi2[index];
    }

    static bool checkIfKolekcijaContains(Kolekcija<T1, T2> kolekcija, T1 el1, T2 el2) {
        for (int i = 0; i < kolekcija.GetTrenutno(); i++) {
            if (kolekcija.getElementi1()[i] == el1 && kolekcija.getElementi2()[i] == el2)
                return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& COUT, const Kolekcija<T1, T2>& obj) {
        for (int i = 0; i < obj.GetTrenutno(); i++) {
            COUT << obj.getElementi1()[i] << " " << obj.getElementi2()[i] << endl;
        }
        return COUT;
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

    Datum(const Datum& obj)
    {
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

    int getDan() const { return(_dan == nullptr) ? 1 : *_dan; }
    int getMjesec() const { return(_mjesec == nullptr) ? 1 : *_mjesec; }
    int getGodina() const { return(_godina == nullptr) ? 2000 : *_godina; }

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

    friend ostream& operator<< (ostream& COUT, const Datum& obj)
    {
        COUT << obj.getDan() << "/" << obj.getMjesec() << "/" << obj.getGodina();
        return COUT;
    }
};

bool operator == (const Datum& d1, const Datum& d2) {
    return d1.getDan() == d2.getDan() &&
        d1.getMjesec() == d2.getMjesec() &&
        d1.getGodina() == d2.getGodina();
}
bool operator != (const Datum& d1, const Datum& d2) {
    return !(d1 == d2);
}
class Osoba
{
protected:
    char* _imePrezime = nullptr;
    Datum* _datumRodjenja = nullptr;
    string _brojTelefona;
public:
    Osoba(const char* imePrezime = "", Datum datum = Datum(), string brojTelefona = "")
    {
        setImePrezime(imePrezime);
        setDatumRodjenja(datum);
        setBrojTelefona(brojTelefona);      // mozda ne treba
    }
    Osoba(const Osoba& obj)
    {
        setImePrezime(obj.getImePrezime());
        setDatumRodjenja(obj.getDatumRodjenja());
        setBrojTelefona(obj.getBrojtelefona());
    }
    Osoba& operator=(const Osoba& obj)
    {
        if (this != &obj) {
            setImePrezime(obj.getImePrezime());
            setDatumRodjenja(obj.getDatumRodjenja());
            setBrojTelefona(obj.getBrojtelefona());
        }
        return *this;
    }
    ~Osoba() { 
        delete[]_imePrezime; _imePrezime = nullptr;    
        delete _datumRodjenja; _datumRodjenja = nullptr;
    }

    const char* getImePrezime() const { return (_imePrezime == nullptr) ? "" : _imePrezime; }
    Datum getDatumRodjenja() const { return (_datumRodjenja == nullptr) ? Datum() : *_datumRodjenja; }
    string getBrojtelefona() const { return _brojTelefona; }

    void setImePrezime(const char* imePrezime) {
        delete[] _imePrezime;
        _imePrezime = alocirajTekst(imePrezime);
    }

    void setDatumRodjenja(Datum datumRodjenja) {
        if (_datumRodjenja == nullptr)
            _datumRodjenja = new Datum;
        *_datumRodjenja = datumRodjenja;
    }

    bool setBrojTelefona(string brojTelefona)
    {
        if (ProvjeriValidnostBrojaTelefona(brojTelefona))
        {
            _brojTelefona = brojTelefona;
            return true;
        }
        return false;
    }

};



class Nastavnik :public Osoba
{
    Kolekcija<Predmeti, Razredi>* _predmetiRazredi = nullptr;

public:

    Nastavnik(const char* imePrezime = "---", Datum datumRodjenja = Datum(), string brojtelefona = "")
    : Osoba(imePrezime, datumRodjenja, brojtelefona)
    { 
        setPredmetiRazredi(Kolekcija<Predmeti, Razredi>());
    }

    Nastavnik(const Nastavnik& obj) : Osoba(obj.getImePrezime(), obj.getDatumRodjenja(), obj.getBrojtelefona())
    { 
        setPredmetiRazredi(obj.getPredmetiRazredi());
    }

    Nastavnik& operator=(const Nastavnik& obj) {
        if (this != &obj) {
            (Osoba&)(*this) = obj;
            setPredmetiRazredi(obj.getPredmetiRazredi());
        }
        return *this;
    }

    /*Kolekcija<Predmeti, Razredi> getPredmetiRazredi() const { return (_predmetiRazredi == nullptr) ? Kolekcija<Predmeti, Razredi>() : *_predmetiRazredi; }*/
    Kolekcija<Predmeti, Razredi>& getPredmetiRazredi() const { return *_predmetiRazredi; }
    void setPredmetiRazredi(Kolekcija<Predmeti, Razredi> predmetiRazredi) {
        if (_predmetiRazredi == nullptr)
            _predmetiRazredi = new Kolekcija<Predmeti, Razredi>;
        *_predmetiRazredi = predmetiRazredi;
    }


    bool provjeriDaLiSePredmetNalaziUKolekciji(Kolekcija<Predmeti, Razredi>& kolekcija, Predmeti predmet) {

    }

    /*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA
    RAZREDA (NA DVIJE RAZLICITE GODINE)*/
    bool AddPredmetRazred(Predmeti predmet, Razredi razred) {
        // Kolekcija<Predmeti, Razredi>* _predmetiRazredi = nullptr;
        /*
        enum Predmeti { Matematika, Historija, Geografija, Hemija, Biologija, Engleski, Muzicko, Fizicko };
        enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
        */
        for (int i = 0; i < _predmetiRazredi->GetTrenutno(); i++) {
            
            if (_predmetiRazredi->getElementi1()[i] == predmet && _predmetiRazredi->getElementi2()[i] == razred)
                return false;
            // retardirano postavljen uslov, ne zna se sta se trazi, nastavnik je navodno omnipotentno bice

            brojaciZaPredmete[predmet]++;
        }






        if (Kolekcija<Predmeti, Razredi>::checkIfKolekcijaContains(getPredmetiRazredi(), predmet, razred))
            return false;       // ako kolekcija sadrzi vec taj "par" elemenata, return false

        // mozda napraviti neki niz brojaca za predmete

        for (int i = 0; i < 8; i++) {           // 8 predmeta
            for (int j = 0; j < 12; j++) {      // 12 razreda

            }
            
        }
        return true;
    }
    // prvo proci kroz cijelu kolekciju i provjeriti je li element koji pokusavamo ubaciti jednak ijednom postojecem, pa ako jeste, ne dodati taj element





    bool RemovePredmetRazred(Predmeti predmet) {
        return true;
    }
};

bool operator==(const Nastavnik& n1, const Nastavnik& n2) {
    if (strcmp(n1.getImePrezime(), n2.getImePrezime()) != 0 || n1.getDatumRodjenja() != n2.getDatumRodjenja() || n1.getBrojtelefona() != n2.getBrojtelefona() || n1.getPredmetiRazredi().GetTrenutno() != n2.getPredmetiRazredi().GetTrenutno())
        return false;

    for (int i = 0; i < n1.getPredmetiRazredi().GetTrenutno(); i++) {
        if (n1.getPredmetiRazredi().getElementi1()[i] != n2.getPredmetiRazredi().getElementi1()[i] ||
            n1.getPredmetiRazredi().getElementi2()[i] != n2.getPredmetiRazredi().getElementi2()[i])
            return false;
    }
    return true;
}

class Ucenik : public Osoba
{
    int _brojUDnevniku;
    Razredi _razred;
    vector<Nastavnik*> _nastavnici;
    Kolekcija<Predmeti, int> _predmetiOcjene;
};

void main()
{
    /****************************************************************************
    // 1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
    // 2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR
    // CE BITI OZNACENO KAO "RE"
    // 3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
    // 4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
    // 5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTI�NI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U.
    // 6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
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

    kolekcija1.RemoveElement(0);//uklanja element na osnovu lokacije
    cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
    cout << kolekcija1 << endl;

    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
        cout << "ISTI BROJ ELEMENATA" << endl;
    Kolekcija<int, int> kolekcija3(kolekcija2);
    cout << kolekcija3 << crt;
#pragma endregion

#pragma region TestiranjeNastavnika
    Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
    Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
    /*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA
    RAZREDA (NA DVIJE RAZLICITE GODINE)*/
    if (jasmin.AddPredmetRazred(Matematika, I1))
        cout << "Predmeti dodan" << endl;
    if (jasmin.AddPredmetRazred(Historija, I1))
        cout << "Predmeti dodan" << endl;

    if (jasmin.AddPredmetRazred(Geografija, I1))
        cout << "Predmeti dodan" << endl;

    if (jasmin.AddPredmetRazred(Geografija, I2))
        cout << "Predmeti dodan" << endl;

    if (adel.AddPredmetRazred(Historija, III1))
        cout << "Predmeti dodan" << endl;

    if (adel.RemovePredmetRazred(Historija))
        cout << "Predmet uklonjen!" << endl;

    Nastavnik goran(adel);
    if (goran == adel)
        cout << "Nastavnici identicni" << endl;
    goran = jasmin;
    if (goran == jasmin)
        cout << "Nastavnici identicni" << endl;

    Kolekcija<Predmeti, Razredi>& predmetiRazredi = jasmin.getPredmetiRazredi();

    if (!jasmin.setBrojTelefona("+38761111222"))
        cout << "Broj telefona nije dodan!" << endl;
    if (!jasmin.setBrojTelefona("+387-61-111-222"))
        cout << "Broj telefona nije dodan!" << endl;
    if (jasmin.setBrojTelefona("+387(61)-111-222"))
        cout << "Broj telefona uspjesno dodan!" << endl;
#pragma endregion
//
//#pragma region TestiranjeUcenika
//    Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
//    Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
//    Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
//    /*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O
//    NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
//    /*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
//    if (denis.AddNastavnik(jasmin))
//        cout << "Nastavnik uspjesno dodan" << endl;
//    /*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
//    if (denis.AddNastavnik(adel))
//        cout << "Nastavnik uspjesno dodan" << endl;
//    /*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
//    if (denis.AddPredmetOcjenu(Matematika, 3))
//        cout << "Ocjena uspjesno dodana" << endl;
//    if (denis.AddPredmetOcjenu(Historija, 4))
//        cout << "Ocjena uspjesno dodana" << endl;
//
//    vector<Nastavnik*>& nastavnici = denis.getNastavnici();
//    cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;
//
//    Kolekcija<Predmeti, int>& uspjeh = denis.getPredmetiOcjene();
//    cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
//    cout << "Prosjecna ocjena kod nastavnika Jasmin Azemovic je " << denis.GetProsjekByNastavnik("Jasmin Azemovic") << endl;
//
//    Ucenik denis2(denis);
//    cout << denis2 << endl;
//
//#pragma endregion
    system("pause");
}