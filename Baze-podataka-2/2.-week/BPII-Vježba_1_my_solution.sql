-- 1. Kreirati bazu podataka pod nazivom ZadaciZaVjezbu.
CREATE DATABASE ZadaciZaVjezbu;
GO
USE ZadaciZaVjezbu;
-- 2. U pomenutoj bazi kreirati tabelu Aplikanti koja će sadržavati sljedeće kolone: Ime, Prezime i Mjesto_rođenja. Sva navedena polja trebaju da budu tekstualnog tipa, te prilikom kreiranja istih paziti da se ne zauzimaju bespotrebno memorijski resursi.

CREATE TABLE Aplikanti
(
	Ime NVARCHAR(50),
	Prezime NVARCHAR(50),
	Mjesto_rodjenja NVARCHAR(80)
);
-- 3. U tabelu Aplikanti dodati kolonu AplikantID, te je proglasiti primarnim ključem tabele (kolona mora biti autoinkrement)

ALTER TABLE Aplikanti
ADD AplikantID INT CONSTRAINT PK_Aplikanti PRIMARY KEY IDENTITY(1,1);

-- 4. U bazi ZadaciZaVjezbu kreirati tabelu Projekti koji će sadržavati sljedeće kolone: Naziv projekta, Akronim projekta, Svrha projekta i Cilj projekta. Sva polja u tabeli su tekstualnog tipa, te prilikom kreiranja istih paziti da se ne zauzimaju bespotrebno memorijski resursi. Sva navedena polja osim cilja projekta moraju imati vrijednost.

CREATE TABLE Projekti
(
	Naziv NVARCHAR(50) NOT NULL,
	Akronim NVARCHAR(10) NOT NULL,
	Svrha NVARCHAR(100) NOT NULL,
	Cilj NVARCHAR(100)
);

-- 5. U tabelu Projekti dodati kolonu Sifra projekta, te je proglasiti primarnim ključem tabele. 

ALTER TABLE Projekti
ADD SifraProjekta NVARCHAR(10) CONSTRAINT PK_Projekti PRIMARY KEY;

-- 6. U tabelu Aplikanti dodati kolonu projekatID koje će biti spoljni ključ na tabelu projekat.

ALTER TABLE Aplikanti
ADD ProjektID NVARCHAR(10) NOT NULL CONSTRAINT FK_Aplikanti_Projekti FOREIGN KEY REFERENCES Projekti(SifraProjekta);

-- 7. U bazi podataka ZadaciZaVjezbu kreirati tabelu TematskeOblasti koja će sadržavati sljedeća polja tematskaOblastID, naziv i opseg. TematskaOblastID predstavlja primarni ključ tabele,te se automatski uvećava. Sva definisana polja moraju imati vrijednost. Prilikom definisanja dužine polja potrebno je obratiti pažnju da se ne zauzimaju bespotrebno memorijski resursi. Projekti pripadaju jednoj tematskoj oblasti.

CREATE TABLE TematskeOblasti
(
	TematskaOblastID INT CONSTRAINT PK_TematskeOblasti PRIMARY KEY IDENTITY(1,1),
	Naziv NVARCHAR(50) NOT NULL,
	Opseg NVARCHAR(100) NOT NULL
);

ALTER TABLE Projekti
ADD TematskaOblastID INT CONSTRAINT FK_Projekti_TematskeOblasti FOREIGN KEY REFERENCES TematskeOblasti(TematskaOblastID);

-- 8. U tabeli Aplikanti dodati polje email koje je tekstualnog tipa i može ostati prazno, a u tabeli Projekti dodati polje cijena koja će biti decimalnog tipa sa dvije cifre preciznosti iza decimalnog zareza.

ALTER TABLE Aplikanti
ADD Email NVARCHAR(100);

ALTER TABLE Projekti
ADD Cijena DECIMAL(18,2);
-- DECIMAL TIPU NAGLAŠAVAMO KOLIKO ĆE CIFARA IMATI IZA ZAREZA, 18 PRIJE I 2 POSLIJE ZAREZA

-- 9. U tabele TematskeOblasti i Projekti dodati sljedeće zapise. 
--Tematske oblasti [Naziv, Opseg]
--• ('Klimatske promjene i zaštita okoliša', 'Uzroci i posljedice globalnog zatopljenja'),
--• ('Umjetna inteligencija i tehnologija', 'Razvoj algoritama za strojno učenje'),
--• ('Globalna ekonomija i trgovina', 'Trgovinski sporovi i carine')

INSERT INTO TematskeOblasti (Naziv, Opseg)
VALUES ('Klimatske promjene i zaštita okoliša', 'Uzroci i posljedice globalnog zatopljenja'),
('Umjetna inteligencija i tehnologija', 'Razvoj algoritama za strojno učenje'),
('Globalna ekonomija i trgovina', 'Trgovinski sporovi i carine');

--Projekti [Naziv, Akronim, Svrha, Cilj, Sifra, TematskaOblastID, Cijena]
--• ('Sunce', 'S', 'Zaštita od UV zračenja', 'Zaštititi planetu', 'ABHC12', 2, 1500.99),
--• ('Mjesec', 'M', 'Apollo-12', 'Sletiti na mjesecc', 'MJSC911', 1, 15000050.99)

INSERT INTO Projekti (Naziv, Akronim, Svrha, Cilj, SifraProjekta, TematskaOblastID, Cijena)
VALUES ('Sunce', 'S', 'Zaštita od UV zračenja', 'Zaštititi planetu', 'ABHC12', 2, 1500.99),
('Mjesec', 'M', 'Apollo-12', 'Sletiti na mjesecc', 'MJSC911', 1, 15000050.99);

-- 10. Promjeniti tip podatka kolone Cijena iz tablice Projekti u tekstualni tip podatka.

ALTER TABLE Projekti
ALTER COLUMN Cijena NVARCHAR(18);

-- 11. Prethodno promijenjeni tip podatka kolone Cijena pokušati pretvoriti u cjelobrojni tip podatka.

ALTER TABLE Projekti
ALTER COLUMN Cijena INT;

-- 12. DDL izrazom izbrisati sve redove tablice TematskeOblasti.

ALTER TABLE Projekti
DROP CONSTRAINT FK_Projekti_TematskeOblasti;

TRUNCATE TABLE TematskeOblasti;

SELECT * FROM TematskeOblasti;

-- 13. DML izrazom izbirsati sve redove tablice Projketi.

DELETE FROM Projekti;

-- RAZLIKA IZMEĐU 12. I 13. -> 
-- 12 - DLL UPIT JE DOSTA BRŽI
-- 13 - MOŽEMO URADITI ROLLBACK, VRATITI PODATKE, 13 TAKOĐER IMA TRIGGERE


-- 14. U tabeli Aplikanti obrisati mjesto rođenja i dodati polja telefon i matični broj. Oba novokreirana polja su tekstualnog tipa i moraju sadržavati vrijednost.

ALTER TABLE Aplikanti
DROP COLUMN Mjesto_rodjenja;

ALTER TABLE Aplikanti
ADD Telefon NVARCHAR(13) NOT NULL,
	JMBG NVARCHAR(13) NOT NULL;

-- 15. Obrisati tabele kreirane u prethodnim zadacima.

DROP TABLE Aplikanti, Projekti, TematskeOblasti;

-- 16. Obrisati kreiranu bazu.

--USE master;
DROP DATABASE ZadaciZaVjezbu;