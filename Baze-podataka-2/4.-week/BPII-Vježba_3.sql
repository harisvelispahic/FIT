--WILDCARDS

--%	Represents zero or more characters	bl% finds bl, black, blue, and blob
--_	Represents a single character	h_t finds hot, hat, and hit
--[]	Represents any single character within the brackets	h[oa]t finds hot and hat, but not hit
--^	Represents any character not in the brackets	h[^oa]t finds hit, but not hot and hat
---	Represents any single character within the specified range	c[a-b]t finds cat and cbt

--1.	Koriste�i bazu Northwind izdvojiti godinu, mjesec i dan datuma isporuke narud�be.
SELECT YEAR(O.ShippedDate) Godina, MONTH(O.ShippedDate) Mjesec, DAY(O.ShippedDate) Dan
FROM Northwind.dbo.Orders AS O

--2.	Koriste�i bazu Northwind izra�unati koliko je godina pro�lo od datum narud�be do danas.
USE Northwind
SELECT DATEDIFF(YEAR, O.OrderDate, GETDATE()) 'Broj godina'
FROM Orders AS O

--3.	Koriste�i bazu Northwind dohvatiti sve kupce kod kojih se po�tanski broj sastoji samo od cifara. 
SELECT *
FROM Customers AS C
WHERE C.PostalCode LIKE '[0-9]%' AND C.PostalCode NOT LIKE '%-%'
--ILI
SELECT *
FROM Customers AS C
WHERE C.PostalCode NOT LIKE '%[^0-9]%'
--ILI
SELECT *
FROM Customers AS C
WHERE ISNUMERIC(C.PostalCode)=1

--4.	Koriste�i bazu AdventureWorks2017 prikazati spojeno ime, srednje ime i prezime osobe. Uslov je da se izme�u pojedinih segmenata nalazi space. Omogu�iti prikaz podataka i ako neki od podataka nije unijet. Prikazati samo jedinstvene zapise (bez ponavljanja istih zapisa). 
--Prikaz zapisa 
SELECT PP.FirstName,PP.MiddleName,PP.LastName
FROM AdventureWorks2017.Person.Person AS PP

--Spajanjem vrijednosti sa NULL izlaz polja postaje NULL
SELECT PP.FirstName + ' ' + PP.MiddleName + ' ' + PP.LastName
FROM AdventureWorks2017.Person.Person AS PP

--Provjera sporne NULL kolone i zamjena sa praznim prostorom
SELECT PP.FirstName + ' ' + ISNULL(PP.MiddleName, ' ') + ' ' + PP.LastName
FROM AdventureWorks2017.Person.Person AS PP

--Kori�tenje CONCAT funkcije u svrhu spajanja stringova.
SELECT CONCAT(PP.FirstName, ' ', PP.MiddleName, ' ', PP.LastName)
FROM AdventureWorks2017.Person.Person AS PP

--Finalni rezultat 2 na�ina:
SELECT DISTINCT PP.FirstName + ' ' + ISNULL(PP.MiddleName, ' ')+ ' ' + PP.LastName
FROM AdventureWorks2017.Person.Person AS PP

SELECT DISTINCT CONCAT(PP.FirstName,' ',PP.MiddleName,' ',PP.LastName)
FROM AdventureWorks2017.Person.Person AS PP

--5.	Koriste�i bazu Pubs prikazati 10 koli�inski najve�ih stavki prodaje. Lista treba da sadr�i broj narud�be, datum narud�be i koli�inu. Provjeriti da li ima vi�e stavki sa koli�inom kao posljednja u listi, te uklju�iti ih u rezultate upita ukoliko postoje.
USE pubs
SELECT TOP 10 WITH TIES S.ord_num, S.ord_date, S.qty
FROM sales AS S
ORDER BY 3 DESC

--6.	 Prikazati podatke o narud�bama koje su napravljene prije 19.07.1996. godine. Izlaz treba da sadr�i sljede�e kolone: ID narud�be, datum narud�be, ID kupca, te grad. 
USE Northwind
SELECT O.OrderID, O.OrderDate, O.CustomerID, O.ShipCity
FROM Orders AS O
WHERE O.OrderDate < '1996-07-19'

--7.	Prikazati nazive proizvoda, njihovu cijenu te naziv i telefonski broj dobavlja�a.

-- Nama treba spajanje jednakosti (equi-join), jer bez join uvjeta dobivamo Kartezijev proizvod, koji svaki red jedne tablice spaja sa svakim redom druge tablice.
--PRIMJER KARTEZIJEVOG PROIZVODA / CROSS JOIN-a (Neispravnog spajanja)
-- 77 redova
SELECT P.ProductName, P.UnitPrice
FROM Products AS P

-- 29 rows
SELECT S.CompanyName, S.Phone
FROM Suppliers AS S

--Kartezijev proizvod
-- 77 * 29 = 2233 reda
SELECT P.ProductName, P.UnitPrice, S.CompanyName, S.Phone
FROM Products AS P, Suppliers AS S

--na isti nacin dobivamo Kartezijev proizvod ako koristili CROSS JOIN
SELECT P.ProductName, P.UnitPrice, S.CompanyName, S.Phone
FROM Products AS P CROSS JOIN Suppliers AS S


--ZA ISPRAVNU IZRADU OVOGA ZADATKA KORISTIMO INNER JOIN (spajaju se samo redovi koji ispunjavaju JOIN uvjet, tj. FOREIGN KEY kolona jednog zapisa je jednaka PRIMARY KEY-u jednog zapisa druge tablice)
--Ispravno rje�enje
SELECT P.ProductName, P.UnitPrice, S.CompanyName, S.Phone
FROM Products AS P 
	INNER JOIN Suppliers AS S ON P.SupplierID = S.SupplierID

--8.	Prikazati imena i prezimena (spojeno) radnika koji imaju nadre�enog te ime i prezime (spojeno) osobe koja im je nadre�ena. Izlaz sortirati abecednim redoslijedom po imenu i prezimenu nadre�enog.
--Ovdje imamo primjer rekurzivne veze tj. tablica Employees ima FK koji se referencira na PK iste tablice, spajanje se izvodi na isti na�in kao i kada nije rije� o rekuzivnoj vezi, osim sto u FROM dijelu sada navodimo iste tablice 2 puta pa ih alias-ima moramo razlikovati

SELECT CONCAT(EMP.FirstName, ' ', EMP.LastName) 'Radnik', CONCAT(BOSS.FirstName, ' ', BOSS.LastName) 'Nadre�eni'
FROM Employees AS EMP
	INNER JOIN Employees AS BOSS ON EMP.ReportsTo = BOSS.EmployeeID
ORDER BY 2

--9.	Prikazati radnike koji posluju na podru�jima Boston-a, Cambridge-a ili New York-a. Izlaz treba sadr�avati sljede�e kolone: Ime i prezime radnika i naziv podru�ja na kojem posluje.
SELECT E.FirstName, E.LastName, T.TerritoryDescription
FROM Employees AS E
	INNER JOIN EmployeeTerritories AS ET ON ET.EmployeeID = E.EmployeeID
	INNER JOIN Territories AS T ON ET.TerritoryID = T.TerritoryID
WHERE T.TerritoryDescription IN ('Boston', 'Cambridge', 'New York')

--BAZA Vjezbe0
--10.	Prikazati kojem rangu primanja pripadaju radnici tablice Radnik, prikazati rang i raspon vrijednosti (spojeno), tako�er prikazati ime i prezime radnika (spojeno).
--Ovdje je rije� o non-equi join-u, gdje tablice nisu spojene vec u ovom primjeru spajamo redove koji ce pripadati samo jednom rangu (pla�a pripada samo jednom rangu koji je definiran zapisima tablice Stupanj)
USE Vjezbe0
SELECT CONCAT(R.Ime, ' ', R.Prezime) 'Ime i prezime', S.Rang, CONCAT(S.Min, ' - ', S.Max) 'Raspon'
FROM Radnik AS R, Stupanj AS S
WHERE R.Placa BETWEEN S.Min AND S.Max

--PRIHODI
--11.	Prikazati imena i prezimena svih osoba i dati pregled svih njihovih vanrednih primanja. U rezultatu upita moraju biti i osobe koje nemaju vanrednih primanja.
USE prihodi
SELECT O.Ime, O.PrezIme, VP.IznosVanrednogPrihoda
FROM Osoba AS O
	LEFT OUTER JOIN VanredniPrihodi AS VP ON VP.OsobaID = O.OsobaID

--12.	Prethodni upit modificirati da prika�e samo one osobe koje nemaju vanredna primanja.
SELECT O.Ime, O.PrezIme, VP.IznosVanrednogPrihoda
FROM Osoba AS O
	LEFT OUTER JOIN VanredniPrihodi AS VP ON VP.OsobaID = O.OsobaID
WHERE VP.VanredniPrihodiID IS NULL --dovoljno je provjeriti da li je PK desne tablice null kako bi prikazali osobe koje nemaju primanja.

--13.	Koriste�i ispravno spajanje prikazati ID, imena i prezimena osoba te ID i neto iznos redovnih primanja. Prikazati i sve osobe i sva primanja. Analizirajte da li postoje primanja koja nisu dodijeljena ni jednoj osobi.
SELECT O.OsobaID, O.Ime, O.PrezIme,RP.RedovniPrihodiID, RP.Neto
FROM Osoba AS O
	FULL OUTER JOIN RedovniPrihodi AS RP ON RP.OsobaID = O.OsobaID

--iako je vidljivo u rezultatu, mozemo kao i u 11. zadatku dodati uslov koji ce provjeriti da li osoba postoji za odre�eni redovni prihod, vidmo da takvi prihodi postoje
SELECT O.OsobaID, O.Ime, O.PrezIme,RP.RedovniPrihodiID, RP.Neto
FROM Osoba AS O
	FULL OUTER JOIN RedovniPrihodi AS RP ON RP.OsobaID = O.OsobaID
WHERE O.OsobaID IS NULL

--14.	Prikazati stavke narud�be gdje je koli�ina narud�be bila ve�a od 100 komada uz odobreni popust.
USE Northwind
SELECT *
FROM [Order Details] AS OD
WHERE OD.Quantity>100 AND OD.Discount>0

--15.	Za svaku narud�bu prikazati ID i naziv dostavlja�a.
SELECT O.OrderID, S.CompanyName
FROM Orders AS O
	INNER JOIN Shippers AS S ON O.ShipVia = S.ShipperID

--16.	Koriste�i bazu Northwind prikazati sve kupce koje u koloni ContactTitle sadr�e pojam "manager".
SELECT *
FROM Customers AS C
WHERE LOWER(C.ContactTitle) LIKE '%manager%'

--17.	Prikazati listu zaposlenika sa sljede�im atributima: Id, ime, prezime, dr�ava i titula, gdje je Id 9 ili dolaze iz Amerike. 
SELECT E.EmployeeID, E.FirstName, E.LastName, E.Country, E.Title
FROM Northwind.dbo.Employees AS E
WHERE E.EmployeeID=9 OR UPPER(E.Country) LIKE 'USA'

--18.	 Prikazati ime kompanije kupca i kontakt telefon i to samo onih koji u svome imenu posjeduju rije� �Restaurant�. Ukoliko naziv kompanije sadr�i karakter (-), kupce izbaciti iz rezultata upita. 
SELECT C.CompanyName, C.Phone
FROM Customers AS C
WHERE LOWER(C.CompanyName) LIKE '%restaurant%' AND C.CompanyName NOT LIKE '%-%'

--19.	 Prikazati proizvode �iji naziv po�inje slovima �C� ili �G�, drugo slovo mo�e biti bilo koje, a tre�e slovo u nazivu je �A� ili �O�. 
SELECT *
FROM Products AS P
WHERE UPPER(P.ProductName) LIKE '[CG]_[AO]%'

--20.	Prikazati listu proizvoda �iji naziv po�inje slovima �L� ili �T�, ili je ID proizvoda = 46. Lista treba da sadr�i samo one proizvode �ija se cijena po komadu kre�e izme�u 10 i 50 (uklju�uju�i grani�ne vrijednosti). Upit napisati na dva na�ina. 
SELECT *
FROM Products AS P
WHERE (UPPER(P.ProductName) LIKE '[LT]%' OR P.ProductID=46) 
AND P.UnitPrice BETWEEN 10 AND 50
--ILI
SELECT *
FROM Products AS P
WHERE (UPPER(P.ProductName) LIKE '[LT]%' OR P.ProductID=46)
AND P.UnitPrice >= 10 AND P.UnitPrice <= 50

--21.	 Prikazati naziv proizvoda i cijenu, gdje je stanje na zalihama manje od naru�ene koli�ine. Tako�er, u rezultate upita uklju�iti razliku izme�u stanja zaliha i naru�ene koli�ine.   
SELECT P.ProductName, P.UnitPrice, P.UnitsInStock - P.UnitsOnOrder Razlika
FROM Products AS P
WHERE P.UnitsInStock < P.UnitsOnOrder

--22.	Prikazati sve podatke o dobavlja�ima koji dolaze iz �panije ili Njema�ke a nemaju unesen broj faxa. Formatirati izlaz NULL vrijednosti na na�in da se prika�e umjesto NULL prikladno obja�njenje. Upit napisati na dva na�ina. 
SELECT S.SupplierID, S.CompanyName, S.ContactName, S.ContactTitle, S.Address, S.City, S.Region, S.PostalCode, S.Country, S.Phone, ISNULL(S.Fax,'nepoznata vrijednost') AS Fax, S.HomePage
FROM Suppliers AS S
WHERE UPPER(S.Country) IN ('SPAIN','GERMANY') AND S.Fax IS NULL
--ILI
SELECT S.SupplierID, S.CompanyName, S.ContactName, S.ContactTitle, S.Address, S.City, S.Region, S.PostalCode, S.Country, S.Phone, ISNULL(S.Fax,'nepoznata vrijednost') AS Fax, S.HomePage
FROM Suppliers AS S
WHERE (UPPER(S.Country) LIKE'SPAIN'OR UPPER(S.Country) LIKE'GERMANY') AND S.Fax IS NULL

--Pubs
--23.	Prikazati naslove knjiga te imena i prezimena njihovih autora (spojeno).
USE pubs
SELECT T.title, CONCAT(A.au_fname, ' ', A.au_fname) 'Autor'
FROM titles AS T
	INNER JOIN titleauthor AS TA ON TA.title_id = T.title_id
	INNER JOIN authors AS A ON TA.au_id = A.au_id

--24.	Prikazati listu autora sa sljede�im kolonama: ID, ime i prezime (spojeno), grad i to samo one autore �iji ID po�inje brojem 8 ili dolaze iz grada �Salt Lake City�. Tako�er autorima status ugovora treba biti 1. Koristiti aliase nad kolonama.
USE pubs
SELECT A.au_id, A.au_fname + ' ' + A.au_lname 'Ime prezime', A.city, A.contract
FROM authors AS A
WHERE (A.au_id LIKE '8%' OR UPPER(A.city) LIKE 'SALT LAKE CITY') AND A.contract=1

--25.	Prikazati sve tipove knjiga bez duplikata. Listu sortirati u abecednom redoslijedu.   
SELECT DISTINCT T.type
FROM titles AS T
ORDER BY T.type

--26.	Prikazati listu prodaje knjiga sa sljede�im kolonama: ID prodavnice, broj narud�be i koli�inu, ali samo gdje je koli�ina izme�u 10 i 50, uklju�uju�i i grani�ne vrijednosti. Rezultat upita sortirati po koli�ini opadaju�im redoslijedom. Upit napisati na dva na�ina.
SELECT S.stor_id, S.ord_num, S.qty Kolicina
FROM sales AS S
WHERE S.qty BETWEEN 10 AND 50
ORDER BY 3 DESC
--ILI
SELECT S.stor_id, S.ord_num, S.qty Kolicina
FROM sales AS S
WHERE S.qty >= 10 AND S.qty <= 50
ORDER BY 3 DESC

--27.	Prikazati listu knjiga sa sljede�im kolonama: naslov, tip djela i cijena. Kao novu kolonu dodati 20% od prikazane cijene (npr. Ako je cijena 19.99 u novoj koloni treba da pi�e 3,998). Naziv kolone se treba zvati �20% od cijene�. Listu sortirati abecedno po tipu djela i po cijeni opadaju�im redoslijedom. Sa liste eliminisati one knjige koje nemeju pohranjenu vrijednost cijene. Modifikovati upit tako da uz ve� prikazane kolone se prika�e i cijena umanjena za 20 %. Naziv kolone treba da se zove �Cijena umanjena za 20%�.   
SELECT T.title, T.type, T.price, T.price*0.2 '20% od cijene', T.price*(1-0.2) 'Cijena umanjena za 20%'
FROM titles AS T
WHERE T.price IS NOT NULL
ORDER BY 2,3 DESC