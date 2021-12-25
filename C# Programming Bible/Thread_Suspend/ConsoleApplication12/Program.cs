using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApplication12
{
    class Program
    {
        public static void Print()
        {
            try
            {
                for (int i = 0; i != 1000; ++i)
                {
                    Console.WriteLine("Print 스레드: {0}", i);
                }
            }
            catch (ThreadAbortException ex)
            {
                Console.WriteLine("스레드 에러: " + ex.Message);
            }
        }

        public static void TInfo(Thread th)
        {
            Console.WriteLine("Thread ID: {0}\t 상태: {1}",
                th.GetHashCode(), th.ThreadState);
        }

        public static void Main()
        {
            string msg = null;

            Thread th = new Thread(new ThreadStart(Print));
            TInfo(th);

            th.Start();
            Thread.Sleep(100);
            TInfo(th);

            th.Suspend();
            Thread.Sleep(100);

            msg = "Thread ID: " + th.GetHashCode() + "\t 상태: "
                + th.ThreadState.ToString();
            System.Windows.Forms.MessageBox.Show(msg);

            th.Resume();
            Thread.Sleep(100);

            msg = "Thread ID: " + th.GetHashCode() + "\t 상태: "
                + th.ThreadState.ToString();
            System.Windows.Forms.MessageBox.Show(msg);

            th.Abort();
            th.Join();

            TInfo(th);
        }
    }
}
