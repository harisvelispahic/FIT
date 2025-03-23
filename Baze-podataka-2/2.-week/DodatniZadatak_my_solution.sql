--Kreirati Relationships dijagram kojim će se opisati dio baze podataka za produkcijsku kuću. 
--Produkcijska kuća zapošljava režisere/producente za koje je potrebno čuvati podatke 
--identifikacijski broj, ime, prezime i broj lične karte. Filmovi koji su opisani identifikacijskim 
--brojem, nazivom, godinom izdavanja, i sadržajem može u slučaju potrebe da režisira i više 
--režisera. Za filmove se angažuju glumci, gdje je za svakog glumca potrebno čuvati 
--identifikacijski broj, ime, prezime, spol, godine i fotografiju. Za svaki angažman glumca na filmu 
--potrebno je čuvati podatak o ulozi koju igra. Produkcijska kuća također surađuje sa 
--recenzentima koji iznose mišljenje/kritike o filmovima. Recenzent je opisan atributima 
--identifikacijski broj i naziv. Recenzenti svoje recenzije mogu ostaviti više puta u obliku pisanog 
--teksta i ocjene, ali samo jedanput za jedan film. Pri izradi relationship dijagrama nije 
--dozvoljeno uvođenje bilo kakvih novih atributa. 

CREATE DATABASE Vjezbe1_dodatni_zadatak;
GO;
USE Vjezbe1_dodatni_zadatak;

CREATE TABLE Producent
(
	ID INT CONSTRAINT PK_Producent PRIMARY KEY IDENTITY(1,1),
	Ime NVARCHAR(50),
	Prezime NVARCHAR(50),
	Broj_licne_karte VARCHAR(10)
);

CREATE TABLE Film
(
	ID INT CONSTRAINT PK_Film PRIMARY KEY IDENTITY(1,1),
	Naziv NVARCHAR(50),
	Godina_izdavanja INT,
	Sadrzaj NVARCHAR(200)
);

CREATE TABLE Glumac
(
	ID INT CONSTRAINT PK_Glumac PRIMARY KEY IDENTITY(1,1),
	Ime NVARCHAR(50),
	Prezime NVARCHAR(50),
	Spol BIT,
	Godine INT,
	Fotografija VARBINARY(MAX)
);

CREATE TABLE Recenzent
(
	ID INT CONSTRAINT PK_Recenzent PRIMARY KEY IDENTITY(1,1),
	Naziv NVARCHAR(50)
);

CREATE TABLE ProducentFilm
(
	ProducentID INT CONSTRAINT FK_ProducentFilm_Producent FOREIGN KEY REFERENCES Producent(ID),
	FilmID INT CONSTRAINT FK_ProducentFilm_Film FOREIGN KEY REFERENCES Film(ID),
	CONSTRAINT PK_ProducentFilm PRIMARY KEY (ProducentID, FilmID)
);

CREATE TABLE FilmGlumac
(
	FilmID INT CONSTRAINT FK_FilmGlumac_Film FOREIGN KEY REFERENCES Film(ID),
	GlumacID INT CONSTRAINT FK_FilmGlumac_Glumac FOREIGN KEY REFERENCES Glumac(ID),
	Uloga NVARCHAR(50)
	CONSTRAINT PK_FilmGlumac PRIMARY KEY (FilmID, GlumacID, Uloga)
);

CREATE TABLE FilmRecenzent
(
	FilmID INT CONSTRAINT FK_FilmRecenzent_Film FOREIGN KEY REFERENCES Film(ID),
	RecenzentID INT CONSTRAINT FK_FilmRecenzent_Recenzent FOREIGN KEY REFERENCES Recenzent(ID),
	Ocjena INT CONSTRAINT CK_Ocjena CHECK (Ocjena BETWEEN 0 AND 10),
	Recenzija NVARCHAR(100),
	CONSTRAINT PK_FilmRecenzent PRIMARY KEY (FilmID, RecenzentID)
);