using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApplication13
{
    class Program
    {
        public static void Print1()
        {
            Console.WriteLine("Print1 스레드 *");
        }
        public static void Print2()
        {
            Console.WriteLine("Print2 스레드 **");
        }
        public static void Print3()
        {
            Console.WriteLine("Print3 스레드 ***");
        }
        public static void Print4()
        {
            Console.WriteLine("Print4 스레드 ****");
        }
        public static void Print5()
        {
            Console.WriteLine("Print5 스레드 *****");
        }
        static void Main(string[] args)
        {
            Thread th1 = new Thread(new ThreadStart(Print1));
            Thread th2 = new Thread(new ThreadStart(Print2));
            Thread th3 = new Thread(new ThreadStart(Print3));
            Thread th4 = new Thread(new ThreadStart(Print4));
            Thread th5 = new Thread(new ThreadStart(Print5));

            th1.Priority = ThreadPriority.Highest;
            th5.Priority = ThreadPriority.Lowest;

            Console.WriteLine("th1 priority: {0}", th1.Priority);
            Console.WriteLine("th2 priority: {0}", th2.Priority);
            Console.WriteLine("th3 priority: {0}", th3.Priority);
            Console.WriteLine("th4 priority: {0}", th4.Priority);
            Console.WriteLine("th5 priority: {0}", th5.Priority);

            th2.Start();
            th5.Start();
            th3.Start();
            th4.Start();
            th1.Start();

            while (true) { }
        }
    }
}
