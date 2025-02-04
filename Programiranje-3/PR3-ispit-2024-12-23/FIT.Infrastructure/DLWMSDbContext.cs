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
            //modelBuilder.Entity<PolozeniPredmeti>()
            //    .HasOne(pp => pp.Student)
            //    .WithMany(s => s.PolozeniPredmeti)
            //    .HasForeignKey(pp => pp.StudentId);

            //modelBuilder.Entity<PolozeniPredmeti>()
            //    .HasOne(pp => pp.Predmet)
            //    .WithMany(p => p.PolozeniPredmeti)
            //    .HasForeignKey(pp => pp.PredmetId);



            //modelBuilder.Entity<StudentiUloge>()
            //    .HasOne(su => su.Student)
            //    .WithMany(s => s.StudentiUloge)
            //    .HasForeignKey(su => su.StudentId);

            //modelBuilder.Entity<StudentiUloge>()
            //    .HasOne(su => su.Uloga)
            //    .WithMany(u => u.StudentiUloge)
            //    .HasForeignKey(su => su.UlogaId);

            base.OnModelCreating(modelBuilder);
        }

        public DbSet<Student> Studenti { get; set; }
        public DbSet<Predmeti> Predmeti { get; set; }
        public DbSet<PolozeniPredmeti> PolozeniPredmeti { get; set; }
        public DbSet<Semestri> Semestri { get; set; }
        public DbSet<Uloge> Uloge { get; set; }
        public DbSet<StudentiUloge> StudentiUloge { get; set; }
        public DbSet<StudentiPorukeIB230172> StudentiPorukeIB230172 { get; set; }

    }
}