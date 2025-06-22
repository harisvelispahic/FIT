--2. 										max: 12 bodova
--Baza: AdventureWorks2017
--2. a)	(6 bodova) Prikazati ukupnu vrijednost narudžbi za svakog kupca pojedinaèno. Upitom prikazati ime i prezime kupca te ukupnu vrijednost narudžbi sa i bez popusta.
--Zaglavlje (kolone): Ime i prezime, Vrijednost bez popusta (kolièina * cijena), Vrijednost sa popustom.
USE AdventureWorks2017

SELECT CONCAT(P.FirstName, ' ', P.LastName) 'Ime i prezime' --ime i prezime može i odvojeno ako se ne traži spojeno 
		, SUM(SOD.UnitPrice * SOD.OrderQty) 'Vrijednost bez popusta',
		SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)) 'Vrijednost sa popustom'
FROM Person.Person AS P
	INNER JOIN Sales.Customer AS C ON C.PersonID = P.BusinessEntityID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON SOH.CustomerID = C.CustomerID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOD.SalesOrderID = SOH.SalesOrderID
GROUP BY CONCAT(P.FirstName, ' ', P.LastName)

--2. b)	(6 bodova) Prikazati 5 proizvoda od kojih je ostvaren najveæi profit (zarada) i 5 s najmanjim profitom.
--Zaglavlje: Ime proizvoda, Zarada.
SELECT * FROM (
	SELECT TOP 5 P.Name, SUM(SOD.OrderQty * SOD.UnitPrice * (1 - SOD.UnitPriceDiscount)) 'Zarada'
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOD.ProductID = P.ProductID
	GROUP BY P.Name
	ORDER BY 2 DESC ) AS Najveci
UNION
SELECT * FROM (
	SELECT TOP 5 P.Name, SUM(SOD.OrderQty * SOD.UnitPrice * (1 - SOD.UnitPriceDiscount)) 'Zarada'
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOD.ProductID = P.ProductID
	GROUP BY P.Name
	ORDER BY 2 ) AS Najmanji
ORDER BY Najveci.Zarada DESC

--ILI

SELECT SQ.Name, SQ.Zarada FROM (
	SELECT P.Name, SUM(SOD.OrderQty * SOD.UnitPrice * (1 - SOD.UnitPriceDiscount)) 'Zarada',
			RANK() OVER(ORDER BY SUM(SOD.OrderQty * SOD.UnitPrice * (1 - SOD.UnitPriceDiscount)) DESC) 'TopRank',
			RANK() OVER(ORDER BY SUM(SOD.OrderQty * SOD.UnitPrice * (1 - SOD.UnitPriceDiscount))) 'BottomRank'
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOD.ProductID = P.ProductID
	GROUP BY P.Name ) AS SQ
WHERE (SQ.BottomRank BETWEEN 1 AND 5) OR (SQ.TopRank BETWEEN 1 AND 5)
ORDER BY SQ.Zarada DESC

--3. 										max: 23 boda
--Baza: Northwind
--3. a)	(7 bodova) Prikazati kupce koji su u sklopu jedne narudžbe naruèili proizvode iz taèno tri kategorije. (Northwind)
--Zaglavlje: ContactName.
USE Northwind

SELECT DISTINCT C.ContactName
FROM Customers AS C
	INNER JOIN Orders AS O ON O.CustomerID = C.CustomerID
	INNER JOIN [Order Details] AS OD ON OD.OrderID = O.OrderID
	INNER JOIN Products AS P ON OD.ProductID = P.ProductID
GROUP BY C.ContactName, O.OrderID
HAVING COUNT(DISTINCT P.CategoryID) = 3

--ILI

SELECT DISTINCT C.ContactName
FROM Customers AS C
	INNER JOIN Orders AS O ON O.CustomerID = C.CustomerID
WHERE O.OrderID IN (SELECT SQ1.OrderID FROM (
						SELECT SQ.OrderID, COUNT(*) 'count' FROM (
							SELECT DISTINCT OD.OrderID, P.CategoryID
							FROM [Order Details] AS OD
								INNER JOIN Products AS P ON OD.ProductID = P.ProductID
							) AS SQ
						GROUP BY SQ.OrderID
						HAVING COUNT(*) = 3
					) AS SQ1)

--3. b)	(7 bodova) Prikazati zaposlenike koji su obradili više narudžbi od zaposlenika koji ima najmanje narudžbi u njihovoj regiji (kolona Region). (Northwind) 
--Zaglavlje: Ime i prezime.
SELECT CONCAT(EMP.FirstName, ' ', EMP.LastName) 'Ime i prezime'
FROM Orders AS O
	INNER JOIN Employees AS EMP ON O.EmployeeID = EMP.EmployeeID
GROUP BY CONCAT(EMP.FirstName, ' ', EMP.LastName), EMP.Region
HAVING COUNT(*) > (SELECT MIN(SQ.[br obradenih narudzbi]) FROM (
					SELECT COUNT(*) 'br obradenih narudzbi'
					FROM Orders AS O
						INNER JOIN Employees AS E ON O.EmployeeID = E.EmployeeID
					WHERE (E.Region = EMP.Region) OR (E.Region IS NULL AND EMP.Region IS NULL) -- provjeravamo je li regija null jer ako jeste jednakost E.Region = EMP.Region æe uvijek u SELECT MIN davati krajnji rezultat NULL
					GROUP BY O.EmployeeID
				) AS SQ)

--3. c)	(9 bodova) Prikazati proizvode koje naruèuju kupci iz zemlje iz koje se najmanje kupuje. (Northwind) 
--Zaglavlje: ProductName.
SELECT DISTINCT P.ProductName
FROM Products AS P
	INNER JOIN [Order Details] AS OD ON OD.ProductID = P.ProductID
	INNER JOIN Orders AS O ON OD.OrderID = O.OrderID
	INNER JOIN Customers AS C ON O.CustomerID = C.CustomerID
WHERE C.Country = (SELECT TOP 1 C.Country
					FROM Customers AS C
						INNER JOIN Orders AS O ON O.CustomerID = C.CustomerID
					GROUP BY C.Country
					ORDER BY COUNT(*) )

--4. 										max: 20 bodova
--Baza: Pubs						
--Napomena: zadatke obavezno rješavati kao podupite (na where, having, ...) – ugnježðeni upiti
--4. a)	(10 bodova) Prikazati trgovine u kojima se mogu naæi naslovi prodani manje puta nego što je prosjeèna prodaja naslova iz godine kad je prodano najmanje naslova (Pubs).
--Zaglavlje: stor_name
USE pubs

SELECT DISTINCT ST.stor_name
FROM stores AS ST
	INNER JOIN sales AS SL ON SL.stor_id = ST.stor_id
WHERE SL.title_id IN (SELECT SL.title_id
						FROM sales AS SL
						GROUP BY SL.title_id
						HAVING SUM(SL.qty) < (SELECT AVG(S.qty) 'prosjecna prodaja'
												FROM sales AS S
												WHERE YEAR(S.ord_date) = (SELECT TOP 1 YEAR(S.ord_date) 'Godina'
																			FROM sales AS S
																			GROUP BY YEAR(S.ord_date)
																			ORDER BY SUM(S.qty) ) ) )

--4. b)	(10 bodova) Prikazati naslove starije od najbolje  prodavanog naslova kojeg je izdao izdavaè iz savezne države koja sadrži slog 'CA'.  (Pubs).
SELECT T.title
FROM titles AS T
WHERE DATEDIFF(YEAR, T.pubdate, GETDATE()) > (SELECT TOP 1 DATEDIFF(YEAR, T.pubdate, GETDATE()) 'Starost najprodavanije knjige'
												FROM publishers AS P
													INNER JOIN titles AS T ON T.pub_id = P.pub_id
													INNER JOIN sales AS S ON S.title_id = T.title_id
												WHERE P.state LIKE '%CA%'
												GROUP BY T.title, T.pubdate
												ORDER BY SUM(S.qty) DESC )

--5. 										
--Kreirati bazu podataka koju æete imenovati svojim brojem indeksa. 
CREATE DATABASE IBVasBrojIndeksa
GO
USE IBVasBrojIndeksa

--5.1. 										max: 5 bodova
--U kreiranoj bazi podataka kreirati tabele sa sljedeæom strukturom: 			
--5.1. a) Izdavaci 
--•	IzdavacID, 4 karaktera fiksne dužine i primarni kljuè, 
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

--5.1. b) Naslovi 
--•	NaslovID, 6 karaktera i primarni kljuè, 
--•	Naslov, 80 karaktera (obavezan unos), 
--•	Tip, 12 karaktera fiksne dužine (obavezan unos), 
--•	Cijena, novèani tip podataka,   
--•	IzdavacID, 4 karaktera fiksne dužine, strani kljuè 

CREATE TABLE Naslovi
(
	NaslovID VARCHAR(6) CONSTRAINT PK_Naslovi PRIMARY KEY,
	Naslov VARCHAR(80) NOT NULL,
	Tip CHAR(12) NOT NULL,
	Cijena MONEY,
	IzdavacID CHAR(4) CONSTRAINT FK_Naslovi_Izdavaci FOREIGN KEY REFERENCES Izdavaci(IzdavacID)
)

--5.1. d)	Prodavnice 
--•	ProdavnicaID, 4 karaktera fiksne dužine i primarni kljuè, 
--•	NazivProdavnice, 40 karaktera, 
--•	Grad, 40 karaktera 

--prvo kreiramo tabelu Prodavnice jer tabela Prodaja ima strani kljuè koji se referencira na PK od Prodavnice
CREATE TABLE Prodavnice
(
	ProdavnicaID CHAR(4) CONSTRAINT PK_Prodavnice PRIMARY KEY,
	NazivProdavnice VARCHAR(40),
	Grad VARCHAR(40)
)

--5.1. c) Prodaja  
--•	ProdavnicaID, 4 karaktera fiksne dužine, strani i primarni kljuè, 
--•	BrojNarudzbe, 20 karaktera, primarni kljuè, 
--•	NaslovID, 6 karaktera, strani i primarni kljuè, 
--•	DatumNarudzbe, polje za unos datuma i vremena (obavezan unos), 
--•	Kolicina, skraæeni cjelobrojni tip (obavezan unos, dozvoljen unos brojeva veæih od 0

CREATE TABLE Prodaja
(
	ProdavnicaID CHAR(4) CONSTRAINT FK_Prodaja_Prodavnice FOREIGN KEY REFERENCES Prodavnice(ProdavnicaID),
	BrojNarudzbe VARCHAR(20),
	NaslovID VARCHAR(6) CONSTRAINT FK_Prodaja_Naslovi FOREIGN KEY REFERENCES Naslovi(NaslovID),
	DatumNarudzbe DATETIME NOT NULL,
	Kolicina SMALLINT NOT NULL CONSTRAINT CHK_Prodaja_Kolicina CHECK(Kolicina > 0),
	CONSTRAINT PK_Prodaja PRIMARY KEY(ProdavnicaID, BrojNarudzbe, NaslovID)
)

--5.2. 										max: 5 bodova
--U kreiranu bazu kopirati podatke iz baze Pubs: 		
--5.2. a)	U tabelu Izdavaci dodati sve izdavaèe 
--•	pub_id -> IzdavacID; pub_name -> NazivIzdavaca; country -> Drzava; Logo -> Logo 
INSERT INTO Izdavaci
SELECT P.pub_id, P.pub_name, P.country, PI.logo
FROM pubs.dbo.publishers AS P
	INNER JOIN pubs.dbo.pub_info AS PI ON PI.pub_id = P.pub_id

SELECT * FROM Izdavaci

--5.2. b)	U tabelu Naslovi dodati sve naslove, na mjestima gdje nema pohranjenih podataka o cijeni zamijeniti vrijednost sa 0 
--•	title_id -> NaslovID; title -> Naslov; type -> Tip; price -> Cijena; pub_id -> IzdavacID 
INSERT INTO Naslovi
SELECT T.title_id, T.title, T.type, ISNULL(T.price, 0), T.pub_id
FROM pubs.dbo.titles AS T

SELECT * FROM Naslovi

--5.2. d)	U tabelu Prodavnice dodati sve prodavnice 
--•	stor_id -> ProdavnicaID; store_name -> NazivProdavnice; city -> Grad 
INSERT INTO Prodavnice
SELECT S.stor_id, S.stor_name, S.city
FROM pubs.dbo.stores AS S
--Izvršavamo insert u Prodavnice prije Prodaje zbog ogranièenja stranog kljuèa

SELECT * FROM Prodavnice

--5.2. c)	U tabelu Prodaja dodati sve stavke iz tabele prodaja 
--•	stor_id -> ProdavnicaID; order_num -> BrojNarudzbe; title_id -> NaslovID; ord_date -> DatumNarudzbe; qty -> Kolicina 
INSERT INTO Prodaja
SELECT S.stor_id, S.ord_num, S.title_id, S.ord_date, S.qty
FROM pubs.dbo.sales AS S

SELECT * FROM Prodaja

--5.3. 										max: 15 bodova
--5.3. a)	(5 bodova) Kreirati pogled v_prodaja kojim æe se prikazati statistika prodaje knjiga po izdavaèima. Prikazati naziv te državu iz koje izdavaèi dolaze, ukupan broj napisanih naslova, te ukupnu prodanu kolièinu. Rezultate sortirati po ukupnoj prodanoj kolièini u opadajuæem redoslijedu. (Novokreirana baza) 
GO
CREATE VIEW v_prodaja
AS
SELECT I.NazivIzdavaca, I.Drzava, (SELECT COUNT(*)
									FROM Naslovi AS NSQ
									WHERE NSQ.IzdavacID = I.IzdavacID
									) 'BrojNapisanihNaslova',
								SUM(P.Kolicina) 'ProdanaKolicina'
FROM Prodaja AS P
	INNER JOIN Naslovi AS N ON P.NaslovID = N.NaslovID
	INNER JOIN Izdavaci AS I ON N.IzdavacID = I.IzdavacID
GROUP BY I.NazivIzdavaca, I.Drzava, I.IzdavacID
GO

SELECT *
FROM v_prodaja AS VP
ORDER BY VP.ProdanaKolicina DESC

--5.3. b)	(2 boda) U novokreiranu bazu iz baze Northwind dodati tabelu Employees. Prilikom kreiranja izvršiti automatsko instertovanje podataka. 
SELECT *
INTO Employees
FROM Northwind.dbo.Employees

--5.3. c)	(5 boda) Kreirati funkciju f_4b koja æe vraæati podatke u formi tabele na osnovu proslijedjenih parametra od i do, cjelobrojni tip. Funkcija æe vraæati one zapise u kojima se godine radnog staža nalaze u intervalu od-do. Potrebno je da se prilikom kreiranja funkcije u rezultatu nalaze sve kolone tabele uposlenici, zajedno sa izraèunatim godinama radnog staža. OBAVEZNO provjeriti ispravnost funkcije unošenjem kontrolnih vrijednosti. (Novokreirana baza) 
GO
CREATE FUNCTION f_4b
(
	@od INT,
	@do INT
)
RETURNS TABLE
AS
RETURN
	SELECT DATEDIFF(YEAR, E.HireDate, GETDATE()) 'Radni staž', *
	FROM Employees AS E
	WHERE DATEDIFF(YEAR, E.HireDate, GETDATE()) BETWEEN @od AND @do
GO

SELECT *
FROM dbo.f_4b(32,33)

--5.3. d)	(3 bodova) Kreirati proceduru sp_Prodavnice_insert kojom æe se izvršiti insertovanje podataka unutar tabele prodavnice. OBAVEZNO kreirati testni sluèaj. (Novokreirana baza) 
GO
CREATE PROCEDURE sp_Prodavnice_insert
(
	@ProdavnicaID CHAR(4),
	@NazivProdavnice VARCHAR(40) = NULL,
	@Grad VARCHAR(40) = NULL
)
AS
BEGIN
	INSERT INTO Prodavnice
	VALUES(@ProdavnicaID, @NazivProdavnice, @Grad)
END
GO

EXEC sp_Prodavnice_insert 'LIDL', 'Lidl', 'Mostar'
EXEC sp_Prodavnice_insert @ProdavnicaID = 'IVAN', @NazivProdavnice = 'Ivo Andric'

SELECT * FROM Prodavnice