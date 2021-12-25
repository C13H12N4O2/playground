using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;

namespace ConsoleApplication10
{
    class ProcessInfo
    {
        static void Main(string[] args)
        {
            try
            {
                Process proc = Process.GetCurrentProcess();
                string processName = proc.ProcessName;
                DateTime startTime = proc.StartTime;
                int proID = proc.Id;
                long memory = proc.VirtualMemorySize64;
                Console.WriteLine("Process: {0}\n ID: {1}\n 시작 시간: {2}\n 메모리: {3}\n",
                    processName, proID, startTime, memory);

                Process[] allProc = Process.GetProcesses();
                Console.WriteLine("시스템에서 실행 중인 프로세스의 수: {0}", allProc.Length);
                int index = 1;
                foreach (Process pro in allProc)
                {
                    Console.WriteLine("***** {0} 번째 프로세스 *****", index++);
                    processName = pro.ProcessName;
                    // startTime = pro.StartTime;
                    proID = pro.Id;
                    memory = pro.VirtualMemorySize64;

                    Console.WriteLine("Process: {0}\n ID: {1}\n 시작 시간: {2}\n 메모리: {3}\n",
                        processName, proID, startTime, memory);
                }
            }
            catch (UnauthorizedAccessException e)
            {
                Console.WriteLine(e);
            }
            catch (Exception e)
            {
                Console.WriteLine("예외 발생");
                Console.WriteLine(e.Message);
                Console.WriteLine(e.StackTrace);
                Console.WriteLine(e.Data);
            }

            while (true) { }
        }
    }
}
