--1. Kroz SQL kod kreirati bazu podataka sa imenom vašeg broja indeksa. 

GO
CREATE DATABASE [2023-09-08]
GO
USE [2023-09-08]

--2. U kreiranoj bazi podataka kreirati tabele sa sljedećom strukturom: 
--a) Prodavaci
--• ProdavacID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• Ime, 50 UNICODE karaktera (obavezan unos)
--• Prezime, 50 UNICODE karaktera (obavezan unos)
--• OpisPosla, 50 UNICODE karaktera (obavezan unos)
--• EmailAdresa, 50 UNICODE 

CREATE TABLE Prodavaci
(
	ProdavacID		INT				CONSTRAINT PK_Prodavaci PRIMARY KEY		IDENTITY(1, 1),
	Ime				NVARCHAR(50)	NOT NULL,
	Prezime			NVARCHAR(50)	NOT NULL,
	OpisPosla		NVARCHAR(50)	NOT NULL,
	EmailAdresa		NVARCHAR(50)
)

--b) Proizvodi
--• ProizvodID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• Naziv, 50 UNICODE karaktera (obavezan unos)
--• SifraProizvoda, 25 UNICODE karaktera (obavezan unos)
--• Boja, 15 UNICODE karaktera
--• NazivKategorije, 50 UNICODE (obavezan unos)

CREATE TABLE Proizvodi
(
	ProizvodID			INT				CONSTRAINT PK_Proizvodi PRIMARY KEY		IDENTITY(1, 1),
	Naziv				NVARCHAR(50)	NOT NULL,
	SifraProizvoda		NVARCHAR(25)	NOT NULL,
	Boja				NVARCHAR(15),
	NazivKategorije		NVARCHAR(50)	NOT NULL
)

--c) ZaglavljeNarudzbe
--• NarudzbaID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• DatumNarudzbe, polje za unos datuma i vremena (obavezan unos)
--• DatumIsporuke, polje za unos datuma i vremena
--• KreditnaKarticaID, cjelobrojna vrijednost
--• ImeKupca, 50 UNICODE (obavezan unos)
--• PrezimeKupca, 50 UNICODE (obavezan unos)
--• NazivGrada, 30 UNICODE (obavezan unos)
--• ProdavacID, cjelobrojna vrijednost i strani ključ
--• NacinIsporuke, 50 UNICODE (obavezan unos)

CREATE TABLE ZaglavljeNarudzbe
(
	NarudzbaID			INT CONSTRAINT PK_ZaglavljeNarudzbe PRIMARY KEY IDENTITY(1, 1),
	DatumNarudzbe		DATETIME NOT NULL,
	DatumIsporuke		DATETIME,
	KreditnaKarticaID	INT,
	ImeKupca			NVARCHAR(50) NOT NULL,
	PrezimeKupca		NVARCHAR(50) NOT NULL,
	NazivGrada			NVARCHAR(30) NOT NULL,
	ProdavacID			INT CONSTRAINT FK_ZaglavljeNarudzbe_Prodavaci FOREIGN KEY REFERENCES Prodavaci(ProdavacID),
	NacinIsporuke		NVARCHAR(50) NOT NULL
)

--c) DetaljiNarudzbe
--• NarudzbaID, cjelobrojna vrijednost, obavezan unos i strani ključ
--• ProizvodID, cjelobrojna vrijednost, obavezan unos i strani ključ
--• Cijena, novčani tip (obavezan unos),
--• Kolicina, skraćeni cjelobrojni tip (obavezan unos),
--• Popust, novčani tip (obavezan unos)
--• OpisSpecijalnePonude, 255 UNICODE (obavezan unos)

CREATE TABLE DetaljiNarudzbe
(
	NarudzbaID INT CONSTRAINT FK_DetaljiNarudzbe_ZaglavljeNarudzbe FOREIGN KEY REFERENCES ZaglavljeNarudzbe(NarudzbaID) NOT NULL,
	ProizvodID INT CONSTRAINT FK_DetaljiNarudzbe_Proizvodi FOREIGN KEY REFERENCES Proizvodi(ProizvodID) NOT NULL,
	Cijena MONEY NOT NULL,
	Kolicina SMALLINT NOT NULL,
	Popust MONEY NOT NULL,
	OpisSpecijalnePonude NVARCHAR(255) NOT NULL,

	--CONSTRAINT PK_DetaljiNarudzbe PRIMARY KEY(NarudzbaID)
	CONSTRAINT UQ_DetaljiNarudzbe UNIQUE (NarudzbaID, ProizvodID, Cijena, Kolicina, Popust, OpisSpecijalnePonude)
)

--**Jedan proizvod se može više puta naručiti, dok jedna narudžba može sadržavati više proizvoda. 
--U okviru jedne narudžbe jedan proizvod se može naručiti više puta.
--7 bodova

--3a. Iz baze podataka AdventureWorks u svoju bazu podataka prebaciti sljedeće podatke:
--a) U tabelu Prodavaci dodati :
--• BusinessEntityID (SalesPerson) -> ProdavacID
--• FirstName -> Ime
--• LastName -> Prezime
--• JobTitle (Employee) -> OpisPosla
--• EmailAddress (EmailAddress) -> EmailAdresa

SET IDENTITY_INSERT Prodavaci ON
INSERT INTO Prodavaci
(
	ProdavacID,
	Ime,
	Prezime,
	OpisPosla,
	EmailAdresa
)
SELECT
	SP.BusinessEntityID,
	P.FirstName,
	P.LastName,
	E.JobTitle,
	EA.EmailAddress
FROM AdventureWorks2017.Person.Person AS P
	INNER JOIN AdventureWorks2017.HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
	INNER JOIN AdventureWorks2017.Sales.SalesPerson AS SP ON E.BusinessEntityID = SP.BusinessEntityID
	INNER JOIN AdventureWorks2017.Person.EmailAddress AS EA ON P.BusinessEntityID = EA.BusinessEntityID
SET IDENTITY_INSERT Prodavaci OFF

--3. Iz baze podataka AdventureWorks u svoju bazu podataka prebaciti sljedeće podatke:
--3b) U tabelu Proizvodi dodati sve proizvode
--• ProductID -> ProizvodID
--• Name -> Naziv
--• ProductNumber -> SifraProizvoda
--• Color -> Boja
--• Name (ProductCategory) -> NazivKategorije

SET IDENTITY_INSERT Proizvodi ON
INSERT INTO Proizvodi
(
	ProizvodID,
	Naziv,
	SifraProizvoda,
	Boja,
	NazivKategorije
)
SELECT
	P.ProductID,
	P.Name,
	P.ProductNumber,
	P.Color,
	PC.Name
FROM AdventureWorks2017.Production.Product AS P
	INNER JOIN AdventureWorks2017.Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN AdventureWorks2017.Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
SET IDENTITY_INSERT Proizvodi OFF

--3c) U tabelu ZaglavljeNarudzbe dodati sve narudžbe
--• SalesOrderID -> NarudzbaID
--• OrderDate -> DatumNarudzbe
--• ShipDate -> DatumIsporuke
--• CreditCardID -> KreditnaKarticaID
--• FirstName (Person) -> ImeKupca
--• LastName (Person) -> PrezimeKupca
--• City (Address) -> NazivGrada
--• SalesPersonID (SalesOrderHeader) -> ProdavacID
--• Name (ShipMethod) -> NacinIsporuke

SET IDENTITY_INSERT ZaglavljeNarudzbe ON
INSERT INTO ZaglavljeNarudzbe
(
	NarudzbaID,
	DatumNarudzbe,
	DatumIsporuke,
	KreditnaKarticaID,
	ImeKupca,
	PrezimeKupca,
	NazivGrada,
	ProdavacID,
	NacinIsporuke
)
SELECT
	SOH.SalesOrderID,
	SOH.OrderDate,
	SOH.ShipDate,
	SOH.CreditCardID,
	P.FirstName,
	P.LastName,
	A.City,
	SOH.SalesPersonID,
	SM.Name
FROM AdventureWorks2017.Sales.SalesOrderHeader AS SOH
	INNER JOIN AdventureWorks2017.Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
	INNER JOIN AdventureWorks2017.Person.Person AS P ON C.PersonID = P.BusinessEntityID
	INNER JOIN AdventureWorks2017.Person.Address AS A ON SOH.ShipToAddressID = A.AddressID
	INNER JOIN AdventureWorks2017.Purchasing.ShipMethod AS SM ON SOH.ShipMethodID = SM.ShipMethodID
SET IDENTITY_INSERT ZaglavljeNarudzbe OFF

--3d) U tabelu DetaljiNarudzbe dodati sve stavke narudžbe
--• SalesOrderID -> NarudzbaID
--• ProductID -> ProizvodID
--• UnitPrice -> Cijena
--• OrderQty -> Kolicina
--• UnitPriceDiscount -> Popust
--• Description (SpecialOffer) -> OpisSpecijalnePonude

INSERT INTO DetaljiNarudzbe
(
	NarudzbaID,
	ProizvodID,
	Cijena,
	Kolicina,
	Popust,
	OpisSpecijalnePonude
)
SELECT
	SOD.SalesOrderID,
	SOD.ProductID,
	SOD.UnitPrice,
	SOD.OrderQty,
	SOD.UnitPriceDiscount,
	SO.Description
FROM AdventureWorks2017.Sales.SalesOrderDetail AS SOD
	INNER JOIN AdventureWorks2017.Sales.SpecialOfferProduct AS SOP ON SOD.ProductID = SOP.ProductID
	INNER JOIN AdventureWorks2017.Sales.SpecialOffer AS SO ON SOP.SpecialOfferID = SO.SpecialOfferID

--4.
--a)(6 bodova) kreirati pogled v_detalji gdje je korisniku potrebno prikazati identifikacijski broj narudzbe, spojeno ime i prezime kupca, grad isporuke, ukupna vrijednost narudzbe sa popustom i bez popusta, te u dodatnom polju informacija da li je narudzba placena karticom ("Placeno karticom" ili "Nije placeno karticom"). Rezultate sortirati prema vrijednosti narudzbe sa popustom u opadajucem redoslijedu. OBAVEZNO kreirati testni slucaj. (Novokreirana baza)

GO
CREATE OR ALTER VIEW v_detalji
AS
	SELECT TOP 100 PERCENT
		ZN.NarudzbaID,
		CONCAT(ZN.ImeKupca, ' ', ZN.PrezimeKupca) AS [Ime i prezime],
		ZN.NazivGrada,
		SUM(DN.Cijena * DN.Kolicina * (1 - DN.Popust)) AS [Ukupna vrijednost sa popustom],
		SUM(DN.Cijena * DN.Kolicina) AS [Ukupna vrijednost bez popusta],
		IIF(ZN.KreditnaKarticaID IS NULL, 'Nije placeno karticom', 'Placeno karticom') AS [Način plaćanja]
	FROM ZaglavljeNarudzbe AS ZN
		INNER JOIN DetaljiNarudzbe AS DN ON ZN.NarudzbaID = DN.NarudzbaID
	GROUP BY ZN.NarudzbaID, ZN.ImeKupca, ZN.PrezimeKupca, ZN.NazivGrada, ZN.KreditnaKarticaID
	ORDER BY 4 DESC
GO

SELECT * FROM v_detalji

--b)( 4 bodova) U kreiranoj bazi kreirati proceduru sp_insert_ZaglavljeNarudzbe kojom ce se omoguciti kreiranje nove narudzbe. OBAVEZNO kreirati testni slucaj. (Novokreirana baza).

GO
CREATE OR ALTER PROCEDURE sp_insert_ZaglavljeNarudzbe
(
	@DatumNarudzbe DATETIME,
	@DatumIsporuke DATETIME = NULL,
	@KreditnaKarticaId INT = NULL,
	@ImeKupca NVARCHAR(50),
	@PrezimeKupca NVARCHAR(50),
	@NazivGrada	NVARCHAR(30),
	@ProdavacID	INT = NULL,
	@NacinIsporuke NVARCHAR(50)
)
AS
	INSERT INTO ZaglavljeNarudzbe
	(
		DatumNarudzbe,
		DatumIsporuke,
		KreditnaKarticaID,
		ImeKupca,
		PrezimeKupca,
		NazivGrada,
		ProdavacID,
		NacinIsporuke
	)
	VALUES
	(
		@DatumNarudzbe,
		@DatumIsporuke,
		@KreditnaKarticaID,
		@ImeKupca,
		@PrezimeKupca,
		@NazivGrada,
		@ProdavacID,
		@NacinIsporuke
	)
GO

SELECT * FROM ZaglavljeNarudzbe

exec sp_insert_ZaglavljeNarudzbe 
	@DatumNarudzbe = '2025-09-06', 
	@DatumIsporuke = '2025-11-06',
	@KreditnaKarticaID = 16281,
	@ImeKupca = 'Haris',
	@PrezimeKupca = 'Velispahić',
	@NazivGrada = 'Kakanj',
	@ProdavacID = 279,
	@NacinIsporuke = 'Brza posta'

--c)(6 bodova) Kreirati upit kojim ce se prikazati ukupan broj proizvoda po kategorijama. Uslov je da se prikazu samo one kategorije kojima ne pripada vise od 30 proizvoda, a sadrze broj u bilo kojoj od rijeci i ne nalaze se u prodaji.(AdventureWorks2017)

GO
USE AdventureWorks2017

SELECT * FROM Production.Product

SELECT
	PC.Name,
	COUNT(*) AS [Broj proizvoda]
FROM Production.Product AS P
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
WHERE P.Name LIKE '%[0-9]%' AND P.SellEndDate IS NOT NULL
GROUP BY PC.Name
HAVING COUNT(*) <= 30

--d)(7 bodova) Kreirati upit koji ce prikazati uposlenike koji imaju iskustva(radili su na jednom odjelu) a trenutno rade na marketing ili odjelu za nabavku. Osobama po prestanku rada na odjelu se upise podatak datuma prestanka rada. Rezultat upita treba prikazati ime i prezime uposlenika, odjel na kojem rade. (AdventureWorks2017)

GO
USE AdventureWorks2017


SELECT
	P.FirstName,
	P.LastName,
	D.Name
FROM HumanResources.Employee AS E
	INNER JOIN HumanResources.EmployeeDepartmentHistory AS EDH ON E.BusinessEntityID = EDH.BusinessEntityID
	INNER JOIN HumanResources.Department AS D ON EDH.DepartmentID = D.DepartmentID
	INNER JOIN Person.Person AS P ON E.BusinessEntityID	= P.BusinessEntityID
WHERE EDH.EndDate IS NOT NULL
	AND	D.Name IN ('Marketing', 'Purchasing')
	AND EXISTS	(
				SELECT 1
				FROM HumanResources.EmployeeDepartmentHistory AS EDH_Inner
				WHERE EDH_Inner.BusinessEntityID = EDH.BusinessEntityID 
					AND EDH_Inner.EndDate IS NOT NULL
				)

--e)(7 bodova) Kreirati upit kojim ce se prikazati proizvod koji je najvise dana bio u prodaji(njegova prodaja je prestala) a pripada kategoriji bicikala. Proizvodu se pocetkom i po prestanku prodaje biljezi datum. Ukoliko postoji vise proizvoda sa istim vremenskim periodom kao i prvi prikazati ih u rezultatima upita. (AdventureWorks2017)

SELECT TOP 1 WITH TIES
	P.Name,
	DATEDIFF(DAY, P.SellStartDate, P.SellEndDate) AS [Dana u prodaji]
FROM Production.Product AS P
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
WHERE P.SellEndDate IS NOT NULL
	AND PC.Name = 'Bikes'
ORDER BY DATEDIFF(DAY, P.SellStartDate, P.SellEndDate) DESC

--(30 bodova)

--5.)
--
--a) (9 bodova) Prikazati nazive odjela na kojima TRENUTNO radi najmanje, odnosno najvise uposlenika(AdventureWorks2017)

SELECT
	Najvise.Name AS [Najvise],
	Najmanje.Name AS [Najmanje]
FROM
	(
	SELECT TOP 1
		D.Name
	FROM HumanResources.Employee AS E
		INNER JOIN HumanResources.EmployeeDepartmentHistory AS EDH ON E.BusinessEntityID = EDH.BusinessEntityID
		INNER JOIN HumanResources.Department AS D ON EDH.DepartmentID = D.DepartmentID
	GROUP BY D.Name
	ORDER BY COUNT(*) DESC
	) AS Najvise
CROSS JOIN
	(
	SELECT TOP 1
		D.Name
	FROM HumanResources.Employee AS E
		INNER JOIN HumanResources.EmployeeDepartmentHistory AS EDH ON E.BusinessEntityID = EDH.BusinessEntityID
		INNER JOIN HumanResources.Department AS D ON EDH.DepartmentID = D.DepartmentID
	GROUP BY D.Name
	ORDER BY COUNT(*) ASC
	) AS Najmanje

--b)(10 bodova) Kreirati upit kojim ce se prikazati ukupan broj obradjenih narudzbi i ukupnu vrijednost narudzbi sa popustom za svakog uposlenika pojedinacno, i to od zadnje 30% kreiranih datumski kreiranih narudzbi. Rezultate sortirati prema ukupnoj vrijednosti u opadajucem redoslijedu.(AdventureWorks2017)

GO

DECLARE @DatumOd DATETIME =	(
							SELECT TOP 1 *
							FROM
								(
								SELECT TOP 30 PERCENT
									SOH.OrderDate
								FROM Sales.SalesOrderHeader AS SOH
								ORDER BY 1 DESC
								) AS DatumOd
							ORDER BY 1 ASC
							)
DECLARE @DatumDo DATETIME =	(
							SELECT TOP 1 *
							FROM
								(
								SELECT TOP 30 PERCENT
									SOH.OrderDate
								FROM Sales.SalesOrderHeader AS SOH
								ORDER BY 1 DESC
								) AS DatumDo
							ORDER BY 1 DESC
							)

SELECT
	P.FirstName,
	P.LastName,
	COUNT(*) AS [Broj narudžbi],
	Ukupno.Suma AS [Ukupna vrijednost narudžbi]
FROM Sales.SalesPerson AS SP
	INNER JOIN Sales.SalesOrderHeader AS SOH ON SP.BusinessEntityID = SOH.SalesPersonID
	INNER JOIN Person.Person AS P ON SP.BusinessEntityID = P.BusinessEntityID
	INNER JOIN
		(
		SELECT
			SP.BusinessEntityID,
			SUM(SOD.OrderQty * SOD.UnitPrice * (1 - SOD.UnitPriceDiscount)) AS Suma
		FROM Sales.SalesPerson AS SP
			INNER JOIN Sales.SalesOrderHeader AS SOH ON SP.BusinessEntityID = SOH.SalesPersonID
			INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
		WHERE SOH.OrderDate BETWEEN @DatumOd AND @DatumDo
		GROUP BY SP.BusinessEntityID
		) AS Ukupno ON SP.BusinessEntityID = Ukupno.BusinessEntityID
WHERE SOH.OrderDate BETWEEN @DatumOd AND @DatumDo
GROUP BY P.FirstName, P.LastName, Ukupno.Suma
ORDER BY 4 DESC

GO

--f)(12 bodova) Upitom prikazati id autora, ime i prezime, napisano djelo i šifra. Prikazati samo one zapise gdje adresa autora pocinje sa ISKLJUCIVO 2 broja (Pubs)
--Šifra se sastoji od sljedećih vrijednosti: 
--	1.Prezime po pravilu (
--		prezime od 6 karaktera -> uzeti prva 4 karaktera; 
--		prezime od 10 karaktera-> uzeti prva 6 karaktera, 
--		za sve ostale slucajeve uzeti prva dva karaktera)
--	2.Ime prva 2 karaktera
--	3.Karakter /
--	4.Zip po pravilu(2 karaktera sa desne strane ukoliko je zadnja cifra u opsegu 0-5; u suprotnom 2 karaktera sa lijeve strane)
--	5.Karakter /
--	6.State(obrnuta vrijednost)
--	7.Phone(brojevi između space i karaktera -)
--	Primjer : za autora sa id-om 486-29-1786 šifra je LoCh/30/AC585
--			  za autora sa id-om 998-72-3567 šifra je RingAl/52/TU826

GO
USE pubs


SELECT
	A.au_id,
	A.au_fname,
	A.au_lname,
	CONCAT	(
			CASE
				WHEN LEN(A.au_lname) = 6 THEN LEFT(A.au_lname, 4)
				WHEN LEN(A.au_lname) = 10 THEN LEFT(A.au_lname, 6)
				ELSE LEFT(A.au_lname, 2)
			END,
			LEFT(A.au_fname, 2),
			'/',
			IIF(RIGHT(CAST(A.zip AS NVARCHAR(5)), 1) LIKE '[0-5]', RIGHT(CAST(A.zip AS NVARCHAR(5)), 2), LEFT(CAST(A.zip AS NVARCHAR(5)), 2)),
			'/',
			REVERSE(A.state),
			SUBSTRING(A.phone, 5, 3)
			) AS Sifra
FROM authors AS A
	INNER JOIN titleauthor AS TA ON A.au_id = TA.au_id
	INNER JOIN titles AS T ON TA.title_id = T.title_id
WHERE A.address LIKE '[0-9][0-9][^0-9]%'

--(31 bod)