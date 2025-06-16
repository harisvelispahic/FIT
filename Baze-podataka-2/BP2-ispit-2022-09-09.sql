--1 Kreirati bazu za svojim brojm indeksa

GO
CREATE DATABASE [2022-09-09]
GO
USE [2022-09-09]

--2 U kreiranoj bazi podataka kreirati tabele slijedecom strukturom
--a)	Uposlenici
--•	UposlenikID, 9 karaktera fiksne duzine i primarni kljuc,
--•	Ime 20 karaktera obavezan unos,
--•	Prezime 20 karaktera obavezan unos
--•	DatumZaposlenja polje za unos datuma i vremena obavezan unos
--•	Opis posla 50 karaktera obavezan unos

CREATE TABLE Uposlenici
(
	UposlenikID NCHAR(9) CONSTRAINT PK_Uposlenici PRIMARY KEY,
	Ime NVARCHAR(20) NOT NULL,
	Prezime NVARCHAR(20) NOT NULL,
	DatumZaposlenja DATETIME NOT NULL,
	OpisPosla NVARCHAR(50) NOT NULL
)

--b)	Naslovi
--•	NaslovID 6 karaktera primarni kljuc,
--•	Naslov 80 karaktera obavezan unos,
--•	Tip 12 karaktera fiksne duzine obavezan unos
--•	Cijena novcani tip podatka,
--•	NazivIzdavaca 40 karaktera,
--•	GradIzdavaca 20 karaktera,
--•	DrzavaIzdavaca 30 karaktera

CREATE TABLE Naslovi
(
	NaslovID NVARCHAR(6) CONSTRAINT PK_Naslovi PRIMARY KEY,
	Naslov NVARCHAR(80) NOT NULL,
	Tip NCHAR(12) NOT NULL,
	Cijena MONEY,
	NazivIzdavaca NVARCHAR(40),
	GradIzdavaca NVARCHAR(20),
	DrzavaIzdavaca NVARCHAR(30)
)

--c)	Prodaja
--•	ProdavnicaID 4 karktera fiksne duzine, strani i primarni kljuc
--•	Broj narudzbe 20 karaktera primarni kljuc,
--•	NaslovID 6 karaktera strani i primarni kljuc
--•	DatumNarudzbe polje za unos datuma i vremena obavezan unos
--•	Kolicina skraceni cjelobrojni tip obavezan unos

CREATE TABLE Prodaja
(
	ProdavnicaID NCHAR(4) CONSTRAINT FK_Prodaja_Prodavnice FOREIGN KEY REFERENCES Prodavnice(ProdavnicaID),
	BrojNarudzbe NVARCHAR(20),
	NaslovID NVARCHAR(6) CONSTRAINT FK_Prodaja_Naslovi FOREIGN KEY REFERENCES Naslovi(NaslovID),
	DatumNarudzbe DATETIME NOT NULL,
	Kolicina SMALLINT NOT NULL,

	CONSTRAINT PK_Prodaja PRIMARY KEY(ProdavnicaID, BrojNarudzbe, NaslovID)
)

--d)	Prodavnice
--•	ProdavnicaID 4 karaktera fiksne duzine primarni kljuc
--•	NazivProdavnice 40 karaktera
--•	Grad 40 karaktera

CREATE TABLE Prodavnice
(
	ProdavnicaID NCHAR(4) CONSTRAINT PK_Prodavnice PRIMARY KEY,
	NazivProdavnice NVARCHAR(40),
	Grad NVARCHAR(40)
)

--3 Iz baze podataka pubs u svoju bazu prebaciti slijedece podatke
--a)	U tabelu Uposlenici dodati sve uposlenike
--•	emp_id -> UposlenikID
--•	fname -> Ime
--•	lname -> Prezime
--•	hire_date - > DatumZaposlenja
--•	job_desc - > Opis posla

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

--b)	U tabelu naslovi dodati sve naslove, na mjestu gdje nema pohranjenih podataka o nazivima izdavaca zamijeniti vrijednost sa nepoznat izdavac
--•	Title_id -> NaslovID
--•	Title->Naslov
--•	Type->Tip
--•	Price->Cijena
--•	Pub_name->NazivIzdavaca
--•	City->GradIzdavaca
--•	Country-DrzavaIzdavaca

INSERT INTO Naslovi
(
	NaslovID,
	Naslov,
	Tip,
	Cijena,
	NazivIzdavaca,
	GradIzdavaca,
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


--c)	U tabelu prodaja dodati sve stavke iz tabele prodaja
--•	Stor_id->ProdavnicaID
--•	Order_num->BrojNarudzbe
--•	titleID->NaslovID,
--•	ord_date->DatumNarudzbe
--•	qty->Kolicina

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

--d)	U tabelu prodavnice dodati sve prodavnice
--•	Stor_id->prodavnicaID
--•	Store_name->NazivProdavnice
--•	City->Grad

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

--4
--a)	Kreirati proceduru sp_delete_uposlenik kojom ce se obrisati odredjeni zapis iz tabele uposlenici. OBAVEZNO kreirati testni slucaj na kreiranu proceduru

GO
CREATE OR ALTER PROCEDURE sp_delete_uposlenik
(
	@UposlenikID NCHAR(9)
)
AS
BEGIN
	DELETE FROM Uposlenici
	WHERE UposlenikID = @UposlenikID
END
GO

SELECT * FROM Uposlenici

exec sp_delete_uposlenik @UposlenikID = 'Y-L77953M'

--b)	Kreirati tabelu Uposlenici_log slijedeca struktura
--Uposlenici_log
--•	UposlenikID 9 karaktera fiksne duzine
--•	Ime 20 karaktera
--•	Prezime 20 karakera,
--•	DatumZaposlenja polje za unos datuma i vremena
--•	Opis posla 50 karaktera

CREATE TABLE Uposlenici_log
(
	UposlenikID NCHAR(9),
	Ime NVARCHAR(20),
	Prezime NVARCHAR(20),
	DatumZaposlenja DATETIME,
	OpisPosla NVARCHAR(50)
)

--c)	Nad tabelom uposlenici kreirati okidac t_ins_Uposlenici koji ce prilikom brisanja podataka iz tabele Uposlenici izvristi insert podataka u tabelu Uposlenici_log. OBAVEZNO kreirati tesni slucaj

GO
CREATE OR ALTER TRIGGER t_ins_Uposlenici
ON Uposlenici
AFTER DELETE
AS
BEGIN
	INSERT INTO Uposlenici_log
	(
		UposlenikID,
		Ime,
		Prezime,
		DatumZaposlenja,
		OpisPosla
	)
	SELECT
		D.UposlenikID,
		D.Ime,
		D.Prezime,
		D.DatumZaposlenja,
		D.OpisPosla
	FROM deleted AS D
END
GO

SELECT * FROM Uposlenici
SELECT * FROM Uposlenici_log

DELETE FROM Uposlenici WHERE UposlenikID = 'VPA30890F'

--d)	Prikazati sve uposlenike zenskog pola koji imaju vise od 10 godina radnog staza, a rade na Production ili Marketing odjelu. Upitom je potrebno pokazati spojeno ime i prezime uposlenika, godine radnog staza, te odjel na kojem rade uposlenici. Rezultate upita sortirati u rastucem redoslijedu prema nazivu odjela,- te -opadajucem prema godinama radnog staza (AdventureWorks2019)

GO
USE AdventureWorks2017


SELECT 
	CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
	DATEDIFF(YEAR, EDH.StartDate, GETDATE()) AS [Godine radnog staza],
	D.Name
FROM HumanResources.EmployeeDepartmentHistory AS EDH
	INNER JOIN HumanResources.Department AS D ON EDH.DepartmentID = D.DepartmentID
	INNER JOIN HumanResources.Employee AS E ON EDH.BusinessEntityID = E.BusinessEntityID
	INNER JOIN Person.Person AS P ON E.BusinessEntityID = P.BusinessEntityID
WHERE 
	((DATEDIFF(YEAR, EDH.StartDate, GETDATE()) > 10 AND EDH.EndDate IS NULL) OR DATEDIFF(YEAR, EDH.StartDate, EDH.EndDate) > 10) AND
	D.Name IN ('Production', 'Marketing') AND
	E.Gender = 'F'
ORDER BY D.Name ASC, [Godine radnog staza] DESC

--e)	Kreirati upit kojim ce se prikazati koliko ukupno je naruceno komada proizvoda za svaku narudzbu pojedinacno, te ukupnu vrijednost narudzbe sa i bez popusta. Uzeti u obzir samo one narudzbe kojima je datum narudzbe do datuma isporuke proteklo manje od 7 dana (ukljuciti granicnu vrijednost), a isporucene su kupcima koji zive na podrucju Madrida, Minhena, Seatle. Rezultate upita sortirati po broju komada u opadajucem redoslijedu, a vrijednost je potrebno zaokruziti na dvije decimale (Northwind)

GO
USE Northwind


SELECT
	O.OrderID,
	SUM(OD.Quantity) AS Kolicina,
	CAST(SUM(OD.Quantity * OD.UnitPrice) AS decimal(18, 2)) AS [Vrijednost bez popusta],
	CAST(SUM(OD.Quantity * OD.UnitPrice * (1 - OD.Discount)) AS decimal(18, 2)) AS [Vrijednost sa popustom]
FROM Customers AS C
	INNER JOIN Orders AS O ON C.CustomerID = O.CustomerID
	INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
WHERE 
	DATEDIFF(DAY, O.OrderDate, O.ShippedDate) <= 7 AND
	C.City IN ('Madrid', 'München', 'Seattle')
GROUP BY O.OrderID
ORDER BY 2 DESC

--f)	Napisati upit kojim ce se prikazati brojNarudzbe, datumNarudzbe i sifra. Prikazati samo one zapise iz tabele Prodaja ciji broj narudzbe ISKLJUCIVO POCINJE jednim slovom, ili zavrsava jednim slovom (Novokreirana baza)
--Sifra se sastoji od slijedecih vrijednosti:
--•	Brojevi (samo brojevi) uzeti iz broja narudzbi,
--•	Karakter /
--•	Zadnja dva karaktera godine narudbze /
--•	Karakter /
--•	Id naslova
--•	Karakter /
--•	Id prodavnice
--Za broj narudzbe 772a sifra je 722/19/PS2091/6380
--Za broj narudzbe N914008 sifra je 914008/19/PS2901/6380

GO
USE [2022-09-09]


SELECT
	*,
	P.BrojNarudzbe,
	P.DatumNarudzbe,
	CONCAT
	(
	CASE
		WHEN 
			(P.BrojNarudzbe LIKE '[A-Za-z]%' AND P.BrojNarudzbe NOT LIKE '[A-Za-z][A-Za-z]%') AND
			(P.BrojNarudzbe LIKE '%[A-Za-z]' AND P.BrojNarudzbe NOT LIKE '%[A-Za-z][A-Za-z]')
		THEN SUBSTRING(P.BrojNarudzbe, PATINDEX('%[0-9]%', P.BrojNarudzbe), LEN(P.BrojNarudzbe) - PATINDEX('%[A-Za-z]%', REVERSE(P.BrojNarudzbe)) - 1)
		
		WHEN P.BrojNarudzbe LIKE '[A-Za-z]%' AND P.BrojNarudzbe NOT LIKE '[A-Za-z][A-Za-z]%'
		THEN SUBSTRING(P.BrojNarudzbe, PATINDEX('%[0-9]%', P.BrojNarudzbe), LEN(P.BrojNarudzbe) - PATINDEX('%[0-9]%', P.BrojNarudzbe) + 1)

		WHEN P.BrojNarudzbe LIKE '%[A-Za-z]' AND P.BrojNarudzbe NOT LIKE '%[A-Za-z][A-Za-z]'
		THEN SUBSTRING(P.BrojNarudzbe, 0, LEN(P.BrojNarudzbe) - PATINDEX('%[0-9]%', P.BrojNarudzbe) + 1)

	END,
	'/',
	LEFT(CAST(YEAR(P.DatumNarudzbe) AS CHAR(4)), 2),
	'/',
	P.NaslovID,
	'/',
	CAST(P.ProdavnicaID AS CHAR(4))
	) AS Sifra
FROM Prodaja AS P
WHERE 
	(P.BrojNarudzbe LIKE '[A-Za-z]%' AND P.BrojNarudzbe NOT LIKE '[A-Za-z][A-Za-z]%') OR
	(P.BrojNarudzbe LIKE '%[A-Za-z]' AND P.BrojNarudzbe NOT LIKE '%[A-Za-z][A-Za-z]')


--5
--a)	Prikazati nazive odjela gdje radi najmanje odnosno najvise uposlenika (AdventureWorks2019)

GO
USE AdventureWorks2017


SELECT *
FROM
	(
	SELECT TOP 1
		D.Name AS [Najmanje uposlenika]
	FROM HumanResources.EmployeeDepartmentHistory AS EDH
		INNER JOIN HumanResources.Department AS D ON EDH.DepartmentID = D.DepartmentID
	GROUP BY D.Name
	ORDER BY COUNT(*) ASC
	) AS SQ1
CROSS JOIN
	(
	SELECT TOP 1
		D.Name AS [Najvise uposlenika]
	FROM HumanResources.EmployeeDepartmentHistory AS EDH
		INNER JOIN HumanResources.Department AS D ON EDH.DepartmentID = D.DepartmentID
	GROUP BY D.Name
	ORDER BY COUNT(*) DESC
	) AS SQ2

--b)	Prikazati spojeno ime i prezime osobe, spol, ukupnu vrijednost redovnih bruto prihoda, ukupnu vrijednost vanrednih prihoda, te sumu ukupnih vandrednih prihoda i ukupnih redovnih prihoda. Uslov je da dolaze iz Latvije, Kine ili Indonezije a poslodavac kod kojeg rade je registrovan kao javno ustanova (Prihodi)

GO
USE prihodi


SELECT
	CONCAT(O.Ime, ' ', O.PrezIme) AS [Ime i prezime],
	O.Spol,
	SUM(RP.Bruto) AS [Ukupna vrijednost redovnih bruto prihoda],
	SUM(VP.IznosVanrednogPrihoda) AS [Ukupna vrijednost vanrednih prihoda],
	SUM(RP.Bruto) + SUM(VP.IznosVanrednogPrihoda) AS [Suma ukupnih vandrednih prihoda i ukupnih redovnih prihoda]
FROM Osoba AS O
	INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
	INNER JOIN VanredniPrihodi AS VP ON O.OsobaID = VP.OsobaID
	INNER JOIN Drzava AS D ON O.DrzavaID = D.DrzavaID
	INNER JOIN Poslodavac AS P ON O.PoslodavacID = P.PoslodavacID
	INNER JOIN TipPoslodavca AS TP ON P.TipPoslodavca = TP.TipPoslodavcaID
WHERE 
	CONCAT(O.Ime, ' ', O.PrezIme) <> ' ' AND
	D.Drzava IN ('Latvia', 'China', 'Indonesia') AND
	TP.OblikVlasnistva = 'javno ustanova'
GROUP BY O.Ime, O.PrezIme, O.Spol

--c)	Modificirati prethodni upit 5_b na nacin da se prikazu samo oni zapisi kod kojih je suma ukupnih bruto i ukupnih vanderednih prihoda (SumaBruto + SumaNeto) veca od 10000KM. Retultate upita sortirati prema ukupnoj vrijednosti prihoda obrnuto abecedno(Prihodi)

SELECT
	CONCAT(O.Ime, ' ', O.PrezIme) AS [Ime i prezime],
	O.Spol,
	SUM(RP.Bruto) AS [Ukupna vrijednost redovnih bruto prihoda],
	SUM(VP.IznosVanrednogPrihoda) AS [Ukupna vrijednost vanrednih prihoda],
	SUM(RP.Bruto) + SUM(VP.IznosVanrednogPrihoda) AS [Suma ukupnih vandrednih prihoda i ukupnih redovnih prihoda]
FROM Osoba AS O
	INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
	INNER JOIN VanredniPrihodi AS VP ON O.OsobaID = VP.OsobaID
	INNER JOIN Drzava AS D ON O.DrzavaID = D.DrzavaID
	INNER JOIN Poslodavac AS P ON O.PoslodavacID = P.PoslodavacID
	INNER JOIN TipPoslodavca AS TP ON P.TipPoslodavca = TP.TipPoslodavcaID
WHERE 
	CONCAT(O.Ime, ' ', O.PrezIme) <> ' ' AND
	D.Drzava IN ('Latvia', 'China', 'Indonesia') AND
	TP.OblikVlasnistva = 'javno ustanova'
GROUP BY O.Ime, O.PrezIme, O.Spol
HAVING SUM(RP.Bruto) + SUM(VP.IznosVanrednogPrihoda) > 10000
ORDER BY 5 DESC