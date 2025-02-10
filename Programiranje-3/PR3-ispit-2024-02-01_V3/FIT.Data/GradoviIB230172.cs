using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class GradoviIB230172
    {
        public int Id {  get; set; }
        public int DrzavaId {  get; set; }
        public DrzaveIB230172 Drzava{  get; set; }
        public string Naziv{  get; set; }
        public bool Status{  get; set; }
    }
}
