--2. 										max: 12 bodova
--Baza: AdventureWorks2017

GO
USE AdventureWorks2017

--a)	(6 bodova) Prikazati ukupnu vrijednost narudžbi za svakog kupca pojedinačno. Upitom prikazati ime i prezime kupca te ukupnu vrijednost narudžbi sa i bez popusta.
--Zaglavlje (kolone): Ime i prezime, Vrijednost bez popusta (količina * cijena), Vrijednost sa popustom.

SELECT
	CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
	SUM(SOD.UnitPrice * SOD.OrderQty) AS [Vrijednost bez popusta],
	SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)) AS [Vrijednost sa popustom]
FROM Sales.Customer AS C
	INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
	INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
GROUP BY P.FirstName, P.LastName

--b)	(6 bodova) Prikazati 5 proizvoda od kojih je ostvaren najveći profit (zarada) i 5 s najmanjim profitom. Zaglavlje: Ime proizvoda, Zarada.

SELECT *
FROM
	(
	SELECT TOP 5
		P.Name,
		SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)) AS [Zarada]
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
	GROUP BY P.Name
	ORDER BY 2 DESC
	) AS SQ1

UNION ALL

SELECT *
FROM
	(
	SELECT TOP 5
		P.Name,
		SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)) AS [Zarada]
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
	GROUP BY P.Name
	ORDER BY 2 ASC
	) AS SQ2

-- 3. 										max: 23 boda
--Baza: Northwind

GO
USE Northwind

--a)	(7 bodova) Prikazati kupce koji su u sklopu jedne narudžbe naručili proizvode iz tačno tri kategorije. (Northwind)
--Zaglavlje: ContactName.

SELECT DISTINCT
	C.ContactName
FROM Customers AS C
	INNER JOIN Orders AS O ON C.CustomerID = O.CustomerID
	INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
	INNER JOIN Products AS P ON OD.ProductID = P.ProductID
GROUP BY C.ContactName, O.OrderID
HAVING COUNT(DISTINCT P.CategoryID) = 3

--b)	(7 bodova) Prikazati zaposlenike koji su obradili više narudžbi od zaposlenika koji ima najmanje narudžbi u njihovoj regiji (kolona Region u tabeli Employees). (Northwind) 
--Zaglavlje: Ime i prezime.

SELECT
	FINAL.FirstName,
	FINAL.LastName
FROM
	(
	SELECT
		E.FirstName,
		E.LastName,
		RegijaBrojNarudzbi.[Broj narudzbi] AS [MinNarudzbi],
		COUNT(*) AS [Broj narudzbi]
	FROM Employees AS E
		INNER JOIN Orders AS O ON E.EmployeeID = O.EmployeeID
		INNER JOIN
		(
		SELECT
			SQ1.Region,
			SQ1.[Broj narudzbi]
		FROM
			(
			SELECT
				E.Region,
				E.EmployeeID,
				COUNT(*) AS [Broj narudzbi],
				ROW_NUMBER() OVER (PARTITION BY E.Region ORDER BY COUNT(*)) AS rb
			FROM Employees AS E 
				INNER JOIN Orders AS O ON E.EmployeeID = O.EmployeeID
			GROUP BY E.Region, E.EmployeeID
			) AS SQ1
		WHERE SQ1.rb = 1
		) AS RegijaBrojNarudzbi ON E.Region = RegijaBrojNarudzbi.Region OR E.Region IS NULL
	GROUP BY E.FirstName, E.LastName, RegijaBrojNarudzbi.[Broj narudzbi]
	) AS FINAL
WHERE FINAL.[Broj narudzbi] > FINAL.MinNarudzbi

--c)	(9 bodova) Prikazati proizvode koje naručuju kupci iz zemlje iz koje se najmanje kupuje. (Northwind)
--Zaglavlje: ProductName.

SELECT DISTINCT
	P.ProductName
FROM Products AS P	
	INNER JOIN [Order Details] AS OD ON P.ProductID = OD.ProductID
	INNER JOIN Orders AS O ON OD.OrderID = O.OrderID
WHERE O.CustomerID IN
						(
						SELECT
							C.CustomerID
						FROM Customers AS C
						WHERE C.Country =
											(
											SELECT TOP 1
												O.ShipCountry
											FROM Orders AS O
												INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
											GROUP BY O.ShipCountry
											ORDER BY SUM(OD.Quantity) ASC
											)
						)

--4. 										max: 20 bodova
--Baza: Pubs	

GO
USE pubs

--a)	(10 bodova) Prikazati trgovine u kojima se mogu naći naslovi prodani manje puta nego što je prosječna prodaja naslova iz godine kad je prodano najmanje naslova (Pubs).
--Zaglavlje: stor_name

SELECT DISTINCT
	ST.stor_name
FROM stores AS ST
	INNER JOIN sales AS SA ON ST.stor_id = SA.stor_id
WHERE SA.title_id IN
					(
					SELECT
						S.title_id
					FROM sales AS S
					GROUP BY S.title_id
					HAVING SUM(S.qty) <
										(
										SELECT
											AVG(S.qty)
										FROM sales AS S
										WHERE YEAR(S.ord_date) =
																(
																SELECT TOP 1
																	YEAR(S.ord_date)
																FROM sales AS S
																GROUP BY YEAR(S.ord_date)
																ORDER BY COUNT(*)
																)
										)
					)

--b)	(10 bodova) Prikazati naslove starije od najbolje prodavanog naslova kojeg je izdao izdavač iz savezne države koja sadrži slog 'CA'.  (Pubs).
--Zaglavlje: title(naslov knjige)
--Napomena: zadatke obavezno rješavati kao podupite (na where, having, ...) – ugnježđeni upiti

SELECT
	T.title
FROM titles AS T
WHERE T.pubdate <
					(
					SELECT TOP 1
						T.pubdate
					FROM publishers AS P
						INNER JOIN titles AS T ON P.pub_id = T.pub_id
						INNER JOIN sales AS S ON T.title_id = S.title_id
					WHERE P.state LIKE '%CA%'
					GROUP BY T.title_id, T.pubdate
					ORDER BY SUM(S.qty) DESC
					)

--5. 										
--Kreirati bazu podataka koju ćete imenovati svojim brojem indeksa. 

GO
CREATE DATABASE IB
GO
USE IB

--5.1. 										max: 5 bodova
--U kreiranoj bazi podataka kreirati tabele sa sljedećom strukturom: 			
--a) Izdavaci 
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

--b) Naslovi 
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
	IzdavacID CHAR(4) CONSTRAINT FK_Naslovi_Izdavaci FOREIGN KEY REFERENCES Izdavaci(IzdavacID) NOT NULL
)

--c) Prodaja  
--•	ProdavnicaID, 4 karaktera fiksne dužine, strani i primarni ključ, 
--•	BrojNarudzbe, 20 karaktera, primarni ključ, 
--•	NaslovID, 6 karaktera, strani i primarni ključ, 
--•	DatumNarudzbe, polje za unos datuma i vremena (obavezan unos), 
--•	Kolicina, skraćeni cjelobrojni tip (obavezan unos, dozvoljen unos brojeva većih od 0

CREATE TABLE Prodaja
(
	ProdavnicaID CHAR(4) CONSTRAINT FK_Prodaja_Prodavnice FOREIGN KEY REFERENCES Prodavnice(ProdavnicaID),
	BrojNarudzbe VARCHAR(20), 
	NaslovID VARCHAR(6) CONSTRAINT FK_Prodaja_Naslovi FOREIGN KEY REFERENCES Naslovi(NaslovID),
	DatumNarudzbe DATETIME NOT NULL,
	Kolicina SMALLINT CONSTRAINT CK_Prodaja_Kolicina CHECK(Kolicina > 0) NOT NULL,

	CONSTRAINT PK_Prodaja PRIMARY KEY (ProdavnicaID, BrojNarudzbe, NaslovID)
)

--d)	Prodavnice 
--•	ProdavnicaID, 4 karaktera fiksne dužine i primarni ključ, 
--•	NazivProdavnice, 40 karaktera, 
--•	Grad, 40 karaktera 

CREATE TABLE Prodavnice
(
	ProdavnicaID CHAR(4) CONSTRAINT PK_Prodavnice PRIMARY KEY,
	NazivProdavnice VARCHAR(40), 
	Grad VARCHAR(40) 
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
	PI.logo
FROM pubs.dbo.publishers AS P
	INNER JOIN pubs.dbo.pub_info AS PI ON P.pub_id = PI.pub_id

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
--•	order_num -> BrojNarudzbe; 
--•	title_id -> NaslovID; 
--•	ord_date -> DatumNarudzbe; 
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
--•	stor_id -> ProdavnicaID; 
--•	store_name -> NazivProdavnice; 
--•	city -> Grad 

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
		UPK.[Ukupna prodana kolicina]
	FROM Izdavaci AS I	
		INNER JOIN Naslovi AS N ON I.IzdavacID = N.IzdavacID
		INNER JOIN
		(
		SELECT
			N.IzdavacID,
			SUM(P.Kolicina) AS [Ukupna prodana kolicina]
		FROM Naslovi AS N
			INNER JOIN Prodaja AS P ON N.NaslovID = P.NaslovID
		GROUP BY N.IzdavacID
		) AS UPK ON I.IzdavacID = UPK.IzdavacID
	GROUP BY I.NazivIzdavaca, I.Drzava, UPK.[Ukupna prodana kolicina]
	ORDER BY 4 DESC
GO

SELECT * FROM v_prodaja ORDER BY 4 DESC

--b)	(2 boda) U novokreiranu bazu iz baze Northwind dodati tabelu Employees. Prilikom kreiranja izvršiti automatsko instertovanje podataka. 

SELECT
	*
INTO Zaposlenici
FROM Northwind.dbo.Employees

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
		DATEDIFF(YEAR, Z.HireDate, GETDATE()) AS [Godine staza]
	FROM Zaposlenici AS Z
	WHERE DATEDIFF(YEAR, Z.HireDate, GETDATE()) BETWEEN @od AND @do
GO

SELECT * FROM f_4b(30, 35)
SELECT * FROM f_4b(30, 32)
SELECT * FROM f_4b(30, 32)
SELECT * FROM f_4b(25, 30)

--d)	(3 bodova) Kreirati proceduru sp_Prodavnice_insert kojom će se izvršiti insertovanje podataka unutar tabele prodavnice. OBAVEZNO kreirati testni slučaj. (Novokreirana baza) 

GO
CREATE OR ALTER PROCEDURE sp_Prodavnice_insert
(
	@ProdavnicaID CHAR(4),
	@NazivProdavnice VARCHAR(40) = NULL,
	@Grad VARCHAR(40) = NULL
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

exec sp_Prodavnice_insert @ProdavnicaID = 'ABCD', @NazivProdavnice = 'Na Drini turpija', @Grad = 'Visegrad'
exec sp_Prodavnice_insert @ProdavnicaID = 'aabb'