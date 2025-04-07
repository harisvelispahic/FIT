USE Northwind;

-- PRIMJERI AGREGATNIH FUNKCIJA

SELECT COUNT(*)
FROM Products AS P;

SELECT P.Discontinued, COUNT(*)
FROM Products AS P
GROUP BY P.Discontinued;
-- grupiramo po polju discontinued

SELECT C.CategoryName, AVG(P.UnitPrice) AS Prosjecna_cijena
FROM Products AS P INNER JOIN Categories AS C ON P.CategoryID = C.CategoryID
WHERE P.Discontinued = 0
GROUP BY C.CategoryName
HAVING AVG(P.UnitPrice) > 30;
-- prosjecna cijena proizvoda po kategorijama

-- WHERE -> FILTRIRANJE ZAPISA
-- HAVING -> FILTRIRANJE GRUPA




-- 1. Prikazati ukupnu vrijednost troška prevoza po državama ali samo ukoliko je veća od 4000 za robu koja se kupila u Francuskoj, Njemačkoj ili Švicarskoj. (Northwind)

SELECT O.ShipCountry, SUM(O.Freight) 'Trosak prevoza'
FROM Orders AS O
WHERE O.ShipCountry IN ('France', 'Germany', 'Switzerland')
GROUP BY O.ShipCountry
HAVING SUM(O.Freight) > 4000;

-- 2. Prikazati 10 najprodavanijih proizvoda. Za proizvod prikazati njegov identifikacijski broj i naziv. Najprodavaniji proizvod je onaj koji je u najvećim količinama prodat. (Northwind)

SELECT TOP 10 P.ProductID, P.ProductName, SUM(OD.Quantity) 'Prodata kolicina'
FROM [Order Details] AS OD
	INNER JOIN Products AS P ON OD.ProductID = P.ProductID
GROUP BY P.ProductID, P.ProductName
ORDER BY SUM(OD.Quantity) DESC;

-- 3. Kreirati upit koji prikazuje zaradu od prodaje proizvoda. Lista treba da sadrži identifikacijski broj, naziv, potkategoriju i kategoriju proizvoda, ukupnu zaradu bez popusta, ukupnu zaradu sa popustom. Vrijednost zarade zaokružiti na dvije decimale. Uslov je da se prikaže zarada samo za stavke gdje je bilo popusta. Listu sortirati prema ukupnoj zaradi sa popustom u opadajućem redoslijedu. (AdventureWorks2017)

USE AdventureWorks2017;

SELECT P.ProductID, P.Name, PS.Name 'Podkategorija', PC.Name 'Kategorija', ROUND(SUM(SOD.UnitPrice * SOD.OrderQty), 2) 'Bez popusta', ROUND(SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)), 2) 'Sa popustom'
FROM Sales.SalesOrderDetail AS SOD
	INNER JOIN Sales.SpecialOfferProduct AS SOP ON SOD.ProductID = SOP.ProductID AND SOD.SpecialOfferID = SOP.SpecialOfferID
	INNER JOIN Production.Product AS P ON SOP.ProductID = P.ProductID
	INNER JOIN Production.ProductSubcategory AS PS ON P.ProductSubcategoryID = PS.ProductSubcategoryID
	INNER JOIN Production.ProductCategory AS PC ON PS.ProductCategoryID = PC.ProductCategoryID
WHERE SOD.UnitPriceDiscount > 0
GROUP BY P.ProductID, P.Name, PS.Name, PC.Name
ORDER BY ROUND(SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)), 2) DESC; 

-- 4. Prikazati tip popusta, naziv prodavnice i njen id. (Pubs) 

USE pubs;

SELECT S.stor_id, S.stor_name, D.discounttype
FROM stores AS S
	INNER JOIN discounts AS D ON S.stor_id = D.stor_id;

-- 5. Prikazati spojeno ime i prezime uposlenika, regiju, broj teritorija koje pokriva i nazive svih tih teritorija (koristeći string_agg funkciju). Uslov je da su zaposlenici mlađi od 65 godina. (Northwind) 

USE Northwind;

SELECT CONCAT(E.FirstName, ' ', E.LastName) 'Ime i prezime', R.RegionDescription, COUNT(*) 'Broj teritorija', STRING_AGG(TRIM(T.TerritoryDescription), ', ')
FROM Region AS R
	INNER JOIN Territories AS T ON T.RegionID = R.RegionID
	INNER JOIN EmployeeTerritories AS ET ON T.TerritoryID = ET.TerritoryID
	INNER JOIN Employees AS E ON ET.EmployeeID = E.EmployeeID
WHERE DATEDIFF(YEAR, E.BirthDate, GETDATE()) < 65
GROUP BY CONCAT(E.FirstName, ' ', E.LastName), R.RegionDescription;

-- STRING_AGG(niz_stringova, delimiter) ---> agregira stringove, tj. concatenatuje ih, u odnosu na neku grupu
-- na primjer ovdje smo grupirali po imenima i prezimenima, te regijama i trebaju nam imena svih teritorija iz neke regije u kojima je neki uposlenik radio


-- 6. Prikazati ukupnu vrijednost obrađenih narudžbi sa popustom za svakog uposlenika pojedinačno. Uslov je da su narudžbe kreirane u 1996. godini, te u obzir uzeti samo one uposlenike čija je ukupna ukupna obrađena vrijednost veća od 20000. Podatke sortirati prema ukupnoj vrijednosti (zaokruženoj na dvije decimale) u rastućem redoslijedu. (Northwind)  

SELECT E.EmployeeID, E.FirstName, E.LastName, ROUND(SUM(OD.UnitPrice * OD.Quantity * (1 - OD.Discount)), 2)
FROM Employees AS E
	INNER JOIN Orders AS O ON E.EmployeeID = O.EmployeeID
	INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
WHERE YEAR(O.OrderDate) = 1996
GROUP BY E.EmployeeID, E.FirstName, E.LastName
HAVING ROUND(SUM(OD.UnitPrice * OD.Quantity * (1 - OD.Discount)), 2) > 20000
ORDER BY 2 ASC;

-- 7. Prikazati naziv dobavljača, adresu i državu dobavljača, te nazive proizvoda koji pripadaju kategoriji pića a ima ih na stanju više od 30 komada. Rezultate upita sortirati po državama u abedecnom redoslijedu. (Northwind)  

SELECT S.CompanyName, S.Address, S.Country, STRING_AGG(P.ProductName, ', ')
FROM Suppliers AS S
	INNER JOIN Products AS P ON S.SupplierID = P.SupplierID
	INNER JOIN Categories AS C ON P.CategoryID = C.CategoryID
WHERE C.CategoryName = 'Beverages' AND P.UnitsInStock > 30
GROUP BY S.CompanyName, S.Address, S.Country
ORDER BY S.Country ASC;

-- 8. Prikazati kontakt ime kupca, njegov id, id narudžbe, datum kreiranja narudžbe (prikazan u formatu dan.mjesec.godina, npr. 24.07.2021) te ukupnu vrijednost narudžbe sa i bez popusta. Prikazati samo one narudžbe koje su kreirane u 1997. godini. Izračunate vrijednosti zaokružiti na dvije decimale, te podatke sortirati prema ukupnoj vrijednosti narudžbe sa popustom u opadajućem redoslijedu. (Northwind) 

SELECT C.ContactName, C.CustomerID, O.OrderID, FORMAT(O.OrderDate, 'dd.MM.yyyy'), ROUND(SUM(OD.UnitPrice * OD.Quantity), 2) 'Bez popusta', ROUND(SUM(OD.UnitPrice * OD.Quantity * (1 - OD.Discount)), 2) 'Sa popustom' 
FROM Customers AS C
	INNER JOIN Orders AS O ON C.CustomerID = O.CustomerID
	INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
WHERE YEAR(O.OrderDate) = 1997
GROUP BY C.ContactName, C.CustomerID, O.OrderID, FORMAT(O.OrderDate, 'dd.MM.yyyy')
ORDER BY ROUND(SUM(OD.UnitPrice * OD.Quantity * (1 - OD.Discount)), 2) DESC;

-- 9. Prikazati 10 najskupljih stavki narudžbi. Upit treba da sadrži id stavke, naziv proizvoda, količinu, cijenu i vrijednost stavke narudžbe. Cijenu i vrijednost stavke narudžbe zaokružiti na dvije decimale. Izlaz formatirati na način da uz količinu stoji “kom” (npr. 50 kom) a uz cijenu i vrijednost stavke narudžbe “KM” (npr. 50 KM). (AdventureWorks2017) 

USE AdventureWorks2017;

SELECT TOP 10 SOD.SalesOrderDetailID, P.Name, CONCAT(SOD.OrderQty, ' kom') 'Kolicina', CONCAT(ROUND(SOD.UnitPrice, 2), ' KM') 'Cijena', CONCAT(CAST(ROUND(SOD.LineTotal, 2) AS DECIMAL(18,2)), ' KM') 'Vrijednost'
FROM Production.Product AS P
	INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
ORDER BY ROUND(SOD.LineTotal, 2) DESC;

-- 10. Kreirati upit koji prikazuje ukupan broj narudžbi po teritoriji na kojoj je kreirana narudžba. Lista treba da sadrži sljedeće kolone: naziv teritorije, ukupan broj narudžbi. Uzeti u obzir samo teritorije na kojima je kreirano više od 1000 narudžbi. (AdventureWorks2017)  

USE AdventureWorks2017;

SELECT ST.Name, COUNT(*) 'broj_narudzbi'
FROM Sales.SalesOrderHeader AS SOH
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID = ST.TerritoryID
GROUP BY ST.Name
HAVING COUNT(*) > 1000;

-- 11. Kreirati upit koji prikazuje zaradu od prodaje proizvoda. Lista treba da sadrži naziv proizvoda, ukupnu zaradu bez uračunatog popusta i ukupnu zaradu sa uračunatim popustom. Iznos zarade zaokružiti na dvije decimale. Uslov je da se prikaže zarada samo za stavke gdje je bilo popusta. Listu sortirati po zaradi sa popustom opadajućim redoslijedom. (AdventureWorks2017)

SELECT P.Name, ROUND(SUM(SOD.UnitPrice * SOD.OrderQty), 2) 'Zarada bez popusta', ROUND(SUM(SOD.UnitPrice * SOD.OrderQty * (1 - SOD.UnitPriceDiscount)), 2) 'Zarada sa popustom'
FROM Production.Product AS P
	INNER JOIN Sales.SalesOrderDetail AS SOD ON P.ProductID = SOD.ProductID
WHERE SOD.UnitPriceDiscount > 0
GROUP BY P.Name
ORDER BY 3 DESC;

-- 12. Prikazati prosječnu ocjenu proizvoda koji su imaju više od 1 recenzije. Izlaz treba sadržavati broj, ime i cijenu proizvoda te prosječnu ocjenu svih njegovih recenzija. (AdventureWorks2017).

SELECT P.ProductID, P.Name, P.ListPrice, AVG(PR.Rating) 'Prosjecna ocjena'
FROM Production.Product AS P
	INNER JOIN Production.ProductReview AS PR ON P.ProductID = PR.ProductID
GROUP BY P.ProductID, P.Name, P.ListPrice
HAVING COUNT(*) > 1;

-- 13. Prikazati 5 dobavljača koji imaju navjeću ukupnu prodanu količinu proizvoda kategorije plodova mora, osim imena dobavljača i ukupne prodane količine, prikazati i ukupan prihod (sa popustom) ostvaren prodajom zaokružen na 2 decimale. (Northwind).

USE Northwind;

SELECT TOP 5 S.CompanyName, SUM(OD.Quantity) 'Ukupna kolicina proizvoda', ROUND(SUM(OD.UnitPrice * OD.Quantity * (1 - OD.Discount)), 2) 'Ukupan prihod'
FROM Suppliers AS S
	INNER JOIN Products AS P ON S.SupplierID = P.SupplierID
	INNER JOIN Categories AS C ON P.CategoryID = C.CategoryID
	INNER JOIN [Order Details] AS OD ON P.ProductID = OD.ProductID
WHERE C.CategoryName = 'Seafood'
GROUP BY S.CompanyName
ORDER BY 2 DESC;

-- 14. Prikazati količinu obavljenih narudžbi za svakog kupca, uzeti u obzir samo one narudžbe koje su obradili uposlenici iz Londona i kupce koji su obavili 5 ili više narudžbi. Prikazati ime kupca, broj narudžbi i dodati novu kolonu 'Popust za vozarinu' koja određuje popust koji će kupac dobiti za plaćanje vozarine sljedeće svoje narudžbe. Kolonu popuniti na sljedeći način: ako je kupac na vozarinu za sve svoje narudžbe potrošio više od 500KM dobiva popust od -20%, za više od 1000KM dobiva popust od -45%, a -100% dobivaju oni koji su potrošili više od 2000KM, kupci koji nisu zadovoljili niti jedan uvjet ne dobivaju nikakav popust --. Izlaz sortirati po broju narudžbi silazno. (Northwind).

USE Northwind;

SELECT C.ContactName, COUNT(*) 'Broj_narudzbi', SUM(O.Freight) 'Potroseno na vozarinu',
	CASE
		WHEN SUM(O.Freight) > 2000 THEN '-100%'
		WHEN SUM(O.Freight) > 1000 THEN '-45%'
		WHEN SUM(O.Freight) > 500 THEN '-20%'
		ELSE '--'
	END 'Popust za vozarinu'
FROM Customers AS C
	INNER JOIN Orders AS O ON C.CustomerID = O.CustomerID
	INNER JOIN Employees AS E ON O.EmployeeID = E.EmployeeID
WHERE E.City = 'London'
GROUP BY C.ContactName
HAVING COUNT(*) > 5
ORDER BY 2 DESC;

-- 15. Prikazati ID kategorije, naziv kategorije i ukupnu količinu proizvoda na stanju po kategorijama, ali samo za kategorije čija je ukupna količina na stanju veća od 500. Rezultate sortirati po ukupnoj količini u opadajućem redoslijedu. (Northwind).

SELECT C.CategoryID, C.CategoryName, SUM(P.UnitsInStock) 'Ukupna kolicina proizvoda'
FROM Categories AS C
	INNER JOIN Products AS P ON C.CategoryID = P.CategoryID
GROUP BY C.CategoryID, C.CategoryName
HAVING SUM(P.UnitsInStock) > 500
ORDER BY 3 DESC;

-- 16. Prikazati ID i naziv kompanije kupca, broj narudžbi koje je napravio i ukupnu potrošnju (sa popustom) za kupce koji su potrošili više od 30,000 KM. Rezultate sortirati po ukupnoj potrošnji u opadajućem redoslijedu. (Northwind).

USE Northwind;

SELECT C.CustomerID, C.CompanyName, COUNT(DISTINCT O.OrderID) 'Broj narudzbi', ROUND(SUM(OD.UnitPrice * OD.Quantity * (1 - OD.Discount)), 2) 'Ukupna potrosnja'
FROM Customers AS C
	INNER JOIN Orders AS O ON C.CustomerID = O.CustomerID
	INNER JOIN [Order Details] AS OD ON O.OrderID = OD.OrderID
GROUP BY C.CustomerID, C.CompanyName
HAVING ROUND(SUM(OD.UnitPrice * OD.Quantity * (1 - OD.Discount)), 2) > 30000
ORDER BY 4 DESC;

-- ne moze ovako (COUNT(*)), jer brojimo stavke narudzbe, a ne kao sto zadatak kaze broj narudzbi, jer je veza izmedju [Orders] i [Order details] 1:N
-- obicno ide preko podupita
-- moramo koristiti COUNT(DISTINCT O.OrderID) da prebrojimo samo unikatne brojeve narudzbe, koje mogu sadrzavati vise stavki narudzbe, medjutim nas zanima broj narudzbi



-- 17. Prikazati naziv dobavljača, broj različitih proizvoda koje isporučuje i prosječnu cijenu njihovih proizvoda (zaokruženu na dvije decimale). Uslov je da dobavljač isporučuje više od 3 proizvoda. (Northwind).

SELECT S.CompanyName, COUNT(DISTINCT P.ProductName) 'Broj proizvoda', ROUND(AVG(P.UnitPrice), 2) 'Prosjecna cijena proizvoda'
FROM Suppliers AS S
	INNER JOIN Products AS P ON S.SupplierID = P.SupplierID
GROUP BY S.CompanyName
HAVING COUNT(DISTINCT P.ProductName) > 3;

-- 18. Prikazati naziv i ID prodavnice, broj naslova i nazive naslova koje prodaje. Prikazati samo prodavnice koje prodaju više od 3 naslova. (Pubs).

USE pubs;

SELECT ST.stor_id, ST.stor_name, COUNT(*) 'Broj naslova', STRING_AGG(T.title, ', ') 'Naslovi'
FROM stores AS ST
	INNER JOIN sales AS SA ON ST.stor_id = SA.stor_id
	INNER JOIN titles AS T ON SA.title_id = T.title_id
GROUP BY ST.stor_id, ST.stor_name
HAVING COUNT(*) > 3;

-- 19. Prikazati naziv teritorije, broj zaposlenika koji rade na njoj, ukupnu prodajnu kvotu te godine i ukupnu prodaju od početka godine do danas, ali samo za teritorije gdje je ukupna prodaja od početka godine do danas 10 puta ispunila svoju ukupnu prodajnu kvotu. (AdventureWorks2017).

USE AdventureWorks2017;

SELECT ST.Name, COUNT(*) 'Broj zaposlenika', SUM(SP.SalesQuota) 'Prodajna kvota', SUM(SP.SalesYTD) 'Prodaja od pocetka godina'
FROM Sales.SalesTerritory AS ST
	INNER JOIN Sales.SalesPerson AS SP ON ST.TerritoryID = SP.TerritoryID
WHERE SP.SalesQuota IS NOT NULL
GROUP BY ST.Name
HAVING SUM(SP.SalesYTD) >= SUM(SP.SalesQuota) * 10;



--SELECT * FROM Sales.SalesTerritory;
--SELECT * FROM Sales.SalesPerson;