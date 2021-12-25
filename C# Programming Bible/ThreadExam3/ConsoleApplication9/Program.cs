using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApplication9
{
    class ThreadExam3
    {
        public static void Print1(object obj)
        {
            Console.WriteLine("첫 번째 Thread : ***");
        }

        public void Print2(object obj)
        {
            Console.WriteLine("두 번째 Thread : ***");
        }

        public static void Main(string[] args)
        {
            Timer timer = new Timer(new TimerCallback(Print1), null, 200, 100);
            timer = new Timer(new TimerCallback((new ThreadExam3()).Print2), null, 200, 100);
            Thread.Sleep(500);
            timer.Dispose();

            while (true) { }
        }
    }
}
