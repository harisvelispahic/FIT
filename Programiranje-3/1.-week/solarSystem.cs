using System;

namespace SolarSystem
{
    public class Moon
    {
        public int Id { get; set; }
        public string Name { get; set; }


        public Moon(int id, string name)
        {
            Id = id;
            Name = name; ;
        }
        public Moon()
        {
            Id = 5;
            Name = "Mjesec";
        }
    }
    public class Planet
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public Moon[] Moons { get; set; }


        public Planet(int id, string name, Moon[] moons)
        {
            Id = id;
            Name = name;
            Moons = moons;
        }
        public Planet()
        {
            Id = 10;
            Name = "Zemlja";
            Moons = new Moon[1];
            Moons.Append(new Moon(5,"Mjesec"));
        }
    }

    public class Star
    {
        public int Id { get; set; }
        public string Name { get; set; }


        public Star(int id, string name)
        {
            Id = id;
            Name = name; ;
        }
        public Star()
        {
            Id = 15;
            Name = "Sunce";
        }
    }

    public class Asteroid
    {
        public int Id { get; set; }
        public string Name { get; set; }


        public Asteroid(int id, string name)
        {
            Id = id;
            Name = name; ;
        }
        public Asteroid()
        {
            Id = 20;
            Name = "Zemljin novi Asteroid";
        }
    }

    

    public class SolarSystem
    {
        public Star Star { get; set;  }
        public Planet[] Planets { get; }
        public Asteroid[] Asteroids { get; }

        public SolarSystem(Star star, Planet[] planets, Asteroid[] asteroids)
        {
            this.Star = star;
            this.Planets = planets;
            this.Asteroids = asteroids;
        }
    }


    public class Program
    {
        public static void Main(string[] args)
        {
            Planet[] planets = new Planet[5];
            Asteroid[] asteroids = new Asteroid[5];

            SolarSystem suncevSistem = new SolarSystem(new Star(0, "Sun"), planets, asteroids);
        }
    }
}