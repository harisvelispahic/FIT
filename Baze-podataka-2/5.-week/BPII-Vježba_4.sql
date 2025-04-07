-- 1. Prikazati ukupnu vrijednost troška prevoza po državama ali samo ukoliko je veća od 4000 za robu koja se kupila u Francuskoj, Njemačkoj ili Švicarskoj. (Northwind)
use Northwind 

select 
	o.ShipCountry, 
	sum(o.Freight) as 'Sum of Freight'
from Orders as o
where o.ShipCountry in ('France', 'Germany', 'Switzerland')
group by o.ShipCountry
having sum(o.Freight) > 4000


-- 2. Prikazati 10 najprodavanijih proizvoda. Za proizvod prikazati njegov identifikacijski broj i naziv. Najprodavaniji proizvod je onaj koji je u najvećim količinama prodat. (Northwind)

select top 10 
	od.ProductID, 
	p.ProductName,
	sum(od.Quantity) as 'Sum of Quantity'
from [Order Details] as od
	inner join Products as p on od.ProductID = p.ProductID
group by od.ProductID, p.ProductName
order by sum(od.Quantity) desc


-- 3. Kreirati upit koji prikazuje zaradu od prodaje proizvoda. Lista treba da sadrži identifikacijski broj, naziv, potkategoriju i kategoriju proizvoda, ukupnu zaradu bez popusta, ukupnu zaradu sa popustom. Vrijednost zarade zaokružiti na dvije decimale. Uslov je da se prikaže zarada samo za stavke gdje je bilo popusta. Listu sortirati prema ukupnoj zaradi sa popustom u opadajućem redoslijedu. (AdventureWorks2017)
use AdventureWorks2017

select
	p.ProductID,
	p.Name,
	ps.Name as 'Subcategory',
	pc.Name as 'Category',
	round(sum(sod.UnitPrice * sod.OrderQty), 2) as 'Ukupna zarada bez popusta',
	cast(sum(sod.LineTotal) as decimal(18, 2)) as 'Ukupna zarada sa popustom'
from Sales.SalesOrderDetail as sod 
	inner join Production.Product as p on sod.ProductID = p.ProductID
	inner join Production.ProductSubcategory as ps on p.ProductSubcategoryID = ps.ProductSubcategoryID
	inner join Production.ProductCategory as pc on ps.ProductCategoryID = pc.ProductCategoryID
where sod.UnitPriceDiscount > 0
group by p.ProductID, p.Name, ps.Name, pc.Name
order by sum(sod.LineTotal) desc


-- 4. Prikazati tip popusta, naziv prodavnice i njen id. (Pubs) 
use pubs

select d.discounttype, s.stor_name, s.stor_id
from stores as s 
	inner join discounts as d on s.stor_id = d.stor_id


-- 5. Prikazati spojeno ime i prezime uposlenika, regiju, broj teritorija koje pokriva i nazive svih tih teritorija (koristeći string_agg funkciju). Uslov je da su zaposlenici mlađi od 65 godina. (Northwind) 
use Northwind

select
	concat(e.FirstName, ' ', e.LastName) 'Ime i prezime', 
	r.RegionDescription as 'Regija',
 	count(t.TerritoryID) as 'Pokriva teritorija',
	string_agg(trim(t.TerritoryDescription), ', ') as 'Teritorije'
from Employees as e
	inner join EmployeeTerritories as et on e.EmployeeID = et.EmployeeID
	inner join Territories as t on et.TerritoryID = t.TerritoryID
	inner join Region as r on r.RegionID = t.RegionID
where datediff(year, e.BirthDate, getdate()) < 65
group by concat(e.FirstName, ' ', e.LastName), r.RegionDescription


-- 6. Prikazati ukupnu vrijednost obrađenih narudžbi sa popustom za svakog uposlenika pojedinačno. Uslov je da su narudžbe kreirane u 1996. godini, te u obzir uzeti samo one uposlenike čija je ukupna ukupna obrađena vrijednost veća od 20000. Podatke sortirati prema ukupnoj vrijednosti (zaokruženoj na dvije decimale) u rastućem redoslijedu. (Northwind)  

select 
	concat(e.FirstName, ' ', e.LastName) as 'Employee',
	cast(sum(od.UnitPrice * od.Quantity * (1 - od.Discount)) as decimal(18, 2)) as 'Ukupna vrijednost narudžbe sa popustom'
from Employees as e 
	inner join Orders as o on e.EmployeeID = o.EmployeeID
	inner join [Order Details] as od on o.OrderID = od.OrderID
where year(o.OrderDate) = 1996
group by concat(e.FirstName, ' ', e.LastName)
having sum(od.UnitPrice * od.Quantity * (1 - od.Discount)) > 20000
order by 2 


-- 7. Prikazati naziv dobavljača, adresu i državu dobavljača, te nazive proizvoda koji pripadaju kategoriji pića a ima ih na stanju više od 30 komada. Rezultate upita sortirati po državama u abedecnom redoslijedu. (Northwind)  

select 
	s.CompanyName, 
	s.Address, 
	s.Country, 
	p.ProductName as 'Product'
from Suppliers as s
	inner join Products as p on s.SupplierID = p.SupplierID
	inner join Categories as c on p.CategoryID = c.CategoryID
where 
	p.UnitsInStock > 30 and
	c.Description like '%drink%'
order by 3


-- 8. Prikazati kontakt ime kupca, njegov id, id narudžbe, datum kreiranja narudžbe (prikazan u formatu dan.mjesec.godina, npr. 24.07.2021) te ukupnu vrijednost narudžbe sa i bez popusta. Prikazati samo one narudžbe koje su kreirane u 1997. godini. Izračunate vrijednosti zaokružiti na dvije decimale, te podatke sortirati prema ukupnoj vrijednosti narudžbe sa popustom u opadajućem redoslijedu. (Northwind) 

select
	c.ContactName,
	c.CustomerID,
	o.OrderID,
	format(o.OrderDate, 'dd.MM.yyyy') as 'OrderDate',
	cast(sum(od.UnitPrice * od.Quantity) as decimal(18, 2)) as 'Total price without discount',
	cast(sum(od.UnitPrice * od.Quantity * (1 - od.Discount)) as decimal(18, 2)) as 'Total price with discount'
from Customers as c
	inner join Orders as o on c.CustomerID = o.CustomerID
	inner join [Order Details] as od on o.OrderID = od.OrderID
where year(o.OrderDate) = 1997
group by c.ContactName, c.CustomerID, o.OrderID, format(o.OrderDate, 'dd.MM.yyyy')
order by 6 desc


-- 9. Prikazati 10 najskupljih stavki narudžbi. Upit treba da sadrži id stavke, naziv proizvoda, količinu, cijenu i vrijednost stavke narudžbe. Cijenu i vrijednost stavke narudžbe zaokružiti na dvije decimale. Izlaz formatirati na način da uz količinu stoji “kom” (npr. 50 kom) a uz cijenu i vrijednost stavke narudžbe “KM” (npr. 50 KM). (AdventureWorks2017) 
use AdventureWorks2017

select top 10
	sod.SalesOrderDetailID,
	p.Name,
	concat(sod.OrderQty, ' kom') as 'OrderQty',
	concat(cast(sod.UnitPrice as decimal(18, 2)), 'KM') as 'UnitPirce',
	concat(cast((sod.UnitPrice * sod.OrderQty) as decimal(18, 2)), 'KM') as 'Total price of Order Detail'
from Sales.SalesOrderDetail as sod
	inner join Production.Product as p on sod.ProductID = p.ProductID	
order by cast((sod.UnitPrice * sod.OrderQty) as decimal(18, 2)) desc


-- 10. Kreirati upit koji prikazuje ukupan broj narudžbi po teritoriji na kojoj je kreirana narudžba. Lista treba da sadrži sljedeće kolone: naziv teritorije, ukupan broj narudžbi. Uzeti u obzir samo teritorije na kojima je kreirano više od 1000 narudžbi. (AdventureWorks2017)  

select 
	st.Name as 'Teritory', 
	count(*) as 'Number of orders on this teritory'
from Sales.SalesOrderHeader as soh
	inner join Sales.SalesTerritory as st on soh.TerritoryID = st.TerritoryID
group by st.Name
having count(*) > 1000


-- 11. Kreirati upit koji prikazuje zaradu od prodaje proizvoda. Lista treba da sadrži naziv proizvoda, ukupnu zaradu bez uračunatog popusta i ukupnu zaradu sa uračunatim popustom. Iznos zarade zaokružiti na dvije decimale. Uslov je da se prikaže zarada samo za stavke gdje je bilo popusta. Listu sortirati po zaradi sa popustom opadajućim redoslijedom. (AdventureWorks2017)

select 
	p.Name as 'Product',
	cast(sum(sod.OrderQty * sod.UnitPrice) as decimal(18, 2)) as 'Total revenue of product without discount',
	cast(sum(sod.LineTotal) as decimal(18, 2)) as 'Total revenue of product with discount'
from Production.Product as p
	inner join Sales.SalesOrderDetail as sod on p.ProductID = sod.ProductID
where sod.UnitPriceDiscount > 0
group by p.Name
order by 3 desc
--ILI
select 
	p.Name as 'Product',
	cast(sum(sod.OrderQty * sod.UnitPrice) as decimal(18, 2)) as 'Total revenue of product without discount',
	cast(sum(sod.LineTotal) as decimal(18, 2)) as 'Total revenue of product with discount'
from Production.Product as p
	inner join Sales.SpecialOfferProduct as sop on p.ProductID = sop.ProductID
	inner join 
		Sales.SalesOrderDetail as sod on sop.ProductID = sod.ProductID and 
		sop.SpecialOfferID = sod.SpecialOfferID
where sod.UnitPriceDiscount > 0
group by p.Name
order by 3 desc


-- 12. Prikazati prosječnu ocjenu proizvoda koji su imaju više od 1 recenzije. Izlaz treba sadržavati broj, ime i cijenu proizvoda te prosječnu ocjenu svih njegovih recenzija. (AdventureWorks2017).
use AdventureWorks2017

select 
	pp.ProductNumber, 
	pp.Name, 
	pp.ListPrice, 
	avg(PR.Rating) 'Prosječna ocjena'
from Production.Product as pp
	inner join Production.ProductReview as pr on pr.ProductID = pp.ProductID
group by pp.ProductNumber, pp.Name, pp.ListPrice
having count(*) > 1

-- 13. Prikazati 5 dobavljača koji imaju navjeću ukupnu prodanu količinu proizvoda kategorije plodova mora, osim imena dobavljača i ukupne prodane količine, prikazati i ukupan prihod (sa popustom) ostvaren prodajom zaokružen na 2 decimale. (Northwind).
USE Northwind

SELECT TOP 5 
	S.CompanyName, 
	SUM(OD.Quantity) 'Količina', 
	SUM(ROUND(OD.UnitPrice*OD.Quantity*(1-OD.Discount), 2)) 'Prihod'
FROM Suppliers AS S
	INNER JOIN Products AS P ON P.SupplierID = S.SupplierID
	INNER JOIN [Order Details] AS OD ON OD.ProductID = P.ProductID
	INNER JOIN Categories AS C ON P.CategoryID = C.CategoryID
WHERE C.CategoryName LIKE 'Seafood'
GROUP BY S.CompanyName
ORDER BY 2 DESC

-- 14. Prikazati količinu obavljenih narudžbi za svakog kupca, uzeti u obzir samo one narudžbe koje su obradili uposlenici iz Londona i kupce koji su obavili 5 ili više narudžbi. Prikazati ime kupca, broj narudžbi i dodati novu kolonu 'Popust za vozarinu' koja određuje popust koji će kupac dobiti za plaćanje vozarine sljedeće svoje narudžbe. Kolonu popuniti na sljedeći način: ako je kupac na vozarinu za sve svoje narudžbe potrošio više od 500KM dobiva popust od -20%, za više od 1000KM dobiva popust od -45%, a -100% dobivaju oni koji su potrošili više od 2000KM, kupci koji nisu zadovoljili niti jedan uvjet ne dobivaju nikakav popust --. Izlaz sortirati po broju narudžbi silazno. (Northwind).

SELECT 
	C.ContactName, 
	COUNT(*) 'Broj narudžbi',
	CASE
		WHEN SUM(O.Freight) > 2000 THEN '-100%'
		WHEN SUM(O.Freight) > 1000 THEN '-45%'
		WHEN SUM(O.Freight) > 500 THEN '-20%'
		ELSE '--'
	END 'Popust za vozarinu'
FROM Customers AS C
	INNER JOIN Orders AS O ON O.CustomerID = C.CustomerID
	INNER JOIN Employees AS E ON O.EmployeeID = E.EmployeeID
WHERE E.City LIKE 'London'
GROUP BY C.ContactName
HAVING COUNT(*) >= 5
ORDER BY 2 DESC

-- 15. Prikazati ID kategorije, naziv kategorije i ukupnu količinu proizvoda na stanju po kategorijama, ali samo za kategorije čija je ukupna količina na stanju veća od 500. Rezultate sortirati po ukupnoj količini u opadajućem redoslijedu. (Northwind).
use Northwind

select 
	c.CategoryID,
	c.CategoryName,
	sum(p.UnitsInStock) as 'Ukupna količina'
from Products as p
	inner join Categories as c on p.CategoryID = c.CategoryID
group by c.CategoryID, c.CategoryName
having sum(p.UnitsInStock) > 500
order by 3 desc

-- 16. Prikazati ID i naziv kompanije kupca, broj narudžbi koje je napravio i ukupnu potrošnju (sa popustom) za kupce koji su potrošili više od 30,000 KM. Rezultate sortirati po ukupnoj potrošnji u opadajućem redoslijedu. (Northwind).

select 
	c.CustomerID,
	c.CompanyName, 
	count(distinct o.OrderID) as 'Broj narudžbi', -- bitno je dodati DISTINCT, jer bez njega broji sve STAVKE narudžbe, a ne narudžbe
	cast(sum(od.UnitPrice * od.Quantity * (1 - od.Discount)) as decimal(18, 2)) as 'Ukupna potrošnja'
from Customers as c
	inner join Orders as o on c.CustomerID = o.CustomerID
	inner join [Order Details] as od on o.OrderID = od.OrderID
group by c.CustomerID, c.CompanyName
having sum(od.UnitPrice * od.Quantity * (1 - od.Discount)) > 30000
order by 4

-- 17. Prikazati naziv dobavljača, broj različitih proizvoda koje isporučuje i prosječnu cijenu njihovih proizvoda (zaokruženu na dvije decimale). Uslov je da dobavljač isporučuje više od 3 proizvoda. (Northwind).

select 
	s.CompanyName,
	count(*) as 'Broj proizvoda',
	cast(avg(p.UnitPrice) as decimal(18, 2)) as 'Prosječna cijena'
from Suppliers as s
	inner join Products as p on s.SupplierID = p.SupplierID
group by s.CompanyName
having count(*) > 3

--ILI
--distinct count nam u ovom slučaju nije potreban, jer će svaki zapis predstavljati različit proizvod, ali dobiti ćemo ispravan rezulat i sa distinct count-om kada prebrojavamo PK (ProductID u ovom slučaju).
select 
	s.CompanyName,
	count(distinct p.ProductID) as 'Broj proizvoda',
	cast(avg(p.UnitPrice) as decimal(18, 2)) as 'Prosječna cijena'
from Suppliers as s
	inner join Products as p on s.SupplierID = p.SupplierID
group by s.CompanyName
having count(distinct p.ProductID) > 3

-- 18. Prikazati naziv i ID prodavnice, broj naslova i nazive naslova koje prodaje. Prikazati samo prodavnice koje prodaju više od 3 naslova. (Pubs).
use pubs

select 
	st.stor_id, 
	st.stor_name, 
	count(distinct sa.title_id) as 'Broj naslova', 
	string_agg(t.title, ' ||| ') as 'Naslovi'
from stores as st
	inner join sales as sa on st.stor_id = sa.stor_id
	inner join titles as t on sa.title_id = t.title_id
group by st.stor_id, st.stor_name
having count(distinct sa.title_id) > 3

-- 19. Prikazati naziv teritorije, broj zaposlenika koji rade na njoj, ukupnu prodajnu kvotu te godine i ukupnu prodaju od početka godine do danas, ali samo za teritorije gdje je ukupna prodaja od početka godine do danas 10 puta ispunila svoju ukupnu prodajnu kvotu. (AdventureWorks2017).
use AdventureWorks2017

select 
	st.Name as 'Territory',
	count(p.BusinessEntityID) as 'No of Employees',
	sum(sp.SalesQuota) as 'Sum of sales quota',
	sum(sp.SalesYTD) as 'Total sales year-to-date'
from Sales.SalesTerritory as st
	inner join Sales.SalesPerson as sp on st.TerritoryID = sp.TerritoryID
	inner join HumanResources.Employee as e on sp.BusinessEntityID = e.BusinessEntityID
	inner join Person.Person as p on e.BusinessEntityID = p.BusinessEntityID
group by st.Name
having sum(sp.SalesYTD) > sum(sp.SalesQuota) * 10

