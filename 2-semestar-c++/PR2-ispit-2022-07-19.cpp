#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <regex>
#include <thread>
#include <mutex>
using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. METODE I KLASE KOJE NE IMPLEMENTIRATE NEMOJTE BRISATI (BEZ OBZIRA STO NEMAJU IMPLEMENTACIJU)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11. ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA (POZIVA FUNKCIJA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12. ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022!\n"
"-------------------------------------------------------------------------------\n";

mutex mutexObj;

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

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
}

template<class T1, class T2>
class Rjecnik {
	T1* _elementi1 = nullptr;
	T2* _elementi2 = nullptr;
	int _trenutno;
	bool _omoguciDupliranje;
public:
	Rjecnik(bool omoguciDupliranje = true) {
		_omoguciDupliranje = omoguciDupliranje;
		_trenutno = 0;

	}
	/*if constexpr (is_same_v<T2, const char*>) {
			cout << "Destruktor const char*" << endl;
			for (int i = 0; i < _trenutno; i++) {
				delete[] _elementi2[i];
				_elementi2[i] = nullptr;
			}
		}*/
	Rjecnik(const Rjecnik& obj) {
		_trenutno = obj._trenutno;
		_omoguciDupliranje = obj._omoguciDupliranje;
		setElementi(obj._trenutno, obj._elementi1, obj._elementi2);
	}
	Rjecnik& operator=(const Rjecnik& obj) {
		if(this!=&obj) {
			_trenutno = obj._trenutno;
			_omoguciDupliranje = obj._omoguciDupliranje;
			setElementi(obj._trenutno, obj._elementi1, obj._elementi2);
		}
		return *this;
	}
	~Rjecnik() {
		delete[] _elementi1; _elementi1 = nullptr;

		if constexpr (is_same_v<T2, const char*>) {
			//cout << "Destruktor const char*" << endl;
			for (int i = 0; i < _trenutno; i++) {
				delete[] _elementi2[i];
				_elementi2[i] = nullptr;
			}
		}

		delete[] _elementi2; _elementi2 = nullptr;

	}
	T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() const { return _trenutno; }
	friend ostream& operator<< (ostream& COUT, const Rjecnik& obj) {
		/*
			//metoda GetKupovineByKomentar treba da pronadje i vrati sve karakteristike proizvoda i komentare kupaca koji sadrze vrijednost proslijedjenog parametra
	Rjecnik<Karakteristike, const char*> osteceniProizvodi = denis->GetKupovineByKomentar("ostecen");
	cout << crt << "Rezultat pretrage -> " << crt << osteceniProizvodi << crt;

		Ocekivani ispis:
		-------------------------------------------
		Rezultat pretrage ->
		-------------------------------------------
		PAKOVANJE Pakovanje je bio osteceno
		KVALITET Jako lose, proizvod ostecen
		-------------------------------------------
	*/
		if constexpr (is_same_v<T1, Karakteristike> && is_same_v<T2, const char*>) {
			for (int i = 0; i < obj.getTrenutno(); i++) {
				cout << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
			}
			cout << crt;
			return COUT;
		}
		else {
			for (size_t i = 0; i < obj._trenutno; i++)
				COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
			return COUT;
		}
	}

	void setElementi(int trenutno = 0, T1* elementi1 = nullptr, T2* elementi2 = nullptr) {
		delete[] _elementi1;
		delete[] _elementi2;

		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];

		_trenutno = 0;
		if (elementi1 != nullptr && elementi2 != nullptr) {
			for (int i = 0; i < trenutno; i++) {
				AddElement(elementi1[i], elementi2[i]);
			}
		}
	}

	void AddElement(const T1& el1, const T2& el2) {
		if (_omoguciDupliranje == false && provjeriDuplikat(el1))
			throw exception("Dupliranje nije dozvoljeno!");
		expand();
		_elementi1[_trenutno] = el1;

		if constexpr (is_same_v<T2, const char*>) {
			//cout << "Proslijedjen const char*" << endl;
			_elementi2[_trenutno] = GetNizKaraktera(el2);
		}
		else {
			_elementi2[_trenutno] = el2;
		}

		_trenutno++;
	}

	bool provjeriDuplikat(const T1& el1) {
		for (int i = 0; i < _trenutno; i++) {
			if (el1 == _elementi1[i])
				return true;
		}
		return false;
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

	Rjecnik<T1, T2> operator()(int from, int to) {
		if (from < 0 || from >= _trenutno || to < 0 || to >= _trenutno)
			throw exception("Indeks van granica!");
		Rjecnik<T1, T2> temp;
		for (int i = from; i <= to; i++) {
			temp.AddElement(_elementi1[i], _elementi2[i]);
		}
		return temp;
	}

	void setDupliranje(bool omoguciDupliranje = false) {
		_omoguciDupliranje = omoguciDupliranje;
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
		if(this != &obj) {
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
	int _ocjena; //za svaku kupovinu kupac moze ostaviti jednu ocjenu
	//uz ocjenu, kupci mogu komentarisati svaku od karakteristika proizvoda.
	//onemoguciti dupliranje karakteristika tj. svaka karakteristika se moze komentarisati samo jednom...u suprotnom baciti objekat tipa exception
	Rjecnik<Karakteristike, const char*> _komentariKarakteristika;
public:
	ZadovoljstvoKupca(int ocjena = 0) {
		_ocjena = ocjena;
		_komentariKarakteristika.setDupliranje(false);
	}
	ZadovoljstvoKupca(const ZadovoljstvoKupca& obj) {
		_ocjena = obj._ocjena;
		_komentariKarakteristika = obj._komentariKarakteristika;
	}
	ZadovoljstvoKupca& operator=(const ZadovoljstvoKupca& obj) {
		if(this!=&obj){
			_ocjena = obj._ocjena;
			_komentariKarakteristika = obj._komentariKarakteristika;
		}
		return *this;
	}
	int GetOcjena() const { return _ocjena; }
	Rjecnik<Karakteristike, const char*>& GetKomentareKarakteristika() { return _komentariKarakteristika; }

	void DodajKomentarKarakteristike(Karakteristike karakteristika, const char* komentar) {
		_komentariKarakteristika.AddElement(karakteristika, komentar);
	}
};

class Osoba {
protected:
	char* _imePrezime = nullptr;
	Datum _datumRodjenja;
public:
	Osoba(const char* imePrezime = "", Datum datumRodjenja = Datum()) : _datumRodjenja(datumRodjenja) {
		_imePrezime = GetNizKaraktera(imePrezime);
	}
	Osoba(const Osoba& obj) {
		setImePrezime(obj.GetImePrezime());
		_datumRodjenja = obj._datumRodjenja;
	}
	Osoba& operator=(const Osoba& obj) {
		if(this!=&obj) {
			setImePrezime(obj.GetImePrezime());
			_datumRodjenja = obj._datumRodjenja;
		}
		return *this;
	}
	virtual ~Osoba() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	char* GetImePrezime() const { return _imePrezime; }
	Datum& GetDatumRodjenja() { return _datumRodjenja; }

	virtual void Info() = 0;
	friend ostream& operator<< (ostream& COUT, const Osoba& obj) {
		COUT << obj._imePrezime << " " << obj._datumRodjenja << endl;
		return COUT;
	}

	void setImePrezime(const char* source) {
		delete[] _imePrezime;
		_imePrezime = GetNizKaraktera(source);
	}
};

class Kupac : public Osoba{
	char* _emailAdresa = nullptr;
	//float se odnosi na iznos racuna za odredjenu kupovinu
	Rjecnik<float, ZadovoljstvoKupca>* _kupovine;
	vector<int> _bodovi; // bodovi sakupljeni tokom kupovine, svakih potrosenih 10KM donosi po 1 bod.
public:
	Kupac(const char* imePrezime = "", Datum datumRodjenja = Datum(), const char* emailAdresa = "") : Osoba(imePrezime, datumRodjenja){
		_emailAdresa = GetNizKaraktera(emailAdresa);
		_kupovine = new Rjecnik<float, ZadovoljstvoKupca>(true);
	}
	Kupac(const Kupac& obj) : Osoba(obj) {
		setEmail(obj.GetEmail());
		setKupovine(obj.constGetKupovine());
		_bodovi = obj.GetBodovi();
	}
	Kupac& operator=(const Kupac& obj) {
		if(this!=&obj) {
			(Osoba&)(*this) = obj;
			setEmail(obj.GetEmail());
			setKupovine(obj.constGetKupovine());
			_bodovi = obj.GetBodovi();
		}
		return *this;
	}
	~Kupac() {
		delete[] _emailAdresa; _emailAdresa = nullptr;
		delete _kupovine; _kupovine = nullptr;
	}
	char* GetEmail() const { return _emailAdresa; }
	Rjecnik<float, ZadovoljstvoKupca>& GetKupovine() { return *_kupovine; }
	Rjecnik<float, ZadovoljstvoKupca> constGetKupovine() const { return *_kupovine; }
	vector<int> GetBodovi() const { return _bodovi; }
	int GetBodoviUkupno() {
		int ukupno = 0;
		for (size_t i = 0; i < _bodovi.size(); i++) ukupno += _bodovi[i];
		return ukupno;
	}

	void setEmail(const char* source) {
		delete[] _emailAdresa;
		_emailAdresa = GetNizKaraktera(source);
	}
	void setKupovine(Rjecnik<float, ZadovoljstvoKupca> kupovine) {
		if (_kupovine == nullptr)
			_kupovine = new Rjecnik<float, ZadovoljstvoKupca>(true);
		*_kupovine = kupovine;
	}

	friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
		COUT << crt << obj._imePrezime << " " << obj._datumRodjenja << " " << obj._emailAdresa << " " << endl;
		COUT << "KUPOVINE -> " << crt;
		for (size_t i = 0; i < obj._kupovine->getTrenutno(); i++)
			COUT << "Iznos racuna: " << obj._kupovine->getElement1(i) << "KM, zadovoljstvo kupca: " << &obj._kupovine->getElement2(i) << crt;	// ???????
		COUT << "BODOVI -> ";
		for (size_t i = 0; i < obj._bodovi.size(); i++)
			COUT << obj._bodovi[i] << ", ";
		COUT << crt;
		return COUT;
	}

	void Info(){
		cout << crt << GetImePrezime() << " " << GetDatumRodjenja() << " " << GetEmail() << "\n";
		cout << "KUPOVINE -> " << crt;
		for (int i = 0; i < _kupovine->getTrenutno(); i++) {
			cout << "Iznos racuna: " << _kupovine->getElement1(i) << ", zadovoljstvo kupca: " << _kupovine->getElement2(i).GetOcjena() << "\n";
			for (int j = 0; j < _kupovine->getElement2(i).GetKomentareKarakteristika().getTrenutno(); j++) {
				cout << "\t" << _kupovine->getElement2(i).GetKomentareKarakteristika().getElement1(j) << " " << 
					_kupovine->getElement2(i).GetKomentareKarakteristika().getElement2(j) << "\n";
			}
			cout << crt;
		}
		cout << "BODOVI -> ";
		for (int i = 0; i < GetBodovi().size(); i++) {
			cout << GetBodovi()[i] << ", ";
		}
		cout << crt;
	}
	/* Primjer ispisa:
		-------------------------------------------
		Denis Music 12.1.1980 denis@fit.ba
		KUPOVINE ->
		-------------------------------------------
		Iznos racuna: 128KM, zadovoljstvo kupca: 7
				NARUDZBA - Nismo mogli odabrati sve potrebne opcije
				KVALITET - Kvalitet je ocekivan
				PAKOVANJE - Pakovanje je bio osteceno
				ISPORUKA - Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana
		-------------------------------------------
		Iznos racuna: 81KM, zadovoljstvo kupca: 4
				KVALITET - Jako lose, proizvod ostecen
		-------------------------------------------
		BODOVI -> 12, 8,
		-------------------------------------------
   */

	void PosaljiEmail(int bodovi) {
		this_thread::sleep_for(chrono::seconds(2));
		cout << "To: " << GetEmail() << ";\n";
		cout << "Subject: Osvareni bodovi\n\nPostovani,\n\n";
		cout << "Prilikom posljednje kupovine ste ostvarili " << bodovi << " bodova, tako da trenutno vas ukupan broj bodova iznosi " << GetBodoviUkupno() << ".";
		cout << "\n\nZahvaljujemo vam na kupovini.\nPuno pozdrava" << crt;
	}

	/*za svakih 10KM kupcu se dodaje 1 bod, pa ce tako kupovina od 128KM kupcu donijeti 12 bodova*/
	void DodajKupovinu(float iznos, ZadovoljstvoKupca& zadovoljstvoKupca) {
		int bodovi = iznos / 10;
		_kupovine->AddElement(iznos, zadovoljstvoKupca);
		_bodovi.push_back(bodovi);

		if (bodovi > 5) {
			mutexObj.lock();
			thread slanjeEmaila(&Kupac::PosaljiEmail, this, bodovi);
			slanjeEmaila.join();
			mutexObj.unlock();
		}

	}

	///*prilikom svake kupovine, ukoliko je kupac ostvario vise od 5 bodova, potrebno je, u zasebnom thread-u (nakon 3 sekunde), poslati email sa sljedecim sadrzajem:

	//  To: denis@fit.ba;
	//  Subject: Osvareni bodovi

	//  Postovani,

	//  Prilikom posljednje kupovine ste ostvarili 8 bodova, tako da trenutno vas ukupan broj bodova iznosi 20.

	//  Zahvaljujemo vam na kupovini.
	//  Puno pozdrava
 // */

	void SacuvajBodove() {
		string imeFajla = GetEmail();
		imeFajla += ".txt";
		ofstream upisBodova(imeFajla, ios::binary);
		int size = GetBodovi().size();
		upisBodova.write((char*)(&size), sizeof(int));		// prva vrijednost koju smjestamo je velicina vektora
		for (int i = 0; i < size; i++) {
			upisBodova.write((char*)(&GetBodovi()[i]), sizeof(int));
		}
		upisBodova.close();
	}

	/*metoda SacuvajBodove treba sve clanove vector-a _bodovi upisati u fajl(ignorisuci ranije dodate/postojece vrijednosti u fajlu) pod nazivom emailKorisnika.txt npr. denis@fit.ba.txt.
   na osnovu trenutnog stanja objekta, sadrzaj fajla denis@fit.ba.txt bi trebao biti sljedeci:
   12
   8

   nakon spasavanja u fajl, sadrzaj vector-a ostaje nepromijenjen.
   */

   //metoda UcitajBodove ucitava sadrzaj fajla pod nazivom emailKorisnika.txt i njegove vrijednosti pohranjuje/dodaje u vector _bodovi (zadrzavajuci postojece bodove).
	void UcitajBodove() {
		string imeFajla = GetEmail();
		imeFajla += ".txt";
		ifstream ispisBodovaIzFajla(imeFajla, ios::binary);

		int size = 0;
		ispisBodovaIzFajla.read((char*)(&size), sizeof(int));			// prvo vadi velicinu vektora, a "iterira" za sizeof(int) byte-ova

		//vector<int> noviBodovi;
		for (int i = 0; i < size; i++) {
			int element = 0;
			ispisBodovaIzFajla.read((char*)(&element), sizeof(int));			// loada u element ---> (&element)
			_bodovi.push_back(element);
			//cout << "NOVI BODOVI -> " << element << endl;
		}

		ispisBodovaIzFajla.close();
	}


	Rjecnik<Karakteristike, const char*> GetKupovineByKomentar(string uzorak) {
		Rjecnik<Karakteristike, const char*> temp;
		regex regObj(uzorak);
		
		for (int i = 0; i < GetKupovine().getTrenutno(); i++) {
			for (int j = 0; j < GetKupovine().getElement2(i).GetKomentareKarakteristika().getTrenutno(); j++) {
				string tempStr = GetKupovine().getElement2(i).GetKomentareKarakteristika().getElement2(j);
				if (regex_search(tempStr, regObj)) {
					temp.AddElement(GetKupovine().getElement2(i).GetKomentareKarakteristika().getElement1(j), 
						GetKupovine().getElement2(i).GetKomentareKarakteristika().getElement2(j));
				}
				
			}
		}
		return temp;
	}

	//metoda GetKupovineByKomentar treba da pronadje i vrati sve karakteristike proizvoda i komentare kupaca koji sadrze vrijednost proslijedjenog parametra
	//Rjecnik<Karakteristike, const char*> osteceniProizvodi = denis->GetKupovineByKomentar("ostecen");
	//cout << crt << "Rezultat pretrage -> " << crt << osteceniProizvodi << crt;

	/*Ocekivani ispis:
		-------------------------------------------
		Rezultat pretrage ->
		-------------------------------------------
		PAKOVANJE Pakovanje je bio osteceno
		KVALITET Jako lose, proizvod ostecen
		-------------------------------------------
	*/
};

//const char* GetOdgovorNaPrvoPitanje() {
//	cout << "Pitanje -> Nabrojite i ukratko pojasnite osnovne razlike izmedju list i vector klase?\n";
//	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}
//const char* GetOdgovorNaDrugoPitanje() {
//	cout << "Pitanje -> Pojasnite opcije vezane za preslikavanje (vrijednosti, referenci, dostupnost) parametara prilikom koristenja lambda funkcija?\n";
//	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
//}

void main() {

	/*cout << PORUKA;
	cin.get();

	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();*/

	const int rjecnikTestSize = 9;
	Rjecnik<int, int> rjecnik1(false);
	for (int i = 0; i < rjecnikTestSize - 1; i++)
		rjecnik1.AddElement(i, i);//dodaje vrijednosti u rjecnik

	try {
		//ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 ili T2), metoda AddElement treba baciti objekat tipa exception
		rjecnik1.AddElement(3, 3);
	}
	catch (exception& err) {
		cout << err.what() << crt;
	}
	rjecnik1.AddElement(9, 9);

	cout << rjecnik1 << crt;

	/*
	* metoda prihvata indekse lokacije, te vraća elemente koji se u rjecniku nalaze na proslijedjenim lokacijama (ukljucujuci i te lokacije)
	*/
	Rjecnik<int, int> rjecnik2 = rjecnik1(2, 5);
	/*clanovi objekta rjecnik2 bi trebali biti:
	2 2
	3 3
	4 4
	5 5
	*/
	cout << rjecnik2 << crt;


	const int maxKupaca = 3;
	Osoba* kupci[maxKupaca];
	kupci[0] = new Kupac("Denis Music", Datum(12, 1, 1980), "denis@fit.ba");
	kupci[1] = new Kupac("Jasmin Azemovic", Datum(12, 2, 1980), "jasmin@fit.ba");
	kupci[2] = new Kupac("Adel Handzic", Datum(12, 3, 1980), "adel@edu.fit.ba");

	ZadovoljstvoKupca zadovoljstvoKupca(7);
	zadovoljstvoKupca.DodajKomentarKarakteristike(NARUDZBA, "Nismo mogli odabrati sve potrebne opcije");
	zadovoljstvoKupca.DodajKomentarKarakteristike(KVALITET, "Kvalitet je ocekivan");

	try {
		//karakteristika kvalitet je vec komentarisana
		zadovoljstvoKupca.DodajKomentarKarakteristike(KVALITET, "Kvalitet je ocekivan");
	}
	catch (exception& err) {
		cout << err.what() << crt;
	}

	zadovoljstvoKupca.DodajKomentarKarakteristike(PAKOVANJE, "Pakovanje je bio osteceno");
	zadovoljstvoKupca.DodajKomentarKarakteristike(ISPORUKA, "Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana");


	Kupac* denis = dynamic_cast<Kupac*>(kupci[0]);
	/*za svakih 10KM kupcu se dodaje 1 bod, pa ce tako kupovina od 128KM kupcu donijeti 12 bodova*/
	denis->DodajKupovinu(128, zadovoljstvoKupca);
	cout << "Ukupno bodova -> " << denis->GetBodoviUkupno();//12 bodova


	ZadovoljstvoKupca zadovoljstvoKupca2(4);
	zadovoljstvoKupca2.DodajKomentarKarakteristike(KVALITET, "Jako lose, proizvod ostecen");
	denis->DodajKupovinu(81, zadovoljstvoKupca2);

	cout << "Ukupno bodova -> " << denis->GetBodoviUkupno();//20 bodova

	/*prilikom svake kupovine, ukoliko je kupac ostvario vise od 5 bodova, potrebno je, u zasebnom thread-u (nakon 3 sekunde), poslati email sa sljedecim sadrzajem:

	  To: denis@fit.ba;
	  Subject: Osvareni bodovi

	  Postovani,

	  Prilikom posljednje kupovine ste ostvarili 8 bodova, tako da trenutno vas ukupan broj bodova iznosi 20.

	  Zahvaljujemo vam na kupovini.
	  Puno pozdrava
  */


  //ispisuje sve podatke o kupcu i njegovim kupovinama.
	denis->Info();
	/* Primjer ispisa:
		-------------------------------------------
		Denis Music 12.1.1980 denis@fit.ba
		KUPOVINE ->
		-------------------------------------------
		Iznos racuna: 128KM, zadovoljstvo kupca: 7
				NARUDZBA - Nismo mogli odabrati sve potrebne opcije
				KVALITET - Kvalitet je ocekivan
				PAKOVANJE - Pakovanje je bio osteceno
				ISPORUKA - Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana
		-------------------------------------------
		Iznos racuna: 81KM, zadovoljstvo kupca: 4
				KVALITET - Jako lose, proizvod ostecen
		-------------------------------------------
		BODOVI -> 12, 8,
		-------------------------------------------
   */
   /*metoda SacuvajBodove treba sve clanove vector-a _bodovi upisati u fajl(ignorisuci ranije dodate/postojece vrijednosti u fajlu) pod nazivom emailKorisnika.txt npr. denis@fit.ba.txt.
   na osnovu trenutnog stanja objekta, sadrzaj fajla denis@fit.ba.txt bi trebao biti sljedeci:
   12
   8

   nakon spasavanja u fajl, sadrzaj vector-a ostaje nepromijenjen.
   */
	denis->SacuvajBodove();
	//metoda UcitajBodove ucitava sadrzaj fajla pod nazivom emailKorisnika.txt i njegove vrijednosti pohranjuje/dodaje u vector _bodovi (zadrzavajuci postojece bodove).  
	denis->UcitajBodove();

	//metoda GetKupovineByKomentar treba da pronadje i vrati sve karakteristike proizvoda i komentare kupaca koji sadrze vrijednost proslijedjenog parametra
	Rjecnik<Karakteristike, const char*> osteceniProizvodi = denis->GetKupovineByKomentar("ostecen");
	cout << crt << "Rezultat pretrage -> " << crt << osteceniProizvodi << crt;

	/*Ocekivani ispis:
		-------------------------------------------
		Rezultat pretrage ->
		-------------------------------------------
		PAKOVANJE Pakovanje je bio osteceno
		KVALITET Jako lose, proizvod ostecen
		-------------------------------------------
	*/

	for (size_t i = 0; i < maxKupaca; i++)
		delete kupci[i], kupci[i] = nullptr;

	//cin.get();
	system("pause>0");
}
