--1. Kreirati bazu Function_ i aktivirati je. 

GO
CREATE DATABASE Function_
GO
USE Function_

--2. Kreirati tabelu Zaposlenici, te prilikom kreiranja uraditi insert podataka iz tabele Employee baze Pubs. 

SELECT *
INTO Zaposlenici
FROM pubs.dbo.employee

--3. U tabeli Zaposlenici dodati izračunatu (stalno pohranjenu) kolonu Godina kojom će se iz kolone hire_date izdvajati godina uposlenja. 

ALTER TABLE Zaposlenici
ADD Godina AS YEAR(hire_date)

--4. Kreirati funkciju f_ocjena sa parametrom brojBodova, cjelobrojni tip koja će vraćati 
--poruke po sljedećem pravilu: 
--	- brojBodova < 55			nedovoljan broj bodova 
--	- brojBodova 55 - 65		šest (6) 
--	- broj Bodova 65 - 75		sedam (7) 
--	- brojBodova 75 - 85		osam (8) 
--	- broj Bodova 85 - 95		devet (9) 
--	- brojBodova 95-100			deset (10) 
--	- brojBodova > 100			fatal error 
--Kreirati testne slučajeve. 

GO
CREATE OR ALTER FUNCTION f_ocjena
(
	@brojBodova INT
)
RETURNS NVARCHAR(30)
AS
BEGIN
	DECLARE @poruka NVARCHAR(30) = 'nedovoljan broj bodova'

	IF @brojBodova BETWEEN 55 AND 64 SET @poruka = 'šest (6)'
	IF @brojBodova BETWEEN 65 AND 74 SET @poruka = 'sedam (7)'
	IF @brojBodova BETWEEN 75 AND 84 SET @poruka = 'osam (8)'
	IF @brojBodova BETWEEN 85 AND 94 SET @poruka = 'devet (9)'
	IF @brojBodova BETWEEN 95 AND 100 SET @poruka = 'deset (10)'

	IF @brojBodova > 100 SET @poruka = 'fatal error'
	
	RETURN @poruka
END
GO

SELECT 
	dbo.f_ocjena(54), 
	dbo.f_ocjena(55), 
	dbo.f_ocjena(95), 
	dbo.f_ocjena(100), 
	dbo.f_ocjena(150)

--5. Kreirati funkciju f_godina koja vraća podatke u formi tabele sa parametrom godina, cjelobrojni tip. Parametar se referira na kolonu godina tabele uposlenici, pri čemu se trebaju vraćati samo oni zapisi u kojima je godina veća od unijete vrijednosti parametra. Potrebno je da se prilikom pokretanja funkcije u rezultatu nalaze sve kolone tabele zaposlenici. Kreirati testne slučajeve. 

GO
CREATE OR ALTER FUNCTION f_godina
(
	@godina INT
)
RETURNS TABLE
AS
RETURN
	SELECT *
	FROM Zaposlenici AS Z
	WHERE Z.Godina > @godina
GO

SELECT * FROM dbo.f_godina(1990)
SELECT * FROM dbo.f_godina(1992)
SELECT * FROM dbo.f_godina(1995)

--6. Kreirati funkciju f_pub_id koja vraća podatke u formi tabele sa parametrima: 
--	- prva_cifra, kratki cjelobrojni tip 
--	- job_id, kratki cjelobrojni tip 
-- Parametar prva_cifra se referira na prvu cifru kolone pub_id tabele uposlenici, pri čemu je njegova zadana vrijednost 0. Parametar job_id se referira na kolonu job_id tabele uposlenici. Potrebno je da se prilikom pokretanja funkcije u rezultatu nalaze sve kolone tabele uposlenici. Kreirati testni slučaj za parametar job_id = 5 

GO
CREATE OR ALTER FUNCTION f_pub_id
(
	@prva_cifra SMALLINT = 0,
	@job_id SMALLINT
)
RETURNS TABLE
AS
RETURN
	SELECT *
	FROM Zaposlenici AS Z
	WHERE LEFT(Z.pub_id, 1) LIKE CAST(@prva_cifra AS VARCHAR(10)) AND Z.job_id = @job_id
GO

SELECT *
FROM f_pub_id(DEFAULT, 5)

--7. Kreirati tabelu Detalji, te prilikom kreiranja uraditi insert podataka iz tabele Order Details baze Northwind. 

SELECT *
INTO Detalji
FROM Northwind.dbo.[Order Details]

--8. Kreirati funkciju f_ukupno sa parametrima 
---	- UnitPrice		novčani tip, 
--	- Quantity		kratki cjelobrojni tip  
--	- Discount		realni broj 
--Funkcija će vraćati rezultat tip decimal (10,2) koji će računati po pravilu: 
--UnitPrice * Quantity * (1 - Discount) 

GO
CREATE FUNCTION f_ukupno
(
	@UnitPrice MONEY,
	@Quantity SMALLINT,
	@Discount REAL
)
RETURNS DECIMAL(10, 2)
AS
BEGIN
	RETURN @UnitPrice * @Quantity * (1 - @Discount)
END
GO

--9. Koristeći funkciju f_ukupno u tabeli detalji prikazati ukupnu vrijednost prometa po ID proizvoda. 

SELECT
	D.OrderID,
	SUM(dbo.f_ukupno(D.UnitPrice, D.Quantity, D.Discount)) AS Ukupno
FROM Detalji AS D
GROUP BY D.OrderID
ORDER BY 2 DESC

--10. Koristeći funkciju f_ukupno u tabeli detalji kreirati pogled v_f_ukupno u kojem će biti prikazan ukupan promet po ID narudžbe. 

GO
CREATE OR ALTER VIEW v_f_ukupno
AS
	SELECT
		D.OrderID,
		SUM(dbo.f_ukupno(D.UnitPrice, D.Quantity, D.Discount)) AS Ukupno
	FROM Detalji AS D
	GROUP BY D.OrderID
GO

--11. Iz pogleda v_f_ukupno odrediti najmanju i najveću vrijednost sume. 

SELECT
	MIN(vfU.Ukupno) AS [Najmanja vrijednost sume],
	MAX(vfU.Ukupno) AS [Najveća vrijednost sume]
FROM v_f_ukupno AS vfU

--12. Kreirati tabelu Kupovina, te prilikom kreiranja uraditi insert podataka iz tabele PurchaseOrderDetail baze AdventureWorks2017. Tabela će sadržavati kolone: 
--	- PurchaseOrderID
--	- PurchaseOrderDetailID
--	- UnitPrice
--	- RejectedQty
--	- RazlikaKolicina koja predstavlja razliku između naručene i primljene količine

SELECT
	POD.PurchaseOrderID,
	POD.PurchaseOrderDetailID,
	POD.UnitPrice,
	POD.RejectedQty,
	(POD.OrderQty - POD.ReceivedQty) AS RazlikaKolicina
INTO Kupovina 
FROM AdventureWorks2017.Purchasing.PurchaseOrderDetail AS POD

--13. Kreirati funkciju f_rejected koja vraća podatke u formi tabele sa parametrima: 
--	- RejectedQty DECIMAL (8,2) 
--	- RazlikaKolicina INT 
-- Parametar RejectedQty se referira na kolonu RejectedQty tabele kupovina, pri čemu je njegova zadana vrijednost 0. Parametar RazlikaKolicina se odnosi na kolonu RazlikaKolicina. Potrebno je da se prilikom pokretanja funkcije u rezultatu nalaze sve kolone tabele Kupovina. Provjeriti funkcioniranje funkcije unošenjem vrijednosti za parametar RazlikaKolicina = 27, pri čemu će upit vraćati sume UnitPrice po PurchaseOrderID. 
--Sortirati po sumiranim vrijednostima u opadajućem redoslijedu. 

GO
CREATE OR ALTER FUNCTION f_rejected
(
	@RejectedQty DECIMAL (8,2) = 0,
	@RazlikaKolicina INT
)
RETURNS TABLE
AS
RETURN
	SELECT *
	FROM Kupovina AS K
	WHERE K.RejectedQty = @RejectedQty AND K.RazlikaKolicina = @RazlikaKolicina
GO

SELECT 
	RESULT.PurchaseOrderID,
	SUM(RESULT.UnitPrice) AS Suma
FROM dbo.f_rejected(DEFAULT, 27) AS RESULT
GROUP BY RESULT.PurchaseOrderID
ORDER BY 2 DESC

--14. Kreirati bazu Trigger_ i aktivirati je. 

GO
CREATE DATABASE Trigger_
GO
USE Trigger_

--15. Kreirati tabelu Autori, te prilikom kreiranja uraditi insert podataka iz tabele Authors baze Pubs. 

SELECT *
INTO Autori
FROM pubs.dbo.authors

--16. Kreirati tabelu Autori_log strukture: 
--	- log_id int IDENTITY (1,1)
--	- au_id VARCHAR (11)
--	- dogadjaj VARCHAR (3)
--	- mod_date DATETIME
--	- au_lname VARCHAR (40)

CREATE TABLE Autori_log
(
	log_id INT IDENTITY (1, 1),
	au_id VARCHAR (11),
	dogadjaj VARCHAR (3),
	mod_date DATETIME,
	au_lname VARCHAR (40)
)

--17. Nad tabelom Autori kreirati okidač t_ins_autori kojim će se prilikom inserta podataka u tabelu autori izvršiti insert podataka u tabelu Autori_log. 

GO
CREATE OR ALTER TRIGGER t_ins_autori
ON Autori
-- FOR ISTO KAO AFTER
AFTER INSERT
AS
BEGIN
	INSERT INTO Autori_log
	SELECT
		I.au_id,
		'ins',
		GETDATE(),
		I.au_lname
	FROM inserted AS I

	--SELECT * FROM inserted
	--SELECT * FROM deleted

	-- tabele inserted i deleted su nam dostupne i u njima se nalaze stvari koje su dodane/obrisane prilikom neke akcije u tabelu
END
GO

--18. U tabelu autori insertovati zapis 
--'1', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1 
--'2', 'Green', 'Marjorie', '415 986-7020', '309 63rd St. #411', 'Oakland', 'CA', 94618, 1 
--Provjeriti stanje u tabelama autori i autori_log. 

INSERT INTO Autori
VALUES 
	('1', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1),
	('2', 'Green', 'Marjorie', '415 986-7020', '309 63rd St. #411', 'Oakland', 'CA', 94618, 1)

SELECT * FROM Autori
SELECT * FROM Autori_log


--19. Nad tabelom Autori kreirati okidač t_upd_autori kojim će se prilikom update podataka u tabeli Autori izvršiti insert podataka u tabelu autori_log. 

GO
CREATE OR ALTER TRIGGER t_upd_autori
ON Autori
AFTER UPDATE
AS
BEGIN
	INSERT INTO Autori_log
	SELECT
		I.au_id,
		'upd',
		GETDATE(),
		I.au_lname
	FROM deleted AS I
END
GO

-- How INSERTED and DELETED work during UPDATE:

-- DELETED contains the old (pre-update) values.
-- INSERTED contains the new (post-update) values.

-- So for an UPDATE, every row in DELETED corresponds 1:1 with a row in INSERTED — representing the row before and after the update.

-- U suštini, kod update triggera deleted tabela sadrži redove koje updatujemo, ali sa starim stanjem, a inserted tabela sadrži isto tako redove koje updateujemo, ali sa novim vrijednostima. Ukoliko pravimo log tabelu u kojoj ćemo pohranjivati oba stanja (prije i poslije), inner joinovati ćemo ove tabele po ključu i dobiti oba stanja
-- To dalje znači da, za naše potrebe možemo koristiti samo deleted tabelu, obzirom da nas ne zanimaju podaci o trenutnom stanju, jer se odražavaju u stvarnoj tabeli koju log tabela predstavlja, a koji će svakako biti pohranjeni u log tabelu, dođe li do promjene stanja.

GO

--20. U tabeli Autori napraviti update zapisa u kojem je au_id = 998-72-3567 tako što će se vrijednost kolone au_lname postaviti na Pasic. Provjeriti stanje u tabelama Autori i Autori_log. 

UPDATE Autori
SET au_lname = 'Pasic'
WHERE au_id = '998-72-3567'

SELECT * FROM Autori
SELECT * FROM Autori_log

--21. Nad tabelom Autori kreirati okidač t_del_autori kojim će se prilikom brisanja podataka u tabeli Autori izvršiti insert podataka u tabelu Autori_log. 

GO
CREATE OR ALTER TRIGGER t_del_autori
ON Autori
AFTER DELETE
AS
BEGIN
	INSERT INTO Autori_log
	SELECT
		I.au_id,
		'del',
		GETDATE(),
		I.au_lname
	FROM deleted AS I

	-- dakle, kao što i ime sugeriše, u deleted tabeli se nalaze podaci koje brišemo iz tabele i možemo im pristupiti tu
END
GO

--22. U tabeli Autori obrisati zapis u kojem je au_id = 2. Provjeriti stanje u tabelama Autori i Autori_log. 

DELETE FROM Autori
WHERE au_id = '2'

SELECT * FROM Autori
SELECT * FROM Autori_log

--23. Kreirati tabelu Autori_instead_log strukture: 
--	- log_id INT IDENTITY (1,1)
--	- au_id VARCHAR (11)
--	- dogadjaj VARCHAR (15)
--	- mod_date DATETIME

CREATE TABLE Autori_instead_log
(
	log_id INT IDENTITY (1, 1),
	au_id VARCHAR (11),
	dogadjaj VARCHAR (15),
	mod_date DATETIME
)

--24. Nad tabelom Autori kreirati okidač t_instead_ins_autori kojim će se onemogućiti insert podataka u tabelu Autori. Okidač treba da vraća poruku da insert nije izvršen i da sačuva podatke u tabelu Autori_instead_log.

GO
CREATE OR ALTER TRIGGER t_instead_ins_autori
ON Autori
INSTEAD OF INSERT
AS
BEGIN
	-- možemo na primjer zaustaviti insert, nakon čega ćemo provjeriti/validirati podatke, te ako je sve ok manuelno insertovati proslijeđene podatke, odnosno ako nije, odbaciti podatke

	PRINT('Insert nije izvršen')

	INSERT INTO Autori_instead_log
	SELECT
		I.au_id,
		'insert failed',
		GETDATE()
	FROM inserted AS I
END
GO

--25. U tabelu Autori insertovati zapis: 
-- '3', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1 
--Provjeriti stanje u tabelama Autori, Autori_log i Autori_instead_log. 

INSERT INTO Autori
VALUES ('3', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1)

SELECT * FROM Autori
SELECT * FROM Autori_instead_log

--26. Nad tabelom Autori kreirati okidač t_instead_upd_autori kojim će se onemogućiti update podataka u tabelu Autori. Okidač treba da vraća poruku da update nije izvršen i da sačuva podatke u tabelu Autori_instead_log. 

GO
CREATE OR ALTER TRIGGER t_instead_upd_autori
ON Autori
INSTEAD OF UPDATE
AS
BEGIN
	PRINT('Update nije izvršen')

	INSERT INTO Autori_instead_log
	SELECT
		I.au_id,
		'update failed',
		GETDATE()
	FROM inserted AS I
	
	-- ovdje inserted jer želim da sačuvam ono što se pokušalo promijeniti u tabeli, obzirom da to nikada neće proći, za razliku od t_upd_autori gdje sam htio da sačuvam ono što je prethodno bilo

END
GO

--27. U tabeli autori pokušati update zapisa u kojem je au_id = 172-32-1176 tako što će se vrijednost kolone contract postaviti na 0. Provjeriti stanje u tabelama autori i autori_instead_log. 

UPDATE Autori
SET contract = 0
WHERE au_id = '172-32-1176'

SELECT * FROM Autori
SELECT * FROM Autori_instead_log

--28. Nad tabelom autori kreirati okidač t_instead_del_autori kojim će se onemogućiti delete podataka u tabelu autori. Okidač treba da vraća poruku da delete nije izvršen i da podatke u tabelu Autori_instead_log. 

GO
CREATE OR ALTER TRIGGER t_instead_del_autori
ON Autori
INSTEAD OF DELETE
AS
BEGIN
	PRINT('Delete nije izvršen')

	INSERT INTO Autori_instead_log
	SELECT
		I.au_id,
		'delete failed',
		GETDATE()
	FROM deleted AS I
END
GO

--29. U tabeli autori pokušati obrisati zapis u kojem je au_id = 172-32-1176. Provjeriti stanje u tabelama autori i autori_instead_log.

DELETE FROM Autori
WHERE au_id = '172-32-1176'

SELECT * FROM Autori
SELECT * FROM Autori_instead_log

--30. Iskljućiti okidač t_instead_ins_autori. 

GO
DISABLE TRIGGER t_instead_ins_autori ON Autori

--31. U tabelu autori insertovati zapis 
-- '3', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1 
-- Provjeriti stanje u tabelama autori, autori_log i autori_instead_log. 

INSERT INTO Autori
VALUES ('3', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1)

SELECT * FROM Autori
SELECT * FROM Autori_log
SELECT * FROM Autori_instead_log

--32. Isključiti sve okidače nad tabelom autori. 

GO
DISABLE TRIGGER ALL ON Autori

--33. Uključiti sve okidače nad tabelom autori. 

GO
ENABLE TRIGGER ALL ON Autori



-- brisanje triggera
DROP TRIGGER t_instead_upd_autori

--34. U tabelu autori dodadati novo polje ModifiedDate. Nakon toga kreirati okidač t_updateMD kojim će se nakon promjene neke vrijednosti unutar tabele autori setovati ModifiedDate na trenutni datum. Voditi računa o tome da pri update-u npr zapisa sa ID-om 172-32-1176 se modificira datum samo za tog autora (ne za sve). 

-- isključit ćemo trigger t_upd_autori i t_instead_upd_autori kako ne bismo spašavali iste podatke na više mjesta
GO
DISABLE TRIGGER t_upd_autori ON Autori
GO
DISABLE TRIGGER t_instead_upd_autori ON Autori


ALTER TABLE Autori
ADD ModifiedDate DATETIME


GO
CREATE OR ALTER TRIGGER t_updateMD
ON Autori
AFTER UPDATE
AS
BEGIN
	UPDATE Autori
	SET ModifiedDate = GETDATE()
	WHERE au_id IN (SELECT au_id FROM inserted)
END
GO

UPDATE Autori
SET au_fname = 'Amy'
WHERE au_id LIKE '172-32-1176'

SELECT * FROM Autori



-- ALTERNATIVNO

--GO
--CREATE OR ALTER TRIGGER t_updateMD
--ON Autori
--AFTER UPDATE
--AS
--BEGIN
--	UPDATE A
--	SET A.ModifiedDate = GETDATE()
--	FROM Autori AS A
--		INNER JOIN deleted AS D ON A.au_id = D.au_id
--		INNER JOIN inserted AS I ON A.au_id = I.au_id
--	WHERE 
--		ISNULL(I.au_lname, '') <> ISNULL(D.au_lname, '') OR
--		ISNULL(I.au_fname, '') <> ISNULL(D.au_fname, '') OR
--		ISNULL(I.phone, '') <> ISNULL(D.phone, '') OR
--		ISNULL(I.address, '') <> ISNULL(D.address, '') OR
--		ISNULL(I.city, '') <> ISNULL(D.city, '') OR
--		ISNULL(I.state, '') <> ISNULL(D.state, '') OR
--		ISNULL(I.zip, '') <> ISNULL(D.zip, '') OR
--		ISNULL(I.contract, '') <> ISNULL(D.contract, '')
--END
--GO



--35. Kreirati bazu Indeksi i aktivirati je. 

GO
CREATE DATABASE Indeksi
GO
USE Indeksi

--36. Kreirati tabelu ProizvodiOsobe koja će nastati spajanjem tabela Product i Person baze AdventureWorks2017 CROSS JOIN-om i prilikom kreiranja importovati 10 miliona zapisa.  

SELECT * FROM AdventureWorks2017.Production.Product
SELECT * FROM AdventureWorks2017.Person.Person

SELECT TOP 10000000
	PR.ProductID,
	PR.Name,
	PR.ProductNumber,
	PR.ModifiedDate,

	PE.BusinessEntityID,
	PE.PersonType,
	PE.FirstName,
	PE.MiddleName,
	PE.LastName
INTO ProizvodiOsobe
FROM AdventureWorks2017.Production.Product AS PR
	CROSS JOIN AdventureWorks2017.Person.Person AS PE

SELECT * FROM ProizvodiOsobe

--37. Kreirati nonclustered index kojim će se ubrzati pretraga po imenu i prezimenu. Kreirati testni slučaj i pogledati aktualni plan izvršenja. Izbrisati kreirani index. 

-- nonclustered index je podrazumijevan pa ne pišem CREATE CLUSTERED INDEX
CREATE INDEX ix_FirstName_LastName
ON ProizvodiOsobe(FirstName, LastName DESC)
-- možemo odrediti smjer sortiranja

SELECT *
FROM ProizvodiOsobe AS PO
WHERE PO.FirstName LIKE 'N%' AND PO.LastName LIKE '%K'

DROP INDEX ix_FirstName_LastName ON ProizvodiOsobe

--38. Kreirati nonclustered indeks koji će omogućiti bržu pretragu prema imenu i prezimenu a također u definiciju indexa uključiti i srednje ime, kao dodatak. Kreirati testni slučaj i pogledati plan izvršenja. Izbrisati kreirani index. 

CREATE NONCLUSTERED INDEX ix_FirstName_LastName_Include_MiddleName
ON ProizvodiOsobe(FirstName, LastName)
INCLUDE (MiddleName)

SELECT *
FROM ProizvodiOsobe AS PO
WHERE PO.FirstName LIKE 'N%' AND PO.LastName LIKE '%s'

SELECT *
FROM ProizvodiOsobe AS PO
WHERE PO.FirstName LIKE 'N%' AND PO.LastName LIKE '%k' AND PO.MiddleName LIKE '%l%'

DROP INDEX ix_FirstName_LastName_Include_MiddleName ON ProizvodiOsobe

--39. Kreirati kompozitni primarni  ključ nad kolonama ProductID i BusinessEntityID. Kreirati testni slučaj za upotrebu primarnog ključa, te nakon testiranja izbrisati primarni ključ. 

ALTER TABLE ProizvodiOsobe
ADD CONSTRAINT PK_ProizvodiOsobe PRIMARY KEY (ProductID, BusinessEntityID)

SELECT * FROM ProizvodiOsobe

SELECT * 
FROM ProizvodiOsobe AS PO
WHERE PO.Name LIKE '[L-P]%' AND PO.FirstName LIKE '%r%'

SELECT *
FROM ProizvodiOsobe AS PO
WHERE PO.ProductId = 1 AND PO.BusinessEntityID = 14951

ALTER TABLE ProizvodiOsobe
DROP CONSTRAINT PK_ProizvodiOsobe

--40. Kreirati clustered index nad kolonom ProductNumber. Kreirati testni slučaj za upotrebu indexa i pogledati plan izvršenja. Izbrisati kreirani index.

CREATE CLUSTERED INDEX ix_ProductNumber
ON ProizvodiOsobe(ProductNumber)

SELECT * FROM ProizvodiOsobe

SELECT *
FROM ProizvodiOsobe AS PO
WHERE PO.ProductNumber LIKE 'A%'

DROP INDEX ix_ProductNumber ON ProizvodiOsobe