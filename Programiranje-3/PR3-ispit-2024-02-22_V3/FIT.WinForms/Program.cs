using FIT.WinForms.IspitIB230172;
using FIT.WinForms.Izvjestaji;

namespace FIT.WinForms
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            var startnaForma = new frmProstorijeIB230172();           
            Application.Run(startnaForma);
        }
    }
}