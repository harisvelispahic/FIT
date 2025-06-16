--1. Kroz SQL kod kreirati bazu podataka sa imenom vašeg broja indeksa.

GO
CREATE DATABASE [2022-06-29]
GO
USE [2022-06-29]

--2. U kreiranoj bazi podataka kreirati tabele sa sljedećom strukturom:
--a) Proizvodi
--• ProizvodID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• Naziv, 50 UNICODE karaktera (obavezan unos)
--• SifraProizvoda, 25 UNICODE karaktera (obavezan unos)
--• Boja, 15 UNICODE karaktera
--• NazivKategorije, 50 UNICODE (obavezan unos)
--• Tezina, decimalna vrijednost sa 2 znaka iza zareza

CREATE TABLE Proizvodi
(
	ProizvodID INT CONSTRAINT PK_Proizvodi PRIMARY KEY IDENTITY(1, 1),
	Naziv NVARCHAR(50) NOT NULL,
	SifraProizvoda NVARCHAR(25) NOT NULL,
	Boja NVARCHAR(15),
	NazivKategorije NVARCHAR(50) NOT NULL,
	Tezina DECIMAL(18, 2)
)

--b) ZaglavljeNarudzbe
--• NarudzbaID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• DatumNarudzbe, polje za unos datuma i vremena (obavezan unos)
--• DatumIsporuke, polje za unos datuma i vremena
--• ImeKupca, 50 UNICODE (obavezan unos)
--• PrezimeKupca, 50 UNICODE (obavezan unos)
--• NazivTeritorije, 50 UNICODE (obavezan unos)
--• NazivRegije, 50 UNICODE (obavezan unos)
--• NacinIsporuke, 50 UNICODE (obavezan unos)

CREATE TABLE ZaglavljeNarudzbe
(
	NarudzbaID INT CONSTRAINT PK_ZaglavljeNarudzbe PRIMARY KEY IDENTITY(1, 1),
	DatumNarudzbe DATETIME NOT NULL,
	DatumIsporuke DATETIME,
	ImeKupca NVARCHAR(50) NOT NULL,
	PrezimeKupca NVARCHAR(50) NOT NULL,
	NazivTeritorije NVARCHAR(50) NOT NULL,
	NazivRegije NVARCHAR(50) NOT NULL,
	NacinIsporuke NVARCHAR(50) NOT NULL,
)

--c) DetaljiNarudzbe
--• NarudzbaID, cjelobrojna vrijednost, obavezan unos i strani ključ
--• ProizvodID, cjelobrojna vrijednost, obavezan unos i strani ključ
--• Cijena, novčani tip (obavezan unos),
--• Kolicina, skraćeni cjelobrojni tip (obavezan unos),
--• Popust, novčani tip (obavezan unos)

CREATE TABLE DetaljiNarudzbe
(
	NarudzbaID INT CONSTRAINT FK_DetaljiNarudzbe_ZaglavljeNarudzbe FOREIGN KEY REFERENCES ZaglavljeNarudzbe(NarudzbaID) NOT NULL,
	ProizvodID INT CONSTRAINT FK_DetaljiNarudzbe_Proizvodi FOREIGN KEY REFERENCES Proizvodi(ProizvodID) NOT NULL,
	Cijena MONEY NOT NULL,
	Kolicina SMALLINT NOT NULL,
	Popust MONEY NOT NULL,

	StavkaNarudzbeID INT IDENTITY(1, 1),

	CONSTRAINT PK_DetaljiNarudzbe PRIMARY KEY (NarudzbaID, ProizvodID, StavkaNarudzbeID)
)

--**Jedan proizvod se može više puta naručiti, dok jedna narudžba može sadržavati više proizvoda. U okviru jedne narudžbe jedan proizvod se može naručiti više puta.
--7 bodova


--3. Iz baze podataka AdventureWorks u svoju bazu podataka prebaciti sljedeće podatke:
--a) U tabelu Proizvodi dodati sve proizvode, na mjestima gdje nema pohranjenih podataka o- -težini
--zamijeniti vrijednost sa 0
--• ProductID -> ProizvodID
--• Name -> Naziv
--• ProductNumber -> SifraProizvoda
--• Color -> Boja
--• Name (ProductCategory) -> NazivKategorije
--• Weight -> Tezina

SET IDENTITY_INSERT Proizvodi ON
INSERT INTO Proizvodi
(
	ProizvodID,
	Naziv,
	SifraProizvoda,
	Boja,
	NazivKategorije,
	Tezina
)
SELECT
	P.ProductID,
	P.Name,
	P.ProductNumber,
	Color,
	PC.Name,
	ISNULL(P.Weight, 0)
FROM AdventureWorks2017.Production.Product AS P
	INNER JOIN AdventureWorks2017.Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN AdventureWorks2017.Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
SET IDENTITY_INSERT Proizvodi OFF

--b) U tabelu ZaglavljeNarudzbe dodati sve narudžbe
--• SalesOrderID -> NarudzbaID
--• OrderDate -> DatumNarudzbe
--• ShipDate -> DatumIsporuke
--• FirstName (Person) -> ImeKupca
--• LastName (Person) -> PrezimeKupca
--• Name (SalesTerritory) -> NazivTeritorije
--• Group (SalesTerritory) -> NazivRegije
--• Name (ShipMethod) -> NacinIsporuke

SET IDENTITY_INSERT ZaglavljeNarudzbe ON
INSERT INTO ZaglavljeNarudzbe
(
	NarudzbaID,
	DatumNarudzbe,
	DatumIsporuke,
	ImeKupca,
	PrezimeKupca,
	NazivTeritorije,
	NazivRegije,
	NacinIsporuke
)
SELECT
	SOH.SalesOrderID,
	SOH.OrderDate,
	SOH.ShipDate,
	P.FirstName,
	P.LastName,
	ST.Name,
	ST.[Group],
	SM.Name
FROM AdventureWorks2017.Sales.SalesOrderHeader AS SOH
	INNER JOIN AdventureWorks2017.Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
	INNER JOIN AdventureWorks2017.Person.Person AS P ON C.PersonID = P.BusinessEntityID
	INNER JOIN AdventureWorks2017.Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
	INNER JOIN AdventureWorks2017.Purchasing.ShipMethod AS SM ON SOH.ShipMethodID = SM.ShipMethodID
SET IDENTITY_INSERT ZaglavljeNarudzbe OFF

--c) U tabelu DetaljiNarudzbe dodati sve stavke narudžbe
--• SalesOrderID -> NarudzbaID
--• ProductID -> ProizvodID
--• UnitPrice -> Cijena
--• OrderQty -> Kolicina
--• UnitPriceDiscount -> Popust
--8 bodova

SET IDENTITY_INSERT DetaljiNarudzbe ON
INSERT INTO DetaljiNarudzbe
(
	NarudzbaID,
	ProizvodID,
	Cijena,
	Kolicina,
	Popust,
	StavkaNarudzbeID
)
SELECT
	SOD.SalesOrderID,
	SOD.ProductID,
	SOD.UnitPrice,
	SOD.OrderQty,
	SOD.UnitPriceDiscount,
	SOD.SalesOrderDetailID
FROM AdventureWorks2017.Sales.SalesOrderDetail AS SOD
SET IDENTITY_INSERT DetaljiNarudzbe OFF

--4.
--a) (6 bodova) Kreirati upit koji će prikazati ukupan broj uposlenika po odjelima. Potrebno je prebrojati
--samo one uposlenike koji su trenutno aktivni, odnosno rade na datom odjelu. Također, -samo- uzeti u obzir
--one uposlenike koji imaju više od 10 godina radnog staža (ne uključujući graničnu vrijednost). Rezultate
--sortirati preba broju uposlenika u opadajućem redoslijedu. (AdventureWorks2017)

GO
USE AdventureWorks2017


SELECT
	D.Name,
	COUNT(*) AS [Broj zaposlenika]
FROM HumanResources.EmployeeDepartmentHistory AS EDH
	INNER JOIN HumanResources.Department AS D ON EDH.DepartmentID = D.DepartmentID
WHERE
	EDH.EndDate IS NULL AND
	DATEDIFF(YEAR, EDH.StartDate, GETDATE()) > 10
GROUP BY D.Name
ORDER BY 2 DESC

--b) (10 bodova) Kreirati upit koji prikazuje po mjesecima ukupnu vrijednost poručene robe- -za skladište, te
--ukupnu količinu primljene robe, isključivo u 2012 godini. Uslov je da su troškovi -prevoza- bili između
--500 i 2500, a da je dostava izvršena CARGO transportom. Također u rezultatima upita je --potrebno
--prebrojati stavke narudžbe na kojima je odbijena količina veća od 100. --(AdventureWorks2017)

SELECT
	MONTH(POH.OrderDate) AS [Mjesec],
	SUM(POD.OrderQty * POD.UnitPrice) AS [Ukupna vrijednost porucene robe],
	SUM(POD.ReceivedQty * POD.UnitPrice) AS [Ukupna vrijednost primljene robe],
	Odbijeni.[Broj odbijenih]
FROM Purchasing.PurchaseOrderHeader AS POH
	INNER JOIN Purchasing.ShipMethod AS SM ON POH.ShipMethodID = SM.ShipMethodID
	INNER JOIN Purchasing.PurchaseOrderDetail AS POD ON POH.PurchaseOrderID = POD.PurchaseOrderID
	INNER JOIN
	(
	SELECT
		SQ1.Mjesec,
		COUNT(*) [Broj odbijenih]
	FROM
		(
		SELECT
			MONTH(POH.OrderDate) [Mjesec],
			POH.PurchaseOrderID
		FROM Purchasing.PurchaseOrderHeader AS POH
			INNER JOIN Purchasing.PurchaseOrderDetail AS POD ON POH.PurchaseOrderID = POD.PurchaseOrderID
		GROUP BY MONTH(POH.OrderDate), POH.PurchaseOrderID
		HAVING SUM(POD.ReceivedQty) > 100
		) AS SQ1
	GROUP BY SQ1.Mjesec
	) AS Odbijeni ON MONTH(POH.OrderDate) = Odbijeni.Mjesec
WHERE 
	YEAR(POH.OrderDate) = 2012 AND
	POH.Freight BETWEEN 500 AND 2500 AND
	LOWER(SM.Name) LIKE '%cargo transport%'
GROUP BY MONTH(POH.OrderDate), Odbijeni.[Broj odbijenih]
ORDER BY 1 ASC

--c) (10 bodova) Prikazati ukupan broj narudžbi koje su obradili uposlenici, za svakog --uposlenika
--pojedinačno. Uslov je da su narudžbe kreirane u 2011 ili 2012 godini, te da je u okviru --jedne narudžbe
--odobren popust na dvije ili više stavki. Također uzeti u obzir samo one narudžbe koje su- -isporučene u
--Veliku Britaniju, Kanadu ili Francusku. (AdventureWorks2017)

SELECT
	SOH.SalesPersonID,
	COUNT(*) AS [Broj narudzbi]
FROM Sales.SalesOrderHeader AS SOH
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
	INNER JOIN
	(
	SELECT
		SOH.SalesOrderID
	FROM Sales.SalesOrderHeader AS SOH
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
	WHERE SOD.UnitPriceDiscount > 0
	GROUP BY SOH.SalesOrderID
	HAVING COUNT(*) >= 2
	) AS Popust ON SOH.SalesOrderID = Popust.SalesOrderID
WHERE
	YEAR(SOH.OrderDate) IN (2011, 2012) AND
	ST.Name IN ('United Kingdom', 'Canada', 'France')
GROUP BY SOH.SalesPersonID

--d) (11 bodova) Napisati upit koji će prikazati sljedeće podatke o proizvodima: naziv proizvoda, naziv
--kompanije dobavljača, količinu na skladištu, te kreiranu šifru proizvoda. Šifra se sastoji od sljedećih
--vrijednosti: (Northwind)
--1) Prva dva slova naziva proizvoda
--2) Karakter /
--3) Prva dva slova druge riječi naziva kompanije dobavljača, uzeti u obzir one kompanije koje u
--nazivu imaju 2 ili 3 riječi
--4) ID proizvoda, po pravilu ukoliko se radi o jednocifrenom broju na njega dodati slovo 'a', u
--suprotnom uzeti obrnutu vrijednost broja
--Npr. Za proizvod sa nazivom Chai i sa dobavljačem naziva Exotic Liquids, šifra će btiti Ch/Li1a.
--37 bodova

GO
USE Northwind


SELECT
	P.ProductName,
	S.CompanyName,
	P.UnitsInStock,
	CONCAT
	(
		LEFT(P.ProductName, 2),
		'/',
		IIF((LEN(S.CompanyName) - LEN(REPLACE(S.CompanyName, ' ', '')) + 1) IN (2, 3),
		LEFT(SUBSTRING(S.CompanyName, CHARINDEX(' ', S.CompanyName) + 1, LEN(S.CompanyName) - CHARINDEX(' ', S.CompanyName)), 2),
		''),
		IIF(P.ProductID < 10, CONCAT(CAST(P.ProductID AS CHAR(1)), 'a'), REVERSE(CAST(P.ProductID AS VARCHAR(10))))
	) AS Sifra
FROM Products AS P
	 INNER JOIN Suppliers AS S ON P.SupplierID = S.SupplierID

--5.
--a) (3 boda) U kreiranoj bazi kreirati index kojim će se ubrzati pretraga prema šifri i --nazivu proizvoda.
--Napisati upit za potpuno iskorištenje indexa.

GO
USE [2022-06-29]


CREATE INDEX ix_Proizvodi_SifraProizvoda_Naziv
ON Proizvodi(SifraProizvoda, Naziv)

SELECT
	*
FROM Proizvodi AS P
WHERE P.SifraProizvoda LIKE 'LJ%' AND P.Naziv LIKE '%e%'

DROP INDEX ix_Proizvodi_SifraProizvoda_Naziv ON Proizvodi

--b) (7 bodova) U kreiranoj bazi kreirati proceduru sp_search_products kojom će se vratiti- -podaci o
--proizvodima na osnovu kategorije kojoj pripadaju ili težini. Korisnici ne moraju unijeti- -niti jedan od
--parametara ali u tom slučaju procedura ne vraća niti jedan od zapisa. Korisnicima unosom- -već prvog
--slova kategorije se trebaju osvježiti zapisi, a vrijednost unesenog parametra težina će --vratiti one
--proizvode čija težina je veća od unesene vrijednosti.

GO
CREATE OR ALTER PROCEDURE sp_search_products
(
	@NazivKategorije NVARCHAR(50) = NULL,
	@Tezina DECIMAL(18, 2) = NULL
)
AS
BEGIN
	SELECT
		*
	FROM Proizvodi AS P
	WHERE
		(P.NazivKategorije LIKE CONCAT(@NazivKategorije, '%') AND @NazivKategorije IS NOT NULL) OR
		(P.Tezina > @Tezina AND @Tezina IS NOT NULL)
END
GO

exec sp_search_products @NazivKategorije = 'Comp', @Tezina = 1
exec sp_search_products @NazivKategorije = 'Comp'
exec sp_search_products @Tezina = 1
exec sp_search_products

--c) (18 bodova) Zbog proglašenja dobitnika nagradne igre održane u prva dva mjeseca drugog kvartala 2013
--godine potrebno je kreirati upit. Upitom će se prikazati treća najveća narudžba (vrijednost bez popusta)
--za svaki mjesec pojedinačno. Obzirom da je u pravilima nagradne igre potrebno nagraditi 2 osobe
--(muškarca i ženu) za svaki mjesec, potrebno je u rezultatima upita prikazati pored navedenih stavki i o
--kojem se kupcu radi odnosno ime i prezime, te koju je nagradu osvojio. Nagrade se dodjeljuju po
--sljedećem pravilu:
--• za žene u prvom mjesecu drugog kvartala je stoni mikser, dok je za muškarce usisivač
--• za žene u drugom mjesecu drugog kvartala je pegla, dok je za muškarc multicooker
--Obzirom da za kupce nije eksplicitno naveden spol, određivat će se po pravilu: Ako je zadnje slovo imena
--a, smatra se da je osoba ženskog spola u suprotnom radi se o osobi muškog spola. Rezultate u formiranoj
--tabeli dobitnika sortirati prema vrijednosti narudžbe u opadajućem redoslijedu. (AdventureWorks2017)
--28 bodova

GO
USE AdventureWorks2017


SELECT
	SQ.FirstName,
	SQ.LastName,
	SQ.Spol,
	SQ.Mjesec,
	SQ.[Vrijednost narudzbe],
	CASE
		WHEN SQ.Spol = 'F' AND SQ.Mjesec = 4 THEN 'Stoni mikser'
		WHEN SQ.Spol = 'M' AND SQ.Mjesec = 4 THEN 'Usisivac'
		WHEN SQ.Spol = 'F' AND SQ.Mjesec = 5 THEN 'Pegla'
		WHEN SQ.Spol = 'M' AND SQ.Mjesec = 5 THEN 'Multicooker'
	END AS [Nagrada]
FROM
	(
	SELECT
		*
	FROM
		(
		SELECT
			MONTH(SOH.OrderDate) AS [Mjesec],
			SUM(SOD.UnitPrice * SOD.OrderQty) AS [Vrijednost narudzbe],
			IIF(LOWER(RIGHT(P.FirstName, 1)) = 'a', 'F', 'M') AS Spol,
			P.FirstName,
			P.LastName,
			ROW_NUMBER() OVER (PARTITION BY MONTH(SOH.OrderDate), IIF(LOWER(RIGHT(P.FirstName, 1)) = 'a', 'F', 'M') ORDER BY SUM(SOD.UnitPrice * SOD.OrderQty) DESC) AS rn
		FROM Sales.SalesOrderHeader AS SOH
			INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
			INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
			INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
		WHERE YEAR(SOH.OrderDate) = 2013
		GROUP BY MONTH(SOH.OrderDate), SOH.SalesOrderID, IIF(LOWER(RIGHT(P.FirstName, 1)) = 'a', 'F', 'M'), P.FirstName, P.LastName
		) AS SQ1
	WHERE SQ1.Mjesec IN (4, 5) AND SQ1.rn = 3
	) AS SQ
ORDER BY 5 DESC


--6. Dokument teorijski_ispit 29JUN22, preimenovati vašim brojem indeksa, te u tom --dokumentu izraditi
--pitanja.
--20 bodova
--SQL skriptu (bila prazna ili ne) imenovati Vašim brojem indeksa npr IB200001.sql, --teorijski dokument imenovan
--Vašim brojem indexa npr IB200001.docx upload-ovati ODVOJEDNO na ftp u folder Upload.
--Maksimalan broj bodova:100
--Prag prolaznosti: 55
