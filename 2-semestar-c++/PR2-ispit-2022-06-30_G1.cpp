#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <regex>
#include <fstream>

using namespace std;

char* GetNizKaraktera(const char* source) {
    if (source == nullptr)
        return nullptr;
    int size = strlen(source) + 1;
    char* temp = new char[size];
    strcpy_s(temp, size, source);
    return temp;
}

unique_ptr<char[]> alocirajUnique(const char* source) {
    if (source == nullptr)
        return nullptr;
    int size = strlen(source) + 1;
    unique_ptr<char[]> temp = make_unique<char[]>(size);
    strcpy_s(temp.get(), size, source);
    return temp;
}

const char* crt = "\n-------------------------------------------\n";
enum Karakteristike { NARUDZBA, KVALITET, PAKOVANJE, ISPORUKA };
ostream& operator<<(ostream& COUT, const Karakteristike& obj) {
    switch (obj) {
    case NARUDZBA: COUT << "NARUDZBA"; break;
    case KVALITET: COUT << "KVALITET"; break;
    case PAKOVANJE: COUT << "PAKOVANJE"; break;
    case ISPORUKA: COUT << "ISPORUKA"; break;
    default:
        break;
    }
    return COUT;
}

/*
    * za validaciju broja pasosa koristiti funkciju ValidirajBrojPasosa koja treba, koristeci regex, osigurati postivanje
    sljedeceg formata:
    - pocetak sadrzi jedan ili dva velika slova unutar uglastih zagrada
    - nakon toga slijede tri ili cetiri broja
    - nakon toga moze, a ne mora, doci znak crtica (-) ili razmak ( )
    - nakon toga slijede dva mala slova unutar viticastih zagrada

    pomenutu funkciju iskoristiti u konstruktoru klase Kupac, te ukoliko jedinstveni kod  nije u validnom formatu onda njegova vrijednost treba biti postavljena na NOT VALID
    */

//if (ValidirajJedinstveniKod("[BH]235-{mo}"))
//cout << "Jedinstveni kod validan" << endl;

bool ValidirajJedinstveniKod(string brojPasosa) {
    string uzorak = "\\[[A-Z]{1,2}\\]\\d{3,4}[\\-\\s]?\\{[a-z]{2}\\}";
    regex regObj(uzorak);
    return regex_match(brojPasosa, regObj);
}

mutex mutexObj;

template<class T1, class T2, int max>
class Kolekcija {
    T1* _elementi1[max] = {nullptr};
    T2* _elementi2[max] = {nullptr};
    int* _trenutno = nullptr;
    bool _omoguciDupliranje;

public:
    Kolekcija(bool omoguciDupliranje = true) {
        _omoguciDupliranje = omoguciDupliranje;
        setTrenutno(0);
        setElementi();
    };
    Kolekcija(const Kolekcija& obj) {
        _omoguciDupliranje = obj._omoguciDupliranje;
        setTrenutno(obj.getTrenutno());
        setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if(this != &obj) {
            _omoguciDupliranje = obj._omoguciDupliranje;
            setTrenutno(obj.getTrenutno());
            setElementi(obj.getTrenutno(), obj.getElementi1(), obj.getElementi2());
        }
        return *this;
    }
    T1& getElement1(int lokacija) const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija) const { return *_elementi2[lokacija]; }
    int getTrenutno() const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj.getTrenutno(); i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    // moje metode

    void Dealociraj() {
        for (int i = 0; i < getTrenutno(); i++) {
            delete _elementi1[i];
            delete _elementi2[i];
            _elementi1[i] = nullptr;
            _elementi2[i] = nullptr;
        }
    }

    T1** getElementi1() const { return (T1**)_elementi1; }
    T2** getElementi2() const { return (T2**)_elementi2; }

    void setTrenutno(int tren) {
        if (_trenutno == nullptr)
            _trenutno = new int;
        *_trenutno = tren;
    }

    void setElementi(int trenutno = 0, T1** elementi1 = nullptr, T2** elementi2 = nullptr) {
        Dealociraj();
        setTrenutno(0);

        if (elementi1 != nullptr && elementi2 != nullptr) {
            for (int i = 0; i < trenutno; i++) {
                AddElement(*elementi1[i], *elementi2[i]);
            }
        }
    }

    bool postojiDuplikat(const T1& el1) {
        for (int i = 0; i < getTrenutno(); i++) {
            if (*_elementi1[i] == el1)
                return true;
        }
        return false;
    }

    void AddElement(const T1& el1, const T2& el2) {
        if (_omoguciDupliranje == false && postojiDuplikat(el1))
            throw exception("Dupliranje elemenata nije dozvoljeno!");
        if (getTrenutno() >= max)
            throw exception("Kolekcija je popunjena!");
        _elementi1[getTrenutno()] = new T1(el1);
        _elementi2[getTrenutno()] = new T2(el2);
        setTrenutno(getTrenutno() + 1);
    }

    //Kolekcija<int, int, KolekcijaTestSize> Kolekcija2 = Kolekcija1.RemoveAt(2);

    Kolekcija<T1, T2, max> RemoveAt(int lokacija) {
        if (lokacija < 0 || lokacija >= getTrenutno())
            throw exception("Indeks van granica!");
        Kolekcija<T1, T2, max> temp;
        temp.AddElement(*_elementi1[lokacija], *_elementi2[lokacija]);
        for (int i = lokacija; i < getTrenutno() - 1; i++) {
            swap(_elementi1[i], _elementi1[i + 1]);
            swap(_elementi2[i], _elementi2[i + 1]);
        }
        delete _elementi1[getTrenutno() - 1];
        delete _elementi2[getTrenutno() - 1];
        _elementi1[getTrenutno() - 1] = nullptr;
        _elementi2[getTrenutno() - 1] = nullptr;

        setTrenutno(getTrenutno() - 1);

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
        setDan(obj.getDan());
        setMjesec(obj.getMjesec());
        setGodina(obj.getGodina());
    }
    Datum& operator=(const Datum& obj) {
        if(this!=&obj){
            setDan(obj.getDan());
            setMjesec(obj.getMjesec());
            setGodina(obj.getGodina());
        }
        return *this;
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << obj.getDan() << "." << obj.getMjesec() << "." << obj.getGodina();
        return COUT;
    }

    // moje metode

    int getDan() const { return _dan == nullptr ? 1 : *_dan; }
    int getMjesec() const { return _mjesec == nullptr ? 1 : *_mjesec; }
    int getGodina() const { return _godina == nullptr ? 2000 : *_godina; }

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
};
class ZadovoljstvoKupca {
    char* _komentar = nullptr;
    //uz komentar, kupci mogu ocijeniti svaku od karakteristika proizvoda, a int se odnosi na ocjenu u rasponu od 1 - 10.
    //onemoguciti dupliranje karakteristika tj. svaki karakteristika se moze ocijeniti samo jednom...u suprotnom baciti objekat tipa exception
    Kolekcija<Karakteristike, int, 4>* _ocjeneKarakteristika = nullptr;
public:
    ZadovoljstvoKupca(const char* komentar = "") {
        //kreirajte funkciju GetNizKaraktera ili na drugi adekvatan nacin izvrsite inicijalizaciju pokazivaca
        _komentar = GetNizKaraktera(komentar);
        _ocjeneKarakteristika = new Kolekcija<Karakteristike, int, 4>(false);
    }
    ZadovoljstvoKupca(const ZadovoljstvoKupca& obj) {
        delete[] _komentar;
        _komentar = GetNizKaraktera(obj.GetKomentar());
        setOcjeneKarakteristika(obj.constGetOcjeneKarakteristika());
    }
    ZadovoljstvoKupca& operator=(const ZadovoljstvoKupca& obj) {
        if(this!=&obj){
            delete[] _komentar;
            _komentar = GetNizKaraktera(obj.GetKomentar());
            setOcjeneKarakteristika(obj.constGetOcjeneKarakteristika());
        }
        return *this;
    }
    ~ZadovoljstvoKupca() {
        delete[] _komentar; _komentar = nullptr;
        delete _ocjeneKarakteristika; _ocjeneKarakteristika = nullptr;
    }
    char* GetKomentar() const { return _komentar; }
    Kolekcija<Karakteristike, int, 4>* GetOcjeneKarakteristika() { return _ocjeneKarakteristika; }
    Kolekcija<Karakteristike, int, 4> constGetOcjeneKarakteristika() const { return *_ocjeneKarakteristika; }

    void setOcjeneKarakteristika(Kolekcija<Karakteristike, int, 4> ocjene) {
        if (_ocjeneKarakteristika == nullptr)
            _ocjeneKarakteristika = new Kolekcija<Karakteristike, int, 4>(false);
        *_ocjeneKarakteristika = ocjene;
    }

    void AddOcjenuKarakteristike(Karakteristike karakteristika, int ocjena) {
        _ocjeneKarakteristika->AddElement(karakteristika, ocjena);
    }

    friend ostream& operator<<(ostream& COUT, const ZadovoljstvoKupca& obj) {
        COUT << "Komentar: " << obj.GetKomentar() << endl;
        for (int i = 0; i < obj.constGetOcjeneKarakteristika().getTrenutno(); i++) {
            COUT << "\t" << obj.constGetOcjeneKarakteristika().getElement1(i) << " : " << obj.constGetOcjeneKarakteristika().getElement2(i) << endl;
        }
        return COUT;
    }

    float getProsjecnaOcjena() const {
        if (_ocjeneKarakteristika->getTrenutno() == 0)
            return 0;
        float suma = 0.0f;
        for (int i = 0; i < _ocjeneKarakteristika->getTrenutno(); i++) {
            suma += _ocjeneKarakteristika->getElement2(i);
        }
        return suma / _ocjeneKarakteristika->getTrenutno();
    }
};

class Kupac {
    unique_ptr<char[]>_imePrezime;
    string _emailAdresa;
    string _jedinstveniKod;
public:
    Kupac(const char* imePrezime, string emailAdresa, string jedinstveniKod) {
        _imePrezime = alocirajUnique(imePrezime);
        _emailAdresa = emailAdresa;
        _jedinstveniKod = (ValidirajJedinstveniKod(jedinstveniKod)) ? jedinstveniKod : "NOT VALID";
    }
    Kupac(const Kupac& obj) {
        _imePrezime = alocirajUnique(obj.GetImePrezime());
        _emailAdresa = obj.GetEmail();
        _jedinstveniKod = obj.GetJedinstveniKod();
    }
    Kupac& operator=(const Kupac& obj) {
        if(this!=&obj){
            _imePrezime = alocirajUnique(obj.GetImePrezime());
            _emailAdresa = obj.GetEmail();
            _jedinstveniKod = obj.GetJedinstveniKod();
        }
        return *this;
    }
    string GetEmail() const { return _emailAdresa; }
    string GetJedinstveniKod() const { return _jedinstveniKod; }
    char* GetImePrezime() const { return _imePrezime.get(); }

    friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._jedinstveniKod << endl;
        return COUT;
    }
};

class Kupovina {
    Datum _datumKupovine;
    //jedna kupovina moze podrazumjevati isporuku proizvoda vecem broju kupaca
    //onemoguciti dodavanje kupaca sa istom email adresom ili jedinstvenim kodom u okviru jedne kupovine
    vector<Kupac> _kupci;
    //za svaku kupovinu se moze ostaviti samo jedan komentar odnosno ocjena zadovoljstva, bez obzira na broj kupaca
    ZadovoljstvoKupca _zadovoljstvoKupca;

public:
    Kupovina(Datum& datum, Kupac& kupac) : _datumKupovine(datum) {
        _kupci.push_back(kupac);
    }
    Kupovina(const Kupovina& obj) {
        _datumKupovine = obj._datumKupovine;
        _kupci = obj._kupci;
        _zadovoljstvoKupca = obj._zadovoljstvoKupca;
    }
    Kupovina& operator=(const Kupovina& obj) {
        if(this!=&obj){
            _datumKupovine = obj._datumKupovine;
            _kupci = obj._kupci;
            _zadovoljstvoKupca = obj._zadovoljstvoKupca;
        }
        return *this;
    }
    vector<Kupac>& GetKupci() { return _kupci; }
    ZadovoljstvoKupca GetZadovoljstvoKupca() { return _zadovoljstvoKupca; }

    bool AddKupca(Kupac& kupac) {
        for (int i = 0; i < _kupci.size(); i++) {
            if (_kupci[i].GetEmail() == kupac.GetEmail() || _kupci[i].GetJedinstveniKod() == kupac.GetJedinstveniKod())
                return false;
        }
        _kupci.push_back(kupac);
        return true;
    }

    void PosaljiEmail() {
        mutexObj.lock();
        this_thread::sleep_for(chrono::seconds(2));
        cout << "To: ";
        for (int i = 0; i < _kupci.size(); i++) {
            cout << _kupci[i].GetEmail() << ";";
        }
        cout << "Subject: Informacija\n\nPostovani,\n\n";
        cout << "Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je " << _zadovoljstvoKupca.getProsjecnaOcjena() << ".\n";
        cout << "Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.\n\n";
        cout << "Nadamo se da cete i dalje poslovati sa nama.\nPuno pozdrava!\n";
        mutexObj.unlock();
    }

    void SetZadovoljstvoKupca(ZadovoljstvoKupca& zadovoljstvo) {
        _zadovoljstvoKupca = zadovoljstvo;

        int brojac = 0;
        for (int i = 0; i < _zadovoljstvoKupca.constGetOcjeneKarakteristika().getTrenutno(); i++) {
            if (_zadovoljstvoKupca.constGetOcjeneKarakteristika().getElement2(i) < 5)
                brojac++;
        }
        if (brojac >= 2) {
            thread SlanjeEmaila(&Kupovina::PosaljiEmail, this);
            SlanjeEmaila.join();
        }
    }
    //ukoliko se kupovini  doda zadovoljstvo koji sadrzi najmanje dvije karakteristike sa ocjenom manjom od 5, svim kupcima, 
    //koji su dodati u kupovinu, u zasebnom thread-u, se salje email sa sljedecim sadrzajem:
   /*
       To: denis@fit.ba;jasmin@fit.ba;
       Subject: Informacija

       Postovani,

       Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je X.X.
       Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.

       Nadamo se da cete i dalje poslovati sa nama
       Puno pozdrava
   */
    friend ostream& operator<< (ostream& COUT, const Kupovina& obj) {
        COUT << crt << "Kupovina " << obj._datumKupovine << " za kupce: " << endl;
        for (size_t i = 0; i < obj._kupci.size(); i++) {
            COUT << "\t" << i + 1 << "." << obj._kupci[i];
        }
        COUT << crt << "Zadovoljstvo kupca: " << endl << obj._zadovoljstvoKupca << crt;
        COUT << "Prosjecna ocjena -> " << obj._zadovoljstvoKupca.getProsjecnaOcjena() << endl;
        return COUT;
    }
    /* Primjer ispisa:
       -------------------------------------------
       Kupovina 30.6.2022 za kupce:
               1.Denis Music denis@fit.ba [BH]235-{mo}
               2.Jasmin Azemovic jasmin@fit.ba [MO]235{sa}
       -------------------------------------------
       Zadovoljstvo kupca:
       Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem.
             NARUDZBA(7)
             KVALITET(4)
             PAKOVANJE(3)
             ISPORUKA(6)
       -------------------------------------------
       Prosjecna ocjena -> 5
   */
    tuple<int, int, int> GetBrojZnakova(string imeFajla) {
        ifstream ispisIzFajla(imeFajla);
        int velikih = 0, malih = 0, razmaka = 0;
        char znak;
        while (ispisIzFajla.get(znak)) {
            if (znak >= 'A' && znak <= 'Z')
                velikih++;
            if (znak >= 'a' && znak <= 'z')
                malih++;
            if (znak == ' ')
                razmaka++;
        }
        ispisIzFajla.close();

        return make_tuple(velikih, malih, razmaka);
    }
    /*metoda GetBrojZnakova treba prebrojati koliko se unutar fajla, cije ime je proslijedjeno kao parametar, nalazi: velikih slova, malih slova i razmaka..*/
    /*
    ukoliko je sadrzaj fajla npr. "Denis Music" povratne vrijednosti metode GetBrojZnakova bi trebale biti 2 8 1. za potrebe testiranja kreirajte fajl sa zeljenim sadzajem
    */
};

const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> \Nabrojite i ukratko pojasnite osnovne ios modove koji se koriste u radu sa fajlovima?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasnite prednosti i nedostatke visestrukog nasljedjivaja, te ulogu virtualnog nasljedjivanja u tom kontekstu?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    /*cout << PORUKA;
    cin.get();*/

    /*cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();*/

    Datum datum30062022(30, 6, 2022);

    const int KolekcijaTestSize = 9;
    Kolekcija<int, int, KolekcijaTestSize> Kolekcija1(false);

    for (int i = 0; i < KolekcijaTestSize - 1; i++)
        Kolekcija1.AddElement(i, i);//dodaje vrijednosti u Kolekcija

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement treba baciti objekat tipa exception
        Kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    Kolekcija1.AddElement(9, 9);

    try {
        //ukoliko je Kolekcija popunje, metoda AddElement treba baciti objekat tipa exception
        Kolekcija1.AddElement(10, 10);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    cout << Kolekcija1 << crt;

    /* metoda RemoveAt treba da ukloni i vrati (kao povratnu vrijednost)clanoveKolekcija koji se nalaze na lokaciji definisanoj prvim parametrom.
    * Nakon izvrsenja metode RemoveAt, objekat Kolekcija1 bi trebao posjedovati sljedeci sadrzaj:
    * 0  0
    * 1  1
    * 3  3
    * 4  4
    * ....
    *
    * a objekat Kolekcija2 samo jedan par:
    *  2  2
    */
    Kolekcija<int, int, KolekcijaTestSize> Kolekcija2 = Kolekcija1.RemoveAt(2);
    cout << Kolekcija2 << crt;


    /*
    * za validaciju broja pasosa koristiti funkciju ValidirajBrojPasosa koja treba, koristeci regex, osigurati postivanje
    sljedeceg formata:
    - pocetak sadrzi jedan ili dva velika slova unutar uglastih zagrada
    - nakon toga slijede tri ili cetiri broja
    - nakon toga moze, a ne mora, doci znak crtica (-) ili razmak ( )
    - nakon toga slijede dva mala slova unutar viticastih zagrada

    pomenutu funkciju iskoristiti u konstruktoru klase Kupac, te ukoliko jedinstveni kod  nije u validnom formatu onda njegova vrijednost treba biti postavljena na NOT VALID
    */

    if (ValidirajJedinstveniKod("[BH]235-{mo}"))
        cout << "Jedinstveni kod validan" << endl;
    if (ValidirajJedinstveniKod("[MO]235{sa}"))
        cout << "Jedinstveni kod validan" << endl;
    if (ValidirajJedinstveniKod("[B]2356 {ih}"))
        cout << "Jedinstveni kod validan" << endl;
    if (!ValidirajJedinstveniKod("[s]2356{ih}"))
        cout << "Jedinstveni kod NIJE validan" << endl;
    if (!ValidirajJedinstveniKod("[BH]2356{h}"))
        cout << "Jedinstveni kod NIJE validan" << endl;
    if (!ValidirajJedinstveniKod("BH2356{ih}"))
        cout << "Jedinstveni kod NIJE validan" << endl;


    Kupac denis("Denis Music", "denis@fit.ba", "[BH]235-{mo}");
    Kupac jasmin("Jasmin Azemovic", "jasmin@fit.ba", "[MO]235{sa}");
    Kupac adel("Adel Handzic", "adel@edu.fit.ba", "[B]2356 {ih}");
    Kupac jedinstveniKodNotValid("Ime Prezime", "korisnik@klix.ba", "BH2356{ih}");//_jedinstveniKod = NOT VALID

    //kupovini  se prilikom kreiranja mora dodijeliti kupac koji je kreator kupovine
    Kupovina kupovina(datum30062022, denis);
    if (kupovina.AddKupca(jasmin))
        cout << "Kupac uspjesno dodan!";

    ZadovoljstvoKupca zadovoljstvoKupca("Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem");
    zadovoljstvoKupca.AddOcjenuKarakteristike(NARUDZBA, 7);
    zadovoljstvoKupca.AddOcjenuKarakteristike(KVALITET, 4);

    try {
        zadovoljstvoKupca.AddOcjenuKarakteristike(KVALITET, 4); //kakrakteristika je vec ocjenjena
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    zadovoljstvoKupca.AddOcjenuKarakteristike(PAKOVANJE, 3);
    zadovoljstvoKupca.AddOcjenuKarakteristike(ISPORUKA, 6);

    //u okviru kupovine postavlja vrijednost atributa _zadovoljstvoKupca
    kupovina.SetZadovoljstvoKupca(zadovoljstvoKupca);

    //ukoliko se kupovini  doda zadovoljstvo koji sadrzi najmanje dvije karakteristike sa ocjenom manjom od 5, svim kupcima, 
    //koji su dodati u kupovinu, u zasebnom thread-u, se salje email sa sljedecim sadrzajem:
   /*
       To: denis@fit.ba;jasmin@fit.ba;
       Subject: Informacija

       Postovani,

       Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je X.X.
       Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.

       Nadamo se da cete i dalje poslovati sa nama
       Puno pozdrava
   */

   //ispisuje sve podatke o kupovini, kupcima, komentar, ocjene pojedinih karakteristika i prosjecnu ocjenu.
    cout << kupovina << endl;
    /* Primjer ispisa:
       -------------------------------------------
       Kupovina 30.6.2022 za kupce:
               1.Denis Music denis@fit.ba [BH]235-{mo}
               2.Jasmin Azemovic jasmin@fit.ba [MO]235{sa}
       -------------------------------------------
       Zadovoljstvo kupca:
       Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem.
             NARUDZBA(7)
             KVALITET(4)
             PAKOVANJE(3)
             ISPORUKA(6)
       -------------------------------------------
       Prosjecna ocjena -> 5
   */

    Kupovina kupovinaSaAdelom = kupovina;
    if (kupovinaSaAdelom.AddKupca(adel))
        cout << "Kupac uspjesno dodan!";
    if (!kupovinaSaAdelom.AddKupca(denis))
        cout << "Kupac je vec dodan!";

    cout << kupovinaSaAdelom << endl;

    /*metoda GetBrojZnakova treba prebrojati koliko se unutar fajla, cije ime je proslijedjeno kao parametar, nalazi: velikih slova, malih slova i razmaka..*/
    tuple<int, int, int> brojac = kupovinaSaAdelom.GetBrojZnakova("sadrzaj.txt");
    cout << "Velikih slova: " << get<0>(brojac) << endl;
    cout << "Malih slova: " << get<1>(brojac) << endl;
    cout << "Razmaka: " << get<2>(brojac) << endl;
    /*
    ukoliko je sadrzaj fajla npr. "Denis Music" povratne vrijednosti metode GetBrojZnakova bi trebale biti 2 8 1. za potrebe testiranja kreirajte fajl sa zeljenim sadzajem
    */
    
    cin.get();
    system("pause>0");
}
