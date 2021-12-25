using System;
using System.Net;

namespace ConsoleApplication16
{
    class IpTest
    {
        static void Main(string[] args)
        {
            IPAddress ex1 = IPAddress.Parse("207.46.156.156");
            IPAddress ex2 = IPAddress.Any;
            IPAddress ex3 = IPAddress.Broadcast;
            IPAddress ex4 = IPAddress.Loopback;
            IPAddress ex5 = IPAddress.None;

            Console.WriteLine("{0} = {1}", "ex1", ex1);
            Console.WriteLine("{0} = {1}", "ex2(Any)", ex2);
            Console.WriteLine("{0} = {1}", "ex3(Broadcast)", ex3);
            Console.WriteLine("{0} = {1}", "ex4(Loopback)", ex4);
            Console.WriteLine("{0} = {1}", "ex5(None)", ex5);

            while (true) { }
        }
    }
}
