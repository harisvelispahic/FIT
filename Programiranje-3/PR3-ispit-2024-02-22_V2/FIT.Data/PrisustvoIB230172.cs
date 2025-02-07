using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class PrisustvoIB230172
    {
        public int Id { get; set; }
        public int NastavaId { get; set; }
        public NastavaIB230172 Nastava {  get; set; }
        public int StudentId { get; set; }
        public Student Student { get; set; }
        [NotMapped]
        public string StudentIndeks => Student.StudentBrIndeksa;
        public string PredmetProstorijaVrijeme => Nastava.PredmetProstorijaVrijeme;
    }
}
