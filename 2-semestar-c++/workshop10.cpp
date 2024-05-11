#include <iostream>

using namespace std;

const char* separator = "-------------------------------------------\n";

#pragma region Enumeracije

enum CiklusStudija { Prvi = 1, Drugi = 2, Treci = 3 };
enum GodinaStudija { Prva = 1, Druga = 2, Treca = 3, Cetvrta = 4 };
enum Semestar { Zimski = 1, Ljetni = 2 };
enum Spol { Muski = 1, Zenski = 0 };
#pragma endregion

#pragma region Alokatori_i_pomocne_funkcije
// Z0.1 
char* alocirajTekst(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, tekst);
    return temp;
}

//Z0.2 :: Funkcija za alokaciju pametnog (shared_ptr) pokazivaca na niz karaktera
shared_ptr<char> shared_alokator(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1;
    shared_ptr<char> novi(new char[vel], default_delete<char[]>());
    strcpy_s(novi.get(), vel, tekst);
    return novi;
}
//Z0.3 :: Funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char[]> unique_alokator(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int size = strlen(tekst) + 1;
    unique_ptr<char[]> temp = make_unique<char[]>(size);
    strcpy_s(temp.get(), size, tekst);
    return temp;
}

// Z0.4 :: funkcija za prebrojavanje broja znamenki [voditi racuna i o negativnim vrijednostima]
int countDigits(int broj) {
    return (broj != 0) ? log10(abs(broj)) + 1 : 1;
}
// Z0.5 :: pretvoriti (int) u (char*) :: koristiti funkciju _itoa_s
char* intToStr(int broj) {
    int vel = countDigits(broj) + 1;
    char* tekst = new char[vel];
    _itoa_s(broj, tekst, vel, 10);
    return tekst;
}

// Z0.6 :: funkcija za poredjenje dva niza karaktera
bool areEqual(const char* str1, const char* str2) {
    return (str1 != nullptr && str2 != nullptr) ? strcmp(str1, str2) == 0 : false;
}

#pragma endregion


#pragma region Kolekcija
template<class T>
class Kolekcija {
    int _trenutno = 0;
    int _maxElemenata;
    T* _elementi = nullptr;
public:
    // getteri
    int getTrenutno() const { return _trenutno; }
    int getMaxElemenata() const { return _maxElemenata; }
    T* getElementi() const { return _elementi; }

    // setteri (u ovom slucaju imamo samo jednu setter funkciju)
    void setElementi(int trenutno, int maxElemenata, T* elementi = nullptr) {
        delete[] _elementi;
        _trenutno = 0;
        _maxElemenata = maxElemenata;
        _elementi = new T[_maxElemenata];

        if (elementi != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                dodaj(elementi[i]);
            }
        }
    }
    // funkcija za dodavanje elementa tipa 'T'.
    // U slucaju da je brojac dosao do kraja -- uraditi prosirivanje niza za 10 elemenata.
    void dodaj(const T& element) {
        if (_trenutno >= _maxElemenata) {
            expandElementi(10);
        }
        _elementi[_trenutno++] = element;
    }

    // funkcija za umetanje elementa na index
    bool insertAt(int index, const T& element) {
        if (index < 0 || index >= _trenutno)
            return false;
        if (_trenutno == 0)
            dodaj(element);
        if (_trenutno >= _maxElemenata)
            expandElementi(10);

        for (int i = _trenutno; i > index; i--) {
            _elementi[i] = _elementi[i - 1];
        }
        _elementi[index] = element;
        _trenutno++;
    }

    // funkcija za uklanjanje zadnjeg elementa iz niza
    bool removeZadnji() {
        if (_trenutno <= 0)
            return false;
        _trenutno--;
        return true;
    }
    // funkcija za prosirivanje dinamickog niza
    void expandElementi(int uvecanje) {
        _maxElemenata += uvecanje;
        T* temp = new T[_maxElemenata];
        for (int i = 0; i < _trenutno; i++) {
            temp[i] = _elementi[i];
        }
        delete[] _elementi;
        _elementi = temp;
    }
    // dflt ctor
    Kolekcija(int maxElemenata = 100) {
        setElementi(0, maxElemenata);
        
    }
    // copy ctor :: Kopirati vrijednosti jednog vektora u drugi
    Kolekcija(const Kolekcija<T>& obj) {
        setElementi(obj.getTrenutno(), obj.getMaxElemenata(), obj.getElementi());
    }
    // operator '='
    Kolekcija<T>& operator = (const Kolekcija<T>& obj) {
        if (this != &obj)
            setElementi(obj.getTrenutno(), obj.getMaxElemenata(), obj.getElementi());
        return *this;
    }
    // operator '[]' za dohvacanje pojedinacne vrijednosti iz niza
    // U slucaju da je vektor prazan, 'baciti' izutetak (objekt klase 'Greska') //ovo ce se uciti u narednim sedmicama, stoga je u rjesenju komentarisano
    // Postupiti na isti nacin i u slucaju da je 'index' izvan opsega granica vektora//ovo ce se uciti u narednim sedmicama, stoga je u rjesenju komentarisano
    T& operator [] (int index) const {
        // Implementirati funkciju
       /*
       //Izuzeci (exception) ce se uciti u narednim sedmicama, stoga je u ovdje komentarisano
       if (_trenutno == 0)
            throw Greska("vektor je prazan", __LINE__, __FUNCTION__);

        if (_trenutno < 0 || index >= _trenutno)
            throw Greska("vektor je prazan", __LINE__, __FUNCTION__);
        */
        if (index >= 0 && index < _trenutno)
            return _elementi[index];
    }

    // Z1.10 :: funkcija za provjeru postojanosti vrijednosti 'element' u okviru dinamickog niza
    bool checkIfContains(T element) {
        for (auto& el : _elementi) {
            if (el == element)
                return true;
        }
        return false;

        /*for (int i = 0; i < _trenutno; i++) {
            if (_elementi[i] == element)
                return true;
        }
        return false;*/
    }
};

template <class T>
ostream& operator << (ostream& COUT, const Kolekcija<T>& obj) {
    for (int i = 0; i < obj.getTrenutno(); i++) {
        COUT << obj.getElementi()[i] << endl;
    }
    return COUT;
}

#pragma endregion

#pragma region Dlwms_Predmet
class Predmet {
    char* naziv = nullptr;
    int ectsKredit;
    GodinaStudija godina;
    Semestar semestar;
    CiklusStudija ciklusStudija;
public:
    // Constructor with parameters
    Predmet(const char* naziv, int ectsKredit, GodinaStudija godina, Semestar semestar, CiklusStudija ciklusStudija) {
        setNaziv(naziv);
        setEctsKredit(ectsKredit);
        setGodina(godina);
        setSemestar(semestar);
        setCiklusStudija(ciklusStudija);
    }
    // Copy constructor (deep copy)
    Predmet(const Predmet& other) {
        setNaziv(other.getNaziv());
        setEctsKredit(other.getEctsKredit());
        setGodina(other.getGodina());
        setSemestar(other.getSemestar());
        setCiklusStudija(other.getCiklusStudija());
        
    }
    // Assignment operator (copy-and-swap idiom)
    Predmet& operator=(Predmet other) {
        if (this != &other) {
            setNaziv(other.getNaziv());
            setEctsKredit(other.getEctsKredit());
            setGodina(other.getGodina());
            setSemestar(other.getSemestar());
            setCiklusStudija(other.getCiklusStudija());
        }
        return *this;
    }

    Predmet() {
        setNaziv("---");
        setEctsKredit(0);
        setGodina(Prva);
        setSemestar(Zimski);
        setCiklusStudija(Prvi);
    }
    // Destructor
    ~Predmet() {
        delete[] naziv;
        naziv = nullptr;
    }

    const char* getNaziv() const { return (naziv == nullptr) ? "" : naziv; }
    int getEctsKredit() const { return ectsKredit; }
    GodinaStudija getGodina() const { return godina; }
    Semestar getSemestar() const { return semestar; }
    CiklusStudija getCiklusStudija() const { return ciklusStudija; }
    void setNaziv(const char* noviNaziv) {
        delete[] naziv;
        naziv = alocirajTekst(noviNaziv);
    }

    void setEctsKredit(int ectsKredit) { this->ectsKredit = ectsKredit; }
    void setGodina(GodinaStudija godina) { this->godina = godina; }
    void setSemestar(Semestar semestar) { this->semestar = semestar; }
    void setCiklusStudija(CiklusStudija ciklusStudija) { this->ciklusStudija = ciklusStudija; }
};

ostream& operator<<(ostream& COUT, const Predmet& obj) {
    COUT << "Naziv predmeta: " << obj.getNaziv() << endl;
    COUT << "Broj ECTS kredita: " << obj.getEctsKredit() << endl;
    COUT << "Godina studija: " << obj.getGodina() << endl;
    COUT << "Semestar: " << ((obj.getSemestar() == 1) ? "Zimski" : "Ljetni") << endl;
    COUT << "Ciklus studija: " << obj.getCiklusStudija() << endl;
    return COUT;
}

#pragma endregion

#pragma region Dlwms_Nastavnik
class Nastavnik {
private:
    char* ime = nullptr;
    char* prezime = nullptr;
    char* email = nullptr;
    char* password = nullptr;

public:
    // Constructor with parameters
    Nastavnik(const char* ime, const char* prezime, const char* email, const char* password){
        setIme(ime);
        setPrezime(prezime);
        setEmail(email);
        setPassword(password);
    }

    // Default constructor
    Nastavnik() {
        setIme("---");
        setPrezime("---");
        setEmail("---");
        setPassword("---");
    }

    // Copy constructor
    Nastavnik(const Nastavnik& other){
        setIme(other.getIme());
        setPrezime(other.getPrezime());
        setEmail(other.getEmail());
        setPassword(other.getPassword());
    }

    // Assignment operator
    Nastavnik& operator=(const Nastavnik& other) {
        if (this != &other) {
            setIme(other.getIme());
            setPrezime(other.getPrezime());
            setEmail(other.getEmail());
            setPassword(other.getPassword());
        }
        return *this;
    }

    // Destructor
    ~Nastavnik() {
        delete[] ime;
        delete[] prezime;
        delete[] email;
        delete[] password;
        ime = prezime = email = password = nullptr;
    }

    // Setters
    void setIme(const char* novoIme) {
        delete[] ime;
        ime = alocirajTekst(novoIme);
    }

    void setPrezime(const char* novoPrezime) {
        delete[] prezime;
        prezime = alocirajTekst(novoPrezime);
    }

    void setEmail(const char* noviEmail) {
        delete[] email;
        email = alocirajTekst(noviEmail);
    }

    void setPassword(const char* noviPassword) {
        delete[] password;
        password = alocirajTekst(noviPassword);
    }

    // Getters
    const char* getIme() const { return (ime == nullptr) ? "" : ime; }
    const char* getPrezime() const { return (prezime == nullptr) ? "" : prezime; }
    const char* getEmail() const { return (email == nullptr) ? "" : email; }
    const char* getPassword() const { return (password == nullptr) ? "" : password; }
};

ostream& operator<<(ostream& COUT, const Nastavnik& obj) {
    COUT << "Ime i prezime nastavnika: " << obj.getIme() << " " << obj.getPrezime() << endl;
    COUT << "Email profesora: " << obj.getEmail() << endl;
    COUT << "Password profesora: ";
    int brojCharactera = strlen(obj.getPassword());
    for (int i = 0; i < brojCharactera; i++)
        cout << "*";
    cout << "\n";
    return COUT;
}

#pragma endregion

class DlwmsApp {

    Kolekcija<Predmet> predmeti;
    Kolekcija<Nastavnik> nastavnici;
public:

    DlwmsApp() {
        admin0_init_podaci();
    }

    void admin0_init_podaci() {
        predmeti.dodaj(Predmet("Programiranje I", 7, GodinaStudija::Prva, Semestar::Zimski, CiklusStudija::Prvi));
        predmeti.dodaj(Predmet("Matematika I", 7, GodinaStudija::Prva, Semestar::Zimski, CiklusStudija::Prvi));
        predmeti.dodaj(Predmet("Programiranje II", 7, GodinaStudija::Prva, Semestar::Ljetni, CiklusStudija::Prvi));
        predmeti.dodaj(Predmet("Matematika II", 6, GodinaStudija::Prva, Semestar::Ljetni, CiklusStudija::Prvi));
        predmeti.dodaj(Predmet("Web razvoj i dizajn", 5, GodinaStudija::Prva, Semestar::Ljetni, CiklusStudija::Prvi));

        nastavnici.dodaj(Nastavnik("Nina", "Bijedic", "nbijedic@edu.fit.ba", "Mostar2019"));
        nastavnici.dodaj(Nastavnik("Denis", "Music", "denis@edu.fit.ba", "Mostar2019"));
        nastavnici.dodaj(Nastavnik("Elmir", "Babovic", "elmir.babovic@edu.fit.ba", "Mostar2019"));
    }

    // Helper function to collect data and return a Predmet object
    Predmet collectPredmetData(Predmet* stari = nullptr) {
        char naziv[100];
        int ects;
        int godina, semestar, ciklus;

        if (stari != nullptr)
            cout << "Unesite naziv predmeta [" << stari->getNaziv() << "]" << endl;
        else
            cout << "Unesite naziv predmeta []" << endl;

        cin.ignore(); // To clear out newline characters from previous input
        cin.getline(naziv, sizeof(naziv));

        cout << "Unesite ECTS kredite: ";
        cin >> ects;

        cout << "Unesite godinu studija (1-4): ";
        cin >> godina;
        cout << "Unesite semestar (1-Zimski, 2-Ljetni): ";
        cin >> semestar;
        if (stari == nullptr) {
            cout << "Unesite ciklus studija (1-Prvi, 2-Drugi, 3-Treci): ";
            cin >> ciklus;
        }
        else
        {
            ciklus = (int)stari->getCiklusStudija();
        }

        return Predmet(naziv, ects, static_cast<GodinaStudija>(godina), static_cast<Semestar>(semestar), static_cast<CiklusStudija>(ciklus));
    }

    void admin1_predmeti() {
        int opcija = 0;
        do {
            // Display all subjects with indices
            system("cls"); // Clear the console
            cout << "Lista predmeta:" << endl;
            for (int i = 0; i < predmeti.getTrenutno(); i++) {
                cout << i + 1 << ". " << predmeti[i].getNaziv() << endl;
            }
            cout << separator;
            cout << "Unesite opciju:" << endl;
            cout << "1. Uredi predmet" << endl;
            cout << "2. Dodaj novi predmet" << endl;
            cout << "3. Podaci o predmetu" << endl;
            cout << "4. Povratak u glavni meni" << endl;
            cout << separator;
            cout << "Opcija: ";
            cin >> opcija;

            switch (opcija) {
            case 1: // Edit existing subject
            {
                int index;
                cout << "Unesite redni broj predmeta za uredjivanje: ";
                cin >> index;
                if (index < 1 || index > predmeti.getTrenutno()) {
                    cout << "Neispravan unos!" << endl;
                    break;
                }
                index--; // Adjust index for 0-based array

                predmeti[index] = collectPredmetData(&predmeti[index]);

                cout << "Predmet uspjesno azuriran!" << endl;
                break;
            }
            case 2: // Add new subject
            {
                predmeti.dodaj(collectPredmetData());
                cout << "Predmet dodan!" << endl;
                break;
            }
            case 3:
                int index;
                cout << "Unesite redni broj predmeta cije podatke zelite vidjeti: ";
                cin >> index;
                if (index < 1 || index > predmeti.getTrenutno()) {
                    cout << "Neispravan unos!" << endl;
                    break;
                }
                index--; // Adjust index for 0-based array

                cout << "Podaci o predmetu [" << predmeti[index].getNaziv() << "]:\n" << endl;
                cout << predmeti[index] << endl;

                system("pause");
                break;
            case 4: // Return to main menu
                return;
            default:
                cout << "Neispravan unos. Molimo unesite pravilan broj opcije." << endl;
                break;
            }
        } while (opcija != 4);
    }


    // Nova funkcija za unos ili ažuriranje nastavnika
    Nastavnik collectNastavnikData(Nastavnik* stari = nullptr) {
        char ime[100], prezime[100], email[100], password[100];

        cout << "Unesite ime [" << (stari ? stari->getIme() : "") << "]: ";
        cin.ignore(); // Za brisanje preostalih newline karaktera
        cin.getline(ime, sizeof(ime));

        cout << "Unesite prezime [" << (stari ? stari->getPrezime() : "") << "]: ";
        cin.getline(prezime, sizeof(prezime));

        cout << "Unesite email [" << (stari ? stari->getEmail() : "") << "]: ";
        cin.getline(email, sizeof(email));

        if (!stari) {
            cout << "Unesite lozinku: ";
            cin.getline(password, sizeof(password));
        }
        else {
            strcpy_s(password, stari->getPassword());
        }

        return Nastavnik(ime, prezime, email, password);
    }

    void admin2_nastavnici() {
        int opcija = 0;
        do {
            system("cls");
            cout << "Lista nastavnika:" << endl;
            for (int i = 0; i < nastavnici.getTrenutno(); ++i) {
                cout << i + 1 << ". " << nastavnici[i].getIme() << " " << nastavnici[i].getPrezime() << endl;
            }
            cout << separator;
            cout << "1. Uredi nastavnika" << endl;
            cout << "2. Dodaj novog nastavnika" << endl;
            cout << "3. Podaci o nastavniku" << endl;
            cout << "4. Povratak u glavni meni" << endl;
            cout << separator;
            cout << "Opcija: ";
            cin >> opcija;

            switch (opcija) {
            case 1: {
                int index;
                cout << "Unesite redni broj nastavnika za uredjivanje: ";
                cin >> index;

                if (index < 1 || index > nastavnici.getTrenutno()) {
                    cout << "Neispravan unos!" << endl;
                    break;
                }

                index--; // Indeksi su 0-bazirani
                nastavnici[index] = collectNastavnikData(&nastavnici[index]);

                cout << "Nastavnik uspješno azuriran!" << endl;
                break;
            }
            case 2: {
                nastavnici.dodaj(collectNastavnikData());
                cout << "Nastavnik dodan!" << endl;
                break;
            }
            case 3:
                int index;
                cout << "Unesite redni broj nastavnika cije podatke zelite vidjeti: ";
                cin >> index;
                if (index < 1 || index > predmeti.getTrenutno()) {
                    cout << "Neispravan unos!" << endl;
                    break;
                }
                index--; // Adjust index for 0-based array

                cout << "Podaci o nastavniku [" << nastavnici[index].getIme() << " " << nastavnici[index].getPrezime() << "]:\n" << endl;
                cout << nastavnici[index] << endl;

                system("pause");
                break;
            case 4: // Return to main menu
                return;
            default:
                cout << "Neispravan unos. Molimo unesite pravilan broj opcije." << endl;
                break;
            }
        } while (opcija != 3);
    }

    void admin3_predaje_predmete() {
    }


    void menu() {
        int izbor = 0;
        do {
            system("cls");
            cout << "::ADMIN - meni::" << endl;
            cout << "(0) IZLAZ" << endl;
            cout << "(1) admin - Predmeti - Uredi/Dodaj" << endl;
            cout << "(2) admin - Nastavnici - Uredi/Dodaj" << endl;
            cout << "(3) admin - Nastavnik-predaje-predmete - Uredi" << endl;
            //itd.
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;

            switch (izbor) {
            case 1: admin1_predmeti(); break;
            case 2: admin2_nastavnici(); break;
            case 3: admin3_predaje_predmete(); break;
            default:break;
            }

        } while (izbor != 0);
    }
};

int main() {
    DlwmsApp app;
    app.menu();
    return 0;
}