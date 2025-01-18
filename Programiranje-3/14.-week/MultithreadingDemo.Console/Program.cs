using System;
using System.Runtime.CompilerServices;

namespace MultithreadingDemo.Consl
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            Console.WriteLine("Press enter to execute ...");
            Console.ReadLine();

            var result = "";

            await Task.Run( () => 
            {
                Console.WriteLine("Starting download...");
                var client = new HttpClient();
                result = client.GetStringAsync("https://www.fit.ba").Result;
                Console.WriteLine("Done downloading");
            });

            Console.WriteLine(result);

            Console.WriteLine("End of application");
            //Console.ReadLine();
        }
    }
}
