--1. Kroz SQL kod kreirati bazu podataka sa imenom vaseg broja indeksa

GO
CREATE DATABASE [2024-06-21]
GO
USE [2024-06-21]

--2. U kreiranoj bazi podataka kreirati tabele sa sljedecom strukturom:
--a)	Uposlenici
--•	UposlenikID, cjelobrojni tip i primarni kljuc, autoinkrement,
--•	Ime 10 UNICODE karaktera obavezan unos,
--•	Prezime 20 UNICODE karaktera obavezan unos
--•	DatumRodjenja polje za unos datuma i vremena obavezan unos
--•	UkupanBrojTeritorija, cjelobrojni tip

CREATE TABLE Uposlenici
(
	UposlenikID				INT				PRIMARY KEY		IDENTITY(1, 1),
	Ime						NVARCHAR(10)	NOT NULL,
	Prezime					NVARCHAR(20)	NOT NULL,
	DatumRodjenja			DATETIME		NOT NULL,
	UkupanBrojTeritorija	INT
)

--b)	Narudzbe
--•	NarudzbaID, cjelobrojni tip i primarni kljuc, autoinkrement
--•	UposlenikID, cjelobrojni tip, strani kljuc,
--•	DatumNarudzbe, polje za unos datuma i vremena,
--•	ImeKompanijeKupca, 40 UNICODE karaktera,
--•	AdresaKupca, 60 UNICODE karaktera

CREATE TABLE Narudzbe
(
	NarudzbaID					INT				PRIMARY KEY		IDENTITY(1, 1),
	UposlenikID					INT				FOREIGN KEY REFERENCES Uposlenici(UposlenikID),
	DatumNarudzbe				DATETIME,
	ImeKompanijeKupca			NVARCHAR(40),
	AdresaKupca					NVARCHAR(60)
)

--c) Proizvodi
--•	ProizvodID, cjelobrojni tip i primarni ključ, autoinkrement
--•	NazivProizvoda, 40 UNICODE karaktera (obavezan unos)
--•	NazivKompanijeDobavljaca, 40 UNICODE karaktera
--•	NazivKategorije, 15 UNICODE karaktera

CREATE TABLE Proizvodi
(
	ProizvodID					INT				PRIMARY KEY		IDENTITY(1, 1),
	NazivProizvoda				NVARCHAR(40)	NOT NULL,
	NazivKompanijeDobavljaca	NVARCHAR(40),
	NazivKategorije				NVARCHAR(15)
)

--d) StavkeNarudzbe
--•	NarudzbalD, cjelobrojni tip strani i primarni ključ
--•	ProizvodlD, cjelobrojni tip strani i primarni ključ
--•	Cijena, novčani tip (obavezan unos)
--•	Kolicina, kratki cjelobrojni tip (obavezan unos)
--•	Popust, real tip podatka (obavezan unos)

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

--4 boda

--3. Iz baze podataka Northwind u svoju bazu podataka prebaciti sljedeće podatke:
--a) U tabelu Uposlenici dodati sve uposlenike
--•	EmployeelD -> UposlenikID
--•	FirstName -> Ime
--•	LastName -> Prezime
--•	BirthDate -> DatumRodjenja
--•	lzračunata vrijednost za svakog uposlenika na osnovu EmployeeTerritories-:----UkupanBrojTeritorija

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

SELECT * FROM Uposlenici

--b) U tabelu Narudzbe dodati sve narudzbe
--•	OrderlD -> NarudzbalD
--•	EmployeelD -> UposlenikID
--•	OrderDate -> DatumNarudzbe
--•	CompanyName -> ImeKompanijeKupca
--•	Address -> AdresaKupca

SET IDENTITY_INSERT Narudzbe ON

INSERT INTO Narudzbe
(
	NarudzbaID,
	UposlenikID,
	DatumNarudzbe,
	ImeKompanijeKupca,
	AdresaKupca
)
SELECT
	O.OrderID,
	O.EmployeeID,
	O.OrderDate,
	C.CompanyName,
	C.Address
FROM Northwind.dbo.Orders AS O
	INNER JOIN Northwind.dbo.Customers AS C ON O.CustomerID = C.CustomerID

SET IDENTITY_INSERT Narudzbe OFF

--c) U tabelu Proizvodi dodati sve proizvode
--•	ProductID -> ProizvodlD
--•	ProductName -> NazivProizvoda
--•	CompanyName -> NazivKompanijeDobavljaca
--•	CategoryName -> NazivKategorije

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

--d) U tabelu StavkeNarudzbe dodati sve stavke narudzbe
--•	OrderlD -> NarudzbalD
--•	ProductID -> ProizvodlD
--•	UnitPrice -> Cijena
--•	Quantity -> Kolicina
--•	Discount -> Popust

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

--5 bodova

--4. 
--a) (4 boda) U tabelu StavkeNarudzbe dodati 2 nove izračunate kolone: vrijednostNarudzbeSaPopustom i vrijednostNarudzbeBezPopusta. Izračunate kolone već čuvaju podatke na osnovu podataka iz kolona! 

ALTER TABLE StavkeNarudzbe
ADD vrijednostNarudzbeSaPopustom AS Cijena * Kolicina * (1 - Popust)


ALTER TABLE StavkeNarudzbe
ADD vrijednostNarudzbeBezPopusta AS Cijena * Kolicina

SELECT * FROM StavkeNarudzbe

--b) (5 bodova) Kreirati pogled v_select_orders kojim će se prikazati ukupna zarada po uposlenicima od narudzbi kreiranih u zadnjem kvartalu 1996. godine. Pogledom je potrebno prikazati spojeno ime i prezime uposlenika, ukupna zarada sa popustom zaokruzena na dvije decimale i ukupna zarada bez popusta. Za prikaz ukupnih zarada koristiti OBAVEZNO koristiti izračunate kolone iz zadatka 4a. (Novokreirana baza)

GO
CREATE OR ALTER VIEW v_select_orders
AS
	SELECT
		CONCAT(U.Ime, ' ', U.Prezime) AS [Ime i prezime],
		CAST(SUM(SN.vrijednostNarudzbeBezPopusta) AS DECIMAL(18, 2)) AS [Ukupna zarada bez popusta],
		CAST(SUM(SN.vrijednostNarudzbeSaPopustom) AS DECIMAL(18, 2)) AS [Ukupna zarada sa popustom]
	FROM Uposlenici AS U
		INNER JOIN Narudzbe AS N ON U.UposlenikID = N.UposlenikID
		INNER JOIN StavkeNarudzbe AS SN ON N.NarudzbaID = SN.NarudzbaID
	WHERE YEAR(N.DatumNarudzbe) = 1996 AND DATEPART(QUARTER, N.DatumNarudzbe) = 4
	GROUP BY U.UposlenikID, U.Ime, U.Prezime
GO

SELECT * FROM v_select_orders

--c) (5 boda) Kreirati funkciju f_stariji_uposlenici koja će vraćati podatke u formi tabele na osnovu proslijedjenog parametra godineStarosti, cjelobrojni tip. Funkcija će vraćati one zapise u kojima su godine starosti kod uposlenika veće od unesene vrijednosti parametra. Potrebno je da se prilikom kreiranja funkcije u rezultatu nalaze sve kolone tabele uposlenici, zajedno sa izračunatim godinama starosti. Provjeriti ispravnost funkcije unošenjem kontrolnih vrijednosti. (Novokreirana baza) 

GO
CREATE OR ALTER FUNCTION f_stariji_uposlenici
(
	@godineStarosti INT
)
RETURNS TABLE
AS
RETURN
	SELECT
		*,
		DATEDIFF(YEAR, U.DatumRodjenja, GETDATE()) AS Starost
	FROM Uposlenici AS U
	WHERE DATEDIFF(YEAR, U.DatumRodjenja, GETDATE()) > @godineStarosti
GO

SELECT * FROM dbo.f_stariji_uposlenici(15)
SELECT * FROM dbo.f_stariji_uposlenici(65)
SELECT * FROM dbo.f_stariji_uposlenici(95)

--d) (7 bodova) Pronaći najprodavaniji proizvod u 2011 godini. Ulogu najprodavanijeg nosi onaj kojeg je najveći broj komada prodat. (AdventureWorks2017)

SELECT TOP 1
	P.ProductID,
	P.Name,
	SUM(SOD.OrderQty) AS [Prodavana kolicina]
FROM AdventureWorks2017.Sales.SalesOrderHeader AS SOH
	INNER JOIN AdventureWorks2017.Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
	INNER JOIN AdventureWorks2017.Production.Product AS P ON SOD.ProductID = P.ProductID
WHERE YEAR(SOH.OrderDate) = 2011
GROUP BY P.ProductID, P.Name
ORDER BY 3 DESC

--e) (6 bodova) Prikazati ukupan broj proizvoda prema specijalnim ponudama. Potrebno je prebrojati samo one proizvode koji pripadaju kategoriji odjeće. (AdventureWorks2017) 

SELECT
	SOP.SpecialOfferID,
	COUNT(*) AS [Broj proizvoda]
FROM AdventureWorks2017.Production.Product AS P
	INNER JOIN AdventureWorks2017.Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN AdventureWorks2017.Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
	INNER JOIN AdventureWorks2017.Sales.SpecialOfferProduct AS SOP ON P.ProductID = SOP.ProductID
WHERE PC.Name = 'Clothing'
GROUP BY SOP.SpecialOfferID


--f) (8 bodova) Prikazati najskuplji proizvod (List Price) u svakoj kategoriji. (AdventureWorks2017) 

SELECT
	PC.Name,
	MAX(P.ListPrice) AS [Najskuplji proizvod]
FROM AdventureWorks2017.Production.Product AS P
	INNER JOIN AdventureWorks2017.Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN AdventureWorks2017.Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
GROUP BY PC.Name

--g) (8 bodova) Prikazati proizvode čija je maloprodajna cijena (List Price) manja od prosječne maloprodajne cijene kategorije proizvoda kojoj pripada. (AdventureWorks2017) 

SELECT
	P.Name
FROM AdventureWorks2017.Production.Product AS P
	INNER JOIN AdventureWorks2017.Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN AdventureWorks2017.Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
	INNER JOIN
	(
	SELECT
		PC.ProductCategoryID,
		AVG(P.ListPrice) AS [Prosjecna cijena]
	FROM AdventureWorks2017.Production.Product AS P
		INNER JOIN AdventureWorks2017.Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
		INNER JOIN AdventureWorks2017.Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
	GROUP BY PC.ProductCategoryID
	) AS AvgCategory ON PC.ProductCategoryID = AvgCategory.ProductCategoryID
WHERE P.ListPrice < AvgCategory.[Prosjecna cijena]


--43 boda

--5. 
--a) (12 bodova) Pronaći najprodavanije proizvode, koji nisu na listi top 10 najprodavanijih proizvoda u zadnjih 11 godina. (AdventureWorks2017) 

USE AdventureWorks2017

SELECT TOP 10
	P.ProductID,
	SUM(SOD.OrderQty) AS Kolicine
FROM Production.Product AS P	
	INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
WHERE YEAR(SOH.OrderDate) > YEAR(GETDATE()) - 11
GROUP BY P.ProductID
ORDER BY 2 DESC

--b) (16 bodova) Prikazati ime i prezime kupca, id narudzbe, te ukupnu vrijednost narudzbe sa popustom (zaokruzenu na dvije decimale), uz uslov da su na nivou pojedine narudžbe naručeni proizvodi iz svih kategorija. (AdventureWorks2017) 

SELECT
	Pers.FirstName,
	Pers.LastName,
	SOH.SalesOrderID,
	CAST(SOH.SubTotal AS DECIMAL(18, 2)) AS SubTotal
FROM Person.Person AS Pers
	INNER JOIN Sales.Customer AS C ON Pers.BusinessEntityID = C.PersonID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
WHERE SOH.SalesOrderID IN

							(
							SELECT
								SOH.SalesOrderID
							FROM Production.Product AS P
								INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
								INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
								INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
							GROUP BY SOH.SalesOrderID
							HAVING COUNT(DISTINCT PS.ProductCategoryID) =
																			(
																			SELECT COUNT(*)
																			FROM Production.ProductCategory AS PC
																			)
							)

--28 bodova 

--6. Dokument teorijski_ispit 21 JUN24, preimcnovati vašim brojem indeksa, te u tom dokumentu izraditi pitanja.
--20 bodova 