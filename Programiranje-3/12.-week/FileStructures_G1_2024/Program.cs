using Core;
using CursorOperationsDemo;
using DelimiterDemo;
using FileIndexingDemo;
using KeyEqualVal;

namespace FileStructures_G1_2024
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //CursorOps.DirectoryOps();

            //for (int i = 0; i < 50; i++)
            //{
            //    var std = new Student() { Id = i+1, Name = $"Fit student {i+1}"};
            //    CursorOps.WriteToAFile(std.ToString());
            //}

            //CursorOps.ReadFromAFileV2();
            //CursorOps.WriteToASpecificLine(3);
            //CursorOps.WriteToASpecificLocation(4);
            //DelimitedFileDemo.SaveDelimitedFile();
            //DelimitedFileDemo.SaveDelimitedFileV2();
            //var std1 = new Student() { Id = 1, Name = "Bob" };
            //var std2 = new Student() { Id = 2, Name = "Dave" };
            //KVFileDemo.SaveStudent(std1);
            //KVFileDemo.SaveStudent(std2);
            //KVFileDemo.WriteStudentDynamically(new Student() { Id = 123456, Name = "Alice", Average = 4.25f });

            //var result = KVFileDemo.LoadStudents();
            //foreach (var item in result)
            //{
            //    Console.WriteLine(item);
            //}

            Indexing.FindName("Ammara");

        }
    }
}