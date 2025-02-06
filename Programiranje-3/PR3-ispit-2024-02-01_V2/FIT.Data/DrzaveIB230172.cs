using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class DrzaveIB230172
    {
        public int Id { get; set; }
        public string Naziv { get; set; }
        public bool Status { get; set; }
        public byte[] Zastava { get; set; }

        public List<GradoviIB230172> GradoviIB230172 { get; set; } = new List<GradoviIB230172>();

        [NotMapped]
        public int BrojGradova => GradoviIB230172.Count(x => x.DrzavaId == Id);
    }
}
