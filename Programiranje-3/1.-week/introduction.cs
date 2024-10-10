using System;   // isto kao include (slicno)

namespace pr3vjezbe1    // nije isto kao u c++, namespace se koristi radi organizacije, definisanja, ogranicenja koda (namespace je kao folder)
{
    public class Person { }
    public class AnotherClass { }

    public class Student : Person/*, AnotherClass*/  // nema visestrukog nasljedjivanja !!!
    {
    
    } 

    public struct PersonStruct  // isto kao klasa, ali se NE alocira na heapu, nego na stacku, osim u nekim uslovima
    {
        public int Id;
    }
    public class Program    // entry point
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello C#");

            int i = 0;
            i.GetType();
            Person p = new Person();
            p.ToString();
        }
    }
}