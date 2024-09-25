#include <iostream>
using namespace std;

//Z1.0
char* alocirajTekst(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, tekst);
    return temp;

}

class Datum
{
    int _dan;
    int _mjesec;
    int _godina;
public:
    //Z1.1 
    void unos(int d, int m, int g) {
        setDan(d);
        setMjesec(m);
        setGodina(g);
    }
    //Z1.2 
    void unos(Datum& datum) {
        setDan(datum.getDan());
        setMjesec(datum.getMjesec());
        setGodina(datum.getGodina());
    }
    //Z1.3
    int getDan() const { return _dan; }
    int getMjesec() const { return _mjesec; }
    int getGodina() const { return _godina; }
    //Z1.4
    void setDan(int dan) {
        _dan = dan;
    }
    void setMjesec(int mjesec) {
        _mjesec = mjesec;
    }
    void setGodina(int godina) {
        _godina = godina;
    }
    //Z1.5
    void ispis() {
        cout << getDan() << "." << getMjesec() << "." << getGodina() << endl;
    }
};

//Z1.6
//Vraca slucajni niz karaktera [mala slova] 
char* getRandomString(int duzina) {
    if (duzina == 0)
        return nullptr;
    char* temp = new char[duzina + 1];  // '\0'
    for (int i = 0; i < duzina; i++) {
        temp[i] = char(rand() % ('z' - 'a' + 1) + 'a');
    }
    temp[duzina] = '\0';
    return temp;
}

class Sjediste {
    char* _sjedisteId{ nullptr }; // Koristiti getRandomString funkciju prilikom inicijalizacije [neka je duzina stringa 7]
    char _red = 'A'; //A-Z
    int _kolona = 0; //1,2,3,..., 100
public:
    //Z2.1
    void unos(char red, int kolona) {
        setSjedisteId();
        setRed(red);
        setKolona(kolona);
    }
    //Z2.2
    void unos(Sjediste& sjediste) {
        setSjedisteId();
        setRed(sjediste.getRed());
        setKolona(sjediste.getKolona());
    }
    //2.3.
    const char* getSjedisteId() const { return (_sjedisteId == nullptr) ? nullptr : _sjedisteId; }
    char getRed() const { return _red; }
    int getKolona() const { return _kolona; }
    //Z2.4
    void setSjedisteId() {
        _sjedisteId = new char[8];
        _sjedisteId = getRandomString(7);
    }
    void setRed(char red) {
        _red = red;
    }
    void setKolona(int kolona) {
        _kolona = kolona;
    }
    //Z2.5
    //ispisati sjediste u formatu: "[A-13]"
    void ispis() {
        cout << "ID sjedista: " << getSjedisteId() << endl;
        cout << "Oznaka sjedista: [" << getRed() << "-" << getKolona() << "]" << endl;
    }
    //Z2.6
    void dealokacija() {
        delete[] _sjedisteId;
        _sjedisteId = nullptr;
    }
};

class Dvorana
{
    char* _naziv{ nullptr };
    int _brojRedova = 0; //max.26 [A-Z]
    int _brojKolona = 0;
    Sjediste** _sjedista{ nullptr }; //2D matrica objekata tipa Sjediste. Dimenzije matrice su: (_brojRedova x _brojKolona)
public:
    //Z2.7
    void unos(const char* naziv, int brojRedova, int brojKolona) {
        setNaziv(naziv);
        setSjedista(brojRedova, brojKolona);
    }
    //Z2.8
    void unos(Dvorana& dvorana) {
        //implementirati funkciju
    }
    //Z2.9
    const char* getNaziv() const { return (_naziv == nullptr) ? nullptr : _naziv; }
    int getBrojRedova() const { return _brojRedova; }
    int getBrojKolona() const { return _brojKolona; }
    //Z2.10
    void setNaziv(const char* naziv) {
        if (_naziv != nullptr)
            delete[] _naziv;
        _naziv = alocirajTekst(naziv);
    }

    //Z2.11
    /*
    Uraditi dealokaciju alocirane matrice sjedista, te zatim uraditi ponovnu alokaciju
    Podesiti vrijednosti atributa objekata matrice na sljedeci nacin -->
    Polje [0][0] => _red : A, _kolona : 1
    Polje [0][1] => _red : A, _kolona : 2
    Polje [0][2] => _red : A, _kolona : 3
    ...
    Polje [1][0] => _red : B, _kolona : 1
    itd.
    */
    void setSjedista(int brojRedova, int brojKolona) {

        if (brojRedova > 26)
            return;

        // Dealokacija
        dealokacijaSjedista();

        // Alokacija
        _sjedista = new Sjediste * [brojRedova];
        for (int i = 0; i < brojRedova; i++) {
            _sjedista[i] = new Sjediste[brojKolona];
        }

        // Kopiranje
        for (int i = 0; i < brojRedova; i++) {
            for (int j = 0; j < brojKolona; j++) {
                _sjedista[i][j].unos('A' + i, j + 1);
            }
        }

        _brojRedova = brojRedova;
        _brojKolona = brojKolona;

    }

    //Z2.12
    //Vratiti adresu objekta sjediste, koje odgovara proslijedjenim vrijednostima reda i kolone
    Sjediste* getSjediste(int red, int kolona) {
        //implementirati funkciju
        return nullptr;
    }

    //Z2.13
    //Uraditi ispis dvorane na sljedeci nacin --->
    //Dvorana: Dvorana 7 Extreme
    //Redova: 11
    //Kolona: 20
    // -----------------------------
    // [A-1] [A-2] [A-3] .... [A-20]
    // [B-1] [B-2] [B-3] .... [B-20]
    // .
    // .
    // .
    // [K-1] [K-2] [K-3] .... [K-20]
    // -----------------------------
    void ispis() {
        //implementirati funkciju
    }

    //Z2.14
    void dealokacija() {

        delete[] _naziv;
        _naziv = nullptr;

        for (int i = 0; i < _brojRedova; i++) {
            for (int j = 0; j < _brojKolona; j++) {
                _sjedista[i][j].dealokacija();
            }
            delete[] _sjedista[i];
            _sjedista[i] = nullptr;
        }
        delete[] _sjedista;
        _sjedista = nullptr;
    }

    void dealokacijaSjedista() {
        for (int i = 0; i < _brojRedova; i++) {
            for (int j = 0; j < _brojKolona; j++) {
                _sjedista[i][j].dealokacija();
            }
            delete[] _sjedista[i];
            _sjedista[i] = nullptr;
        }
        delete[] _sjedista;
        _sjedista = nullptr;
    }
};
class Uposlenik {
    char* _ime{ nullptr };
    char* _prezime{ nullptr };
    Datum* _datumRodjenja{ nullptr };
    bool* _spol{ nullptr };
    char _radnoMjesto[100] = "";
    char* _grad{ nullptr };
    char _email[100] = "";
public:
    //Z3.1
    void unos(const char* ime, const char* prezime, Datum datum, bool spol, const char* radnoM, const char* grad, const char* email) {
        setIme(ime);
        setPrezime(prezime);
        setDatumRodjenja(datum);
        setSpol(spol);
        setRadnoMjesto(radnoM);
        setGrad(grad);
        setEmail(email);
    }
    //Z3.2
    void unos(Uposlenik& u) {
        setIme(u.getIme());
        setPrezime(u.getPrezime());
        setDatumRodjenja(u.getDatumRodjenja());
        setSpol(u.getSpol());
        setRadnoMjesto(u.getRadnoMjesto());
        setGrad(u.getGrad());
        setEmail(u.getEmail());
    }

    //Z3.3
    const char* getIme() const { return (_ime == nullptr) ? nullptr : _ime; }
    const char* getPrezime() const { return (_prezime == nullptr) ? nullptr : _prezime; }
    Datum getDatumRodjenja() const { return *_datumRodjenja; }
    bool getSpol() const { return (_spol == nullptr) ? nullptr : _spol; }
    const char* getRadnoMjesto() const { return _radnoMjesto; }
    const char* getGrad() const { return (_grad == nullptr) ? nullptr : _grad; }
    const char* getEmail() const { return _email; }

    //Z3.4
    void setIme(const char* ime) {
        if (_ime != nullptr)
            delete[] _ime;
        _ime = alocirajTekst(ime);
    }
    //Z3.5
    void setPrezime(const char* prezime) {
        if (_prezime != nullptr)
            delete[] _prezime;
        _prezime = alocirajTekst(prezime);
    }
    //Z3.6
    void setDatumRodjenja(Datum datum) {
        if (_datumRodjenja != nullptr)
            delete _datumRodjenja;
        _datumRodjenja = new Datum;
        _datumRodjenja->unos(datum);
    }
    //Z3.7
    void setSpol(bool spol) {
        if (_spol != nullptr)
            delete _spol;
        _spol = new bool{ spol };
    }
    //Z3.8
    void setRadnoMjesto(const char* radnoMjesto) {
        strcpy_s(_radnoMjesto, strlen(radnoMjesto) + 1, radnoMjesto);
    }
    //Z3.9
    void setGrad(const char* grad) {
        _grad = alocirajTekst(grad);
    }
    //Z3.10
    void setEmail(const char* email) {
        strcpy_s(_email, strlen(email) + 1, email);
    }
    //Z3.11
    void ispis() {
        cout << "Ime i prezime: " << getIme() << " " << getPrezime() << endl;
        cout << "Datum rodjenja: ";
        getDatumRodjenja().ispis();
        cout << "Spol: ";
        (getSpol()) ? cout << "Musko" << endl : cout << "Zensko" << endl;
        cout << "Radno mjesto: " << getRadnoMjesto() << endl;
        cout << "Grad: " << getGrad() << endl;
        cout << "Email: " << getEmail() << endl;
     }
    //Z3.12
    void dealokacija() {
        delete[] _ime, delete[] _prezime, delete[] _grad;
        _ime = _prezime = _grad = nullptr;
        delete _spol;
        _spol = nullptr;
        delete _datumRodjenja;
        _datumRodjenja = nullptr;
    }
};

class Kino {
    char* _naziv = nullptr;
    char _adresa[100] = "";

    int* _maxBrojDvorana{ nullptr }; // pokazivac na varijablu (sadrzi vrijednost velicine niza)
    int _trenutnoDvorana = 0; //brojac (pocinje od 0)
    Dvorana* _dvorane{ nullptr }; // pokazivac na niz objekata

    int _trenutnoUposlenika = 0; //brojac (pocinje od 0)
    Uposlenik* _uposlenici[50] = { nullptr }; // niz pokazivaca na objekte tipa Uposlenik
public:
    //Z4.1
    void unos(const char* naziv, const char* adresa, int maxBrojDvorana) {
        //implementirati funkciju
    }
    //Z4.2
    const char* getNaziv() const { return ""; } //implementirati funkciju
    const char* getAdresa() const { return ""; } //implementirati funkciju
    int getMaxBrojDvorana() const { return  0; } //implementirati funkciju
    int getTrenutnoDvorana() const { return _trenutnoDvorana; }
    int getTrenutnoUposlenika() const { return _trenutnoUposlenika; }
    //Z4.3
    void setNaziv(const char* naziv) {
        //implementirati funkciju
    }
    //Z4.4
    void setAdresa(const char* adresa) {
        //implementirati funkciju
    }
    //Z4.5
    void setDvorane(int maxBrojDvorana) {
        //implementirati funkciju
    }

    //Z4.6
    bool dodajDvoranu(Dvorana& d) {
        //implementirati funkciju
        return false;
    }
    //Z4.7
    bool dodajUposlenika(Uposlenik& u) {
        //implementirati funkciju
        return false;
    }
    //Z4.8
    //ispisati naziv kina, adresu, nazive dvorana, te imena i prezimena uposlenika
    void ispis() {
        //implementirati funkciju
    }
    //Z4.9
    void dealokacija() {
        //implementirati funkciju
    }
};
void zadatak1() {
    cout << "Testiranje klase 'Datum'" << endl;
    Datum euro2021;
    euro2021.setDan(11);
    euro2021.setMjesec(6);
    euro2021.setGodina(2021);
    Datum olimpijskeIgre;
    olimpijskeIgre.unos(24, 7, 2021);
    Datum paraOlimprijskeIgre;
    paraOlimprijskeIgre.unos(olimpijskeIgre.getDan(), olimpijskeIgre.getMjesec(), olimpijskeIgre.getGodina());
    paraOlimprijskeIgre.setMjesec(8);
    cout << "EURO 2021:" << endl;
    euro2021.ispis();
    cout << endl;
    cout << "Olimpijske igre 2021:" << endl;
    olimpijskeIgre.ispis();
    cout << endl;
    cout << "Paraolimpijske igre 2021:" << endl;
    paraOlimprijskeIgre.ispis();
    cout << endl;
    cout << "Dealokacija ..." << endl;
}

void zadatak2() {
    cout << "Testiranje klase 'Sjediste'" << endl;
    Sjediste s1, s2;
    s2.unos('C', 4);
    Sjediste s3;
    s3.unos(s2.getRed(), s2.getKolona());
    s3.ispis();
    cout << endl;
    s3.setRed('M');
    s3.setKolona(16);
    s3.ispis();
    cout << endl;
    cout << "Done." << "\n\n";

    cout << "Testiranje klase 'Dvorana'" << endl;
    Dvorana extreme3;
    extreme3.unos("Dvorana Extreme 3", 7, 7);
    extreme3.ispis();
    cout << endl;
    Dvorana realExtreme3;
    realExtreme3.unos(extreme3.getNaziv(), extreme3.getBrojRedova(), extreme3.getBrojKolona());
    realExtreme3.setNaziv("Dvorana Real Extreme 3");
    realExtreme3.setSjedista(10, 10);
    realExtreme3.ispis();
    cout << endl;
    Dvorana real3D;
    real3D.setNaziv("Dvorana Real 3D");
    real3D.setSjedista(15, 8);
    real3D.ispis();
    cout << endl;

    Sjediste* pok = real3D.getSjediste(1, 2);
    cout << "Trazimo sjediste u dvorani Real 3D." << endl;
    if (pok != nullptr) {
        pok->ispis();
        cout << endl << "Nadjeno." << endl;
    }
    else
        cout << "Nije nadjeno." << endl;
    cout << "Dealokacija dvorana..." << endl;
    s1.dealokacija();
    s2.dealokacija();
    s3.dealokacija();
    extreme3.dealokacija();
    realExtreme3.dealokacija();
    real3D.dealokacija();
}
void zadatak3() {
    cout << "Testiranje klase 'Uposlenik'" << endl;

    Datum datumRodjenja;
    datumRodjenja.unos(3, 2, 1967);
    Uposlenik connanOBrien;
    connanOBrien.unos("Connan", "O'Brien", datumRodjenja, 1, "blagajnik", "Bihac", "teamcoco@gmail.com");
    connanOBrien.setEmail("orangecoconut@gmail.com");
    connanOBrien.ispis();
    cout << endl;

    Uposlenik jimmyKimmel;
    jimmyKimmel.setIme("Jimmy");
    jimmyKimmel.setPrezime("Kimmel");
    datumRodjenja.unos(5, 5, 1967);
    jimmyKimmel.setDatumRodjenja(datumRodjenja);
    jimmyKimmel.setSpol(true);
    jimmyKimmel.setEmail("the_pranklord@hotmail.com");
    jimmyKimmel.setRadnoMjesto("prodavac kokica");
    jimmyKimmel.setGrad("Portland");
    jimmyKimmel.ispis();
    cout << endl;

    Uposlenik chuckNorris;
    chuckNorris.setIme("Chuck");
    chuckNorris.setPrezime("Norris");
    datumRodjenja.unos(30, 2, 1940);
    chuckNorris.setDatumRodjenja(datumRodjenja);
    chuckNorris.setSpol(true);
    chuckNorris.setEmail("gmail@chucknorris.com");
    chuckNorris.setRadnoMjesto("redar, domar, financijski menadzer, projekcijski menadzer, direktor, ...");
    chuckNorris.setGrad("Planeta Zemlja");
    chuckNorris.ispis();
    cout << endl;
    cout << "Dealokacija uposlenika..." << endl;
    connanOBrien.dealokacija();
    jimmyKimmel.dealokacija();
    chuckNorris.dealokacija();

}

void zadatak4() {
    Kino dejaView;
    dejaView.unos("Deja View Cinema", "Bihac Ul. 76", 5);
    Dvorana d1, d2;
    d1.unos("Dvorana 1", 10, 5);
    d2.unos("Dvorana 2", 10, 6);
    cout << (dejaView.dodajDvoranu(d1) ?
        "Uspjesno dodavanje dvorane d1." :
        "Bezuspjesno dodavanje dvorane d1.") << endl;
    cout << (dejaView.dodajDvoranu(d2) ?
        "Uspjesno dodavanje dvorane d2." :
        "Bezuspjesno dodavanje dvorane d2.") << endl;;

    Datum datum1, datum2, datum3;
    datum1.unos(2, 3, 1966);
    datum2.unos(2, 4, 1969);
    datum3.unos(1, 5, 1955);
    Uposlenik u1, u2, u3;
    u1.unos("Jonah", "Hillside", datum1, 1, "prodavac ulaznica", "Banja Luka", "jonahillside@gmail.com");
    u2.unos("Dwayne", "'The Mountain' Johnson", datum2, 1, "domar", "Sarajevo", "johnrocksbigtime@gmail.com");
    u3.unos("Tom", "Cruiser", datum3, 1, "vozac", "Brcko", "thomas_cruiser@gmail.com");

    if (dejaView.dodajUposlenika(u1))
        cout << "Uspjesno dodan " << u1.getIme() << " " << u1.getPrezime() << endl;
    if (dejaView.dodajUposlenika(u2))
        cout << "Uspjesno dodan " << u2.getIme() << " " << u2.getPrezime() << endl;
    if (dejaView.dodajUposlenika(u3))
        cout << "Uspjesno dodan " << u3.getIme() << " " << u3.getPrezime() << endl;
    dejaView.ispis();
    cout << endl;
    cout << "Dealokacija ..." << endl;
    d1.dealokacija();
    d2.dealokacija();
    u1.dealokacija();
    u2.dealokacija();
    u3.dealokacija();
    dejaView.dealokacija();
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
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 4);
        switch (izbor) {
        case 1: zadatak1(); cout << "Zadatak 1. Done." << endl; break;
        case 2: zadatak2(); cout << "Zadatak 2. Done." << endl; break;
        case 3: zadatak3(); cout << "Zadatak 3. Done." << endl; break;
        case 4: zadatak4(); cout << "Zadatak 4. Done." << endl; break;
        default:break;
        }
        do {
            cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
            cin >> nastaviDalje;
        } while (nastaviDalje != 0 && nastaviDalje != 1);
    }
}

int main()
{
    /*char* random = getRandomString(19);
    cout << random;*/

    /*Sjediste s1;
     s1.unos('c', 51);
     s1.ispis();
     s1.dealokacija();*/


    Uposlenik u1;
    Datum d1;
    d1.unos(1,1,1);
    u1.unos("Haris", "Velispahic", d1, 1, "FIT", "Kakanj", "haris.velispahic@gmail.com");
    u1.ispis();

    cout << endl;
    Uposlenik u2;
    u2.unos(u1);
    u2.ispis();

    u1.dealokacija();
    u2.dealokacija();

     //menu();
    return 0;
}