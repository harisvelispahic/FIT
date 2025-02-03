using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class PrisustvoIB230172
    {
        public int Id { get; set; }
        public int NastavaId { get; set; }
        public NastavaIB230172 Nastava { get; set; }
        public int StudentId { get; set; }
        public Student Student { get; set; }

    }
}
