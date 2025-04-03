-- 1. Koristeći bazu Northwind izdvojiti godinu, mjesec i dan datuma isporuke narudžbe. 

USE Northwind;

-- 1. nacin
SELECT YEAR(O.ShippedDate) Godina, MONTH(O.ShippedDate) Mjesec, DAY(O.ShippedDate) Dan
FROM Orders AS O;

-- 2. nacin
SELECT DATEPART(YEAR, O.ShippedDate) Godina, DATEPART(MONTH, O.ShippedDate) Mjesec, DATEPART(DAY, O.ShippedDate) Dan
FROM Orders AS O;

-- 2. Koristeći bazu Northwind izračunati koliko je godina prošlo od datum narudžbe do danas.

SELECT DATEDIFF(YEAR, O.OrderDate, GETDATE()) Razlika
FROM Orders AS O;

-- 3. Koristeći bazu Northwind dohvatiti sve kupce kod kojih se poštanski broj sastoji samo od cifara. 

SELECT C.ContactName, C.PostalCode
FROM Customers AS C
WHERE C.PostalCode NOT LIKE '%[a-zA-Z]%' AND C.PostalCode NOT LIKE '%-%';

-- ILI

SELECT C.ContactName, C.PostalCode
FROM Customers AS C
WHERE ISNUMERIC(C.PostalCode) = 1;

-- 4. Koristeći bazu AdventureWorks2017 prikazati spojeno ime, srednje ime i prezime osobe. Uslov je da se između pojedinih segmenata nalazi space. Omogućiti prikaz podataka i ako neki od podataka nije unijet. Prikazati samo jedinstvene zapise (bez ponavljanja istih zapisa). 

USE AdventureWorks2017;

SELECT DISTINCT P.FirstName + ISNULL(' ' + P.MiddleName, '') + ' ' + P.LastName AS 'Ime i prezime'
FROM Person.Person AS P;

SELECT DISTINCT CONCAT(P.FirstName, ' ', P.MiddleName, ' ', P.LastName)
FROM Person.Person AS P;

-- 5. Koristeći bazu Pubs prikazati 10 količinski najvećih stavki prodaje. Lista treba da sadrži broj narudžbe, datum narudžbe i količinu. Provjeriti da li ima više stavki sa količinom kao posljednja u listi, te uključiti ih u rezultate upita ukoliko postoje. 
 
 USE pubs;

 SELECT TOP 10 WITH TIES S.ord_num, S.ord_date, S.qty
 FROM sales AS S
 ORDER BY 3 DESC;

 -- TOP 10 - DA ODABEREMO PRVIH 10
 -- WITH TIES - UKOLIKO SU NEKI ELEMENTI ISTI (PO NEKOJ VRIJEDNOSTI), UZIMA SVE NJIH

-- Northwind 

USE Northwind;

-- 6. Prikazati podatke o narudžbama koje su napravljene prije 19.07.1996. godine. Izlaz treba da sadrži sljedeće kolone: Id narudžbe, datum narudžbe, ID kupca, te grad. 

SELECT O.OrderID, O.OrderDate, O.CustomerID, O.ShipCity
FROM Orders AS O
WHERE O.OrderDate < '1996-07-19';

-- 7. Prikazati nazive proizvoda, njihovu cijenu te naziv i telefonski broj dobavljača. 

SELECT P.ProductName, P.UnitPrice, S.CompanyName, S.Phone
FROM Products AS P 
	INNER JOIN Suppliers AS S ON P.SupplierID = S.SupplierID;

/*
	equi join
	non-equi join
	self join
	cross join
*/

-- 8. Prikazati imena i prezimena (spojeno) radnika koji imaju nadređenog te ime i prezime (spojeno) osobe koja im je nadređena. Izlaz sortirati abecednim redoslijedom po imenu i prezimenu nadređenog. 

SELECT CONCAT(EMP.FirstName, ' ', EMP.LastName) 'Ime i prezime radnika', CONCAT(BOSS.FirstName, ' ', BOSS.LastName) 'Ime i prezime nadredjenog'
FROM Employees AS EMP INNER JOIN Employees AS BOSS ON EMP.ReportsTo = BOSS.EmployeeID
ORDER BY [Ime i prezime nadredjenog];

-- 9. Prikazati radnike koji posluju na područjima Boston-a, Cambridge-a ili New York-a. Izlaz treba sadržavati sljedeće kolone: Ime i prezime radnika i naziv područja na kojem posluje. 
 
SELECT CONCAT(E.FirstName, ' ', E.LastName), T.TerritoryDescription
FROM Employees AS E 
	INNER JOIN EmployeeTerritories AS ET ON E.EmployeeID = ET.EmployeeID
	INNER JOIN Territories AS T ON ET.TerritoryID = T.TerritoryID
WHERE T.TerritoryDescription IN ('Boston', 'Cambridge', 'New York');

-- Baza Vjezbe0 (dostupna kao skripta BazaV0.sql) 

USE Vjezbe0;

-- 10. Prikazati kojem rangu primanja pripadaju radnici tablice Radnik, prikazati rang i raspon vrijednosti (spojeno), također prikazati ime i prezime radnika (spojeno). 

 SELECT CONCAT(R.Ime, ' ', R.Prezime) 'Ime i prezime', R.Placa, S.Rang, CONCAT(S.Min, ' - ', S.Max) 'Raspon'
 FROM Radnik AS R, Stupanj AS S
 WHERE R.Placa BETWEEN S.Min AND S.Max
 ORDER BY 1;

 -- ILI

 SELECT CONCAT(R.Ime, ' ', R.Prezime) 'Ime i prezime', R.Placa, S.Rang, CONCAT(S.Min, ' - ', S.Max) 'Raspon'
 FROM Radnik AS R 
	INNER JOIN Stupanj AS S ON R.Placa BETWEEN S.Min AND S.Max
 ORDER BY 1;

-- Prihodi 

USE prihodi;

-- 11. Prikazati imena i prezimena svih osoba i dati pregled svih njihovih vanrednih primanja. U rezultatu upita moraju biti i osobe koje nemaju vanrednih primanja.

SELECT O.Ime, O.PrezIme, VP.IznosVanrednogPrihoda
FROM Osoba AS O 
	LEFT JOIN VanredniPrihodi AS VP ON O.OsobaID = VP.OsobaID;

-- 12. Prethodni upit modificirati da prikaže samo one osobe koje nemaju vanredna primanja. 

SELECT O.Ime, O.PrezIme, VP.IznosVanrednogPrihoda
FROM Osoba AS O 
	LEFT JOIN VanredniPrihodi AS VP ON O.OsobaID = VP.OsobaID
WHERE VP.VanredniPrihodiID IS NULL;

-- 13. Koristeći ispravno spajanje prikazati ID, imena i prezimena osoba te ID i neto iznos redovnih primanja. Prikazati i sve osobe i sva primanja. Analizirajte da li postoje primanja koja nisu dodijeljena ni jednoj osobi. 

SELECT O.OsobaID, O.Ime, O.PrezIme, RP.RedovniPrihodiID, RP.Neto
FROM Osoba AS O 
	FULL JOIN RedovniPrihodi AS RP ON O.OsobaID = RP.OsobaID
WHERE O.OsobaID IS NULL;

-- Northwind 

USE Northwind;

-- 14. Prikazati stavke narudžbe gdje je količina narudžbe bila veća od 100 komada uz odobreni popust.

SELECT *
FROM [Order Details] AS OD
WHERE OD.Quantity > 100 AND OD.Discount <> 0;

-- 15. Za svaku narudžbu prikazati ID i naziv dostavljača.

SELECT O.OrderID, S.CompanyName
FROM Orders AS O
	INNER JOIN Shippers AS S ON O.ShipVia = S.ShipperID;

-- 16. Prikazati sve kupce koje u koloni ContactTitle sadrže pojam "manager". 

SELECT *
FROM Customers AS C
WHERE C.ContactTitle LIKE '%manager%';

-- 17. Prikazati listu zaposlenika sa sljedećim atributima: Id, ime, prezime, država i titula, gdje je Id 9 ili dolaze iz Amerike. 

SELECT E.EmployeeID, E.FirstName, E.LastName, E.Country, E.Title
FROM Employees AS E
WHERE E.EmployeeID = 9 OR E.Country = 'USA';

-- 18. Prikazati ime kompanije kupca i kontakt telefon i to samo onih koji u svome imenu posjeduju riječ „Restaurant“. Ukoliko naziv kompanije sadrži karakter (-), kupce izbaciti iz rezultata upita. 

SELECT C.CompanyName, C.Phone
FROM Customers AS C
WHERE C.CompanyName LIKE '%Restaurant%' AND C.CompanyName NOT LIKE '%-%';

-- 19. Prikazati proizvode čiji naziv počinje slovima „C“ ili „G“, drugo slovo može biti bilo koje, a treće slovo u nazivu je „A“ ili „O“.

SELECT *
FROM Products AS P
WHERE P.ProductName LIKE '[CG][a-z][ao]%';

-- 20. Prikazati listu proizvoda čiji naziv počinje slovima „L“ ili „T“, ili je ID proizvoda = 46. Lista treba da sadrži samo one proizvode čija se cijena po komadu kreće između 10 i 50 (uključujući granične vrijednosti). Upit napisati na dva načina.

SELECT *
FROM Products AS P
WHERE (P.ProductName LIKE '[LT]%' OR P.ProductID = 46) AND P.UnitPrice BETWEEN 10 AND 50;

-- 21. Prikazati naziv proizvoda i cijenu, gdje je stanje na zalihama manje od naručene količine. Također, u rezultate upita uključiti razliku između stanja zaliha i naručene količine.

SELECT P.ProductName, P.UnitPrice, P.UnitsInStock - P.UnitsOnOrder 'Razlika u stanju'
FROM Products AS P
WHERE P.UnitsInStock < P.UnitsOnOrder;

-- 22. Prikazati sve podatke o dobavljačima koji dolaze iz Španije ili Njemačke a nemaju unesen broj faxa. Formatirati izlaz NULL vrijednosti na način da se prikaže umjesto NULL prikladno objašnjenje. Upit napisati na dva načina. 

SELECT S.SupplierID, S.CompanyName, S.ContactName, S.ContactTitle, S.Address, S.City, S.Region, S.PostalCode, S.CompanyName, S.Phone, ISNULL(S.Fax, 'nepoznata vrijednost'), S.HomePage
FROM Suppliers AS S
WHERE S.Country IN ('Spain', 'Germany') AND S.Fax IS NULL;

-- Pubs 

USE pubs;

-- 23. Prikazati naslove knjiga te imena i prezimena njihovih autora (spojeno). 

SELECT T.title, CONCAT(A.au_fname, ' ', au_lname) 
FROM titles AS T
	INNER JOIN titleauthor AS TA ON T.title_id = TA.title_id
	INNER JOIN authors AS A ON A.au_id = TA.au_id;


-- 24. Prikazati listu autora sa sljedećim kolonama: Id, ime i prezime (spojeno), grad i to samo one autore čiji Id počinje brojem 8 ili dolaze iz grada „Salt Lake City“. Također autorima status ugovora treba biti 1. Koristiti aliase nad kolonama. 

SELECT A.au_id 'ID', CONCAT(A.au_fname, ' ', A.au_lname) 'Ime i prezime', A.city 'Grad'
FROM authors AS A
WHERE (A.au_id LIKE '8%' OR A.city = 'Salt Lake City') AND A.contract = 1;


-- 25. Prikazati sve tipove knjiga bez duplikata. Listu sortirati u abecednom redoslijedu. 

SELECT DISTINCT T.type
FROM titles AS T
ORDER BY 1;

-- 26. Prikazati listu prodaje knjiga sa sljedećim kolonama: Id prodavnice, broj narudžbe i količinu, ali samo gdje je količina između 10 i 50, uključujući i granične vrijednosti. Rezultat upita sortirati po količini opadajućim redoslijedom. Upit napisati na dva načina. 

--		1.
SELECT ST.stor_id, S.ord_num, S.qty
FROM titles AS T
	INNER JOIN sales AS S ON T.title_id = S.title_id
	INNER JOIN stores AS ST ON S.stor_id = ST.stor_id
WHERE S.qty BETWEEN 10 AND 50
ORDER BY S.qty DESC;

--		2.
SELECT ST.stor_id, S.ord_num, S.qty
FROM stores AS ST
	INNER JOIN sales AS S ON ST.stor_id = S.stor_id
	INNER JOIN titles AS T ON S.title_id = T.title_id
WHERE S.qty BETWEEN 10 AND 50
ORDER BY S.qty DESC;

-- 27. Prikazati listu knjiga sa sljedećim kolonama: naslov, tip djela i cijena. Kao novu kolonu dodati 20% od prikazane cijene (npr. Ako je cijena 19.99 u novoj koloni treba da piše 3,998). Naziv kolone se treba zvati „20% od cijene“. Listu sortirati abecedno po tipu djela i po cijeni opadajućim redoslijedom. Sa liste eliminisati one knjige koje nemeju pohranjenu vrijednost cijene. Modifikovati upit tako da uz već prikazane kolone se prikaže i cijena umanjena za 20 %. Naziv kolone treba da se zove „Cijena umanjena za 20%“.

SELECT T.title 'Naslov', T.type 'Tip djela', T.price 'Cijena', CAST(ROUND(T.price * 0.2, 3) AS DECIMAL(18, 3)) '20% od cijene', CAST(ROUND(T.price * 0.8, 3) AS DECIMAL (18, 3)) 'Cijena umanjena za 20%'
FROM titles AS T
WHERE T.price IS NOT NULL
ORDER BY T.type, T.price DESC;