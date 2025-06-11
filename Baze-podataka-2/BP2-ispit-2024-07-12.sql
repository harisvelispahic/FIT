--1.Kreirati bazu podataka sa imenom vaseg broja indeksa

GO
CREATE DATABASE [2024-07-12]
GO
USE [2024-07-12]

--2.U kreiranoj bazi tabelu sa strukturom : 
--a) Uposlenici 
-- UposlenikID cjelobrojni tip i primarni kljuc autoinkrement,
-- Ime 10 UNICODE karaktera (obavezan unos)
-- Prezime 20 UNICODE karaktera (obaveznan unos),
-- DatumRodjenja polje za unos datuma i vremena (obavezan unos)
-- UkupanBrojTeritorija cjelobrojni tip

CREATE TABLE Uposlenici
(
	UposlenikID				INT				PRIMARY KEY		IDENTITY(1, 1),
	Ime						NVARCHAR(10)	NOT NULL,
	Prezime					NVARCHAR(20)	NOT NULL,
	DatumRodjenja			DATETIME		NOT NULL,
	UkupanBrojTeritorija	INT
)

--b) Narudzbe
-- NarudzbaID cjelobrojni tip i primarni kljuc autoinkrement,
-- UposlenikID cjelobrojni tip i strani kljuc,
-- DatumNarudzbe polje za unos datuma i vremena,
-- ImeKompanijeKupca 40 UNICODE karaktera,
-- AdresaKupca 60 UNICODE karaktera,
-- UkupanBrojStavkiNarudzbe cjelobrojni tip

CREATE TABLE Narudzbe
(
	NarudzbaID					INT				PRIMARY KEY		IDENTITY(1, 1),
	UposlenikID					INT				FOREIGN KEY REFERENCES Uposlenici(UposlenikID),
	DatumNarudzbe				DATETIME,
	ImeKompanijeKupca			NVARCHAR(40),
	AdresaKupca					NVARCHAR(60),
	UkupanBrojStavkiNarudzbe	INT
)

--c) Proizvodi
-- ProizvodID cjelobrojni tip i primarni kljuc autoinkrement,
-- NazivProizvoda 40 UNICODE karaktera (obaveznan unos),
-- NazivKompanijeDobavljaca 40 UNICODE karaktera,
-- NazivKategorije 15 UNICODE karaktera

CREATE TABLE Proizvodi
(
	ProizvodID					INT				PRIMARY KEY		IDENTITY(1, 1),
	NazivProizvoda				NVARCHAR(40)	NOT NULL,
	NazivKompanijeDobavljaca	NVARCHAR(40),
	NazivKategorije				NVARCHAR(15)
)

--d) StavkeNarudzbe
-- NarudzbaID cjelobrojni tip strani i primarni kljuc,
-- ProizvodID cjelobrojni tip strani i primarni kljuc,
-- Cijena novcani tip (obavezan unos),
-- Kolicina kratki cjelobrojni tip (obavezan unos),
-- Popust real tip podataka (obavezno)

CREATE TABLE StavkeNarudzbe
(
	NarudzbaID		INT,
	ProizvodID		INT,
	Cijena			MONEY		NOT NULL,
	Kolicina		SMALLINT	NOT NULL,
	Popust			REAL		NOT NULL,

	CONSTRAINT PK_StavkeNarudzbe PRIMARY KEY (NarudzbaID, ProizvodID),
	CONSTRAINT FK_StavkeNarudzbe_Narudzbe FOREIGN KEY (NarudzbaID) REFERENCES Narudzbe(NarudzbaID),
	CONSTRAINT FK_StavkeNarudzbe_Proizvodi FOREIGN KEY (ProizvodID) REFERENCES Proizvodi(ProizvodID)
)

--(4 boda)


--3.Iz baze Northwind u svoju prebaciti sljedece podatke :
--a) U tabelu uposlenici sve uposlenike , Izracunata vrijednost za svakog uposlenika
-- na osnovnu EmployeeTerritories -> UkupanBrojTeritorija

INSERT INTO Uposlenici
SELECT
	E.FirstName,
	E.LastName,
	E.BirthDate,
	COUNT(ET.TerritoryID)
FROM Northwind.dbo.Employees AS E
	INNER JOIN Northwind.dbo.EmployeeTerritories AS ET ON E.EmployeeID = ET.EmployeeID
GROUP BY E.EmployeeID, E.FirstName, E.LastName, E.BirthDate

SELECT * FROM Uposlenici

--b) U tabelu narudzbe sve narudzbe, Izracunata vrijednost za svaku narudzbu pojedinacno 
-- ->UkupanBrojStavkiNarudzbe

SET IDENTITY_INSERT Narudzbe ON

INSERT INTO Narudzbe
(
	NarudzbaID,
	UposlenikID,
	DatumNarudzbe,
	ImeKompanijeKupca,
	AdresaKupca,
	UkupanBrojStavkiNarudzbe
)
SELECT
	O.OrderID,
	O.EmployeeID,
	O.OrderDate,
	C.CompanyName,
	C.Address,
	COUNT(*)
FROM Northwind.dbo.Orders AS O
	INNER JOIN Northwind.dbo.[Order Details] AS OD ON O.OrderID = OD.OrderID
	INNER JOIN Northwind.dbo.Customers AS C ON O.CustomerID = C.CustomerID
GROUP BY O.OrderID, O.EmployeeID, O.OrderDate, C.CompanyName, C.Address

SET IDENTITY_INSERT Narudzbe OFF

SELECT * FROM Narudzbe

--c) U tabelu proizvodi sve proizvode

SET IDENTITY_INSERT Proizvodi ON

INSERT INTO Proizvodi
(
	ProizvodID,
	NazivProizvoda,
	NazivKompanijeDobavljaca,
	NazivKategorije
)
SELECT
	P.ProductID,
	P.ProductName,
	S.CompanyName,
	C.CategoryName
FROM Northwind.dbo.Products AS P
	INNER JOIN Northwind.dbo.Suppliers AS S ON P.SupplierID = S.SupplierID
	INNER JOIN Northwind.dbo.Categories AS C ON P.CategoryID = C.CategoryID

SET IDENTITY_INSERT Proizvodi OFF

SELECT * FROM Proizvodi

--d) U tabelu StavkeNarudzbe sve narudzbe

INSERT INTO StavkeNarudzbe
(
	NarudzbaID,
	ProizvodID,
	Cijena,
	Kolicina,
	Popust
)
SELECT
	OD.OrderID,
	OD.ProductID,
	OD.UnitPrice,
	OD.Quantity,
	OD.Discount
FROM Northwind.dbo.[Order Details] AS OD

SELECT * FROM StavkeNarudzbe

--(5 bodova)


--4. 
--a) (4 boda) Kreirati indeks kojim ce se ubrzati pretraga po nazivu proizvoda, OBEVAZENO kreirati testni slucaj (Nova baza)

CREATE INDEX ix_NazivProizvoda
ON Proizvodi(NazivProizvoda)

SELECT *
FROM Proizvodi AS P
WHERE P.NazivProizvoda LIKE 'P%'

DROP INDEX ix_NazivProizvoda ON Proizvodi

--b) (4 boda) Kreirati proceduru sp_update_proizvodi kojom ce se izmijeniti podaci o proizvodima u tabeli. Korisnici mogu poslati jedan ili vise parametara te voditi racuna da ne dodje do gubitka podataka.(Nova baza)

GO
CREATE OR ALTER PROCEDURE sp_update_proizvodi
(
	@ProizvodID INT,
	@NazivProizvoda NVARCHAR(40) = NULL,
	@NazivKompanijeDobavljaca NVARCHAR(40) = NULL,
	@NazivKategorije NVARCHAR(15) = NULL
)
AS
BEGIN
	UPDATE Proizvodi
	SET
		NazivProizvoda = ISNULL(@NazivProizvoda, NazivProizvoda),
		NazivKompanijeDobavljaca = ISNULL(@NazivKompanijeDobavljaca, NazivKompanijeDobavljaca),
		NazivKategorije = ISNULL(@NazivKategorije, NazivKategorije)
	WHERE ProizvodID = @ProizvodID
END
GO

SELECT * FROM Proizvodi

exec sp_update_proizvodi @ProizvodID = 1, @NazivProizvoda = 'Čaj'
exec sp_update_proizvodi @ProizvodID = 1, @NazivProizvoda = 'Chai'

--c) (5 bodova) Kreirati funckiju f_4c koja ce vratiti podatke u tabelarnom obliku na osnovnu prosljedjenog parametra idNarudzbe cjelobrojni tip. Funckija ce vratiti one narudzbe ciji id odgovara poslanom parametru. Potrebno je da se prilikom kreiranja funkcije u rezultatu nalazi id narudzbe, ukupna vrijednost bez popusta. OBAVEZNO testni slucaj (Nova baza)

GO
CREATE OR ALTER FUNCTION f_4c
(
	@idNarudzbe INT
)
RETURNS TABLE
AS
RETURN
	SELECT
		SN.NarudzbaID,
		(SN.Cijena * SN.Kolicina) AS [Ukupna vrijednost bez popusta]
	FROM StavkeNarudzbe AS SN
	WHERE SN.NarudzbaID = @idNarudzbe
GO

SELECT * FROM StavkeNarudzbe

SELECT * FROM dbo.f_4c(10248)

--d) (6 bodova) Pronaci najmanju narudzbu placenu karticom i isporuceno na porducje Europe, uz id narudzbe prikazati i spojeno ime i prezime kupca te grad u koji je isporucena narudzba (AdventureWorks)

GO
USE AdventureWorks2017

SELECT TOP 1
	SOH.SalesOrderID,
	CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
	A.City
FROM Sales.SalesOrderHeader AS SOH 
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
	INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
	INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
	INNER JOIN Person.Address AS A ON SOH.ShipToAddressID = A.AddressID
WHERE CreditCardID IS NOT NULL AND ST.[Group] = 'Europe'
ORDER BY SOH.TotalDue


--e) (6 bodova) Prikazati ukupan broj porizvoda prema specijalnim ponudama.Potrebno je prebrojati samo one proizvode koji pripadaju kategoriji odjece ili imaju zabiljezen model (AdventureWorks)

SELECT
	SOP.SpecialOfferID,
	COUNT(*) AS [Broj proizvoda]
FROM Production.Product AS P
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
	INNER JOIN Sales.SpecialOfferProduct AS SOP ON P.ProductID = SOP.ProductID
WHERE PC.Name = 'Clothing' AND P.ProductModelID IS NOT NULL
GROUP BY SOP.SpecialOfferID

--f) (9 bodova) Prikazati 5 kupaca koji su napravili najveci broj narudzbi u zadnjih 30% narudzbi iz 2011 ili 2012 god. (AdventureWorks)

GO

CREATE OR ALTER VIEW v_Raspon_Datuma
AS
SELECT TOP 30 PERCENT
	SOH.OrderDate
FROM Sales.SalesOrderHeader AS SOH
WHERE YEAR(SOH.OrderDate) = 2011

UNION

SELECT TOP 30 PERCENT
	SOH.OrderDate
FROM Sales.SalesOrderHeader AS SOH
WHERE YEAR(SOH.OrderDate) = 2012

GO

DECLARE @najranijiDatum DATETIME = 
									(
									SELECT TOP 1 *
									FROM v_Raspon_Datuma
									ORDER BY 1 ASC
									)
DECLARE @najkasnijiDatum DATETIME = 
									(
									SELECT TOP 1 *
									FROM v_Raspon_Datuma
									ORDER BY 1 DESC
									)

SELECT TOP 5
	C.CustomerID,
	COUNT(*)
FROM Sales.Customer AS C
	INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
WHERE SOH.OrderDate BETWEEN @najranijiDatum AND @najkasnijiDatum
GROUP BY C.CustomerID
ORDER BY 2 DESC

GO

--g) (10 bodova) Menadzmentu kompanije potrebne su informacije o najmanje prodavanim proizvodima. ...kako bi ih eliminisali iz ponude. Obavezno prikazati naziv o kojem se proizvodu radi i kvartal i godinu i adekvatnu poruku. (AdventureWorks)

--5.
--a) (11 bodova) Prikazati kupce koji su kreirali narudzbe u minimalno 5 razlicitih mjeseci u 2012 godini.

SELECT
	C.CustomerID,
	COUNT(DISTINCT MONTH(SOH.OrderDate))
FROM Sales.Customer AS C
	INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
WHERE YEAR(SOH.OrderDate) = 2012
GROUP BY C.CustomerID
HAVING COUNT(DISTINCT MONTH(SOH.OrderDate)) >= 5


--b) (16 bodova) Prikazati 5 narudzbi sa najvise narucenih razlicitih proizvoda i 5 narudzbi sa najvise proizvoda koji pripadaju razlicitim potkategorijama. Upitom prikazati ime i prezime kupca, id narudzbe te ukupnu vrijednost narudzbe sa popoustom zaokruzenu na 2 decimale (AdventureWorks)

SELECT *
FROM
	(
	SELECT TOP 5
		P.FirstName,
		P.LastName,
		SOH.SalesOrderID,
		CAST(SOH.TotalDue AS DECIMAL(18, 2)) AS [Ukupna vrijednost narudzbe]
	FROM Sales.SalesOrderHeader AS SOH
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
		INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
		INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
	GROUP BY P.FirstName, P.LastName, SOH.SalesOrderID, SOH.TotalDue
	ORDER BY COUNT(DISTINCT SOD.ProductID) DESC
	) AS SUBQ1

UNION ALL

SELECT *
FROM
	(
	SELECT TOP 5
		P.FirstName,
		P.LastName,
		SOH.SalesOrderID,
		CAST(SOH.TotalDue AS DECIMAL(18, 2)) AS [Ukupna vrijednost narudzbe]
	FROM Person.Person AS P
		INNER JOIN Sales.Customer AS C ON P.BusinessEntityID = C.PersonID
		INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
		INNER JOIN Production.Product AS PROD ON SOD.ProductID = PROD.ProductID
	GROUP BY P.FirstName, P.LastName, SOH.SalesOrderID, SOH.TotalDue
	ORDER BY COUNT(DISTINCT PROD.ProductSubcategoryID) DESC
	) AS SUBQ2