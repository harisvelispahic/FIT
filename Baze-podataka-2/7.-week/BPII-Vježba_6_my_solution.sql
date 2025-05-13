--*******--


USE prihodi;

SELECT AVG(SUBQ.TOP10) 'Prosjek'
FROM
	(SELECT TOP 10 AVG(RP.Neto) 'TOP10'
	FROM RedovniPrihodi AS RP
	WHERE RP.Godina = 2018
	GROUP BY RP.OsobaID
	ORDER BY 1 DESC) AS SUBQ;


SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek', 
	AVG(RP.Neto) - (
		SELECT AVG(RP.Neto)
		FROM RedovniPrihodi AS RP
		WHERE RP.Godina = 2018
		) 'Razlika'
FROM Osoba AS O
	INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
WHERE RP.Godina = 2018
GROUP BY O.OsobaID, O.Ime, O.PrezIme
ORDER BY Razlika DESC;


	(SELECT AVG(RP.Neto) 'Prosjek'
	FROM RedovniPrihodi AS RP
	WHERE RP.Godina = 2018
	GROUP BY RP.OsobaID)

SELECT O.OsobaID, O.Ime, O.PrezIme
FROM Osoba AS O
	INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
WHERE RP.Godina = 2018
GROUP BY O.OsobaID, O.Ime, O.PrezIme
HAVING AVG(RP.Neto) <
						(SELECT AVG(RP.Neto)
						FROM RedovniPrihodi AS RP
						WHERE RP.Godina = 2018)
-- ***

USE Northwind;

SELECT E.FirstName, E.LastName, DATEDIFF(YEAR, E.BirthDate, GETDATE())
FROM Employees AS E
WHERE DATEDIFF(YEAR, E.BirthDate, GETDATE()) <
	(SELECT AVG(DATEDIFF(YEAR, E.BirthDate, GETDATE()))
	FROM Employees AS E)



SELECT C.ContactName
FROM Customers AS C
WHERE NOT EXISTS 
				(SELECT 1
				FROM Orders AS O
				WHERE O.CustomerID = C.CustomerID)

				
SELECT E.FirstName, E.LastName
FROM Employees AS E
WHERE NOT EXISTS 
				(SELECT 1
				FROM Orders AS O
				WHERE O.EmployeeID = E.EmployeeID)



-- SET OPERATORI
--	UNION
--	UNION ALL
--	INTERSECT
--	EXCEPT

SELECT *
FROM
	(SELECT TOP 2 E.FirstName, E.LastName, DATEDIFF(YEAR, E.BirthDate, GETDATE()) 'Starost', E.Country
	FROM Employees AS E
	WHERE E.Country LIKE 'USA'
	ORDER BY 3 DESC) AS USA

UNION

SELECT *
FROM
	(SELECT TOP 2 E.FirstName, E.LastName, DATEDIFF(YEAR, E.BirthDate, GETDATE()) 'Starost', E.Country
	FROM Employees AS E
	WHERE E.Country LIKE 'UK'
	ORDER BY 3 DESC) AS UK


-- UNION VS UNION ALL
--	UNION NE UZIMA DUPLIKATE, UNION ALL UZIMA SVE REDOVE
--	INTERSECT - PRESJEK - REDOVI I U JEDNOM, I DRUGOM UPITU
--	EXCEPT - RAZLIKA - SVE STO JE U PRVOJ, A NIJE U DRUGOJ




--*******--



-- 1. Prikazati sve osobe koje nemaju prihode, niti vanredne, ni redovne. (Prihodi) 

USE prihodi;

SELECT *
FROM Osoba AS O
WHERE NOT EXISTS
				(SELECT 1
				FROM RedovniPrihodi AS RP
				WHERE RP.OsobaID = O.OsobaID) AND NOT EXISTS
															(SELECT 1
															FROM VanredniPrihodi AS VP
															WHERE VP.OsobaID = O.OsobaID)



--2. Prikazati ID narudžbe, ID proizvoda i prodajnu cijenu, te razliku prodajne cijene u odnosu na prosječnu vrijednost prodajne cijene za sve stavke. Rezultat sortirati prema vrijednosti razlike u rastućem redoslijedu. (Northwind) 

USE Northwind;

SELECT OD.OrderID, OD.ProductID, OD.UnitPrice, 
	OD.UnitPrice - (
	SELECT AVG(OD.UnitPrice)
	FROM [Order Details] AS OD
	) AS Razlika
FROM [Order Details] AS OD
ORDER BY Razlika ASC

--3. Za sve proizvode kojih ima na stanju dati prikaz njihovog id-a, naziva, stanja zaliha, te razliku stanja zaliha proizvoda u odnosu na prosječnu vrijednost stanja za sve proizvode u tabeli. Rezultat sortirati prema vrijednosti razlike u opadajućem redoslijedu. (Northwind) 

USE Northwind;

SELECT P.ProductID, P.ProductName, P.UnitsInStock,
	P.UnitsInStock - (
	SELECT AVG(P.UnitsInStock)
	FROM Products AS P
	) AS Razlika
FROM Products AS P
ORDER BY Razlika DESC

--4. Prikazati po 5 najstarijih zaposlenika muškog, i ženskog spola uz navoðenje sljedećih podataka: spojeno ime i prezime, datum roðenja, godine starosti, opis posla koji obavlja, spol. Konačne rezultate sortirati prema spolu rastućim, a zatim prema godinama starosti opadajućim redoslijedom. (AdventureWorks2017) 

USE AdventureWorks2017;

SELECT *
FROM
	(SELECT TOP 5 CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime], E.BirthDate, DATEDIFF(YEAR, E.BirthDate, GETDATE()) AS Starost, E.JobTitle, E.Gender
	FROM Person.Person AS P
		INNER JOIN HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
	WHERE E.Gender = 'M'
	ORDER BY Starost DESC) AS Male

UNION

SELECT *
FROM
	(SELECT TOP 5 CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime], E.BirthDate, DATEDIFF(YEAR, E.BirthDate, GETDATE()) AS Starost, E.JobTitle, E.Gender
	FROM Person.Person AS P
		INNER JOIN HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
	WHERE E.Gender = 'F'
	ORDER BY Starost DESC) AS Female
ORDER BY Gender, Starost

--5. Prikazati 3 zaposlenika koji su u braku i 3 koja nisu a obavljaju poslove menadžera uz navoðenje sljedećih podataka: opis posla koji obavlja, datum zaposlenja, bračni status i staž. Ako osoba nije u braku plaća dodatni porez (upitom naglasiti to), inače ne plaća. Konačne rezultate sortirati prema bračnom statusu rastućim, a zatim prema stažu opadajućim redoslijedom. (AdventureWorks2017) 

USE AdventureWorks2017;

SELECT *
FROM
	(SELECT TOP 3 E.JobTitle, E.HireDate, E.MaritalStatus, DATEDIFF(YEAR, E.HireDate, GETDATE()) 'Staz', IIF(E.MaritalStatus = 'M', 'Ne placa', 'Placa') AS Porez
	FROM HumanResources.Employee AS E
	ORDER BY E.MaritalStatus ASC) AS Married
UNION
SELECT *
FROM
	(SELECT TOP 3 E.JobTitle, E.HireDate, E.MaritalStatus, DATEDIFF(YEAR, E.HireDate, GETDATE()) 'Staz',  IIF(E.MaritalStatus = 'S', 'Placa', 'Ne placa') AS Porez
	FROM HumanResources.Employee AS E
	ORDER BY E.MaritalStatus DESC) AS Single
ORDER BY MaritalStatus ASC, Staz DESC

--6. Prikazati po 5 najstarijih zaposlenika koje se nalaze na prvom ili četvrtom organizacionom nivou. Grupe se prave u zavisnosti od polja EmailPromotion. Prvu grupu će činiti oni čija vrijednost u pomenutom polju je 0, zatim drugu će činiti oni sa vrijednosti 1, dok treću sa vrijednosti 2. Za svakog zaposlenika potrebno je prikazati spojeno ime i prezime, organizacijski nivo na kojem se nalazi, te da li prima email promocije. Pored ovih polja potrebno je uvesti i polje pod nazivom „Prima“ koje će sadržavati poruke: Ne prima (ukoliko je EmailPromotion = 0), Prima selektirane (ukoliko je EmailPromotion = 1) i Prima (ukoliko je EmailPromotion = 2). Konačne rezultate sortirati prema organizacijskom nivou i dodatno uvedenom polju. (AdventureWorks2017)

USE AdventureWorks2017;

SELECT *
FROM (
	SELECT TOP 5 CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime], E.OrganizationLevel, P.EmailPromotion, 'Ne prima' AS Prima
	FROM HumanResources.Employee AS E
		INNER JOIN Person.Person AS P ON E.BusinessEntityID = P.BusinessEntityID
	WHERE E.OrganizationLevel IN (1, 4) AND P.EmailPromotion = 0
	ORDER BY DATEDIFF(YEAR, E.BirthDate, GETDATE()) DESC
	) AS Ne_prima
UNION
SELECT *
FROM (
	SELECT TOP 5 CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime], E.OrganizationLevel, P.EmailPromotion, 'Prima selektirane' AS Prima
	FROM HumanResources.Employee AS E
		INNER JOIN Person.Person AS P ON E.BusinessEntityID = P.BusinessEntityID
	WHERE E.OrganizationLevel IN (1, 4) AND P.EmailPromotion = 1
	ORDER BY DATEDIFF(YEAR, E.BirthDate, GETDATE()) DESC
	) AS Prima_selektirane
UNION
SELECT *
FROM (
	SELECT TOP 5 CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime], E.OrganizationLevel, P.EmailPromotion, 'Prima' AS Prima
	FROM HumanResources.Employee AS E
		INNER JOIN Person.Person AS P ON E.BusinessEntityID = P.BusinessEntityID
	WHERE E.OrganizationLevel IN (1, 4) AND P.EmailPromotion = 2
	ORDER BY DATEDIFF(YEAR, E.BirthDate, GETDATE()) DESC
	) AS Prima
ORDER BY 2, 4

--7. Prikazati id narudžbe, datum narudžbe i datum isporuke za narudžbe koje su isporučene na područje Kanade u 7. mjesecu 2014. godine. Uzeti u obzir samo narudžbe koje nisu plaćene kreditnom karticom. Datume formatirati na način (dd.mm.yyyy).(AdventureWorks2017) 

SELECT *
FROM Sales.SalesTerritory;

SELECT SOH.SalesOrderID, SOH.OrderDate, FORMAT(SOH.ShipDate, 'dd.MM.yyyy')
FROM Sales.SalesOrderHeader AS SOH
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
WHERE SOH.CreditCardID IS NULL AND ST.Name = 'Canada' AND MONTH(SOH.ShipDate) = 7 AND YEAR(SOH.ShipDate) = 2014 

--8. Kreirati upit koji prikazuje minimalnu, maksimalnu i prosječnu vrijednost narudžbe bez uračunatog popusta po mjesecima u 2013. godini (datum narudžbe). Rezultate sortirati po mjesecima u rastućem redoslijedu, te vrijednosti zaokružiti na dvije decimale. (AdventureWorks2017) 

SELECT MONTH(SOH.OrderDate) AS [Month],
	ROUND(MIN(SOD.UnitPrice * SOD.OrderQty), 2) AS MinVrijednost,
	ROUND(MAX(SOD.UnitPrice * SOD.OrderQty), 2) AS MaxVrijednost,
	ROUND(AVG(SOD.UnitPrice * SOD.OrderQty), 2) AS ProsjecnaVrijednost
FROM Sales.SalesOrderHeader AS SOH
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
WHERE YEAR(SOH.OrderDate) = 2013
GROUP BY MONTH(SOH.OrderDate)
ORDER BY [Month]

--9. Kreirati upit koji prikazuje ime i prezime, korisničko ime (sve iza znaka „\“ u koloni LoginID), dužinu korisničkog imena, opis posla koji obavljaju, datum zaposlenja (dd.mm.yyyy), starost i staž zaposlenika. Uslov je da se prikaže 10 najstarijih zaposlenika koji obavljaju bilo koju ulogu menadžer (AdventureWorks2017) 

SELECT TOP 10
	P.FirstName, 
	P.LastName, 
	SUBSTRING(E.LoginID, 17, LEN(E.LoginID) - 16) AS [Korisnicko ime], 
	LEN(SUBSTRING(E.LoginID, 17, LEN(E.LoginID) - 16)) AS [Duzina korisnickog imena], 
	E.JobTitle, 
	FORMAT(E.HireDate, 'dd.MM.yyyy') AS [Datum zaposlenja],
	DATEDIFF(YEAR, E.BirthDate, GETDATE()) AS Starost,
	DATEDIFF(YEAR, E.HireDate, GETDATE()) AS Staz
FROM HumanResources.Employee AS E
	INNER JOIN Person.Person AS P ON E.BusinessEntityID = P.BusinessEntityID
WHERE LOWER(E.JobTitle) LIKE '%manager%'
ORDER BY Starost DESC

--10. Kreirati upit koji prikazuje naziv modela i opis proizvoda. Uslov je da naziv modela sadrži riječ „Mountain“, i da je jezik na kojem su pohranjeni podaci engleski. (AdventureWorks2017)

SELECT PM.Name, PD.Description
FROM Production.Product AS P
	INNER JOIN Production.ProductModel AS PM ON P.ProductModelID = PM.ProductModelID
	INNER JOIN Production.ProductModelProductDescriptionCulture AS PMPDC ON PM.ProductModelID = PMPDC.ProductModelID
	INNER JOIN Production.ProductDescription AS PD ON PMPDC.ProductDescriptionID = PD.ProductDescriptionID
WHERE LOWER(PM.Name) LIKE '%mountain%' AND PMPDC.CultureID = 'en';


--11. Kreirati upit koji prikazuje id proizvoda, naziv i cijenu proizvoda(ListPrice), te ukupnu količinu proizvoda na zalihama po lokacijama. Uzeti u obzir samo proizvode koji pripadaju kategoriji „Bikes“. Izlaz sortirati po ukupnoj količini u opadajućem redoslijedu. (AdventureWorks2017) 

SELECT P.ProductID, P.Name, P.ListPrice, SUM(PI.Quantity) AS Zalihe
FROM Production.Product AS P
	INNER JOIN Production.ProductInventory AS PI ON P.ProductID = PI.ProductID
	INNER JOIN Production.Location AS L ON PI.LocationID = L.LocationID
	INNER JOIN Production.ProductSubCategory AS PSC ON P.ProductSubcategoryID = PSC.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PSC.ProductCategoryID = PC.ProductCategoryID
WHERE PC.Name = 'Bikes'
GROUP BY P.ProductID, P.Name, P.ListPrice, L.Name
ORDER BY Zalihe DESC

--12. Kreirati upit koji prikazuje ukupno ostvarenu zaradu po zaposleniku, za robu isporučenu na područje Evrope, u januaru mjesecu 2014. godine. Lista treba da sadrži ime i prezime zaposlenika, datum zaposlenja (dd.mm.yyyy), mail adresu, te ukupnu ostvarenu zaradu (bez popusta) zaokruženu na dvije decimale. Izlaz sortirati po zaradi u opadajućem redoslijedu. (AdventureWorks2017)

SELECT 
	P.FirstName, 
	P.LastName, 
	FORMAT(E.HireDate, 'dd.MM.yyyy') AS [Datum zaposlenja], 
	EA.EmailAddress, 
	ROUND(SUM(SOD.OrderQty * SOD.UnitPrice), 2) AS [Ukupna zarada]
FROM Person.Person AS P
	INNER JOIN HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
	INNER JOIN Person.EmailAddress AS EA ON P.BusinessEntityID = EA.BusinessEntityID
	INNER JOIN Sales.SalesPerson AS SP ON E.BusinessEntityID = SP.BusinessEntityID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON SP.BusinessEntityID = SOH.SalesPersonID
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
WHERE 
	ST.[Group] = 'Europe' AND 
	YEAR(SOH.ShipDate) = 2014 AND 
	MONTH(SOH.ShipDate) = 1
GROUP BY P.FirstName, P.LastName, E.HireDate, EA.EmailAddress
ORDER BY [Ukupna zarada] DESC