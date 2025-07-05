#include <iostream>
#include <iomanip>

using namespace std;

char *alocirajTekst(const char *source)
{
    if (source == nullptr)
        return nullptr;
    int len = strlen(source) + 1;
    char *temp = new char[len];
    strcpy_s(temp, len, source);
    return temp;
}

const char *crt = "\n--------------------------------\n";
class KupljeniArtikal
{
    char *_naziv = nullptr;
    float _cijena;
    int _kolicina;
    // konstruktor, destruktor i potrebne funkcije
public:
    KupljeniArtikal(const char *naziv = "N/A", float cijena = 0.f)
    {
        _naziv = alocirajTekst(naziv);
        _cijena = cijena;
        _kolicina = 1;
    }
    KupljeniArtikal(KupljeniArtikal &drugi)
    {
        // cout << "konstruktor kopije za " << drugi._naziv << endl;
        delete[] _naziv;
        _naziv = alocirajTekst(drugi.getNaziv());
        _cijena = drugi._cijena;
        _kolicina = drugi._kolicina;
    }
    KupljeniArtikal &operator=(KupljeniArtikal &drugi)
    {
        // cout << "konstruktor kopije za " << drugi._naziv << endl;
        if (this != &drugi)
        {
            delete[] _naziv;
            _naziv = alocirajTekst(drugi.getNaziv());
            _cijena = drugi._cijena;
            _kolicina = drugi._kolicina;
        }
        return *this;
    }
    ~KupljeniArtikal()
    {
        // cout << "Destruktor artikal " << _naziv << endl;
        delete[] _naziv;
        _naziv = nullptr;
    }

    const char *getNaziv() const { return (_naziv == nullptr) ? "" : _naziv; }
    float getCijena() const { return _cijena; }
    int getKolicina() const { return _kolicina; }

    void operator+=(const float dodaj)
    {
        _cijena += dodaj;
    }
    void operator++()
    {
        ++_kolicina;
    }
    int getKolicina()
    {
        return _kolicina;
    }
    float getCijena()
    {
        return _cijena;
    }
    bool operator==(KupljeniArtikal &drugi)
    {
        return strcmp(drugi._naziv, _naziv) == 0;
    }

    friend ostream &operator<<(ostream &COUT, KupljeniArtikal &a)
    {

        COUT << setw(10) << a.getNaziv() << " " << setw(4) << a._kolicina << " " << setw(5) << a._cijena << " KM " << setw(5) << a._cijena * a._kolicina << "KM";
        return COUT;
    }
};

class Racun
{
    static int _brojacRacuna;
    const int _brojRacuna;               // brojevi racuna krecu od 1
    KupljeniArtikal *_artikli = nullptr; // niz povecavamo prilikom svakog dodavanja artikla
    int _trenutno;

public:
    Racun() : _brojRacuna(_brojacRacuna++)
    {
        _trenutno = 0;
        _artikli = nullptr;
    }
    ~Racun()
    {
        // cout << "Destruktor racun " << _brojRacuna << endl;
        delete[] _artikli;
        _artikli = nullptr;
    }
    void operator+=(KupljeniArtikal &a)
    {
        for (int i = 0; i < _trenutno; i++)
        {
            if (a == _artikli[i])
            {
                for (int j = 0; j < a.getKolicina(); j++)
                    ++_artikli[i];
                return;
            }
        }

        KupljeniArtikal *tmp = new KupljeniArtikal[_trenutno + 1];

        for (int i = 0; i < _trenutno; i++)
        {
            tmp[i] = _artikli[i];
        }
        delete[] _artikli;
        _artikli = tmp;

        _artikli[_trenutno] = a;
        _trenutno++;
    }
    KupljeniArtikal *operator[](int i)
    {
        if (i >= 0 && i < _trenutno)
            return &_artikli[i];
        return nullptr;
    }

    friend ostream &operator<<(ostream &COUT, Racun &racun)
    {
        COUT << "Broj racuna: " << racun._brojRacuna << endl;
        COUT << "Ukupno artikala: " << racun._trenutno;
        COUT << crt;
        float ukupno = 0;
        for (int i = 0; i < racun._trenutno; i++)
        {
            COUT << *racun[i] << endl;
            ukupno += racun[i]->getCijena() * racun[i]->getKolicina();
        }
        COUT << crt;
        COUT << "Ukupno: " << ukupno << "KM";
        return COUT;
    }

    KupljeniArtikal *operator()(float ukupnaCijena, int &brojPronadjenih)
    {
        for (int i = 0; i < _trenutno; i++)
        {
            if (_artikli[i].getCijena() * _artikli[i].getKolicina() >= ukupnaCijena)
                brojPronadjenih++;
        }

        int brojac = 0;
        KupljeniArtikal *niz = new KupljeniArtikal[brojPronadjenih];
        for (int i = 0; i < _trenutno; i++)
        {
            if (_artikli[i].getCijena() * _artikli[i].getKolicina() >= ukupnaCijena)
                niz[brojac++] = _artikli[i];
        }
        return niz;
    }
};

int Racun::_brojacRacuna = 1;

void main()
{
    KupljeniArtikal cokolada("Milka", 2.29); // naziv i cijena artikla
    KupljeniArtikal sok("Jucy", 1.38);
    KupljeniArtikal cigarete("Drina", 4.32);
    KupljeniArtikal mlijeko("Meggle", 2.87);
    cokolada += 0.27; // povecavamo cijenu artikla, sada je cijena 2,56BAM
    ++cokolada;       // povecavamo kolicinu artikla, sada je kolicina 2
    ++sok;
    Racun racun;
    racun += cokolada; // dodajemo 2 cokolade po cijeni od 2,56BAM
    racun += sok;
    racun += sok; // ako vise puta pokusamo dodati isti artikal, treba da se uveca samo
    // njegova kolicina na racunu tj.artikli se ne smiju duplirati
    racun += cigarete;
    racun += mlijeko;
    cout << racun << endl; // ispis racuna mozete vidjeti na slici.

    int brojPronadjenih = 0;
    float ukupnaCijena = 5.10;
    cout << crt << "Artikli skuplji od >> " << ukupnaCijena << crt;
    // treba da vrati sve artikle cija je ukupna cijena na racunu (cijena * kolicina)
    // veca od poslane tj. 5.10BAM
    KupljeniArtikal *artikli = racun(ukupnaCijena, brojPronadjenih);
    if (artikli != nullptr)
    {
        for (size_t i = 0; i < brojPronadjenih; i++)
        {
            cout << artikli[i] << endl;
        }
    }
    delete[] artikli;
    artikli = nullptr;
}