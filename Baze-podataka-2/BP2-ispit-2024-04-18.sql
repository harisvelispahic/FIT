--1.	Kroz SQL kod kreirati bazu podataka sa imenom vašeg broja indeksa.

GO
CREATE DATABASE [2024-04-18]
GO
USE [2024-04-18]

--2.	U kreiranoj bazi podataka kreirati tabele sa sljedećom strukturom:
--a)	Izdavaci
--•	IzdavacID, 4 karaktera fiksne dužine i primarni ključ,
--•	NazivIzdavaca, 40 karaktera, (zadana vrijednost „nepoznat izdavac“)
--•	Drzava, 30 karaktera,
--•	Logo, fotografija 

CREATE TABLE Izdavaci
(
	IzdavacID CHAR(4) CONSTRAINT PK_Izdavaci PRIMARY KEY,
	NazivIzdavaca VARCHAR(40) DEFAULT('nepoznat izdavac'),
	Drzava VARCHAR(30),
	Logo IMAGE
)

--b)	Naslovi
--•	NaslovID, 6 karaktera i primarni ključ,
--•	Naslov, 80 karaktera (obavezan unos),
--•	Tip, 12 karaktera fiksne dužine (obavezan unos),
--•	Cijena, novčani tip podataka,  
--•	IzdavacID, 4 karaktera fiksne dužine, strani ključ

CREATE TABLE Naslovi
(
	NaslovID VARCHAR(6) CONSTRAINT PK_Naslovi PRIMARY KEY,
	Naslov VARCHAR(80) NOT NULL,
	Tip CHAR(12) NOT NULL,
	Cijena MONEY,
	IzdavacID CHAR(4) CONSTRAINT FK_Naslovi_Izdavaci FOREIGN KEY REFERENCES Izdavaci(IzdavacID)
)

--c)	Prodaja 
--•	ProdavnicaID, 4 karaktera fiksne dužine, strani i primarni ključ,
--•	BrojNarudzbe, 20 karaktera, primarni ključ,
--•	NaslovID, 6 karaktera, strani i primarni ključ,
--•	DatumNarudzbe, polje za unos datuma i vremena (obavezan unos),
--•	Kolicina, skraćeni cjelobrojni tip (obavezan unos, dozvoljen unos brojeva većih od 0)

CREATE TABLE Prodaja
(
	ProdavnicaID CHAR(4) CONSTRAINT FK_Prodaja_Prodavnice FOREIGN KEY REFERENCES Prodavnice(ProdavnicaID),
	BrojNarudzbe VARCHAR(20),
	NaslovID VARCHAR(6) CONSTRAINT FK_Prodaja_Naslovi FOREIGN KEY REFERENCES Naslovi(NaslovID),
	DatumNarudzbe DATETIME NOT NULL,
	Kolicina SMALLINT CONSTRAINT CK_KolicinaGT0 CHECK(Kolicina > 0) NOT NULL,

	CONSTRAINT PK_Prodaja PRIMARY KEY (ProdavnicaID, BrojNarudzbe, NaslovID)
)

--d)	Prodavnice
--•	ProdavnicaID, 4 karaktera fiksne dužine i primarni ključ,
--•	NazivProdavnice, 40 karaktera,
--•	Grad, 40 karaktera
--4 bodova

CREATE TABLE Prodavnice
(
	ProdavnicaID CHAR(4) CONSTRAINT PK_Prodavnice PRIMARY KEY,
	NazivProdavnice VARCHAR(40),
	Grad VARCHAR(40),
)

--3.	Iz baze podataka Pubs u svoju bazu podataka prebaciti sljedeće podatke:
--a)	U tabelu Izdavaci dodati sve izdavače
--•	pub_id -> IzdavacID
--•	pub_name -> NazivIzdavaca
--•	country -> Drzava
--•	Logo -> Logo

INSERT INTO Izdavaci
(
	IzdavacID,
	NazivIzdavaca,
	Drzava,
	Logo
)
SELECT
	P.pub_id,
	P.pub_name,
	P.country,
	PI.logo
FROM pubs.dbo.publishers AS P
	INNER JOIN pubs.dbo.pub_info AS PI ON P.pub_id = PI.pub_id

--b)	U tabelu Naslovi dodati sve naslove, na mjestima gdje nema pohranjenih podataka o cijeni zamijeniti vrijednost sa 0
--•	title_id -> NaslovID
--•	title -> Naslov 	
--•	type -> Tip
--•	price -> Cijena 
--•	pub_id-> IzdavacID

INSERT INTO Naslovi
(
	NaslovID,
	Naslov,
	Tip,
	Cijena,
	IzdavacID
)
SELECT
	T.title_id,
	T.title,
	T.type,
	ISNULL(T.price, 0),
	T.pub_id
FROM pubs.dbo.titles AS T

--c)	U tabelu Prodaja dodati sve stavke iz tabele prodaja
--•	stor_id -> ProdavnicaID
--•	order_num -> BrojNarudzbe
--•	title_id -> NaslovID
--•	ord_date -> DatumNarudzbe
--•	qty -> Kolicina

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

--d)	U tabelu Prodavnice dodati sve prodavnice
--•	stor_id -> ProdavnicaID
--•	store_name -> NazivProdavnice
--•	city -> Grad
--4 bodova

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

--4.	
--a)	(6 bodova) Prikazati ukupan broj narudžbi po uposlenicima koji su mlađi od 65 godina, žive na području Velike Britanije i kreirali su više od 50 narudžbi. (Northwind)

GO
USE Northwind


SELECT
	E.EmployeeID,
	COUNT(*) AS [Broj narudzbi]
FROM Employees AS E
	INNER JOIN Orders AS O ON E.EmployeeID = O.EmployeeID
WHERE
	E.Country = 'UK' AND
	DATEDIFF(YEAR, E.BirthDate, GETDATE()) < 65
GROUP BY E.EmployeeID
HAVING COUNT(*) > 50

--b)	(4 boda) Prikazati uposlenike koji su obradili 100 najvećih narudžbi na području Evrope. Upitom prikazati ID narudžbe, ime i prezime uposlenika, tip i broj kreditne kartice, ukupnu vrijednost narudžbe sa popustom, te ukupnu vrijednost narudžbe sa troškovima prevoza i taksom. Uz vrijednosti prikazati valutu 'KM'. (AdventureWorks2017)

GO
USE AdventureWorks2017


SELECT TOP 100
	SOH.SalesOrderID,
	SOH.SalesPersonID,
	P.FirstName,
	P.LastName,
	P.PersonType,
	SOH.CreditCardID,
	CONCAT(SOH.SubTotal, ' KM') AS SubTotal,
	CONCAT(SOH.TotalDue, ' KM') AS TotalDue
FROM Sales.SalesOrderHeader AS SOH
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
	INNER JOIN Sales.SalesPerson AS SP ON SOH.SalesPersonID = SP.BusinessEntityID
	INNER JOIN HumanResources.Employee AS E ON SP.BusinessEntityID = E.BusinessEntityID
	INNER JOIN Person.Person AS P ON E.BusinessEntityID = P.BusinessEntityID
WHERE ST.[Group] = 'Europe'
ORDER BY TotalDue DESC

--c)	(4 boda) Prikazati proizvode iz kategorije Bicikla koji nikad nisu prodavani (AdventureWorks2017)

SELECT
	*
FROM Production.Product AS P
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
WHERE 
	PC.Name = 'Bikes' AND
	P.ProductID NOT IN
						(
						SELECT DISTINCT
							SOD.ProductID
						FROM Production.Product AS P
							INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
							INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
							INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
						WHERE PC.Name = 'Bikes'
						)

--d)	(6 bodova) Prikazati ukupnu prodanu količinu i ukupnu zaradu bez popusta po kategorijama proizvoda, osim bicikala. U rezultate uključiti sve proizvode koji nisu bijeli ni crna, a ukupna prodana količina im nije veća od 20000. Rezultate sortirati prema ukupnoj zaradi u opadajućem redoslijedu. (AdventureWorks2017)

SELECT
	PC.Name,
	SUM(SOD.OrderQty) AS [Ukupna prodana količina],
	SUM(SOD.OrderQty * SOD.UnitPrice) AS [Ukupna zarada bez popusta]
FROM Production.Product AS P	
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
WHERE
	PC.Name NOT IN ('Bikes') AND
	P.Color NOT IN ('White', 'Black')
GROUP BY PC.Name
HAVING SUM(SOD.OrderQty) <= 20000
ORDER BY SUM(SOD.OrderQty * SOD.UnitPrice) DESC

--e)	(4 boda) Za svakog autora čija adresa počinje sa ISKLJUČIVO 4 broja kreirati šifru po principu (Pubs):
--1.	Prezime po pravilu (prezime od 4 karaktera->uzeti prva 2 karaktera; 6 karaktera -> prva 4 karaktera; za sve ostale slučajeve uzeti zadnja 2 karaktera)
--2.	Ime po pravilu (prva 2 karaktera za ime sa početnim samoglasnikom, zadnja 2 karaktera za ime sa početnim suglasnikom) 
--3.	Karakter _
--4.	Zip po pravilu (2 karaktera sa desne strane ukoliko je zadnja cifra u opsegu 0-5; u suprotnom 2 karaktera sa lijeve strane)
--5.	Karakter /
--6.	State (obrnuta vrijednost)
--7.	Phone (brojevi između space i karaktera -)
--                  Primjer:  za autora sa id-om 409-56-7008 šifra je BennAb_05/AC658
--		    za autora sa id-om 807-91-6654 šifra je Pantelia_53/DM946		            24 bod

GO
USE pubs

SELECT
	*,
	CONCAT
	(
		CASE
			WHEN LEN(A.au_lname) = 4 THEN LEFT(A.au_lname, 2)
			WHEN LEN(A.au_lname) = 6 THEN LEFT(A.au_lname, 4)
			ELSE RIGHT(A.au_lname, 2)
		END,
		IIF
		(
			LEFT(A.au_fname, 1) IN ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'),
			LEFT(A.au_fname, 2),
			RIGHT(A.au_fname, 2)
		),
		'_',
		IIF
		(
			RIGHT(A.zip, 1) IN ('0', '2','2','3','4', '5'),
			RIGHT(A.zip, 2),
			LEFT(A.zip, 1)
		),
		'/',
		REVERSE(A.state),
		SUBSTRING(A.phone, 5, 3)
	)
FROM authors AS A
WHERE 
	A.address LIKE '[0-9][0-9][0-9][0-9]%' AND
	A.address NOT LIKE '[0-9][0-9][0-9][0-9][0-9]%'

--SQL skriptu (bila prazna ili ne) imenovati Vašim brojem indeksa npr IB200001.sql, teorijski dokument imenovan Vašim brojem indexa npr IB200001.docx upload-ovati ODVOJEDNO na ftp u folder Upload. 