using MinimalGameStore.Core;

namespace PRIII_G1_2024_Concepts
{
    public class Mathematics
    {
        const float PI = 3.141529f;                 // static by default, immutable, because it is static, it is related to the class

        // const:
        // - is resolved during compile time
        // - must be assigned when declared
        // - cannot be modified once declared
        // - implicitly static
        // - only primitive types are allowed
        // - accessed via class
    }

    public abstract class Window
    {
        public readonly int Id;

        // readonly:
        // - initialization time: at runtime through constructor or at declaration
        // - cannot be modified after object construction
        // - can be either static or instance based

        public void SettingUpWindow()
        {
            // code
        }

        //public Window(int id)
        //{
        //    Id = id;              // demonstracija kako se settuje readonly field
        //}

        public abstract void Render();      // YOU MUST OVERRIDE THIS
    }

    public class WindowTask1 : Window
    {
        public override void Render()
        {
            Console.WriteLine("Task1");
        }
    }

    public class WindowTask2 : Window
    {
        public override void Render()
        {
            Console.WriteLine("Task2");
        }
    }
        

    class SimpleDictionary
    {
        private string[] keys;
        private string[] values;

        private int count;

        public SimpleDictionary(int capacity) 
        {
            keys = new string[capacity];
            values = new string[capacity];
            count = 0;
        }
        public string this[string val]      // indexers
        { 
            get 
            { 
                for(int i = 0; i < count; i++) 
                {
                    if (keys[i] == val)
                    {
                        return values[i];
                    }
                }

                throw new ArgumentException("Key not found");
            }
            set
            {
                // check if key already exists
                if(count < keys.Length)
                {
                    keys[count] = val;
                    values[count] = value;
                    count++;
                }
            }
        
        }
    }

    internal class Program
    {
        static List<Window> Windows = new List<Window>();                   // ZAŠTO TU, private default access modifier?


        static void Main(string[] args)
        {
            Console.WriteLine(Math.PI);



            Window task1 = new WindowTask1();
            Window task2 = new WindowTask2();

            Windows.Add(task1);
            Windows.Add(task2);

            for(int i = 0;i < Windows.Count; i++)
            {
                Windows[i].Render();
            }
            

            Genre genre = new Genre()
            {
                Id = 1,
                Name = "Adventure"
            };

            Console.WriteLine(genre);
            Console.WriteLine(Divider.Lines);



            Game game = new Game()
            {
                Id = 1,
                Name = "Assassin's Creed II",
                Publisher = "Ubisoft",
                ReleaseDate = DateTime.Now,
                CoverArt = "Ezio Auditore da Firenze",
                Genres = new List<Genre>
                {
                    new Genre() { Id = 1, Name = "Adventure" },
                    new Genre() { Id = 2, Name = "Parkour" }
                }
            };

            Console.WriteLine(game);


            User user = new User()
            {
                Id = 1,
                FirstName = "Haris",
                LastName = "Velispahic",
                BirthDate = DateTime.Now,
                Games = new List<Game>
                {
                    game
                }
            };

            Console.WriteLine(user);


            User defaultUser = null;
            var user1 = defaultUser ?? GenerateUser();  // null coalescing operator

            var NameOfUser1 = user1?.FirstName;         // null conditional operator
            Console.WriteLine(NameOfUser1);

            user1 ??= GenerateUser();                   // null coalescing assignment

            if(user1 is null)
            {
                Console.WriteLine("User 1 is null");
            }

            ArgumentNullException.ThrowIfNull(user1, nameof(user1));


            Console.WriteLine(user1!.FirstName);        // null forgiving operator
            // compiler ignores this


            VariadicPrintFunction("Hello", "World", "Something");


            SimpleDictionary Rjecnik = new SimpleDictionary(10);
            Rjecnik["speedy"] = "hitri";
            Rjecnik["white"] = "bijeli";
            Rjecnik["days"] = "dani";

            Console.WriteLine($"Hej vi { Rjecnik["speedy"] } {Rjecnik["white"] } {Rjecnik["days"] }");
        }

        private static User GenerateUser()
        {
            return new User(1, "Edin", "Dzeko", DateTime.Now, null);
        }

        public static void VariadicFunction(params string[] args)       // funkcije koje primaju ili niz parametara, ili parametre koje ce compiler kasnije pretvoriti u niz
                                                                        // not used too much
        {                       

        }

        public static void VariadicPrintFunction(params string[] args)
        {
            for(int i = 0;i < args.Length; i++)
            {
                Console.WriteLine(args[i]);
            }
        }
    }
}