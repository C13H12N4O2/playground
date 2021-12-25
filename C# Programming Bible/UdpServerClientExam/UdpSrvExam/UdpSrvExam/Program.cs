﻿using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace UdpSrvExam
{
    class Program
    {
        static void Main(string[] args)
        {
            byte[] data = new byte[1024];
            IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 9009);
            UdpClient server = new UdpClient(ipep);

            Console.WriteLine("UDP 서버 실행 중");

            IPEndPoint ipe = new IPEndPoint(IPAddress.Any, 0);

            data = server.Receive(ref ipe);

            string msg = Encoding.Default.GetString(data);

            Console.WriteLine("{0}에서 보낸 데이터: {1}", ipe.ToString(), msg);

            for (int i = 0; i != 10; ++i)
            {
                data = Encoding.Default.GetBytes("Send data :[" + i + "]");
                server.Send(data, data.Length, ipe);
            }
            server.Close();

            while (true) { }
        }
    }
}
