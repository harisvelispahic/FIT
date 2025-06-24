--3.
--	Baza: Northwind 

GO 
USE Northwind

-- a) (5 bodova) Prikazati zaposlenike koji su obradili manje narudžbi od zaposlenika koji ima najviše narudžbi u njihovoj regiji. 

SELECT DISTINCT
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
				ROW_NUMBER() OVER (PARTITION BY E.Region ORDER BY COUNT(*) DESC) AS rb
			FROM Employees AS E
				INNER JOIN Orders AS O ON E.EmployeeID = O.EmployeeID
			GROUP BY E.EmployeeID, E.Region
			) AS SUBQ1
		WHERE rb = 1
		) AS RangiraniUposlenici ON (SviUposlenici.Region = RangiraniUposlenici.Region OR RangiraniUposlenici.Region IS NULL) AND SviUposlenici.Obrađeno < RangiraniUposlenici.Obrađeno
	) AS SUBQ ON E.EmployeeID = SUBQ.EmployeeID

-- b) (5 bodova) Prikazati proizvode koje naručuju kupci iz zemlje iz koje se najmanje kupuje. 

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

--4. 
--Baza: Pubs 

GO
USE pubs

-- a) (5 bodova) Prikazati prosječnu starost knjiga/naslova prodanih u trgovinama u kojima se prodaju naslovi duži od 35 znakova.

SELECT
	AVG(DATEDIFF(YEAR, T.pubdate, GETDATE())) AS [Prosjecna starost]
FROM titles AS T
	INNER JOIN sales AS SA ON T.title_id = SA.title_id
WHERE SA.stor_id IN
					(
					SELECT
						ST.stor_id
					FROM stores AS ST
						INNER JOIN sales AS SA ON ST.stor_id = SA.stor_id
					WHERE SA.title_id IN
										(
										SELECT
											T.title_id
										FROM titles AS T
										WHERE LEN(T.title) > 35
										)
					)

-- b) (10 bodova) Prikazati trgovine u kojima se mogu naći knjige/naslovi čiji autori žive u istom gradu kao i izdavač, a prodani su više puta nego što je prosječna prodaja naslova iz tri godine s najmanjom prodajom. 

SELECT
	ST.stor_name
FROM stores AS ST
	INNER JOIN sales AS SA ON ST.stor_id = SA.stor_id
WHERE SA.title_id IN
						(
						SELECT
							T.title_id
						FROM authors AS A
							INNER JOIN titleauthor AS TA ON A.au_id = TA.au_id
							INNER JOIN titles AS T ON TA.title_id = T.title_id 
							INNER JOIN publishers AS P ON T.pub_id = P.pub_id
							INNER JOIN sales AS SA ON T.title_id = SA.title_id
						WHERE A.city = P.city
						GROUP BY T.title_id
						HAVING SUM(SA.qty) >
												(
												SELECT
													AVG(SQ.Prodaja)
												FROM
													(
													SELECT
														YEAR(SA.ord_date) AS Godina,
														SUM(SA.qty) AS Prodaja,
														ROW_NUMBER() OVER (ORDER BY SUM(SA.qty) ASC) AS rn
													FROM sales AS SA
													GROUP BY YEAR(SA.ord_date)
													) AS SQ
												WHERE SQ.rn IN (1, 2, 3)
												)
						)

-- c) (10 bodova) Prikazati autore čije se knjige/naslovi prodaju u trgovinama koje se nalaze u istim gradovima u kojima su smješteni izdavači koji su objavili više od prosječnog broja objavljenih knjiga/naslova po izdavaču. 
-- Napomena: Zadatke obavezno riješiti kao podupite (na where, having, ...) ugniježdeni upiti 

SELECT
	A.au_fname,
	A.au_lname
FROM authors AS A
	INNER JOIN titleauthor AS TA ON A.au_id = TA.au_id
WHERE TA.title_id IN
					(
					SELECT
						SA.title_id
					FROM stores AS ST
						INNER JOIN sales AS SA ON ST.stor_id = SA.stor_id
					WHERE ST.stor_id IN
										(
										SELECT
											ST.stor_id
										FROM stores AS ST
										WHERE ST.city IN
														(
														SELECT
															A.city
														FROM authors AS A
															INNER JOIN titleauthor AS TA ON A.au_id = TA.au_id
														GROUP BY A.city
														HAVING COUNT(*) >
																			(
																			SELECT
																				AVG(CAST(SQ1.Broj AS DECIMAL(18, 2))) AS Prosjek
																			FROM 
																				(
																				SELECT
																					P.pub_id,
																					COUNT(*) AS Broj
																				FROM publishers AS P
																					INNER JOIN titles AS T ON P.pub_id = T.pub_id
																				GROUP BY P.pub_id
																				) AS SQ1
																			)
														)
										)
					)

--5. Kreirati bazu podataka koju ćete imenovati svojim brojem indeksa.

GO
CREATE DATABASE zima2
GO
USE zima2

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
	IzdavacID CHAR(4) CONSTRAINT FK_Naslovi_Izdavaci FOREIGN KEY REFERENCES Izdavaci(IzdavacID)
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
	Kolicina SMALLINT NOT NULL CONSTRAINT CK_Kolicina CHECK(Kolicina > 0)

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



-- 5.2.
--U kreiranu bazu kopirati podatke iz baze Pubs: 

-- a) U tabelu Izdavaci dodati sve izdavače
--• pub_id → IzdavacID; 
--• pub_name → NazivIzdavaca; 
--• country → Drzava; 
--• Logo → Logo

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

--b) U tabelu Naslovi dodati sve naslove, na mjestima gdje nema pohranjenih podataka o cijeni zamijeniti vrijednost sa 0
--• title_id → NaslovID; 
--• title → Naslov; 
--• type → Tip;
--• price → Cijena; 
--• pub_id → IzdavacID

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
	T.price,
	T.pub_id
FROM pubs.dbo.titles AS T

--c) U tabelu Prodaja dodati sve stavke iz tabele prodaja
--• stor_id → ProdavnicalD; 
--• order_num → BrojNarudzbe; 
--• title_id → NaslovID; 
--• ord_date → DatumNarudzbe; 
--• qty → Kolicina

INSERT INTO Prodaja
(
	ProdavnicaID,
	BrojNarudzbe,
	NaslovID,
	DatumNarudzbe,
	Kolicina
)
SELECT
	SA.stor_id,
	SA.ord_num,
	SA.title_id,
	SA.ord_date,
	SA.qty
FROM pubs.dbo.sales AS SA

--d) U tabelu Prodavnice dodati sve prodavnice
--• stor_id → ProdavnicaID;
--• store_name → NazivProdavnice;
--• city → Grad

INSERT INTO Prodavnice
(
	ProdavnicaID,
	NazivProdavnice,
	Grad
)
SELECT
	ST.stor_id,
	ST.stor_name,
	ST.city
FROM pubs.dbo.stores AS ST

-- 5.3.
--a) (5 bodova) Kreirati pogled PRODAJA_PO_IZDAVACIMA kojim će dati pregled prodaje knjiga po izdavačima. Prikazati naziv te državu iz koje izdavači dolaze, ukupan broj napisanih naslova, te ukupnu prodanu količinu. Rezultate sortirati opadajući po ukupnoj prodanoj količini. (Novokreirana baza)

GO
CREATE OR ALTER VIEW PRODAJA_PO_IZDAVACIMA
AS
	SELECT TOP 100 PERCENT
		I.NazivIzdavaca,
		I.Drzava,
		COUNT(DISTINCT N.NaslovID) AS [Ukupan broj napisanih naslova],
		SUM(P.Kolicina) AS [Ukupna prodana količina]
	FROM Izdavaci AS I
		INNER JOIN Naslovi AS N ON I.IzdavacID = N.IzdavacID
		INNER JOIN Prodaja AS P ON N.NaslovID = P.NaslovID
	GROUP BY I.NazivIzdavaca, I.Drzava
	ORDER BY SUM(P.Kolicina) DESC
GO

SELECT * FROM PRODAJA_PO_IZDAVACIMA
ORDER BY 4 DESC

--b) (2 boda) U novokreiranu bazu iz baze Northwind dodati tabelu Employees. Prilikom kreiranja izvršiti automatsko instertovanje podataka. Tabelu i njene kolone imenovati domaćim jezikom

SELECT
	E.EmployeeID AS ZaposlenikID,
	E.LastName AS Prezime,
	E.FirstName AS Ime,
	E.Title AS Titula,
	E.BirthDate AS DatumRodjenja,
	E.HireDate AS DatumZaposlenja,
	E.Address AS Adresa,
	E.City AS Grad
INTO Zaposlenici
FROM Northwind.dbo.Employees AS E

SELECT * FROM Zaposlenici

--c) (5 boda) Kreirati funkciju fun_53c koja će vraćati podatke u formi tabele na osnovu proslijedjenih parametra od i do, cjelobrojni tip. Funkcija će vraćati one zapise u kojima se godine radnog staža nalaze u intervalu od-do. Potrebno je da se prilikom kreiranja funkcije u rezultatu nalaze sve kolone tabele uposlenici, zajedno sa izračunatim godinama radnog staža. OBAVEZNO provjeriti ispravnost funkcije unošenjem kontrolnih vrijednosti. (Novokreirana baza)

GO
CREATE OR ALTER FUNCTION fun_53c
(
	@od INT,
	@do INT
)
RETURNS TABLE
AS
RETURN
	SELECT
		*,
		DATEDIFF(YEAR, Z.DatumZaposlenja, GETDATE()) AS Staz
	FROM Zaposlenici AS Z
	WHERE DATEDIFF(YEAR, Z.DatumZaposlenja, GETDATE()) BETWEEN @od AND @do
GO

SELECT * FROM fun_53c(15, 45)

--d) (3 bodova) Kreirati proceduru sp_Prodavnice_insert kojom će se izvršiti insertovanje podataka unutar tabele prodavnice. OBAVEZNO kreirati testni slučaj. (Novokreirana baza)

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

exec sp_Prodavnice_insert 'ABCD', 'Na Drini turpija :)', 'Visegrad'