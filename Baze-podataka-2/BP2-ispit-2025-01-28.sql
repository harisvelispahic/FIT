--2. 										max: 12 bodova
--Baza: AdventureWorks2017
--a)	(6 bodova) Prikazati ukupnu vrijednost narudžbi za svakog kupca pojedinačno. Upitom prikazati ime i prezime kupca te ukupnu vrijednost narudžbi sa i bez popusta.
--Zaglavlje (kolone): Ime i prezime, Vrijednost bez popusta (količina * cijena), Vrijednost sa popustom.

GO
USE AdventureWorks2017

SELECT
	CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
	SUM(SOD.UnitPrice * SOD.OrderQty) AS [Bez popusta],
	SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)) AS [Sa popustom]
FROM Person.Person AS P	
	INNER JOIN Sales.Customer AS C ON P.BusinessEntityID = C.PersonID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
GROUP BY P.FirstName, P.LastName

--b)	(6 bodova) Prikazati 5 proizvoda od kojih je ostvaren najveći profit (zarada) i 5 s najmanjim profitom. Zaglavlje: Ime proizvoda, Zarada.

SELECT *
FROM
	(
	SELECT TOP 5
		P.Name,
		SUM(SOD.OrderQty * SOD.UnitPrice * (1 - SOD.UnitPriceDiscount)) AS Zarada
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
	GROUP BY P.Name
	ORDER BY 2 DESC
	) AS SUBQ1

UNION

SELECT *
FROM
	(
	SELECT TOP 5
		P.Name,
		SUM(SOD.OrderQty * SOD.UnitPrice * (1 - SOD.UnitPriceDiscount)) AS Zarada
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
	GROUP BY P.Name
	ORDER BY 2 ASC
	) SUBQ2

-- 3. 										max: 23 boda
--Baza: Northwind
--a)	(7 bodova) Prikazati kupce koji su u sklopu jedne narudžbe naručili proizvode iz tačno tri kategorije. (Northwind)
--Zaglavlje: ContactName.

GO
USE Northwind

SELECT
	C.ContactName
FROM Customers AS C
	INNER JOIN Orders AS O ON C.CustomerID = O.CustomerID
	INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
	INNER JOIN Products AS P ON OD.ProductID = P.ProductID
GROUP BY C.ContactName
HAVING COUNT(DISTINCT P.CategoryID) = 3

--b)	(7 bodova) Prikazati zaposlenike koji su obradili više narudžbi od zaposlenika koji ima najmanje narudžbi u njihovoj regiji (kolona Region u tabeli Employees). (Northwind) 
--Zaglavlje: Ime i prezime.

SELECT
	CONCAT(E.FirstName, ' ', E.LastName) AS [Ime i prezime]
FROM employees AS E
	INNER JOIN
	(
	SELECT
		SviUposlenici.EmployeeID
	FROM
		(
		SELECT
			E.EmployeeID,
			E.Region,
			COUNT(*) AS Obrađeno
		FROM employees AS E
			INNER JOIN Orders AS O ON E.EmployeeID = O.EmployeeID
		GROUP BY E.EmployeeID, E.Region
		) AS SviUposlenici
		INNER JOIN
		(
		SELECT
			SUBQ1.EmployeeID,
			SUBQ1.Region,
			SUBQ1.Obrađeno
		FROM
			(
			SELECT
				E.EmployeeID,
				E.Region,
				COUNT(*) AS Obrađeno,
				ROW_NUMBER() OVER (PARTITION BY E.Region ORDER BY COUNT(*)) AS rb
			FROM Employees AS E
				INNER JOIN Orders AS O ON E.EmployeeID = O.EmployeeID
			GROUP BY E.EmployeeID, E.Region
			) AS SUBQ1
		WHERE rb = 1
		) AS RangiraniUposlenici ON (SviUposlenici.Region = RangiraniUposlenici.Region OR SviUposlenici.Region IS NULL) AND SviUposlenici.Obrađeno > RangiraniUposlenici.Obrađeno
	) AS SUBQ ON E.EmployeeID = SUBQ.EmployeeID


--c)	(9 bodova) Prikazati proizvode koje naručuju kupci iz zemlje iz koje se najmanje kupuje. (Northwind)
--Zaglavlje: ProductName.

SELECT DISTINCT
	P.ProductName
FROM Customers AS C
	INNER JOIN Orders AS O ON C.CustomerID = O.CustomerID
	INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
	INNER JOIN Products AS P ON OD.ProductID = P.ProductID
WHERE C.Country =
					(
					SELECT TOP 1
						O.ShipCountry
					FROM Orders AS O
						INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
					GROUP BY O.ShipCountry
					ORDER BY SUM(OD.Quantity) ASC
					)

--4. 										max: 20 bodova
--Baza: Pubs						
--a)	(10 bodova) Prikazati trgovine u kojima se mogu naći naslovi prodani manje puta nego što je prosječna prodaja naslova iz godine kad je prodano najmanje naslova (Pubs).
--Zaglavlje: stor_name

--		1. Godina kad je prodano najmanje naslova
--		2. Prosjecna prodaja u toj godini
--		3. Naslovi prodavani manje puta od 2. koraka
--		4. Trgovine gdje se prodaju ti naslovi

GO
USE pubs

SELECT
	ST.stor_name
FROM stores AS ST
	INNER JOIN sales AS SA ON ST.stor_id = SA.stor_id
WHERE SA.title_id IN	(
						SELECT
							T.title_id
						FROM titles AS T
							INNER JOIN sales AS S ON T.title_id = S.title_id
						GROUP BY T.title_id
						HAVING SUM(S.qty) < (
											SELECT
												AVG(S.qty)
											FROM sales AS S
												INNER JOIN titles AS T ON S.title_id = T.title_id
											WHERE YEAR(S.ord_date) = 
																	(
																	SELECT TOP 1
																		YEAR(S.ord_date)
																	FROM sales AS S
																	GROUP BY YEAR(S.ord_date)
																	ORDER BY COUNT(*) ASC
																	) -- Godina
											) -- Prosjek
						) -- Naslovi
GROUP BY ST.stor_name

--b)	(10 bodova) Prikazati naslove starije od najbolje prodavanog naslova kojeg je izdao izdavač iz savezne države koja sadrži slog 'CA'.  (Pubs).
--Zaglavlje: title(naslov knjige)
--Napomena: zadatke obavezno rješavati kao podupite (na where, having, ...) – ugnježđeni upiti
 
 --	1. Najbolje prodavani naslov izdavaca iz 'CA' drzave
 -- 2. Naslovi stariji od njega

SELECT
	T.title
FROM titles AS T
WHERE T.pubdate <	(
					SELECT TOP 1
						S.ord_date
					FROM authors AS A
						INNER JOIN titleauthor AS TA ON A.au_id = TA.au_id
						INNER JOIN titles AS T ON TA.title_id = T.title_id
						INNER JOIN sales AS S ON T.title_id = S.title_id
					WHERE LOWER(A.state) LIKE '%ca%'
					GROUP BY T.title_id, S.ord_date
					ORDER BY SUM(S.qty) DESC
					)

--5. 										
--Kreirati bazu podataka koju ćete imenovati svojim brojem indeksa. 

GO
CREATE DATABASE [2025-01-28]
GO
USE [2025-01-28]

--5.1. 										max: 5 bodova
--U kreiranoj bazi podataka kreirati tabele sa sljedećom strukturom: 

--a) Izdavaci 
--•	IzdavacID, 4 karaktera fiksne dužine i primarni ključ, 
--•	NazivIzdavaca, 40 karaktera, (zadana vrijednost „nepoznat izdavac“) 
--•	Drzava, 30 karaktera, 
--•	Logo, fotografija  

CREATE TABLE Izdavaci
(
	IzdavacID		NCHAR(4)		CONSTRAINT PK_Izdavaci PRIMARY KEY,
	NazivIzdavaca	NVARCHAR(40)	DEFAULT('nepoznat izdavac'),
	Drzava			NVARCHAR(30),
	Logo			IMAGE
)

--b) Naslovi 
--•	NaslovID, 6 karaktera i primarni ključ, 
--•	Naslov, 80 karaktera (obavezan unos), 
--•	Tip, 12 karaktera fiksne dužine (obavezan unos), 
--•	Cijena, novčani tip podataka,   
--•	IzdavacID, 4 karaktera fiksne dužine, strani ključ 

CREATE TABLE Naslovi
(
	NaslovID	NVARCHAR(6)		CONSTRAINT PK_Naslovi PRIMARY KEY,
	Naslov		NVARCHAR(80)	NOT NULL,
	Tip			NCHAR(12)		NOT NULL,
	Cijena		MONEY,
	IzdavacID	NCHAR(4)		CONSTRAINT FK_NasloviIzdavaci FOREIGN KEY REFERENCES Izdavaci(IzdavacID)
)

--c) Prodaja  
--•	ProdavnicaID, 4 karaktera fiksne dužine, strani i primarni ključ, 
--•	BrojNarudzbe, 20 karaktera, primarni ključ, 
--•	NaslovID, 6 karaktera, strani i primarni ključ, 
--•	DatumNarudzbe, polje za unos datuma i vremena (obavezan unos), 
--•	Kolicina, skraćeni cjelobrojni tip (obavezan unos, dozvoljen unos brojeva većih od 0

CREATE TABLE Prodaja
(
	ProdavnicaID	NCHAR(4)		CONSTRAINT FK_ProdajaProdavnice FOREIGN KEY REFERENCES Prodavnice(ProdavnicaID),
	BrojNarudzbe	NVARCHAR(20),
	NaslovID		NVARCHAR(6)		CONSTRAINT FK_ProdajaNaslovi FOREIGN KEY REFERENCES Naslovi(NaslovID),
	DatumNarudzbe	DATETIME		NOT NULL,
	Kolicina		SMALLINT		NOT NULL CONSTRAINT KolicinaVecaOdNule CHECK(Kolicina >= 0),

	CONSTRAINT PK_Prodaja PRIMARY KEY (ProdavnicaID, BrojNarudzbe, NaslovID)
)

--d)	Prodavnice 
--•	ProdavnicaID, 4 karaktera fiksne dužine i primarni ključ, 
--•	NazivProdavnice, 40 karaktera, 
--•	Grad, 40 karaktera 

CREATE TABLE Prodavnice
(
	ProdavnicaID		NCHAR(4)		PRIMARY KEY,
	NazivProdavnice		NVARCHAR(40),
	Grad				NVARCHAR(40)
)


--5.2. 										max: 5 bodova
--U kreiranu bazu kopirati podatke iz baze Pubs: 		
--a)	U tabelu Izdavaci dodati sve izdavače 
--•	pub_id -> IzdavacID; 
--•	pub_name -> NazivIzdavaca; 
--•	country -> Drzava; 
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
	PINFO.logo
FROM pubs.dbo.publishers AS P
	INNER JOIN pubs.dbo.pub_info AS PINFO ON P.pub_id = PINFO.pub_id

--b)	U tabelu Naslovi dodati sve naslove, na mjestima gdje nema pohranjenih podataka o cijeni zamijeniti vrijednost sa 0 
--•	title_id -> NaslovID; 
--•	title -> Naslov; 
--•	type -> Tip; 
--•	price -> Cijena; 
--•	pub_id -> IzdavacID 

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
--•	stor_id -> ProdavnicaID; 
--•order_num -> BrojNarudzbe; 
--•title_id -> NaslovID; 
--•ord_date -> DatumNarudzbe; 
--•qty -> Kolicina 

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
--•	stor_id -> ProdavnicaID; 
--• store_name -> NazivProdavnice; 
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
 
--5.3. 										max: 15 bodova
--a)	(5 bodova) Kreirati pogled v_prodaja kojim će se prikazati statistika prodaje knjiga po izdavačima. Prikazati naziv te državu iz koje izdavači dolaze, ukupan broj napisanih naslova, te ukupnu prodanu količinu. Rezultate sortirati po ukupnoj prodanoj količini u opadajućem redoslijedu. (Novokreirana baza) 

GO
CREATE OR ALTER VIEW v_prodaja
AS
	SELECT TOP 100 PERCENT
		I.NazivIzdavaca,
		I.Drzava,
		COUNT(*) AS [Ukupan broj napisanih naslova],
		ProdaneKolicine.[Ukupna prodana količina]
	FROM Izdavaci AS I
		INNER JOIN Naslovi AS N ON I.IzdavacID = N.IzdavacID
		INNER JOIN 
			(
			SELECT
				I.IzdavacID,
				SUM(P.Kolicina) AS [Ukupna prodana količina]
			FROM Izdavaci AS I
				INNER JOIN Naslovi AS N ON I.IzdavacID = N.IzdavacID
				INNER JOIN Prodaja AS P ON N.NaslovID = P.NaslovID
			GROUP BY I.IzdavacID
			) AS ProdaneKolicine ON I.IzdavacID = ProdaneKolicine.IzdavacID
	GROUP BY I.IzdavacID, I.NazivIzdavaca, I.Drzava, ProdaneKolicine.[Ukupna prodana količina]
	ORDER BY 4 DESC
GO

-- može se koristiti ovaj pattern, gdje imamo n-deep subquery i n+1-deep subquery iz kojeg moramo vaditi informacije
-- npr ovdje ne možemo prebrojavati u istom query-ju gdje sumiramo, tako da možemo joinovati ove rezultate po zajedničkom id-u i na taj način izvući potrebne informacije

SELECT * FROM v_prodaja

--b)	(2 boda) U novokreiranu bazu iz baze Northwind dodati tabelu Employees. Prilikom kreiranja izvršiti automatsko instertovanje podataka. 

SELECT * 
INTO Employees
FROM Northwind.dbo.Employees

SELECT * FROM Employees

--c)	(5 boda) Kreirati funkciju f_4b koja će vraćati podatke u formi tabele na osnovu proslijedjenih parametra od i do, cjelobrojni tip. Funkcija će vraćati one zapise u kojima se godine radnog staža nalaze u intervalu od-do. Potrebno je da se prilikom kreiranja funkcije u rezultatu nalaze sve kolone tabele uposlenici, zajedno sa izračunatim godinama radnog staža. OBAVEZNO provjeriti ispravnost funkcije unošenjem kontrolnih vrijednosti. (Novokreirana baza) 

GO
CREATE OR ALTER FUNCTION f_4b
(
	@od INT,
	@do INT
)
RETURNS TABLE
AS
RETURN
	SELECT
		*,
		DATEDIFF(YEAR, E.HireDate, GETDATE()) AS [Razlika]
	FROM Employees AS E
	WHERE DATEDIFF(YEAR, E.HireDate, GETDATE()) BETWEEN @od AND @do
GO

SELECT *
FROM f_4b(30, 32)

--d)	(3 bodova) Kreirati proceduru sp_Prodavnice_insert kojom će se izvršiti insertovanje podataka unutar tabele prodavnice. OBAVEZNO kreirati testni slučaj. (Novokreirana baza) 

GO
CREATE PROCEDURE sp_Prodavnice_insert
(
	@ProdavnicaID NCHAR(4),
	@NazivProdavnice NVARCHAR(40) = NULL,
	@Grad NVARCHAR(40) = NULL
)
AS
BEGIN
	INSERT INTO Prodavnice
	(
		ProdavnicaID,
		NazivProdavnice,
		Grad
	)
	VALUES
	(
		@ProdavnicaID,
		@NazivProdavnice,
		@Grad
	)
END
GO

SELECT * FROM Prodavnice

exec sp_Prodavnice_insert @ProdavnicaID = '1234', @Grad = 'Sarajevo'
exec sp_Prodavnice_insert @ProdavnicaID = '9876', @NazivProdavnice = 'Na Drini turpija'