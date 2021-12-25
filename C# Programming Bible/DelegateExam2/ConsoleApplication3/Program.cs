using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication3
{
    class Example
    {
        public static void StaticMethod()
        {
            Console.WriteLine("Static method");
        }

        public void NormalMethod()
        {
            Console.WriteLine("Normal method");
        }
    }
    
    delegate void ExamDelegate();
    class Program
    {
        static void Main(string[] args)
        {
            Example obj = new Example();
            ExamDelegate ex1 = new ExamDelegate(obj.NormalMethod);
            ExamDelegate ex2 = new ExamDelegate(Example.StaticMethod);
            ExamDelegate data;

            data = ex1;
            data();
            Console.WriteLine();

            data += ex2;
            data();
            Console.WriteLine();

            data -= ex1;
            data();

            while (true) { }
        }
    }
}
