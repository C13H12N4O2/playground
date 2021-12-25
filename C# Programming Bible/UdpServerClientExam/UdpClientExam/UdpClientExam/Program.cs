using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace UdpClientExam
{
    class Program
    {
        static void Main(string[] args)
        {
            byte[] data = new byte[1024];

            UdpClient server = new UdpClient("127.0.0.1", 9009);
            Console.WriteLine("UDP 서버 접속 성공..");

            IPEndPoint ipe = new IPEndPoint(IPAddress.Any, 0);

            data = Encoding.Default.GetBytes("Hello UdpClient !");
            server.Send(data, data.Length);

            for (int i = 0; i != 10; ++i)
            {
                data = server.Receive(ref ipe);
                Console.WriteLine(Encoding.Default.GetString(data));
            }
            server.Close();

            while (true) { }
        }
    }
}
