--1.Kreirati bazu podataka sa imenom vaseg broja indeksa

GO
CREATE DATABASE [2024-07-12_V3]
GO
USE [2024-07-12_V3]

--2.U kreiranoj bazi tabelu sa strukturom : 
--a) Uposlenici 
-- UposlenikID cjelobrojni tip i primarni kljuc autoinkrement,
-- Ime 10 UNICODE karaktera (obavezan unos)
-- Prezime 20 UNICODE karaktera (obaveznan unos),
-- DatumRodjenja polje za unos datuma i vremena (obavezan unos)
-- UkupanBrojTeritorija cjelobrojni tip

CREATE TABLE Uposlenici
(
	UposlenikID INT CONSTRAINT PK_Uposlenici PRIMARY KEY IDENTITY(1, 1),
	Ime NVARCHAR(10) NOT NULL,
	Prezime NVARCHAR(20) NOT NULL,
	DatumRodjenja DATETIME NOT NULL,
	UkupanBrojTeritorija INT
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
	NarudzbaID INT CONSTRAINT PK_Narudzbe PRIMARY KEY IDENTITY(1, 1),
	UposlenikID INT CONSTRAINT FK_Narudzbe_Uposlenici FOREIGN KEY REFERENCES Uposlenici(UposlenikID),
	DatumNarudzbe DATETIME,
	ImeKompanijeKupca NVARCHAR(40),
	AdresaKupca NVARCHAR(60),
	UkupanBrojStavkiNarudzbe INT
)

--c) Proizvodi
-- ProizvodID cjelobrojni tip i primarni kljuc autoinkrement,
-- NazivProizvoda 40 UNICODE karaktera (obaveznan unos),
-- NazivKompanijeDobavljaca 40 UNICODE karaktera,
-- NazivKategorije 15 UNICODE karaktera

CREATE TABLE Proizvodi
(
	ProizvodID INT CONSTRAINT PK_Proizvodi PRIMARY KEY IDENTITY(1, 1),
	NazivProizvoda NVARCHAR(40) NOT NULL,
	NazivKompanijeDobavljaca NVARCHAR(40) NOT NULL,
	NazivKategorije NVARCHAR(15)
)

--d) StavkeNarudzbe
-- NarudzbaID cjelobrojni tip strani i primarni kljuc,
-- ProizvodID cjelobrojni tip strani i primarni kljuc,
-- Cijena novcani tip (obavezan unos),
-- Kolicina kratki cjelobrojni tip (obavezan unos),
-- Popust real tip podataka (obavezno)

CREATE TABLE StavkeNarudzbe
(
	NarudzbaID INT CONSTRAINT FK_StavkeNarudzbe_Narudzbe FOREIGN KEY REFERENCES Narudzbe(NarudzbaID),
	ProizvodID INT CONSTRAINT FK_StavkeNarudzbe_Proizvodi FOREIGN KEY REFERENCES Proizvodi(ProizvodID),
	Cijena MONEY NOT NULL,
	Kolicina SMALLINT NOT NULL,
	Popust REAL NOT NULL,

	CONSTRAINT PK_StavkeNarudzbe PRIMARY KEY (NarudzbaID, ProizvodID)
)

--(4 boda)


--3.Iz baze Northwind u svoju prebaciti sljedece podatke :
--a) U tabelu uposlenici sve uposlenike , Izracunata vrijednost za svakog uposlenika na osnovnu EmployeeTerritories -> UkupanBrojTeritorija

SET IDENTITY_INSERT Uposlenici ON
INSERT INTO Uposlenici
(
	UposlenikID,
	Ime,
	Prezime,
	DatumRodjenja,
	UkupanBrojTeritorija
)
SELECT
	E.EmployeeID,
	E.FirstName,
	E.LastName,
	E.BirthDate,
	COUNT(*)
FROM Northwind.dbo.Employees AS E
	INNER JOIN Northwind.dbo.EmployeeTerritories AS ET ON E.EmployeeID = ET.EmployeeID
GROUP BY E.EmployeeID, E.FirstName, E.LastName, E.BirthDate
SET IDENTITY_INSERT Uposlenici OFF

--b)UkupanBrojTeritorija U tabelu narudzbe sve narudzbe, Izracunata vrijensot za svaku narudzbu pojedinacno 
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
	INNER JOIN Northwind.dbo.Customers AS C ON O.CustomerID = C.CustomerID
	INNER JOIN Northwind.dbo.[Order Details] AS OD ON O.OrderID = OD.OrderID
GROUP BY O.OrderID, O.EmployeeID, O.OrderDate, C.CompanyName, C.Address
SET IDENTITY_INSERT Narudzbe OFF

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

--d) U tabelu StavkeNrudzbe sve narudzbe

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

--(5 bodova)


--4. 
--a) (4 boda) Kreirati indeks kojim ce se ubrzati pretraga po nazivu proizvoda, OBEVAZENO kreirati testni slucaj (Nova baza)

GO
CREATE INDEX ix_Proizvodi_NazivProizvoda
ON Proizvodi(NazivProizvoda)
GO

SELECT
	*
FROM Proizvodi AS P
WHERE P.NazivProizvoda LIKE '%L%'

DROP INDEX ix_Proizvodi_NazivProizvoda ON Proizvodi

--b) (4 boda) Kreirati proceduru sp_update_proizvodi kojom ce se izmjeniti podaci o prpoizvodima u tabeli. Korisnici mogu poslati jedan ili vise parametara te voditi raucna da ne dodje do gubitka podataka.(Nova baza)

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

exec sp_update_proizvodi 1, 'Caj'
exec sp_update_proizvodi 1, 'Chai'

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
		SUM(SN.Cijena * SN.Kolicina) AS Ukupno
	FROM StavkeNarudzbe AS SN
	WHERE SN.NarudzbaID = @idNarudzbe
	GROUP BY SN.NarudzbaID
GO

SELECT * FROM StavkeNarudzbe

SELECT * FROM f_4c(10248)

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
WHERE 
	ST.[Group] = 'Europe' AND 
	SOH.CreditCardID IS NOT NULL
ORDER BY SOH.SubTotal ASC

--e) (6 bodova) Prikazati ukupan broj porizvoda prema specijalnim ponudama.Potrebno je prebrojati samo one proizvode koji pripadaju kategoriji odjece ili imaju zabiljezen model (AdventureWorks)

SELECT
	SO.Description,
	COUNT(*) AS [Ukupno proizvoda]
FROM Production.Product AS P
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
	INNER JOIN Sales.SpecialOfferProduct AS SOP ON P.ProductID = SOP.ProductID
	INNER JOIN Sales.SpecialOffer AS SO ON SOP.SpecialOfferID = SO.SpecialOfferID
WHERE
	P.ProductModelID IS NOT NULL OR
	PC.Name = 'Clothing'
GROUP BY SO.Description


--f) (9 bodova) Prikazatu 5 kupaca koji su napravili najveci broj narudzbi u zadnjih 30% narudzbi iz 2011 ili 2012 god. (AdventureWorks)

GO

DECLARE @MIN_2011 DATETIME =
(
SELECT TOP 1
	SQ.OrderDate
FROM
	(
	SELECT TOP 30 PERCENT
		SOH.OrderDate
	FROM Sales.SalesOrderHeader AS SOH
	WHERE YEAR(SOH.OrderDate) = 2011
	ORDER BY 1 DESC
	) AS SQ
ORDER BY 1 ASC
)

DECLARE @MAX_2011 DATETIME =
(
SELECT TOP 1
	SQ.OrderDate
FROM
	(
	SELECT TOP 30 PERCENT
		SOH.OrderDate
	FROM Sales.SalesOrderHeader AS SOH
	WHERE YEAR(SOH.OrderDate) = 2011
	ORDER BY 1 DESC
	) AS SQ
ORDER BY 1 DESC
)

DECLARE @MIN_2012 DATETIME =
(
SELECT TOP 1
	SQ.OrderDate
FROM
	(
	SELECT TOP 30 PERCENT
		SOH.OrderDate
	FROM Sales.SalesOrderHeader AS SOH
	WHERE YEAR(SOH.OrderDate) = 2012
	ORDER BY 1 DESC
	) AS SQ
ORDER BY 1 ASC
)


DECLARE @MAX_2012 DATETIME =
(
SELECT TOP 1
	SQ.OrderDate
FROM
	(
	SELECT TOP 30 PERCENT
		SOH.OrderDate
	FROM Sales.SalesOrderHeader AS SOH
	WHERE YEAR(SOH.OrderDate) = 2012
	ORDER BY 1 DESC
	) AS SQ
ORDER BY 1 DESC
)

SELECT TOP 5
	P.FirstName,
	P.LastName,
	COUNT(*) AS [Ukupno]
FROM Sales.Customer AS C
	INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
	INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
WHERE
	SOH.OrderDate BETWEEN @MIN_2011 AND @MAX_2011 OR
	SOH.OrderDate BETWEEN @MIN_2012 AND @MAX_2012
GROUP BY P.FirstName, P.LastName
ORDER BY COUNT(*) DESC

GO

--g) (10 bodova) Menadzmentu kompanije potrebne su informacije o najmanje prodavanim proizvodima. (1 proizvod po kvartalu i godini), kako bi ih eliminisali iz ponude. Obavezno prikazati naziv o kojem se proizvodu radi i kvartal i godinu i adekvatnu poruku. (AdventureWorks)

SELECT
	SQ.Name,
	SQ.Godina,
	SQ.Kvartal,
	SQ.[Ukupna kolicina]
FROM
	(
	SELECT
		P.Name,
		YEAR(SOH.OrderDate) AS Godina,
		DATEPART(QUARTER, SOH.OrderDate) AS Kvartal,
		SUM(SOD.OrderQty) AS [Ukupna kolicina],
		ROW_NUMBER() OVER (PARTITION BY YEAR(SOH.OrderDate), DATEPART(QUARTER, SOH.OrderDate) ORDER BY SUM(SOD.OrderQty) ASC) AS rn
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
		INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
	GROUP BY P.Name, YEAR(SOH.OrderDate), DATEPART(QUARTER, SOH.OrderDate)
	) AS SQ
WHERE SQ.rn = 1

--5.
--a) (11 bodova) Prikazati kupce koji su kreirali narudzbe u minimalno 5 razlicitih mjeseci u 2012 godini.

SELECT
	P.FirstName,
	P.LastName,
	COUNT(DISTINCT MONTH(SOH.OrderDate)) AS Mjeseci
FROM Person.Person AS P	
	 INNER JOIN Sales.Customer AS C ON P.BusinessEntityID = C.PersonID
	 INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
WHERE YEAR(SOH.OrderDate) = 2012
GROUP BY P.FirstName, P.LastName
HAVING COUNT(DISTINCT MONTH(SOH.OrderDate)) >= 5

--b) (16 bodova) Prikazati 5 narudzbi sa najvise narucenih razlicitih proizvoda i 5 narudzbi sa najvise porizvoda koji pripadaju razlicitim potkategorijama. Upitom prikazati ime i prezime kupca, id narudzbe te ukupnu vrijednost narudzbe sa popoustom zaokruzenu na 2 decimale (AdventureWorks)

SELECT
	*
FROM
	(
	SELECT TOP 5
		P.FirstName,
		P.LastName,
		SOH.SalesOrderID,
		CAST(SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)) AS DECIMAL(18, 2)) AS [Ukupna vrijednost]
	FROM Sales.SalesOrderHeader AS SOH
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
		INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
		INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
	GROUP BY P.FirstName, P.LastName, SOH.SalesOrderID
	ORDER BY COUNT(DISTINCT SOD.ProductID) DESC
	) AS SQ1

UNION ALL

SELECT
	*
FROM
	(
	SELECT TOP 5
		P.FirstName,
		P.LastName,
		SOH.SalesOrderID,
		CAST(SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)) AS DECIMAL(18, 2)) AS [Ukupna vrijednost]
	FROM Sales.SalesOrderHeader AS SOH
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
		INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
		INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
		INNER JOIN Production.Product AS PROD ON SOD.ProductID = PROD.ProductID
	GROUP BY P.FirstName, P.LastName, SOH.SalesOrderID
	ORDER BY COUNT(DISTINCT PROD.ProductSubcategoryID) DESC
) AS SQ2