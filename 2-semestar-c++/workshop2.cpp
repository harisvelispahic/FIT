#include <iostream>
using namespace std;

//Koristene skracenice u komentarima
// dflt. = default
// user-def. = user-defined (korisnicki-definirano)
// ctor = constructor (konstruktor)

// Z1.0
char* alocirajTekst(const char* tekst) {
    if(tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, tekst);
    return temp;
}

class Datum
{
    //zadatak1
    int* _dan{ nullptr };
    int* _mjesec{ nullptr };
    int* _godina{ nullptr };
public:
    //konstr default
    //konstr kopije
    //konstr sa parametrima (d m g)
    //destruktor
    //get i set funkcije
    //ispis

    int getDan() const { return (_dan == nullptr) ? 1 : *_dan; }
    int getMjesec() const { return (_mjesec == nullptr) ? 1 : *_mjesec; }
    int getGodina() const { return (_godina == nullptr) ? 1970 : *_godina; }

    void setDan(int dan = 1) {
        if (_dan != nullptr)
            delete _dan;
        _dan = new int;
        *_dan = dan;
    }

    void setMjesec(int mjesec = 1) {
        if (_mjesec != nullptr)
            delete _mjesec;
        _mjesec = new int;
        *_mjesec = mjesec;
    }

    void setGodina(int godina = 1970) {
        if (_godina != nullptr)
            delete _godina;
        _godina = new int;
        *_godina = godina;
    }

    void set(Datum& datum) {
        setDan(datum.getDan());
        setMjesec(datum.getMjesec());
        setGodina(datum.getGodina());
    }

    Datum() {
        setDan();
        setMjesec();
        setGodina();
    }

    Datum(int dan, int mjesec, int godina) {
        setDan(dan);
        setMjesec(mjesec);
        setGodina(godina);
    }

    Datum(const Datum& datum) {
        setDan(datum.getDan());
        setMjesec(datum.getMjesec());
        setGodina(datum.getGodina());
    }

    ~Datum() {
        delete _dan, delete _mjesec, delete _godina;
        _dan = _mjesec = _godina = nullptr;
    }

    void unos(Datum& datum) {
        setDan(datum.getDan());
        setMjesec(datum.getMjesec());
        setGodina(datum.getGodina());
    }

    void ispis(char razmak = '.') {
        cout << getDan() << razmak << getMjesec() << razmak << getGodina() << endl;
    }
};
class Gost
{
    //zadatak2
    char* _ime{ nullptr };
    char* _prezime{ nullptr };
    char* _zemljaPorijekla{ nullptr };
    Datum* _datumRodjenja{ nullptr };
    bool* _spol{ nullptr }; //1-Muski, 0-Zenski
public:
    //konstr kopije
     //konstr sa parametrima (i p z d s)
    //destruktor
    //get i set funkcije
    //ispis

    const char* getIme() const { return (_ime == nullptr) ? "" : _ime; }
    const char* getPrezime() const { return (_prezime == nullptr) ? "" : _prezime; }
    const char* getZemljaPorijekla() const { return (_zemljaPorijekla == nullptr) ? "" : _zemljaPorijekla; }
    Datum getDatumRodjenja() const { return (_datumRodjenja == nullptr) ? Datum() : *_datumRodjenja; }
    bool getSpol() const { return (_spol == nullptr) ? true : *_spol; }       // defaultno vraca 1-Muski spol


    void setIme(const char* ime) {
        delete[] _ime;
        _ime = alocirajTekst(ime);
    }
    void setPrezime(const char* prezime) {
        delete[] _prezime;
        _prezime = alocirajTekst(prezime);
    }
    void setZemljaPorijekla(const char* zemljaPorijekla) {
        delete[] _zemljaPorijekla;
        _zemljaPorijekla = alocirajTekst(zemljaPorijekla);
    }
    void setDatumRodjenja(const Datum& datum) {                 // ovdje mora biti const, jer je kao copy constructor
        if (_datumRodjenja != nullptr)                          
            delete _datumRodjenja;
        _datumRodjenja = new Datum(datum);
    }
    void setSpol(bool spol = true) {
        if (_spol != nullptr)
            delete _spol;
        _spol = new bool{ spol };
    }

    void unos(const Gost& gost) {
        setIme(gost.getIme());
        setPrezime(gost.getPrezime());
        setZemljaPorijekla(gost.getZemljaPorijekla());
        setDatumRodjenja(gost.getDatumRodjenja());
        setSpol(gost.getSpol());
    }


    Gost() {
        setIme("Ime");
        setPrezime("Prezime");
        setZemljaPorijekla("Bosna i Hercegovina");
        setDatumRodjenja(Datum(1,1,2024));              // ovdje se salje ova instanca u setter, gdje se kopira u _datumRodjenja
        setSpol(1);                                      // nakon cega se ova instanca jednostavno brise na kraju funkcije
    }

    Gost(const char* ime, const char* prezime, const char* zemljaPorijekla, Datum datumRodjenja, bool spol) {
        setIme(ime);
        setPrezime(prezime);
        setZemljaPorijekla(zemljaPorijekla);
        setDatumRodjenja(datumRodjenja);
        setSpol(spol);
    }

    Gost(const Gost& gost) {
        setIme(gost.getIme());
        setPrezime(gost.getPrezime());
        setZemljaPorijekla(gost.getZemljaPorijekla());
        setDatumRodjenja(gost.getDatumRodjenja());
        setSpol(gost.getSpol());
    }

    ~Gost() {
        delete[] _ime, delete[] _prezime, delete[] _zemljaPorijekla;
        _ime = _prezime = _zemljaPorijekla = nullptr;
        delete _datumRodjenja;  // 
        _datumRodjenja = nullptr;
        delete _spol;
        _spol = nullptr;
    }

    void ispis() {
        cout << "Ime i prezime: " << getIme() << " " << getPrezime() << endl;
        cout << "Zemlja porijekla: " << getZemljaPorijekla() << endl;
        cout << "Datum rodjenja: "; getDatumRodjenja().ispis();
        cout << "Spol: " << ((getSpol()) ? "Muski" : "Zenski") << endl;
    }

};
class Odrediste {
    //zadatak3
    char* _naziv{ nullptr };
    int* _trajanje{ nullptr }; //u danima
    char _kratakSadrzaj[100] = "";

    int _maxOcjena; // velicina niza '_ocjene'
    int _trenutnoOcjena = 0; //brojac 
    int* _ocjene{ nullptr };//niz ocjena
public:
    // konstr kopije
    // konstr default
      //destruktor
      //get i set funkcije

    // Z3.3 :: getteri 
    const char* getNaziv() const { return (_naziv == nullptr) ? "" : _naziv; }
    int getTrajanje() const { return (_trajanje == nullptr) ? 0 : *_trajanje; }
    const char* getKratakSadrzaj() const { return _kratakSadrzaj; }

    int getTrenutnoOcjena() const { return _trenutnoOcjena; }
    int getMaxBrojOcjena() const { return _maxOcjena; }
    int* getOcjene() const { return (_ocjene == nullptr) ? nullptr : _ocjene; }
    int getOcjena(int index) const {
        if (index < 0 || index >= getTrenutnoOcjena())
            return 0;
        return _ocjene[index];
    }

    // Z3.4 :: setteri
    void setNaziv(const char* naziv) {
        delete[] _naziv;
        _naziv = alocirajTekst(naziv);
    }
    void setTrajanje(int trajanje) {
        if (_trajanje != nullptr)
            delete _trajanje;
        _trajanje = new int{ trajanje };
    }
    void setKratakSadrzaj(const char* kratakSadrzaj) {
        strcpy_s(_kratakSadrzaj, strlen(kratakSadrzaj) + 1, kratakSadrzaj);
    }

    // Z3.5 :: metoda koja brise postojeci niz i kreira novi na osnovu tri unesena parametra
    // također, metoda mora uraditi kopiranje ocjena ako je ulazni pokazivač 'ocjene' različit od NULL
    void setOcjene(int trenutnoOcjena, int maxOcjena, int* ocjene = nullptr) {
        if (trenutnoOcjena > maxOcjena) {
            cout << "Neuspjesno postavljanje niza \"ocjene\"" << endl;
            return;
        }
        delete[] _ocjene;
        _ocjene = new int[maxOcjena];                   // ?
        if (ocjene != nullptr) {
            for (int i = 0; i < trenutnoOcjena; i++) {
                _ocjene[i] = ocjene[i];
            }
        }
        _trenutnoOcjena = trenutnoOcjena;
        _maxOcjena = maxOcjena;
    }

    // Z3.6 :: metoda za kopiranje vrijednosti
    void set(const Odrediste& e) {
        setNaziv(e.getNaziv());
        setTrajanje(e.getTrajanje());
        setKratakSadrzaj(e.getKratakSadrzaj());
        setOcjene(e.getTrenutnoOcjena(), e.getMaxBrojOcjena(), e.getOcjene());
    }


    // Z3.7
    // Prosiriti niz _ocjene na sljedeci nacin:
    //  *Konstruisati novi niz velicine [_maxBrojOcjena + prosiriZa]
    //  *Kopirati vrijednosti iz starog niza u novi niz
    //  *Dealocirati stari niz
    void expandOcjene(int uvecanje) {
        int* temp = new int[getMaxBrojOcjena() + uvecanje];
        for (int i = 0; i < getTrenutnoOcjena(); i++) {
            temp[i] = _ocjene[i];
        }
        delete[] _ocjene;
        _ocjene = temp;
        _maxOcjena += uvecanje;
    }

    // Z3.8 :: metoda za dodavanje ocjene
    // Ukoliko je brojac dosao do kraja (jednak velicini niza), uraditi prosirivanje niza za 10 elemenata
    void dodajOcjenu(int ocjena) {
        if (_trenutnoOcjena >= getMaxBrojOcjena())
            expandOcjene(10);
        _ocjene[_trenutnoOcjena] = ocjena;
        _trenutnoOcjena++;
    }
    // Z3.9 :: metoda za uklanjanje zadnje ocjene
    bool ukloniZadnjuOcjenu() {
        if (_trenutnoOcjena == 0 || _maxOcjena == 0)
            return false;
        else if(_trenutnoOcjena == 1) {
            int* temp = new int;                            // inicijalizira prazan niz?
            return true;
        }
        int* temp = new int[_maxOcjena - 1];
        for (int i = 0; i < _maxOcjena - 1; i++) {
            temp[i] = _ocjene[i];
        }
        delete[] _ocjene;
        _ocjene = temp;
        _trenutnoOcjena--;
        return true;
    }
    // Z3.10
    float getProsjecnaOcjena() const {
        float sumaOcjena = 0.0f;
        for (int i = 0; i < getTrenutnoOcjena(); i++) {
            sumaOcjena += _ocjene[i];
        }
        return sumaOcjena / getTrenutnoOcjena();
    }
    // Z3.11
    void ispis() const {
        cout << "Naziv odredista: " << getNaziv() << endl;
        cout << "Trajanje (u danima): " << getTrajanje() << endl;
        cout << "Kratak sadrzaj: " << getKratakSadrzaj() << endl;
        cout << "Ocjene: ";
        for (int i = 0; i < getTrenutnoOcjena(); i++)
            cout << _ocjene[i] << " ";
        cout << endl;
    }

    Odrediste() {
        setNaziv("Naziv");
        setTrajanje(0);
        setKratakSadrzaj("-");
        setOcjene(0, 0, nullptr);
    }

    Odrediste(const char* naziv, int trajanje, const char* kratakSadrzaj, int trenutnoOcjena, int maxOcjena, int* ocjene) {
        setNaziv(naziv);
        setTrajanje(trajanje);
        setKratakSadrzaj(kratakSadrzaj);
        setOcjene(trenutnoOcjena, maxOcjena, ocjene);
    }

    Odrediste(const Odrediste& e) {
        setNaziv(e.getNaziv());
        setTrajanje(e.getTrajanje());
        setKratakSadrzaj(e.getKratakSadrzaj());
        setOcjene(e.getTrenutnoOcjena(), e.getMaxBrojOcjena(), e.getOcjene());
    }

    // Z3.12
    ~Odrediste() {
        delete[] _naziv;
        _naziv = nullptr;
        delete[] _trajanje;
        _trajanje = nullptr;
        delete[] _ocjene;
        _ocjene = nullptr;
    }

    void unos(Odrediste& e) {
        setNaziv(e.getNaziv());
        setTrajanje(e.getTrajanje());
        setKratakSadrzaj(e.getKratakSadrzaj());
        setOcjene(e.getTrenutnoOcjena(), e.getMaxBrojOcjena(), e.getOcjene());
    }
};
class PrijavaPutovanja {
    //zadatak4
    Gost* _gost{ nullptr };
    char* _komentar{ nullptr };
    float _uplaceno = 0;
public:
    Gost getGost() const { return (_gost == nullptr) ? Gost() : *_gost; }
    const char* getKomentar() const { return (_komentar == nullptr) ? "" : _komentar; }
    float getUplaceno() const { return _uplaceno; }
    


    void setGost(Gost gost) {
        if (_gost != nullptr)
            delete _gost;
        _gost = new Gost;
        _gost->unos(gost);
    }
    void setKomentar(const char* komentar) {
        _komentar = alocirajTekst(komentar);
    }
    void setUplaceno(float uplaceno) {
        _uplaceno = uplaceno;
    }

    void ispis() {
        cout << "--------------------------------------------------------------\n";
        cout << "                    PRIJAVA PUTOVANJA                         \n";
        cout << endl;
        cout << "Gost: " << endl;
        getGost().ispis();
        cout << "Komentar: " << getKomentar() << endl;
        cout << "Uplaceno: " << getUplaceno() << endl;
        cout << "--------------------------------------------------------------\n";    
    }

    PrijavaPutovanja()
    {
        setGost(Gost());
        setKomentar("-");
        setUplaceno(0.0f);
    }

    PrijavaPutovanja(Gost& gost, const char* komentar, float uplaceno)
    {
        setGost(gost);
        setKomentar(komentar);
        setUplaceno(uplaceno);
    }

    PrijavaPutovanja(const PrijavaPutovanja& prijavaputovanja)
    {
        setGost(prijavaputovanja.getGost());
        setKomentar(prijavaputovanja.getKomentar());
        setUplaceno(prijavaputovanja.getUplaceno());
    }

    ~PrijavaPutovanja() {
        delete _gost;
        _gost = nullptr;
        delete[] _komentar;
        _komentar = nullptr;
    }

    void unos(PrijavaPutovanja& prijavaputovanja) {
        setGost(prijavaputovanja.getGost());
        setKomentar(prijavaputovanja.getKomentar());
        setUplaceno(prijavaputovanja.getUplaceno());
    }
};
class Putovanje {
    //zadatak5
    char* _naziv{ nullptr };
    Datum* _datumPutovanja = nullptr;
    int _trenutnoPrijava = 0; // broj validnih elemenata (adresa dinamičkih objekata tipa Uloga).
    PrijavaPutovanja* _prijave[50] = { nullptr }; //Svi elementi (pokazivaci) se postavljaju na NULL
    Odrediste* _odredista{ nullptr }; // pokazivač na dinamički niz
public:
    const char* getNaziv() const { return(_naziv == nullptr) ? "" : _naziv; }
    Datum getDatumPutovanja() const {
        Datum temp;
        return (_datumPutovanja == nullptr) ? temp : *_datumPutovanja;
    }
    int getTrenutnoPrijava() const { return _trenutnoPrijava; }
    PrijavaPutovanja* const* getPrijave() const { return _prijave; }                    // vraca pokazivac na konstantni pokazivac koji pokazuje na "_prijave"      ?????????
    // PrijavaPutovanja* getPrijave() const { return *_prijave; }
    Odrediste* getOdrediste() const { return _odredista; }



    void setNaziv(const char* naziv) {
        _naziv = alocirajTekst(naziv);
    }
    void setDatumPutovanja(Datum datum) {               // treba li referenca ili ne ?
        if (_datumPutovanja != nullptr)
            delete[] _datumPutovanja;
        _datumPutovanja = new Datum;
        _datumPutovanja->unos(datum);
    }
    /*void setTrenutnoPrijava(int trenutnoPrijava) {        // suvisna metoda?
        _trenutnoPrijava = trenutnoPrijava;
    }*/
    void setPrijave(PrijavaPutovanja* prijave, int trenutnoPrijava) {

        if (prijave == nullptr || trenutnoPrijava <= 0)
            return;

        // dealokacija
        dealocirajPrijave();

        // kopiranje
        for (int i = 0; i < trenutnoPrijava; i++) {
            _prijave[i] = new PrijavaPutovanja();
            _prijave[i]->unos(prijave[i]);
        }
        _trenutnoPrijava = trenutnoPrijava;
    }

    void dodajPrijavu(PrijavaPutovanja& prijava) {
        if (_trenutnoPrijava >= 50)
            return;
        _prijave[_trenutnoPrijava++]->unos(prijava);
    }

    void dealocirajPrijave() {
        for (int i = 0; i < _trenutnoPrijava; i++) {
            delete _prijave[i];
            _prijave[i] = nullptr;
        }
    }

    void setOdredista(Odrediste* odredista, int velicina){
        if (odredista == nullptr)
            return;
        if (_odredista != nullptr)
            delete[] _odredista;
        _odredista = new Odrediste[velicina];
        
        for (int i = 0; i < velicina; i++) {
            _odredista[i].unos(odredista[i]);
        }
    }

    void dodajOdrediste(Odrediste& odrediste) {
        // buduci da nema neka brojacka varijabla unutar klase, nije moguce implementirati ovu metodu ???
    }


    Putovanje()
    {
        setNaziv("Naziv putovanja");
        setDatumPutovanja(Datum());
        setPrijave(nullptr, 0);
        setOdredista(nullptr, 0);
    }
    
    Putovanje(const Putovanje& putovanje)
    {
        setNaziv(putovanje.getNaziv());
        setDatumPutovanja(putovanje.getDatumPutovanja());
        setPrijave(*putovanje.getPrijave(), putovanje.getTrenutnoPrijava());                    // ?????????????    dereferenciranje const pokazivaca?
        setOdredista(nullptr, 0);
    }

    Putovanje(const char* naziv, Datum datumPutovanja, PrijavaPutovanja* prijave, int trenutnoPrijava, Odrediste* odredista, int vel)
    {
        setNaziv(naziv);
        setDatumPutovanja(datumPutovanja);
        setPrijave(prijave, trenutnoPrijava);
        setOdredista(odredista, vel);
    }
    
    ~Putovanje() {
        delete[] _naziv;
        _naziv = nullptr;
        delete _datumPutovanja;
        _datumPutovanja = nullptr;
        dealocirajPrijave();
        delete[] _odredista;
        _odredista = nullptr;
    }
    
    void ispis() {
        cout << "Naziv putovanja: " << getNaziv() << endl;
        cout << "Datum putovanja: ";
        getDatumPutovanja().ispis();
        cout << "Prijave za putovanja: " << endl;
        for (int i = 0; i < _trenutnoPrijava; i++)
            _prijave[i]->ispis();

    }
};


void zadatak1() {
    cout << "Testiranje klase 'Datum'\n\n";
    Datum novaGodina; // dflt ctor
    
    novaGodina.setDan(1);
    novaGodina.setMjesec(1);
    novaGodina.setGodina(2024);
    novaGodina.ispis();
    cout << endl;
    Datum prviFebruar(novaGodina.getDan(), novaGodina.getMjesec() + 1, novaGodina.getGodina());
    prviFebruar.ispis();
    cout << endl;

    Datum prviMart(1, 3, 2024); // user-def. ctor
    Datum prviTreceg(prviMart); // copy ctor
    prviTreceg.ispis();
    cout << endl;

    Datum danSale(1, 4, 2024);
    Datum prviCetvrtog;
    prviCetvrtog.set(danSale); // metoda 'set' (kopiranje)
    prviCetvrtog.ispis('/');
    cout << endl;
    cout << "Dealokacija ..." << endl;
    
}

void zadatak2() {
    cout << "Testiranje klase 'Gost'\n\n";
    Gost ryanGosling; // dflt ctor

    
    ryanGosling.setIme("Ryan");
    ryanGosling.setPrezime("Gosling");
    ryanGosling.setSpol(1);
    ryanGosling.setDatumRodjenja(Datum(1, 1, 1980));
    ryanGosling.setZemljaPorijekla("Kanada");
    ryanGosling.ispis();
    cout << endl;
    //
    Gost harrisonFord("Harrison", "Ford", "SAD", Datum(2, 2, 1955), 1); // user-def. ctor
    Gost michellePfeifer("Michelle", "Pfeiffer", "SAD", Datum(3, 3, 1966), 0); // user-def. ctor
    harrisonFord.ispis();
    cout << endl;
    michellePfeifer.ispis();
    cout << endl;

    Gost jackNicholson;
    jackNicholson.setIme("Jack");
    jackNicholson.setPrezime("Nicholson");
    jackNicholson.setSpol(1);
    jackNicholson.setDatumRodjenja(Datum(1, 4, 1945));
    jackNicholson.setZemljaPorijekla("SAD");
    jackNicholson.ispis();
    cout << endl;

    Gost heathLedger;
    heathLedger.setIme("Heath");
    heathLedger.setPrezime("Ledger");
    heathLedger.setSpol(1);
    heathLedger.setDatumRodjenja(Datum(5, 3, 1983));
    heathLedger.setZemljaPorijekla("Australija");
    heathLedger.ispis();
    cout << endl;

    Gost jaredLeto(heathLedger); // copy ctor
    jaredLeto.setIme("Jared");
    jaredLeto.setPrezime("Leto");
    jaredLeto.setSpol(1);
    jaredLeto.setDatumRodjenja(Datum(26, 12, 1971));
    jaredLeto.setZemljaPorijekla("SAD");
    jaredLeto.ispis();
    cout << endl;
    cout << "Dealokacija ..." << endl;

    
}

void zadatak3() {
    cout << "Testiranje klase 'Odrediste'\n\n";
    Odrediste e1;
    e1.setNaziv("Istanbul?");
    e1.setTrajanje(21);
    e1.setKratakSadrzaj("Opis odredista - avio prevoz, brod, ...");
    int ocjene[] = { 6,7,4,3,7,17,4,4,1,15 };
    e1.setOcjene(size(ocjene), size(ocjene), ocjene);
    e1.ispis();
    
    cout << endl;

    e1.dodajOcjenu(10);
    e1.ispis();
    cout << endl;

    e1.ukloniZadnjuOcjenu();
    e1.ispis();
}

void zadatak4() {
    Gost g1;
    PrijavaPutovanja pp1(g1, "Dobar", 527);
    pp1.ispis();
    PrijavaPutovanja pp2(pp1);
    pp2.ispis();
}

void zadatak5() {
    cout << "Testiranje klase \"Putovanje\"" << endl;
    PrijavaPutovanja* prijave = new PrijavaPutovanja[2];
    Odrediste* odredista = new Odrediste[2];
    Putovanje p1("Izlet u Blagaj", Datum(24, 4, 2024), prijave, 2, odredista, 0);
    p1.ispis();
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