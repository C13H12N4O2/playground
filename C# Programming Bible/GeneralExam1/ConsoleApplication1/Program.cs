using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {

            Console.WriteLine("Hello, world!");

            int i;
            int sum = 0;
            for (i = 0; i != 10; ++i)
                sum += i;

            Console.WriteLine(sum);

            List<string> list = new List<string>();
            list.Add("James");
            list.Add("Chris");
            list.Add("Neuro");

            foreach (string item in list)
                Console.WriteLine(item);

            var varList = new List<int>();
            for (i = 0; i != 10; ++i)
                varList.Add(i);

            foreach (int item in varList)
                Console.WriteLine(item);

            const int j = 65535;
            Console.WriteLine(j);


            Func<int, int> square = (x) => x * x;
            Console.WriteLine(square(5));

            Action<string> greet = (name) => {
                string greeting = string.Format("Hello {0}", name);
                Console.WriteLine(greeting);
            };
            greet("World");

            int[] scores = new int[] { 97, 92, 81, 60 };
            IEnumerable<int> scoreQuery =
                from score in scores
                where score > 80
                select score;

            foreach (int item in scoreQuery)
                Console.Write(item + " ");

            var stringCollection = new SampleCollection<string>();
            stringCollection[0] = "Hello, world!";
            Console.WriteLine(stringCollection[0]);

            while (true) ;
        }
    }
}

class SampleCollection<T>
{
    private T[] arr = new T[100];

    public T this[int i]
    {
        get { return arr[i]; }
        set { arr[i] = value; }
    }
}