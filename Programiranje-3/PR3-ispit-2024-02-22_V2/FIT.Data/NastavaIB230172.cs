﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.Data
{
    public class NastavaIB230172
    {
        public int Id {  get; set; }
        public int ProstorijeId {  get; set; }
        public ProstorijeIB230172 Prostorije { get; set; }
        public int PredmetId {  get; set; }
        public Predmeti Predmet {  get; set; }
        public string Vrijeme {  get; set; }
        public string Dan{  get; set; }
        public string Oznaka{  get; set; }
        [NotMapped]
        public string PredmetProstorijaVrijeme => $"{Predmet.Naziv} - u {Dan} @ {Vrijeme}";

    }
}
