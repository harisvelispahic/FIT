using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class StudentiUvjerenja
    {
        public int Id { get; set; }
        public int StudentId { get; set; }
        public DateTime VrijemeKreiranja { get; set; }
        public string Vrsta { get; set; }
        public string Svrha { get; set; }
        public byte[] Uplatnica { get; set; }
        public bool Printano { get; set; }

    }
}
