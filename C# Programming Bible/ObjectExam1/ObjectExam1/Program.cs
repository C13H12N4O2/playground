using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace ObjectExam1
{
    public class Person
    {
        public string Name { get; set; }
        public int Age { get; set; }
        public Person(string name, int age)
        {
            Name = name;
            Age = age;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Person person1 = new Person("Leopold", 6);
            Console.WriteLine("person1 Name = {0} Age = {1}",
                person1.Name, person1.Age);

            Person person2 = person1;

            person2.Name = "Molly";
            person2.Age = 16;

            Console.WriteLine("person2 Name = {0} Age = {1}",
                person2.Name, person2.Age);
            Console.WriteLine("person1 Name = {0} Age = {1}",
                person1.Name, person1.Age);

            Console.WriteLine("Press any key to exit.");
            Debug.WriteLine("Print a line on a debug screen");
            Console.ReadKey();
        }
    }
}
