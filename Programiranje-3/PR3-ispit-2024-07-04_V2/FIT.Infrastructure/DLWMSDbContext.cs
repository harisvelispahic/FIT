using FIT.Data;

using Microsoft.EntityFrameworkCore;

using System.Configuration;

namespace FIT.Infrastructure
{
    public class DLWMSDbContext : DbContext
    {
        private readonly string dbPutanja;

        public DLWMSDbContext()
        {
            dbPutanja = ConfigurationManager.
                ConnectionStrings["DLWMSBaza"].ConnectionString;
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite(dbPutanja);
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            //modelBuilder.Entity<Student>.hasMany(student => student.PolozeniPredmeti).WithOne(polPred => polPred.Student)
            //modelBuilder.Entity<Student>.

            modelBuilder.Entity<PolozeniPredmeti>()
                .HasOne(pp => pp.Student)
                .WithMany(s => s.PolozeniPredmeti)
                .HasForeignKey(pp => pp.StudentId);

            modelBuilder.Entity<PolozeniPredmeti>()
                .HasOne(pp => pp.Predmet)
                .WithMany(p => p.PolozeniPredmeti)
                .HasForeignKey(pp => pp.PredmetId);

            base.OnModelCreating(modelBuilder);

        }

        public DbSet<Student> Studenti { get; set; }
        public DbSet<Predmeti> Predmeti { get; set; }
        public DbSet<PolozeniPredmeti> PolozeniPredmeti { get; set; }
        public DbSet<StudentiUvjerenjaIB230172> StudentiUvjerenjaIB230172 { get; set; }

    }
}