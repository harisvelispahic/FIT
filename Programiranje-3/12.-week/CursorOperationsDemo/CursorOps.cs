using System.IO;

namespace CursorOperationsDemo
{
    public class CursorOps
    {
        public static void DirectoryOps()
        {
            var dirInfo = Directory.CreateDirectory("MyDirectory/SomeOtherDirectory");
            Console.WriteLine(dirInfo.FullName);
            var path = Path.Combine(dirInfo.FullName, "test.txt");
            File.Create(path);


            Console.WriteLine(string.Join("\n",
                Directory.EnumerateFiles(Directory.GetCurrentDirectory())));

            Console.WriteLine("-----------------------------");
            Console.WriteLine("-----------------------------");

            Console.WriteLine(string.Join("\n",
                Directory.EnumerateDirectories(
                    AppDomain.CurrentDomain.BaseDirectory, "*.*", SearchOption.AllDirectories)));
        }

        public static void WriteToAFile(string data)
        {
            using (StreamWriter sw = new StreamWriter("testCursor.txt", true))
            {
                sw.WriteLine(data);
                sw.Close();
            }
        }

        public static void ReadFromAFileV1()
        {
            using (StreamReader sr = new StreamReader("testCursor.txt"))
            {
                while (sr.Peek() != -1)
                {
                    Console.WriteLine(sr.ReadLine());
                }
                sr.Close();
            }
        }

        public static void ReadFromAFileV2()
        {
            using (FileStream fs = new FileStream("testCursor.txt", FileMode.Open))
            using (StreamReader sr = new StreamReader(fs))
            {
                fs.Position = 0;
                var data = sr.ReadToEnd();
                Console.WriteLine(data);
                sr.Close();
            }
        }

        public static void WriteToASpecificLine(int lineNumber)
        {
            using (var fs = new FileStream("testCursor.txt", FileMode.Open, FileAccess.Read))
            using (var sr = new StreamReader(fs))
            using(var sw = new StreamWriter(fs))
            {
                var myFileContentLines = new List<string>();

                while(sr.Peek() != -1)
                    myFileContentLines.Add(sr.ReadLine());

                myFileContentLines.Insert(lineNumber, "This is my crazy data");
                fs.Position = 0;
                var strResult = string.Join("\n", myFileContentLines);
                sw.Write(strResult);
            }
        }

        public static void WriteToASpecificLocation(int locationIndex)
        {
            using (var fs = new FileStream("testCursor.txt", FileMode.Open, FileAccess.ReadWrite))
            using (var sr = new StreamReader(fs))
            using (var sw = new StreamWriter(fs))
            {
                var myFileContent = sr.ReadToEnd();
                var result = myFileContent.Insert(locationIndex, "MyDataInjected");
                fs.Position = 0;
                sw.Write(result);
            }
        }
    }
}