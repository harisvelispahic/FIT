using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class ProstorijeIB230172
    {
        public int Id {  get; set; }
        public string Naziv{ get; set; }
        public string Oznaka{ get; set; }
        public byte[] Logo{ get; set; }
        public int Kapacitet{ get; set; }

        public List<NastavaIB230172> NastavaIB230172 { get; set; } = new List<NastavaIB230172>();

        [NotMapped]
        public int BrojPredmeta => NastavaIB230172.Where(x => x.ProstorijeId == Id).Count();
    }
}
