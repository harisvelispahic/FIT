-- PRIPREMA

USE Northwind;

SELECT *
FROM [Order Details] AS OD
WHERE OD.UnitPrice =
	(SELECT MIN(OD.UnitPrice)
	FROM [Order Details] AS OD);


-- Prikazi najjeftiniji proizvod iz svake kategorije

SELECT *
FROM Products AS P
WHERE P.UnitPrice IN
	(SELECT MIN(P.UnitPrice)
	FROM Products AS P
		INNER JOIN Categories AS C ON P.CategoryID = C.CategoryID
	GROUP BY C.CategoryName);






-- 1. Prikazati sve države čija je ukupna vrijednost projekata bila veća od prosječne vrijednosti projekata. 
-- Izgled izvješća: Šifra države, Naziv države, Ukupna vrijednost projekata 

USE Test;

SELECT DR.sifra, DR.naziv, SUM(P.vrijednost) 'Ukupna vrijednost projekata'
FROM drzave AS DR
	INNER JOIN donatori AS DO ON DR.sifra = DO.id_drzava
	INNER JOIN projekti AS P ON DO.sifra = P.id_donator
GROUP BY DR.sifra, DR.naziv
HAVING SUM(P.vrijednost) >
							(SELECT AVG(P.vrijednost) 'Prosjecna vrijednost projekata'
							FROM projekti AS P);

-- 2. Prikazati sve države kod kojih je vrijednost projekta jednaka maksimalnoj vrijednosti projekta za tu državu. 
-- Izgled izvješća: Šifra države, Naziv države, Vrijednost projekta 

SELECT DR.naziv, MAX(P.vrijednost)
FROM drzave AS DR
	INNER JOIN donatori AS DO ON DR.sifra = DO.id_drzava
	INNER JOIN projekti AS P ON DO.sifra = P.id_donator
GROUP BY DR.naziv


-- 3. Prikazati sve fakultete koji nisu imali niti jednog voditelja projekta. 
-- Izgled izvješća: Šifra fakulteta Naziv fakulteta

SELECT F.sifra, F.naziv
FROM fakulteti AS F
WHERE NOT EXISTS 
				(SELECT 1
				FROM projekti AS PROJ
					INNER JOIN profesori AS PROF ON PROJ.id_voditelj = PROF.sifra
				WHERE PROJ.id_voditelj = PROF.sifra)

-- 4. Prikazati sve projekte na kojima je radilo više profesora od prosječnog broja profesora po projektu. 
-- Izgled izvješća: Naziv projekta Vrijednost Broj profesora

SELECT PROJ.naziv, PROJ.vrijednost, COUNT(*) 'Broj profesora'
FROM projekti AS PROJ
		INNER JOIN projekti_ucesnici AS PU ON PROJ.sifra = PU.id_projekt
GROUP BY PROJ.naziv, PROJ.vrijednost
HAVING COUNT(*) > 
					(SELECT AVG(SUBQ.[Broj profesora])
					FROM
						(SELECT COUNT(*) 'Broj profesora'
						FROM projekti_ucesnici AS PU
						GROUP BY PU.id_projekt) AS SUBQ)


-- 5. Prikazati sve projekte čija je duljina trajanja veća od prosječne duljine trajanja projekta. 
-- Izgled izvješća: Šifra Naziv projekta Vrijednost Duljina trajanja

SELECT P.sifra, P.naziv, P.vrijednost, DATEDIFF(DAY, P.datum_pocetka, P.datum_svrsetka) 'Trajanje projekta'
FROM projekti AS P
WHERE DATEDIFF(DAY, P.datum_pocetka, P.datum_svrsetka) >
														(SELECT AVG(DATEDIFF(DAY, P.datum_pocetka, P.datum_svrsetka)) 'Prosjecno trajanje projekta'
														FROM projekti AS P)