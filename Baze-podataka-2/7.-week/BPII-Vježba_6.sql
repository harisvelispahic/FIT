--Uvodni zadaci
--PRIKAZATI PROSJECNA REDOVNA NETO PRIMANJA OD 10 UPOSLENIKA SA NAJVECIM NETO PRIMANJIMA U 2018 GODINI (JEDNA ĆELIJA). UKOLIKO SU UPOSLENICI IMALI VIŠE UPLATA NA NIVOU 2018 GODINE PRVENSTVENO JE POTREBNO POJEDINAČNO ZA SVAKOG OD NJIH ODREDITI PROJEČNU REDOVNU NETO ISPLATU.

--FIRST STEP
--PRVO PROVJERAVAMO DA LI SU UPOSLENICI IMALI VIŠE ISPLATA U 2018 GODINI
USE prihodi
SELECT O.OsobaID, O.Ime, RP.Neto, RP.Mjesec
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
ORDER BY 1

--SECOND STEP
-- UKOLIKO JE BAREM JEDNA OSOBA IMALA VIŠE PRIHODA PO MJESECIMA MORAMO RAČUNATI PROSJEK PO UPOSLENICIMA
SELECT O.OsobaID, AVG(RP.Neto) 'Prosjecni prihodi po uposleniku'
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
GROUP BY O.OsobaID
ORDER BY 1

--THIRD STEP
--NAKON ŠTO SMO IZRAČUNALI PROSJEČNE VRIJEDNOSTI PRIMANJA ZA SVAKU OD OSOBA SADA PRISTUPAMO RAČUNANJU PROSJEČNE VRIJEDNOSTI PRIMANJA TOP 10 OSOBA
SELECT TOP 10 O.OsobaID, AVG(RP.Neto) 'Prosjecni prihodi po uposleniku'
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
GROUP BY O.OsobaID
ORDER BY 2 DESC

--FOURTH STEP
--SADA VRIJEDNOSTI KOJE SMO DOBILI PROSLIJEDIMO UPITU, I NAŠ UPIT POSTAJE PODUPIT
SELECT AVG(PODQ.[Prosjecni prihodi po uposleniku])
FROM(SELECT TOP 10 O.OsobaID, AVG(RP.Neto) 'Prosjecni prihodi po uposleniku'
		FROM Osoba AS O
		INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
		WHERE RP.Godina=2018
		GROUP BY O.OsobaID
		ORDER BY 2 DESC) AS PODQ
-- FINISH
SELECT CAST(AVG(A.[Prosjek po osobama]) AS DECIMAL (18,2)) 'Prosjek prihoda za top 10 uposlenika'
FROM(SELECT TOP 10 O.OsobaID, AVG(RP.Neto) 'Prosjek po osobama'
		FROM Osoba AS O
		INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
		WHERE RP.Godina=2018
		GROUP BY O.OsobaID
		ORDER BY 2 DESC) AS A

--PRIHODI
--KREIRATI UPIT KOJIM JE POTREBNO PRIKAZATI ID, IME I PREZIME UPOSLENIKA, PLATU IZ 2018 GODINE (UZETI PROSJEK UKOLIKO JE UPOSLENIK IMAO VIŠE ISPLATA), TE RAZLIKU PLATE I PROSJEČNE PLATE SVIH UPOSLENIKA U 2018 GODINI(ZA SVAKOG UPOSLENIKA PRVO IZRAČUNATI PROSJEČNU PLATU PA TEK NAKON TOGA ZAJEDNIČKI PROSJEK). REZULTATE UPITA SORTIRATI PREMA RAZLICI U OPADAJUĆEM REDOSLIJEDU.

--FIRST STEP
--PRIKAZATI SVE DO DIJELA UPOTREBE PODUPITA
SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek po osobama'
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
GROUP BY O.OsobaID, O.Ime, O.PrezIme

--SECOND STEP 
--IZRAČUNATI U NOVOM UPITU PROSJEČNU PLATU SVIH UPOSLENIKA U 2018 GODINI
SELECT AVG(PODQ.[Prosjek po osobama])
FROM(SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek po osobama'
		FROM Osoba AS O
		INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
		WHERE RP.Godina=2018
		GROUP BY O.OsobaID, O.Ime, O.PrezIme) AS PODQ

--THIRD STEP 
--KOPIRATI PRETHODNO KREIRANI UPIT, ZATIM UPIT IZ SECOND STEPA STAVITI U ZAGRADE I DODATI U SELECT DIO
SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Plata',
AVG(RP.Neto) - (SELECT AVG(PODQ.[Prosjek po osobama])
				 FROM(SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek po osobama'
						FROM Osoba AS O INNER JOIN RedovniPrihodi AS RP
						ON O.OsobaID=RP.OsobaID
						WHERE RP.Godina=2018
						GROUP BY O.OsobaID, O.Ime, O.PrezIme) AS PODQ) 'Razlika'
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
GROUP BY O.OsobaID, O.Ime, O.PrezIme
--LAST STEP
SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Plata',
AVG(RP.Neto) - (SELECT AVG(PODQ.[Prosjek po osobama])
					FROM(SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek po osobama'
							FROM Osoba AS O
							INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
							WHERE RP.Godina=2018
							GROUP BY O.OsobaID, O.Ime, O.PrezIme) AS PODQ) 'Razlika'
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
GROUP BY O.OsobaID, O.Ime, O.PrezIme
ORDER BY 5 DESC

--PRIHODI
--KREIRATI UPIT KOJI PRIKAZUJE ONE UPOSLENIKE(Id, ime i prezime) ČIJA SU PROSJEČNA NETO PRIMANJA U 2018 GODINI MANJA OD PROSJEKA PLATE SVIH UPOSLENIKA U 2018

--FIRST STEP 
SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek po osobama'
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
GROUP BY O.OsobaID, O.Ime, O.PrezIme

--SECOND STEP 
SELECT AVG(PODQ.[Prosjek po osobama])
FROM(SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek po osobama'
		FROM Osoba AS O
		INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
		WHERE RP.Godina=2018
		GROUP BY O.OsobaID, O.Ime, O.PrezIme) AS PODQ

--THIRD STEP KOMBINOVATI PRETHODNA DVA UPITA
SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek po osobama'
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
GROUP BY O.OsobaID, O.Ime, O.PrezIme
HAVING AVG(RP.Neto) < 
(SELECT AVG(PODQ.[Prosjek po osobama])
	FROM(SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto) 'Prosjek po osobama'
			FROM Osoba AS O
			INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
			WHERE RP.Godina=2018
			GROUP BY O.OsobaID, O.Ime, O.PrezIme) AS PODQ)


--NETAČAN NAČIN JER PRETHODNO NISMO IZRAČUNALI PROSJEK REDOVNIH PRIMANJA PO OSOBAMA
SELECT O.OsobaID, O.Ime, O.PrezIme, AVG(RP.Neto)
FROM Osoba AS O
INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
WHERE RP.Godina=2018
GROUP BY O.OsobaID, O.Ime, O.PrezIme
HAVING AVG(RP.Neto) <
(SELECT AVG(RP.Neto) 'PROSJEK'
	FROM Osoba AS O
	INNER JOIN RedovniPrihodi AS RP ON O.OsobaID=RP.OsobaID
	WHERE RP.Godina=2018)

--NORTHWIND
--KREIRATI UPIT KOJI PRIKAZUJE ONE UPOSLENIKE (IME I PREZIME) KOJI IMAJU MANJE GODINA OD PROSJEKA STAROSTI SVIH UPOSLENIKA U KOLEKTIVU

--FIRST STEP
USE Northwind
SELECT CONCAT(E.FirstName, ' ', E.LastName) 'Ime i prezime', DATEDIFF(YEAR, E.BirthDate, GETDATE())
FROM Employees AS E

--SECOND STEP
--IZRAČUNATI PROSJEK
SELECT AVG(DATEDIFF(YEAR, E.BirthDate, GETDATE()))
 FROM Employees AS E

--FINAL STEP
USE Northwind
SELECT CONCAT(E.FirstName, ' ', E.LastName) 'Ime i prezime', DATEDIFF(YEAR, E.BirthDate, GETDATE())
FROM Employees AS E
WHERE DATEDIFF(YEAR, E.BirthDate, GETDATE()) < 
(SELECT AVG(DATEDIFF(YEAR, E.BirthDate, GETDATE()))
  FROM Employees AS E)

--EXIST OPERATOR
--KREIRATI UPIT KOJIM ĆE SE PRIKAZATI SAMO ONI KUPCI KOJI NISU KREIRALI NITI JEDNU NARUDŽBU

 USE Northwind
 SELECT C.ContactName
 FROM Customers AS C 
 WHERE NOT EXISTS (SELECT * FROM Orders AS O WHERE C.CustomerID=O.CustomerID)

--KREIRATI UPIT KOJI ĆE PRIKAZATI PO 2 NAJSTARIJIH UPOSLENIKA IZ AMERIKE I VELIKE BRITANIJE. UPITOM JE POTREBNO PRIKAZATI IME, PREZIME, STAROST I DRŽAVU IZ KOJE DOLAZI (NORTHWIND)
 
 USE Northwind
 SELECT *
 FROM(SELECT TOP 2 E.FirstName, E.LastName, DATEDIFF(YEAR,E.BirthDate, GETDATE()) 'Starost', E.Country
		FROM Employees AS E
		WHERE E.Country LIKE 'USA'
		ORDER BY 3 DESC) AS A
 UNION
 SELECT *
 FROM(SELECT TOP 2 E.FirstName, E.LastName, DATEDIFF(YEAR,E.BirthDate, GETDATE()) 'Starost', E.Country
		FROM Employees AS E
		WHERE E.Country LIKE 'UK'
 ORDER BY 3 DESC) AS B

--Vježba 6 :: Zadaci


--1.	Prikazati sve osobe koje nemaju prihode, niti vanredne, ni redovne. (Prihodi)  
USE prihodi
SELECT O.OsobaID, o.Ime
FROM Osoba AS O
WHERE NOT EXISTS  (SELECT VP.OsobaID
				   FROM VanredniPrihodi AS VP
					WHERE VP.OsobaID=O.OsobaID) AND NOT EXISTS (SELECT RP.OsobaID
																FROM RedovniPrihodi AS RP
																WHERE RP.OsobaID=O.OsobaID)


--ILI

SELECT O.OsobaID
FROM Osoba AS O
LEFT JOIN VanredniPrihodi AS VP
ON VP.OsobaID=O.OsobaID
WHERE VP.OsobaID IS NULL
INTERSECT
SELECT O.OsobaID
FROM Osoba AS O
LEFT JOIN RedovniPrihodi AS RP
ON RP.OsobaID=O.OsobaID
WHERE RP.OsobaID IS NULL 

--ILI

SELECT O.OsobaID
FROM Osoba AS O
LEFT JOIN VanredniPrihodi AS VP
ON VP.OsobaID=O.OsobaID
LEFT JOIN RedovniPrihodi AS RP ON RP.OsobaID = O.OsobaID
WHERE VP.OsobaID IS NULL AND RP.OsobaID IS NULL

--2.	Prikazati ID narudžbe, ID proizvoda i prodajnu cijenu, te razliku podajne cijene u odnosu na prosječnu vrijednost prodajne cijene za sve stavke. Rezultat sortirati prema vrijednosti razlike u rastućem redoslijedu.  (Northwind) 
USE Northwind
SELECT OD.OrderID, OD.ProductID, OD.UnitPrice, 
(SELECT AVG(OD.UnitPrice) FROM [Order Details] AS OD) 'Prosjecna vrijednost', 
OD.UnitPrice - (SELECT AVG(OD.UnitPrice) FROM [Order Details] AS OD) 'Razlika'
FROM [Order Details] AS OD
ORDER BY 5 

--3.	Za sve proizvode kojih ima na stanju dati prikaz njihovog id-a, naziva, stanja zaliha, te razliku stanja zaliha proizvoda u odnosu na prosječnu vrijednost stanja za sve proizvode u tabeli. Rezultat sortirati prema vrijednosti razlike u opadajućem redoslijedu. (Northwind) 
SELECT P.ProductID, P.ProductName, P.UnitsInStock, 
P.UnitsInStock -(SELECT AVG(P.UnitsInStock)	FROM Products AS P)
FROM Products AS P
WHERE P.UnitsInStock>0

--4.	Prikazati po 5 najstarijih zaposlenika muškog, i ženskog spola uz navođenje sljedećih podataka: spojeno ime i prezime, datum rođenja, godine starosti, opis posla koji obavlja, spol. Konačne rezultate sortirati prema spolu rastućim, a zatim prema godinama starosti opadajućim redoslijedom. (AdventureWorks2017) 
USE AdventureWorks2017
SELECT *
FROM
(SELECT TOP 5 CONCAT(P.FirstName,' ',P.LastName) 'Ime i prezime', E.BirthDate,
	DATEDIFF(YEAR, E.BirthDate, GETDATE()) 'Starost', E.JobTitle, E.Gender
	FROM HumanResources.Employee AS E
	INNER JOIN Person.Person AS P ON E.BusinessEntityID=P.BusinessEntityID
	WHERE E.Gender='F'
	ORDER BY 3 DESC) AS PODQ1
UNION
SELECT *
FROM
(SELECT TOP 5 CONCAT(P.FirstName,' ',P.LastName) 'Ime i prezime', E.BirthDate,
	DATEDIFF(YEAR, E.BirthDate, GETDATE()) 'Starost', E.JobTitle, E.Gender
	FROM HumanResources.Employee AS E 
	INNER JOIN Person.Person AS P ON E.BusinessEntityID=P.BusinessEntityID
	WHERE E.Gender='M'
	ORDER BY 3 DESC) AS PODQ2
ORDER BY PODQ1.Gender, PODQ1.Starost DESC

--5.	Prikazati 3 zaposlenika koji su u braku i 3 koja nisu a obavljaju poslove menadžera uz navođenje sljedećih podataka: opis posla koji obavlja, datum zaposlenja, bračni status i staž. Ako osoba nije u braku plaća dodatni porez (upitom naglasiti to), inače ne plaća. Konačne rezultate sortirati prema bračnom statusu rastućim, a zatim prema stažu opadajućim redoslijedom. (AdventureWorks2017) 
SELECT TOP 3 E.JobTitle, E.HireDate, E.MaritalStatus, 
DATEDIFF(YEAR, E.HireDate, GETDATE()) 'Godine staza', 'Placa dodatni porez' Porez
FROM HumanResources.Employee AS E
WHERE E.JobTitle LIKE '%manager%' AND E.MaritalStatus ='S'
UNION
SELECT TOP 3 E.JobTitle, E.HireDate, E.MaritalStatus, 
DATEDIFF(YEAR, E.HireDate, GETDATE()) 'Godine staza', 'Ne placa' Porez
FROM HumanResources.Employee AS E
WHERE E.JobTitle LIKE '%manager%' AND E.MaritalStatus ='M'
ORDER BY 3, 4 DESC

--6.	Prikazati po 5 najstarijih zaposlenika koje se nalaze na prvom ili četvrtom organizacionom nivou. Grupe se prave u zavisnosti od polja EmailPromotion. Prvu grupu će činiti oni čija vrijednost u pomenutom polju je 0, zatim drugu će činiti oni sa vrijednosti 1, dok treću sa vrijednosti 2. Za svakog zaposlenika potrebno je prikazati spojeno ime i prezime, organizacijski nivo na kojem se nalazi, te da li prima email promocije. Pored ovih polja potrebno je uvesti i polje pod nazivom „Prima“ koje će sadržavati poruke: Ne prima (ukoliko je EmailPromotion = 0), Prima selektirane (ukoliko je EmailPromotion = 1) i Prima (ukoliko je EmailPromotion = 2). Konačne rezultate sortirati prema organizacijskom nivou i dodatno uvedenom polju. (AdventureWorks2017)
SELECT *
FROM
	(SELECT TOP 5 CONCAT(PP.FirstName, ' ', PP.LastName) 'Ime i prezime', E.OrganizationLevel, PP.EmailPromotion, DATEDIFF(YEAR, E.BirthDate, GETDATE()) 'Starost', 'Ne prima' Prima
	FROM HumanResources.Employee AS E
	INNER JOIN Person.Person AS PP ON E.BusinessEntityID=PP.BusinessEntityID
	WHERE (E.OrganizationLevel=1 OR E.OrganizationLevel=4) AND PP.EmailPromotion=0
	ORDER BY 4 DESC) AS A
UNION 
SELECT *
FROM
	(SELECT TOP 5 CONCAT(PP.FirstName, ' ', PP.LastName) 'Ime i prezime', E.OrganizationLevel, PP.EmailPromotion, 
	DATEDIFF(YEAR, E.BirthDate, GETDATE()) 'Starost', 'Prima selektirane' Prima
	FROM HumanResources.Employee AS E
	INNER JOIN Person.Person AS PP ON E.BusinessEntityID=PP.BusinessEntityID
	WHERE (E.OrganizationLevel=1 OR E.OrganizationLevel=4) AND PP.EmailPromotion=1
	ORDER BY 4 DESC) AS B
UNION 
SELECT *
FROM
	(SELECT TOP 5 CONCAT(PP.FirstName, ' ', PP.LastName) 'Ime i prezime', E.OrganizationLevel, PP.EmailPromotion, DATEDIFF(YEAR,	E.BirthDate, GETDATE()) 'Starost','Prima email promocije' Prima
	FROM HumanResources.Employee AS E
	INNER JOIN Person.Person AS PP ON E.BusinessEntityID=PP.BusinessEntityID
	WHERE (E.OrganizationLevel=1 OR E.OrganizationLevel=4) AND PP.EmailPromotion=2
	ORDER BY 4 DESC) AS C
ORDER BY 2 ,4 

--7.	Prikazati id narudžbe, datum narudžbe i datum isporuke za narudžbe koje su isporučene na područje Kanade u 7. mjesecu 2014. godine. Uzeti u obzir samo narudžbe koje nisu plaćene kreditnom karticom. Datume formatirati na način (dd.mm.yyyy). (AdventureWorks2017)  
SELECT SOH.SalesOrderID, FORMAT(SOH.OrderDate,'dd.MM.yyyy') 'Order date', 
FORMAT(SOH.ShipDate,'dd.MM.yyyy') 'Ship date', SOH.ShipDate
FROM Sales.SalesOrderHeader AS SOH
INNER JOIN Sales.SalesTerritory AS ST ON ST.TerritoryID=SOH.TerritoryID
WHERE ST.Name LIKE 'Canada' AND YEAR(SOH.ShipDate)=2014 AND MONTH(SOH.ShipDate)=7 AND SOH.CreditCardID IS NULL
--ILI
SELECT SOH.SalesOrderID, FORMAT(SOH.OrderDate,'dd.MM.yyyy') 'Order date', 
FORMAT(SOH.ShipDate,'dd.MM.yyyy') 'Ship date', SOH.ShipDate
FROM Sales.SalesOrderHeader AS SOH
INNER JOIN Person.Address AS A ON SOH.ShipToAddressID=A.AddressID
INNER JOIN Person.StateProvince AS SPP ON A.StateProvinceID=SPP.StateProvinceID
INNER JOIN Sales.SalesTerritory AS ST ON SPP.TerritoryID=ST.TerritoryID
WHERE ST.Name LIKE 'Canada' AND YEAR(SOH.ShipDate)=2014 AND MONTH(SOH.ShipDate)=7 AND SOH.CreditCardID IS NULL

--8.	Kreirati upit koji prikazuje minimalnu, maksimalnu i prosječnu vrijednost narudžbe bez uračunatog popusta po mjesecima u 2013. godini (datum narudžbe). Rezultate sortirati po mjesecima u rastućem redoslijedu, te vrijednosti zaokružiti na dvije decimale. (AdventureWorks2017) 
SELECT PODQ.Mjesec, AVG(PODQ.[Vrijednost narudžbe bez popusta]) 'Prosjek', 
MIN(PODQ.[Vrijednost narudžbe bez popusta]) 'Minimalna',
MAX(PODQ.[Vrijednost narudžbe bez popusta]) 'Maksimalna'
FROM (
	SELECT SOH.SalesOrderID, MONTH(SOH.OrderDate) 'Mjesec', 
	ROUND(SUM(SOD.UnitPrice*SOD.OrderQty),2) 'Vrijednost narudžbe bez popusta'
	FROM Sales.SalesOrderDetail AS SOD
	INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID=SOH.SalesOrderID
	WHERE YEAR(SOH.OrderDate)=2013
	GROUP BY SOH.SalesOrderID, MONTH(SOH.OrderDate)
	) AS PODQ
GROUP BY PODQ.Mjesec
ORDER BY 1

--9.	Kreirati upit koji prikazuje ime i prezime, korisničko ime (sve iza znaka „\“ u koloni LoginID), dužinu korisničkog imena, opis posla koji obavljaju, datum zaposlenja (dd.mm.yyyy), starost i staž zaposlenika. Uslov je da se prikaže 10 najstarijih zaposlenika koji obavljaju bilo koju ulogu menadžera. (AdventureWorks2017) 
SELECT TOP 10 CONCAT(PP.FirstName, ' ',PP.LastName) 'Ime i prezime', 
RIGHT(E.LoginID, CHARINDEX('\',REVERSE(E.LoginID))-1) 'Korisnicko ime', 
LEN(RIGHT(E.LoginID, CHARINDEX('\',REVERSE(E.LoginID))-1)) 'Dužina korisnickog imena', 
E.JobTitle, 
FORMAT(E.HireDate,'dd.MM.yyyy') 'Datum zaposlenja', 
DATEDIFF(YEAR,E.BirthDate,GETDATE()) 'Starost', 
DATEDIFF(YEAR, E.HireDate,GETDATE()) 'Staž'
FROM Person.Person AS PP
INNER JOIN HumanResources.Employee AS E ON E.BusinessEntityID=PP.BusinessEntityID
WHERE E.JobTitle LIKE '%Manager%'
ORDER BY 6 DESC

--10.	Kreirati upit koji prikazuje naziv modela i opis proizvoda. Uslov je da naziv modela sadrži riječ „Mountain“, i da je jezik na kojem su pohranjeni podaci engleski. (AdventureWorks2017) 
SELECT PM.Name,PD.Description
FROM Production.ProductModel AS PM
INNER JOIN Production.ProductModelProductDescriptionCulture AS PMPDC ON PM.ProductModelID=PMPDC.ProductModelID
INNER JOIN Production.ProductDescription AS PD ON PD.ProductDescriptionID=PMPDC.ProductDescriptionID
INNER JOIN Production.Culture AS C ON C.CultureID=PMPDC.CultureID
WHERE C.Name LIKE 'English' AND PM.Name LIKE '%Mountain%'

--11.	Kreirati upit koji prikazuje id proizvoda, naziv i cijenu proizvoda(ListPrice), te ukupnu količinu proizvoda na zalihama po lokacijama. Uzeti u obzir samo proizvode koji pripadaju kategoriji „Bikes“. Izlaz sortirati po ukupnoj količini u opadajućem redoslijedu. (AdventureWorks2017) 
SELECT PP.ProductID, PP.Name, PP.ListPrice, PL.Name 'Lokacija', SUM(PI.Quantity) 'Stanje zaliha'
FROM Production.Product AS PP
INNER JOIN Production.ProductInventory AS PI ON PP.ProductID=PI.ProductID
INNER JOIN Production.Location AS PL ON PI.LocationID=PL.LocationID
INNER JOIN Production.ProductSubcategory AS PS ON PP.ProductSubcategoryID=PS.ProductSubcategoryID
INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID=PC.ProductCategoryID
WHERE PC.Name LIKE 'Bikes'
GROUP BY PP.ProductID, PP.Name, PP.ListPrice, PL.Name
ORDER BY 5 DESC

--12.	Kreirati upit koji prikazuje ukupno ostvarenu zaradu po zaposleniku, za robu isporuèenu na podruèje Evrope, u januaru mjesecu 2014. godine. Lista treba da sadrži ime i prezime zaposlenika, datum zaposlenja (dd.mm.yyyy), mail adresu, te ukupnu ostvarenu zaradu (bez popusta) zaokruženu na dvije decimale. Izlaz sortirati po zaradi u opadajuæem redoslijedu. (AdventureWorks2017)   
SELECT CONCAT(PP.FirstName, ' ', PP.LastName) 'Ime i prezime zaposlenika', FORMAT(E.HireDate,'dd.MM.yyyy') 'Datum zaposlenja',E.HireDate,EA.EmailAddress,SUM(SOD.UnitPrice*SOD.OrderQty)'Ukupna zarada'
FROM HumanResources.Employee AS E
INNER JOIN Person.Person AS PP ON E.BusinessEntityID=PP.BusinessEntityID
INNER JOIN Person.EmailAddress AS EA ON PP.BusinessEntityID=EA.BusinessEntityID
INNER JOIN Sales.SalesPerson AS SP ON E.BusinessEntityID=SP.BusinessEntityID
INNER JOIN Sales.SalesOrderHeader AS SOH ON SOH.SalesPersonID=SP.BusinessEntityID
INNER JOIN Sales.SalesOrderDetail AS SOD ON SOD.SalesOrderID=SOH.SalesOrderID
INNER JOIN Person.Address AS A ON SOH.ShipToAddressID=A.AddressID
INNER JOIN Person.StateProvince AS SPP ON A.StateProvinceID=SPP.StateProvinceID
INNER JOIN Sales.SalesTerritory AS ST ON SPP.TerritoryID=ST.TerritoryID
WHERE ST.[Group]='Europe' AND YEAR(SOH.ShipDate)=2014 AND MONTH(SOH.ShipDate)=1
GROUP BY CONCAT(PP.FirstName, ' ', PP.LastName),
FORMAT(E.HireDate,'dd.MM.yyyy'), E.HireDate, EA.EmailAddress
ORDER BY [Ukupna zarada] DESC

--ILI

SELECT PP.FirstName + ' '+ PP.LastName 'Ime i prezime zaposlenika', FORMAT(E.HireDate,'dd.MM.yyyy') 'Datum zaposlenja',E.HireDate,EA.EmailAddress,SUM(SOD.UnitPrice*SOD.OrderQty)'Ukupna zarada'
FROM HumanResources.Employee AS E
INNER JOIN Person.Person AS PP ON E.BusinessEntityID=PP.BusinessEntityID
INNER JOIN Person.EmailAddress AS EA ON PP.BusinessEntityID=EA.BusinessEntityID
INNER JOIN Sales.SalesPerson AS SP ON E.BusinessEntityID=SP.BusinessEntityID
INNER JOIN Sales.SalesOrderHeader AS SOH ON SOH.SalesPersonID=SP.BusinessEntityID
INNER JOIN Sales.SalesOrderDetail AS SOD ON SOD.SalesOrderID=SOH.SalesOrderID
INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID=ST.TerritoryID
WHERE ST.[Group]='Europe' AND YEAR(SOH.ShipDate)=2014 AND MONTH(SOH.ShipDate)=1
GROUP BY PP.FirstName + ' '+ PP.LastName,FORMAT(E.HireDate,'dd.MM.yyyy'),E.HireDate,EA.EmailAddress
ORDER BY [Ukupna zarada] DESC