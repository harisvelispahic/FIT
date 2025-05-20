-- 1. Kreirati bazu View_ i aktivirati je.

GO
CREATE DATABASE View_;
GO
USE View_;
GO
-- 2. U bazi View_ kreirati pogled v_Employee sljedeće strukture:
-- - prezime i ime uposlenika kao polje ime i prezime,
-- - teritoriju i
-- - regiju koju pokrivaju
-- Uslov je da se dohvataju uposlenici koji su stariji od 60 godina. (Northwind)

GO
CREATE VIEW v_Employee
AS
SELECT
	CONCAT(E.FirstName, ' ', E.LastName) AS [Ime i prezime],
	T.TerritoryDescription AS [Teritorija],
	R.RegionDescription AS [Regija]
FROM Northwind.dbo.Employees AS E
	INNER JOIN Northwind.dbo.EmployeeTerritories AS ET ON E.EmployeeID = ET.EmployeeID
	INNER JOIN Northwind.dbo.Territories AS T ON ET.TerritoryID = T.TerritoryID
	INNER JOIN Northwind.dbo.Region AS R ON T.RegionID = R.RegionID
WHERE DATEDIFF(YEAR, E.BirthDate, GETDATE()) > 60
GO

SELECT * FROM v_Employee

-- 3. Koristeći pogled v_Employee prebrojati broj teritorija koje uposlenik pokriva po jednoj regiji. Rezultate sortirati prema broju teritorija u opadajućem redoslijedu, te prema prezimenu i imenu u rastućem redoslijedu.

SELECT
	vE.[Ime i prezime],
	vE.Regija,
	COUNT(*) AS [# teritorija]
FROM v_Employee AS vE
GROUP BY vE.[Ime i prezime], vE.Regija
ORDER BY 3 DESC, 1 ASC

-- 4. Kreirati pogled v_Sales sljedeće strukture: (Adventureworks2017)
-- - Id kupca
-- - Ime i prezime kupca
-- - Godinu narudžbe
-- - Vrijednost narudžbe bez troškova prevoza i takse

GO
CREATE VIEW v_Sales
AS
SELECT
	C.CustomerID,
	CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime kupca],
	YEAR(SOH.OrderDate) AS [Godina narudzbe],
	SOH.SubTotal
FROM AdventureWorks2017.Sales.Customer AS C
	INNER JOIN AdventureWorks2017.Person.Person AS P ON C.PersonID = P.BusinessEntityID
	INNER JOIN AdventureWorks2017.Sales.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
GO

-- 5. Koristeći pogled v_Sales dati pregled sumarno ostvarenih prometa po osobi i godini.

SELECT
	vS.CustomerID,
	vS.[Ime i prezime kupca],
	vS.[Godina narudzbe],
	SUM(vS.SubTotal) AS [Promet sumarno]
FROM v_Sales AS vS
GROUP BY vS.CustomerID, vS.[Ime i prezime kupca], vS.[Godina narudzbe]

-- 6. Koristeći pogled v_Sales dati pregled zapisa iz 2013. godine u kojima je vrijednost narudžbe u intervalu 10% u odnosu na prosječnu vrijednost narudžbe iz 2013 godine. Pregled treba da sadrži ime i prezime kupca i vrijednost narudžbe, sortirano prema vrijednosti narudžbe obrnuto abecedno.

DECLARE @Prosjek2013 DECIMAL(18,2);
SET @Prosjek2013 =	(
					SELECT AVG(vS.SubTotal)
					FROM v_Sales AS vS
					WHERE vS.[Godina narudzbe] = 2013
					)

SELECT
	vS.[Ime i prezime kupca],
	vS.SubTotal
FROM v_Sales AS vS
WHERE vS.[Godina narudzbe] = 2013 AND vS.SubTotal BETWEEN (@Prosjek2013 * 0.9) AND (@Prosjek2013 * 1.1)
ORDER BY 2 DESC, 1 DESC
GO

-- 7. Kreirati tabelu Zaposlenici te prilikom kreiranja uraditi insert podataka iz tabele Employees baze Northwind.

SELECT *
INTO Zaposlenici
FROM Northwind.dbo.Employees AS E

SELECT *
FROM Zaposlenici

-- 8. Kreirati pogled v_Zaposlenici koji će dati pregled ID-a, imena, prezimena i države zaposlenika.

GO
CREATE VIEW v_Zaposlenici
AS
SELECT
	Z.EmployeeID,
	Z.FirstName,
	Z.LastName,
	Z.Country
FROM Zaposlenici AS Z
GO

-- 9. Modificirati prethodno kreirani pogled te onemogućiti unos podataka kroz pogled za uposlenike koji ne dolaze iz Amerike ili Velike Britanije.

GO
CREATE OR ALTER VIEW v_Zaposlenici
AS
SELECT
	Z.EmployeeID,
	Z.FirstName,
	Z.LastName,
	Z.Country
FROM Zaposlenici AS Z
WHERE Z.Country IN ('USA', 'UK')
WITH CHECK OPTION
GO

-- 10. Testirati prethodno modificiran view unosom ispravnih i neispravnih podataka (napisati 2 testna slučaja).

INSERT INTO v_Zaposlenici
VALUES ('Ime', 'Prezime', 'UK')

SELECT * FROM v_Zaposlenici


INSERT INTO v_Zaposlenici
VALUES ('Ime', 'Prezime', 'BIH')

SELECT * FROM v_Zaposlenici

-- 11. Koristeći tabele Purchasing.Vendor i Purchasing.PurchaseOrderDetail kreirati v_Purchasing pogled sljedeće strukture:
--		- Name iz tabele Vendor
--		- PurchaseOrderID iz tabele Purchasing.PurchaseOrderDetail
--		- DueDate iz tabele Purchasing.PurchaseOrderDetail
--		- OrderQty iz tabele Purchasing.PurchaseOrderDetail
--		- UnitPrice iz tabele Purchasing.PurchaseOrderDetail
--		- ukupno kao proizvod OrderQty i UnitPrice
-- Uslov je da se dohvate samo oni zapisi kod kojih DueDate pripada 1. ili 3. kvartalu.
-- (AdventureWorks2017)

GO
CREATE VIEW v_Purchasing
AS
SELECT
	V.Name,
	POD.PurchaseOrderID,
	POD.DueDate,
	POD.OrderQty,
	POD.UnitPrice,
	(POD.UnitPrice * POD.OrderQty) AS [Ukupno]
FROM AdventureWorks2017.Purchasing.Vendor AS V
	INNER JOIN AdventureWorks2017.Purchasing.PurchaseOrderHeader AS POH ON V.BusinessEntityID = POH.VendorID
	INNER JOIN AdventureWorks2017.Purchasing.PurchaseOrderDetail AS POD ON POH.PurchaseOrderID = POD.PurchaseOrderID
WHERE DATEPART(QUARTER, POD.DueDate) IN (1, 3)
GO

-- 12. Koristeći pogled v_Purchasing dati pregled svih dobavljača čiji je ukupan broj stavki u okviru jedne narudžbe jednak minimumu, odnosno maksimumu ukupnog broja stavki po dostavljačima i purchaseOrderID.
-- Pregled treba imati sljedeću strukturu:
--		- Name
--		- PurchaseOrderID
--		- Ukupan broj stavki

GO
CREATE VIEW v_Max_Stavki
AS
SELECT MAX(SQ1.[# stavki]) AS [Broj stavki]
FROM
	(
	SELECT COUNT(*) AS [# stavki]
	FROM v_Purchasing AS vP
	GROUP BY vP.Name, vP.PurchaseOrderID
	) AS SQ1

GO

CREATE VIEW v_Min_Stavki
AS
SELECT MIN(SQ1.[# stavki]) AS [Broj stavki]
FROM
	(
	SELECT COUNT(*) AS [# stavki]
	FROM v_Purchasing AS vP
	GROUP BY vP.Name, vP.PurchaseOrderID
	) AS SQ1
GO


SELECT
	vP.Name,
	vP.PurchaseOrderID,
	COUNT(*) AS [Broj stavki]
FROM v_Purchasing AS vP
GROUP BY vP.Name, vP.PurchaseOrderID
HAVING COUNT(*) IN	(
						(SELECT vMS.[Broj stavki] FROM v_Max_Stavki vMS),
						(SELECT vMS.[Broj stavki] FROM v_Min_Stavki vMS)
					)

-- 13. U bazi View_ kreirati tabele Osoba i Uposlenik. 
-- Strukture tabela su sljedeće:
-- - Osoba
--		OsobaID cjelobrojna varijabla, primarni ključ
--		VrstaOsobe 2 unicode karaktera, obavezan unos
--		Prezime 50 unicode karaktera, obavezan unos
--		Ime 50 unicode karaktera, obavezan unos
-- - Uposlenik
--		UposlenikID cjelobrojna varijabla, primarni ključ
--		NacionalniID 15 unicode karaktera, obavezan unos
--		LoginID 256 unicode karaktera, obavezan unos
--		RadnoMjesto 50 unicode karaktera, obavezan unos
--		DtmZapos datumska varijabla
-- Spoj tabela napraviti prema spoju između tabela Person.Person i HumanResources.Employee baze AdventureWorks2017.

CREATE TABLE Osoba 
(
	OsobaID			INT,
	VrstaOsobe		NVARCHAR(2) NOT NULL,
	Prezime			NVARCHAR(50) NOT NULL,
	Ime				NVARCHAR(50) NOT NULL

	CONSTRAINT PK_Osoba PRIMARY KEY (OsobaID)
)

GO

CREATE TABLE Uposlenik
(
	UposlenikID		INT,
	NacionalniID	NVARCHAR(15) NOT NULL,
	LoginID			NVARCHAR(256) NOT NULL,
	RadnoMjesto		NVARCHAR(50) NOT NULL,
	DtmZapos		DATE

	CONSTRAINT PK_Uposlenik PRIMARY KEY (UposlenikID),
	CONSTRAINT FK_Uposlenik_Osoba FOREIGN KEY (UposlenikID) REFERENCES Osoba(OsobaID)
)

-- 14. Nakon kreiranja tabela u tabelu Osoba kopirati odgovarajuće podatke iz tabele Person.Person, a u tabelu Uposlenik kopirati odgovarajuće zapise iz tabele HumanResources.Employee.

INSERT INTO Osoba(OsobaID, VrstaOsobe, Prezime, Ime)
SELECT P.BusinessEntityID, P.PersonType, P.LastName, P.FirstName
FROM AdventureWorks2017.Person.Person AS P

GO

INSERT INTO Uposlenik(UposlenikID, NacionalniID, LoginID, RadnoMjesto, DtmZapos)
SELECT E.BusinessEntityID, E.NationalIDNumber, E.LoginID, E.JobTitle, E.HireDate
FROM AdventureWorks2017.HumanResources.Employee AS E

-- 15. Kreirati pogled (view) v_Osoba_Uposlenik nad tabelama Uposlenik i Osoba koji će sadržavati sva polja obje tabele.

GO
CREATE VIEW v_Osoba_Uposlenik
AS
SELECT *
FROM Osoba AS O
	INNER JOIN Uposlenik AS U ON O.OsobaID = U.UposlenikID
GO

SELECT * FROM v_Osoba_Uposlenik

-- 16. Koristeći pogled v_Osoba_Uposlenik prebrojati koliko se osoba zaposlilo po godinama.

SELECT
	YEAR(vOU.DtmZapos) AS [Godina],
	COUNT(*) AS [Broj zaposlenih]
FROM v_Osoba_Uposlenik AS vOU
GROUP BY YEAR(vOU.DtmZapos)