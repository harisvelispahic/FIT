--1.	Kreirati bazu podataka pod nazivom ZadaciZaVjezbu. 
CREATE DATABASE ZadaciZaVjezbu
GO 
USE ZadaciZaVjezbu

--2.	U pomenutoj bazi kreirati tabelu Aplikanti koja �e sadr�avati sljede�e kolone: Ime, Prezime i Mjesto_ro�enja. Sva navedena polja trebaju da budu tekstualnog tipa, te prilikom kreiranja istih paziti da se ne zauzimaju bespotrebno memorijski resursi.
CREATE TABLE Aplikanti
(
	Ime NVARCHAR(10),
	Prezime NVARCHAR(20),
	MjestoRodjenja NVARCHAR(50)
)

--3.	U tabelu Aplikanti dodati kolonu AplikantID, te je proglasiti primarnim klju�em tabele (kolona mora biti autonkrement)
ALTER TABLE Aplikanti
ADD AplikantID INT NOT NULL IDENTITY(1,1)

ALTER TABLE Aplikanti
ADD CONSTRAINT PK_Aplikanti PRIMARY KEY(AplikantID)

--4.	U bazi ZadaciZaVjezbu kreirati tabelu Projekti koji �e sadr�avati sljede�e kolone: Naziv projekta, Akronim projekta, Svrha projekta i Cilj projekta. Sva polja u tabeli su tekstualnog tipa, te prilikom kreiranja istih paziti da se ne zauzimaju bespotrebno memorijski resursi. Sva navedena polja osim cilja projekta moraju imati vrijednost.
CREATE TABLE Projekti
(
	NazivProjekta NVARCHAR(30) NOT NULL,
	AkronimProjekta NVARCHAR(30) NOT NULL,
	SvrhaProjekta NVARCHAR(150) NOT NULL,
	CiljProjekta NVARCHAR(150)
)

--5.	U tabelu Projekti dodati kolonu Sifra projekta, te je proglasiti primarnim klju�em tabele. 
ALTER TABLE Projekti
ADD SifraProjekta NVARCHAR(30) PRIMARY KEY --Obzirom da nije naveden tip podatka, ni INT ne bi bio pogre�an izbor

--6.	U tabelu Aplikanti dodati kolonu projekatID koje �e biti spoljni klju� na tabelu projekat.
ALTER TABLE Aplikanti
ADD ProjekatID NVARCHAR(30) NOT NULL CONSTRAINT FK_Aplikanti_Projekti FOREIGN KEY REFERENCES Projekti(sifraProjekta)

--ILI

ALTER TABLE Aplikanti
ADD ProjekatID NVARCHAR(30) CONSTRAINT FK_Aplikanti_Projekti FOREIGN KEY REFERENCES Projekti(sifraProjekta)

--7.	U bazi podataka ZadaciZaVjezbu kreirati tabelu TematskeOblasti koja �e sadr�avati sljede�a polja tematskaOblastID, naziv i opseg. TematskaOblastID predstavlja primarni klju� tabele, te se automatski uve�ava. Sva definisana polja moraju imati vrijednost. Prilikom definisanja du�ine polja potrebno je obratiti pa�nju da se ne zauzimaju bespotrebno memorijski resursi.
CREATE TABLE TematskeOblasti
(
	TematskaOblastID INT CONSTRAINT PK_TematskeOblasti PRIMARY KEY IDENTITY(1,1),
	Naziv NVARCHAR(50) NOT NULL,
	Opseg NVARCHAR(150) NOT NULL
)
ALTER TABLE Projekti
ADD TematskaOblastID INT CONSTRAINT FK_Projekti_TematskeOblasti FOREIGN KEY REFERENCES TematskeOblasti(TematskaOblastID)

--8.	U tabeli Aplikanti dodati polje email koje je tekstualnog tipa i mo�e ostati prazno, a u tabeli Projekti dodati polje cijena koja �e biti decimalnog tipa sa dvije cifre preciznosti iza decimalnog zareza.
ALTER TABLE Aplikanti
ADD Email NVARCHAR(50)

ALTER TABLE Projekti
ADD Cijena DECIMAL(18,2)

--9.	U tabele TematskeOblasti i Projekti dodati sljede�e zapise. 
--Tematske oblasti [Naziv, Opseg]
--�	('Klimatske promjene i za�tita okoli�a', 'Uzroci i posljedice globalnog zatopljenja'),
--�	('Umjetna inteligencija i tehnologija', 'Razvoj algoritama za strojno u�enje'),
--�	('Globalna ekonomija i trgovina', 'Trgovinski sporovi i carine')
INSERT INTO TematskeOblasti (Naziv, Opseg) --bitno je navesti svako polje koje mora imati vrijednost (ozna�eno NOT NULL) i PK ako nije autoinkrement (Identity) polje
VALUES ('Klimatske promjene i za�tita okoli�a', 'Uzroci i posljedice globalnog zatopljenja'),
	('Umjetna inteligencija i tehnologija', 'Razvoj algoritama za strojno u�enje'),
	('Globalna ekonomija i trgovina', 'Trgovinski sporovi i carine')

--Projekti [Naziv, Akronim, Svrha, Cilj, Sifra, TematskaOblastID, Cijena]
--�	('Sunce', 'S', 'Za�tita od UV zra�enja', 'Za�tititi planetu', 'ABHC12', 2, 1500.99),
--�	('Mjesec', 'M', 'Apollo-12', 'Sletiti na mjesecc', 'MJSC911', 1, 15000050.99)
INSERT INTO Projekti (NazivProjekta, AkronimProjekta, SvrhaProjekta, CiljProjekta, SifraProjekta, TematskaOblastID, Cijena)
VALUES ('Sunce', 'S', 'Za�tita od UV zra�enja', 'Za�tititi planetu', 'ABHC12', 2, 1500.99),
	('Mjesec', 'M', 'Apollo-12', 'Sletiti na mjesecc', 'MJSC911', 1, 15000050.99)

--10.	Promjeniti tip podatka Cijena iz tablice Projekti u tekstualni tip podatka.
SELECT * FROM Projekti --provjera podataka prije promjene

ALTER TABLE Projekti
ALTER COLUMN Cijena NVARCHAR(20)

SELECT * FROM Projekti --vidimo da nakon promjene nemamo gubitka podataka

--11.	Prethodno promijenjeni tip podatka kolone Cijena poku�ati pretvoriti u cjelobrojni tip podatka.
ALTER TABLE Projekti
ALTER COLUMN Cijena INT --direktna/implicitna pretvorba u int nije mogu�a

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
--WHERE TematskaOblastID = 1 --sa DELETE imamo mogu�nost koristiti WHERE izraz ako �elimo izbrisati samo odre�ene redove
SELECT * FROM TematskeOblasti

--Osim WHERE izraza, koriste�i transakcije mo�emo vratiti podatke izbrisane DELETE izrazom u slu�aju kada smo izbrisali pogre�ne podatke
/*
BEGIN TRANSACTION
DELETE FROM TematskeOblasti

SELECT * FROM TematskeOblasti

ROLLBACK

SELECT * FROM TematskeOblasti
*/

--14.	U tabeli Aplikanti obrisati mjesto ro�enja i dodati polja telefon i mati�ni broj. Oba novokreirana polja su tekstualnog tipa i moraju sadr�avati vrijednost.
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
