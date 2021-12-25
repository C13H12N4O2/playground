using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading.Tasks;

namespace ConsoleApplication11
{
    class ThreadInfo
    {
        static void Main(string[] args)
        {
            Process proc = Process.GetCurrentProcess();
            ProcessThreadCollection ths = proc.Threads;

            int threadID;
            DateTime startTime;
            int priority;
            ThreadState thstate;

            int index = 1;

            Console.WriteLine("현재 프로세스에서 실행 중인 스레드 수: ", ths.Count);

            foreach (ProcessThread pth in ths)
            {
                threadID = pth.Id;
                startTime = pth.StartTime;
                priority = pth.BasePriority;
                thstate = pth.ThreadState;

                Console.WriteLine("***** {0} 스레드 정보 *****", index++);
                Console.WriteLine("ID: {0}\n 시작 시간: {1}\n Priority: {2}\n 스레드 상태: {3}\n",
                    threadID, startTime, priority, thstate);
            }

            while (true) { }
        }
    }
}
