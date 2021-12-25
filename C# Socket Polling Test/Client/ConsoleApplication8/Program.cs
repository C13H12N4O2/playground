using System;
using System.Net;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace Client
{
    class Program
    {
        const int MAX_BYTE_SIZE = 1024;

        static void Main(string[] args)
        {
            byte[] data = new byte[MAX_BYTE_SIZE];
            IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 9050);
            Socket sock = new Socket(AddressFamily.InterNetwork,
                                     SocketType.Stream,
                                     ProtocolType.Tcp);

            sock.Connect(ipep);

            while (true)
            {
                var str = Console.ReadLine();
                data = Encoding.ASCII.GetBytes(str);
                sock.Send(data);
            }
        }
    }
}
