--1.	 Prikazati izdavaèe koji su objavili više naslova/knjiga nego izdavaèi iz Kalifornije. Zaglavlje: naziv izdavaèa, grad, država
use pubs

select p.pub_name, p.city, p.state, count(*) as 'Broj naslova'
from publishers as p
	inner join titles as t on p.pub_id = t.pub_id
group by p.pub_name, p.city, p.state
having count(*) > (
	select count(*)
	from publishers as p
		inner join titles as t on p.pub_id = t.pub_id
	where p.state like 'CA'
	group by p.state
)

--2.	 Prikazati trgovine u kojima je prodano više knjiga (kolièina) od ukupnog broja prodanih knjiga tipa „business“.  Zaglavlje: naziv trgovine, grad, država 
select
	st.stor_name
	,st.city
	,st.state
	,sum(sa.qty) as 'Ukupno prodano knjiga'
from stores as st
	inner join sales as sa on st.stor_id = sa.stor_id
group by st.stor_name, st.city, st.state
having sum(sa.qty) > (
	select sum(s.qty) as 'Ukupno prodano knjiga'
	from titles as t
		inner join sales as s on t.title_id = s.title_id
	where t.type like 'business'
	)

--3.	Prikazati sve autore koji su izdali više knjiga od prosjeènog broja izdanih knjiga po izdavaèu. Zaglavlje: šifra, ime, grad
select a.au_id, a.au_fname, a.city, count(*) as 'Izdao knjiga'
from authors as a
	inner join titleauthor as ta on a.au_id = ta.au_id
group by a.au_id, a.au_fname, a.city
having count(*) > (
	select avg(subQ.[Izdao knjiga]) as 'Prosjek izdatih knjiga po izdavaèima'
	from (
		select p.pub_name, count(*) as 'Izdao knjiga'
		from publishers as p 
			inner join titles as t on p.pub_id = t.pub_id
		group by p.pub_name
		) as subQ
)

--4.	Za svaki grad prikazati izdavaèe koji su u njemu ostvarili najveæi prihod od prodaje (prihod od prodaje = kolièina * cijena). Zaglavlje: grad, izdavaè, prihod 
select st.city, p.pub_name, sum(sa.qty * t.price) as 'Prihod'
from stores as st
	inner join sales as sa on st.stor_id = sa.stor_id
	inner join titles as t on sa.title_id = t.title_id
	inner join publishers as p on t.pub_id = p.pub_id
group by st.city, p.pub_name
having concat(sum(sa.qty * t.price), ' ', st.city) IN (
											select concat(max(sq.Prihod), ' ', sq.city) 'Najveći prihod u gradu po prodavaču'
											from (
													select st.city, p.pub_name, sum(sa.qty*t.price) as 'Prihod'
													from stores as st
														inner join sales as sa on st.stor_id = sa.stor_id
														inner join titles as t on sa.title_id = t.title_id
														inner join publishers as p on t.pub_id = p.pub_id
													group by st.city, p.pub_name
												) as sq
											group by sq.city
											)

--5.	Prikaži autore koji nisu prodali niti jednu knjigu u trgovina smještenima u Washingtonu. Zaglavlje: ime, prezime, grad, država 
select a.au_fname, a.au_lname, a.city, a.state
from authors as a
where not exists (
	select *
	from authors as aSQ
		inner join titleauthor as ta on aSQ.au_id = ta.au_id
		inner join titles as t on ta.title_id = t.title_id
		inner join sales as sa on t.title_id = sa.title_id
		inner join stores as st on sa.stor_id = st.stor_id
	where aSQ.au_id = a.au_id and (st.state like 'WA')
	)

--6.	Prikazati prosjeènu starost knjiga/naslova prodanih u trgovinama u kojima se prodaju naslovi duži od 35 znakova. Zaglavlje: prosjeèna starost knjiga 
select avg(subQ.[Starost knjige]) as 'Prosjeèna starost knjiga'
from (
	select t.title_id, datediff(year, t.pubdate, getdate()) as 'Starost knjige'
	from titles as t
		inner join sales as sa on t.title_id = sa.title_id
		inner join stores as st on sa.stor_id = st.stor_id
	where len(t.title) > 35
	) as subQ

--7.	Prikazati autore èije se knjige/naslovi prodaju u trgovinama koje se nalaze u istim saveznim državama u kojima su smješteni izdavaèi koji su objavili više od 5 naslova. Zaglavlje: ime, prezime, savezna država 
SELECT DISTINCT A.au_fname, A.au_lname, A.state
FROM authors AS A
	INNER JOIN titleauthor AS TA ON TA.au_id = A.au_id
	INNER JOIN sales AS S ON TA.title_id = S.title_id
	INNER JOIN stores AS ST ON S.stor_id = ST.stor_id
WHERE ST.state IN (
					SELECT SQ.state
					FROM (
						SELECT P.pub_id, P.pub_name, P.state, COUNT(*) 'Izdano'
						FROM publishers AS P
							INNER JOIN titles AS T ON T.pub_id = P.pub_id
						GROUP BY P.pub_id, P.pub_name, P.state
						HAVING COUNT(*) > 5
					) AS SQ
				)

--8.	Prikaži naslove koji su prodani u više od 40 komada, a objavljeni su nakon 12.6.1991. Zaglavlje: naslov, tip, cijena, datum objave  
SELECT T.title, T.type, T.price, T.pubdate
FROM titles AS T
	INNER JOIN sales AS S ON S.title_id = T.title_id
WHERE T.pubdate > '1991-06-12'
GROUP BY T.title, T.type, T.price, T.pubdate
HAVING SUM(S.qty) > 40

--9.	Prikazati naslove starije od najbolje prodavanog naslova kojeg je izdao izdavaè iz savezne države koja sadrži slog 'CA'. Zaglavlje: naslov, tip 
SELECT T.title, T.type, T.pubdate
FROM titles AS T
WHERE T.pubdate < (
				SELECT SQ.pubdate
				FROM (
					SELECT TOP 1 P.pub_id, T.title_id, T.pubdate, SUM(S.qty) 'Prodano'
					FROM sales AS S
						INNER JOIN titles AS T ON S.title_id = T.title_id
						INNER JOIN publishers AS P ON T.pub_id = P.pub_id
					WHERE P.state LIKE 'CA'
					GROUP BY P.pub_id, T.title_id, T.pubdate
					ORDER BY 4 DESC 
					) AS SQ
				)

--10.	Prikaži tko je izdavao knjige poslije 1.1.1992. Zaglavlje: naziv izdavaèa, grad, država 
SELECT P.pub_name, P.city, P.country
FROM publishers AS P
WHERE EXISTS (
			SELECT *
			FROM titles AS T
			WHERE T.pubdate > '1992-01-01' AND T.pub_id = P.pub_id
			)
