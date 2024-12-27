namespace Core
{
    public class Student
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public float Average { get; set; }

        public override string ToString()
        {
            return $"{this.Name} has id {this.Id}";
        }

    }
}