USE Test;

-- 1. Prikazati ukupan broj profesora koji su učestvovali na projektima tipa 'Razvojni'

SELECT COUNT(*)
FROM profesori AS PROF INNER JOIN projekti_ucesnici AS PROJ_UCES ON PROF.sifra = PROJ_UCES.id_profesor
INNER JOIN projekti AS PROJ ON PROJ_UCES.id_projekt = PROJ.sifra
INNER JOIN tipovi_projekata AS TIP_PROJ ON PROJ.id_tip = TIP_PROJ.sifra
WHERE TIP_PROJ.naziv = 'Razvojni';

-- 2. Prikazati sve donatore (šifra, naziv i broj učesnika) na čijim je projektima učestvovalo više od 5 profesora.

SELECT D.sifra, D.naziv, COUNT(*) Broj_ucesnika
FROM donatori AS D INNER JOIN projekti PROJ ON D.sifra = PROJ.id_donator
INNER JOIN projekti_ucesnici AS PROJ_UCES ON PROJ.sifra = PROJ_UCES.id_projekt
GROUP BY D.sifra, D.naziv
HAVING COUNT(*) > 5;

-- 3. Prikazati fakultete (šifra, naziv i broj voditelja) koji su imali više od 3 voditelja na projektima vrijednosti veće od 800000.

SELECT F.sifra, F.naziv, COUNT(*)
FROM fakulteti AS F INNER JOIN profesori AS PROF ON F.sifra = PROF.id_fakultet
INNER JOIN projekti AS PROJ ON PROF.sifra = PROJ.id_voditelj
WHERE PROJ.vrijednost > 800000
GROUP BY F.sifra, F.naziv
HAVING COUNT(*) > 3;

-- 4. Prikazati države (šifra, naziv, broj projekata) koje su imale više od 2 projekta vrijednosti veće od 1000000.
SELECT DR.sifra, DR.naziv, COUNT(*) broj_projekata
FROM drzave AS DR INNER JOIN donatori DO ON DR.sifra = DO.id_drzava
INNER JOIN projekti PROJ ON PROJ.id_donator = DO.sifra
WHERE PROJ.vrijednost > 1000000
GROUP BY DR.sifra, DR.naziv
HAVING COUNT(*) > 2;

-- 5. Prikazati tipove projekata (šifra, naziv, UkupnaVrijedProj) čija je ukupna vrijednost projekata bila veća od 3000000.

SELECT TIP_PROJ.sifra, TIP_PROJ.naziv, SUM(PROJ.vrijednost) ukupna_vrijednost
FROM tipovi_projekata TIP_PROJ INNER JOIN projekti PROJ ON TIP_PROJ.sifra = PROJ.id_tip
GROUP BY TIP_PROJ.sifra, TIP_PROJ.naziv
HAVING SUM(PROJ.vrijednost) > 3000000;

--  6. Prikazati profesore (ime, prezime, naziv fakulteta, brojProjVodili) koji su bili voditelji projekta na više od 2 projekta.

SELECT PROF.ime, PROF.prezime, F.naziv, COUNT(*) brojProjVoditelja
FROM profesori AS PROF INNER JOIN projekti AS PROJ ON PROF.sifra = PROJ.id_voditelj
INNER JOIN fakulteti F ON PROF.id_fakultet = F.sifra
GROUP BY PROF.ime, PROF.prezime, F.naziv
HAVING COUNT(*) > 2;

-- 7. Prikazati fakultete (sifra, naziv) čiji profesori nisu vodili niti jedan projekt.

SELECT F.sifra, F.naziv, PROJ.sifra
FROM fakulteti AS F INNER JOIN profesori AS PROF ON F.sifra = PROF.id_fakultet
LEFT JOIN projekti AS PROJ ON PROF.sifra = PROJ.id_voditelj
WHERE PROJ.sifra IS NULL;

-- 8. Prikazati po fakultetima (sifra, naziv, broj profesora) broj profesora koji nisu vodili niti jedan projekt.

SELECT F.sifra, F.naziv, COUNT(*) broj_profesora
FROM fakulteti AS F INNER JOIN profesori AS PROF ON F.sifra = PROF.id_fakultet
LEFT JOIN projekti AS PROJ ON PROF.sifra = PROJ.id_voditelj
WHERE PROJ.sifra IS NULL
GROUP BY F.sifra, F.naziv;

-- 9. Prikazati profesore (sifra, ime, prezime, titula, funkcija) koji nisu vodili niti jedan projekt.

SELECT PROF.sifra, PROF.ime, PROF.prezime, PROF.titula, PROF.funkcija
FROM profesori AS PROF LEFT JOIN projekti AS PROJ ON PROF.sifra = PROJ.id_voditelj
WHERE PROJ.sifra IS NULL;

-- 10. Prikazati profesore (sifra, ime, prezime, titula, funkcija) koji nisu učestvovali niti u jednom projektu.

SELECT PROF.sifra, PROF.ime, PROF.prezime, PROF.titula, PROF.funkcija
FROM profesori AS PROF LEFT JOIN projekti_ucesnici AS PROJ_UCES ON PROF.sifra = PROJ_UCES.id_profesor
WHERE PROJ_UCES.id_profesor IS NULL;