using MinimalGameStore.Core;
using System.Security.Cryptography.X509Certificates;
using System.Security.Principal;
using System.Text.Json;
using System.Transactions;

namespace PRIII_G1_2024_Concepts
{
    public struct Position
    {
        public int X;
        public int Y;

        public override string? ToString()
        {
            return $"X: {X}, Y: {Y}";
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            var positionsList = new List<Position>();
            var position = new Position() { X = 10, Y = 20 };

            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine($"Position before method call: {position}");

            ChangePosition(ref position);

            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine($"Position after method call: {position}");

            //var result = new Position();
            if (DetectCollision(position, out var result))  // in line declaration and initialization
            {
                result.X = 100;
            }
        }

        static void ChangePosition(ref Position position)    // ref je isto kao & u c++, a in kao const & u c++
        {
            position.X *= 10;
            position.Y *= 20;
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.WriteLine($"Position after change inside method: {position}");
        }
            
        static bool DetectCollision(Position position, out Position target)     // out can be used to return two things from a method (for simple things)
        {
            // logic for detecting collision // overlapping positions
            if (true)
            {
                target = new Position() { X = 10, Y = 20 };
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}