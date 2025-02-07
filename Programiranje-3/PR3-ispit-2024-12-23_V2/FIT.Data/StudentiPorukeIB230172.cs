using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace FIT.Data
{
	public class StudentiPorukeIB230172
	{
		public int Id { get; set; }
		public int StudentId { get; set; }
		public Student Student {  get; set; }
		public int PredmetId { get; set; }
		public Predmeti Predmet {get; set; }
		public DateTime Validnost { get; set; }
		public string Sadrzaj { get; set; }
		public string Hitnost { get; set; }
		public byte[] Slika { get; set; }

		[NotMapped]
		public string PredmetNaziv => Predmet.Naziv;
    }
}
