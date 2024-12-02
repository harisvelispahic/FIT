namespace Midterm
{
    public class Midterm
    {
        public bool WasHard { get; set; }
        public bool Passed { get; set; }
        public Midterm(bool wasHard, bool passed)
        {
            WasHard = wasHard;
            Passed = passed;
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            Midterm FirstMidterm20112024 = new Midterm(true, true);
            Console.WriteLine(FirstMidterm20112024.Passed ? "Great! You've passed the exam! :D" : ":(");
        }
    }
}