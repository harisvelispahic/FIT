namespace DelimiterDemo
{
    public class DelimitedFileDemo
    {
        public static void SaveDelimitedFile()
        {
            var sw = File.AppendText("Delimited.csv");
            sw.WriteLine("sep=,");
            for (int i = 0; i < 500; i++)
            {
                sw.Write($"{i},");
            }
            sw.Flush();
            sw.Close();
            sw.Dispose();
        }

        public static void SaveDelimitedFileV2()
        {
            var sw = File.AppendText("Delimited.csv");
            sw.WriteLine("sep=,");
            for (int i = 2; i < 500; i++)
            {
                sw.WriteLine($"{i}, {i * i}, {i * i * i}");
            }
            sw.Flush();
            sw.Close();
            sw.Dispose();
        }
    }
}