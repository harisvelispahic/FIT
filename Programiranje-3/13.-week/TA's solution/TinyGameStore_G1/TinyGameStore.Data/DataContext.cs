using Microsoft.EntityFrameworkCore;

namespace TinyGameStore.Data
{
    public class DataContext : DbContext
    {

        public DataContext() : base() { }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("DataSource=TinyGameStore.db");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<GameRating>(entity =>
            {
                entity.HasOne(d => d.UsersGame).WithMany(p => p.GameRatings).HasForeignKey(d => d.UserGamesId);
            });

            modelBuilder.Entity<GamesGenre>(entity =>
            {
                entity.HasOne(d => d.Game).WithMany(p => p.GamesGenres).HasForeignKey(d => d.GameId);
                entity.HasOne(d => d.Genre).WithMany(p => p.GamesGenres).HasForeignKey(d => d.GenreId);
            });

            modelBuilder.Entity<UsersGame>(entity =>
            {
                entity.HasOne(d => d.Game).WithMany(p => p.UsersGames).HasForeignKey(d => d.GameId);
                entity.HasOne(d => d.User).WithMany(p => p.UsersGames).HasForeignKey(d => d.UserId);
            });
        }

        public virtual DbSet<Game> Games { get; set; }
        public virtual DbSet<User> Users { get; set; }
        public virtual DbSet<GameRating> GameRatings { get; set; }
        public virtual DbSet<GamesGenre> GamesGenres { get; set; }
        public virtual DbSet<Genre> Genres { get; set; }
        public virtual DbSet<UsersGame> UsersGames { get; set; }
    }
}
