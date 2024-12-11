using DLWMS.Data;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DLWMS.Infrastructure
{
    public class DLWMSContext : DbContext
    {
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data source=C:\\Users\\xy\\Desktop\\github\\FIT\\Programiranje-3\\DLWMS_P11\\DLWMS.db");
        }

        public DbSet<Student> Studenti { get; set; }
        public DbSet<Predmet> Predmeti { get; set; }
        public DbSet<PolozeniPredmet> PolozeniPredmeti { get; set; }
    }
}
