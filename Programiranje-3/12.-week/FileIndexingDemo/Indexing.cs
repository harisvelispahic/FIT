namespace FileIndexingDemo
{
    public class Indexing
    {
        public static void FindName(string name)
        {
            var foundFile = "";

            using(var fs = new FileStream("IndexDemo/Index.txt", FileMode.Open, FileAccess.Read))
            using(var sr = new StreamReader(fs))
            {
                var indexFile = sr.ReadToEnd().Split('\n').ToList();

                foreach (var item in indexFile)
                {
                    Console.WriteLine($"-->{item}");
                }

                var firstLetter = name.ToLower()[0];

                var line = indexFile.Where(item => firstLetter == item[0]).FirstOrDefault();

                var targetFile = line.Split('=').ToList()[1].Trim();
                Console.WriteLine($"{targetFile}.txt");
                foundFile = $"IndexDemo/Data/{targetFile}.txt";
            }

            using(var fs = new FileStream(foundFile, FileMode.Open, FileAccess.Read))
            using (var sr = new StreamReader(fs))
            {
                var result = sr.ReadToEnd().Split('\n').ToList();
                foreach (var item in result)
                {
                    if(item.Split(' ').ToList()[0] == name)
                    {
                        Console.WriteLine(item);
                        break;
                    }
                }
            }
        }
    }
}