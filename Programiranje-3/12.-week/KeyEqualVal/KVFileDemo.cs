using Core;

namespace KeyEqualVal
{
    public class KVFileDemo
    {
        public static void SaveStudent(Student student)
        {
            var sw = new StreamWriter("TestStudent.txt", true);
            sw.WriteLine($"Indeks={student.Id}");
            sw.WriteLine($"Name={student.Name}");
            sw.Flush();
            sw.Close();
            sw.Dispose();
        }
        public static void WriteStudentDynamically(Student std)
        {
            var stdClassProps = std.GetType().GetProperties();

            using(var sw = new StreamWriter("TestStudent.txt"))
            {
                for (int i = 0; i < stdClassProps.Length; i++)
                {
                    sw.WriteLine($"{stdClassProps[i].Name} = {stdClassProps[i].GetValue(std)}");
                }
                sw.Flush();
                sw.Close();
            }
        }
        public static List<Student> LoadStudents()
        {
            var lstStd = new List<Student>();

            using(var sr = new StreamReader("TestStudent.txt"))
            {
                while (sr.Peek() != -1)
                {
                    var line1 = sr.ReadLine();//moving cursor further
                    var line2 = sr.ReadLine();//moving cusror further
                    var line3 = sr.ReadLine();//moving cusror further

                    var strArr1 = line1.Split('=');
                    var strArr2 = line2.Split('=');
                    var strArr3 = line3.Split('=');

                    lstStd.Add(new Student() { Id = int.Parse(strArr1[1]), Name = strArr2[1], Average = float.Parse(strArr3[1]) });
                }
            }

            return lstStd;
        }
    }
}