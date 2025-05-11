SELECT LEFT('Softverski inzenjering', 2);
SELECT RIGHT('Softverski inzenjering', 11);
-- odsijece string s lijeve ili desne strane zadani broj karaktera

SELECT CHARINDEX(' ', ' Softverski inzenjering');
-- saljemo karakter koji trazimo

SELECT LEFT('Softverski inzenjering', CHARINDEX(' ', 'Softverski inzenjering') - 1);

SELECT PATINDEX('%[0-9]%', 'Softverski1inzenjering');

SELECT PATINDEX('%[a-z]%', 'Softverski inzenjering');

-- trazi pattern u tekstu, vraca index

SELECT SUBSTRING('Softverski inzenjering', CHARINDEX(' ', 'Softverski inzenjering') + 1, LEN('Softverski inzenjering'));
-- vraca substring od stringa 1.argument sa indexa 2. argument, duzine 3. argument

SELECT LEN('Softverski inzenjering');
-- duzina stringa

SELECT UPPER('Softverski inzenjering');
SELECT LOWER('Softverski inzenjering');

SELECT REPLACE('Softverski inzenjering  ', ' ', '\');
-- mijenja svaki drugi argument sa trecim

SELECT STUFF('Softverski inzenjering', 12, 3, '123');
-- zamijeni od mjesta koje smo rekli da zamijeni (2. argument), duzinu (3. argument), stringom (4. argument)

SELECT REVERSE('Softverski inzenjering');

SELECT CAST('00123' AS INT);

SELECT CONVERT(NVARCHAR, 123); -- stariji nacin



--1. Iz tabele HumanResources.Employee baze AdventureWorks2017 iz kolone LoginID izvući ime uposlenika.

USE AdventureWorks2017;

SELECT E.LoginID, SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID) + 1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID) - 1) 'Ime'
FROM HumanResources.Employee AS E;

SELECT E.LoginID,
	LEFT(
		SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID) + 1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)),
		PATINDEX('%[0-9]%', SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID) + 1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)))
	) 'Ime'
FROM HumanResources.Employee AS E;

--2. Kreirati upit koji prikazuje podatke o zaposlenicima. Lista treba da sadrži sljedeće kolone: ID uposlenika, korisničko ime i novu lozinku: Uslovi su sljedeći:
--• Za korisničko ime potrebno je koristiti kolonu LoginID (tabela Employees). Npr. LoginID zaposlenika sa identifikacijskim brojem 23 je adventureworks\mary0. Korisničko ime zaposlenika je sve što se nalazi iza znaka \ (backslash) što je u ovom primjeru mary0
--• Nova lozinka se formira koristeći Rowguid zaposlenika na sljedeći način: Rowguid je potrebno okrenuti obrnuto (npr. dbms2015 -> 5102smbd) i nakon toga preskačemo prvih 5 i uzimamo narednih 7 karaktera. Sljedeći korak jeste da iz dobijenog stringa počevši od drugog karaktera naredna dva zamijenimo sa X# (npr. ako je dobiveni string dbms2015 izlaz će biti dX#s2015)

SELECT *
FROM HumanResources.Employee AS E;


SELECT E.BusinessEntityID, REVERSE(E.rowguid), 
	LEFT(
		SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID) + 1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)),
		PATINDEX('%[0-9]%', SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID) + 1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)))
	) 'Korisnicko ime',
	STUFF(LEFT(SUBSTRING(REVERSE(E.rowguid), 6, LEN(E.rowguid)), 7), 2, 2, 'X#')
FROM HumanResources.Employee AS E;

--3. Iz tabele Sales.Customer baze AdventureWorks2017 iz kolone AccountNumber izvući broj pri čemu je potrebno broj prikazati bez vodećih nula.
--a) dohvatiti sve zapise
--b) dohvatiti one zapise kojima je unijet podatak u kolonu PersonID

-- a)
SELECT C.AccountNumber,
	RIGHT(C.AccountNumber, LEN(C.AccountNumber) + 1 - PATINDEX('%[1-9]%', C.AccountNumber))
FROM Sales.Customer AS C;


-- b)
SELECT C.AccountNumber,
	RIGHT(C.AccountNumber, LEN(C.AccountNumber) + 1 - PATINDEX('%[1-9]%', C.AccountNumber))
FROM Sales.Customer AS C
WHERE C.PersonID IS NOT NULL;

--4. Iz tabele Purchasing.Vendor baze AdventureWorks2017 dohvatiti zapise u kojima se podatak u koloni AccountNumber formirao iz prve riječi kolone Name. Npr. dostavljač koji ima id 1492 ne ispunjava definisani uslov, dok dostavljač koji ima id 1494 ispunjava. U rezultatima upita prikazati samo one kolone koje se nalaze u definiciji tabele.

--SELECT UPPER(IIF(SUBSTRING(V.Name, 0, CHARINDEX(' ', V.Name)) = '', V.Name, SUBSTRING(V.Name, 0, CHARINDEX(' ', V.Name)))), 
--	*, 
--	SUBSTRING(V.AccountNumber, 0, LEN(V.AccountNumber) - 3)
--FROM Purchasing.Vendor AS V
--WHERE UPPER(IIF(SUBSTRING(V.Name, 0, CHARINDEX(' ', V.Name)) = '', V.Name, SUBSTRING(V.Name, 0, CHARINDEX(' ', V.Name)))) = SUBSTRING(V.AccountNumber, 0, LEN(V.AccountNumber) - 3);

SELECT *
FROM Purchasing.Vendor AS V
WHERE UPPER(IIF(SUBSTRING(V.Name, 0, CHARINDEX(' ', V.Name)) = '', V.Name, SUBSTRING(V.Name, 0, CHARINDEX(' ', V.Name)))) = SUBSTRING(V.AccountNumber, 0, LEN(V.AccountNumber) - 3);

--5. Koristeći bazu Northwind kreirati upit koji će prikazati odvojeno ime i prezime (dobijeno iz kolone ContactName), naziv firme te državu i grad kupca ali samo onih čija zadnja riječ adrese se sastoji od 2 ili 3 cifre. Također, uzeti u obzir samo one kupce koji u polju ContactName imaju dvije riječi.

USE Northwind;

SELECT *,
	SUBSTRING(C.ContactName, 0, CHARINDEX(' ', C.ContactName)) 'Ime',
	SUBSTRING(C.ContactName, CHARINDEX(' ', C.ContactName) + 1, LEN(C.ContactName)) 'Prezime',
	C.CompanyName,
	C.City,
	SUBSTRING(C.Address, LEN(C.Address) - CHARINDEX(' ', REVERSE(C.Address)) + 2, LEN(C.Address))
FROM Customers AS C
WHERE (SUBSTRING(C.Address, LEN(C.Address) - CHARINDEX(' ', REVERSE(C.Address)) + 2, LEN(C.Address)) LIKE '[0-9][0-9]' OR SUBSTRING(C.Address, LEN(C.Address) - CHARINDEX(' ', REVERSE(C.Address)) + 2, LEN(C.Address)) LIKE '[0-9][0-9][0-9]') AND -- USLOV ZA DVIJE RIJECI

--6. Koristeći bazu Northwind u tabeli Customers dodati izračunato polje Spol u koji će se upitom pohraniti vrijednost da li se radi o muškarcu ili ženi (M ili F). Vrijednost na osnovu koje se određuje to o kojem se spolu radi nalazi se u koloni ContactName gdje zadnje slovo prve riječi određuje spol (riječi koje se završavaju slovom a predstavljaju osobe ženskog spola). Nakon testiranja ispravnosti izračunato polje izbrisati iz pomenute tabele.


--7. Prikazati dobavljače koji su ukupno prodali više od 1000 proizvoda, uzeti u obzir samo one prodavače koji posjeduju web stranicu, u izlazu osim naziva prodavača i prodane količine prikazati i lokaciju web stranice bez www i / (npr. www.google.com/ -> google.com). (AdventureWorks2017)

USE AdventureWorks2017;

SELECT V.Name, 
	SUBSTRING(V.PurchasingWebServiceURL, 5, LEN(V.PurchasingWebServiceURL) - 5) 'URL',
	SUM(POD.OrderQty) 'Prodana količina'
FROM Purchasing.Vendor AS V
	INNER JOIN Purchasing.PurchaseOrderHeader AS POH ON V.BusinessEntityID = POH.VendorID
	INNER JOIN Purchasing.PurchaseOrderDetail AS POD ON POH.PurchaseOrderID = POD.PurchaseOrderID
WHERE V.PurchasingWebServiceURL IS NOT NULL
GROUP BY V.Name, V.PurchasingWebServiceURL
HAVING SUM(POD.OrderQty) > 1000;

-- hardkodirano :DDDDDDDDD

--8. Prikazati naziv i broj proizvoda koji imaju 2 ili više dokumenta koji ih opisuju. (AdventureWorks2017)

SELECT P.Name, COUNT(*)
FROM Production.Product AS P
	INNER JOIN Production.ProductDocument AS PD ON P.ProductID = PD.ProductID
	INNER JOIN Production.Document AS D ON PD.DocumentNode = D.DocumentNode
GROUP BY P.Name
HAVING COUNT(*) >= 2;

--9. Prikazati ukupnu prodanu količinu proizvoda po kategorijama u 1996. godini za 2, 3 i 4 kvartal, izlaz sortirati silazno po prodanoj količini, i uzeti u obzir samo one kategorije koje su u to vrijeme prodali više od 1000 proizvoda. (Northwind)

USE Northwind;

SELECT C.CategoryName, SUM(OD.Quantity) 'Prodana kolicina'
FROM Products AS P
	INNER JOIN Categories AS C ON P.CategoryID = C.CategoryID
	INNER JOIN [Order Details] AS OD ON P.ProductID = OD.ProductID
	INNER JOIN Orders AS O ON OD.OrderID = O.OrderID
WHERE YEAR(O.OrderDate) = 1996 AND DATEPART(QUARTER, O.OrderDate) <> 1
GROUP BY C.CategoryName
HAVING SUM(OD.Quantity) > 1000
ORDER BY SUM(OD.Quantity) DESC;

--10. Prikazati imena i prezimena (spojeno) radnika kojima se satnica mijenjala kroz vrijeme. (AdventureWorks2017)

USE AdventureWorks2017;

SELECT *
FROM Person.Person;