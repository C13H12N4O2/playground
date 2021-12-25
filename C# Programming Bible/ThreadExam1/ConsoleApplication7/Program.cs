using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApplication7
{
    class ThreadExam1
    {
        public static void Print1()
        {
            Console.WriteLine("첫 번째 Thread ***");
        }

        public void Print2()
        {
            Console.WriteLine("두 번쨰 Thread ***");
        }
        public static void Main()
        {
            Thread thread = new Thread(new ThreadStart(Print1));
            thread.Start();
            thread = new Thread(new ThreadStart((new ThreadExam1()).Print2));
            thread.Start();

            Console.WriteLine("세 번째 Thread ***");

            while (true) { }
        }
    }
}
