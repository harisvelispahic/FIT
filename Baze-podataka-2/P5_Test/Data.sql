USE master;

DROP DATABASE IF EXISTS Test;
CREATE DATABASE Test
GO
USE Test;

CREATE TABLE drzave(
	sifra INT IDENTITY(1, 1) CONSTRAINT PK_drzave PRIMARY KEY,
	naziv VARCHAR(50) NOT NULL,
	kratki_naziv VARCHAR(10) NOT NULL,
);

CREATE TABLE fakulteti(
	sifra INT IDENTITY(1, 1) CONSTRAINT PK_fakulteti PRIMARY KEY,
	naziv VARCHAR(50) NOT NULL,
	adresa VARCHAR(50) NOT NULL,
);

CREATE TABLE tipovi_projekata(
	sifra INT IDENTITY(1, 1) CONSTRAINT PK_tipovi_projekata PRIMARY KEY,
	naziv VARCHAR(50) NOT NULL,
);

CREATE TABLE donatori(
	sifra INT IDENTITY(1, 1) CONSTRAINT PK_donatori PRIMARY KEY,
	naziv VARCHAR(50) NOT NULL,
	sjediste VARCHAR(50) NOT NULL,
	id_drzava INT NOT NULL CONSTRAINT FK_donatori_drzave FOREIGN KEY REFERENCES drzave(sifra),
);

CREATE TABLE profesori(
	sifra INT IDENTITY(1, 1) CONSTRAINT PK_profesori PRIMARY KEY,
	ime VARCHAR(30) NOT NULL,
	prezime VARCHAR(30) NOT NULL,
	titula VARCHAR(20) NOT NULL,
	funkcija VARCHAR(50) NOT NULL,
	id_fakultet INT NOT NULL CONSTRAINT FK_profesori_fakulteti FOREIGN KEY REFERENCES fakulteti(sifra),
);

CREATE TABLE projekti(
	sifra INT IDENTITY(1, 1) CONSTRAINT PK_projekti PRIMARY KEY,
	naziv VARCHAR(50) NOT NULL,
	datum_pocetka DATE NOT NULL,
	datum_svrsetka DATE NOT NULL,
	vrijednost NUMERIC(20, 2) NOT NULL,
	id_tip INT NOT NULL CONSTRAINT FK_projekti_tipovi_projekata FOREIGN KEY REFERENCES tipovi_projekata(sifra),
	id_donator INT NOT NULL CONSTRAINT FK_projekti_donatori FOREIGN KEY REFERENCES donatori(sifra),
	id_voditelj INT NOT NULL CONSTRAINT FK_projekti_profesori FOREIGN KEY REFERENCES profesori(sifra),
);

CREATE TABLE projekti_ucesnici(
	id_projekt INT NOT NULL CONSTRAINT FK_projekti_ucesnici_projekti FOREIGN KEY REFERENCES projekti(sifra),
	id_profesor INT NOT NULL CONSTRAINT FK_projekti_ucesnici_profesori FOREIGN KEY REFERENCES profesori(sifra),
	CONSTRAINT PK_projekti_ucesnici PRIMARY KEY(id_projekt, id_profesor)
);

-- Inserts below were generated using ChatGPT

INSERT INTO drzave (naziv, kratki_naziv) 
VALUES 
('Sjedinjene Američke Države', 'SAD'),
('Kanada', 'CAN'),
('Njemačka', 'DEU'),
('Francuska', 'FRA'),
('Italija', 'ITA'),
('Velika Britanija', 'GBR'),
('Australija', 'AUS'),
('Japan', 'JPN'),
('Indija', 'IND'),
('Brazil', 'BRA');

INSERT INTO fakulteti (naziv, adresa) 
VALUES 
('Fakultet računarstva', 'Sarajevo, BiH'),
('Fakultet elektrotehnike', 'Beograd, Srbija'),
('Fakultet inženjeringa', 'Zagreb, Hrvatska'),
('Fakultet umjetnosti', 'Podgorica, Crna Gora'),
('Fakultet građevine', 'Ljubljana, Slovenija'),
('Fakultet ekonomije', 'Sarajevo, BiH'),
('Fakultet prava', 'Beograd, Srbija'),
('Fakultet medicine', 'Zagreb, Hrvatska'),
('Fakultet biologije', 'Podgorica, Crna Gora'),
('Fakultet političkih nauka', 'Belgrade, Serbia');

INSERT INTO tipovi_projekata (naziv) 
VALUES 
('Istraživački'),
('Razvojni'),
('Edukativni'),
('Obrazovni'),
('Komercijalni'),
('Kreativni'),
('Tehnički'),
('Sociološki'),
('Ekološki'),
('Zdravstveni');

INSERT INTO donatori (naziv, sjediste, id_drzava) 
VALUES 
('UNDP', 'New York, USA', 1),
('EU', 'Brussels, Belgium', 3),
('USAID', 'Washington, USA', 1),
('WB', 'Washington, USA', 1),
('GIZ', 'Berlin, Germany', 2),
('DFID', 'London, UK', 6),
('JICA', 'Tokyo, Japan', 7),
('SIDA', 'Stockholm, Sweden', 8),
('CIDA', 'Ottawa, Canada', 2),
('AUSAID', 'Canberra, Australia', 6);

INSERT INTO profesori (ime, prezime, titula, funkcija, id_fakultet) 
VALUES 
('Marko', 'Marković', 'Dr', 'Profesor', 1),
('Ivana', 'Ivić', 'Dr', 'Docent', 2),
('Jovana', 'Jovanović', 'Dr', 'Asistent', 3),
('Nikola', 'Nikolić', 'Prof', 'Profesor', 4),
('Aleksandra', 'Aleksić', 'Dr', 'Profesor', 5),
('Luka', 'Lukić', 'Dr', 'Docent', 6),
('Marija', 'Marić', 'Dr', 'Profesor', 7),
('Petar', 'Petrović', 'Dr', 'Asistent', 8),
('Ana', 'Anić', 'Prof', 'Docent', 9),
('Maja', 'Majkić', 'Dr', 'Asistent', 10);

INSERT INTO projekti (naziv, datum_pocetka, datum_svrsetka, vrijednost, id_tip, id_donator, id_voditelj) 
VALUES 
('Projekt A', '2025-01-01', '2025-12-31', 50000.00, 1, 1, 1),
('Projekt B', '2025-03-01', '2025-11-30', 150000.00, 2, 2, 2),
('Projekt C', '2025-04-01', '2026-04-01', 75000.00, 3, 3, 3),
('Projekt D', '2025-05-01', '2025-12-01', 200000.00, 4, 4, 4),
('Projekt E', '2025-06-01', '2025-11-01', 100000.00, 5, 5, 5),
('Projekt F', '2025-07-01', '2026-01-01', 125000.00, 6, 6, 6),
('Projekt G', '2025-08-01', '2025-10-31', 50000.00, 7, 7, 7),
('Projekt H', '2025-09-01', '2026-06-30', 60000.00, 8, 8, 8),
('Projekt I', '2025-10-01', '2025-12-31', 80000.00, 9, 9, 9),
('Projekt J', '2025-11-01', '2026-05-31', 95000.00, 10, 10, 10);

INSERT INTO projekti_ucesnici (id_projekt, id_profesor) 
VALUES 
(1, 1),
(1, 2),
(2, 3),
(3, 4),
(4, 5),
(5, 6),
(6, 7),
(7, 8),
(8, 9),
(9, 10);
