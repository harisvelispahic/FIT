using System.ComponentModel.DataAnnotations.Schema;

namespace DLWMS.Data
{

    [Table("Spolovi")]  // omogucava razlicite nazive tabela i klasa
    public class Spol
    {
        public int Id { get; set; }
        public string Naziv { get; set; }
    }

}