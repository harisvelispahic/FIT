--1.	Kreirati bazu podataka pod nazivom ZadaciZaVjezbu. 
CREATE DATABASE ZadaciZaVjezbu
GO 
USE ZadaciZaVjezbu

--2.	U pomenutoj bazi kreirati tabelu Aplikanti koja æe sadržavati sljedeæe kolone: Ime, Prezime i Mjesto_roðenja. Sva navedena polja trebaju da budu tekstualnog tipa, te prilikom kreiranja istih paziti da se ne zauzimaju bespotrebno memorijski resursi.
CREATE TABLE Aplikanti
(
	Ime NVARCHAR(10),
	Prezime NVARCHAR(20),
	MjestoRodjenja NVARCHAR(50)
)

--3.	U tabelu Aplikanti dodati kolonu AplikantID, te je proglasiti primarnim kljuèem tabele (kolona mora biti autonkrement)
ALTER TABLE Aplikanti
ADD AplikantID INT NOT NULL IDENTITY(1,1)

ALTER TABLE Aplikanti
ADD CONSTRAINT PK_Aplikanti PRIMARY KEY(AplikantID)

--4.	U bazi ZadaciZaVjezbu kreirati tabelu Projekti koji æe sadržavati sljedeæe kolone: Naziv projekta, Akronim projekta, Svrha projekta i Cilj projekta. Sva polja u tabeli su tekstualnog tipa, te prilikom kreiranja istih paziti da se ne zauzimaju bespotrebno memorijski resursi. Sva navedena polja osim cilja projekta moraju imati vrijednost.
CREATE TABLE Projekti
(
	NazivProjekta NVARCHAR(30) NOT NULL,
	AkronimProjekta NVARCHAR(30) NOT NULL,
	SvrhaProjekta NVARCHAR(150) NOT NULL,
	CiljProjekta NVARCHAR(150)
)

--5.	U tabelu Projekti dodati kolonu Sifra projekta, te je proglasiti primarnim kljuèem tabele. 
ALTER TABLE Projekti
ADD SifraProjekta NVARCHAR(30) PRIMARY KEY --Obzirom da nije naveden tip podatka, ni INT ne bi bio pogrešan izbor

--6.	U tabelu Aplikanti dodati kolonu projekatID koje æe biti spoljni kljuè na tabelu projekat.
ALTER TABLE Aplikanti
ADD ProjekatID NVARCHAR(30) NOT NULL CONSTRAINT FK_Aplikanti_Projekti FOREIGN KEY REFERENCES Projekti(sifraProjekta)

--ILI

ALTER TABLE Aplikanti
ADD ProjekatID NVARCHAR(30) CONSTRAINT FK_Aplikanti_Projekti FOREIGN KEY REFERENCES Projekti(sifraProjekta)

--7.	U bazi podataka ZadaciZaVjezbu kreirati tabelu TematskeOblasti koja æe sadržavati sljedeæa polja tematskaOblastID, naziv i opseg. TematskaOblastID predstavlja primarni kljuè tabele, te se automatski uveæava. Sva definisana polja moraju imati vrijednost. Prilikom definisanja dužine polja potrebno je obratiti pažnju da se ne zauzimaju bespotrebno memorijski resursi.
CREATE TABLE TematskeOblasti
(
	TematskaOblastID INT CONSTRAINT PK_TematskeOblasti PRIMARY KEY IDENTITY(1,1),
	Naziv NVARCHAR(50) NOT NULL,
	Opseg NVARCHAR(150) NOT NULL
)
ALTER TABLE Projekti
ADD TematskaOblastID INT CONSTRAINT FK_Projekti_TematskeOblasti FOREIGN KEY REFERENCES TematskeOblasti(TematskaOblastID)

--8.	U tabeli Aplikanti dodati polje email koje je tekstualnog tipa i može ostati prazno, a u tabeli Projekti dodati polje cijena koja æe biti decimalnog tipa sa dvije cifre preciznosti iza decimalnog zareza.
ALTER TABLE Aplikanti
ADD Email NVARCHAR(50)

ALTER TABLE Projekti
ADD Cijena DECIMAL(18,2)

--9.	U tabele TematskeOblasti i Projekti dodati sljedeæe zapise. 
--Tematske oblasti [Naziv, Opseg]
--•	('Klimatske promjene i zaštita okoliša', 'Uzroci i posljedice globalnog zatopljenja'),
--•	('Umjetna inteligencija i tehnologija', 'Razvoj algoritama za strojno uèenje'),
--•	('Globalna ekonomija i trgovina', 'Trgovinski sporovi i carine')
INSERT INTO TematskeOblasti (Naziv, Opseg) --bitno je navesti svako polje koje mora imati vrijednost (oznaèeno NOT NULL) i PK ako nije autoinkrement (Identity) polje
VALUES ('Klimatske promjene i zaštita okoliša', 'Uzroci i posljedice globalnog zatopljenja'),
	('Umjetna inteligencija i tehnologija', 'Razvoj algoritama za strojno uèenje'),
	('Globalna ekonomija i trgovina', 'Trgovinski sporovi i carine')

--Projekti [Naziv, Akronim, Svrha, Cilj, Sifra, TematskaOblastID, Cijena]
--•	('Sunce', 'S', 'Zaštita od UV zraèenja', 'Zaštititi planetu', 'ABHC12', 2, 1500.99),
--•	('Mjesec', 'M', 'Apollo-12', 'Sletiti na mjesecc', 'MJSC911', 1, 15000050.99)
INSERT INTO Projekti (NazivProjekta, AkronimProjekta, SvrhaProjekta, CiljProjekta, SifraProjekta, TematskaOblastID, Cijena)
VALUES ('Sunce', 'S', 'Zaštita od UV zraèenja', 'Zaštititi planetu', 'ABHC12', 2, 1500.99),
	('Mjesec', 'M', 'Apollo-12', 'Sletiti na mjesecc', 'MJSC911', 1, 15000050.99)

--10.	Promjeniti tip podatka Cijena iz tablice Projekti u tekstualni tip podatka.
SELECT * FROM Projekti --provjera podataka prije promjene

ALTER TABLE Projekti
ALTER COLUMN Cijena NVARCHAR(20)

SELECT * FROM Projekti --vidimo da nakon promjene nemamo gubitka podataka

--11.	Prethodno promijenjeni tip podatka kolone Cijena pokušati pretvoriti u cjelobrojni tip podatka.
ALTER TABLE Projekti
ALTER COLUMN Cijena INT --direktna/implicitna pretvorba u int nije moguæa

ALTER TABLE Projekti
ALTER COLUMN Cijena DECIMAL(18,2)

ALTER TABLE Projekti
ALTER COLUMN Cijena INT --sa ova dva izraza smo uspjeli prebaciti kolonu u cjelobrojni tip, ali smo zbog toga trajno izgubili preciznost (cifre nakon decimale)

SELECT * FROM Projekti

--12.	DDL TRUNCATE izrazom izbrisati sve redove tablice Projketi.
ALTER TABLE Aplikanti --da bi mogli izbrisati sve podatke potrebno je izbrisati FK constraint tablica koje se referenciraju na tablicu Projekti
DROP CONSTRAINT FK_Aplikanti_Projekti

TRUNCATE TABLE Projekti
SELECT * FROM Projekti

--13.	DML DELETE izrazom izbirsati sve redove tablice TematskeOblasti.
DELETE FROM TematskeOblasti
--WHERE TematskaOblastID = 1 --sa DELETE imamo moguænost koristiti WHERE izraz ako želimo izbrisati samo odreðene redove
SELECT * FROM TematskeOblasti

--Osim WHERE izraza, koristeæi transakcije možemo vratiti podatke izbrisane DELETE izrazom u sluèaju kada smo izbrisali pogrešne podatke
/*
BEGIN TRANSACTION
DELETE FROM TematskeOblasti

SELECT * FROM TematskeOblasti

ROLLBACK

SELECT * FROM TematskeOblasti
*/

--14.	U tabeli Aplikanti obrisati mjesto roðenja i dodati polja telefon i matièni broj. Oba novokreirana polja su tekstualnog tipa i moraju sadržavati vrijednost.
ALTER TABLE Aplikanti
DROP COLUMN MjestoRodjenja

ALTER TABLE Aplikanti 
ADD Telefon NVARCHAR(10) NOT NULL,
	MaticniBroj NVARCHAR(13) NOT NULL 

--15.	Obrisati tabele kreirane u prethodnim zadacima. 
DROP TABLE TematskeOblasti, Aplikanti, Projekti

--16.	Obrisati kreiranu bazu.	
USE Northwind --moramo se prebaciti na neku drugu bazu kako bi izbrisali trenutnu
GO
DROP DATABASE ZadaciZaVjezbu
