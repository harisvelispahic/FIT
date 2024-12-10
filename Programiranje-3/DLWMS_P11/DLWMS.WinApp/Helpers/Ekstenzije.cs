using DLWMS.Data;
using DLWMS.Infrastructure;

namespace DLWMS.WinApp.Helpers
{
    public static class Ekstenzije
    {
        public static bool IsSet(this string text)
        {
            return !string.IsNullOrWhiteSpace(text);
        }


        public static object GetOdabraniRed(this DataGridView dataGridView)
        {
            if(dataGridView.SelectedRows.Count == 0)
                throw new Exception("Niste odabrali red!");//TODO: prebaciti u resource fajl
            return dataGridView.SelectedRows[0].DataBoundItem;         
        }

        public static void UcitajPodatke<T>(this ComboBox comboBox, List<T> dataSource,
            string displayMember = "Naziv", string valueMember = "Id")
        {
            comboBox.DataSource = dataSource;
            comboBox.DisplayMember = displayMember;
            comboBox.ValueMember = valueMember;
        }     

    }
}
