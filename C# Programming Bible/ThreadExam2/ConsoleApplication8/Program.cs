using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApplication8
{
    class ThreadExam2
    {
        static int i = 0;
        public static void Print1(object obj)
        {
            for (i = 0; i != 3; ++i)
            {
                Console.WriteLine("첫 번쨰 Thread : {0} ***", i);
                Thread.Sleep(100);
            }
        }

        public void Print2(object obj)
        {
            for (int i = 0; i != 3; ++i)
            {
                Console.WriteLine("두 번째 Thread : {0} ***", i);
                Thread.Sleep(100);
            }
        }
        public static void Main(string[] args)
        {
            ThreadPool.QueueUserWorkItem(new WaitCallback(Print1), null);
            ThreadPool.QueueUserWorkItem(new WaitCallback((new ThreadExam2()).Print2), null);

            for (int i = 0; i != 10; ++i)
            {
                Console.WriteLine("main: {0}", i);
                Thread.Sleep(100);
            }

            while (true) { }
        }
    }
}
