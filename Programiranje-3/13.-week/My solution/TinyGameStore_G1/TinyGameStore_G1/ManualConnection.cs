using Microsoft.Data.Sqlite;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TinyGameStore_G1
{
    public class ManualConnection : IDisposable
    {
        public SqliteConnection Connection { get; set; }

        public ManualConnection()
        {
            if (!System.IO.File.Exists("GameDb.db"))
            {
                System.IO.File.Create("GameDb.db");
                Connection = new SqliteConnection("DataSource = GameDb.db;");
            }
            
            Connection = new SqliteConnection($"Data source = {ConfigurationManager.ConnectionStrings[1].ConnectionString}");
        }

        public void Dispose()
        {
            Connection.Close();
            Connection.Dispose();
        }
    }
}
