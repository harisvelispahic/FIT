--1. Kroz SQL kod kreirati bazu podataka sa imenom vašeg broja indeksa.
GO
CREATE DATABASE [2023-09-22]
GO
USE [2023-09-22]

--2. U kreiranoj bazi podataka kreirati tabele sa sljedećom strukturom:
--a) Uposlenici
--• UposlenikID, 9 karaktera fiksne dužine i primarni ključ,
--• Ime, 20 karaktera (obavezan unos),
--• Prezime, 20 karaktera (obavezan unos),
--• DatumZaposlenja, polje za unos datuma i vremena (obavezan unos),
--• OpisPosla, 50 karaktera (obavezan unos)

CREATE TABLE Uposlenici
(
	UposlenikID			NCHAR(9)		PRIMARY KEY,
	Ime					NVARCHAR(20)	NOT NULL,
	Prezime				NVARCHAR(20)	NOT NULL,
	DatumZaposlenja		DATETIME		NOT NULL,
	OpisPosla			NVARCHAR(50)	NOT NULL
)

--b) Naslovi
--• NaslovID, 6 karaktera i primarni ključ,
--• Naslov, 80 karaktera (obavezan unos),
--• Tip, 12 karaktera fiksne dužine (obavezan unos),
--• Cijena, novčani tip podataka,
--• NazivIzdavaca, 40 karaktera,
--• GradIzadavaca, 20 karaktera,
--• DrzavaIzdavaca, 30 karaktera

CREATE TABLE Naslovi
(
	NaslovID			NVARCHAR(6)			PRIMARY KEY,
	Naslov				NVARCHAR(80)		NOT NULL,
	Tip					NCHAR(12)			NOT NULL,
	Cijena				MONEY,
	NazivIzdavaca		NVARCHAR(40),
	GradIzadavaca		NVARCHAR(20),
	DrzavaIzdavaca		NVARCHAR(30)
)

--c) Prodaja
--• ProdavnicaID, 4 karaktera fiksne dužine, strani i primarni ključ,
--• BrojNarudzbe, 20 karaktera, primarni ključ,
--• NaslovID, 6 karaktera, strani i primarni ključ,
--• DatumNarudzbe, polje za unos datuma i vremena (obavezan unos),
--• Kolicina, skraćeni cjelobrojni tip (obavezan unos)

CREATE TABLE Prodaja
(
	ProdavnicaID	NCHAR(4)		FOREIGN KEY REFERENCES Prodavnice(ProdavnicaID),
	BrojNarudzbe	NVARCHAR(20),
	NaslovID		NVARCHAR(6)		FOREIGN KEY REFERENCES Naslovi(NaslovID),
	DatumNarudzbe	DATETIME		NOT NULL,
	Kolicina		SMALLINT		NOT NULL,

	CONSTRAINT PK_Prodaja PRIMARY KEY (ProdavnicaID, BrojNarudzbe, NaslovID)
)

--d) Prodavnice
--• ProdavnicaID, 4 karaktera fiksne dužine i primarni ključ,
--• NazivProdavnice, 40 karaktera,
--• Grad, 40 karaktera
--6 bodova

CREATE TABLE Prodavnice
(
	ProdavnicaID		NCHAR(4)		PRIMARY KEY,
	NazivProdavnice		NVARCHAR(40),
	Grad				NVARCHAR(40)
)

--3. Iz baze podataka Pubs u svoju bazu podataka prebaciti sljedeće podatke:
--a) U tabelu Uposlenici dodati sve uposlenike
--• emp_id -> UposlenikID
--• fname -> Ime
--• lname -> Prezime
--• hire_date -> DatumZaposlenja
--• job_desc -> OpisPosla

INSERT INTO Uposlenici
(
	UposlenikID,
	Ime,
	Prezime,
	DatumZaposlenja,
	OpisPosla
)
SELECT
	E.emp_id,
	E.fname,
	E.lname,
	E.hire_date,
	J.job_desc
FROM pubs.dbo.employee AS E
	INNER JOIN pubs.dbo.jobs AS J ON E.job_id = J.job_id

--b) U tabelu Naslovi dodati sve naslove, na mjestima gdje nema pohranjenih podataka o nazivima izdavača
--zamijeniti vrijednost sa nepoznat izdavac
--• title_id -> NaslovID
--• title -> Naslov
--• type -> Tip
--• price -> Cijena
--• pub_name -> NazivIzdavaca
--• city -> GradIzdavaca
--• country -> DrzavaIzdavaca

INSERT INTO Naslovi
(
	NaslovID,
	Naslov,
	Tip,
	Cijena,
	NazivIzdavaca,
	GradIzadavaca,
	DrzavaIzdavaca
)
SELECT
	T.title_id,
	T.title,
	T.type,
	T.price,
	ISNULL(P.pub_name, 'nepoznat izdavac'),
	P.city,
	P.country
FROM pubs.dbo.titles AS T
	INNER JOIN pubs.dbo.publishers AS P ON T.pub_id = P.pub_id

--c) U tabelu Prodaja dodati sve stavke iz tabele prodaja
--• stor_id -> ProdavnicaID
--• order_num -> BrojNarudzbe
--• title_id -> NaslovID
--• ord_date -> DatumNarudzbe
--• qty -> Kolicina

INSERT INTO Prodaja
(
	ProdavnicaID,
	BrojNarudzbe,
	NaslovID,
	DatumNarudzbe,
	Kolicina
)
SELECT
	S.stor_id,
	S.ord_num,
	S.title_id,
	S.ord_date,
	S.qty
FROM pubs.dbo.sales AS S

--d) U tabelu Prodavnice dodati sve prodavnice
--• stor_id -> ProdavnicaID
--• store_name -> NazivProdavnice
--• city -> Grad

INSERT INTO Prodavnice
(
	ProdavnicaID,
	NazivProdavnice,
	Grad
)
SELECT
	S.stor_id,
	S.stor_name,
	S.city
FROM pubs.dbo.stores AS S

--6 bodova

--4.
--a) (6 bodova) Kreirati proceduru sp_update_naslov kojom će se uraditi update podataka u tabelu Naslovi.
--Korisnik može da pošalje jedan ili više parametara i pri tome voditi računa da se -ne- desi gubitak/brisanje
--zapisa. OBAVEZNO kreirati testni slučaj za kreiranu proceduru. (Novokreirana baza)

GO
CREATE OR ALTER PROCEDURE sp_update_naslov
(
	@NaslovID NVARCHAR(6),
	@Naslov NVARCHAR(80) = NULL,
	@Tip NCHAR(12) = NULL,
	@Cijena MONEY = NULL,
	@NazivIzdavaca NVARCHAR(40) = NULL,
	@GradIzdavaca NVARCHAR(20) = NULL,
	@DrzavaIzdavaca NVARCHAR(30) = NULL
)
AS
BEGIN
	UPDATE Naslovi
	SET
		Naslov = ISNULL(@Naslov, Naslov),
		Tip = ISNULL(@Tip, Tip),
		Cijena = ISNULL(@Cijena, Cijena),
		NazivIzdavaca = ISNULL(@NazivIzdavaca, NazivIzdavaca),
		GradIzadavaca = ISNULL(@GradIzdavaca, GradIzadavaca),
		DrzavaIzdavaca = ISNULL(@DrzavaIzdavaca, DrzavaIzdavaca)
	WHERE NaslovID = @NaslovID
END
GO

SELECT * FROM Naslovi

exec sp_update_naslov @NaslovID = 'BU1032', @Cijena = 21.99
exec sp_update_naslov @NaslovID = 'BU1032', @Cijena = 19.99

--b) (7 bodova) Kreirati upit kojim će se prikazati ukupna prodana količina i ukupna zarada bez popusta za
--svaku kategoriju proizvoda pojedinačno. Uslov je da proizvodi ne pripadaju kategoriji bicikala, da im je
--boja bijela ili crna te da ukupna prodana količina nije veća od 20000. Rezultate sortirati prema ukupnoj
--zaradi u opadajućem redoslijedu. (AdventureWorks2017)

GO
USE AdventureWorks2017

SELECT
	PC.ProductCategoryID,
	SUM(SOD.OrderQty) [Ukupna prodana količina],
	SUM(SOD.OrderQty * SOD.UnitPrice) AS [Ukupna zarada bez popusta]
FROM Production.ProductCategory AS PC
	INNER JOIN Production.ProductSubcategory AS PS ON PC.ProductCategoryID = PS.ProductCategoryID
	INNER JOIN Production.Product AS P ON PS.ProductSubcategoryID = P.ProductSubcategoryID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
WHERE PC.Name NOT LIKE 'Bikes' AND (P.Color LIKE 'White' OR P.Color LIKE 'Black')
GROUP BY PC.ProductCategoryID
HAVING SUM(SOD.OrderQty) < 20000
ORDER BY 3 DESC

--c) (8 bodova) Kreirati upit koji prikazuje kupce koji su u maju mjesecu 2013 ili 2014 godine naručili
--proizvod „Front Brakes“ u količini većoj od 5. Upitom prikazati spojeno ime i prezime kupca, email,
--naručenu količinu i datum narudžbe formatiran na način dan.mjesec.godina (AdventureWorks2017)

SELECT
	CONCAT(Pers.FirstName, ' ', Pers.LastName) AS [Ime i prezime],
	EA.EmailAddress,
	SOD.OrderQty,
	FORMAT(SOH.OrderDate, 'dd.MM.yyyy') AS OrderDate
FROM Person.Person AS Pers
	INNER JOIN Person.EmailAddress AS EA ON Pers.BusinessEntityID = EA.BusinessEntityID
	INNER JOIN Sales.Customer AS C ON Pers.BusinessEntityID = C.PersonID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
	INNER JOIN Production.Product AS Prod ON SOD.ProductID = Prod.ProductID
WHERE 
	Prod.Name = 'Front Brakes' AND 
	MONTH(SOH.OrderDate) = 5 AND
	(YEAR(SOH.OrderDate) = 2013 OR YEAR(SOH.OrderDate) = 2014) AND
	SOD.OrderQty > 5

--d) (10 bodova) Kreirati upit koji će prikazati naziv kompanije dobavljača koja je dobavila proizvode, koji
--se u najvećoj količini prodaju (najprodavaniji). Uslov je da proizvod pripada kategoriji morske hrane i
--da je dostavljen/isporučen kupcu. Također uzeti u obzir samo one proizvode na kojima je popust odobren.
--U rezultatima upita prikazati naziv kompanije dobavljača i ukupnu prodanu količinu proizvoda.
--(Northwind)

GO
USE Northwind

SELECT TOP 1
	S.CompanyName,
	SUM(OD.Quantity) AS [Ukupna prodana količina]
FROM Suppliers AS S
	INNER JOIN Products AS P ON S.SupplierID = P.SupplierID
	INNER JOIN Categories AS C ON P.CategoryID = C.CategoryID
	INNER JOIN [Order Details] AS OD ON P.ProductID = OD.ProductID
	INNER JOIN Orders AS O ON OD.OrderID = O.OrderID
WHERE 
	C.CategoryName = 'Seafood' AND
	O.ShippedDate IS NOT NULL AND
	OD.Discount > 0
GROUP BY S.CompanyName
ORDER BY 2 DESC

--e) (11 bodova) Kreirati upit kojim će se prikazati narudžbe u kojima je na osnovu popusta kupac uštedio
--2000KM i više. Upit treba da sadrži identifikacijski broj narudžbe, spojeno ime i prezime kupca, te
--stvarnu ukupnu vrijednost narudžbe zaokruženu na 2 decimale. Rezultate sortirati po ukupnoj vrijednosti
--narudžbe u opadajućem redoslijedu.
-- 43 boda

SELECT
	O.OrderID,
	C.ContactName,
	CAST(SUM(OD.Quantity * OD.UnitPrice * (1 - OD.Discount)) AS DECIMAL(18, 2)) AS Ukupno
FROM Customers AS C
	INNER JOIN Orders AS O ON C.CustomerID = O.CustomerID
	INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
GROUP BY O.OrderID, C.ContactName
HAVING SUM(OD.Quantity * OD.UnitPrice - OD.Quantity * OD.UnitPrice * (1 - OD.Discount)) >= 2000
ORDER BY 3 DESC

--5.
--a) (13 bodova) Kreirati upit koji će prikazati kojom kompanijom (ShipMethod(Name)) je isporučen najveći
--broj narudžbi, a kojom najveća ukupna količina proizvoda. (AdventureWorks2017)

GO
USE AdventureWorks2017

SELECT *
FROM
	(
	SELECT TOP 1
		SM.Name,
		COUNT(*) AS [Najveći broj narudžbi]
	FROM Purchasing.ShipMethod AS SM
		INNER JOIN Sales.SalesOrderHeader AS SOH ON SM.ShipMethodID = SOH.ShipMethodID
	GROUP BY SM.Name
	ORDER BY 2 DESC
	) AS SUBQ1
CROSS JOIN
	(
	SELECT TOP 1
		SM.Name,
		SUM(SOD.OrderQty) AS [Najveća ukupna količina proizvoda]
	FROM Purchasing.ShipMethod AS SM
		INNER JOIN Sales.SalesOrderHeader AS SOH ON SM.ShipMethodID = SOH.ShipMethodID
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
	GROUP BY SM.Name
	ORDER BY 2 DESC
	) AS SUBQ2

--b) (8 bodova) Modificirati prethodno kreirani upit na način ukoliko je jednom kompanijom istovremeno
--isporučen najveći broj narudžbi i najveća ukupna količina proizvoda upitom prikazati poruku „Jedna
--kompanija“, u suprotnom „Više kompanija“ (AdventureWorks2017)

SELECT
	IIF(SUBQ1.Name = SUBQ2.Name, 'Jedna kompanija', 'Više kompanija') AS Poruka
	--CASE
	--	WHEN SUBQ1.Name = SUBQ2.Name THEN 'Jedna kompanija'
	--	ELSE 'Više kompanija'
	--END
FROM
	(
	SELECT TOP 1
		SM.Name,
		COUNT(*) AS [Najveći broj narudžbi]
	FROM Purchasing.ShipMethod AS SM
		INNER JOIN Sales.SalesOrderHeader AS SOH ON SM.ShipMethodID = SOH.ShipMethodID
	GROUP BY SM.Name
	ORDER BY 2 DESC
	) AS SUBQ1
CROSS JOIN
	(
	SELECT TOP 1
		SM.Name,
		SUM(SOD.OrderQty) AS [Najveća ukupna količina proizvoda]
	FROM Purchasing.ShipMethod AS SM
		INNER JOIN Sales.SalesOrderHeader AS SOH ON SM.ShipMethodID = SOH.ShipMethodID
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
	GROUP BY SM.Name
	ORDER BY 2 DESC
	) AS SUBQ2

--c) (4 boda) Kreirati indeks IX_Naslovi_Naslov kojim će se ubrzati pretraga prema naslovu. OBAVEZNO
--kreirati testni slučaj. (NovokreiranaBaza)

GO
USE [2023-09-22]

CREATE INDEX IX_Naslovi_Naslov
ON Naslovi(Naslov)

SELECT *
FROM Naslovi
WHERE Naslov LIKE '%l%'

DROP INDEX IX_Naslovi_Naslov ON Naslovi

--25 bodova
--6. Dokument teorijski_ispit 22SEP23, preimenovati vašim brojem indeksa, te u tom --dokumentu izraditi pitanja.
--20 bodova
--SQL skriptu (bila prazna ili ne) imenovati Vašim brojem indeksa npr IB210001.sql, --teorijski dokument imenovan
--Vašim brojem indexa npr IB210001.docx upload-ovati ODVOJEDNO na ftp u folder -Upload.
--Maksimalan broj bodova:100
--Prag prolaznosti: 55
