#include <iostream>
#include <regex>
#include <vector>
#include <list>
using namespace std;

const char* crt = "\n---------------------------------------\n";

// Z0.1 
char* alociraj(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, tekst);
    return temp;
}

// Z0.2 :: funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char[]> alocirajUnique(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    unique_ptr<char[]> temp = make_unique<char[]>(size);
    strcpy_s(temp.get(), size, tekst);
    return temp;
}
// Z0.3:: Provjeriti da li su dva niza karaktera ista (po vrijednosti)
bool areEqual(const char* tekst1, const char* tekst2) {
    if (tekst1 == nullptr || tekst2 == nullptr)
        return false;
    return strcmp(tekst1, tekst2) == 0;
}


class FizikalnaVelicina abstract {
    unique_ptr<float> _vrijednost;
public:
    // Z0.4 :: getteri
    float getVrijednost() const { return (_vrijednost == nullptr) ? 0.0f : *_vrijednost; }
    // Z0.5 :: setteri
    void setVrijednost(float vrijednost) {
        if (_vrijednost == nullptr)
            _vrijednost = make_unique<float>();
        *_vrijednost = vrijednost;
    }

    // Z0.6 :: dflt ctor /user-def ctor
    FizikalnaVelicina(float vrijednost = 0.0) {
        setVrijednost(vrijednost);
    }
    // Z0.7 :: copy ctor
    FizikalnaVelicina(const FizikalnaVelicina& obj) {
        setVrijednost(obj.getVrijednost());
    }

    // Z0.8 :: operator '='
    FizikalnaVelicina& operator = (const FizikalnaVelicina& obj) {
        if (this != &obj) {
            setVrijednost(obj.getVrijednost());
        }
        return *this;
    }
    // Z0.9 :: dtor
    virtual ~FizikalnaVelicina() {}
};

enum class JedinicaUdaljenosti { m, km, er, sr, ls, au, ly };
ostream& operator << (ostream& COUT, const JedinicaUdaljenosti& obj) {
    switch (obj) {
    case JedinicaUdaljenosti::m:  COUT << "m"; break;
    case JedinicaUdaljenosti::km: COUT << "km"; break;
    case JedinicaUdaljenosti::er: COUT << "er"; break; // earth radius
    case JedinicaUdaljenosti::sr: COUT << "sr"; break; // solar radius
    case JedinicaUdaljenosti::ls: COUT << "ls"; break; // ligth second
    case JedinicaUdaljenosti::au: COUT << "au"; break; // astronomical unit
    case JedinicaUdaljenosti::ly: COUT << "ly"; break; // ligth year
    default: break;
    }
    return COUT;
}

class Udaljenost : public FizikalnaVelicina {
    unique_ptr<JedinicaUdaljenosti> _jedinica;
public:
    // Z1.1 :: getter
    JedinicaUdaljenosti getJedinica() const { return (_jedinica == nullptr) ? JedinicaUdaljenosti::m : *_jedinica; }
    // Z1.2 :: setter
    void setJedinica(JedinicaUdaljenosti jedinica) {
        if (_jedinica == nullptr)
            _jedinica = make_unique<JedinicaUdaljenosti>();
        *_jedinica = jedinica;
    }
    // Z1.3 :: dflt / user-def ctor
    Udaljenost(float vrijednost = 0.0f, JedinicaUdaljenosti jedinica = JedinicaUdaljenosti::m)
        :FizikalnaVelicina(vrijednost) {
        setJedinica(jedinica);
    }
    // Z1.4 :: copy ctor
    Udaljenost(const Udaljenost& obj)
        :FizikalnaVelicina(obj) {
        setJedinica(obj.getJedinica());
    }
    // Z1.5 :: operator '='
    Udaljenost& operator = (const Udaljenost& obj) {
        if (this != &obj) {
            (FizikalnaVelicina&)(*this) = obj;
            setJedinica(obj.getJedinica());
        }
        return *this;
    }
    // Z1.6 :: dtor
    ~Udaljenost() {
    }

};
// Z1.7 :: ispisati vrijednost pa jedinicu [npr. "4 m", "20 km, "3 ly", ...]
ostream& operator <<(ostream& COUT, const Udaljenost& obj) {
    COUT << obj.getVrijednost() << " " << obj.getVrijednost();
    return COUT;
}
// Z1.8 :: porediti sva obiljezja
bool operator == (const Udaljenost& u1, const Udaljenost& u2) {
    return u1.getJedinica() == u2.getJedinica() && u1.getVrijednost() == u2.getVrijednost();
}
bool operator != (const Udaljenost& u1, const Udaljenost& u2) {
    return !(u1 == u2);
}

enum class JedinicaMase { kg, EM, SM }; // EM- Earth Mass, SM - Solar Mass
// Z1.9
ostream& operator << (ostream& COUT, const JedinicaMase& obj) {
    switch (obj) {
    case JedinicaMase::kg: COUT << "kg"; break;
    case JedinicaMase::EM: COUT << "EM"; break;
    case JedinicaMase::SM: COUT << "SM"; break;
    default:
        break;
    }
    return COUT;
}

class Masa : public FizikalnaVelicina {
    unique_ptr<JedinicaMase> _jedinica;
public:
    // Z1.10 :: getter
    JedinicaMase getJedinica() const { return (_jedinica == nullptr) ? JedinicaMase::kg : *_jedinica; }
    // Z1.11 :: setter
    void setJedinica(JedinicaMase jedinica) {
        if (_jedinica == nullptr)
            _jedinica = make_unique<JedinicaMase>();
        *_jedinica = jedinica;
    }
    // Z1.12 :: dflt / user-def ctor
    Masa(float vrijednost = 0.0f, JedinicaMase jedinica = JedinicaMase::kg) :FizikalnaVelicina(vrijednost) {
        setJedinica(jedinica);
    }
    // Z1.13 :: copy ctor
    Masa(const Masa& obj) :FizikalnaVelicina(obj) {
        setJedinica(obj.getJedinica());
    }
    // Z1.14 :: operator '='
    Masa& operator = (const Masa& obj) {
        if (this != &obj) {
            (FizikalnaVelicina&)(*this) = obj;
            setJedinica(obj.getJedinica());
        }
        return *this;
    }
    // Z1.15 :: dtor
    ~Masa() {
    }
};
// Z1.16
ostream& operator <<(ostream& COUT, const Masa& obj) {
    COUT << obj.getVrijednost() << " " << obj.getJedinica();
    return COUT;
}
// Z1.17
bool operator == (const Masa& m1, const Masa& m2) {
    return m1.getJedinica() == m2.getJedinica() && m1.getVrijednost() == m2.getVrijednost();
}
bool operator != (const Masa& m1, const Masa& m2) {
    return !(m1 == m2);
}

// planete, zvijezde, meteori, komete, nebule, crne rupe, ...
class NebeskoTijelo {
    string _naziv;
    unique_ptr<Udaljenost> _poluprecnik;
    unique_ptr<Masa> _masa;
    string* _sastav = nullptr;
public:
    // Z2.1 :: getteri
    string getNaziv() const { return _naziv; }
    Udaljenost getPoluprecnik() const { return (_poluprecnik == nullptr) ? Udaljenost() : *_poluprecnik; }
    Masa getMasa() const { return (_masa == nullptr) ? Masa() : *_masa; }
    string getSastav() const { return (_sastav == nullptr) ? "" : *_sastav; }

    // Z2.2 :: setteri
    void setNaziv(string naziv) {
        _naziv = naziv;
    }
    void setPoluprecnik(Udaljenost poluprecnik) {
        if (_poluprecnik == nullptr)
            _poluprecnik = make_unique<Udaljenost>();
        *_poluprecnik = poluprecnik;
    }
    void setMasa(Masa masa) {
        if (_masa == nullptr)
            _masa = make_unique<Masa>();
        *_masa = masa;
    }
    void setSastav(string sastav) {
        if (_sastav == nullptr)
            _sastav = new string;
        *_sastav = sastav;
    }
    // Z2.3 :: dflt ctor
    NebeskoTijelo() {
        setNaziv("");
        setPoluprecnik(Udaljenost());
        setMasa(Masa());
        setSastav("");
    }
    // Z2.4 :: user-def ctor
    NebeskoTijelo(const char* naziv, Udaljenost poluprecnik, Masa masa, const char* sastav) {
        setNaziv(naziv);
        setPoluprecnik(poluprecnik);
        setMasa(masa);
        setSastav(sastav);
    }
    // Z2.5 :: copy ctor
    NebeskoTijelo(const NebeskoTijelo& obj) {
        setNaziv(obj.getNaziv());
        setPoluprecnik(obj.getPoluprecnik());
        setMasa(obj.getMasa());
        setSastav(obj.getSastav());
    }

    // Z2.6 :: operator '='
    NebeskoTijelo& operator = (const NebeskoTijelo& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setPoluprecnik(obj.getPoluprecnik());
            setMasa(obj.getMasa());
            setSastav(obj.getSastav());
        }
        return *this;
    }
    // Z2.7 :: ispis
    virtual void ispis() {
        cout << crt << "Naziv tijela: " << _naziv << endl;
        cout << "Poluprecnik: " << getPoluprecnik() << endl;
        cout << "Masa: " << getMasa() << endl;
        cout << "Sastav: " << getSastav() << crt;
    }
    // Z2.8 :: dtor
    virtual ~NebeskoTijelo() {
        delete _sastav; _sastav = nullptr;
    }
};
// Z2.9 :: operator '=='
bool operator == (const NebeskoTijelo& n1, const NebeskoTijelo& n2) {
    return n1.getNaziv() == n2.getNaziv() && n1.getMasa() == n2.getMasa() && n1.getPoluprecnik() == n2.getPoluprecnik() && n1.getSastav() == n2.getSastav();
    return false;
}
bool operator != (const NebeskoTijelo& n1, const NebeskoTijelo& n2) {
    return !(n1 == n2);
}

class Planeta : public NebeskoTijelo {
    Udaljenost _udaljenostOdSunca; // u AJ (astronomska jedinica) // Npr. 1.5 AJ
    vector<string>* _sateliti = nullptr;
public:

    // Z3.1 :: getteri
    Udaljenost getUdaljenostOdSunca() const { return _udaljenostOdSunca; }
    vector<string> getSateliti() const { return (_sateliti == nullptr) ? vector<string>() : *_sateliti; }

    // Z3.2:: setteri
    void setUdaljenostOdSunca(Udaljenost udaljenost) {
        _udaljenostOdSunca = udaljenost;
    }
    void setSateliti(vector<string> sateliti) {
        if (_sateliti == nullptr)
            _sateliti = new vector<string>();
        *_sateliti = sateliti;
    }
    Planeta() {
        _sateliti = new vector<string>;
    }
    // Z3.3 :: user-def ctor
    Planeta(const char* naziv, Udaljenost radijus, Masa masa, const char* sastav, Udaljenost doSunca, vector<string> sateliti) :NebeskoTijelo(naziv, radijus, masa, sastav) {
        setUdaljenostOdSunca(doSunca);
        setSateliti(sateliti);
    }
    // Z3.4 :: copy ctor
    Planeta(const Planeta& obj) :NebeskoTijelo(obj) {
        setUdaljenostOdSunca(obj.getUdaljenostOdSunca());
        setSateliti(obj.getSateliti());
    }
    // Z3.5 :: operator '='
    Planeta& operator =(const Planeta& obj) {
        if (this != &obj) {
            (NebeskoTijelo&)(*this) = obj;
            setUdaljenostOdSunca(obj.getUdaljenostOdSunca());
            setSateliti(obj.getSateliti());
        }
        return *this;
    }
    // Z3.6 :: dodavanje novog satelita (mjeseca)
    void operator +=(string satelit) {
        _sateliti->push_back(satelit);
    }
    // Z3.7 :: ispisati sve atribute [ukljucujuci i atribute bazne klase]
    void ispis() {
        NebeskoTijelo::ispis();
        cout << "Udaljenost od sunca: " << _udaljenostOdSunca << endl;
        cout << "Sateliti:" << endl;
        for (int i = 0; i < _sateliti->size(); i++) {
            cout << "\t" << _sateliti->at(i) << endl;
        }
    }
    // Z3.8 :: dtor
    ~Planeta() {
        delete _sateliti; _sateliti = nullptr;
    }
};
// Z3.9 :: porediti sva obiljezja
bool operator == (const Planeta& p1, const Planeta& p2) {
    if ((NebeskoTijelo&)(p1) != (NebeskoTijelo&)(p2) || p1.getUdaljenostOdSunca() != p2.getUdaljenostOdSunca() || p1.getSateliti().size() != p2.getSateliti().size())
        return false;
    for (int i = 0; i < p1.getSateliti().size(); i++) {
        if (p1.getSateliti().at(i) != p2.getSateliti().at(i))
            return false;
    }
    return true;
}
bool operator != (const Planeta& p1, const Planeta& p2) {
    return !(p1 == p2);
}

enum class Boja { Crvena, Zuta, Plava, Bijela };
// Z4.0 :: operator '<<' za ispis boje
ostream& operator <<(ostream& COUT, const Boja& obj) {
    switch (obj) {
    case Boja::Crvena: COUT << "Crvena"; break;
    case Boja::Zuta: COUT << "Zuta"; break;
    case Boja::Plava: COUT << "Plava"; break;
    case Boja::Bijela: COUT << "Bijela"; break;
    default:
        break;
    }
    return COUT;
}
enum class Velicina { Patuljak, Div, Superdiv };
ostream& operator <<(ostream& COUT, const Velicina& obj) {
    switch (obj) {
    case Velicina::Patuljak:COUT << "Patuljak"; break;
    case Velicina::Div:COUT << "Div"; break;
    case Velicina::Superdiv:COUT << "Superdiv"; break;
    default:
        break;
    }
    return COUT;
}

class Zvijezda : public NebeskoTijelo {
    unique_ptr<float> _absolutnaMagnituda; // npr. 4.83 
    unique_ptr<int> _povrsinskaTemperatura; // u kelvinima
    pair<Boja, Velicina> _klasifikacija;
    list<Planeta> _planetarniSistem;
public:
    // Z4.1 :: getteri
    float getAbsolutnaMagnituda() const { return (_absolutnaMagnituda == nullptr) ? 0.0f : *_absolutnaMagnituda; }
    int getTemperatura() const { return (_povrsinskaTemperatura == nullptr) ? 0 : *_povrsinskaTemperatura; }
    Boja getBoja() const { return _klasifikacija.first; }
    Velicina getVelicina() const { return _klasifikacija.second; }
    list<Planeta> getPlanetarniSistem() const { return _planetarniSistem; }
    list<Planeta>& refGetPlanetarniSistem() { return _planetarniSistem; }

    // 4.2 :: setteri
    void setAbsolutnaMagnituda(float absolutnaMagnituda) {
        if (_absolutnaMagnituda == nullptr)
            _absolutnaMagnituda = make_unique<float>();
        *_absolutnaMagnituda = absolutnaMagnituda;
    }
    void setTemperatura(int temperatura) {
        if (_povrsinskaTemperatura == nullptr)
            _povrsinskaTemperatura = make_unique<int>();
        *_povrsinskaTemperatura = temperatura;
    }
    void setBoja(Boja boja) {
        _klasifikacija.first = boja;
    }
    void setVelicina(Velicina velicina) {
        _klasifikacija.second = velicina;
    }
    void setPlanetarniSistem(list<Planeta> planete) {
        _planetarniSistem = planete;
    }
    // Z4.3 :: dflt ctor
    Zvijezda() {}
    // Z4.4 :: user-def ctor
    Zvijezda(const char* nz, Udaljenost pp, Masa masa, const char* sstv, float absMag, int tmp, pair<Boja, Velicina> klas) :
        NebeskoTijelo(nz, pp, masa, sstv) {
        setAbsolutnaMagnituda(absMag);
        setTemperatura(tmp);
        setBoja(klas.first);
        setVelicina(klas.second);
    }
    // Z4.5 :: copy ctor
    Zvijezda(const Zvijezda& obj) : NebeskoTijelo(obj) {
        setAbsolutnaMagnituda(obj.getAbsolutnaMagnituda());
        setTemperatura(obj.getTemperatura());
        setBoja(obj.getBoja());
        setVelicina(obj.getVelicina());
        setPlanetarniSistem(obj.getPlanetarniSistem());
    }

    // Z4.6 :: dodaj planetu
    void dodajPlanetu(Planeta p) {
        _planetarniSistem.push_back(p);
    }
    // Z4.7 :: operator '='
    Zvijezda& operator =(const Zvijezda& obj) {
        if (this != &obj) {
            (NebeskoTijelo&)(*this) = obj;
            setAbsolutnaMagnituda(obj.getAbsolutnaMagnituda());
            setTemperatura(obj.getTemperatura());
            setBoja(obj.getBoja());
            setVelicina(obj.getVelicina());
            setPlanetarniSistem(obj.getPlanetarniSistem());
        }
        return *this;
    }
    // Z4.8 :: ispisati sve atribute [ukljucujuci i atribute bazne klase]
    void ispis() {
        NebeskoTijelo::ispis();
        cout << "Absolutna magnituda: " << getAbsolutnaMagnituda() << endl;
        cout << "Temperatura: " << getTemperatura() << endl;
        cout << "Boja: " << getBoja() << endl;
        cout << "Velicina: " << getVelicina() << endl;
        cout << "Planetarni sistem: " << endl;
        list<Planeta>::iterator it;
        for (it = _planetarniSistem.begin(); it != _planetarniSistem.end(); it++) {
            it->ispis();
        }
    }
    // Z4.9 :: dtor
    ~Zvijezda() {}
};
// Z4.10 :: porediti sva obiljezja
bool operator == (const Zvijezda& z1, const Zvijezda& z2) {
    if ((NebeskoTijelo&)(z1) != (NebeskoTijelo&)(z2) || z1.getAbsolutnaMagnituda() != z2.getAbsolutnaMagnituda() || z1.getTemperatura() != z2.getTemperatura() || z1.getBoja() != z2.getBoja() || z1.getVelicina() != z2.getVelicina() || z1.getPlanetarniSistem().size() != z2.getPlanetarniSistem().size())
        return false;
    list<Planeta>::iterator itZ1;
    list<Planeta>::iterator itZ2;
    for (itZ1 = z1.getPlanetarniSistem().begin(), itZ2 = z2.getPlanetarniSistem().begin(); itZ1 != z1.getPlanetarniSistem().end(); itZ1++, itZ2++) {
        if (*itZ1 != *itZ2)
            return false;
    }
    return true;
}
bool operator != (const Zvijezda& z1, const Zvijezda& z2) {
    return !(z1 == z2);
}
// Z4.11 :: funkcija za provjeru validnosti broja telefona
// Neka su dozvoljeni formati -->
// +38762111222 
// +387 62 111-222
// +(387)62 111-222
bool isValidNumber(string brojTelefona) {
    return regex_match(brojTelefona, regex("\\+(\\d{3}|\\(\\d{3}\\)|\\d{3}\\s)?\\d(\\s)?\\d{3}(\\-)?\\d{3}"));
}
// Z4.12 :: funkcija za provjeru validnosti emaila
// U prvom dijelu email-a, znak '.' ili '_' smije se pojaviti maksimalno jednom (ostali specijalni znakovi su zabranjeni)
// Prvo dio emaila ne smije pocinjati niti zavrsavati znakom '.' ili '_'
// Mora postojati znak '@'
// Zavrsetak mora biti validna domena tipa: gmail.com, bih.net, outlook.com, edu.fit.ba
bool isValidEmail(string email) {
    return regex_match(email, regex("[a-z]+(\\._)?[a-z]+@([a-z]+\\.)?[a-z]+\\.[a-z]+"));
}


class Observatorija {
    unique_ptr<char[]> _naziv;
    const char* _lokacija = nullptr;
    string _kontaktTelefon = "";
    string* _email = nullptr;
    vector<NebeskoTijelo*> _katalog;
public:
    // Z5.1 :: getteri
    const char* getNaziv() const { return (_naziv == nullptr) ? "" : _naziv.get(); }
    const char* getLokacija() const { return (_lokacija == nullptr) ? "" : _lokacija; }
    string getKontaktTelefon() const { return _kontaktTelefon; }
    string getEmail() const { return (_email == nullptr) ? "" : *_email; }
    NebeskoTijelo* getNebeskoTijelo(int index) const { return _katalog[index]; }
    vector<NebeskoTijelo*> getKatalog() const { return _katalog; }
    // Z5.2 :: setteri
    void setNaziv(const char* naziv) {
        _naziv = alocirajUnique(naziv);
    }
    void setLokacija(const char* lokacija) {
        delete[] _lokacija;
        _lokacija = alociraj(lokacija);
    }
    void setKontaktTelefon(string telefon) {
        _kontaktTelefon = telefon;
        //_kontaktTelefon = isValidNumber(telefon) ? telefon : "NOT SET";
    }
    void setEmail(string email) {
        if (_email == nullptr)
            _email = new string;
        *_email = email;
        //*_email = isValidEmail(email) ? email : "notSet@edu.fit.ba";
    }
    void setKatalog(vector<NebeskoTijelo*> katalog) {
        _katalog = katalog;
    }
    // Z5.3 :: dflt ctor
    Observatorija() {}
    // Z5.4 :: user-def ctor
    Observatorija(const char* naziv, const char* lokacija, string kontaktTelefon, string email, vector<NebeskoTijelo*> katalog) {
        setNaziv(naziv);
        setLokacija(lokacija);
        setKontaktTelefon(kontaktTelefon);
        setEmail(email);
        setKatalog(katalog);
    }
    // Z5.5 :: copy ctor
    Observatorija(const Observatorija& obj) {
        setNaziv(obj.getNaziv());
        setLokacija(obj.getLokacija());
        setKontaktTelefon(obj.getKontaktTelefon());
        setEmail(obj.getEmail());
        //setKatalog(obj.getKatalog());
        for (int i = 0; i < obj._katalog.size(); i++) {
            _katalog.push_back(new NebeskoTijelo(*obj._katalog.at(i)));
        }
    }
    // Z5.6 :: operator '='
    Observatorija& operator= (const Observatorija& obj) {
        if (this != &obj) {
            setNaziv(obj.getNaziv());
            setLokacija(obj.getLokacija());
            setKontaktTelefon(obj.getKontaktTelefon());
            setEmail(obj.getEmail());
            //setKatalog(obj.getKatalog());
            for (int i = 0; i < obj._katalog.size(); i++) {
            _katalog.push_back(new NebeskoTijelo(*obj._katalog.at(i)));
            }
        }
        return *this;
    }

    // Z5.7 :: metoda za dodavanje nebeskog tijela (planeta, zvijezda, ...)
    template<class T>
    void dodajNebeskoTijelo(T nebeskoTijelo) {
        _katalog.push_back(new T(nebeskoTijelo));
    }
    // Z5.8 :: dtor
    ~Observatorija() {
        delete _email; _email = nullptr;
        for (int i = 0; i < _katalog.size(); i++) {
            delete _katalog[i];
            _katalog[i] = nullptr;
        }
    }
};
// Z5.9 :: operator '<<'
ostream& operator <<(ostream& COUT, const Observatorija& obj) {
    COUT << crt << "OBSERVATORIJA" << crt;
    COUT << "Naziv: " << obj.getNaziv() << endl;
    COUT << "Lokacija: " << obj.getLokacija() << endl;
    COUT << "Email: " << obj.getEmail() << endl;
    COUT << "Kontakt telefon: " << obj.getKontaktTelefon() << endl;
    COUT << "Katalog: " << endl;
    for (int i = 0; i < obj.getKatalog().size(); i++) {
        obj.getKatalog().at(i)->ispis();
    }
    COUT << crt;
    return COUT;
}

void zadatak1() {
    // klasa 'Udaljenost'
    Udaljenost sirinaGalaksije; // Proxima Centauri
    sirinaGalaksije.setVrijednost(130000.0f);
    sirinaGalaksije.setJedinica(JedinicaUdaljenosti::ly);
    cout << "Sirina galaksije Mlijecni put: " << sirinaGalaksije << endl;
    // kopiranje vrijednosti
    Udaljenost u1(sirinaGalaksije.getVrijednost(), sirinaGalaksije.getJedinica());
    Udaljenost u2(u1);
    Udaljenost u3;
    u3 = u2;
    // klasa 'Masa'
    Masa masaSjevernjace;
    masaSjevernjace.setJedinica(JedinicaMase::SM);
    masaSjevernjace.setVrijednost(5.4f);
    cout << "Masa zvijezde Polaris: " << masaSjevernjace << endl;
    // kopiranje vrijednosti
    Masa m1(masaSjevernjace.getVrijednost(), masaSjevernjace.getJedinica());
    Masa m2(m1);
    Masa m3;
    m3 = m2;
    cout << endl << "Dealokacija..." << endl;
}
void zadatak2() {
    NebeskoTijelo sagittariusA;
    sagittariusA.setNaziv("Sagittarius A* - Supermasivna crna rupa");
    sagittariusA.setPoluprecnik(Udaljenost(22000000.0f, JedinicaUdaljenosti::km));
    sagittariusA.setMasa(Masa(4.15e6, JedinicaMase::SM));
    sagittariusA.setSastav("vodik, helij");
    sagittariusA.ispis();
    // kopiranje vrijednosti
    NebeskoTijelo t1(sagittariusA);
    NebeskoTijelo t2;
    t2 = t1;
    cout << endl << "Dealokacija..." << endl;
}
void zadatak3() {
    Planeta uran;
    uran.setNaziv("Uran");
    uran.setPoluprecnik(Udaljenost(4.007f, JedinicaUdaljenosti::er));
    uran.setMasa(Masa(15.54f, JedinicaMase::EM));
    uran.setSastav("vodik, helij, voda, metan, amonijak");
    uran.setUdaljenostOdSunca(Udaljenost(19.21f, JedinicaUdaljenosti::au));
    uran += "Miranda";
    uran += "Umbriel";
    uran += "Titania";
    uran += "Oberon";
    // kopiranje vrijednosti
    Planeta p1(uran);
    Planeta p3 = p1;
    p3.ispis();
    cout << endl << "Dealokacija..." << endl;
}
void zadatak4() {
    Zvijezda vyCma;
    vyCma.setNaziv("VY Canis Majoris");
    vyCma.setPoluprecnik(Udaljenost(2069.0f, JedinicaUdaljenosti::sr));
    vyCma.setMasa(Masa(17.5, JedinicaMase::SM));
    vyCma.setSastav("vodik, helij, litij, ...");
    vyCma.setAbsolutnaMagnituda(-0.72f);
    vyCma.setTemperatura(3490);
    vyCma.setBoja(Boja::Crvena);
    vyCma.setVelicina(Velicina::Superdiv);
    // kreiranje planeta
    Planeta p1("CMa-1", Udaljenost(0.5f, JedinicaUdaljenosti::er), Masa(1.3f, JedinicaMase::EM), "zeljezo", Udaljenost(0.7f, JedinicaUdaljenosti::au), {});
    Planeta p2("CMa-2", Udaljenost(0.7f, JedinicaUdaljenosti::er), Masa(2.0f, JedinicaMase::EM), "zeljezo", Udaljenost(5.3f, JedinicaUdaljenosti::au), {});
    // dodavanje planeta u planetarni sistem [vyCma]
    vyCma.dodajPlanetu(p1);
    vyCma.dodajPlanetu(p2);
    // kopiranje vrijednosti
    Zvijezda z1(vyCma);
    Zvijezda z3;
    z3 = z1;
    z3.ispis();
    cout << endl << "Dealokacija..." << endl;
}
void zadatak5() {
    Observatorija zvjezdarnica;
    zvjezdarnica.setNaziv("Zvjezdarnica");
    zvjezdarnica.setLokacija("Sarajevo, BiH");
    zvjezdarnica.setEmail("zvjezdarnica_ba@gmail.com");
    zvjezdarnica.setKontaktTelefon("+(387)62 546-241");
    NebeskoTijelo messier61;
    messier61.setNaziv("Messier 61 - Supermasivna crna rupa");
    messier61.setPoluprecnik(Udaljenost(133000000.0f, JedinicaUdaljenosti::km));
    messier61.setMasa(Masa(70.15e6, JedinicaMase::SM));
    messier61.setSastav("vodik, helij");
    Planeta nibiru;
    nibiru.setNaziv("Nibiru - planeta Anunnakija");
    nibiru.setPoluprecnik(Udaljenost(2.607f, JedinicaUdaljenosti::er));
    nibiru.setMasa(Masa(21.3f, JedinicaMase::EM));
    nibiru.setSastav("voda, zeljezo, amonijak");
    nibiru.setUdaljenostOdSunca(Udaljenost(10.3f, JedinicaUdaljenosti::au));
    nibiru.setSateliti({});
    Zvijezda uyScuti;
    uyScuti.setNaziv("UY Scuti");
    uyScuti.setPoluprecnik(Udaljenost(3500.0f, JedinicaUdaljenosti::sr));
    uyScuti.setMasa(Masa(19.45f, JedinicaMase::SM));
    uyScuti.setSastav("vodik, helij");
    uyScuti.setAbsolutnaMagnituda(-0.69f);
    uyScuti.setTemperatura(4150);
    uyScuti.setBoja(Boja::Crvena);
    uyScuti.setVelicina(Velicina::Superdiv);
    zvjezdarnica.dodajNebeskoTijelo<NebeskoTijelo>(messier61);
    zvjezdarnica.dodajNebeskoTijelo<Planeta>(nibiru);
    zvjezdarnica.dodajNebeskoTijelo<Zvijezda>(uyScuti);
    cout << "Telefon je u " << (isValidNumber(zvjezdarnica.getKontaktTelefon()) ? "validnom" : "nevalidnom") << " formatu" << endl;
    cout << "Email je u " << (isValidEmail(zvjezdarnica.getEmail()) ? "validnom" : "nevalidnom") << " formatu" << endl;
    // kopiranje vrijednosti
    Observatorija o1(zvjezdarnica);
    Observatorija o2;
    o2 = o1;
    cout << o2 << endl;
    cout << endl << "Dealokacija..." << endl;
}

void menu() {
    int nastaviDalje = 1;
    while (nastaviDalje == 1) {
        int izbor = 0;
        do {
            system("cls");
            cout << "::Zadaci::" << endl;
            cout << "(1) Zadatak 1" << endl;
            cout << "(2) Zadatak 2" << endl;
            cout << "(3) Zadatak 3" << endl;
            cout << "(4) Zadatak 4" << endl;
            cout << "(5) Zadatak 5" << endl;
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 5);
        switch (izbor) {
        case 1: zadatak1(); cout << "Zadatak 1. Done." << endl; break;
        case 2: zadatak2(); cout << "Zadatak 2. Done." << endl; break;
        case 3: zadatak3(); cout << "Zadatak 3. Done." << endl; break;
        case 4: zadatak4(); cout << "Zadatak 4. Done." << endl; break;
        case 5: zadatak5(); cout << "Zadatak 5. Done." << endl; break;
        default:break;
        }
        do {
            cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
            cin >> nastaviDalje;
        } while (nastaviDalje != 0 && nastaviDalje != 1);
    }
}
int main() {
    menu();
    return 0;
}