--1. Kreirati bazu Procedure_ i aktivirati je.

CREATE DATABASE Procedure_
GO
USE Procedure_
GO

--2. Kreirati tabelu Proizvodi te prilikom kreiranja uraditi insert podataka iz tabele Products baze Northwind.

SELECT *
INTO Proizvodi
FROM Northwind.dbo.Products;

SELECT * FROM Proizvodi

--3. Kreirati proceduru sp_Products_Insert kojom će se u tabeli Proizvodi uraditi insert novog zapisa.

GO
CREATE OR ALTER PROCEDURE sp_Products
(
	@ProductName NVARCHAR(40),
	@SupplierID INT = NULL,
	@CategoryID INT = NULL,
	@QuantityPerUnit NVARCHAR(20) = NULL,
	@UnitPrice MONEY = NULL,
	@UnitsInStock SMALLINT = NULL,
	@UnitsOnOrder SMALLINT = NULL,
	@ReorderLevel SMALLINT = NULL,
	@Discontinued BIT
)
AS
BEGIN
	INSERT INTO Proizvodi
	--(ProductName, SupplierID, CategoryID, QuantityPerUnit, UnitPrice, UnitsInStock, UnitsOnOrder, ReorderLevel, Discontinued)	  ->	OPCIONALNO - jer smo dolje redom naveli atribute koje insertujemo
	VALUES	(
		@ProductName,
		@SupplierID,
		@CategoryID,
		@QuantityPerUnit,
		@UnitPrice,
		@UnitsInStock,
		@UnitsOnOrder,
		@ReorderLevel,
		@Discontinued
	)
END
GO

--4. Kreirati dva testna slučaja, u prvom poslati podatke u sva polja, u drugom samo u ona koja su obavezna.

exec sp_Products 'Proizvod1', 1, 1, '2 per unit', 100, 100, 100, 100, 0;

SELECT * FROM Proizvodi

exec sp_Products @ProductName = 'Proizvod2', @Discontinued = 0;

SELECT * FROM Proizvodi


--5. Kreirati proceduru sp_Products_Update kojom će se u tabeli Proizvodi uraditi update zapisa.

GO
CREATE OR ALTER PROCEDURE sp_Products_Update
(
	@ProductID INT,
	@ProductName NVARCHAR(40) = NULL,
	@SupplierID INT = NULL,
	@CategoryID INT = NULL,
	@QuantityPerUnit NVARCHAR(20) = NULL,
	@UnitPrice MONEY = NULL,
	@UnitsInStock SMALLINT = NULL,
	@UnitsOnOrder SMALLINT = NULL,
	@ReorderLevel SMALLINT = NULL,
	@Discontinued BIT = NULL  
)
AS
BEGIN
	UPDATE Proizvodi
	SET 
		ProductName = ISNULL(@ProductName, ProductName),
		SupplierID = ISNULL(@SupplierID, SupplierID),
		CategoryID = ISNULL(@CategoryID, CategoryID),
		QuantityPerUnit = ISNULL(@QuantityPerUnit, QuantityPerUnit),
		UnitPrice = ISNULL(@UnitPrice, UnitPrice),
		UnitsInStock = ISNULL(@UnitsInStock, UnitsInStock),
		UnitsOnOrder = ISNULL(@UnitsOnOrder, UnitsOnOrder),
		ReorderLevel = ISNULL(@ReorderLevel, ReorderLevel),
		Discontinued = ISNULL(@Discontinued, Discontinued)
	WHERE ProductID = @ProductID
END
GO

--6. Kreirati testni slučaj za update zapisa kroz proceduru.

exec sp_Products_Update @ProductID = 79, @UnitPrice = 100

SELECT * FROM Proizvodi

--7. Kreirati proceduru sp_Products_Delete kojom će se u tabeli Proizvodi uraditi delete određenog zapisa.

GO
CREATE OR ALTER PROCEDURE sp_Products_Delete
(
	@ProductID INT
)
AS
BEGIN
	DELETE FROM Proizvodi
	WHERE ProductID = @ProductID
END
GO

--8. Kreirati testni slučaj za brisanje proizvoda sa id-om 78.

exec sp_Products_Delete @ProductID = 78

SELECT * FROM Proizvodi

--9. Kreirati tabelu StavkeNarudzbe te prilikom kreiranja uraditi insert podataka iz tabele Order Details baze Northwind.

SELECT *
INTO StavkeNarudzbe
FROM Northwind.dbo.[Order Details]

--10. Kreirati proceduru sp_OrderDetails_Products_InsertUpdate kojom će se u tabeli StavkeNarudzbe dodati nova stavka narudžbe a u tabeli Proizvodi umanjiti stanje za zalihama.

GO
CREATE OR ALTER PROCEDURE sp_OrderDetails_Products_InsertUpdate
(
	@OrderID INT,
	@ProductID INT,
	@UnitPrice MONEY,
	@Quantity SMALLINT,
	@Discount REAL
)
AS
BEGIN
	
	DECLARE @QuantityInStock SMALLINT;

	SELECT @QuantityInStock = P.UnitsInStock
	FROM Proizvodi AS P
	WHERE P.ProductID = @ProductID

	IF @QuantityInStock IS NULL
	BEGIN
		RAISERROR('Proizvod ne postoji!', 16, 1);
		RETURN;
	END

	IF @QuantityInStock < @Quantity
	BEGIN
		RAISERROR('Za ovaj proizvod nema tolika kolicina na stanju!', 16, 1);
		RETURN;
	END

	INSERT INTO StavkeNarudzbe
	VALUES	(
		@OrderID,
		@ProductID,
		@UnitPrice,
		@Quantity,
		@Discount
	)

	UPDATE Proizvodi
	SET UnitsInStock = UnitsInStock - @Quantity
	WHERE ProductID = @ProductID
END
GO

--11. Kreirati testni slučaj za prethodno kreiranu proceduru.

SELECT * FROM Proizvodi

exec sp_OrderDetails_Products_InsertUpdate 2, 1, 100, 10, 0

SELECT * FROM StavkeNarudzbe

--12. Kreirati proceduru sp_Products_SelectByProductNameOrCategoryID kojom će se u tabeli Proizvodi uraditi select proizvoda prema nazivu proizvoda ili ID kategorije. Ukoliko korisnik ne unese ništa od navedenog prikazati sve proizvode.

GO
CREATE OR ALTER PROCEDURE sp_Products_SelectByProductNameOrCategoryID
(
	@ProductName NVARCHAR(40) = NULL,
	@CategoryID INT = NULL
)
AS
BEGIN
	SELECT *
	FROM Proizvodi AS P
	WHERE
		(@ProductName IS NULL OR P.ProductName = @ProductName) AND
		(@CategoryID IS NULL OR P.CategoryID = @CategoryID)
END
GO

--13. Prethodno kreiranu proceduru izvršiti sa sljedećim testnim slučajevima:
--• Ime proizvoda 'Chai'
--• Id kategorije 7
--• Ime proizvoda 'Tofu' i id kategorije = 7
--• bez slanja bilo kakvih podataka

exec sp_Products_SelectByProductNameOrCategoryID @ProductName = 'Chai'

exec sp_Products_SelectByProductNameOrCategoryID @CategoryID = 7

exec sp_Products_SelectByProductNameOrCategoryID @ProductName = 'Tofu', @CategoryID = 7

exec sp_Products_SelectByProductNameOrCategoryID


--- ***

DECLARE @ImeProizvoda NVARCHAR(40) = 'Tofu'
SET @ImeProizvoda = 'Coffee'

SET @ImeProizvoda = (SELECT TOP 1 P.ProductName FROM Proizvodi AS P)

-- Pozivamo proceduru nad varijablom
exec sp_Products_SelectByProductNameOrCategoryID @ProductName = @ImeProizvoda

-- Postoji sve do oznake za kraj batch-a  ->  GO
GO

---***


--14. Kreirati proceduru sp_Products_SearchByProductName kojom će se uraditi select proizvoda prema nazivu. Korisniku već na unos prvog slova proizvoda treba prikazati podatke. Korisnik ne mora poslati vrijednost, i tada je potrebno vratiti sve proizvode. Procedura vraća sve stavke tabele Proizvodi. Obavezno kreirati testni slučaj.

GO
CREATE OR ALTER PROCEDURE sp_Products_SearchByProductName
(
	@ProductName NVARCHAR(100) = NULL
)
AS
BEGIN
	SELECT *
	FROM Proizvodi AS P
	WHERE LOWER(P.ProductName) LIKE LOWER('%' + @ProductName + '%') OR @ProductName IS NULL
END
GO

exec sp_Products_SearchByProductName @ProductName = 'M'

exec sp_Products_SearchByProductName

--15. Kreirati proceduru u bazi Procedure_ naziva sp_uposlenici_selectAll odgovarajućim tabelama baze AdventureWorks2017 kojom će se dati prikaz polja BusinessEntityID, FirstName, LastName i JobTitle. Proceduru podesiti da se rezultati sortiraju po BusinessEntityID.

GO
CREATE PROCEDURE sp_uposlenici_selectAll
AS
BEGIN
	SELECT P.BusinessEntityID, P.FirstName, P.LastName, E.JobTitle
	FROM AdventureWorks2017.Person.Person AS P
		INNER JOIN AdventureWorks2017.HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
	ORDER BY P.BusinessEntityID
END
GO

exec sp_uposlenici_selectAll

--16. Iz baze AdventureWorks2017 u tabelu Vendor kopirati tabelu Purchasing.Vendor.

--DROP TABLE Vendor
SELECT *
INTO Vendor
FROM AdventureWorks2017.Purchasing.Vendor

SELECT * FROM Vendor

--17. Kreirati proceduru sp_Vendor_deleteColumn kojom će se izvršiti brisanje kolone PurchasingWebServiceURL.

GO
CREATE PROCEDURE sp_Vendor_deleteColumn
AS
BEGIN
	ALTER TABLE Vendor
	DROP COLUMN PurchasingWebServiceURL
END
GO

exec sp_Vendor_deleteColumn

SELECT * FROM Vendor

--18. Kreirati proceduru sp_Vendor_updateAccountNumber kojom će se izvršiti update kolone AccountNumber tako da u svakom zapisu posljednji znak (cifra) podatka isključivo bude 1. Za podatke u navedenoj koloni koji inicijalno završavaju sa 1 ne treba raditi update.

GO
CREATE OR ALTER PROCEDURE sp_Vendor_updateAccountNumber
AS
BEGIN
	UPDATE Vendor
	SET AccountNumber = CONCAT(LEFT(AccountNumber, LEN(AccountNumber) - 1), '1')
	WHERE RIGHT(AccountNumber, 1) NOT LIKE '1'
END
GO

exec sp_Vendor_updateAccountNumber

SELECT * FROM Vendor

-- HELPERS
		SELECT *, CONCAT(LEFT(V.AccountNumber, LEN(V.AccountNumber) - 1), 'đ')
		FROM Vendor AS V

		SELECT *, RIGHT(V.AccountNumber, 1)
		FROM Vendor AS V

--19. Kreirati proceduru u bazi Procedure_ naziva sp_Zaposlenici_SelectByFirstNameLastNameGender nad odgovarajućim tabelama baze AdventureWorks2017 kojom će se definirati sljedeći ulazni parametri:
--	- EmployeeID,
--	- FirstName,
--	- LastName,
--	- Gender.
--Proceduru kreirati tako da je prilikom izvršavanja moguće unijeti bilo koji broj parametara (možemo ostaviti bilo koje polje bez unijete vrijednosti parametra), te da procedura daje rezultat ako je zadovoljena bilo koja od vrijednosti koje su navedene kao vrijednosti parametara. Ukoliko korisnik ne unese niti jedan od parametara procedura neće vraćati niti jedan zapis.

GO
CREATE OR ALTER PROCEDURE sp_Zaposlenici_SelectByFirstNameLastNameGender
(
	@EmployeeID INT = NULL,
	@FirstName NVARCHAR(50) = NULL,
	@LastName NVARCHAR(50) = NULL,
	@Gender NCHAR(1) = NULL
)
AS
BEGIN
	SELECT E.BusinessEntityID, P.FirstName, P.LastName, E.Gender
	FROM AdventureWorks2017.Person.Person AS P
		INNER JOIN AdventureWorks2017.HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
	WHERE 
		(@EmployeeID IS NOT NULL AND E.BusinessEntityID = @EmployeeID) OR
		(@FirstName IS NOT NULL AND P.FirstName = @FirstName) OR
		(@LastName IS NOT NULL AND P.LastName = @LastName) OR
		(@Gender IS NOT NULL AND E.Gender = @Gender)
END
GO

-- Nakon kreiranja pokrenuti proceduru sa sljedećim testnim slučajevima:
--	• EmployeeID = 20,
--	• LastName = Miller,
--	• LastName = Abercrombie, Gender = M

exec sp_Zaposlenici_SelectByFirstNameLastNameGender @EmployeeID = 20

exec sp_Zaposlenici_SelectByFirstNameLastNameGender @LastName = 'Miller'

exec sp_Zaposlenici_SelectByFirstNameLastNameGender @LastName = 'Abercrombie', @Gender = 'M'


exec sp_Zaposlenici_SelectByFirstNameLastNameGender

--20. Proceduru sp_Zaposlenici_SelectByFirstNameLastNameGender izmijeniti tako da je prilikom izvršavanja moguće unijeti bilo koje vrijednosti za prva tri parametra (možemo ostaviti bilo koje od tih polja bez unijete vrijednosti), a da vrijednost četvrtog parametra bude F. Nakon izmjene pokrenuti proceduru sa sljedećim testnim slučajevima:
	--• EmployeeID = 2,
	--• LastName = Miller

GO
CREATE OR ALTER PROCEDURE sp_Zaposlenici_SelectByFirstNameLastNameGender
(
	@EmployeeID INT = NULL,
	@FirstName NVARCHAR(50) = NULL,
	@LastName NVARCHAR(50) = NULL,
	@Gender NCHAR(1) = 'F'
)
AS
BEGIN
	SELECT E.BusinessEntityID, P.FirstName, P.LastName, E.Gender
	FROM AdventureWorks2017.Person.Person AS P
		INNER JOIN AdventureWorks2017.HumanResources.Employee AS E ON P.BusinessEntityID = E.BusinessEntityID
	WHERE
		(
		(@EmployeeID IS NOT NULL AND E.BusinessEntityID = @EmployeeID) OR
		(@FirstName IS NOT NULL AND P.FirstName = @FirstName) OR
		(@LastName IS NOT NULL AND P.LastName = @LastName)
		) AND
		(@Gender IS NOT NULL AND E.Gender = @Gender)
END
GO

exec sp_Zaposlenici_SelectByFirstNameLastNameGender @EmployeeID = 2

exec sp_Zaposlenici_SelectByFirstNameLastNameGender @LastName = 'Miller'


exec sp_Zaposlenici_SelectByFirstNameLastNameGender

--21. Kreirati proceduru u bazi Procedure_ naziva sp_Narudzbe_SelectByCustomerID nad odgovarajućim tabelama baze Northwind, sa parametrom CustomerID kojom će se dati pregled ukupno naručenih količina svakog od proizvoda za unijeti ID Customera. Proceduru pokrenuti za ID Customera BOLID

GO
CREATE OR ALTER PROCEDURE sp_Narudzbe_SelectByCustomerID
(
	@CustomerID NVARCHAR(10)
)
AS
BEGIN
	SELECT
		OD.ProductID,
		SUM(OD.Quantity) AS [Ukupna naručena količina]
	FROM Northwind.dbo.Orders AS O
		INNER JOIN Northwind.dbo.[Order Details] AS OD ON O.OrderID = OD.OrderID
	WHERE O.CustomerID = @CustomerID
	GROUP BY OD.ProductID
END
GO

exec sp_Narudzbe_SelectByCustomerID 'BOLID'

exec sp_Narudzbe_SelectByCustomerID 'BLAUS'

--22. Koristeći bazu Northwind kreirati pogled v_Narudzbe strukture:
--	- OrderID
--	- ShippedDate
--	- Ukupno (predstavlja sumu vrijednosti stavki po narudžbi).

GO
CREATE OR ALTER VIEW v_Narudzbe
AS
SELECT
	O.OrderID,
	O.ShippedDate,
	SUM(OD.UnitPrice * OD.Quantity) AS [Ukupno]
FROM Northwind.dbo.Orders AS O
	INNER JOIN Northwind.dbo.[Order Details] AS OD ON O.OrderID = OD.OrderID
GROUP BY O.OrderID, O.ShippedDate
GO


SELECT * FROM v_Narudzbe

--23. Koristeći pogled v_Narudzbe kreirati proceduru sp_Prodavci_Zemlje sa parametrima:
	--- startDate, datumski tip
	--- endDate, datumski tip
--startDate i endDate su datumi između kojih se izračunava suma prometa po narudžbi i obavezno je unijeti oba datuma.
--Procedura ima sljedeću strukturu, odnosno vraća sljedeće podatke:
	--- OrderID
	--- Ukupno
--pri čemu će kolona ukupno biti tipa money. Omogućiti sortiranje u opadajućem redoslijedu po Ukupno. 
--Nakon kreiranja procedure pokrenuti za vrijednosti
	--• startDate = 1997-01-01, endDate= 1997-12-31

GO
CREATE OR ALTER PROCEDURE sp_Prodavci_Zemlje
(
	@startDate DATE,
	@endDate DATE
)
AS
BEGIN
	SELECT
		vN.OrderID,
		CAST(vN.Ukupno AS MONEY) AS Ukupno
	FROM v_Narudzbe AS vN
	WHERE vN.ShippedDate BETWEEN @startDate AND @endDate
	ORDER BY vN.Ukupno DESC
END
GO

exec sp_Prodavci_Zemlje @startDate = '1997-01-01', @endDate = '1997-12-31'

--24. Iz baze AdventureWorks2017 u bazu Procedure_ kopirati tabelu zaglavlje i tabelu stavke narudžbe za nabavke. Novokreirane tabele imenovati kao zaglavlje i detalji. U kreiranim tabelama definirati PK kao u tabelama u Bazi AdventureWorks2017. Definirati relationships između tabela zaglavlje i stavke narudzbe.

SELECT *
INTO Zaglavlje
FROM AdventureWorks2017.Purchasing.PurchaseOrderHeader

SELECT *
INTO Detalji
FROM AdventureWorks2017.Purchasing.PurchaseOrderDetail


ALTER TABLE Zaglavlje
ADD CONSTRAINT PK_Zaglavlje PRIMARY KEY (PurchaseOrderID)

ALTER TABLE Detalji
ADD CONSTRAINT PK_Detalji PRIMARY KEY (PurchaseOrderID, PurchaseOrderDetailID)

ALTER TABLE Detalji
ADD CONSTRAINT FK_Detalji_Zaglavlje FOREIGN KEY (PurchaseOrderID) REFERENCES Zaglavlje(PurchaseOrderID)

--25. Kreirati proceduru sp_Narudzbe_Stavke sa parametrima: 
--	- status, kratki cjelobrojni tip 
--	- mjesecNarudzbe, cjelobrojni tip 
--	- kvartalIsporuke, cjelobrojni tip 
--	- vrijednostStavke, realni tip  
--Rezultat procedure je sljedeće strukture: 
--	- status 
--	- mjesec datuma narudžbe 
--	- kvartal datuma isporuke 
--	- naručena količina 
--	- cijena 
--	- vrijednost stavke kao proizvod količine i cijene 
-- Uslov je da procedura dohvata samo one zapise u kojima je vrijednost kolone vrijednost stavki između 100 i 500, pri čemu će prilikom pokretanja procedure rezultati biti sortirani u opadajućem redoslijedu. Proceduru kreirati tako da je prilikom izvršavanja moguće unijeti bilo koji broj parametara (možemo ostaviti bilo koje polje bez unijetog parametra), te da procedura daje rezultat ako je zadovoljena bilo koja od vrijednosti koje su navedene kao vrijednosti parametara.

GO
CREATE OR ALTER PROCEDURE sp_Narudzbe_Stavke
(
	@status SMALLINT = NULL,
	@mjesecNarudzbe INT = NULL,
	@kvartalIsporuke INT = NULL,
	@vrijednostStavke REAL = NULL
)
AS
BEGIN
	SELECT
		Z.Status,
		MONTH(Z.OrderDate) AS [Mjesec narudžbe],
		DATEPART(QUARTER, Z.ShipDate) AS [Kvartal isporuke],
		D.OrderQty,
		D.UnitPrice,
		(D.OrderQty * D.UnitPrice) AS [Vrijednost stavke]
	FROM Zaglavlje AS Z
		INNER JOIN Detalji AS D ON Z.PurchaseOrderID = D.PurchaseOrderID
	WHERE
		(
		(@status IS NOT NULL AND Z.Status = @status) OR
		(@mjesecNarudzbe IS NOT NULL AND MONTH(Z.OrderDate) = @mjesecNarudzbe) OR
		(@kvartalIsporuke IS NOT NULL AND DATEPART(QUARTER, Z.ShipDate) = @kvartalIsporuke)
		) AND
		(D.OrderQty * D.UnitPrice) BETWEEN 100 AND 500
	ORDER BY 6 DESC
END
GO

-- Nakon kreiranja procedure pokrenuti za sljedeće testne slučajeve: 
	--• status = 3 
	--• kvartal_isporuke = 4 
	--• mjesec_narudzbe = 3, 
	--• status = 1 

exec sp_Narudzbe_Stavke @status = 3

exec sp_Narudzbe_Stavke @kvartalIsporuke = 4

exec sp_Narudzbe_Stavke @mjesecNarudzbe = 3

exec sp_Narudzbe_Stavke @status = 1


exec sp_Narudzbe_Stavke 3, 3, 4, 1

exec sp_Narudzbe_Stavke

--26. Kreirati proceduru sp_Narudzbe_Stavke_sum sa paramterima: 
--	- status, kratki cjelobrojni tip 
--	- mjesecNarudzbe, cjelobrojni tip 
--	- kvartalIsporuke, cjelobrojni tip 
--Rezultat procedure je sljedeće strukture: 
--	- Status 
--	- mjesec datuma narudžbe 
--	- kvartal datuma isporuke 
--	- ukupnu vrijednost narudžbe 
-- Uslov je da procedura dohvata samo one zapise u kojima je vrijednost kolone ukupno između 10 000 i 5 000 000, pri čemu će prilikom pokretanja procedure rezultati biti sortirani u opadajućem redoslijedu. Proceduru kreirati tako da je prilikom izvršavanja moguće unijeti bilo koji broj parametara (možemo ostaviti bilo koje polje bez unijetog parametra), te da procedura daje rezultat ako je zadovoljena bilo koja od vrijednosti koje su navedene kao vrijednosti parametara.

GO
CREATE OR ALTER PROCEDURE sp_Narudzbe_Stavke_sum
(
	@status SMALLINT = NULL,
	@mjesecNarudzbe INT = NULL,
	@kvartalIsporuke INT = NULL
)
AS
BEGIN
	SELECT
		Z.Status,
		MONTH(Z.OrderDate) AS [Mjesec narudžbe],
		DATEPART(QUARTER, Z.ShipDate) AS [Kvartal isporuke],
		SUM(D.OrderQty * D.UnitPrice) AS [Ukupna vrijednost narudžbe]
	FROM Zaglavlje AS Z
		INNER JOIN Detalji AS D ON Z.PurchaseOrderID = D.PurchaseOrderID
	WHERE
		(@status IS NOT NULL AND Z.Status = @status) OR
		(@mjesecNarudzbe IS NOT NULL AND MONTH(Z.OrderDate) = @mjesecNarudzbe) OR
		(@kvartalIsporuke IS NOT NULL AND DATEPART(QUARTER, Z.ShipDate) = @kvartalIsporuke)
	GROUP BY Z.Status, Z.OrderDate, Z.ShipDate
	HAVING SUM(D.OrderQty * D.UnitPrice) BETWEEN 10000 AND 5000000
	ORDER BY 4 DESC
END
GO

-- Nakon kreiranja procedure pokrenuti za sljedeće testne slučajeve: 
	--• status = 1 
	--• kvartal_isporuke = 4 
	--• mjesec_narudzbe = 3

exec sp_Narudzbe_Stavke_sum @status = 1

exec sp_Narudzbe_Stavke_sum @kvartalIsporuke = 4

exec sp_Narudzbe_Stavke_sum @mjesecNarudzbe = 3


exec sp_Narudzbe_Stavke_sum @status = 1, @kvartalIsporuke = 4, @mjesecNarudzbe = 3

exec sp_Narudzbe_Stavke_sum