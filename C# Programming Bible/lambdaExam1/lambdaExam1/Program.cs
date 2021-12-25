using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lambdaExam1
{
    class Program
    {
        static void Main(string[] args)
        {
            Func<int, int> square = x => x * x;
            Console.WriteLine(square(5));

            System.Linq.Expressions.Expression<Func<int, int>> e = x => x * x;
            Console.WriteLine(e);

            int[] numbers = { 2, 3, 4, 5 };
            var squaredNumbers = numbers.Select(x => x * x);
            Console.WriteLine(string.Join(" ", squaredNumbers));

            Action<string> greet = name =>
            {
                string greeting = "Hello";
                Console.WriteLine("{0}, {1}", greeting, name);
            };
            greet("World");

            Action line = () => Console.WriteLine();
            line();

            Func<double, double> cube = x => x * x * x;
            Console.WriteLine(cube(3));

            Func<int, int, bool> testForEquality = (x, y) => x == y;
            Console.WriteLine(testForEquality(15, 15));

            Func<int, string, bool> isTooLong = (int x, string s) => s.Length > x;
            Console.WriteLine(isTooLong(6, "Hello"));

            Func<int, bool> equalsFive = x => x == 5;
            bool result = equalsFive(4);
            Console.WriteLine(result);

            numbers = new int[] { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            int oddNumbers = numbers.Count(n => n % 2 == 1);
            Console.WriteLine("There are {0} odd numbers in {1}",
                oddNumbers, string.Join(" ", numbers));

            numbers = new int[] { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            var firstNumbersLessThanSix = numbers.TakeWhile(n => n < 6);
            Console.WriteLine(string.Join(" ", firstNumbersLessThanSix));

            numbers = new int[] { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            var firstSmallNumbers = numbers.TakeWhile((n, index) => n >= index);
            Console.WriteLine(string.Join(" ", firstSmallNumbers));

            numbers = new int[] { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            firstSmallNumbers = numbers.TakeWhile((n, index) =>
            {
                Console.WriteLine("{0}, {1}, {2}", n, index, n >= index);
                return n >= index;
            });
            Console.WriteLine(string.Join(" ", firstSmallNumbers));

            Console.ReadKey();
        }
    }
}
