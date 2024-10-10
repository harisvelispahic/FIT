namespace PRIII.vjezbe2 
{
    public class Game
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public decimal Price { get; set; }  // najbolje za novac (rounding problems), decimal is a value type
        public Publisher GamePublisher { get; set; }

        //public int test; // field
        //public void SetTest(int val)    // accesors
        //{
        //    test = val;
        //}
        //public int GetTest() { return test; }   // accesors


        //// properties are there because there is need to control things, what can be set and what can be retrieved via get & set function

        //// before it was done like this

        //private int age;

        //public int Age
        //{
        //    get { return age; }
        //    //set { age = value; }
        //    set { age = MyCustomRuleForSettingAValue(value); }
        //}

        //// properties su najmoderniji nacin da se isto postigne

        //private int MyCustomRuleForSettingAValue(int age)
        //{
        //    return age;
        //}
        public Game(string name, string description, decimal price)
        {
            Name = name;
            Description = description;
            Price = price;
        }

        public override string ToString()   // RESEARCH STRING BUILDER !!!
        {
            return $"Name: {Name}\nDescription: {Description}\nPrice: {Price}$";
        }
    }
    public class Publisher
    {
        public int Id { get; set; }
        public string Name { get; set; }
    }
    public class Program 
    {
        static void Main(string[] args) 
        {
            Game game = new Game("Assassin's Creed II", "Best AC game ever created", 10.0m);
            Game game2 = new Game("Assassin's Creed II", "Best AC game ever created", 10.0m);
            Console.WriteLine(game);
            Console.WriteLine("========================================");
            Console.WriteLine(game.GetHashCode());
            Console.WriteLine(game2.GetHashCode());

        }
    }
}