using System.Runtime.InteropServices.ObjectiveC;

namespace CsharpConceptsG1
{
    public class ConnectionExample<T1, T2> where T1 : IEnumerable<T2>
    {

    }

    public class Connection<T> where T : struct
    {
        public T Something { get; set; }
        public void TransferData()
        {
            Console.WriteLine(typeof(T).Name);
        }

    }

    public class MyResource
    {
        // code goes here

        public event Action MyEvent;
        public Action MyDelegate;
        public void SomeMethod()
        {
            MyEvent?.Invoke();
            MyEvent();  // the same, but ? is nullable
        }
    }

    public class Student
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string FirstName { get; set; }

        public List<Predmet> Predmeti { get; set; }
    }
    public class Predmet
    {
        public string Name { get; set; }
        public int Ocjena { get; set; }
    }
    internal class Program
    {
        static List<object> connections = new List<object>(); 
        static void Main(string[] args)
        {
            var enumerator = SomeMethod();
            enumerator.MoveNext();
            Console.WriteLine(enumerator.Current);

            var con = new ConnectionExample<List<int>, int>();

            connections.Add(new Connection<int>());
            connections.Add(new Connection<float>());
            connections.Add(new Connection<double>());
            connections.Add(new Connection<Int64>());

            foreach (var item in connections) 
            {
                dynamic connection = item;
                connection.TransferData();
                // ovo bi puklo ako se metoda promijeni
            }

            // REFLECTION
            for (int i = 0; i < con.GetType().GetMethods().Length; i++) 
            {
                Console.WriteLine(con.GetType().GetMethods()[i].Name);
            }
            Console.WriteLine();

            for (int i = 0; i < con.GetType().GetConstructors().Length; i++)
            {
                Console.WriteLine(con.GetType().GetConstructors()[i].GetParameters());
            }
            Console.WriteLine();


            // ANONYMOUS OBJECTS
            var myObject = new { Index = 10, Name = "Someone", Age = 20 };
            // koristimo ga samo u scope-u u kojem smo
            SomeOperation(myObject);


            // DELEGATES AND EVENTS


            Action<MyResource> callback_afterloaded = (loadedStuff) =>
            { /*do things with the loaded stuff*/
                Console.WriteLine("Doing things...");
            };

            // mozemo proslijediti null jer je delegate tip (ne bismo trebali...)
            LoadHugeResoruce(callback_afterloaded);

            MyResource resource = new MyResource();
            //resource.MyEvent();   // ovo ne smijemo raditi, mozemo ga pozvati samo unutar klase
            resource.MyDelegate();  // ovo mozemo raditi

            resource.MyEvent += Resource_MyEvent;
            resource.MyDelegate += MyDelegateStack;


            // LINQ - extension methods over IEnumerable objects?
            // 2 nacina da pisemo query-e
            var listStudents = new List<Student>(); // suppose this is full of students
            var result = listStudents.Select(x => new Student()
            {
                Id = x.Id,
                Name = x.Name,
                Predmeti = x.Predmeti.Where(pr => pr.Ocjena > 5).ToList()
            });

            // cannonical form
            var result2 = from x in listStudents
                          select new Student()
                          {
                              Id = x.Id,
                              Name = x.Name,
                              Predmeti = (from pr in x.Predmeti
                                          where pr.Ocjena > 5
                                          select new Predmet() { Name = pr.Name, Ocjena = pr.Ocjena }).ToList()
                          };
        }

      

        private static void MyDelegateStack()
        {
            throw new NotImplementedException();
        }

        private static void Resource_MyEvent()
        {
            throw new NotImplementedException();
        }

        static void LoadHugeResoruce(Action<MyResource> callback)  // async
        {
            var LoadedResource = new MyResource();
            // here goes loading the huge resources which is taking some time
            // loading from internet onging ... blocking here
            Thread.Sleep(2000);

            callback(LoadedResource);

        }

        static List<int> FilterList(List<int> input, Func<int, bool> filter) 
        {
            //return input.Where(x => filter(x)).ToList();
            var result = new List<int>();
            foreach(var item in input)
            {
                if(filter(item))
                    result.Add(item);
            }
            return result;
        }
        static void SomeOperation(object x) 
        {
            
        }
        private static IEnumerator<int> SomeMethod()
        {
            yield return 1;
        }
    }
}

/*
Iterator vs enumerator - iterator for loop
Enumerator radi samo read, iterator moze read/write

U foreachu možemo mijenjati pojedine atribute objekata, ali ne reassignovati objekte

Foreach radi na svim klasama koje implementiraju IEnumerable interface

Yield

Foreach je stateless - ne mozemo zapamptiti stanje
Da bi bio statefull koristimo yield
Da bi koristili yield, metoda mora da vraća IEnumerator

Yield je syntatic sugar

Dynamic keyword

Reflection - objekat kaze ko je i sta ima
Dynamic se oslanja na reflection


Anonimni objekti
Read only su, immutable
Da ne bismo pravili novu specificnu klasu za objekt koji preuzimamo od baze, mozemo koristiti anonimni objekat

Delegates and events

Delegat mozemo pozvati bilo gdje u kodu
npr DelegateName.Invoke();
*/