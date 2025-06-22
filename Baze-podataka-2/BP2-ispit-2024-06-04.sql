--1.	Kroz SQL kod kreirati bazu podataka sa imenom vašeg broja indeksa.

GO
CREATE DATABASE [2024-06-04]
GO
USE [2024-06-04]

--2.	Kreirati tabelu Kupci, te prilikom kreiranja uraditi insert podataka iz tabele Customers baze Northwind.

SELECT
	*
INTO Kupci
FROM Northwind.dbo.Customers

--3.	(3 boda) Kreirati proceduru sp_insert_customers kojom će se izvršiti insert podataka u tabelu Kupci. OBAVEZNO kreirati testni slučaj.

GO
CREATE OR ALTER PROCEDURE sp_insert_customers
(
	@CustomerID NCHAR(5),
	@CompanyName NVARCHAR(40),
	@ContactName NVARCHAR(30) = NULL,
	@ContactTitle NVARCHAR(30) = NULL,
	@Address NVARCHAR(60) = NULL,
	@City NVARCHAR(15) = NULL,
	@Region NVARCHAR(15) = NULL,
	@PostalCode NVARCHAR(10) = NULL,
	@Country NVARCHAR(15) = NULL,
	@Phone NVARCHAR(24) = NULL,
	@Fax NVARCHAR(24) = NULL
)
AS
BEGIN
	INSERT INTO Kupci
	(
		CustomerID,
		CompanyName,
		ContactName,
		ContactTitle,
		Address,
		City,
		Region,
		PostalCode,
		Country,
		Phone,
		Fax
	)
	VALUES
	(
		@CustomerID,
		@CompanyName, 
		@ContactName,
		@ContactTitle,
		@Address,
		@City,
		@Region,
		@PostalCode,
		@Country,
		@Phone,
		@Fax
	)
END
GO

SELECT * FROM Kupci

exec sp_insert_customers 'ZZZZZ', 'Na Drini turpija'

--4.	(3 boda) Kreirati index koji je ubrzati pretragu po nazivu kompanije kupca i kontakt imenu. OBAVEZNO kreirati testni slučaj.

GO
CREATE INDEX ix_Kupci_CompanyName_ContactName
ON Kupci(CompanyName, ContactName)
GO

SELECT
	*
FROM Kupci AS K
WHERE K.CompanyName LIKE '%p%' AND K.ContactName LIKE 'A%l%'

DROP INDEX ix_Kupci_CompanyName_ContactName ON Kupci

--5.	(5 boda) Kreirati funkciju f_satnice unutar novokreirane baze koja će vraćati podatke u vidu tabele iz baze AdventureWorks2017. Korisniku slanjem parametra satnica će biti ispisani uposlenici (ime, prezime, starost, staž i email) čija je satnica manja od vrijednosti poslanog parametra. Korisniku pored navedenih podataka treba prikazati razliku unesene i stvarne satnice.

GO
CREATE OR ALTER FUNCTION f_satnice
(
	@satnica MONEY
)
RETURNS TABLE
AS
RETURN
	SELECT
		P.FirstName,
		P.LastName,
		DATEDIFF(YEAR, E.BirthDate, GETDATE()) AS Starost,
		DATEDIFF(YEAR, E.HireDate, GETDATE()) AS Staz,
		EA.EmailAddress,
		(@satnica - EPH.Rate) AS Razlika
	FROM AdventureWorks2017.HumanResources.EmployeePayHistory AS EPH
		INNER JOIN AdventureWorks2017.HumanResources.Employee AS E ON EPH.BusinessEntityID = E.BusinessEntityID
		INNER JOIN AdventureWorks2017.Person.Person AS P ON E.BusinessEntityID = P.BusinessEntityID
		INNER JOIN AdventureWorks2017.Person.EmailAddress AS EA ON P.BusinessEntityID = EA.BusinessEntityID
	WHERE EPH.Rate < @satnica
GO

SELECT * FROM f_satnice(150)

--6.	(6 boda) Prikazati ime i prezime kupaca čiji je ukupan iznos potrošnje(ukupna vrijednost sa troškovima prevoza i taksom) veći od prosječnog ukupnog iznosa potrošnje svih kupaca. U obzir uzeti samo narudžbe koje su isporučene kupcima. (AdventureWorks2019)

GO
USE AdventureWorks2017


SELECT
	P.FirstName,
	P.LastName,
	SUM(SOH.TotalDue) AS [Ukupna potrosnja]
FROM Person.Person AS P	
	INNER JOIN Sales.Customer AS C ON P.BusinessEntityID = C.PersonID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
WHERE SOH.ShipDate IS NOT NULL
GROUP BY P.FirstName, P.LastName
HAVING SUM(SOH.TotalDue) >
							(
							SELECT
								AVG(SOH.TotalDue)
							FROM Sales.SalesOrderHeader AS SOH
							)

--7.	(6 bodova) Prikazati prosječnu vrijednost od svih kreiranih narudžbi bez popusta (jedno polje) (AdventureWorks2019)

SELECT
	AVG(SOH.SubTotal) AS Prosjek
FROM Sales.SalesOrderHeader AS SOH

WHERE NOT EXISTS
	(
	SELECT 1
	FROM Sales.SalesOrderDetail AS SOD
	WHERE SOD.SalesOrderID = SOH.SalesOrderID AND SOD.UnitPriceDiscount > 0
	)

--8.	(9 bodova) Prikazati naziv odjela na kojima trenutno radi najmanje, te naziv odjela na kojem radi najviše uposlenika starijih od 50 godina. Dodatni uslov je da odjeli pripadaju grupama proizvodnje, te prodaje i marketinga. (Adventureworks 2019)

SELECT
	*
FROM
	(
	SELECT TOP 1
		D.Name
	FROM HumanResources.Department AS D
		INNER JOIN HumanResources.EmployeeDepartmentHistory AS EDH ON D.DepartmentID = EDH.DepartmentID
		INNER JOIN HumanResources.Employee AS E ON EDH.BusinessEntityID = E.BusinessEntityID
	WHERE 
		D.GroupName IN ('Manufacturing', 'Sales and Marketing') AND
		DATEDIFF(YEAR, E.BirthDate, GETDATE()) > 50
	GROUP BY D.Name
	ORDER BY COUNT(*) DESC
	) AS SQ1

UNION ALL

SELECT
	*
FROM
	(
	SELECT TOP 1 WITH TIES
		D.Name
	FROM HumanResources.Department AS D
		INNER JOIN HumanResources.EmployeeDepartmentHistory AS EDH ON D.DepartmentID = EDH.DepartmentID
		INNER JOIN HumanResources.Employee AS E ON EDH.BusinessEntityID = E.BusinessEntityID
	WHERE 
		D.GroupName IN ('Manufacturing', 'Sales and Marketing') AND
		DATEDIFF(YEAR, E.BirthDate, GETDATE()) > 50
	GROUP BY D.Name
	ORDER BY COUNT(*) ASC
	) AS SQ2

--9.	(8 bodova) Prikazati najprodavaniji proizvod za svaku godinu pojedinačno. Ulogu najprodavanijeg proizvoda ima onaj koji je u najvećoj količini prodat.(Northwind)

GO
USE Northwind


SELECT
	SQ.Godina,
	SQ.ProductName
FROM
	(
	SELECT
		YEAR(O.OrderDate) AS Godina,
		P.ProductName,
		SUM(OD.Quantity) AS Kolicina,
		ROW_NUMBER() OVER (PARTITION BY YEAR(O.OrderDate) ORDER BY SUM(OD.Quantity) DESC) AS rn
	FROM Products AS P
		INNER JOIN [Order Details] AS OD ON P.ProductID = OD.ProductID
		INNER JOIN Orders AS O ON OD.OrderID = O.OrderID
	GROUP BY YEAR(O.OrderDate), P.ProductName
	) AS SQ
WHERE SQ.rn = 1

--10.	(8 bodova) Prikazati ukupan broj narudžbi i ukupnu količinu proizvoda za svaku od teritorija pojedinačno. Uslov je da je ukupna količina manja od 3000 a popust nije odobren za te stavke, te ukupan broj narudžbi 1000 i više. (Adventureworks 2019)
 
GO
USE AdventureWorks2017


SELECT
	ST.TerritoryID,
	COUNT(DISTINCT SOH.SalesOrderID),
	SUM(SOD.OrderQty)
FROM Sales.SalesOrderHeader AS SOH
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
WHERE SOD.UnitPriceDiscount = 0
GROUP BY ST.TerritoryID
HAVING COUNT(DISTINCT SOH.SalesOrderID) >= 1000
ORDER BY 1 ASC