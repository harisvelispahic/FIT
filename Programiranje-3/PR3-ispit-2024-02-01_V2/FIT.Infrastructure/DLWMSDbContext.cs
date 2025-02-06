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
            //modelBuilder.Entity<GradoviIB230172>()
            //    .HasOne(g => g.Drzava)
            //    .WithMany(d => d.GradoviIB230172)
            //    .HasForeignKey(g => g.DrzavaId);

            base.OnModelCreating(modelBuilder);
        }
        public DbSet<Student> Studenti { get; set; }
        public DbSet<Predmeti> Predmeti { get; set; }
        public DbSet<PolozeniPredmeti> PolozeniPredmeti { get; set; }
        public DbSet<DrzaveIB230172> DrzaveIB230172 { get; set; }
        public DbSet<GradoviIB230172> GradoviIB230172 { get; set; }


    }
}