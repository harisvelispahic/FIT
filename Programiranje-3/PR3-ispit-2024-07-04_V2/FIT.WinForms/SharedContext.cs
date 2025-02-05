using FIT.Infrastructure;

namespace FIT.WinForms
{
    public class SharedContext
    {
        public readonly static DLWMSDbContext db = new();
    }
}
