using System;
using System.Net;

namespace ConsoleApplication18
{
    class IpInfo
    {
        static void Main(string[] args)
        {
            Console.Write(" 주소를 입력 하세요 -> ");
            string str = Console.ReadLine();
            IPAddress[] host = Dns.GetHostAddresses(str);
            Console.WriteLine(" IP 주소 리스트: ");
            for (int i = 0; i != host.Length; ++i)
            {
                IPAddress ip = host[i];
                Console.WriteLine("[{0}]", ip.ToString());
            }

            while (true) { }
        }
    }
}
