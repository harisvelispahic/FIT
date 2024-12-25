using DLWMS.Infrastructure;

namespace DLWMS.WinApp.Helpers
{
    public static class Ekstenzije
    {
        public static bool IsSet(this string text)
        {
            return !string.IsNullOrWhiteSpace(text);
        }


        public static void UcitajPodatke<T>(this ComboBox comboBox, List<T> dataSource,
            string displayMember = "Naziv", string valueMember = "Id")
        {
            comboBox.DataSource = null;
            comboBox.DataSource = dataSource;
            comboBox.DisplayMember = "Naziv";
            comboBox.ValueMember = "Id";
        }     

    }
}
