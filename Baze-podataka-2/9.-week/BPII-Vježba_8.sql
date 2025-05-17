--1.	Prikazati nazive svih gradova u kojima su ukupna zabilježena neto primanja veća od 25% ukupnih neto primanja koje je zabilježila Kina. Također prikazati postotak primanja tih gradova u odnosu na Kinu, te izlaz sortirati po postotku u opadajućem redoslijedu. (Prihodi)
USE prihodi
SELECT G.Grad, 
CONCAT(CAST((SUM(RP.Neto) / (
				SELECT SUM(RP.Neto) 'Ukupna prodaja'
				FROM Drzava AS D
					INNER JOIN Osoba AS O ON O.DrzavaID = D.DrzavaID
					INNER JOIN RedovniPrihodi AS RP ON RP.OsobaID = O.OsobaID
					WHERE D.Drzava = 'China') * 100) AS DECIMAL(18,2)), '%')'% primanja u odnosu na Kinu'
FROM Grad AS G
	INNER JOIN Osoba AS O ON O.GradID = G.GradID
	INNER JOIN RedovniPrihodi AS RP ON RP.OsobaID = O.OsobaID
GROUP BY G.Grad
HAVING SUM(RP.Neto) / (SELECT SUM(RP.Neto) 'Ukupna prodaja'
						FROM Drzava AS D
							INNER JOIN Osoba AS O2 ON O2.DrzavaID = D.DrzavaID
							INNER JOIN RedovniPrihodi AS RP ON RP.OsobaID = O2.OsobaID
							WHERE D.Drzava = 'China') 
		> 0.25
ORDER BY [% primanja u odnosu na Kinu] DESC

--2.	Prikazati osobe čiji su neto redovni prihodi manji od prosjeka svih neto redovnih primanja i čiji su vanredni prihodi veći od prosjeka svih vandrednih primanja. (Prihodi)

select 
    o.OsobaID, 
    concat(o.Ime, ' ', o.PrezIme) as 'Ime i prezime',
    cast(avg(rp.Neto) as decimal(18, 2)) as 'Prosjek neto',
    cast(avg(vp.IznosVanrednogPrihoda) as decimal(18, 2)) as 'Prosjek VP'
from Osoba as o
    inner join RedovniPrihodi as rp on o.OsobaID = rp.OsobaID
    inner join VanredniPrihodi as vp on o.OsobaID = vp.OsobaID
group by o.OsobaID, concat(o.Ime, ' ', o.PrezIme)
having 
    avg(rp.Neto) < (
        select avg(rp.Neto)
        from RedovniPrihodi as rp
    ) and 
    avg(vp.IznosVanrednogPrihoda) > (
        select avg(vp.IznosVanrednogPrihoda)
        from VanredniPrihodi as vp
    )
--3.	Za svaku pojedinačnu godinu u kojima su kreirane narudžbe (izvući godinu iz datuma narudžbe) prikazati ime i prezime (spojeno) prodavača koji je ostvario najveći prihod u toj godini (sa popustom i taksama), naziv proizvoda koji je ostvario najeću prodaju (ukupna prodata količina) i ime i prezime (spojeno) kupca koji je najviše potrošio (sa popustom i taksama) u toj godini. Izlaz sortirati ulazno po godinama. (AdvantureWorks2017)
USE AdventureWorks2017

SELECT DISTINCT YEAR(SOHY.OrderDate) 'Godina',
(
SELECT SQ.[Ime i prezime] FROM (
	SELECT TOP 1 CONCAT(P.FirstName, ' ', P.LastName) 'Ime i prezime', SUM(SOH.TotalDue) 'Ukupni prihodi'
	FROM Sales.SalesOrderHeader AS SOH
		INNER JOIN Person.Person AS P ON SOH.SalesPersonID = P.BusinessEntityID
	WHERE YEAR(SOH.OrderDate) = YEAR(SOHY.OrderDate) --Za svaku godinu vanjskog upita filtriramo i računamo prihod prodavača u toj godini
	GROUP BY CONCAT(P.FirstName, ' ', P.LastName) 
	ORDER BY 2 DESC ) AS SQ
) 'Prodavač sa najvećim prihodom',
(
SELECT SQ.Name FROM (
	SELECT TOP 1 P.Name, SUM(SOD.OrderQty) 'Ukupna prodata količina'
	FROM Sales.SalesOrderHeader AS SOH
		INNER JOIN Sales.SalesOrderDetail AS SOD ON SOD.SalesOrderID = SOH.SalesOrderID
		INNER JOIN Production.Product AS P ON SOD.ProductID = P.ProductID
	WHERE YEAR(SOH.OrderDate) = YEAR(SOHY.OrderDate) --Za svaku godinu vanjskog upita filtriramo i računamo prodaju proizvoda u toj godini
	GROUP BY P.Name
	ORDER BY 2 DESC ) AS SQ
) 'Najviše prodavani proizvod',
(
SELECT SQ.[Ime i prezime] FROM (
	SELECT TOP 1 CONCAT(P.FirstName, ' ', P.LastName) 'Ime i prezime', SUM(SOH.TotalDue) 'Ukupno potrošeno'
	FROM Sales.SalesOrderHeader AS SOH
		INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
		INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
	WHERE YEAR(SOH.OrderDate) = YEAR(SOHY.OrderDate) --Za svaku godinu vanjskog upita filtriramo i računamo ukupni trošak kupca u toj godini
	GROUP BY CONCAT(P.FirstName, ' ', P.LastName)
	ORDER BY 2 DESC ) AS SQ
) 'Kupac koji je najviše potrošio'
FROM Sales.SalesOrderHeader AS SOHY
ORDER BY 1

--ILI za brže izvršavanje nekorelacijski podupiti spojeni sa vanjskim podupitom u FROM izrazu

SELECT DISTINCT YEAR(SOH.OrderDate) 'Godina', 
				Prodavac.[Ime prezime] 'Prodavač sa najvećim prihodom', 
				Proizvod.Name 'Najviše prodavni proizvod',
				Kupac.[Ime prezime] 'Kupac koji je najviše potrošio'
FROM Sales.SalesOrderHeader AS SOH
	LEFT JOIN (SELECT SQ2.Godina, SQ3.[Ime prezime]
				FROM (
					SELECT SQ.Godina, MAX(SQ.Prihod) 'Max'
					FROM(SELECT YEAR(SOH.OrderDate) 'Godina', CONCAT(P.FirstName, ' ', P.LastName) 'Ime prezime', SUM(SOH.TotalDue) 'Prihod'
										FROM Sales.SalesOrderHeader AS SOH
											INNER JOIN Sales.SalesPerson AS SP ON SOH.SalesPersonID = SP.BusinessEntityID
											INNER JOIN Person.Person AS P ON SP.BusinessEntityID = P.BusinessEntityID
										GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)) AS SQ
					GROUP BY SQ.Godina ) SQ2
				INNER JOIN (SELECT YEAR(SOH.OrderDate) 'Godina', CONCAT(P.FirstName, ' ', P.LastName) 'Ime prezime', SUM(SOH.TotalDue) 'Prihod'
							FROM Sales.SalesOrderHeader AS SOH
								INNER JOIN Sales.SalesPerson AS SP ON SOH.SalesPersonID = SP.BusinessEntityID
								INNER JOIN Person.Person AS P ON SP.BusinessEntityID = P.BusinessEntityID
							GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)) AS SQ3
				ON SQ2.Max = SQ3.Prihod
	) AS Prodavac ON Prodavac.Godina = YEAR(SOH.OrderDate)
	LEFT JOIN (SELECT SQ2.Godina, SQ3.Name
				FROM (
					SELECT SQ.Godina, MAX(SQ.Prodano) 'Max'
					FROM (SELECT YEAR(SOH.OrderDate) 'Godina', P.Name, SUM(SOD.OrderQty) 'Prodano'
							FROM Sales.SalesOrderDetail AS SOD 
								INNER JOIN Production.Product AS P ON SOD.ProductID = P.ProductID
								INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
							GROUP BY YEAR(SOH.OrderDate), P.Name) AS SQ
					GROUP BY SQ.Godina) AS SQ2
					INNER JOIN (SELECT YEAR(SOH.OrderDate) 'Godina', P.Name, SUM(SOD.OrderQty) 'Prodano'
							FROM Sales.SalesOrderDetail AS SOD 
								INNER JOIN Production.Product AS P ON SOD.ProductID = P.ProductID
								INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID = SOH.SalesOrderID
							GROUP BY YEAR(SOH.OrderDate), P.Name) AS SQ3 ON SQ2.Max = SQ3.Prodano
	) AS Proizvod ON Proizvod.Godina = YEAR(SOH.OrderDate)
	LEFT JOIN (SELECT SQ2.Godina, SQ3.[Ime prezime]
			FROM (
				SELECT SQ.Godina, MAX(SQ.Prihod) 'Max'
				FROM(SELECT YEAR(SOH.OrderDate) 'Godina', CONCAT(P.FirstName, ' ', P.LastName) 'Ime prezime', SUM(SOH.TotalDue) 'Prihod'
									FROM Sales.SalesOrderHeader AS SOH
										INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
										INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
									GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)) AS SQ
				GROUP BY SQ.Godina ) SQ2
				INNER JOIN (SELECT YEAR(SOH.OrderDate) 'Godina', CONCAT(P.FirstName, ' ', P.LastName) 'Ime prezime', SUM(SOH.TotalDue) 'Prihod'
									FROM Sales.SalesOrderHeader AS SOH
										INNER JOIN Sales.Customer AS C ON SOH.CustomerID = C.CustomerID
										INNER JOIN Person.Person AS P ON C.PersonID = P.BusinessEntityID
									GROUP BY YEAR(SOH.OrderDate), CONCAT(P.FirstName, ' ', P.LastName)) AS SQ3 ON SQ2.Max = SQ3.Prihod
	) AS Kupac ON Kupac.Godina = YEAR(SOH.OrderDate)
ORDER BY 1

--4.	 Prikazati ime i prezime, broj godina staža, opis posla uposlenika te broj knjiga uposlenika koji su učestvovali u objavljivanju više od broja objavljenih naslova izdavača sa id 0736 a koji imaju više od 31 godine staža. Rezultate upita sortirati prema godinama staža rastućim i prema broju naslova u opadajućem redoslijedu. (Pubs) 
USE pubs

SELECT CONCAT(E.fname, ' ', E.lname) 'Ime i prezime', DATEDIFF(YEAR, E.hire_date, GETDATE()) 'Staž', J.job_desc 'Opis posla', COUNT(*) 'Broj naslova'
FROM employee AS E
	INNER JOIN jobs AS J ON E.job_id=J.job_id
	INNER JOIN publishers AS P ON E.pub_id=P.pub_id
	INNER JOIN titles AS T ON P.pub_id=T.pub_id
WHERE DATEDIFF(YEAR, E.hire_date, GETDATE())>31 
GROUP BY CONCAT(E.fname, ' ', E.lname), DATEDIFF(YEAR, E.hire_date, GETDATE()), J.job_desc
HAVING COUNT(*)>
				(SELECT COUNT(*)
				 FROM titles AS T
				 WHERE T.pub_id=0736)
ORDER BY 2, 4 DESC
GO

--5. Napisati upit kojim će se prikazati ime i prezime uposlenika koji rade na poziciji dizajnera, a koji su učestvovali u objavljivanju knjiga čija je prosječna prodata količina veća od prosječne prodane količine izdavačke kuće sa id 0877. U rezultatima upita prikazati i prosječnu prodanu količinu. (Pubs) 
USE pubs 

SELECT CONCAT(E.fname, ' ', E.lname) 'Ime i prezime ', AVG(S.qty) 'Prosjecna prodana vrijednost'
FROM employee AS E
	INNER JOIN jobs AS J ON E.job_id=J.job_id
	INNER JOIN publishers AS P ON E.pub_id=P.pub_id
	INNER JOIN titles AS T ON P.pub_id=T.pub_id
	INNER JOIN sales AS S ON T.title_id=S.title_id
WHERE J.job_desc LIKE '%Designer%' 
GROUP BY CONCAT(E.fname, ' ', E.lname)
HAVING AVG(S.qty)>
				  (SELECT AVG(S.qty)
				   FROM sales AS S
				   INNER JOIN titles AS T
				   ON T.title_id=S.title_id
				   WHERE T.pub_id =0877)

--6. Kreirati upit koji prikazuje sumaran iznos svih transakcija (šema Production) po godinama (uzeti u obzir i transakcije iz arhivske tabele). U rezultatu upita prikazati samo dvije kolone: kalendarska godina i ukupan iznos transakcija u godini. Iznos transakcije predstavlja umnožak količine i stvarne cijene.(AdventureWorks2017) 
USE AdventureWorks2017
SELECT T1.Godina,ROUND(SUM(T1.Ukupno),2) 'Ukupan iznos transakcija'
FROM (SELECT YEAR(TH.TransactionDate) Godina, SUM(TH.Quantity*TH.ActualCost) Ukupno
	  FROM Production.TransactionHistory AS TH
	  GROUP BY YEAR(TH.TransactionDate)
	  UNION ALL
	  SELECT YEAR(TH.TransactionDate) Godina, SUM(TH.Quantity*TH.ActualCost) Ukupno
	  FROM Production.TransactionHistoryArchive AS TH
	  GROUP BY YEAR(TH.TransactionDate)) AS T1
GROUP BY T1.Godina
ORDER BY 1 

--7. Kreirati upit koji prikazuje četvrtu najveću satnicu uposlenika u preduzeću. U rezultatima upita prikazati pored vrijednosti satnice i ime i prezime zaposlenika. (AdventureWorks2017) 
USE AdventureWorks2017
SELECT TOP 1 *
FROM(SELECT TOP 4 PP.FirstName, PP.LastName, EPH.Rate
	 FROM HumanResources.EmployeePayHistory AS EPH
	 INNER JOIN HumanResources.Employee AS E ON EPH.BusinessEntityID=E.BusinessEntityID
	 INNER JOIN Person.Person AS PP ON EPH.BusinessEntityID=PP.BusinessEntityID
	 ORDER BY 3 DESC) AS PODQ
ORDER BY 3

--DRUGI NAÈIN
SELECT PODQ.FirstName, PODQ.LastName, PODQ.Rate
FROM(SELECT PP.FirstName, PP.LastName, EPH.Rate, 
	 ROW_NUMBER() OVER(ORDER BY EPH.Rate DESC) AS Redoslijed
	 FROM HumanResources.EmployeePayHistory AS EPH
	 INNER JOIN HumanResources.Employee AS E ON EPH.BusinessEntityID=E.BusinessEntityID
	 INNER JOIN Person.Person AS PP ON EPH.BusinessEntityID=PP.BusinessEntityID) AS PODQ
WHERE PODQ.Redoslijed=4

--8.	Kreirati upit koji prikazuje proizvode kojih na skladištu ima u količini manjoj od 30 komada. Lista treba da sadrži naziv proizvoda, naziv skladišta (lokaciju), stanje na skladištu i ukupnu prodanu količinu. U rezultate upita uključiti i one proizvode koji nikad nisu prodavani, ne uzimajući u obzir njihovo stanje na skladištu. Ukoliko je ukupna prodana količina prikazana kao NULL vrijednost, izlaz zamijeniti brojem 0. (AdvantureWorks2017)
USE AdventureWorks2017

SELECT P.Name, L.Name, PI.Quantity,
ISNULL((SELECT SUM(SOD.OrderQty)
		FROM Sales.SalesOrderDetail AS SOD
        WHERE SOD.ProductID=P.ProductID
		), 0) 'Prodana količina'
FROM Production.Product AS P
	INNER JOIN Production.ProductInventory AS PI ON P.ProductID=PI.ProductID
	INNER JOIN Production.Location AS L ON PI.LocationID=L.LocationID
WHERE PI.Quantity<30 OR 
P.ProductID NOT IN
				(SELECT DISTINCT SOD.ProductID
				FROM Sales.SalesOrderDetail AS SOD) 
ORDER BY 4 DESC

--9.	Prikazati ukupnu prodanu količinu i ukupnu zaradu (uključujući popust) od prodaje svakog pojedinog proizvoda po teritoriji. Uzeti u obzir samo prodaju u sklopu ponude pod nazivom “Volume Discount 11 to 14” i to samo gdje je ukupna prodana količina veća od 100 komada. Zaradu zaokružiti na dvije decimale, te izlaz sortirati po zaradi u opadajućem redoslijedu. (AdvantureWorks2017)
SELECT ST.Name Teritorija, PP.Name Proizvod , 
		CAST(SUM(SOD.LineTotal) AS DECIMAL(10,2)) 'Ukupna zarada'
FROM Production.Product AS PP
	INNER JOIN Sales.SpecialOfferProduct AS SOP ON PP.ProductID=SOP.ProductID
	INNER JOIN Sales.SpecialOffer AS SO ON SOP.SpecialOfferID=SO.SpecialOfferID
	INNER JOIN Sales.SalesOrderDetail AS SOD ON SOP.SpecialOfferID=SOD.SpecialOfferID AND SOP.ProductID=SOD.ProductID
	INNER JOIN Sales.SalesOrderHeader AS SOH ON SOD.SalesOrderID=SOH.SalesOrderID
	INNER JOIN Sales.SalesTerritory AS ST ON SOH.TerritoryID=ST.TerritoryID
WHERE SO.Description LIKE 'Volume Discount 11 to 14'
GROUP BY ST.Name, PP.Name
HAVING SUM(SOD.OrderQty)>100
ORDER BY 3 DESC

--10.	Kreirati upit koji prikazuje naziv proizvoda, naziv lokacije, stanje zaliha na lokaciji, ukupno stanje zaliha na svim lokacijama i ukupnu prodanu količinu (stanja i ukupnu prodanu količinu izračunati za svaki proizvod pojedinačno). Uzeti u obzir prodaju samo u 2013. godini.  U rezultatima NULL vrijednosti zamijeniti sa 0 i sortirati po ukupnoj prodanoj količini u opadajućem redoslijedu. (AdvantureWorks2017)
SELECT P.Name 'Proizvod', L.Name 'Lokacija', PI.Quantity 'Zalihe na lokaciji',
(
	SELECT SUM(PI1.Quantity)
	FROM  Production.ProductInventory AS PI1
	WHERE PI1.ProductID=P.ProductID
) 'Ukupno stanje zaliha na svim lokacijama',
ISNULL((SELECT SUM(SOD.OrderQty)
		FROM Sales.SalesOrderHeader AS SOH
		INNER JOIN Sales.SalesOrderDetail AS SOD
		ON SOH.SalesOrderID=SOD.SalesOrderID
		WHERE YEAR(SOH.OrderDate)=2013 AND SOD.ProductID=P.ProductID
),0) 'Ukupna prodana kolicina'
FROM Production.Product AS P
	INNER JOIN Production.ProductInventory AS PI ON P.ProductID=PI.ProductID
	INNER JOIN Production.Location AS L ON PI.LocationID=L.LocationID
ORDER BY 5 DESC

--11.	Kreirati upit koji prikazuje uposlenike koji obavljaju ulogu predstavnika prodaje a obradili su 125 i više narudžbi i prodali količinski 8000 i više proizvoda. U rezultatima upita prikazati id, ime i prezime uposlenika, ukupan broj narudžbi i ukupan broj prodatih proizvoda. Rezultate sortirati prema ukupnom broju narudžbi u opadajućem redoslijedu. (Northwind)
USE Northwind
SELECT E.EmployeeID, E.FirstName, E.LastName, COUNT(*) AS 'Broj Narudzbi', Q.UkupnaProdaja AS 'Prodato'
FROM Employees AS E
INNER JOIN Orders AS O ON E.EmployeeID=O.EmployeeID
INNER JOIN (
    SELECT E1.EmployeeID, SUM(OD1.Quantity) AS 'UkupnaProdaja'
    FROM Employees AS E1
    INNER JOIN Orders AS O1 ON E1.EmployeeID=O1.EmployeeID
    INNER JOIN [Order Details] AS OD1 ON O1.OrderID=OD1.OrderID
    WHERE E1.Title LIKE 'Sales Representative'
    GROUP BY E1.FirstName, E1.LastName, E1.EmployeeID
) AS Q
ON E.EmployeeID=Q.EmployeeID
WHERE E.Title LIKE 'Sales Representative' AND Q.UkupnaProdaja>8000
GROUP BY E.FirstName, E.LastName, Q.UkupnaProdaja, E.EmployeeID
HAVING COUNT(*)>125

--12.	Naæi proizvode èijom je prodajom ostvaren najmanji i najveæi ukupni promet (uzimajuæi u obzir i popust), a zatim odrediti razliku izmeðu najmanjeg prometa po proizvodu i prosjeènog prometa prodaje proizvoda, te najveæeg prometa po proizvodu i prosjeènog prometa prodaje proizvoda. Rezultate prikazati zaokružene na dvije decimale. Upit treba sadržavati nazive proizvoda sa njihovim ukupnim prometom te izraèunate razlike. Rezultate upita prikazati na 2 naèina kao na slikama. (AdventureWorks2017)
--PRVA SLIKA 
USE AdventureWorks2017
SELECT PODQ1.Name Proizvod, PODQ1.[Najmanji promet], PODQ2.Name Proizvod, PODQ2.[Najveći promet],
PODQ1.[Najmanji promet]-PODQ3.[Prosjecan promet] 'Razlika min-avg',
PODQ2.[Najveći promet]-PODQ3.[Prosjecan promet] 'Razlika max-avg'
FROM
	(SELECT TOP 1 P.Name, CAST(SUM(SOD.LineTotal) AS decimal(18,2)) 'Najmanji promet'
	 FROM Sales.SalesOrderDetail AS SOD
	 INNER JOIN Production.Product AS P ON SOD.ProductID=P.ProductID
	 GROUP BY P.Name
	 ORDER BY 2) AS PODQ1, --CROSS JOIN
	(SELECT TOP 1 P.Name, CAST(SUM(SOD.LineTotal) AS decimal(18,2)) 'Najveći promet'
	 FROM Sales.SalesOrderDetail AS SOD
	 INNER JOIN Production.Product AS P ON SOD.ProductID=P.ProductID
	 GROUP BY P.Name
	 ORDER BY 2 DESC) AS PODQ2, --CROSS JOIN
	(SELECT CAST(AVG(PODQ.[Ukupan promet]) AS decimal(18,2)) 'Prosjecan promet'
	 FROM(SELECT P.Name, SUM(SOD.LineTotal) 'Ukupan promet'
		  FROM Sales.SalesOrderDetail AS SOD
		  INNER JOIN Production.Product AS P ON SOD.ProductID=P.ProductID
		  GROUP BY P.Name) AS PODQ) AS PODQ3

--DRUGA SLIKA (PRVI NAČIN)
DECLARE @Prosjek DECIMAL(18,2)
SET @Prosjek= (SELECT CAST(AVG(PODQ.[Ukupan promet]) AS decimal(18,2)) 'Prosjecan promet'
				FROM(SELECT SOD.ProductID, SUM(SOD.LineTotal) 'Ukupan promet'
					 FROM Sales.SalesOrderDetail AS SOD
		             GROUP BY SOD.ProductID) AS PODQ)
SELECT *
FROM(SELECT TOP 1 P.Name, CAST(SUM(SOD.LineTotal) AS decimal(18,2)) 'Najmanji promet',
	 CAST(SUM(SOD.LineTotal) AS decimal(18,2)) - @Prosjek 'Razlike'
		 FROM Sales.SalesOrderDetail AS SOD
		 INNER JOIN Production.Product AS P ON SOD.ProductID=P.ProductID
		 GROUP BY P.Name
		 ORDER BY 2) AS PODQ1

UNION

SELECT *
FROM(SELECT TOP 1 P.Name, CAST(SUM(SOD.LineTotal) AS decimal(18,2)) 'Najveći promet',
CAST(SUM(SOD.LineTotal) AS decimal(18,2)) -@Prosjek 'Razlike'
	FROM Sales.SalesOrderDetail AS SOD
	INNER JOIN Production.Product AS P ON SOD.ProductID=P.ProductID
	GROUP BY P.Name
	ORDER BY 2 DESC) AS PODQ2

--DRUGA SLIKA (DRUGI NAČIN)
DECLARE @Prosjek DECIMAL(18,2)
SET @Prosjek= (SELECT CAST(AVG(PODQ.[Ukupan promet]) AS decimal(18,2)) 'Prosjecan promet'
				FROM(SELECT SOD.ProductID, SUM(SOD.LineTotal) 'Ukupan promet'
					 FROM Sales.SalesOrderDetail AS SOD
		             GROUP BY SOD.ProductID) AS PODQ)

SELECT PODQ.Name, PODQ.Promet, PODQ.Promet-@Prosjek 'Razlike'
FROM(SELECT P.Name, CAST(SUM(SOD.LineTotal) AS decimal(18,2)) 'Promet',
	 ROW_NUMBER() OVER (ORDER BY SUM(SOD.LineTotal)) 'RowAsc',
	 ROW_NUMBER() OVER (ORDER BY SUM(SOD.LineTotal) DESC) 'RowDesc'
	 FROM Sales.SalesOrderDetail AS SOD
	 INNER JOIN Production.Product AS P ON SOD.ProductID=P.ProductID
	 GROUP BY P.Name) AS PODQ
WHERE RowAsc=1 OR RowDesc=1
ORDER BY 3


