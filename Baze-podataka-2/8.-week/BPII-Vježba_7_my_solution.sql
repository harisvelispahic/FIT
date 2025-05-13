-- 1. Prikazati izdavače koji su objavili više naslova/knjiga nego izdavači iz Kalifornije. Zaglavlje: naziv izdavača, grad, država

USE pubs;

SELECT 
	P.pub_name, 
	P.city, 
	P.state
FROM publishers AS P
	INNER JOIN titles AS T ON P.pub_id = T.pub_id
GROUP BY P.pub_name, P.city, P.state
HAVING COUNT(*) >	(
					SELECT COUNT(*) AS broj_naslova
					FROM publishers AS P
						INNER JOIN titles AS T ON P.pub_id = T.pub_id
					WHERE P.state LIKE 'CA'
					)


-- 2. Prikazati trgovine u kojima je prodano više knjiga (količina) od ukupnog broja prodanih knjiga tipa „business“.  Zaglavlje: naziv trgovine, grad, država

SELECT 
	ST.stor_name, 
	ST.city, 
	ST.state
FROM stores AS ST
	INNER JOIN sales AS SA ON ST.stor_id = SA.stor_id
GROUP BY ST.stor_name, ST.city, ST.state
HAVING SUM(SA.qty) >
					(
					SELECT SUM(S.qty)
					FROM titles AS T
						INNER JOIN sales AS S ON T.title_id = S.title_id
					WHERE T.type LIKE 'business'
					)	

-- 3. Prikazati sve autore koji su izdali više knjiga od prosječnog broja izdanih knjiga po izdavaču. Zaglavlje: šifra, ime, grad

SELECT 
	A.au_id, 
	A.au_fname, 
	A.city
FROM authors AS A
	INNER JOIN titleauthor AS TA ON A.au_id = TA.au_id
GROUP BY A.au_id, A.au_fname, A.city
HAVING COUNT(*) >
					(
					SELECT AVG(SUBQ_INNER.broj_knjiga)
					FROM
						(
						SELECT COUNT(*) AS broj_knjiga
						FROM publishers AS P
							INNER JOIN titles AS T ON P.pub_id = T.pub_id
						GROUP BY P.pub_id
						) AS SUBQ_INNER
					)

-- 4. Za svaki grad prikazati izdavače koji su u njemu ostvarili najveći prihod od prodaje (prihod od prodaje = količina * cijena). Zaglavlje: grad, izdavač, prihod

SELECT 
	Rezultat.city, 
	Rezultat.pub_name, 
	Rezultat.Prihod
FROM
	(
	SELECT ST.city, P.pub_id, P.pub_name, SUM(T.price * SA.qty) AS Prihod
	FROM publishers AS P
		INNER JOIN titles AS T ON P.pub_id = T.pub_id
		INNER JOIN sales AS SA ON T.title_id= SA.title_id
		INNER JOIN stores AS ST ON SA.stor_id = ST.stor_id
	GROUP BY ST.city, P.pub_id, P.pub_name
	) AS Rezultat
INNER JOIN
			(
			SELECT ZaradaPoGradu.city, MAX(ZaradaPoGradu.Prihod) AS Max_Prihod
			FROM
				(
				SELECT ST.city, P.pub_id, P.pub_name, SUM(T.price * SA.qty) AS Prihod
				FROM publishers AS P
					INNER JOIN titles AS T ON P.pub_id = T.pub_id
					INNER JOIN sales AS SA ON T.title_id= SA.title_id
					INNER JOIN stores AS ST ON SA.stor_id = ST.stor_id
				GROUP BY ST.city, P.pub_id, P.pub_name
				) AS ZaradaPoGradu
			GROUP BY ZaradaPoGradu.city
			) AS MaxZaradaPoGradu
ON Rezultat.city = MaxZaradaPoGradu.city AND Rezultat.Prihod = MaxZaradaPoGradu.Max_Prihod


-- 5. Prikaži autore koji nisu prodali niti jednu knjigu u trgovinama smještenim u Washingtonu. Zaglavlje: ime, prezime, grad, država

SELECT A.au_fname, A.au_lname, A.city, A.state
FROM authors AS A
WHERE NOT EXISTS
				(
				SELECT 1
				FROM titleauthor AS TA1
					INNER JOIN sales AS SA1 ON TA1.title_id = SA1.title_id
					INNER JOIN stores AS ST1 ON SA1.stor_id = ST1.stor_id
				WHERE ST1.state LIKE 'WA' AND TA1.au_id = A.au_id
				)

-- 6. Prikazati prosječnu starost knjiga/naslova prodanih u trgovinama u kojima se prodaju naslovi duži od 35 znakova. Zaglavlje: prosječna starost knjiga

SELECT AVG(DATEDIFF(YEAR, T.pubdate, GETDATE())) AS prosjecna_starost
FROM titles AS T
	INNER JOIN sales AS SA ON T.title_id = SA.title_id
WHERE SA.stor_id IN
					(
					SELECT ST.stor_id
					FROM stores AS ST
						INNER JOIN sales AS SA ON ST.stor_id = SA.stor_id
					WHERE SA.title_id IN
										(
										SELECT T.title_id
										FROM titles AS T
										WHERE LEN(T.title) > 35
										)
					)

-- 7. Prikazati autore čije se knjige/naslovi prodaju u trgovinama koje se nalaze u istim saveznim državama u kojima su smješteni izdavači koji su objavili više od 5 naslova. Zaglavlje: ime, prezime, savezna država

SELECT DISTINCT 
	A.au_fname, 
	A.au_lname, 
	A.state
FROM authors AS A
	INNER JOIN titleauthor AS TA ON A.au_id = TA.au_id
	INNER JOIN titles AS T ON TA.title_id = T.title_id
	INNER JOIN sales AS SA ON T.title_id = SA.title_id
	INNER JOIN stores AS ST ON SA.stor_id = ST.stor_id
WHERE ST.state IN
					(
					SELECT P.state
					FROM publishers AS P	
							INNER JOIN titles AS T ON P.pub_id = T.pub_id
					GROUP BY P.pub_id, P.state
					HAVING COUNT(*) > 5
					)

-- 8. Prikaži naslove koji su prodani u više od 40 komada, a objavljeni su nakon 12.6.1991. Zaglavlje: naslov, tip, cijena, datum objave 

SELECT 
	T.title, 
	T.type, 
	T.price, 
	T.pubdate
FROM titles AS T
	INNER JOIN sales AS S ON T.title_id = S.title_id
WHERE T.pubdate > '1991-06-12'
GROUP BY T.title, T.type, T.price, T.pubdate
HAVING SUM(S.qty) > 40

-- 9. Prikazati naslove starije od najbolje prodavanog naslova kojeg je izdao izdavač iz savezne države koja sadrži slog 'CA'. Zaglavlje: naslov, tip
SELECT
	T.title,
	T.type
FROM titles AS T
WHERE T.pubdate <	
					(
					SELECT T.pubdate
					FROM titles AS T
						INNER JOIN sales AS S ON T.title_id = S.title_id
					GROUP BY T.title_id, T.pubdate
					HAVING SUM(S.qty) =
										(
										SELECT MAX(SUBQ.ukupna_kolicina)
										FROM
											(
											SELECT SUM(S.qty) AS ukupna_kolicina
											FROM titles AS T
												INNER JOIN sales AS S ON T.title_id = S.title_id
												INNER JOIN publishers AS P ON T.pub_id = P.pub_id
											WHERE P.state LIKE '%CA%'
											GROUP BY T.title_id
											) AS SUBQ
										)
					)

-- 10. Prikaži tko je izdavao knjige poslije 1.1.1992. Zaglavlje: naziv izdavača, grad, država

SELECT DISTINCT 
	P.pub_name, 
	P.city, 
	P.state
FROM publishers AS P
	INNER JOIN titles AS T ON P.pub_id = T.pub_id
WHERE T.pubdate > '1992-1-1'


-- ILI


SELECT 
	P.pub_name, 
	P.city, 
	P.state
FROM publishers AS P
WHERE EXISTS	(
				SELECT 1
				FROM titles AS T
				WHERE P.pub_id = T.pub_id AND T.pubdate > '1992-1-1'
				)

-- EXISTS KORELACIJSKI UPIT