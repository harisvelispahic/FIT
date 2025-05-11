--FUNKCIJE ZA RAD SA STRINGOVIMA
SELECT LEFT('Softverski inzinjering',2)  --REZULTAT: So
SELECT RIGHT('Softverski inzinjering',11)  --REZULTAT: inzinjering
SELECT CHARINDEX(' ','Sofrverski inzinjering') --REZULTAT: 11
SELECT PATINDEX('%[0-9]%','FITCC2022') --REZULTAT 6
SELECT SUBSTRING('Sofrverski inzinjering',11+1,11) --REZULTAT: inzinjering
SELECT UPPER('Sofrverski inzinjering') --REZULTAT: SOFTVERSKI INZINJERING
SELECT LOWER('Sofrverski inzinjering') --REZULTAT: softverski inzinjering
SELECT LEN('Sofrverski inzinjering') --REZULTAT: 22
SELECT REPLACE('Sofrverski inzinjering','i','XY') --REZULTAT:SofrverskXY XYnzXYnjerXYng
SELECT STUFF('Softverski inzinjering',3,2,'XY') --REZULTAT: SoXYverski inzinjering
SELECT CONVERT(NVARCHAR,122)+'.' --122.
SELECT CONCAT(122, '.')
SELECT CAST(122 AS NVARCHAR)+'.' --122.
SELECT REVERSE('Softverski inzinjering') --REZULTAT: gnirejnizni iksrevtfoS0

--Vježba 4 :: Zadaci 
--1.	Iz tabele HumanResources.Employee baze AdventureWorks2017 iz kolone LoginID izvući ime uposlenika. 
--STEP 1
SELECT E.LoginID
FROM AdventureWorks2017.HumanResources.Employee AS E
--STEP 2
SELECT E.LoginID, SUBSTRING(E.LoginID,16+1,10)
FROM AdventureWorks2017.HumanResources.Employee AS E
--STEP 3
SELECT E.LoginID, SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, 10)
FROM AdventureWorks2017.HumanResources.Employee AS E
--STEP 4
SELECT E.LoginID, 
SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)-1) 'Ime uposlenika'
FROM AdventureWorks2017.HumanResources.Employee AS E

--UKOLIKO SE S DESNE STRANE NALAZI 1 ILI VIŠE BROJEVA 
SELECT E.LoginID, LEFT(SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID)-CHARINDEX('\', E.LoginID)), PATINDEX('%[0-9]%', SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID)-CHARINDEX('\', E.LoginID)))-1)
FROM AdventureWorks2017.HumanResources.Employee AS E
--2.	Kreirati upit koji prikazuje podatke o zaposlenicima. Lista treba da sadrži sljedeće kolone: ID uposlenika, korisničko ime i novu lozinku: 
--Uslovi su sljedeći:  • Za korisničko ime potrebno je koristiti kolonu LoginID (tabela Employees). Npr. LoginID zaposlenika sa imenom i prezimenom 'Mary Gibson' je adventureworks\mary0. Korisničko ime zaposlenika je sve što se nalazi iza znaka \ (backslash) što je u ovom primjeru mary0,  
--•	Nova lozinka se formira koristeći Rowguid zaposlenika na sljedeći način:  Rowguid je potrebno okrenuti obrnuto (npr. dbms2015 -> 5102smbd) i nakon toga preskačemo prvih 5 i uzimamo narednih 7 karaktera  
--•	Sljedeći korak jeste da iz dobivenog stringa počevši od drugog karaktera naredna dva zamijenimo sa X# (npr. ako je dobiveni string dbms2015 izlaz će biti dX#s2015)  
--STEP 1
SELECT E.BusinessEntityID, 
SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)) 'Korisnicko ime'
FROM AdventureWorks2017.HumanResources.Employee AS E
WHERE SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)) LIKE 'mary%'
--STEP 2
SELECT E.BusinessEntityID, 
SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)) 'Korisnicko ime',
E.rowguid, REVERSE(E.rowguid)
FROM AdventureWorks2017.HumanResources.Employee AS E
WHERE SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)) LIKE 'mary%'
--STEP 3
SELECT E.BusinessEntityID, 
SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)) 'Korisnicko ime',
E.rowguid, REVERSE(E.rowguid)
FROM AdventureWorks2017.HumanResources.Employee AS E
--STEP 4
SELECT E.BusinessEntityID, 
SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)) 'Korisnicko ime',
E.rowguid, SUBSTRING(REVERSE(E.rowguid),6,7)
FROM AdventureWorks2017.HumanResources.Employee AS E
--STEP 5
SELECT E.BusinessEntityID, 
SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)) 'Korisnicko ime',
STUFF(SUBSTRING(REVERSE(E.rowguid),6,7),2,2,'X#') 'Lozinka'
FROM AdventureWorks2017.HumanResources.Employee AS E

--RJEŠENJE
SELECT E.BusinessEntityID, 
SUBSTRING(E.LoginID, CHARINDEX('\', E.LoginID)+1, LEN(E.LoginID) - CHARINDEX('\', E.LoginID)) 'Korisnicko ime',
STUFF(SUBSTRING(REVERSE(E.rowguid), 6, 7), 2, 2, 'X#') 'Lozinka'
FROM AdventureWorks2017.HumanResources.Employee AS E



--3.	 Iz tabele Sales.Customer baze AdventureWorks2017 iz kolone AccountNumber izvući broj pri čemu je potrebno broj prikazati bez vodećih nula. 
--a) dohvatiti sve zapise 
--b) dohvatiti one zapise kojima je unijet podatak u kolonu PersonID 
--STEP 1
SELECT C.AccountNumber
FROM AdventureWorks2017.Sales.Customer AS C
--STEP 2
SELECT C.AccountNumber, RIGHT(C.AccountNumber,8) 
FROM AdventureWorks2017.Sales.Customer AS C
--STEP 3
SELECT C.AccountNumber, RIGHT(C.AccountNumber,PATINDEX('%[A-Z]%',REVERSE(C.AccountNumber))-1) 
FROM AdventureWorks2017.Sales.Customer AS C
--STEP 4
SELECT C.AccountNumber, RIGHT(C.AccountNumber,PATINDEX('%[A-Z]%',REVERSE(C.AccountNumber))-1), 
PATINDEX('%[A-Z]%',REVERSE(C.AccountNumber)) 
FROM AdventureWorks2017.Sales.Customer AS C
--STEP 5
--RJEŠENJE a
SELECT C.AccountNumber, CAST(RIGHT(C.AccountNumber,PATINDEX('%[A-Z]%',REVERSE(C.AccountNumber))-1) AS INT)
FROM AdventureWorks2017.Sales.Customer AS C

--RJEŠENJE b
SELECT C.AccountNumber, CAST(RIGHT(C.AccountNumber,PATINDEX('%[A-Z]%',REVERSE(C.AccountNumber))-1) AS INT)
FROM AdventureWorks2017.Sales.Customer AS C
WHERE C.PersonID IS NOT NULL

--4.	 Iz tabele Purchasing.Vendor baze AdventureWorks2017 dohvatiti zapise u kojima se podatak u koloni AccountNumber formirao iz prve riječi kolone Name. Npr. dostavljač koji ima id 1492 ne ispunjava definisani uslov, dok dostavljač koji ima id 1494 ispunjava. U rezultatima upita prikazati samo one kolone koje se nalaze u definiciji tabele..
--STEP 1
SELECT V.AccountNumber, V.Name
FROM AdventureWorks2017.Purchasing.Vendor AS V
--STEP 2
SELECT V.AccountNumber, V.Name, 
LEFT(V.AccountNumber, PATINDEX('%[0-9]%', V.AccountNumber)-1)
FROM AdventureWorks2017.Purchasing.Vendor AS V
--STEP 3
SELECT V.AccountNumber, V.Name, 
LEFT(V.AccountNumber, PATINDEX('%[0-9]%', V.AccountNumber)-1), 
LEFT(V.Name, CHARINDEX(' ', V.Name)-1)
FROM AdventureWorks2017.Purchasing.Vendor AS V
--STEP 4
SELECT V.AccountNumber, V.Name, 
LEFT(V.AccountNumber, PATINDEX('%[0-9]%', V.AccountNumber)-1), 
LEFT(V.Name +' ', CHARINDEX(' ', V.Name+' ')-1)
FROM AdventureWorks2017.Purchasing.Vendor AS V
--STEP 5
SELECT V.AccountNumber, V.Name, 
LEFT(V.AccountNumber, PATINDEX('%[0-9]%', V.AccountNumber)-1), 
LEFT(V.Name +' ', CHARINDEX(' ', V.Name+' ')-1)
FROM AdventureWorks2017.Purchasing.Vendor AS V
WHERE LEFT(V.AccountNumber, PATINDEX('%[0-9]%', V.AccountNumber)-1) LIKE LEFT(V.Name +' ', CHARINDEX(' ', V.Name+' ')-1)

-- UPGRADE RJEŠENJA 
SELECT V.AccountNumber, V.Name, 
LEFT(V.AccountNumber, PATINDEX('%[0-9]%', V.AccountNumber)-1), 
IIF(CHARINDEX(' ', V.Name)=0,V.Name,LEFT(V.Name, CHARINDEX(' ', V.Name+' ')-1))
FROM AdventureWorks2017.Purchasing.Vendor AS V
WHERE 
LEFT(V.AccountNumber, PATINDEX('%[0-9]%', V.AccountNumber)-1) LIKE IIF(CHARINDEX(' ', V.Name)=0,V.Name,LEFT(V.Name, CHARINDEX(' ', V.Name+' ')-1))
--LAST STEP
SELECT *
FROM AdventureWorks2017.Purchasing.Vendor AS V
WHERE 
LEFT(V.AccountNumber, PATINDEX('%[0-9]%', V.AccountNumber)-1) LIKE IIF(CHARINDEX(' ', V.Name)=0,V.Name,LEFT(V.Name, CHARINDEX(' ', V.Name+' ')-1))

--5.	 Koristeći bazu Northwind kreirati upit koji će prikazati odvojeno ime i prezime (dobijeno iz kolone ContactName), naziv firme te državu i grad kupca ali samo onih čija zadnja riječ adrese se sastoji od 2 ili 3 cifre. Također, uzeti u obzir samo one kupce koji u polju ContactName imaju dvije riječi. 
--STEP 1
SELECT C.ContactName
FROM Northwind.dbo.Customers AS C
--STEP 2
SELECT C.ContactName, LEFT(C.ContactName,CHARINDEX(' ', C.ContactName)-1)
FROM Northwind.dbo.Customers AS C
--STEP 3
SELECT C.ContactName, LEFT(C.ContactName,CHARINDEX(' ', C.ContactName)-1)Ime, RIGHT(C.ContactName, CHARINDEX(' ',REVERSE(C.ContactName))-1) Prezime, C.CompanyName, C.Country, C.City
FROM Northwind.dbo.Customers AS C
--STEP 4
SELECT C.ContactName, LEFT(C.ContactName,CHARINDEX(' ', C.ContactName)-1)Ime, RIGHT(C.ContactName, CHARINDEX(' ',REVERSE(C.ContactName))-1) Prezime, C.CompanyName, C.Country, C.City, C.Address
FROM Northwind.dbo.Customers AS C
WHERE  LEN(RIGHT(C.Address, CHARINDEX(' ',REVERSE(C.Address))-1)) IN (2,3)
--STEP 5
SELECT C.ContactName, LEFT(C.ContactName,CHARINDEX(' ', C.ContactName)-1)Ime, RIGHT(C.ContactName, CHARINDEX(' ',REVERSE(C.ContactName))-1) Prezime, C.CompanyName, C.Country, C.City, C.Address
FROM Northwind.dbo.Customers AS C
WHERE  LEN(RIGHT(C.Address, CHARINDEX(' ',REVERSE(C.Address))-1)) IN (2,3) AND ISNUMERIC(RIGHT(C.Address, CHARINDEX(' ',REVERSE(C.Address))-1))=1
--STEP 6
SELECT C.ContactName, LEFT(C.ContactName,CHARINDEX(' ', C.ContactName)-1)Ime, RIGHT(C.ContactName, CHARINDEX(' ',REVERSE(C.ContactName))-1) Prezime, C.CompanyName, C.Country, C.City, C.Address
FROM Northwind.dbo.Customers AS C
WHERE LEN(RIGHT(C.Address, CHARINDEX(' ',REVERSE(C.Address))-1)) IN (2,3) AND ISNUMERIC(RIGHT(C.Address, CHARINDEX(' ',REVERSE(C.Address))-1))=1 AND LEN(C.ContactName) - LEN(REPLACE(C.ContactName,' ',''))=1

--6.	Koristeći bazu Northwind u tabeli Customers dodati izračunato polje Spol u koji će se upitom pohraniti vrijednost da li se radi o muškarcu ili ženi (M ili F). Vrijednost na osnovu koje se određuje to o kojem se spolu radi nalazi se u koloni ContactName gdje zadnje slovo prve riječi određuje spol (riječi koje se završavaju slovom a predstavljaju osobe ženskog spola). Nakon testiranja ispravnosti izračunato polje izbrisati iz pomenute tabele.
SELECT C.ContactName, IIF(RIGHT(LEFT(C.ContactName,CHARINDEX(' ', C.ContactName)-1),1) LIKE 'a','F','M')
FROM Northwind.dbo.Customers AS C
 
 ALTER TABLE Northwind.dbo.Customers
 ADD Spol AS IIF(RIGHT(LEFT(ContactName,CHARINDEX(' ', ContactName)-1),1) LIKE 'a','F','M')

 SELECT *
 FROM Northwind.dbo.Customers

 ALTER TABLE Northwind.dbo.Customers
 DROP COLUMN Spol

--7.	Prikazati dobavljače koji su ukupno prodali više od 1000 proizvoda, uzeti u obzir samo one prodavače koji posjeduju web stranicu, u izlazu osim naziva prodavača i prodane količine prikazati i lokaciju web stranice bez www i / (npr. www.google.com/ -> google.com). (AdventureWorks2017)
USE AdventureWorks2017

SELECT V.Name,
	SUBSTRING(V.PurchasingWebServiceURL, 
		CHARINDEX('.', V.PurchasingWebServiceURL)+1, 
		LEN(V.PurchasingWebServiceURL) - CHARINDEX('.', V.PurchasingWebServiceURL) - 1) 'Web lokacija',
	SUM(POD.OrderQty) 'Količina'
FROM Purchasing.PurchaseOrderDetail AS POD
	INNER JOIN Purchasing.PurchaseOrderHeader AS POH ON POD.PurchaseOrderID = POH.PurchaseOrderID
	INNER JOIN Purchasing.Vendor AS V ON POH.VendorID = V.BusinessEntityID
WHERE V.PurchasingWebServiceURL IS NOT NULL
GROUP BY V.Name, V.PurchasingWebServiceURL
HAVING SUM(POD.OrderQty) > 1000

--NADOGRADNJA RJEŠENJA AKO SE POJAVI URL SA VIŠE / (npr. www.google.ba/search/results/page?id=1)
SELECT V.Name,
	LEFT(
	SUBSTRING(
			V.PurchasingWebServiceURL, 
			CHARINDEX('.', V.PurchasingWebServiceURL) + 1,
			LEN(V.PurchasingWebServiceURL) - CHARINDEX('.', V.PurchasingWebServiceURL)
			),
	CHARINDEX('/', 	SUBSTRING(
			V.PurchasingWebServiceURL, 
			CHARINDEX('.', V.PurchasingWebServiceURL) + 1,
			LEN(V.PurchasingWebServiceURL) - CHARINDEX('.', V.PurchasingWebServiceURL)
			)) - 1 
	) 'Web lokacija',
	SUM(POD.OrderQty) 'Količina'
FROM Purchasing.PurchaseOrderDetail AS POD
	INNER JOIN Purchasing.PurchaseOrderHeader AS POH ON POD.PurchaseOrderID = POH.PurchaseOrderID
	INNER JOIN Purchasing.Vendor AS V ON POH.VendorID = V.BusinessEntityID
WHERE V.PurchasingWebServiceURL IS NOT NULL
GROUP BY V.Name, V.PurchasingWebServiceURL
HAVING SUM(POD.OrderQty) > 1000

--8.	Prikazati naziv i broj proizvoda koji imaju 2 ili više dokumenta koji ih opisuju. (AdventureWorks2017)
SELECT P.Name, P.ProductNumber, COUNT(*) 'Broj dokumenata'
FROM Production.Product AS P
	INNER JOIN Production.ProductDocument AS PD ON PD.ProductID = P.ProductID
	INNER JOIN Production.Document AS D ON PD.DocumentNode = D.DocumentNode
GROUP BY P.Name, P.ProductNumber
HAVING COUNT(*) >= 2

--9.	Prikazati ukupnu prodanu količinu proizvoda po kategorijama u 1996. godini za 2, 3 i 4 kvartal, izlaz sortirati silazno po prodanoj količini, i uzeti u obzir samo one kategorije koje su u to vrijeme prodali više od 1000 proizvoda. (Northwind)
USE Northwind

SELECT C.CategoryName, SUM(OD.Quantity) 'Prodana količina'
FROM Categories AS C
	INNER JOIN Products AS P ON P.CategoryID = C.CategoryID
	INNER JOIN [Order Details] AS OD ON OD.ProductID = P.ProductID
	INNER JOIN Orders AS O ON OD.OrderID = O.OrderID
WHERE (DATEPART(QUARTER,O.OrderDate) BETWEEN 2 AND 4) AND YEAR(O.OrderDate) = 1996
GROUP BY C.CategoryName
HAVING SUM(OD.Quantity) > 1000
ORDER BY 2 DESC

--10.	Prikazati imena i prezimena (spojeno) radnika kojima se satnica mijenjala kroz vrijeme. (AdventureWorks2017)
USE AdventureWorks2017

SELECT CONCAT(P.FirstName, ' ', P.LastName, ' ', P.MiddleName) 'Ime i prezime',
	COUNT(*) 'Broj različitih satnica'
FROM Person.Person AS P
	INNER JOIN HumanResources.Employee AS E ON E.BusinessEntityID = P.BusinessEntityID
	INNER JOIN HumanResources.EmployeePayHistory AS EPH ON EPH.BusinessEntityID = E.BusinessEntityID
GROUP BY CONCAT(P.FirstName, ' ', P.LastName, ' ', P.MiddleName)
HAVING COUNT(*) > 1
