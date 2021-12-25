using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication2
{
    class Arithmetic
    {
        public int Add(int a, int b)
        {
            return a + b;
        }

        public int Sub(int a, int b)
        {
            return a - b;
        }

        public int Mul(int a, int b)
        {
            return a * b;
        }

        public int Div(int a, int b)
        {
            if ((a == 0) || (b == 0))
                return 0;
            return a / b;
        }

        public void PrintInfo(string str)
        {
            System.Console.WriteLine("Arithmetic::PrintInfo = {0}", str);
        }
    }
    
    public delegate int ArithmeticDelegate(int a, int b);
    public delegate void PrintInfoDelegate(string str);

    class DelegateExam1
    {
        static void Main(string[] args)
        {
            Arithmetic obj = new Arithmetic();
            ArithmeticDelegate ex1 = new ArithmeticDelegate(obj.Add);
            System.Console.WriteLine("Add: ex(20, 10) = {0}", ex1(20, 10));

            ex1 = new ArithmeticDelegate(obj.Sub);
            System.Console.WriteLine("Sub: ex(20, 10) = {0}", ex1(20, 10));

            ex1 = new ArithmeticDelegate(obj.Mul);
            System.Console.WriteLine("Mul: ex(20, 10) = {0}", ex1(20, 10));

            ex1 = new ArithmeticDelegate(obj.Div);
            System.Console.WriteLine("Div: ex(20, 10) = {0}", ex1(20, 10));

            PrintInfoDelegate ex2 = new PrintInfoDelegate(obj.PrintInfo);
            ex2("델리게이트 예제");

            while (true) { }
        }
    }
}
