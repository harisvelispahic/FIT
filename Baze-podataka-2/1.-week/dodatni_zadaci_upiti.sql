--USE Vjezbe0;

--1
SELECT *
FROM Radnik;

--2
SELECT R.Ime, R.Prezime, R.Adresa
FROM Radnik AS R
ORDER BY R.Prezime;

--3
SELECT R.Id, R.Ime, R.Prezime, R.Adresa
FROM Radnik AS R
ORDER BY R.Adresa, R.Prezime;

--4
SELECT R.Prezime, R.DatumU, R.Placa
FROM Radnik AS R
ORDER BY R.Placa DESC;

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
FROM Radnik AS R
WHERE R.IdOdjel = 60 OR R.Placa >= 4000
ORDER BY R.Adresa, R.Prezime;

--9
SELECT R.Ime, R.DatumU, R.Dodatak
FROM Radnik AS R
WHERE R.Prezime LIKE '%ic';

--10
SELECT R.Id, R.Adresa, R.DatumU
FROM Radnik AS R
WHERE LOWER(R.Ime) LIKE 'm%' AND LOWER(R.Adresa) LIKE 'd%';

--11
SELECT R.Ime, R.IdOdjel
FROM Radnik AS R
WHERE R.Dodatak IS NULL;

--12
SELECT *
FROM Radnik AS R
WHERE LOWER(R.Prezime) LIKE '%mi%' OR R.IdOdjel = 20;

--13
SELECT *
FROM Radnik AS R
WHERE LOWER(R.Adresa) LIKE '%v%' AND R.Placa > 1250;

--14
SELECT R.Prezime, R.DatumU, R.Placa
FROM Radnik AS R
WHERE R.IdManager IS NULL
ORDER BY R.DatumU DESC;

--15
SELECT R.Ime
FROM Radnik AS R
WHERE R.Placa IN (1300, 1400, 1500, 1600);

--16
SELECT R.Id, R.Ime, R.DatumU
FROM Radnik AS R
WHERE R.Placa BETWEEN 2000 AND 3000
ORDER BY R.Ime;

--17
SELECT R.Id
FROM Radnik AS R
WHERE R.Dodatak BETWEEN 500 AND 1000;

--18
SELECT R.Ime
FROM Radnik AS R;

--19
SELECT DISTINCT R.Ime
FROM Radnik AS R;

--20
SELECT R.Ime, R.Placa, R.Placa / 30 'Dnevnica'
FROM Radnik AS R;

--21
SELECT R.Ime, R.Placa, R.Placa * 12 'Godisnja placa', R.Placa / 30 'Dnevnica'
FROM Radnik AS R
ORDER BY R.Placa DESC;

--22
SELECT R.Id
FROM Radnik AS R
WHERE R.Placa / 30 BETWEEN 200 AND 300;

--23
SELECT R.Id, R.IdManager, R.IdOdjel
FROM Radnik AS R
WHERE R.IdOdjel NOT IN (40,50);

--24
SELECT R.Placa * 1.15 'Uvecana placa', R.Placa * 0.15 'Uvecana za'
FROM Radnik AS R
WHERE R.Adresa LIKE 'Zagreba%';
--FORMATIRANJE --> Zagreba%

--25
SELECT *
FROM Klijent AS K
WHERE K.Grad = 'Mostar';

--26
SELECT U.Id
FROM Ugovor AS U
WHERE U.Iznos > 500000;

--27
SELECT *
FROM Ugovor AS U
WHERE LOWER(U.Mjesto) LIKE '%ar%'
ORDER BY U.Mjesto, U.Datum;

--28
SELECT U.Datum
FROM Ugovor AS U
WHERE U.Iznos BETWEEN 300000 AND 750000;

--29
SELECT K.Naziv, K.Fax
FROM Klijent AS K
WHERE K.Fax LIKE '6%';

--30
SELECT *
FROM Klijent AS K
WHERE K.Grad = 'Mostar' AND K.Telefon LIKE '4%';

--31
SELECT DISTINCT R.Posao
FROM Radnik AS R;

--32
SELECT SUM(R.Placa) 'Ukupna placa'
FROM Radnik AS R;

--33
SELECT AVG(R.Placa) 'Prosjecna placa'
FROM Radnik AS R;

--34
SELECT MIN(R.Placa) 'Najmanja placa', MAX(R.Placa) 'Najveca placa'
FROM Radnik AS R;

--35
SELECT SUM(R.Placa) 'Ukupna placa', AVG(R.Placa) 'Prosjecna placa'
FROM Radnik AS R;

--36
SELECT MAX(R.Placa) 'Najveca placa', AVG(R.Placa) 'Prosjecna placa'
FROM Radnik AS R
WHERE R.Adresa LIKE '%Splitska%';

--37
SELECT COUNT(*)
FROM Radnik AS R;

--38
SELECT COUNT(*)
FROM Radnik AS R
WHERE R.Dodatak IS NOT NULL;

--39
SELECT COUNT(*)
FROM Radnik AS R
WHERE R.IdManager IS NOT NULL;

--40
SELECT COUNT(*)
FROM Radnik AS R
WHERE R.IdManager IS NULL;

--41
SELECT COUNT(*)
FROM Radnik AS R
WHERE R.IdOdjel = 30 AND R.Dodatak IS NOT NULL;

--42
SELECT SUM(U.Iznos)
FROM Ugovor AS U;

--43
SELECT AVG(U.Iznos)
FROM Ugovor AS U
WHERE U.Mjesto = 'Mostar';

--44
SELECT COUNT(*)
FROM Ugovor AS U;

--45
SELECT COUNT(*)
FROM Ugovor AS U
WHERE U.Mjesto = 'Sarajevo';

--46
SELECT COUNT(*)
FROM Radnik AS R
WHERE R.Adresa LIKE 'Zagreba%' AND R.Dodatak IS NULL;

--47
SELECT COUNT(*)
FROM Ugovor AS U
WHERE U.Iznos BETWEEN 200000 AND 800000;

--48
SELECT COUNT(*)
FROM Klijent AS K
WHERE K.Grad = 'Mostar' AND K.Adresa = 'Vukovarska%';

--49
SELECT COUNT(*)
FROM Klijent AS K;

--50
SELECT COUNT(*)
FROM Klijent AS K
WHERE LOWER(K.Naziv) LIKE 'a%';

--51
SELECT COUNT(*)
FROM Radnik AS R
WHERE R.Adresa LIKE 'Dubrova%' AND R.Posao LIKE 'Prodava%';

--52
SELECT R.IdOdjel, MIN(R.Placa) 'Najmanja placa', MAX(R.Placa) 'Najveca placa'
FROM Radnik AS R
GROUP BY R.IdOdjel;

--53
SELECT K.Grad ,COUNT(*)
FROM Klijent AS K
GROUP BY K.Grad;

--54
SELECT R.Posao, COUNT(*)
FROM Radnik AS R
GROUP BY R.Posao;

--55
SELECT R.Posao, COUNT(*)
FROM Radnik AS R
GROUP BY R.Posao
HAVING COUNT(*) > 2;

--56
SELECT R.Posao, COUNT(*)
FROM Radnik AS R
WHERE R.Dodatak IS NOT NULL
GROUP BY R.Posao;

--57
SELECT R.Posao, COUNT(*)
FROM Radnik AS R
WHERE R.Dodatak IS NULL
GROUP BY R.Posao
HAVING COUNT(*) > 3;

--58
SELECT R.Posao,
AVG(R.Placa) 'Prosjecna placa',
MIN(R.Placa) 'Najmanja placa',
MAX(R.Placa) 'Najveca placa'
FROM Radnik AS R
GROUP BY R.Posao;

--59
SELECT R.Ime, R.Prezime, O.Naziv, O.Sjediste
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id;

--60
SELECT R.Ime, R.Prezime, O.Naziv
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id
WHERE O.Sjediste = 'Sarajevo';

--61
SELECT *
FROM Radnik AS R
WHERE R.Placa * 12 BETWEEN 10000 AND 20000;

--62
SELECT R.DatumU
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id
WHERE O.Naziv = 'Uprava' AND R.Id >= 5100 AND R.Placa < 1500;

--63
SELECT R.Ime, R.Prezime, R.Placa * 1.2, O.Naziv
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id
WHERE O.Naziv = 'Uprava'
ORDER BY R.Placa DESC;

--64
SELECT R.Ime, R.Prezime, R.Posao, R.Placa * 1.15, O.Naziv
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id
WHERE O.Naziv <> 'Uprava';

--65
SELECT R.Ime, R.Prezime, R.Placa
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id
WHERE R.Posao = 'Promotor' OR O.Naziv = 'Istraživanje';

--66
SELECT R.Ime, R.Prezime, R.Placa
FROM Radnik AS R INNER JOIN Odjel AS O ON R.IdOdjel = O.Id
WHERE R.Placa > 2000 AND O.Naziv = 'Uprava';

--67
SELECT DISTINCT R.Posao
FROM Radnik AS R;

--68
SELECT R.Ime, R.Posao, R.Placa * 12
FROM Radnik AS R
WHERE R.Placa * 12 < 18500
ORDER BY R.Placa DESC;

--69
SELECT R.Ime
FROM Radnik AS R
WHERE R.Placa > R.Dodatak * 3;

--70
SELECT R.Ime, R.DatumU
FROM Radnik AS R
WHERE R.Posao <> 'Menadžer';

--71
SELECT R.Id, R.IdOdjel, R.DatumU
FROM Radnik AS R
WHERE LEN(R.Posao) > 6 AND R.Placa > 2000
ORDER BY R.IdOdjel;

--72
SELECT R.Ime, R.Id, R.Placa
FROM Radnik AS R
WHERE R.Dodatak IS NULL AND R.Posao = 'Menadžer'
ORDER BY R.Placa;

--73
SELECT O.Naziv, O.Sjediste
FROM Odjel AS O INNER JOIN Radnik AS R ON O.Id = R.IdOdjel
INNER JOIN Ugovor AS U ON R.Id = U.IdRadnik
INNER JOIN Klijent AS K ON U.IdKlijent = K.Id
WHERE K.Grad = 'Banja Luka';