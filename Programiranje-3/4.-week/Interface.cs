using MinimalGameStore.Core;
using System.Security.Cryptography.X509Certificates;
using System.Security.Principal;
using System.Text.Json;
using System.Transactions;

namespace PRIII_G1_2024_Concepts
{
    interface IVehicle
    {
        public int Id { get; set; }
        public int FuelAmount { get; set; }
        void Drive();
        void Refuel(int amount);
        void Park();
    }

    class Car : IVehicle
    {
        public int Id { get; set; }
        public int FuelAmount { get; set; }

        public Car()
        {
            Id = Random.Shared.Next();
        }
        public void Drive()
        {
            if (FuelAmount <= 0)
            {
                Console.WriteLine($"{Id} - Can't drive car, no fuel!");
            }
            else
            {
                Console.WriteLine($"{Id} - Driving the car around using gasoline");
                FuelAmount--;
            }
        }

        public void Park()
        {
            Console.WriteLine($"{Id} - Parking the car");
        }

        public void Refuel(int amount)
        {
            Console.WriteLine($"{Id} - Refueled with gasoline");
            FuelAmount = amount;
        }
    }

    class ElectricCar : IVehicle
    {
        public int Id { get; set; }
        public int FuelAmount { get; set; }

        public ElectricCar()
        {
            Id = Random.Shared.Next();
        }
        public void Drive()
        {
            if (FuelAmount <= 0)
            {
                Console.WriteLine($"{Id} - Can't drive car, no electricity!");
            }
            else
            {
                Console.WriteLine($"{Id} - Driving the car around using electricity");
                FuelAmount =- 2;
            }
        }

        public void Park()
        {
            Console.WriteLine($"{Id} - Parking the car");
        }

        public void Refuel(int amount)
        {
            Console.WriteLine($"{Id} - Refueled with electricity");
            FuelAmount = amount;
        }
    }


    internal class Program
    {
        static void Main(string[] args)
        {
            // kako provjeravamo jel interface npr is IVehicle
            var listOfVehicles = new List<IVehicle>();
            listOfVehicles.Add(new Car());
            listOfVehicles.Add(new Car());
            listOfVehicles.Add(new Car());
            listOfVehicles.Add(new Car());
            listOfVehicles.Add(new Car());
            listOfVehicles.Add(new ElectricCar());
            listOfVehicles.Add(new ElectricCar());
            listOfVehicles.Add(new ElectricCar());
            listOfVehicles.Add(new ElectricCar());
            listOfVehicles.Add(new ElectricCar());

            for(int i=0; i<listOfVehicles.Count; i++)
            {
                listOfVehicles[i].Drive();
            }
        }
    }
}