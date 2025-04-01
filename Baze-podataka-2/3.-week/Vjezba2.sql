--1.	Kroz SQL kod kreirati bazu podataka Vjezba2
CREATE DATABASE Vjezba2
GO
USE Vjezba2

--2.    U pomenutoj bazi kreirati šemu Prodaja
GO
CREATE SCHEMA Prodaja
GO

--3.	U šemi prodaja kreirati tabele sa sljedeæom strukturom:
CREATE TABLE Prodaja.Autori
(
	AutorID VARCHAR(11) CONSTRAINT PK_Autori PRIMARY KEY,
	Prezime VARCHAR(40) NOT NULL,
	Ime VARCHAR(20) NOT NULL,
	Telefon CHAR(12) DEFAULT 'nepoznato',
	Adresa VARCHAR(40),
	SaveznaDrzava CHAR(2),
	PostanskiBroj CHAR(5),
	Ugovor BIT NOT NULL
)

CREATE TABLE Prodaja.Knjige
(
	KnjigaID VARCHAR(6) CONSTRAINT PK_Knjige PRIMARY KEY,
	Naziv VARCHAR(80) NOT NULL,
	Vrsta CHAR(12) NOT NULL,
	IzdavacID CHAR(4), 
	Cijena MONEY,
	Biljeska VARCHAR(200),
	Datum DATETIME
)

--4. Upotrebom insert naredbe iz tabele Publishers baze Pubs izvršiti kreiranje i insertovanje podataka u tabelu Izdavaci šeme Prodaja (Nazivi kolona trebaju biti na bosanskom jeziku)
SELECT 
P.pub_id AS IzdavacID,
P.pub_name AS NazivIzdavaca,
P.city AS Grad,
P.state AS SaveznaDrzava,
P.country AS Drazava
INTO Prodaja.Izdavaci
FROM pubs.dbo.publishers AS P

--5. U kreiranoj tabeli Izdavaci provjeriti koje polje je primarni ključ, ukoliko ga nema, prikladno polje proglasiti primarnim ključem 
ALTER TABLE Prodaja.Izdavaci
ADD CONSTRAINT PK_Izdavaci PRIMARY KEY(IzdavacID)

--6. Povezati tabelu Izdavaci sa tabelom Knjige, po uzoru na istoimene tabele baze Pubs
ALTER TABLE Prodaja.Knjige
ADD CONSTRAINT FK_Knjige_Izdavaci FOREIGN KEY(IzdavacID) REFERENCES Prodaja.Izdavaci(IzdavacID)

--7.	U šemu prodaja dodati tabelu sa sljedeæom strukturom
CREATE TABLE Prodaja.AutoriKnjige
(
	AutorID VARCHAR(11) CONSTRAINT FK_AutoriKnjige_Autori FOREIGN KEY REFERENCES Prodaja.Autori(AutorID),
	KnjigaID VARCHAR(6) CONSTRAINT FK_AutoriKnjige_Kjige FOREIGN KEY REFERENCES Prodaja.Knjige(KnjigaID),
	AuOrd TINYINT,
	CONSTRAINT PK_AutoriKnjige PRIMARY KEY(AutorID, KnjigaID)
)

--8.	U kreirane tabele izvršiti insert podataka iz baze Pubs (Za polje biljeska tabele knjige na mjestima gdje je vrijednost NULL pohraniti „nepoznata vrijednost“)
INSERT INTO Prodaja.Autori
SELECT A.au_id, A.au_lname, A.au_fname, A.phone, A.address, A.state, A.zip, A.contract
FROM pubs.dbo.authors AS A

INSERT INTO Prodaja.Knjige
SELECT T.title_id, T.title, T.type, T.pub_id, T.price, ISNULL(T.notes, 'nepoznata vrijednost'), T.pubdate
FROM pubs.dbo.titles AS T

INSERT INTO Prodaja.AutoriKnjige
SELECT TA.au_id, TA.title_id, TA.au_ord
FROM pubs.dbo.titleauthor as TA

--Ukoliko je potrebno brisanje zbog nepravilnog inserta podataka iz tabele knjige šeme prodaja
DELETE
FROM Prodaja.Knjige

--9.	U tabeli autori nad kolonom Adresa promijeniti tip podatka na nvarchar (40)
ALTER TABLE Prodaja.Autori
ALTER COLUMN Adresa NVARCHAR(40)

--10.	Prikazati sve Autore èije ime poèinje sa slovom A ili S
SELECT *
FROM Prodaja.Autori AS PA
WHERE PA.Ime LIKE 'A%' OR PA.Ime LIKE 'S%'

--11.	Prikazati knjige gdje cijena nije unesena
SELECT*
FROM Prodaja.Knjige AS K
WHERE K.Cijena IS NULL

--12. U tabeli Izdavaci nad poljem NazivIzdavaca postaviti ograničenje kojim se onemogućuje unos duplikata
ALTER TABLE Prodaja.Izdavaci
ADD CONSTRAINT UQ_Izdavaci_NazivIzdavaca UNIQUE (NazivIzdavaca)

--13. Prikladnim primjerima testirati postavljeno ograničenje na polju NazivIzdavaca
SELECT *
FROM Prodaja.Izdavaci

INSERT INTO Prodaja.Izdavaci(IzdavacID, NazivIzdavaca)
VALUES('AAAA', 'GGG&G1')

INSERT INTO Prodaja.Izdavaci(IzdavacID, NazivIzdavaca)
VALUES('AAA2', 'GGG&G1')

--14. U bazi Vjezba2 kreirati šemu Narudzbe
GO
CREATE SCHEMA Narudzbe
GO

--15. Upotrebom insert naredbe iz tabele Region baze Northwind izvršiti kreiranje i insertovanje podataka u tabelu Regije šeme Narudžbe
SELECT *
INTO Narudzbe.Regije
FROM Northwind.dbo.Region

--16.	Prikazati sve podatke koji se nalaze u tabeli Regija
SELECT *
FROM Narudzbe.Regije

--17.	U tabelu Regije insertovati zapis:
--5    SE
INSERT INTO Narudzbe.Regije
VALUES (5, 'SE')

--Sada da prikažemo opet sve Regije
SELECT *
FROM Narudzbe.Regije

--18.	U tabelu Regije insertovati zapise:
-- 6  NE
-- 7  NW
INSERT INTO Narudzbe.Regije
VALUES (6, 'NE'),
		(7, 'NW')

--19. Upotrebom insert naredbe iz tabele OrderDetails baze Northwind izvršiti kreiranje i insertovanje podataka u tabelu StavkeNarudzbe šeme Narudzbe
SELECT *
INTO Narudzbe.StavkeNarudzbe
FROM Northwind.dbo.[Order Details]

--20.	U tabeli StavkeNarudzbe dodati standardnu kolonu ukupno tipa decimalni broj (8,2).
ALTER TABLE Narudzbe.StavkeNarudzbe
ADD Ukupno DECIMAL(8, 2)

--21.	Izvršiti update kreirane kolone kao umnožak kolona Quantity i UnitPrice.
UPDATE Narudzbe.StavkeNarudzbe
SET Ukupno=Quantity*UnitPrice

--Nakon dodavanja novog zapisa vrijednost Ukupno nije ponovno izračunata za novododano polje 
SELECT *
FROM Narudzbe.StavkeNarudzbe

INSERT INTO Narudzbe.StavkeNarudzbe(OrderID, ProductID, UnitPrice, Quantity, Discount)
VALUES (10248, 50, 10, 2, 0)

SELECT *
FROM Narudzbe.StavkeNarudzbe AS SN
WHERE SN.OrderID=10248

--22. U tabeli StavkeNarduzbe dodati izračunatu kolonu CijeliDio(broj ispred decimalnog zareza) u kojoj će biti cijeli dio iz kolone UnitPrice 
ALTER TABLE Narudzbe.StavkeNarudzbe
ADD CijeliDio2 AS FLOOR(UnitPrice) --PERSISTED

SELECT *
FROM Narudzbe.StavkeNarudzbe AS SN

INSERT INTO Narudzbe.StavkeNarudzbe(OrderID, ProductID, UnitPrice, Quantity, Discount)
VALUES (10248, 51, 10.4, 2, 0)

--Ukoliko želimo provjeriti da li je kolona persisted
SELECT * 
FROM sys.computed_columns 
WHERE is_persisted = 1

--23. U tabeli StavkeNarduzbe kreirati ograničenje na koloni Discount kojim će se onemogućiti unos vrijednosti manjih od 0. 
ALTER TABLE Narudzbe.StavkeNarudzbe
ADD CONSTRAINT CK_StavkeNarudzbe_Discount CHECK(Discount>=0)

--24. U tabelu StavkeNarudzbe insertovati novi zapis (potrebno je testirati postavljeno ograničenje) 
INSERT INTO Narudzbe.StavkeNarudzbe(OrderID, ProductID, UnitPrice, Quantity, Discount) 
VALUES(11, 222, 22, 66, -1)

INSERT INTO Narudzbe.StavkeNarudzbe(OrderID, ProductID, UnitPrice, Quantity, Discount) 
VALUES(11, 222, 22, 66, 1)

SELECT *
FROM Narudzbe.StavkeNarudzbe
WHERE OrderID=11

--25.	U šemu narudzbe dodati tabelu sa sljedeæom strukturom:
--Kategorije
--•	KategorijaID ,  cjelobrojna vrijednost, primarni kljuè i autoinkrement
--•	ImeKategorije, 15 UNICODE znakova (obavezan unos)
--•	Opis, tekstualan UNICODE tip podatka 
CREATE TABLE Narudzbe.Kategorije
(
	KategorijaID INT CONSTRAINT PK_Kategorije PRIMARY KEY IDENTITY(1,1),
	NazivKategorije NVARCHAR(15) NOT NULL,
	Opis NTEXT
)

--26. U kreiranu tabelu izvršiti insertovanje podataka iz tabele Categories baze Northwind
SET IDENTITY_INSERT Narudzbe.Kategorije ON
INSERT INTO Narudzbe.Kategorije(KategorijaID, NazivKategorije, Opis)
SELECT C.CategoryID, C.CategoryName, C.Description
FROM Northwind.dbo.Categories AS C
SET IDENTITY_INSERT Narudzbe.Kategorije OFF

--27. U tabelu Kategorije insertovati novu kategoriju pod nazivom „Ncategory“
INSERT INTO Narudzbe.Kategorije(NazivKategorije)
VALUES('Ncategory')

--28. Kreirati upit kojim će se prikazati sve kategorije
SELECT *
FROM Narudzbe.Kategorije

--29. Izvršiti update zapisa u tabeli Kategorije na mjestima gdje Opis kategorije nije dodan pohraniti vrijednost „bez opisa“
UPDATE Narudzbe.Kategorije
SET	Opis ='bez opisa'
WHERE Opis IS NULL

--30.	Izvršiti brisanje svih kategorija
DELETE FROM Narudzbe.Kategorije

--PRIMJER ISPITNOG DDL ZADATKA
--1) Kreirati tabelu Proizvodi šeme Narudzbe, sljedeće strukture:
--• ProizvodID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• Naziv, 50 UNICODE karaktera (obavezan unos)
--• SifraProizvoda, 25 UNICODE karaktera (obavezan unos)
--• Boja, 15 UNICODE karaktera
--• NazivKategorije, 50 UNICODE (obavezan unos)
--• Tezina, decimalna vrijednost sa 2 znaka iza zareza

CREATE TABLE Narudzbe.Proizvodi
(
	ProizvodID INT CONSTRAINT PK_Proizvodi PRIMARY KEY IDENTITY(1,1),
	Naziv NVARCHAR(50) NOT NULL,
	SifraProizvoda NVARCHAR(25) NOT NULL,
	Boja NVARCHAR(15),
	NazivKategorije NVARCHAR(50) NOT NULL,
	Tezina DECIMAL(18,2)
)

--2) Iz baze podataka AdventureWorks2017 u tabelu Proizvodi dodati sve proizvode, na mjestima gdje nema pohranjenih podataka o težini
--zamijeniti vrijednost sa 0
--• ProductID -> ProizvodID
--• Name -> Naziv
--• ProductNumber -> SifraProizvoda
--• Color -> Boja
--• Name (ProductCategory) -> NazivKategorije
--• Weight -> Tezina

SET IDENTITY_INSERT Narudzbe.Proizvodi ON

INSERT INTO Narudzbe.Proizvodi(ProizvodID, Naziv, SifraProizvoda, Boja, NazivKategorije, Tezina)
SELECT P.ProductID, P.Name, P.ProductNumber, P.Color, PC.Name, ISNULL(P.Weight, 0)
FROM AdventureWorks2017.Production.Product AS P
	INNER JOIN AdventureWorks2017.Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN AdventureWorks2017.Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID

SET IDENTITY_INSERT Narudzbe.Proizvodi OFF


SELECT * FROM Narudzbe.Proizvodi --pregled unesenih proizvoda


--DODATNI ZADACI ZA VJEZBU
--1.	Kroz SQL kod kreirati bazu podataka ZadaciZaVjezbu2
CREATE DATABASE ZadaciZaVjezbu2
GO
USE ZadaciZaVjezbu2

--2.	U pomenutoj bazi kreirati šemu Prodaja
GO
CREATE SCHEMA Prodaja
GO

--3.	U kreiranoj bazi podataka kreirati tabele sa sljedeæom strukturom:
CREATE TABLE Prodaja.Proizvodi
(
	ProizvodID INT CONSTRAINT PK_Proizvodi PRIMARY KEY IDENTITY(1,1),
	Naziv  NVARCHAR(40) NOT NULL,
	Cijena MONEY,
	KolicinaNaSkladistu SMALLINT,
	Raspolozivost BIT NOT NULL
)
CREATE TABLE Prodaja.Kupci
(
	KupacID NCHAR(5) CONSTRAINT PK_Kupci PRIMARY KEY,
	NazivKompanije NVARCHAR(40) NOT NULL,
	Ime NVARCHAR(30),
	Telefon NVARCHAR(24),
	Faks NVARCHAR(24)
)
CREATE TABLE Prodaja.Narudzbe
(
	NarudzbaID INT CONSTRAINT PK_Narudzbe PRIMARY KEY IDENTITY(1,1), 
	DatumNarudzbe DATE,
	DatumPrijema DATE,
	DatumIsporuke DATE,
	Drzava NVARCHAR(15),
	Regija NVARCHAR(15),
	Grad NVARCHAR(15),
	Adresa NVARCHAR(60)
)
CREATE TABLE Prodaja.StavkeNarudzbe
(
	NarudzbaID INT CONSTRAINT FK_StavkeNarudzbe_Narudzbe FOREIGN KEY REFERENCES Prodaja.Narudzbe(NarudzbaID),
	ProizvodID INT CONSTRAINT FK_StavkeNarudzbe_Proizvodi FOREIGN KEY REFERENCES Prodaja.Proizvodi(ProizvodID),
	Cijena MONEY NOT NULL,
	Kolicina SMALLINT NOT NULL DEFAULT(1),
	Popust REAL NOT NULL,
	VrijednostStavki AS (Cijena*Kolicina*(1-Popust)),
	CONSTRAINT PK_StavkeNarudzbe PRIMARY KEY(NarudzbaID,ProizvodID)
)
--**Definisati primarni kljuè tabele
--4.	Iz baze podataka Northwind u svoju bazu podataka prebaciti sljedeæe podatke:
--a)	U tabelu Proizvodi dodati sve proizvode 
--•	ProductID -> ProizvodID
--•	ProductName -> Naziv 	
--•	UnitPrice -> Cijena 	
--•	UnitsInStock -> KolicinaNaSkladistu
--•	Discontinued -> Raspolozivost 	

SET IDENTITY_INSERT Prodaja.Proizvodi ON 
INSERT INTO Prodaja.Proizvodi(ProizvodID, Naziv, Cijena, KolicinaNaSkladistu, Raspolozivost)
SELECT P.ProductID, P.ProductName, P.UnitPrice, P.UnitsInStock, P.Discontinued
FROM Northwind.dbo.Products AS P
SET IDENTITY_INSERT Prodaja.Proizvodi OFF

--b)	U tabelu Kupci dodati sve kupce 
--•	CustomerID -> KupciID
--•	CompanyName -> NazivKompanije	
--•	ContactName -> Ime 	
--•	Phone -> Telefon
--•	Fax -> Faks

INSERT INTO Prodaja.Kupci(KupacID, NazivKompanije, Ime, Telefon, Faks)
SELECT C.CustomerID, C.CompanyName, C.ContactName, C.Phone, C.Fax
FROM Northwind.dbo.Customers AS C

--c)	U tabelu Narudzbe dodati sve narudžbe, na mjestima gdje nema pohranjenih podataka o regiji zamijeniti vrijednost sa nije naznaceno
--•	OrderID -> NarudzbaID
--•	OrderDate -> DatumNarudzbe
--•	RequiredDate -> DatumPrijema
--•	ShippedDate -> DatumIsporuke
--•	ShipCountry -> Drzava
--•	ShipRegion -> Regija
--•	ShipCity -> Grad
--•	ShipAddress -> Adresa

SET IDENTITY_INSERT Prodaja.Narudzbe ON 
INSERT INTO Prodaja.Narudzbe(NarudzbaID, DatumNarudzbe, DatumPrijema, DatumIsporuke, Drzava, Regija, Grad, Adresa)
SELECT O.OrderID, O.OrderDate, O.RequiredDate, O.ShippedDate, O.ShipCountry, O.ShipRegion, O.ShipCity, O.ShipAddress
FROM Northwind.dbo.Orders AS O
SET IDENTITY_INSERT Prodaja.Narudzbe OFF

--d)	U tabelu StavkeNarudzbe dodati sve stavke narudžbe gdje je kolièina veæa od 4
--•	OrderID -> NarudzbaID
--•	ProductID -> ProizvodID
--•	UnitPrice -> Cijena
--•	Quantity -> Kolicina
--•	Discount -> Popust


INSERT INTO Prodaja.StavkeNarudzbe(NarudzbaID, ProizvodID, Cijena, Kolicina, Popust)
SELECT OD.OrderID, OD.ProductID, OD.UnitPrice, OD.Quantity, OD.Discount
FROM Northwind.dbo.[Order Details] AS OD

--5.	Kreirati upit kojim æe se prikazati svi proizvodi èija je cijena veæa od 100
SELECT *
FROM Prodaja.Proizvodi AS P
WHERE P.Cijena>100

--6.	Insert komandom dodati novi proizvod 
INSERT INTO Prodaja.Proizvodi(Naziv, Raspolozivost)
VALUES('novi proizvod', 1)

SELECT*
FROM Prodaja.Proizvodi AS PP
WHERE PP.Naziv='novi proizvod'

--7.	Dodati novu stavku narudzbe
INSERT INTO Prodaja.StavkeNarudzbe(NarudzbaID, ProizvodID, Cijena, Popust)
VALUES(10248, 78, 4, 0)

SELECT*
FROM Prodaja.StavkeNarudzbe

--8.	Izbrisati sve stavke narudzbe gdje je narudzbaID 10248
DELETE 
FROM Prodaja.StavkeNarudzbe 
WHERE NarudzbaID=10248

--9.	U tabeli Proizvodi kreirati ogranièenje na koloni Cijena kojim æe se onemoguæiti unos vrijednosti manjih od 0.1
ALTER TABLE Prodaja.Proizvodi
ADD CONSTRAINT CK_Cijena CHECK(Cijena>=0.1)

--10.	U tabeli proizvodi dodati izraèunatu kolonu pod nazivom potrebnoNaruciti za kolièinu proizvoda na skladištu ispod 10 potrebno je pohraniti vrijednost „DA“ a u suptornom „NE“.
ALTER TABLE Prodaja.Proizvodi
ADD potrebnoNaruciti AS CASE WHEN(KolicinaNaSkladistu<10) THEN 'DA' ELSE 'NE' END

SELECT*
FROM Prodaja.Proizvodi


