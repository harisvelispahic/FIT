--1. Kroz SQL kod kreirati bazu podataka Vjezba2
CREATE DATABASE Vjezba2;
GO;
USE Vjezba2;

--2. U pomenutoj bazi kreirati šemu Prodaja
GO;
CREATE SCHEMA Prodaja;
GO;
--Šema je u biti kao namespace, npr sales, management...


--3. U šemi Prodaja kreirati tabele sa sljedeæom strukturom:
--Autori
--• AutorID, 11 karaktera i primarni kljuè
--• Prezime, 40 karaktera (obavezan unos)
--• Ime, 20 karaktera (obavezan unos)
--• Telefon, 12 karaktera fiksne dužine, zadana vrijednost „nepoznato“
--• Adresa, 40 karaktera
--• SaveznaDrzava, 2 karaktera fiksne dužine
--• PostanskiBroj, 5 karaktera fiksne dužine
--• Ugovor, bit polje (obavezan unos)
--Knjige
--• KnjigaID, 6 karaktera i primarni kljuè
--• Naziv, 80 karaktera (obavezan unos)
--• Vrsta, 12 karaktera fiksne dužine (obavezan unos)
--• IzdavacID, 4 karaktera fiksne duzine
--• Cijena, novèani tip podatka
--• Biljeska, 200 karaktera
--• Datum, datumsko-vremenski tip

CREATE TABLE Prodaja.Autori
(
	AutorID VARCHAR(11),
	Ime VARCHAR(20) NOT NULL,
	Prezime VARCHAR(40) NOT NULL,
	Telefon CHAR(12) DEFAULT 'nepoznato',
	Adresa VARCHAR(40),
	SaveznaDrzava CHAR(2),
	PostanskiBroj CHAR(5),
	Ugovor BIT NOT NULL,

	CONSTRAINT PK_Autori PRIMARY KEY(AutorID)
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

--4. Upotrebom insert naredbe iz tabele Publishers baze Pubs izvršiti kreiranje i insertovanje podataka u 
--tabelu Izdavaci šeme Prodaja (Nazivi kolona trebaju biti na bosanskom jeziku)

SELECT P.pub_id IzdavacID, P.pub_name NazivIzdavaca, P.city Grad, P.state SaveznaDrzava, P.country Drzava
INTO Prodaja.Izdavaci
FROM pubs.dbo.publishers AS P;

--5. U kreiranoj tabeli Izdavaci provjeriti koje polje je primarni kljuè, ukoliko ga nema, prikladno polje 
--proglasiti primarnim kljuèem

ALTER TABLE Prodaja.Izdavaci
ADD CONSTRAINT PK_Izdavaci PRIMARY KEY (IzdavacID);

--6. Povezati tabelu Izdavaci sa tabelom Knjige, po uzoru na istoimene tabele baze Pubs
ALTER TABLE Prodaja.Knjige
ADD CONSTRAINT FK_Knjige_Izdavaci FOREIGN KEY (IzdavacID) REFERENCES Prodaja.Izdavaci(IzdavacID);


--7. U šemu Prodaja dodati tabelu sa sljedeæom strukturom
--AutoriKnjige
--• AutorID 11 karaktera, spoljni kljuè
--• KnjigaID 6 karaktera, spoljni kljuè
--• AuOrd kratki cjelobrojni tip podatka
--• **Definisati primarni kljuè po uzoru na tabelu TitleAuthor baze Pubs

CREATE TABLE Prodaja.AutoriKnjige
(
	AutorID VARCHAR(11) CONSTRAINT FK_AutoriKnjige_Autori FOREIGN KEY REFERENCES Prodaja.Autori(AutorID),
	KnjigaID VARCHAR(6) CONSTRAINT FK_AutoriKnjige_Knjige FOREIGN KEY REFERENCES Prodaja.Knjige(KnjigaID),
	AuOrd TINYINT,
	CONSTRAINT PK_AutoriKnjige PRIMARY KEY (AutorID, KnjigaID)
);

--8. U kreirane tabele izvršiti insert podataka iz baze Pubs (Za polje biljeska tabele Knjige na mjestima 
--gdje je vrijednost NULL pohraniti „nepoznata vrijednost“)

INSERT INTO Prodaja.Autori
SELECT A.au_id, A.au_fname, A.au_lname, A.phone, A.address, A.state, A.zip, A.contract
FROM pubs.dbo.authors as A;

SELECT * FROM Prodaja.Autori;


INSERT INTO Prodaja.Knjige
SELECT T.title_id, T.title, T.type, T.pub_id, T.price, ISNULL(T.notes,'nepoznata vrijednost'), T.pubdate
FROM pubs.dbo.titles AS T;


SELECT * FROM Prodaja.Knjige;


INSERT INTO Prodaja.AutoriKnjige
SELECT TA.au_id, TA.title_id, TA.au_ord
FROM pubs.dbo.titleauthor AS TA;

SELECT * FROM Prodaja.AutoriKnjige;

--9. U tabeli Autori nad kolonom Adresa promijeniti tip podatka na nvarchar (40)

ALTER TABLE Prodaja.Autori
ALTER COLUMN Adresa NVARCHAR(40);

--10. Prikazati sve autore èije ime poèinje sa slovom A ili S

SELECT *
FROM Prodaja.Autori AS A
WHERE A.Ime LIKE '[AS]%';

--11. Prikazati knjige gdje cijena nije unesena

SELECT *
FROM Prodaja.Knjige AS K
WHERE K.Cijena IS NULL;

--12. U tabeli Izdavaci nad poljem NazivIzdavaca postaviti ogranièenje kojim se onemoguæuje unos 
--duplikata

ALTER TABLE Prodaja.Izdavaci
ADD CONSTRAINT UQ_Izdavaci_NazivIzdavaca UNIQUE (NazivIzdavaca);


--13. Prikladnim primjerima testirati postavljeno ogranièenje na polju NazivIzdavaca

SELECT * FROM Prodaja.Izdavaci;

INSERT INTO Prodaja.Izdavaci (IzdavacID, NazivIzdavaca)
VALUES ('1234', 'New Moon Books');

--14. U bazi Vjezba2 kreirati šemu Narudzbe

GO;
CREATE SCHEMA Narudzbe;

--15. Upotrebom insert naredbe iz tabele Region baze Northwind izvršiti kreiranje i insertovanje podataka 
--u tabelu Regije šeme Narudžbe

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

--19. Upotrebom insert naredbe iz tabele OrderDetails baze Northwind izvršiti kreiranje i insertovanje 
--podataka u tabelu StavkeNarudzbe šeme Narudzbe

SELECT OD.OrderID StavkaNarudzbeID, OD.ProductID ProizvodID, OD.UnitPrice CijenaStavke, OD.Quantity Kolicina, OD.Discount Popust
INTO Narudzbe.StavkeNarudzbe
FROM Northwind.dbo.[Order Details] AS OD;

SELECT * FROM Narudzbe.StavkeNarudzbe;

--20. U tabeli StavkeNarudzbe dodati standardnu kolonu ukupno tipa decimalni broj (8,2).

ALTER TABLE Narudzbe.StavkeNarudzbe
ADD Ukupno DECIMAL(8,2);

--21. Izvršiti update kreirane kolone kao umnožak kolona Quantity i UnitPrice.

UPDATE Narudzbe.StavkeNarudzbe
SET Ukupno = Kolicina * CijenaStavke;

--22. U tabeli StavkeNarduzbe dodati izraèunatu kolonu CijeliDio(broj ispred decimalnog zareza) u kojoj 
--æe biti cijeli dio iz kolone UnitPrice

ALTER TABLE Narudzbe.StavkeNarudzbe
ADD CijeliDio AS CAST(FLOOR(CijenaStavke) AS INT) PERSISTED;

--AS nam govori da je calculated tj. kao derivirani, kao i CAST, tip je COMPUTED
--PERSISTED kaze da kad se izracuna, da zapravo sacuva taj rezultat, tj da ga pohrani

SELECT *
FROM sys.computed_columns
WHERE is_persisted = 1;

--23. U tabeli StavkeNarduzbe kreirati ogranièenje na koloni Discount kojim æe se onemoguæiti unos 
--vrijednosti manjih od 0.

ALTER TABLE Narudzbe.StavkeNarudzbe
ADD CONSTRAINT CHK_StavkeNarudzbe_Discount CHECK (Popust >= 0);

--24. U tabelu StavkeNarudzbe insertovati novi zapis (potrebno je testirati postavljeno ogranièenje)

INSERT INTO Narudzbe.StavkeNarudzbe (StavkaNarudzbeID, ProizvodID, CijenaStavke, Kolicina, Popust)
VALUES (11, 222, 22, 66, 1);

INSERT INTO Narudzbe.StavkeNarudzbe (StavkaNarudzbeID, ProizvodID, CijenaStavke, Kolicina, Popust)
VALUES (11, 222, 22, 66, 0);

INSERT INTO Narudzbe.StavkeNarudzbe (StavkaNarudzbeID, ProizvodID, CijenaStavke, Kolicina, Popust)
VALUES (11, 222, 22, 66, -1);

--25. U šemu Narudzbe dodati tabelu sa sljedeæom strukturom:
--Kategorije
--• KategorijaID, cjelobrojna vrijednost, primarni kljuè i autoinkrement
--• NazivKategorije, 15 UNICODE znakova (obavezan unos)
--• Opis, tekstualan UNICODE tip podatka

CREATE TABLE Narudzbe.Kategorije
(
	KategorijaID INT CONSTRAINT PK_Kategorije PRIMARY KEY IDENTITY(1,1),
	NazivKategorije NVARCHAR(15) NOT NULL,
	Opis NTEXT
);

--26. U kreiranu tabelu izvršiti insertovanje podataka iz tabele Categories baze Northwind

SET IDENTITY_INSERT Narudzbe.Kategorije ON 
INSERT INTO Narudzbe.Kategorije(KategorijaID, NazivKategorije, Opis)
SELECT C.CategoryID, C.CategoryName, C.Description
FROM Northwind.dbo.Categories AS C
SET IDENTITY_INSERT Narudzbe.Kategorije OFF;

SELECT * FROM Narudzbe.Kategorije;

--Prva linija nam dopusta insert

--27. U tabelu Kategorije insertovati novu kategoriju pod nazivom „Ncategory“

INSERT INTO Narudzbe.Kategorije(NazivKategorije)
VALUES('Ncategory');

--28. Kreirati upit kojim æe se prikazati sve kategorije

SELECT * FROM Narudzbe.Kategorije;

--29. Izvršiti update zapisa u tabeli Kategorije na mjestima gdje Opis kategorije nije dodan pohraniti 
--vrijednost „bez opisa“

UPDATE Narudzbe.Kategorije
SET Opis = 'bez opisa'
WHERE Opis IS NULL;

--30. Izvršiti brisanje svih kategorija

DELETE FROM Narudzbe.Kategorije;










---------------------

-- ISPITNI ZADATAK --

---------------------

USE Vjezba2;

-- 1.

CREATE TABLE Narudzbe.Proizvodi 
(
	ProizvodID INT IDENTITY(1,1),
	Naziv NVARCHAR(50) NOT NULL,
	SifraProizvoda NVARCHAR(25) NOT NULL,
	Boja NVARCHAR(15),
	NazivKategorije NVARCHAR(50) NOT NULL,
	Tezina DECIMAL(10, 2)

	CONSTRAINT PK_Proizvodi PRIMARY KEY (ProizvodID)
);

-- 2.

SET IDENTITY_INSERT Narudzbe.Proizvodi ON 
INSERT INTO Narudzbe.Proizvodi (ProizvodID, Naziv, SifraProizvoda, Boja, NazivKategorije, Tezina)
SELECT 
Products.ProductID,
Products.Name,
Products.ProductNumber,
Products.Color,
ProductsCategory.Name,
ISNULL(Products.Weight, 0)
FROM AdventureWorks2017.Production.Product AS Products INNER JOIN AdventureWorks2017.Production.ProductCategory AS ProductsCategory ON Products.ProductSubcategoryID = ProductsCategory.ProductCategoryID;
SET IDENTITY_INSERT Narudzbe.Proizvodi OFF


SELECT * FROM Narudzbe.Proizvodi;




------------------------------

-- DODATNI ZADACI ZA VJEZBU --

------------------------------


-- 1. Kroz SQL kod kreirati bazu podataka ZadaciZaVjezbu2 

CREATE DATABASE ZadaciZaVjezbu2;

USE ZadaciZaVjezbu2;

--2. U pomenutoj bazi kreirati šemu Prodaja

CREATE SCHEMA Prodaja;

--3. U kreiranoj bazi podataka kreirati tabele sa sljedećom strukturom: 
--a) Proizvodi 
--• ProizvodID, cjelobrojna vrijednost, autoinkrement i primarni ključ 
--• Naziv, 40 UNICODE karaktera (obavezan unos) 
--• Cijena, novčani tip 
--• KolicinaNaSkladistu, skraćeni cjelobrojni tip 
--• Raspolozivost, bit polje (obavezan unos) 

CREATE TABLE Prodaja.Proizvodi
(
	ProizvodID INT IDENTITY(1,1),
	Naziv NVARCHAR(40) NOT NULL,
	Cijena MONEY,
	KolicinaNaSkladistu SMALLINT,
	Raspolozivost BIT NOT NULL,

	CONSTRAINT PK_Proizvodi PRIMARY KEY (ProizvodID)
);

--b) Kupci 
--• KupacID, 5 UNICODE fiksna karaktera i primarni ključ 
--• NazivKompanije, 40 UNICODE karaktera (obavezan unos) 
--• Ime, 30 UNICODE karaktera 
--• Telefon, 24 UNICODE karaktera 
--• Faks, 24 UNICODE karaktera 

CREATE TABLE Prodaja.Kupci
(
	KupacID NCHAR(5),
	NazivKompanije NVARCHAR(40) NOT NULL,
	Ime NVARCHAR(30),
	Telefon NVARCHAR(24),
	Faks NVARCHAR(24),

	CONSTRAINT PK_Kupci PRIMARY KEY (KupacID)
);

--c) Narudzbe 
--• NarudzbaID, cjelobrojna vrijednost, autoinkrement i primarni ključ, 
--• DatumNarudzbe, polje za unos datuma 
--• DatumPrijema, polje za unos datuma 
--• DatumIsporuke, polje za unos datuma 
--• Drzava, 15 UNICODE karaktera 
--• Regija, 15 UNICODE karaktera 
--• Grad, 15 UNICODE karaktera 
--• Adresa, 60 UNICODE karaktera 

CREATE TABLE Prodaja.Narudzbe
(
	NarudzbaID INT IDENTITY(1,1), 
    DatumNarudzbe DATE,
    DatumPrijema DATE,
    DatumIsporuke DATE,
    Drzava NVARCHAR(15),
    Regija NVARCHAR(15),
    Grad NVARCHAR(15),
    Adresa NVARCHAR(60),

	CONSTRAINT PK_Narudzbe PRIMARY KEY (NarudzbaID)
);

--d) StavkeNarudzbe 
--• NarudzbaID, cjelobrojna vrijednost, strani ključ 
--• ProizvodID, cjelobrojna vrijednost, strani ključ 
--• Cijena, novčani tip (obavezan unos), 
--marko.dogan@edu.fit.ba 
--esmir.hero@edu.fit.ba 
--Dodatni zadaci za vježbu 
--• Kolicina, skraćeni cjelobrojni tip (obavezan unos) i defaultna vrijednost (1), 
--• Popust, realna vrijednost (obavezan unos) 
--• VrijednostStavki narudžbe (uzeti u obzir i popust)- calculated polje 
--**Definisati primarni ključ tabele 

CREATE TABLE Prodaja.StavkeNarudzbe
(
	NarudzbaID INT CONSTRAINT FK_StavkeNarudzbe_Narudzbe FOREIGN KEY REFERENCES Prodaja.Narudzbe(NarudzbaID),
	ProizvodID INT CONSTRAINT FK_StavkeNarudzbe_Proizvodi FOREIGN KEY REFERENCES Prodaja.Proizvodi(ProizvodID),
	Cijena MONEY NOT NULL,
	Kolicina SMALLINT NOT NULL DEFAULT 1, 
	Popust FLOAT NOT NULL, 
	VrijednostStavkiNarudzbe AS (Cijena * Kolicina * (1 - Popust)) PERSISTED,

	CONSTRAINT PK_StavkeNarudzbe PRIMARY KEY (NarudzbaID, ProizvodID)
);

SELECT * FROM Prodaja.StavkeNarudzbe;

--4. Iz baze podataka Northwind u svoju bazu podataka prebaciti sljedeće podatke: 
--a) U tabelu Proizvodi dodati sve proizvode 
--• ProductID -> ProizvodID 
--• ProductName -> Naziv 
--• UnitPrice -> Cijena 
--• UnitsInStock -> KolicinaNaSkladistu 
--• Discontinued -> Raspolozivost 

--RAZLICITA VERZIJA NORTHWINDA

SET IDENTITY_INSERT Prodaja.Proizvodi ON 
INSERT INTO Prodaja.Proizvodi (ProizvodID, Naziv, Cijena)
SELECT
P.ProductID,
P.Name,
P.ListPrice
FROM Northwind.Production.Product AS P;
SET IDENTITY_INSERT Prodaja.Proizvodi OFF

SELECT * FROM Prodaja.Proizvodi;

--b) U tabelu Kupci dodati sve kupce 
--• CustomerID -> KupciID 
--• CompanyName -> NazivKompanije 
--• ContactName -> Ime 
--• Phone -> Telefon 
--• Fax -> Faks 

INSERT INTO Prodaja.Kupci (KupacID)
SELECT
C.CustomerID
FROM Northwind.Sales.Customer AS C;

--c) U tabelu Narudzbe dodati sve narudžbe, na mjestima gdje nema pohranjenih podataka o regiji 
--zamijeniti vrijednost sa nije naznaceno 
--• OrderID -> NarudzbaID 
--• OrderDate -> DatumNarudzbe 
--• RequiredDate -> DatumPrijema 
--• ShippedDate -> DatumIsporuke 
--• ShipCountry -> Drzava 
--• ShipRegion -> Regija 
--• ShipCity -> Grad 
--• ShipAddress -> Adresa 
--d) U tabelu StavkeNarudzbe dodati sve stavke narudžbe gdje je količina veća od 4 
--• OrderID -> NarudzbaID 
--• ProductID -> ProizvodID 
--• UnitPrice -> Cijena 
--• Quantity -> Kolicina 
--• Discount -> Popust 
--5. Kreirati upit kojim će se prikazati svi proizvodi čija je cijena veća od 100 
--6. Insert komandom dodati novi proizvod 
--7. Dodati novu stavku narudžbe 
--8. Izbrisati sve stavke narudžbe gdje je id narudžbe 10248 
--9. U tabeli Proizvodi kreirati ograničenje na koloni Cijena kojim će se onemogućiti unos vrijednosti 
--manjih od 0,1 
--10. U tabeli proizvodi dodati izračunatu kolonu pod nazivom potrebnoNaruciti za količinu proizvoda 
--na skladištu ispod 10 potrebno je pohraniti vrijednost „DA“ a u suptornom „NE“.


-- to be continued ...