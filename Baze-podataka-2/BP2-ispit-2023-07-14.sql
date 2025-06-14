--1. Kroz SQL kod kreirati bazu podataka sa imenom vašeg broja indeksa.

GO
CREATE DATABASE [2023-07-14]
GO
USE [2023-07-14]

--2. U kreiranoj bazi podataka kreirati tabele sa sljedećom strukturom:
--a) Prodavaci
--• ProdavacID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• Ime, 50 UNICODE (obavezan unos)
--• Prezime, 50 UNICODE (obavezan unos)
--• OpisPosla, 50 UNICODE karaktera (obavezan unos)
--• EmailAdresa, 50 UNICODE karaktera

CREATE TABLE Prodavaci
(
	ProdavacID		INT				CONSTRAINT PK_Prodavaci		PRIMARY KEY		IDENTITY(1, 1),
	Ime				NVARCHAR(50)	NOT NULL,
	Prezime			NVARCHAR(50)	NOT NULL,
	OpisPosla		NVARCHAR(50)	NOT NULL,
	EmailAdresa		NVARCHAR(50)
)

--b) Proizvodi
--• ProizvodID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• Naziv, 50 UNICODE karaktera (obavezan unos)
--• SifraProizvoda, 25 UNICODE karaktera (obavezan unos)
--• Boja, 15 UNICODE karaktera
--• NazivPodkategorije, 50 UNICODE (obavezan unos)

CREATE TABLE Proizvodi
(
	ProizvodID				INT				CONSTRAINT PK_Proizvodi		PRIMARY KEY		IDENTITY(1, 1),
	Naziv					NVARCHAR(50)	NOT NULL,
	SifraProizvoda			NVARCHAR(25)	NOT NULL,
	Boja					NVARCHAR(15),
	NazivPodkategorije		NVARCHAR(50)	NOT NULL
)

--c) ZaglavljeNarudzbe
--• NarudzbaID, cjelobrojna vrijednost i primarni ključ, autoinkrement
--• DatumNarudzbe, polje za unos datuma i vremena (obavezan unos)
--• DatumIsporuke, polje za unos datuma i vremena
--• KreditnaKarticaID, cjelobrojna vrijednost
--• ImeKupca, 50 UNICODE (obavezan unos)
--• PrezimeKupca, 50 UNICODE (obavezan unos)
--• NazivGradaIsporuke, 30 UNICODE (obavezan unos)
--• ProdavacID, cjelobrojna vrijednost, strani ključ
--• NacinIsporuke, 50 UNICODE (obavezan unos)

CREATE TABLE ZaglavljeNarudzbe
(
	NarudzbaID			INT				CONSTRAINT PK_ZaglavljeNarudzbe		PRIMARY KEY		IDENTITY(1, 1),
	DatumNarudzbe		DATETIME		NOT NULL,
	DatumIsporuke		DATETIME,
	KreditnaKarticaID	INT,
	ImeKupca			NVARCHAR(50)	NOT NULL,
	PrezimeKupca		NVARCHAR(50)	NOT NULL,
	NazivGradaIsporuke	NVARCHAR(30)	NOT NULL,
	ProdavacID			INT				CONSTRAINT FK_ZaglavljeNarudzbe_Prodavaci FOREIGN KEY REFERENCES Prodavaci(ProdavacID),
	NacinIsporuke		NVARCHAR(50)	NOT NULL
)

--d) DetaljiNarudzbe
--• NarudzbaID, cjelobrojna vrijednost, obavezan unos i strani ključ
--• ProizvodID, cjelobrojna vrijednost, obavezan unos i strani ključ
--• Cijena, novčani tip (obavezan unos),
--• Kolicina, skraćeni cjelobrojni tip (obavezan unos),
--• Popust, novčani tip (obavezan unos)
--• OpisSpecijalnePonude, 255 UNICODE (obavezan unos)
--**Jedan proizvod se može više puta naručiti, dok jedna narudžba može sadržavati više proizvoda. U okviru jedne narudžbe jedan proizvod se može naručiti više puta.

CREATE TABLE DetaljiNarudzbe
(
	NarudzbaID				INT					CONSTRAINT FK_DetaljiNarudzbe_ZaglavljeNarudzbe FOREIGN KEY REFERENCES ZaglavljeNarudzbe(NarudzbaID),
	ProizvodID				INT					CONSTRAINT FK_DetaljiNarudzbe_Proizvodi FOREIGN KEY REFERENCES Proizvodi(ProizvodID)	NOT NULL,
	Cijena					MONEY				NOT NULL,
	Kolicina				SMALLINT			NOT NULL,
	Popust					MONEY				NOT NULL,
	OpisSpecijalnePonude	NVARCHAR(255)		NOT NULL,

	StavkaNarudzbeID		INT					IDENTITY(1, 1),

	CONSTRAINT PK_DetaljiNarudzbe PRIMARY KEY (NarudzbaID, StavkaNarudzbeID, OpisSpecijalnePonude)

	-- ovo ogranicenje cu u ovom ispitnom rijesiti dodavajuci na svoju incijativu atribut StavkaNarudzbeID
)

--9 bodova
--3. Iz baze podataka AdventureWorks u svoju bazu podataka prebaciti sljedeće podatke:
--a) U tabelu Prodavaci dodati sve prodavače
--• BusinessEntityID (SalesPerson) -> ProdavacID
--• FirstName (Person) -> Ime
--• LastName (Person) -> Prezime
--• JobTitle (Employee) -> OpisPosla
--• EmailAddress (EmailAddress) -> EmailAdresa

SET IDENTITY_INSERT Prodavaci ON
INSERT INTO Prodavaci
(
	ProdavacID,
	Ime,
	Prezime,
	OpisPosla,
	EmailAdresa
)
SELECT
	SP.BusinessEntityID,
	P.FirstName,
	P.LastName,
	E.JobTitle,
	EA.EmailAddress
FROM AdventureWorks2017.Sales.SalesPerson AS SP	
	INNER JOIN AdventureWorks2017.HumanResources.Employee AS E ON SP.BusinessEntityID = E.BusinessEntityID
	INNER JOIN AdventureWorks2017.Person.Person AS P ON E.BusinessEntityID = P.BusinessEntityID
	INNER JOIN AdventureWorks2017.Person.EmailAddress AS EA ON P.BusinessEntityID = EA.BusinessEntityID
SET IDENTITY_INSERT Prodavaci OFF

--b) U tabelu Proizvodi dodati sve proizvode
--• ProductID (Product)-> ProizvodID
--• Name (Product)-> Naziv
--• ProductNumber (Product)-> SifraProizvoda
--• Color (Product)-> Boja
--• Name (ProductSubategory) -> NazivPodkategorije

SET IDENTITY_INSERT Proizvodi ON
INSERT INTO Proizvodi
(
	ProizvodID,
	Naziv,
	SifraProizvoda,
	Boja,
	NazivPodkategorije
)
SELECT
	P.ProductID,
	P.Name,
	P.ProductNumber,
	P.Color,
	PS.Name
FROM AdventureWorks2017.Production.Product AS P	
	INNER JOIN AdventureWorks2017.Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
SET IDENTITY_INSERT Proizvodi OFF

--c) U tabelu ZaglavljeNarudzbe dodati sve narudžbe
--• SalesOrderID (SalesOrderHeader) -> NarudzbaID
--• OrderDate (SalesOrderHeader)-> DatumNarudzbe
--• ShipDate (SalesOrderHeader)-> DatumIsporuke
--• CreditCardID(SalesOrderID)-> KreditnaKarticaID
--• FirstName (Person) -> ImeKupca
--• LastName (Person) -> PrezimeKupca
--• City (Address) -> NazivGradaIsporuke
--• SalesPersonID (SalesOrderHeader)-> ProdavacID
--• Name (ShipMethod)-> NacinIsporuke

SET IDENTITY_INSERT ZaglavljeNarudzbe ON
INSERT INTO ZaglavljeNarudzbe
(
	NarudzbaID,
	DatumNarudzbe,
	DatumIsporuke,
	KreditnaKarticaID,
	ImeKupca,
	PrezimeKupca,
	NazivGradaIsporuke,
	ProdavacID,
	NacinIsporuke
)
SELECT
	SOH.SalesOrderID,
	SOH.OrderDate,
	SOH.ShipDate,
	SOH.CreditCardID,
	P.FirstName,
	P.LastName,
	A.City,
	SOH.SalesPersonID,
	SM.Name
FROM AdventureWorks2017.Sales.SalesOrderHeader AS SOH
	INNER JOIN AdventureWorks2017.Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
	INNER JOIN AdventureWorks2017.Person.Person AS P ON C.PersonID = P.BusinessEntityID
	INNER JOIN AdventureWorks2017.Person.Address AS A ON SOH.ShipToAddressID = A.AddressID
	INNER JOIN AdventureWorks2017.Purchasing.ShipMethod AS SM ON SOH.ShipMethodID = SM.ShipMethodID
SET IDENTITY_INSERT ZaglavljeNarudzbe OFF

--d) U tabelu DetaljiNarudzbe dodati sve stavke narudžbe
--• SalesOrderID (SalesOrderDetail)-> NarudzbaID
--• ProductID (SalesOrderDetail)-> ProizvodID
--• UnitPrice (SalesOrderDetail)-> Cijena
--• OrderQty (SalesOrderDetail)-> Kolicina
--• UnitPriceDiscount (SalesOrderDetail)-> Popust
--• Description (SpecialOffer) -> OpisSpecijalnePonude
--10 bodova

SET IDENTITY_INSERT DetaljiNarudzbe ON
INSERT INTO DetaljiNarudzbe
(
	NarudzbaID,
	StavkaNarudzbeID,
	ProizvodID,
	Cijena,
	Kolicina,
	Popust,
	OpisSpecijalnePonude
)
SELECT
	SOD.SalesOrderID,
	SOD.SalesOrderDetailID,
	SOD.ProductID,
	SOD.UnitPrice,
	SOD.OrderQty,
	SOD.UnitPriceDiscount,
	SO.Description
FROM AdventureWorks2017.Sales.SalesOrderDetail AS SOD
	INNER JOIN AdventureWorks2017.Sales.SpecialOfferProduct AS SOP ON SOD.ProductID = SOP.ProductID
	INNER JOIN AdventureWorks2017.Sales.SpecialOffer AS SO ON SOP.SpecialOfferID = SO.SpecialOfferID
SET IDENTITY_INSERT DetaljiNarudzbe OFF

--4.
--a) (6 bodova) Kreirati funkciju f_detalji u formi tabele gdje korisniku slanjem parametra identifikacijski broj narudžbe će biti ispisano spojeno ime i prezime kupca, grad isporuke, ukupna vrijednost narudžbe sa popustom, te poruka da li je narudžba plaćena karticom ili ne. Korisnik može dobiti 2 poruke „Plaćeno karticom“ ili „Nije plaćeno karticom“. OBAVEZNO kreirati testni slučaj. (Novokreirana baza)

GO
CREATE OR ALTER FUNCTION f_detalji
(
	@NarudzbaID INT
)
RETURNS TABLE
AS
RETURN
	SELECT
		CONCAT(ZN.ImeKupca, ' ', ZN.PrezimeKupca) AS [Ime i prezime],
		ZN.NazivGradaIsporuke,
		SUM(DN.Cijena * DN.Kolicina * (1 - DN.Popust)) AS [Ukupna vrijednost narudžbe sa popustom],
		IIF(ZN.KreditnaKarticaID IS NULL, 'Nije plaćeno karticom', 'Plaćeno karticom') AS [Način plaćanja]
	FROM ZaglavljeNarudzbe AS ZN
		INNER JOIN DetaljiNarudzbe AS DN ON ZN.NarudzbaID = DN.NarudzbaID
	WHERE ZN.NarudzbaID = @NarudzbaID
	GROUP BY ZN.ImeKupca, ZN.PrezimeKupca, ZN.NazivGradaIsporuke, ZN.KreditnaKarticaID
GO

SELECT * FROM ZaglavljeNarudzbe

SELECT * FROM f_detalji(43714)

--b) (4 bodova) U kreiranoj bazi kreirati proceduru sp_insert_DetaljiNarudzbe kojom će se omogućiti insert nove stavke narudžbe. OBAVEZNO kreirati testni slučaj. (Novokreirana baza)

GO
CREATE OR ALTER PROCEDURE sp_insert_DetaljiNarudzbe
(
	@NarudzbaID INT,
	@ProizvodID INT,
	@Cijena MONEY,
	@Kolicina INT,
	@Popust MONEY,
	@OpisSpecijalnePonude NVARCHAR(255)
)
AS
BEGIN
	INSERT INTO DetaljiNarudzbe
	(
		NarudzbaID,
		ProizvodID,
		Cijena,
		Kolicina,
		Popust,
		OpisSpecijalnePonude
	)
	VALUES
	(
		@NarudzbaID,
		@ProizvodID,
		@Cijena,
		@Kolicina,
		@Popust,
		@OpisSpecijalnePonude
	)
END
GO

SELECT * FROM DetaljiNarudzbe

exec sp_insert_DetaljiNarudzbe
	@NarudzbaID = 43659,
	@ProizvodID = 776,
	@Cijena = 2023,
	@Kolicina = 1,
	@Popust = 0,
	@OpisSpecijalnePonude = 'Nema popusta'

--c) (6 bodova) Kreirati upit kojim će se prikazati ukupan broj proizvoda po kategorijama. Korisnicima se treba ispisati o kojoj kategoriji se radi. Uslov je da se prikažu samo one kategorije kojima pripada više od 30 proizvoda, te da nazivi proizvoda se sastoje od 3 riječi, a sadrže broj u bilo kojoj od riječi i još uvijek se nalaze u prodaji. Također, ukupan broj proizvoda po kategorijama mora biti veći od 50. (AdventureWorks2017)

GO
USE AdventureWorks2017


SELECT
	PC.Name,
	COUNT(*) AS [Broj proizvoda]
FROM Production.Product AS P
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
WHERE 
	P.Name LIKE '% % %' 
	AND (P.Name NOT LIKE '% %' OR P.Name NOT LIKE '% % % %') 
	AND P.Name LIKE '%[0-9]%'
	AND P.SellEndDate IS NULL
GROUP BY PC.Name
HAVING COUNT(*) > 30

--d) (7 bodova) Za potrebe menadžmenta kompanije potrebno je kreirati upit kojim će se prikazati proizvodi koji trenutno nisu u prodaji i ne pripada kategoriji bicikala, kako bi ih ponovno vratili u prodaju. Proizvodu se početkom i po prestanku prodaje zabilježi datum. Osnovni uslov za ponovno povlačenje u prodaju je to da je ukupna prodana količina za svaki proizvod pojedinačno bila veća od 200 komada. Kao rezultat upita očekuju se podaci u formatu npr. Laptop 300kom itd. (AdventureWorks2017)

SELECT
	P.Name,
	CONCAT(SUM(SOD.OrderQty), ' kom') AS [Ukupna prodana količina]
FROM Production.Product AS P
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
WHERE PC.Name NOT LIKE 'Bikes' AND P.SellEndDate IS NOT NULL
GROUP BY P.Name
HAVING SUM(SOD.OrderQty) > 200

--e) (7 bodova) Kreirati upit kojim će se prikazati identifikacijski broj narudžbe, spojeno ime i prezime kupca, te ukupna vrijednost narudžbe koju je kupac platio. Uslov je da je od datuma narudžbe do datuma isporuke proteklo manje dana od prosječnog broja dana koji je bio potreban za isporuku svih narudžbi. (AdventureWorks2017)
--30 bodova

SELECT
	SOH.SalesOrderID,
	CONCAT(P.FirstName, ' ', P.LastName) AS [Ime i prezime],
	SOH.SubTotal
FROM Sales.SalesOrderHeader AS SOH
	INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
	INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
WHERE DATEDIFF(DAY, OrderDate, ShipDate) <
											(
											SELECT 
												AVG(CAST(DATEDIFF(DAY, OrderDate, ShipDate) AS decimal(18,10))) AS [Prosjecna razlika dana]
											FROM Sales.SalesOrderHeader
											)
--5.
--a) (9 bodova) Kreirati upit koji će prikazati one naslove kojih je ukupno prodano više od 30 komada a napisani su od strane autora koji su napisali 2 ili više djela/romana. U rezultatima upita prikazati naslov i ukupnu prodanu količinu. (Pubs)

GO
USE pubs


SELECT
	T.title_id,
	SUM(S.qty) AS [Ukupna prodana količina]
FROM titleauthor AS TA
	INNER JOIN titles AS T ON TA.title_id = T.title_id
	INNER JOIN sales AS S ON T.title_id = S.title_id
WHERE TA.au_id IN
					(
					SELECT
						TA.au_id
					FROM titleauthor AS TA
						INNER JOIN titles AS T ON TA.title_id = T.title_id
					GROUP BY TA.au_id
					HAVING COUNT(*) >= 2
					)
GROUP BY T.title_id
HAVING SUM(S.qty) > 30

--b) (10 bodova) Kreirati upit koji će u % prikazati koliko je narudžbi (od ukupnog broja kreiranih) isporučeno na svaku od teritorija pojedinačno. Npr Australia 20.2%, Canada 12.01% itd. Vrijednosti dobijenih postotaka zaokružiti na dvije decimale i dodati znak %. (AdventureWorks2017)

GO
USE AdventureWorks2017


SELECT
	ST.Name,
	CONCAT(
	CAST(
	CAST(COUNT(*) AS DECIMAL(18, 2)) * 100 /
											(
											SELECT
												COUNT(*)
											FROM Sales.SalesOrderHeader AS SOH
											) AS decimal(18, 2)), ' %')
FROM Sales.SalesOrderHeader AS SOH
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
GROUP BY ST.Name


SELECT
	COUNT(*)
FROM Sales.SalesOrderHeader AS SOH

--c) (12 bodova) Kreirati upit koji će prikazati osobe koje imaju redovne prihode a nemaju vanredne, i one koje imaju vanredne a nemaju redovne. Lista treba da sadrži spojeno ime i prezime osobe, grad i adresu stanovanja i ukupnu vrijednost ostvarenih prihoda (za redovne koristiti neto). Pored navedenih podataka potrebno je razgraničiti kategorije u novom polju pod nazivom Opis na način "ISKLJUČIVO VANREDNI" za one koji imaju samo vanredne prihode, ili "ISKLJUČIVO REDOVNI" za one koji imaju samo redovne prihode. Konačne rezultate sortirati prema opisu abecedno i po ukupnoj vrijednosti ostvarenih prihoda u opadajućem redoslijedu. (prihodi)
--31 bod

GO
USE prihodi

-- NAČIN SA JOINOVIMA

SELECT
	SQ.[Ime i prezime],
	SQ.Grad,
	SQ.Adresa,
	SUM(SQ.Prihod) AS [Ukupna vrijednost ostvarenih prihoda],
	SQ.Opis
FROM
	(
	SELECT
		CONCAT(O.Ime, ' ', O.PrezIme) AS [Ime i prezime],
		G.Grad,
		O.Adresa,
		IIF(RP.RedovniPrihodiID IS NULL, VP.IznosVanrednogPrihoda, RP.Neto) AS Prihod,
		IIF(RP.RedovniPrihodiID IS NULL, 'ISKLJUČIVO VANREDNI', 'ISKLJUČIVO REDOVNI') AS Opis
	FROM RedovniPrihodi AS RP
		FULL OUTER JOIN VanredniPrihodi AS VP ON RP.OsobaID = VP.OsobaID

		INNER JOIN Osoba AS O ON ISNULL(RP.OsobaID, VP.OsobaID) = O.OsobaID
		INNER JOIN Grad AS G ON O.GradID = G.GradID
	WHERE 
		RP.OsobaID IS NULL OR VP.OsobaID IS NULL
	) AS SQ
GROUP BY SQ.[Ime i prezime], SQ.Grad, SQ.Adresa, SQ.Opis
ORDER BY 5 ASC, 4 DESC


-- NAČIN SA UNIJOM

SELECT *
FROM
	(
	SELECT
		CONCAT(O.Ime, ' ', O.PrezIme) AS [Ime i prezime],
		G.Grad,
		O.Adresa,
		SUM(RP.Neto) AS [Ukupna vrijednost ostvarenih prihoda],
		'ISKLJUČIVO REDOVNI' AS Opis
	FROM Osoba AS O
		INNER JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
		INNER JOIN Grad AS G ON O.GradID = G.GradID
		LEFT JOIN VanredniPrihodi AS VP ON O.OsobaID = VP.OsobaID
	WHERE VP.OsobaID IS NULL
	GROUP BY O.Ime, O.PrezIme, G.Grad, O.Adresa

	UNION ALL
	-- jer je kao brže

	SELECT
		CONCAT(O.Ime, ' ', O.PrezIme) AS [Ime i prezime],
		G.Grad,
		O.Adresa,
		SUM(VP.IznosVanrednogPrihoda) AS [Ukupna vrijednost ostvarenih prihoda],
		'ISKLJUČIVO VANREDNI' AS Opis
	FROM Osoba AS O
		INNER JOIN VanredniPrihodi AS VP ON O.OsobaID = VP.OsobaID
		INNER JOIN Grad AS G ON O.GradID = G.GradID
		LEFT JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
	WHERE RP.OsobaID IS NULL
	GROUP BY O.Ime, O.PrezIme, G.Grad, O.Adresa
	) AS SQ
ORDER BY 5 ASC, 4 DESC

--6. Dokument teorijski_ispit 14JUL23, preimenovati vašim brojem indeksa,te u tom dokumentu izraditi pitanja.
--20 bodova
--SQL skriptu (bila prazna ili ne) imenovati Vašim brojem indeksa npr IB210001.sql, teorijski dokument imenovan Vašim brojem indexa npr IB210001.docx upload-ovati ODVOJEDNO na ftpu folder Upload.
--Maksimalan broj bodova:100
--Prag prolaznosti: 55