CREATE DATABASE Vjezbe0
GO
USE Vjezbe0

CREATE TABLE Odjel (
    Id INT PRIMARY KEY,
    Naziv VARCHAR(255),
    Sjediste VARCHAR(255),
    Telefon VARCHAR(20)
);

CREATE TABLE Stupanj (
    Rang INT PRIMARY KEY,
    [Min] INT,
    [Max] INT
);

CREATE TABLE Klijent (
    Id INT PRIMARY KEY,
    Naziv VARCHAR(255),
    Adresa VARCHAR(255),
    Grad VARCHAR(255),
    Telefon VARCHAR(20),
    Fax VARCHAR(20)
);

CREATE TABLE Radnik (
    Id INT PRIMARY KEY,
    Ime VARCHAR(255),
    Prezime VARCHAR(255),
    Adresa VARCHAR(255),
    DatumU DATE,
    Posao VARCHAR(255),
    Placa INT,
    IdManager INT,
    Dodatak DECIMAL(10,1),
    IdOdjel INT,
    FOREIGN KEY (IdManager) REFERENCES Radnik(Id),
    FOREIGN KEY (IdOdjel) REFERENCES Odjel(Id)
);

CREATE TABLE Ugovor (
    Id INT PRIMARY KEY,
    Datum DATE,
    Mjesto VARCHAR(255),
    Iznos DECIMAL(15,2),
    IdRadnik INT,
    IdKlijent INT,
    FOREIGN KEY (IdRadnik) REFERENCES Radnik(Id),
    FOREIGN KEY (IdKlijent) REFERENCES Klijent(Id)
);

-- Populate Tables
INSERT INTO Odjel (Id, Naziv, Sjediste, Telefon) VALUES
(10, 'Raèunovodstvo', 'Mostar', '345234'),
(20, 'Istraživanje', 'Sarajevo', '734990'),
(30, 'Prodaja', 'Tuzla', '311324'),
(40, 'Marketing', 'Banja Luka', '678456'),
(50, 'Uprava', 'Mostar', '355246'),
(60, 'Management', 'Sarajevo', '768443'),
(70, 'Kadrovska', 'Mostar', '380468');

INSERT INTO Stupanj (Rang, [Min], [Max]) VALUES
(1, 2001, 6000),
(2, 1501, 2000),
(3, 1001, 1500),
(4, 801, 1000),
(5, 501, 800),
(6, 0, 500);

INSERT INTO Klijent (Id, Naziv, Adresa, Grad, Telefon, Fax) VALUES
(201, 'Adria Group', 'Mostarska 98', 'Sarajevo', '365987', '669359'),
(202, 'Weltplast', 'Tuzlanska 56', 'Sarajevo', '333253', '695836'),
(203, 'Agro Tours', 'Zagrebaèka 12', 'Mostar', '454695', '256287'),
(204, 'Kosmo Promet', 'Dubrovaèka 69', 'Mostar', '565893', '369546'),
(205, 'Mobil Media', 'Splitska 6', 'Sarajevo', '336598', '245365'),
(206, 'Intertrans', 'Avenija 235', 'Banja Luka', '557869', '284569'),
(207, 'TransTour', 'Splitska 25/A', 'Banja Luka', '659658', '336545'),
(208, 'Balkan Promet', 'Mostarska 65', 'Tuzla', '635674', '558468'),
(209, 'XYZ Group', 'Avenija 1263z', 'Zenica', '5698563', '5552369'),
(210, 'XTours', 'Mostarska 12', 'Doboj', '245369', '458752');

-- Populate Radnik (all 20 records)
INSERT INTO Radnik (Id, Ime, Prezime, Adresa, DatumU, Posao, Placa, IdManager, Dodatak, IdOdjel) VALUES
(101, 'Boris', 'Antiæ', 'Zagrebaèka 12', '2000-10-12', 'Raèunovoða', 900, 102, 200.0, 10),
(102, 'Boris', 'Peric', 'Treæa ulica 156', '2000-08-08', 'Revizor', 1500, NULL, NULL, 10),
(103, 'Marko', 'Peric', 'Splitska 15', '1999-01-12', 'Tajnik', 1400, 106, 50.0, 60),
(104, 'Ivan', 'Tomic', 'Splitska 114a', '1998-11-12', 'Promotor', 1600, 105, 64.0, 40),
(105, 'Edo', 'Iviæ', 'Dubrovaèka 5', '1995-01-04', 'Kontrolor', 2300, NULL, NULL, 60),
(106, 'Marija', 'Simic', 'Treæa ulica 54', '1995-01-04', 'Kontrolor', 2300, NULL, NULL, 60),
(107, 'Majda', 'Babic', 'Dubrovaèka 23', '1998-07-29', 'Istraživaè', 2300, 106, 312.3, 20),
(108, 'Marino', 'Babic', 'Avenija 23', '1998-07-29', 'Prodavaè', 2300, 105, 118.9, 30),
(109, 'Sanja', 'Matic', 'Avenija 698', '1998-07-29', 'Prodavaè', 853, 105, 332.0, 30),
(110, 'Ema', 'Maslac', 'Avenija 12b', '2001-04-13', 'Prodavaè', 987, 105, 118.0, 30),
(111, 'Slavica', 'Mamiæ', 'Treæa ulica 1', '2002-05-13', 'Analitièar', 1002, 106, 10.0, 20),
(112, 'Vanja', 'Maslo', 'Avenija 157', '2003-06-25', 'Menadžer', 5400, NULL, NULL, 50),
(113, 'Stanko', 'Perko', 'Vukovarska 25a', '2004-06-11', 'Menadžer', 5200, NULL, NULL, 50),
(114, 'Tanja', 'Petric', 'Sarajevska 25a', '1999-06-11', 'Menadžer', 5500, NULL, NULL, 50),
(115, 'Mia', 'Bošnjak', 'Sarajevska 115', '2000-03-18', 'Menadžer', 5400, NULL, NULL, 50),
(116, 'Slavo', 'Mariæ', 'Tuzlanska 17', '2000-10-21', 'Promotor', 2200, 112, 12.0, 40),
(117, 'Maja', 'Ribiæ', 'Tuzlanska 19', '2003-10-19', 'Promotor', 1300, 112, 113.0, 40),
(118, 'Anja', 'Jovic', 'Avenija 66', '2004-01-09', 'Marketar', 1100, 113, 223.0, 40),
(119, 'Marko', 'Petkoviæ', 'Sarajevska 12', '1997-03-11', 'Analitièar', 2100, 114, 11.0, 20),
(120, 'Marina', 'Bebiæ', 'Sarajevska 369', '1998-04-11', 'Tajnik', 1800, 115, 200.0, 50);

-- Populate Ugovor (all 22 records)
INSERT INTO Ugovor (Id, Datum, Mjesto, Iznos, IdRadnik, IdKlijent) VALUES
(301, '2002-01-15', 'Zenica', 1200200.00, 101, 204),
(302, '2000-03-16', 'Mostar', 163159.00, 110, 205),
(303, '1999-10-19', 'Mostar', 698622.00, 112, 204),
(304, '1998-12-15', 'Visoko', 5698320.00, 115, 204),
(305, '2001-04-13', 'Sarajevo', 3365263.00, 114, 204),
(306, '2002-08-13', 'Travnik', 1111230.00, 116, 203),
(307, '2003-09-25', 'Travnik', 525363.00, 110, 202),
(308, '2004-03-11', 'Sarajevo', 8889253.00, 102, 201),
(309, '2003-11-19', 'Sarajevo', 887936.50, 102, 202),
(310, '2004-10-09', 'Mostar', 156148.00, 102, 203),
(311, '1997-03-18', 'Mostar', 256398.00, 103, 205),
(312, '1998-04-16', 'Visoko', 669255.00, 105, 205),
(313, '2003-09-09', 'Banja Luka', 1453652.00, 106, 207),
(314, '2005-03-01', 'Banja Luka', 758458.00, 108, 201),
(315, '2003-11-10', 'Banja Luka', 798798.00, 105, 210),
(316, '2006-10-03', 'Sarajevo', 458475.00, 106, 201),
(317, '2006-03-18', 'Mostar', 448758.00, 108, 202),
(318, '2003-04-16', 'Zenica', 755869.00, 116, 208),
(319, '2004-04-14', 'Banja Luka', 7777585.00, 119, 203),
(320, '2005-12-23', 'Sarajevo', 797985.00, 117, 207),
(321, '2024-12-12', 'Zenica', 7669000.53, 110, 210),
(322, '2023-09-03', 'Visoko', 421635.50, 111, 204);