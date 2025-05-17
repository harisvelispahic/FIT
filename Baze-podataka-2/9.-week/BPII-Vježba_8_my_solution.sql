-- 1. Prikazati nazive svih gradova u kojima su ukupna zabilježena neto primanja veća od 25% ukupnih neto primanja koje je zabilježila Kina. Također prikazati postotak primanja tih gradova u odnosu na Kinu, te izlaz sortirati po postotku u opadajućem redoslijedu. (Prihodi) 

USE prihodi;

SELECT 
	G.Grad,
	CAST(SUM(RP.Neto) * 100.0 /
							(
							SELECT SUM(RP.Neto) 
							FROM Drzava AS D
								INNER JOIN Osoba AS O ON D.DrzavaID = O.DrzavaID
								INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
							WHERE D.Drzava = 'China'
							) AS VARCHAR) + '%' AS Postotak
FROM Grad AS G
	INNER JOIN Osoba AS O ON G.GradID = O.GradID
	INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
GROUP BY G.Grad
HAVING SUM(RP.Neto) > 0.25 *
							(
							SELECT SUM(RP.Neto) 
							FROM Drzava AS D
								INNER JOIN Osoba AS O ON D.DrzavaID = O.DrzavaID
								INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
							WHERE D.Drzava = 'China'
							)
ORDER BY 2 DESC;


-- 2. Prikazati osobe čiji su neto redovni prihodi manji od prosjeka svih neto redovnih primanja i čiji su vanredni prihodi veći od prosjeka svih vandrednih primanja. (Prihodi)


SELECT
	O.OsobaID,
	CONCAT(O.Ime, ' ', O.PrezIme) AS [Ime i prezime],
	AVG(RP.Neto) AS Neto, 
	AVG(VP.IznosVanrednogPrihoda) AS Vanredni
FROM Osoba AS O
	LEFT JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
	LEFT JOIN VanredniPrihodi AS VP ON O.OsobaID = VP.OsobaID
WHERE O.Ime IS NOT NULL AND O.PrezIme IS NOT NULL
GROUP BY O.OsobaID, O.Ime, O.PrezIme
HAVING AVG(RP.Neto) <
				(
				SELECT AVG(RP.Neto)
				FROM Osoba AS O
					INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
				)
AND AVG(VP.IznosVanrednogPrihoda) >
									(
									SELECT AVG(VP.IznosVanrednogPrihoda)
									FROM Osoba AS O
										INNER JOIN VanredniPrihodi AS VP ON O.OsobaID = VP.OsobaID
									)
;

-- Uzet prosjek AVG(RP.Neto) i AVG(VP.IznosVanrednogPrihoda) zbog toga sto jedna osoba moze da ima vise neto/vanrednih prihoda


-- 3. Za svaku pojedinačnu godinu u kojima su kreirane narudžbe (izvući godinu iz datuma narudžbe) prikazati ime i prezime (spojeno) prodavača koji je ostvario najveći prihod u toj godini (sa popustom i taksama), naziv proizvoda koji je ostvario najeću prodaju (ukupna prodata količina) i ime i prezime (spojeno) kupca koji je najviše potrošio (sa popustom i taksama) u toj godini. Izlaz sortirati uzlazno po godinama. (AdventureWorks2017)

USE AdventureWorks2017;

--		1. NACIN

SELECT
	[Prodavaci final].Godina, 
	[Prodavaci final].[Ime i prezime prodavaca], 
	[Proizvodi final].[Ime proizvoda],
	[Kupci final].[Ime i prezime kupca]
FROM
	(
	SELECT
		[Svi prodavaci].Godina,
		[Svi prodavaci].[Ime i prezime prodavaca]
	FROM
		(
		SELECT 
				YEAR(SOH.OrderDate) AS Godina,
				CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime prodavaca],
				SUM(SOD.LineTotal) AS Prihod
			FROM Sales.SalesPerson AS SP
				INNER JOIN Sales.SalesOrderHeader AS SOH ON SP.BusinessEntityID = SOH.SalesPersonID
				INNER JOIN Person.Person AS P ON SP.BusinessEntityID = P.BusinessEntityID
				INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
			GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)
		) AS [Svi prodavaci]
	WHERE 
		([Svi prodavaci].Godina + [Svi prodavaci].Prihod) IN

															(
															SELECT
																Prodavaci.Godine + MAX(Prodavaci.Prihod) AS [Max prihod po godini]
															FROM
																(
																SELECT 
																	YEAR(SOH.OrderDate) AS Godine,
																	CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
																	SUM(SOD.LineTotal) AS Prihod
																FROM Sales.SalesPerson AS SP
																	INNER JOIN Sales.SalesOrderHeader AS SOH ON SP.BusinessEntityID = SOH.SalesPersonID
																	INNER JOIN Person.Person AS P ON SP.BusinessEntityID = P.BusinessEntityID
																	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
																GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)
																) AS Prodavaci
															GROUP BY Prodavaci.Godine
															)
	) AS [Prodavaci final]

INNER JOIN


	(
	SELECT
		[Svi proizvodi].Godina,
		[Svi proizvodi].[Ime proizvoda]
	FROM
		(
		SELECT
			YEAR(SOH.OrderDate) AS Godina,
			P.Name AS [Ime proizvoda],
			SUM(SOD.OrderQty) AS Kolicina
		FROM Production.Product AS P
			INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
			INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
		GROUP BY YEAR(SOH.OrderDate), P.Name
		) AS [Svi proizvodi]
	WHERE 
		(CAST([Svi proizvodi].Godina AS VARCHAR(4)) + CAST([Svi proizvodi].Kolicina AS VARCHAR(20))) IN
																(
																SELECT 
																	CAST(Proizvodi.Godina AS VARCHAR(4)) + CAST(MAX(Proizvodi.Kolicina) AS VARCHAR								(20)) AS [Max kolicina]
																FROM
																	(
																	SELECT
																		YEAR(SOH.OrderDate) AS Godina,
																		P.Name,
																		SUM(SOD.OrderQty) AS Kolicina
																	FROM Production.Product AS P
																		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
																		INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
																	GROUP BY YEAR(SOH.OrderDate), P.Name
																	) AS Proizvodi
																GROUP BY Proizvodi.Godina
																)
	) AS [Proizvodi final] ON [Prodavaci final].Godina = [Proizvodi final].Godina

INNER JOIN

	(
	SELECT
		[Svi kupci].Godina,
		[Svi kupci].[Ime i prezime kupca],
		[Svi kupci].Potroseno
	FROM
		(
		SELECT
			YEAR(SOH.OrderDate) AS Godina,
			CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime kupca],
			SUM(SOD.LineTotal) AS [Potroseno]
		FROM Sales.Customer AS C
			INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
			INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
			INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
		GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)
		) AS [Svi kupci]
	WHERE [Svi kupci].Godina + [Svi kupci].Potroseno IN
														(
														SELECT
															Kupci.Godina + MAX(Kupci.Potroseno) AS [Max potroseno]
														FROM
															(
															SELECT
																YEAR(SOH.OrderDate) AS Godina,
																CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
																SUM(SOD.LineTotal) AS [Potroseno]
															FROM Sales.Customer AS C
																INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
																INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
																INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
															GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)
															) AS Kupci
														GROUP BY Kupci.Godina
														)
	) AS [Kupci final] ON [Prodavaci final].Godina = [Kupci final].Godina
ORDER BY 1;



--		2. NACIN
-- ROW_NUMBER()

USE AdventureWorks2017;

WITH TopProdavaci AS (
	SELECT
		YEAR(SOH.OrderDate) AS Godina,
		CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
		SUM(SOD.LineTotal) AS [Ukupni prihod],
		ROW_NUMBER() OVER (
			PARTITION BY YEAR(SOH.OrderDate) 
			ORDER BY SUM(SOD.LineTotal) DESC
		) AS RN
	FROM Person.Person AS P
		INNER JOIN Sales.SalesPerson AS SP ON P.BusinessEntityID = SP.BusinessEntityID
		INNER JOIN Sales.SalesOrderHeader AS SOH ON SP.BusinessEntityID = SOH.SalesPersonID
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
	GROUP BY YEAR(SOH.OrderDate), P.FirstName, P.LastName
),

TopProizvodi AS (
	SELECT
		YEAR(SOH.OrderDate) AS Godina,
		P.Name AS [Naziv proizvoda],
		SUM(SOD.OrderQty) AS [Ukupna prodata kolicina],
		ROW_NUMBER() OVER (
			PARTITION BY YEAR(SOH.OrderDate)
			ORDER BY SUM(SOD.OrderQty) DESC
		) AS RN
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
		INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
	GROUP BY YEAR(SOH.OrderDate), P.Name
),

TopKupci AS (
	SELECT
		YEAR(SOH.OrderDate) AS Godina,
		CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
		SUM(SOD.LineTotal) [Ukupno potroseno],
		ROW_NUMBER() OVER (
			PARTITION BY YEAR(SOH.OrderDate)
			ORDER BY SUM(SOD.LineTotal) DESC
		) AS RN
	FROM Person.Person AS P
		INNER JOIN Sales.Customer AS C ON P.BusinessEntityID = C.PersonID
		INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
	GROUP BY YEAR(SOH.OrderDate), P.FirstName, P.LastName


)

SELECT
	PROD.Godina,
	PROD.[Ime i prezime],
	PROI.[Naziv proizvoda],
	KUPCI.[Ime i prezime]
FROM TopProdavaci AS PROD
	INNER JOIN TopProizvodi AS PROI ON PROD.Godina = PROI.Godina
	INNER JOIN TopKupci AS KUPCI ON PROD.Godina = KUPCI.Godina
WHERE PROD.RN = 1 AND PROI.RN = 1 AND KUPCI.RN = 1
ORDER BY PROD.Godina;


-- 4. Prikazati ime i prezime, broj godina staža, opis posla uposlenika te broj knjiga uposlenika koji su učestvovali u objavljivanju više od broja objavljenih naslova izdavača sa id 0736 a koji imaju više od 31 godine staža. Rezultate upita sortirati prema godinama staža rastućim i prema broju naslova u opadajućem redoslijedu. (Pubs)

USE pubs;


SELECT 
	CONCAT(E.fname, ' ', E.lname) AS [Ime i prezime], 
	DATEDIFF(YEAR, E.hire_date, GETDATE()) AS [Godine staza], 
	J.job_desc, 
	COUNT(*) AS [Broj knjiga]
FROM jobs AS J
	INNER JOIN employee AS E ON J.job_id = E.job_id
	INNER JOIN publishers AS P ON E.pub_id = P.pub_id
	INNER JOIN titles AS T ON P.pub_id = T.pub_id
WHERE DATEDIFF(YEAR, E.hire_date, GETDATE()) > 31
GROUP BY CONCAT(E.fname, ' ', E.lname), DATEDIFF(YEAR, E.hire_date, GETDATE()), J.job_desc
HAVING COUNT(*) >
				(
				SELECT COUNT(*) AS [Broj naslova]
				FROM publishers AS P
					INNER JOIN titles AS T ON P.pub_id = T.pub_id
				WHERE P.pub_id = '0736'
				)
ORDER BY 2 ASC, 4 DESC;


-- 5. Napisati upit kojim će se prikazati ime i prezime uposlenika koji rade na poziciji dizajnera, a koji su učestvovali u objavljivanju knjiga čija je prosječna prodata količina veća od prosječne prodane količine izdavačke kuće sa id 0877. U rezultatima upita prikazati i prosječnu prodanu količinu. (Pubs) 

USE pubs;


SELECT 
	CONCAT(E.fname, ' ', E.lname) AS [Ime i prezime],
	AVG(S.qty) AS [Prosjecna prodata kolicina]
FROM employee AS E
	INNER JOIN jobs AS J ON E.job_id = J.job_id
	INNER JOIN publishers AS P ON E.pub_id = P.pub_id
	INNER JOIN titles AS T ON P.pub_id = T.pub_id
	INNER JOIN sales AS S ON T.title_id = S.title_id
WHERE LOWER(J.job_desc) LIKE '%designer%' 
	AND T.title_id IN
						(
						SELECT T.title_id
						FROM titles AS T
							INNER JOIN sales AS S ON T.title_id = S.title_id
						GROUP BY T.title_id
						HAVING AVG(S.qty) >
											(
											SELECT AVG(S.qty) AS Prosjek0877
											FROM publishers AS P
												INNER JOIN titles AS T ON P.pub_id = T.pub_id
												INNER JOIN sales AS S ON T.title_id = S.title_id
											WHERE P.pub_id LIKE '0877'
											)
						)
GROUP BY CONCAT(E.fname, ' ', E.lname);



-- 6. Kreirati upit koji prikazuje sumaran iznos svih transakcija (šema Production) po godinama (uzeti u obzir i transakcije iz arhivske tabele). U rezultatu upita prikazati samo dvije kolone: kalendarska godina i ukupan iznos transakcija u godini. Iznos transakcije predstavlja umnožak količine i stvarne cijene.(AdventureWorks2017)

USE AdventureWorks2017;


SELECT 
	YEAR(SQ1.TransactionDate) AS Godina, 
	SUM(SQ1.Quantity * SQ1.ActualCost) AS [Suma transakcija]
FROM
	(
	SELECT *
	FROM Production.TransactionHistory
	UNION ALL
	SELECT *
	FROM Production.TransactionHistoryArchive
	) AS SQ1
GROUP BY YEAR(SQ1.TransactionDate)
ORDER BY 1;


-- 7. Kreirati upit koji prikazuje četvrtu najveću satnicu uposlenika u preduzeću. U rezultatima upita prikazati pored vrijednosti satnice i ime i prezime zaposlenika. (AdventureWorks2017) 

--		1. NACIN

SELECT TOP 1 *
FROM
	(
	SELECT TOP 4
		CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime], EPH.Rate
	FROM Person.Person AS P
		INNER JOIN HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
		INNER JOIN HumanResources.EmployeePayHistory AS EPH ON E.BusinessEntityID = EPH.BusinessEntityID
	ORDER BY 2 DESC
	) AS TOP4
ORDER BY 2 ASC;


--		2. NACIN
-- ROW_NUMBER()

SELECT
	SQ1.[Ime i prezime],
	SQ1.Rate
FROM
	(
	SELECT
		CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
		EPH.Rate,
		ROW_NUMBER() OVER (
			ORDER BY EPH.Rate DESC
		) AS RN
	FROM Person.Person AS P
		INNER JOIN HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
		INNER JOIN HumanResources.EmployeePayHistory AS EPH ON E.BusinessEntityID = EPH.BusinessEntityID
	) AS SQ1
WHERE SQ1.RN = 4;

-- 8. Kreirati upit koji prikazuje proizvode kojih na skladištu ima u količini manjoj od 30 komada. Lista treba da sadrži naziv proizvoda, naziv skladišta (lokaciju), stanje na skladištu i ukupnu prodanu količinu. U rezultate upita uključiti i one proizvode koji nikad nisu prodavani, ne uzimajući u obzir njihovo stanje na skladištu. Ukoliko je ukupna prodana količina prikazana kao NULL vrijednost, izlaz zamijeniti brojem 0. (AdventureWorks2017)

SELECT 
	P.Name AS [Naziv proizvoda], 
	L.Name AS [Naziv skladista], 
	PI.Quantity,
	ISNULL(SUM(SOD.OrderQty), 0) AS [Ukupna prodana kolicina]
FROM Production.Product AS P
	INNER JOIN Production.ProductInventory AS PI ON P.ProductID = PI.ProductID
	INNER JOIN Production.Location AS L ON PI.LocationID = L.LocationID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
WHERE PI.Quantity < 30
GROUP BY P.Name, L.Name, PI.Quantity

UNION

SELECT 
	P.Name AS [Naziv proizvoda], 
	L.Name AS [Naziv skladista], 
	PI.Quantity,
	ISNULL(SUM(SOD.OrderQty), 0) AS [Ukupna prodana kolicina]
FROM Production.Product AS P
	INNER JOIN Production.ProductInventory AS PI ON P.ProductID = PI.ProductID
	INNER JOIN Production.Location AS L ON PI.LocationID = L.LocationID
	LEFT JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
WHERE SOD.OrderQty IS NULL
GROUP BY P.Name, L.Name, PI.Quantity


-- 9. Prikazati ukupnu prodanu količinu i ukupnu zaradu (uključujući popust) od prodaje svakog pojedinog proizvoda po teritoriji. Uzeti u obzir samo prodaju u sklopu ponude pod nazivom “Volume Discount 11 to 14” i to samo gdje je ukupna prodana količina veća od 100 komada. Zaradu zaokružiti na dvije decimale, te izlaz sortirati po zaradi u opadajućem redoslijedu. (AdventureWorks2017)

SELECT
	ST.Name AS [Ime teritorije],
	P.Name AS [Ime proizvoda],
	SUM(SOD.OrderQty) AS [Ukupna prodana kolicina],
	ROUND(SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)), 2) AS [Ukupna zarada]
FROM Production.Product AS P
INNER JOIN Sales.SpecialOfferProduct AS SOP ON P.ProductID = SOP.ProductID
	INNER JOIN Sales.SpecialOffer AS SO ON SOP.SpecialOfferID = SO.SpecialOfferID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOP.ProductID = SOD.ProductID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID

WHERE SO.Description = 'Volume Discount 11 to 14'
GROUP BY ST.Name, P.Name
HAVING SUM(SOD.OrderQty) > 100
ORDER BY 4 DESC;


-- 10. Kreirati upit koji prikazuje naziv proizvoda, naziv lokacije, stanje zaliha na lokaciji, ukupno stanje zaliha na svim lokacijama i ukupnu prodanu količinu (stanja i ukupnu prodanu količinu izračunati za svaki proizvod pojedinačno). Uzeti u obzir prodaju samo u 2013. godini. U rezultatima NULL vrijednosti zamijeniti sa 0 i sortirati po ukupnoj prodanoj količini u opadajućem redoslijedu. (AdventureWorks2017)

USE AdventureWorks2017;


SELECT
	P.Name AS [Ime proizvoda],
	L.Name AS [Ime lokacije],
	PI.Quantity AS [Stanje zaliha na lokaciji],
	(
	SELECT SUM(PI1.Quantity)
	FROM Production.ProductInventory AS PI1
	WHERE P.ProductID = PI1.ProductID
	) AS [Stanje zaliha na svim lokacijama],
	(
	SELECT ISNULL(SUM(SOD1.OrderQty), 0)
	FROM Production.Product AS P1
		INNER JOIN Sales.SalesOrderDetail AS SOD1 ON P1.ProductID = SOD1.ProductID
		INNER JOIN Sales.SalesOrderHeader AS SOH1 ON SOD1.SalesOrderID = SOH1.SalesOrderID
	WHERE YEAR(SOH1.OrderDate) = 2013 AND P.ProductID = P1.ProductID
	) AS [Ukupna prodana kolicina]
FROM Production.Product AS P
	INNER JOIN Production.ProductInventory AS PI ON P.ProductID = PI.ProductID
	INNER JOIN Production.Location AS L ON PI.LocationID = L.LocationID
ORDER BY 5 DESC;


-- 11. Kreirati upit koji prikazuje uposlenike koji obavljaju ulogu predstavnika prodaje a obradili su 125 i više narudžbi i prodali količinski 8000 i više proizvoda. U rezultatima upita prikazati id, ime i prezime uposlenika, ukupan broj narudžbi i ukupan broj prodatih proizvoda. Rezultate sortirati prema ukupnom broju narudžbi u opadajućem redoslijedu. (Northwind) 

USE Northwind;


SELECT
	E.EmployeeID,
	CONCAT(E.FirstName, ' ', E.LastName) AS [Ime i prezime],
	COUNT(*) AS [Broj narudzbi],
	SQ.[Broj proizvoda]
FROM Employees AS E
	INNER JOIN Orders AS O ON E.EmployeeID = O.EmployeeID
	INNER JOIN
	(
	SELECT
		E1.EmployeeID,
		SUM(OD1.Quantity) AS [Broj proizvoda]
	FROM Employees AS E1
		INNER JOIN Orders AS O1 ON E1.EmployeeID = O1.EmployeeID
		INNER JOIN [Order Details] AS OD1 ON O1.OrderID = OD1.OrderID
	WHERE E1.Title = 'Sales Representative'
	GROUP BY E1.EmployeeID, E1.FirstName, E1.LastName
	HAVING SUM(OD1.Quantity) > 8000
	) AS SQ ON E.EmployeeID = SQ.EmployeeID
WHERE E.Title = 'Sales Representative'
GROUP BY E.EmployeeID, E.FirstName, E.LastName, SQ.[Broj proizvoda]
HAVING COUNT(*) > 125
ORDER BY SQ.[Broj proizvoda] DESC;


-- 12. Naći proizvode čijom je prodajom ostvaren najmanji i najveći ukupni promet (uzimajući u obzir i popust), a zatim odrediti razliku između najmanjeg prometa po proizvodu i prosječnog prometa prodaje proizvoda, te najvećeg prometa po proizvodu i prosječnog prometa prodaje proizvoda. Rezultate prikazati zaokružene na dvije decimale. Upit treba sadržavati nazive proizvoda sa njihovim ukupnim prometom te izračunate razlike. (AdventureWorks2017) 

USE AdventureWorks2017;


--		1. NACIN

SELECT 
	Najmanji.Name, 
	Najmanji.[Najmanji promet], 
	Najveci.Name, 
	Najveci.[Najveci promet], 
	Najmanji.[Razlika MIN-AVG], 
	Najveci.[Razlika MAX-AVG]
FROM
	(
	SELECT TOP 1 
			P.Name, 
			CAST(SUM(SOD.LineTotal) AS DECIMAL(18, 2)) AS [Najveci promet],
			CAST(SUM(SOD.LineTotal) -	(
									SELECT AVG(SQ1.[LineTotal sum])
									FROM
										(
										SELECT SUM(SOD.LineTotal) AS [LineTotal sum]
										FROM Production.Product AS P
											INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
										GROUP BY P.ProductID
										) AS SQ1
									) AS DECIMAL(18, 2)) AS [Razlika MAX-AVG]
		FROM Production.Product AS P
			INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
		GROUP BY P.ProductID, P.Name
		ORDER BY 2 DESC
	) AS Najveci
CROSS JOIN
	(
	SELECT TOP 1 
			P.Name, 
			CAST(SUM(SOD.LineTotal) AS DECIMAL(18, 2)) AS [Najmanji promet],
			CAST(SUM(SOD.LineTotal) -	(
									SELECT AVG(SQ1.[LineTotal sum])
									FROM
										(
										SELECT SUM(SOD.LineTotal) AS [LineTotal sum]
										FROM Production.Product AS P
											INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
										GROUP BY P.ProductID
										) AS SQ1
									) AS DECIMAL(18, 2)) AS [Razlika MIN-AVG]
		FROM Production.Product AS P
			INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
		GROUP BY P.ProductID, P.Name
		ORDER BY 2 ASC
	) AS Najmanji




--		2. NACIN

SELECT *
FROM
	(
	SELECT TOP 1 
		P.Name, 
		CAST(SUM(SOD.LineTotal) AS DECIMAL(18, 2)) AS [Najmanji/najveci promet],
		CAST(SUM(SOD.LineTotal) -	(
								SELECT AVG(SQ1.[LineTotal sum])
								FROM
									(
									SELECT SUM(SOD.LineTotal) AS [LineTotal sum]
									FROM Production.Product AS P
										INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
									GROUP BY P.ProductID
									) AS SQ1
								) AS DECIMAL(18, 2)) AS Razlika
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
	GROUP BY P.ProductID, P.Name
	ORDER BY 2 DESC
	) AS Najveci

UNION

SELECT *
FROM
	(
	SELECT TOP 1 
		P.Name, 
		CAST(SUM(SOD.LineTotal) AS DECIMAL(18, 2)) AS [Najmanji/najveci promet],
		CAST(SUM(SOD.LineTotal) -	(
								SELECT AVG(SQ1.[LineTotal sum])
								FROM
									(
									SELECT SUM(SOD.LineTotal) AS [LineTotal sum]
									FROM Production.Product AS P
										INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
									GROUP BY P.ProductID
									) AS SQ1
								) AS DECIMAL(18, 2)) AS Razlika
	FROM Production.Product AS P
		INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
	GROUP BY P.ProductID, P.Name
	ORDER BY 2 ASC
	) AS Najmanji














-- 3. ZADATAK SA VJEZBI
-- Za svaku pojedinačnu godinu u kojima su kreirane narudžbe (izvući godinu iz datuma narudžbe) prikazati ime i prezime (spojeno) prodavača koji je ostvario najveći prihod u toj godini (sa popustom i taksama), naziv proizvoda koji je ostvario najeću prodaju (ukupna prodata količina) i ime i prezime (spojeno) kupca koji je najviše potrošio (sa popustom i taksama) u toj godini. Izlaz sortirati uzlazno po godinama. (AdventureWorks2017)

USE AdventureWorks2017;

SELECT DISTINCT 
	YEAR(SOH.OrderDate) AS Godina, 
	Prodavac.[Ime i prezime] AS [Prodavac sa najvecim prihodima], 
	Proizvod.Name AS [Najvise prodani proizvod]
FROM Sales.SalesOrderHeader AS SOH
	LEFT JOIN
	(
	SELECT SQ2.Godina, SQ3.[Ime i prezime]
	FROM
		(
		SELECT SQ.Godina, MAX(SQ.Prihod) AS [Max prihod]
		FROM
			(
			SELECT YEAR(SOH.OrderDate) AS Godina, CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime], SUM(SOH.TotalDue) AS Prihod
			FROM Sales.SalesOrderHeader AS SOH
				INNER JOIN Sales.SalesPerson AS SP ON SOH.SalesPersonID = SP.BusinessEntityID
				INNER JOIN Person.Person AS P ON SP.BusinessEntityID = P.BusinessEntityID
			GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)
			) AS SQ
		GROUP BY SQ.Godina
		) AS SQ2
		INNER JOIN (
			SELECT YEAR(SOH.OrderDate) AS Godina, CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime], SUM(SOH.TotalDue) AS Prihod
			FROM Sales.SalesOrderHeader AS SOH
				INNER JOIN Sales.SalesPerson AS SP ON SOH.SalesPersonID = SP.BusinessEntityID
				INNER JOIN Person.Person AS P ON SP.BusinessEntityID = P.BusinessEntityID
			GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)
			) AS SQ3
			ON SQ2.[Max prihod] = SQ3.Prihod
	) AS Prodavac ON Prodavac.Godina = YEAR(SOH.OrderDate)

	LEFT JOIN
	(
	SELECT SQ2.Godina, SQ3.Name
	FROM
		(
		SELECT SQ.Godina, MAX(SQ.Prodano) AS [Max prodano]
		FROM
		(
		SELECT YEAR(SOH.OrderDate) AS Godina, P.Name, SUM(SOD.OrderQty) AS Prodano
		FROM Sales.SalesOrderDetail AS SOD
			INNER JOIN Production.Product AS P ON SOD.ProductID = P.ProductID
			INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
		GROUP BY YEAR(SOH.OrderDate), P.Name
		) AS SQ
	GROUP BY SQ.Godina
	) AS SQ2
	INNER JOIN
	(
	SELECT YEAR(SOH.OrderDate) AS Godina, P.Name, SUM(SOD.OrderQty) AS Prodano
	FROM Sales.SalesOrderDetail AS SOD
		INNER JOIN Production.Product AS P ON SOD.ProductID = P.ProductID
		INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
	GROUP BY YEAR(SOH.OrderDate), P.Name
	) AS SQ3 ON SQ2.[Max prodano] = SQ3.Prodano
	) AS Proizvod ON Proizvod.Godina = YEAR(SOH.OrderDate)
ORDER BY 1;