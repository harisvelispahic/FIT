using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace FIT.Data
{
    public class StudentiUvjerenjaIB230172
    {
	    public int Id {  get; set; }
	    public int StudentId { get; set; }
        public Student Student { get; set; }
        public DateTime VrijemeKreiranja { get; set; }
        public string Vrsta { get; set; }
        public string Svrha { get; set; }
        public byte[] Uplatnica { get; set; }
        public bool Printano { get; set; }
    }
}
