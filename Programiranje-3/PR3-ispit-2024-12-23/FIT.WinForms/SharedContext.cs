using FIT.Infrastructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FIT.WinForms
{
    public class SharedContext
    {
        public readonly static DLWMSDbContext db = new DLWMSDbContext();
    }
}
