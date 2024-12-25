using DLWMS.Data;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DLWMS.ConsoleApp.Predavanja
{
    internal class P3
    {

        public static void Pokreni()
        {
            //Reference();
            //Out();
            In();
        }

        private static void In()
        {
            StudentInit student = new StudentInit();
            TestIn(student);
        }

        private static void TestIn(in StudentInit student)
        {
            student.BrojIndeksa = "IB120021";
            student.DatumRodjenja = DateTime.Now;           
        }

        private static void Out()
        {
            if(int.TryParse("65*465", out int rezultat))
                Console.WriteLine($"Rezultat -> {rezultat}");            
            int godina;
            TestOut(out godina);
        }

        private static void TestOut(out int godina)
        {
            godina = 2025;
        }

        private static void Reference()
        {
            int godina = 2024;
            UvecajGodinu(ref godina);
            Console.WriteLine($"Godina -> {godina}");
        }

        private static void UvecajGodinu(ref int godina)
        {
            godina++;
        }
    }
}
