--1. Kroz SQL kod kreirati bazu podataka Vjezba2
CREATE DATABASE Vjezba2;
GO;
USE Vjezba2;

--2. U pomenutoj bazi kreirati �emu Prodaja
GO;
CREATE SCHEMA Prodaja;
GO;
--�ema je u biti kao namespace, npr sales, management...


--3. U �emi Prodaja kreirati tabele sa sljede�om strukturom:
--Autori
--� AutorID, 11 karaktera i primarni klju�
--� Prezime, 40 karaktera (obavezan unos)
--� Ime, 20 karaktera (obavezan unos)
--� Telefon, 12 karaktera fiksne du�ine, zadana vrijednost �nepoznato�
--� Adresa, 40 karaktera
--� SaveznaDrzava, 2 karaktera fiksne du�ine
--� PostanskiBroj, 5 karaktera fiksne du�ine
--� Ugovor, bit polje (obavezan unos)
--Knjige
--� KnjigaID, 6 karaktera i primarni klju�
--� Naziv, 80 karaktera (obavezan unos)
--� Vrsta, 12 karaktera fiksne du�ine (obavezan unos)
--� IzdavacID, 4 karaktera fiksne duzine
--� Cijena, nov�ani tip podatka
--� Biljeska, 200 karaktera
--� Datum, datumsko-vremenski tip

CREATE TABLE Prodaja.Autori
(
	AutorID VARCHAR(11),
	Ime VARCHAR(20) NOT NULL,
	Prezime VARCHAR(40) NOT NULL,
	Telefon CHAR(12) DEFAULT 'nepoznato',
	Adresa VARCHAR(40),
	SaveznaDrzava CHAR(2),
	PostanskiBroj CHAR(5),
	Ugovor BIT NOT NULL
);

--ALTER TABLE Prodaja.Autori
--ALTER COLUMN AutorID VARCHAR(11) NOT NULL;

--ALTER TABLE Prodaja.Autori
--ADD CONSTRAINT PK_Autori PRIMARY KEY (AutorID);

CREATE TABLE Prodaja.Knjige
(
	KnjigaID VARCHAR(6),
	Naziv VARCHAR(80) NOT NULL,
	Vrsta CHAR(12) NOT NULL,
	IzdavacID CHAR(4),
	Cijena MONEY,
	Biljeska VARCHAR(200),
	Datum DATETIME,
	CONSTRAINT PK_Knjige PRIMARY KEY (KnjigaID)
);
--4. Upotrebom insert naredbe iz tabele Publishers baze Pubs izvr�iti kreiranje i insertovanje podataka u 
--tabelu Izdavaci �eme Prodaja (Nazivi kolona trebaju biti na bosanskom jeziku)

SELECT P.pub_id IzdavacID, P.pub_name NazivIzdavaca, P.city Grad, P.state SaveznaDrzava, P.country Drzava
INTO Prodaja.Izdavaci
FROM pubs.dbo.publishers AS P;

--5. U kreiranoj tabeli Izdavaci provjeriti koje polje je primarni klju�, ukoliko ga nema, prikladno polje 
--proglasiti primarnim klju�em

ALTER TABLE Prodaja.Izdavaci
ADD CONSTRAINT PK_Izdavaci PRIMARY KEY (IzdavacID);

--6. Povezati tabelu Izdavaci sa tabelom Knjige, po uzoru na istoimene tabele baze Pubs
ALTER TABLE Prodaja.Knjige
ADD CONSTRAINT FK_Knjige_Izdavaci FOREIGN KEY (IzdavacID) REFERENCES Prodaja.Izdavaci(IzdavacID);


--7. U �emu Prodaja dodati tabelu sa sljede�om strukturom
--AutoriKnjige
--� AutorID 11 karaktera, spoljni klju�
--� KnjigaID 6 karaktera, spoljni klju�
--� AuOrd kratki cjelobrojni tip podatka
--� **Definisati primarni klju� po uzoru na tabelu TitleAuthor baze Pubs

CREATE TABLE Prodaja.AutoriKnjige
(
	AutorID VARCHAR(11) CONSTRAINT FK_AutoriKnjige_Autori FOREIGN KEY REFERENCES Prodaja.Autori(AutorID),
	KnjigaID VARCHAR(6) CONSTRAINT FK_AutoriKnjige_Knjige FOREIGN KEY REFERENCES Prodaja.Knjige(KnjigaID),
	AuOrd TINYINT,
	CONSTRAINT PK_AutoriKnjige PRIMARY KEY (AutorID, KnjigaID)
);

--8. U kreirane tabele izvr�iti insert podataka iz baze Pubs (Za polje biljeska tabele Knjige na mjestima 
--gdje je vrijednost NULL pohraniti �nepoznata vrijednost�)INSERT INTO Prodaja.AutoriSELECT A.au_id, A.au_fname, A.au_lname, A.phone, A.address, A.state, A.zip, A.contractFROM pubs.dbo.authors as A;SELECT * FROM Prodaja.Autori;INSERT INTO Prodaja.KnjigeSELECT T.title_id, T.title, T.type, T.pub_id, T.price, ISNULL(T.notes,'nepoznata vrijednost'), T.pubdateFROM pubs.dbo.titles AS T;SELECT * FROM Prodaja.Knjige;INSERT INTO Prodaja.AutoriKnjigeSELECT TA.au_id, TA.title_id, TA.au_ordFROM pubs.dbo.titleauthor AS TA;SELECT * FROM Prodaja.AutoriKnjige;--9. U tabeli Autori nad kolonom Adresa promijeniti tip podatka na nvarchar (40)

ALTER TABLE Prodaja.Autori
ALTER COLUMN Adresa NVARCHAR(40);

--10. Prikazati sve autore �ije ime po�inje sa slovom A ili S

SELECT *
FROM Prodaja.Autori AS A
WHERE A.Ime LIKE '[AS]%';

--11. Prikazati knjige gdje cijena nije unesena

SELECT *
FROM Prodaja.Knjige AS K
WHERE K.Cijena IS NULL;

--12. U tabeli Izdavaci nad poljem NazivIzdavaca postaviti ograni�enje kojim se onemogu�uje unos 
--duplikata

ALTER TABLE Prodaja.Izdavaci
ADD CONSTRAINT UQ_Izdavaci_NazivIzdavaca UNIQUE (NazivIzdavaca);


--13. Prikladnim primjerima testirati postavljeno ograni�enje na polju NazivIzdavaca

SELECT * FROM Prodaja.Izdavaci;

INSERT INTO Prodaja.Izdavaci (IzdavacID, NazivIzdavaca)
VALUES ('1234', 'New Moon Books');

--14. U bazi Vjezba2 kreirati �emu Narudzbe

GO;
CREATE SCHEMA Narudzbe;

--15. Upotrebom insert naredbe iz tabele Region baze Northwind izvr�iti kreiranje i insertovanje podataka 
--u tabelu Regije �eme Narud�be

SELECT R.RegionID RegijaID, R.RegionDescription OpisRegije
INTO Narudzbe.Regije
FROM Northwind.dbo.Region AS R;

--16. Prikazati sve podatke koji se nalaze u tabeli Regije

SELECT * FROM Narudzbe.Regije;

--17. U tabelu Regije insertovati zapis:
--5 SE

INSERT INTO Narudzbe.Regije (RegijaID, OpisRegije)
VALUES (5, 'SE');

--18. U tabelu Regije insertovati zapise:
--6 NE
--7 NW

INSERT INTO Narudzbe.Regije (RegijaID, OpisRegije)
VALUES (6, 'NE'), 
(7, 'NW');

--19. Upotrebom insert naredbe iz tabele OrderDetails baze Northwind izvr�iti kreiranje i insertovanje 
--podataka u tabelu StavkeNarudzbe �eme Narudzbe
SELECT OD.OrderID StavkaNarudzbeID, OD.ProductID ProizvodID, OD.UnitPrice CijenaStavke, OD.Quantity Kolicina, OD.Discount PopustINTO Narudzbe.StavkeNarudzbeFROM Northwind.dbo.[Order Details] AS OD;SELECT * FROM Narudzbe.StavkeNarudzbe;--20. U tabeli StavkeNarudzbe dodati standardnu kolonu ukupno tipa decimalni broj (8,2).
ALTER TABLE Narudzbe.StavkeNarudzbe
ADD Ukupno DECIMAL(8,2);

--21. Izvr�iti update kreirane kolone kao umno�ak kolona Quantity i UnitPrice.

UPDATE Narudzbe.StavkeNarudzbe
SET Ukupno = Kolicina * CijenaStavke;

--22. U tabeli StavkeNarduzbe dodati izra�unatu kolonu CijeliDio(broj ispred decimalnog zareza) u kojoj 
--�e biti cijeli dio iz kolone UnitPrice

ALTER TABLE Narudzbe.StavkeNarudzbe
ADD CijeliDio AS CAST(FLOOR(CijenaStavke) AS INT) PERSISTED;

--AS nam govori da je calculated tj. kao derivirani, kao i CAST, tip je COMPUTED
--PERSISTED kaze da kad se izracuna, da zapravo sacuva taj rezultat, tj da ga pohrani

SELECT *
FROM sys.computed_columns
WHERE is_persisted = 1;

--23. U tabeli StavkeNarduzbe kreirati ograni�enje na koloni Discount kojim �e se onemogu�iti unos 
--vrijednosti manjih od 0.

ALTER TABLE Narudzbe.StavkeNarudzbe
ADD CONSTRAINT CHK_StavkeNarudzbe_Discount CHECK (Popust >= 0);

--24. U tabelu StavkeNarudzbe insertovati novi zapis (potrebno je testirati postavljeno ograni�enje)

INSERT INTO Narudzbe.StavkeNarudzbe (StavkaNarudzbeID, ProizvodID, CijenaStavke, Kolicina, Popust)
VALUES (11, 222, 22, 66, 1);

INSERT INTO Narudzbe.StavkeNarudzbe (StavkaNarudzbeID, ProizvodID, CijenaStavke, Kolicina, Popust)
VALUES (11, 222, 22, 66, 0);

INSERT INTO Narudzbe.StavkeNarudzbe (StavkaNarudzbeID, ProizvodID, CijenaStavke, Kolicina, Popust)
VALUES (11, 222, 22, 66, -1);

--25. U �emu Narudzbe dodati tabelu sa sljede�om strukturom:
--Kategorije
--� KategorijaID, cjelobrojna vrijednost, primarni klju� i autoinkrement
--� NazivKategorije, 15 UNICODE znakova (obavezan unos)
--� Opis, tekstualan UNICODE tip podatka

CREATE TABLE Narudzbe.Kategorije
(
	KategorijaID INT CONSTRAINT PK_Kategorije PRIMARY KEY IDENTITY(1,1),
	NazivKategorije NVARCHAR(15) NOT NULL,
	Opis NTEXT
);

--26. U kreiranu tabelu izvr�iti insertovanje podataka iz tabele Categories baze Northwind

SET IDENTITY_INSERT Narudzbe.Kategorije ON 
INSERT INTO Narudzbe.Kategorije(KategorijaID, NazivKategorije, Opis)
SELECT C.CategoryID, C.CategoryName, C.Description
FROM Northwind.dbo.Categories AS C
SET IDENTITY_INSERT Narudzbe.Kategorije OFF;

SELECT * FROM Narudzbe.Kategorije;

--Prva linija nam dopusta insert

--27. U tabelu Kategorije insertovati novu kategoriju pod nazivom �Ncategory�

INSERT INTO Narudzbe.Kategorije(NazivKategorije)
VALUES('Ncategory');

--28. Kreirati upit kojim �e se prikazati sve kategorije

SELECT * FROM Narudzbe.Kategorije;

--29. Izvr�iti update zapisa u tabeli Kategorije na mjestima gdje Opis kategorije nije dodan pohraniti 
--vrijednost �bez opisa�

UPDATE Narudzbe.Kategorije
SET Opis = 'bez opisa'
WHERE Opis IS NULL;

--30. Izvr�iti brisanje svih kategorija

DELETE FROM Narudzbe.Kategorije;