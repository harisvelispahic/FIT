--Vježba 11 :: Zadaci

--1.    Kreirati bazu Function_ i aktivirati je.
CREATE DATABASE Function_
GO
USE Function_

--2.	Kreirati tabelu Zaposlenici te prilikom kreiranja uraditi insert podataka iz tabele Employees baze Northwind.
SELECT*
INTO Zaposlenici
FROM pubs.dbo.employee

--3.	U tabeli uposlenici dodati izraèunatu (stalno pohranjenu) kolonu godina kojom æe se iz kolone hire_date izdvajati godina uposlenja.
ALTER TABLE Zaposlenici
ADD GodinaZaposlenja AS YEAR(hire_date)

SELECT*
FROM Zaposlenici

--4.	Kreirati funkciju f_ocjena sa parametrom brojBodova, cjelobrojni tip koja æe vraæati poruke po sljedeæem pravilu:
--	- brojBodova < 55		nedovoljan broj bodova
--	- brojBodova 55 - 65		šest (6)
--	- broj Bodova 65 - 75		sedam (7)
--	- brojBodova 75 - 85		osam (8)
--	- broj Bodova 85 - 95		devet (9)
--	- brojBodova 95-100		deset
--	- brojBodova >100		fatal error
--Kreirati testne sluèajeve.
GO
CREATE FUNCTION f_ocjena
(
	@brojBodova int
)
RETURNS VARCHAR (50)
AS
BEGIN
	DECLARE @poruka VARCHAR (50)
	SET @poruka = 'nedovoljan broj bodova'
	IF @brojBodova BETWEEN 55 AND 64 SET @poruka = 'šest (6)'
	IF @brojBodova BETWEEN 65 AND 74 SET @poruka = 'sedam (7)'
	IF @brojBodova BETWEEN 75 AND 84 SET @poruka = 'osam (8)'
	IF @brojBodova BETWEEN 85 AND 94 SET @poruka = 'devet (9)'
	IF @brojBodova BETWEEN 95 AND 100 SET @poruka = 'deset (10)'
	IF @brojBodova>100 SET @poruka = 'fatal error'
	RETURN @poruka
END
GO
SELECT dbo.f_ocjena(55),dbo.f_ocjena(40),dbo.f_ocjena(80)

--5.	Kreirati funkciju f_godina koja vraæa podatke u formi tabele sa parametrom godina, cjelobrojni tip. Parametar se referira na kolonu godina tabele uposlenici, pri èemu se trebaju vraæati samo oni zapisi u kojima je godina veæa od unijete vrijednosti parametra. Potrebno je da se prilikom pokretanja funkcije u rezultatu nalaze sve kolone tabele uposlenici. Kreirati testne slučajeve. 
GO
CREATE FUNCTION f_godina
(
@godina INT
)
RETURNS TABLE
AS
RETURN
SELECT*
FROM Zaposlenici AS Z
WHERE Z.GodinaZaposlenja>@godina


SELECT	*
FROM f_godina (1993)
ORDER BY 9

--6.	Kreirati funkciju f_pub_id koja vraæa podatke u formi tabele sa parametrima:
--	- prva_cifra, kratki cjelobrojni tip
--	- job_id, kratki cjelobrojni tip
--Parametar prva_cifra se referira na prvu cifru kolone pub_id tabele uposlenici, pri èemu je njegova zadana vrijednost 0. Parametar job_id se referira na kolonu job_id tabele uposlenici. Potrebno je da se prilikom pokretanja funkcije u rezultatu nalaze sve kolone tabele uposlenici. Kreirati testni slučaj za parametar job_id = 5 
GO
CREATE FUNCTION f_pub_id 
(
	@prva_cifra TINYINT = 0,
	@job_id TINYINT
)
RETURNS TABLE 
AS
RETURN
	SELECT *
	FROM Zaposlenici AS Z
	WHERE	LEFT (Z.pub_id,1) = @prva_cifra and
			Z.job_id = @job_id
GO

SELECT *
FROM f_pub_id (DEFAULT, 5)

--7.	Kreirati tabelu detalji, te prilikom kreiranja uraditi isert podataka iz tabele Order Details baze Northwind. 
SELECT*
INTO Detalji
FROM Northwind.dbo.[Order Details]

--8.	Kreirati funkciju f_ukupno sa parametrima
--	- UnitPrice	novèani tip money,
--	- Quantity	kratki cjelobrojni tip
--	- Discount	realni broj
--Funkcija æe vraæati rezultat tip decimal (10,2) koji æe raèunati po pravilu:
--	UnitPrice * Quantity * (1 - Discount)
GO
CREATE FUNCTION f_ukupno
(
@UnitPrice MONEY,
@Quantity SMALLINT,
@Discount REAL
)
RETURNS DECIMAL(10,2)
AS
BEGIN 
RETURN @UnitPrice*@Quantity*(1-@Discount)
END
GO

SELECT dbo.f_ukupno(2,2,0.1)

--9.	Koristeæi funkciju f_ukupno u tabeli detalji prikazati ukupnu vrijednost prometa po ID proizvoda.
SELECT ProductID, SUM (dbo.f_ukupno([UnitPrice],[Quantity],[Discount])) 'Ukupno'
FROM Detalji
GROUP BY ProductID
ORDER BY 1

--10.	Koristeæi funkciju f_ukupno u tabeli detalji kreirati pogled v_f_ukupno u kojem æe biti prikazan ukupan promet po ID narudžbe.
GO
CREATE VIEW v_f_ukupno
AS
SELECT OrderID, SUM (dbo.f_ukupno([UnitPrice],[Quantity],[Discount])) as 'Ukupno'
FROM Detalji
GROUP BY OrderID
GO

--11.	Iz pogleda v_f_ukupno odrediti najmanju i najveæu vrijednost sume.
SELECT MIN(VU.Ukupno) 'Min', MAX(VU.Ukupno) 'Max'
FROM v_f_ukupno AS VU

--12.	Kreirati tabelu Kupovina, te prilikom kreiranja uraditi insert podataka iz tabele PurchaseOrderDetail baze AdventureWorks2017.
--Tabela æe sadržavati kolone:
--	- PurchaseOrderID, 
--	- PurchaseOrderDetailID,
--	- UnitPrice
--	- RejectedQty, 
--	- RazlikaKolicina koja predstavlja razliku izmeðu naruèene i primljene kolièine
SELECT POD.PurchaseOrderID,POD.PurchaseOrderDetailID,POD.UnitPrice,POD.RejectedQty,POD.OrderQty-POD.ReceivedQty 'RazlikaKolicina'
INTO Kupovina
FROM AdventureWorks2017.Purchasing.PurchaseOrderDetail AS POD

--13.	Kreirati funkciju f_rejected koja vraæa podatke u formi tabele sa parametrima:
--	- RejectedQty	 decimal (8,2)
--	- RazlikaKolicina  int
--Parametar RejectedQty se referira na kolonu RejectedQty tabele kupovina, pri èemu je njegova zadana vrijednost 0. Parametar RazlikaKolicina  se odnosi na kolonu RazlikaKolicina. Potrebno je da se prilikom pokretanja funkcije u rezultatu nalaze sve kolone tabele uposlenici. Provjeriti funkcioniranje funkcije unošenjem vrijednosti za parametar RazlikaKolicina = 27, pri èemu æe upit vraæati sume UnitPrice po PurchaseOrderID.
--Sortirati po sumiranim vrijednostima u opadajuæem redoslijedu.
GO
CREATE FUNCTION f_rejected
(
@RejectedQty DECIMAL (8,2)=0,
@RazlikaKolicina INT
)
RETURNS TABLE
AS
RETURN
	SELECT *
	FROM Kupovina
	WHERE	 RejectedQty= @RejectedQty AND
			RazlikaKolicina = @RazlikaKolicina
GO

SELECT DISTINCT RazlikaKolicina
FROM kupovina

--0.00
--62.00
--5.00
--3.00
--1.00
--280.00
--187.00
--27.00
--82.00
--9.00


SELECT PurchaseOrderID, SUM (UnitPrice)'Ukupno'
FROM f_rejected (DEFAULT, 27)
GROUP BY PurchaseOrderID
ORDER BY 2 DESC

--14.	Kreirati bazu Trigger_ i aktivirati je.
CREATE DATABASE Trigger_
GO
USE Trigger_

--15.	Kreirati tabelu Autori, te prilikom kreiranja uraditi insert podataka iz tabele Authors baze Pubs.
SELECT*
INTO Autori
FROM pubs.dbo.authors

--16.	16.	Kreirati tabelu Autori_log strukture:
	--- log_id int identity (1,1)
	--- au_id varchar (11)
	--- dogadjaj varchar (3)
	--- mod_date datetime
CREATE TABLE Autori_log
(
	 log_id INT IDENTITY (1,1),
	 au_id VARCHAR (11),
	 dogadjaj VARCHAR (3),
	 mod_date DATETIME,
	 au_lname VARCHAR (40)
)

--17.	Nad tabelom Autori kreirati okidaè t_ins_autori kojim æe se prilikom inserta podataka u tabelu autori izvršiti insert podataka u tabelu Autori_log.
GO
CREATE TRIGGER t_ins_autori
ON Autori
AFTER INSERT 
AS
BEGIN
	INSERT INTO Autori_log
	SELECT au_id, 'ins', GETDATE (), au_lname
	FROM inserted
	select * from inserted
	select * from deleted
END

--18.	U tabelu Autori insertovati zapis 
--'1', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1
--'2', 'Green', 'Marjorie', '415 986-7020', '309 63rd St. #411', 'Oakland',	'CA', 94618, 1
--Provjeriti stanje u tabelama Autori i Autori_log.
INSERT INTO Autori
VALUES
('1', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1),
('2', 'Green', 'Marjorie', '415 986-7020', '309 63rd St. #411', 'Oakland',	'CA', 94618, 1)

SELECT * 
FROM Autori

SELECT * 
FROM autori_log

--19.	Nad tabelom Autori kreirati okidaè t_upd_autori kojim æe se prilikom update podataka u tabeli Autori izvršiti insert podataka u tabelu autori_log.
GO
CREATE TRIGGER t_upd_autori
ON Autori
AFTER UPDATE
AS
BEGIN 
	INSERT INTO Autori_log
	SELECT	au_id, 'upd', GETDATE (), au_lname
	FROM	deleted
	select * from inserted
	select * from deleted
END

--20.	U tabeli autori napraviti update zapisa u kojem je au_id = 998-72-3567 tako što æe se vrijednost kolone au_lname postaviti na prezime. Provjeriti stanje u tabelama autori i autori_log.
UPDATE Autori
SET au_lname = 'Pasic'
WHERE au_id = '998-72-3567'

SELECT * FROM autori
SELECT * FROM autori_log

--21.	Nad tabelom Autori kreirati okidaè t_del_autori kojim æe se prilikom brisanja podataka u tabeli Autori izvršiti insert podataka u tabelu Autori_log.
GO
CREATE TRIGGER t_del_autori
ON Autori
AFTER DELETE
AS
BEGIN
	INSERT INTO Autori_log
	SELECT	au_id, 'del', GETDATE (), au_lname
	FROM	deleted
	SELECT * FROM inserted
	SELECT * FROM deleted
END

--22.	U tabeli Autori obrisati zapis u kojem je au_id = 3. Provjeriti stanje u tabelama Autori i Autori_log.
DELETE 
FROM Autori
WHERE au_id = '2'

SELECT * FROM autori
SELECT * FROM autori_log

--23.	Kreirati tabelu Autori_instead_log strukture:
--	- log_id INT IDENTITY (1,1),
--	- au_id VARCHAR (11),
--	- dogadjaj VARCHAR (15),	
--	- mod_date datetime
--	-au_lname VARCHAR (40)
CREATE TABLE Autori_instead_log
(
	log_id INT IDENTITY (1,1),
	au_id VARCHAR (11),
	dogadjaj VARCHAR (15),
	mod_date datetime
)

--24.	Nad tabelom Autori kreirati okidač t_instead_ins_autori kojim će se onemogućiti insert podataka u tabelu Autori. Okidač treba da vraća poruku da insert nije izvršen i da sačuva podatke u tabelu Autori_instead_log. 
GO
CREATE TRIGGER t_instead_ins_autori
ON Autori
INSTEAD OF INSERT
AS
BEGIN
	SELECT 'Insert nije izvršen'
	INSERT INTO Autori_instead_log
	SELECT au_id, 'not_inserted', GETDATE ()
	FROM inserted
END
GO

--25.	U tabelu autori insertovati zapis 
--'3', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1
--Provjeriti stanje u tabelama autori, autori_log i autori_instead_log.
INSERT INTO Autori
VALUES ('3', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1)

SELECT * FROM Autori
SELECT * FROM Autori_log
SELECT * FROM Autori_instead_log

--26.	Nad tabelom Autori kreirati okidač t_instead_upd_autori kojim će se onemogućiti update podataka u tabelu Autori. Okidač treba da vraća poruku da update nije izvršen i da sačuva podatke u tabelu Autori_instead_log. 
GO
CREATE TRIGGER t_instead_upd_autori
ON Autori
INSTEAD OF UPDATE
AS
BEGIN
	SELECT 'Update nije izvršen'
	INSERT INTO Autori_instead_log
	SELECT au_id, 'not_updated', GETDATE ()
	FROM inserted
	SELECT * FROM inserted
	SELECT * FROM deleted
END

--27.	U tabeli Autori pokušati update zapisa u kojem je au_id = 172-32-1176 tako što æe se vrijednost kolone contract postaviti na  0. Provjeriti stanje u tabelama autori i autori_instead_log.
UPDATE Autori
SET contract = 0
WHERE au_id = '172-32-1176'

SELECT * FROM Autori
SELECT * FROM Autori_log
SELECT * FROM Autori_instead_log

--28.	Nad tabelom autori kreirati okidač t_instead_del_autori kojim će se onemogućiti delete podataka u tabelu autori. Okidač treba da vraća poruku da delete nije izvršen i da sačuva podatke u tabelu Autori_instead_log. 
GO
CREATE OR ALTER TRIGGER t_instead_del_autori
ON Autori
INSTEAD OF DELETE
AS
BEGIN
	SELECT 'Delete nije izvršen'
	INSERT INTO Autori_instead_log
	SELECT au_id, 'not_deleted', GETDATE ()
	FROM deleted
	--SELECT * FROM inserted
	--SELECT * FROM deleted
END

--29.	U tabeli autori pokušati obrisati zapis u kojem je au_id = 172-32-1176. Provjeriti stanje u tabelama autori i autori_instead_log.
DELETE Autori
WHERE au_id = '172-32-1176'

SELECT * FROM Autori
SELECT * FROM Autori_log
SELECT * FROM Autori_instead_log

--30.	Iskljuæiti okidaè t_instead_ins_autori.
GO
DISABLE TRIGGER t_instead_ins_autori ON Autori

--31.	U tabelu Autori insertovati zapis 
--'3', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1
--Provjeriti stanje u tabelama Autori, Autori_log i Autori_instead_log.
INSERT INTO Autori
VALUES ('3', 'Ringer', 'Albert', '801 826-0752', '67 Seventh Av.', 'Salt Lake City', 'UT', 84152, 1)

SELECT * FROM Autori
SELECT * FROM Autori_log
SELECT * FROM Autori_instead_log

--32.	Iskljuèiti sve okidaèe nad tabelom autori.
GO
DISABLE TRIGGER ALL ON Autori

--33.	Ukljuèiti sve okidaèe nad tabelom autori.
GO
ENABLE TRIGGER ALL ON Autori

--34.	U tabelu autori dodadati novo polje ModifiedDate. Nakon toga kreirati okidač t_updateMD kojim će se nakon promjene neke vrijednosti unutar tabele autori setovati ModifiedDate na trenutni datum. Voditi računa o tome da pri update-u npr zapisa sa ID-om 172-32-1176 se modificira datum samo za tog autora (ne za sve).
GO
ALTER TABLE Autori
ADD ModifiedDate DATETIME
GO
DISABLE TRIGGER t_instead_upd_autori ON Autori
GO
DISABLE TRIGGER t_update ON Autori

GO
CREATE TRIGGER t_updateMD
ON Autori
AFTER UPDATE
AS
BEGIN
	UPDATE Autori
	SET ModifiedDate=GETDATE()
	WHERE Autori.au_id IN (SELECT au_id FROM inserted)
	--SELECT au_id FROM inserted
END
GO

--ENABLE TRIGGER t_updateMD ON Autori

UPDATE Autori
SET au_fname='Amy'
WHERE au_id like '172-32-1176'

select *
from Autori


--DROP TRIGGER t_update
--DROP TRIGGER t_instead_upd_autori

--35.	Kreirati bazu Indeksi i aktivirati je.
CREATE DATABASE Indeksi
GO
USE Indeksi

--36.	Kreirati tabelu ProizvodiOsobe koja će nastati spajanjem tabela Product i Person baze AdventureWorks2017 CROSS JOIN-om i prilikom kreiranja importovati 10 miliona zapisa.  
SELECT TOP 100000000 P.ProductID,P.Name,P.ProductNumber,P.Color,P.ListPrice,PP.BusinessEntityID,PP.FirstName,PP.LastName,PP.MiddleName
INTO ProizvodiOsobe
FROM AdventureWorks2017.Production.Product AS P
CROSS JOIN AdventureWorks2017.Person.Person AS PP

--37.	Kreirati nonclustered index kojim će se ubrzati pretraga po imenu i prezimenu. Kreirati testni slučaj i pogledati aktualni plan izvršenja. Izbrisati kreirani index.
CREATE INDEX IX_proizvodiOsobe_FirstName_LastName
ON ProizvodiOsobe(FirstName,LastName)

SELECT PO.FirstName,PO.LastName
FROM ProizvodiOsobe AS PO
WHERE PO.FirstName LIKE 'A%' AND PO.LastName LIKE 'S%'

DROP INDEX IX_proizvodiOsobe_FirstName_LastName
ON ProizvodiOsobe

--38.	Kreirati nonclustered indeks koji će omogućiti bržu pretragu prema imenu i prezimenu a također pretraga će biti ubrzana iako se prikaže srednje ime. Kreirati testni slučaj i pogledati plan izvršenja. Izbrisati kreirani index.
CREATE INDEX IX_proizvodiOsobe_FirstName_LastName_INC_MiddleName
ON ProizvodiOsobe(FirstName,LastName) INCLUDE(MiddleName)

SELECT PO.FirstName,PO.LastName,PO.MiddleName
FROM ProizvodiOsobe AS PO
WHERE PO.FirstName LIKE 'A%' AND PO.LastName LIKE 'S%' and po.MiddleName like 'L'
GROUP BY  PO.FirstName,PO.LastName,PO.MiddleName

DROP INDEX IX_proizvodiOsobe_FirstName_LastName_INC_MiddleName
ON ProizvodiOsobe

--39.	Kreirati kompozitni primarni ključ nad kolonama ProductId i BusindessEntityId. Kreirati testni slučaj za upotrebu primarnog ključa.
ALTER TABLE ProizvodiOsobe 
ADD CONSTRAINT PK_ProizvodiOsobe PRIMARY KEY (ProductId, BusinessEntityId)

SELECT *
FROM ProizvodiOsobe AS PO
WHERE PO.ProductId = 1 AND PO.BusinessEntityID=14951

ALTER TABLE ProizvodiOsobe
DROP PK_ProizvodiOsobe

--40.	Kreirati clustered index nad kolonom ProductNumber. Kreirati testni slučaj za upotrebu indexa i pogledati plan izvršenja. Izbrisati kreirani index.
CREATE CLUSTERED INDEX IX_proizvodiOsobe_ProductNumber
ON ProizvodiOsobe(ProductNumber)

SELECT *
FROM ProizvodiOsobe AS PO
WHERE PO.ProductNumber LIKE 'A%'

DROP INDEX IX_proizvodiOsobe_ProductNumber
ON ProizvodiOsobe

