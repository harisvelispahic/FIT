-- Kreirati Relationships dijagram kojim æe se opisati dio baze podataka za produkcijsku kuæu. Produkcijska kuæa zapošljava 
--režisere/producente za koje je potrebno èuvati podatke identifikacijski broj, ime, prezime i broj liène karte. Filmovi koji 
--su opisani identifikacijskim brojem, nazivom, godinom izdavanja, i sadržajem može u sluèaju potrebe da režisira i više 
--režisera. Za filmove se angažuju glumci, gdje je za svakog glumca potrebno èuvati identifikacijski broj, ime, prezime, 
--spol, godine i fotografiju. Za svaki angažman glumca na filmu potrebno je èuvati podatak o ulozi koju igra. Produkcijska 
--kuæa takoðer suraðuje sa recenzentima koji iznose mišljenje/kritike o filmovima. Recenzent je opisan atributima 
--identifikacijski broj i naziv. Recenzenti svoje recenzije mogu ostaviti više puta u obliku pisanog teksta i ocjene, ali samo 
--jedanput za jedan film

CREATE DATABASE ProdukcijskaKuca
GO
USE ProdukcijskaKuca

CREATE TABLE Reziseri
(
	ReziserID INT CONSTRAINT PK_Reziser PRIMARY KEY IDENTITY(1,1),
	Ime NVARCHAR(20) NOT NULL,
	Prezime NVARCHAR(30) NOT NULL,
	Br_lk NVARCHAR(10) NOT NULL CONSTRAINT UQ_BrojLicne UNIQUE
)

CREATE TABLE Filmovi
(
	FilmID INT CONSTRAINT PK_Film PRIMARY KEY IDENTITY (1,1),
	Naziv NVARCHAR (50) NOT NULL,
	GodinaIzdavanja DATE,
	Sadrzaj NTEXT NOT NULL
)
CREATE TABLE Glumci
(
	GlumacID INT CONSTRAINT PK_Glumac PRIMARY KEY IDENTITY (1,1),
	Ime NVARCHAR(20) NOT NULL,
	Prezime NVARCHAR(30) NOT NULL,
	Spol CHAR(1),
	DatumRodjenja DATE,
	Fotografija VARBINARY(MAX)
)
CREATE TABLE Recezenti
(
	RecezentID INT CONSTRAINT PK_Recezent PRIMARY KEY IDENTITY(1,1),
	Naziv NVARCHAR(40) NOT NULL
)
CREATE TABLE FilmoviReziseri
(
	FilmID INT CONSTRAINT FK_FilmReziser_Film FOREIGN KEY REFERENCES Filmovi(FilmID),
	ReziserID INT CONSTRAINT FK_FilmReziser_Reziser FOREIGN KEY REFERENCES Reziseri(ReziserID),
	CONSTRAINT PK_FilmReziser PRIMARY KEY(FilmID, ReziserID)
)
CREATE TABLE FilmoviGlumci
(
	FilmID INT CONSTRAINT FK_FilmGlumac_Film FOREIGN KEY REFERENCES Filmovi(FilmID),
	GlumacID INT CONSTRAINT FK_FilmGlumac_Glumac FOREIGN KEY REFERENCES Glumci(GlumacID),
	Uloga NVARCHAR(30),
	CONSTRAINT PK_FilmGlumac PRIMARY KEY(FilmID, GlumacID, Uloga)
)
CREATE TABLE FilmoviRecezenti
(
	FilmID INT CONSTRAINT FK_FilmRecezent_Film FOREIGN KEY REFERENCES Filmovi(FilmID),
	RecezentID INT CONSTRAINT FK_FilmRecezent_Recezent FOREIGN KEY REFERENCES Recezenti(RecezentID),
	Ocjena INT CONSTRAINT CK_Ocjena CHECK (Ocjena BETWEEN 0 AND 10),
	Recenzija NVARCHAR(100)
	CONSTRAINT PK_FilmRecezent PRIMARY KEY(FilmID, RecezentID)
)

--Za probleme prilikom kreiranja dijagrama
EXEC sp_changedbowner 'sa'