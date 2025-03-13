--USE Vjezbe0;
--1
SELECT *
FROM Radnik;

--2
SELECT Ime, Prezime, Adresa
FROM Radnik
ORDER BY Prezime ASC;

--3
SELECT R.Id, R.Ime, R.Prezime, R.Adresa
FROM Radnik AS R
ORDER BY R.Adresa DESC, R.Prezime;

--4
SELECT Prezime, DatumU, Placa
FROM Radnik
ORDER BY Placa DESC;

--5
SELECT *
FROM Radnik AS R
WHERE R.Placa > 1500;

--6
SELECT R.Ime, R.Adresa
FROM Radnik AS R
WHERE R.Placa < 2000 AND R.Dodatak > 500;

--7
SELECT R.DatumU, R.IdManager, R.IdOdjel
FROM Radnik AS R
WHERE R.IdOdjel = 40 AND R.IdManager = 112 AND R.Dodatak < 50;

--8
SELECT *
FROM Radnik as R
WHERE R.IdOdjel = 60 OR R.Placa >= 4000
ORDER BY R.Adresa, R.Prezime;

--9
SELECT R.Ime, R.DatumU, R.Dodatak
FROM Radnik AS R
WHERE R.Prezime LIKE '%ic';

--10
SELECT R.Id, R.Adresa, R.DatumU, R.Ime
FROM Radnik AS R
WHERE LOWER(R.Ime) LIKE 'm%' AND LOWER(R.Adresa) LIKE 'd%';

--11
SELECT R.Ime, R.IdOdjel
FROM Radnik AS R
WHERE R.Dodatak IS NULL;

--12
SELECT *
FROM Radnik as R
WHERE R.Prezime LIKE '%mi%' OR R.IdOdjel = 20;

--13
SELECT *
FROM Radnik as R
WHERE R.Adresa LIKE '%v%' AND R.Placa > 1250;

--14
SELECT R.Prezime, R.DatumU, R.Placa
FROM Radnik as R
WHERE R.IdManager IS NULL
ORDER BY R.DatumU DESC;

--15
SELECT R.Ime
FROM Radnik as R
WHERE R.Placa IN (1300, 1400, 1500, 1600);

--16
SELECT R.Id, R.Ime, R.DatumU
FROM Radnik as R
WHERE R.Placa BETWEEN 2000 AND 3000
ORDER BY R.Ime;

--17
SELECT R.IdOdjel
FROM Radnik as R
WHERE R.Dodatak BETWEEN 500 AND 1000;

--18
SELECT R.Ime
FROM Radnik as R;

--19
SELECT DISTINCT R.Ime
FROM Radnik as R;

--20
SELECT R.Ime, R.Placa, R.Placa/30 "Dnevnica"
FROM Radnik as R;

--21
SELECT AVG(R.Placa) "Prosjecna placa"
FROM Radnik AS R;

--22
SELECT COUNT(R.Id) "Broj radnika"
FROM Radnik AS R;

--23
SELECT COUNT(R.Id) "Broj radnika"
FROM Radnik AS R
WHERE R.Dodatak IS NOT NULL;

--ILI

SELECT COUNT(R.Dodatak) "Broj radnika"
FROM Radnik AS R;

--24
SELECT COUNT(U.Id) "Broj ugovora (SA)"
FROM Ugovor AS U
WHERE U.Mjesto = 'Sarajevo';

--25
SELECT R.Ime, R.Prezime, O.Sjediste
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id;

--26
SELECT R.Ime, R.Prezime, O.Naziv
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id
WHERE O.Sjediste = 'Sarajevo';

--27
SELECT R.Ime, R.Prezime, R.Placa
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id
WHERE R.Posao = 'Promotor' OR O.Naziv='Istraživanje';




--SELECT R.Posao, AVG(R.Placa) 'Prosjek po poslu'
--FROM Radnik AS R
--GROUP BY R.Posao
--HAVING AVG(R.Placa)>1500;

--HAVING filtrira grupe, ne mozemo ga imati bez GROUP BY


--SELECT *
--FROM Radnik AS R, Odjel AS O;
--CROSS JOIN -> rijetko se koristi, uzme sve podatke iz jedne i iz druge tabele

--SELECT *
--FROM Radnik AS R 
--INNER JOIN 
--Odjel AS O 
--ON R.IdOdjel = O.Id;

--INNER JOIN -> spajamo na osnovu stranih ključeva