using System;
using System.Net;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace Server
{
    class Program
    {
        const int MAX_BYTE_SIZE = 1024;
        static Queue<int> queue = new Queue<int>();
        static Random rand = new Random();

        static void Main(string[] args)
        {
            int recv;
            byte[] data = new byte[MAX_BYTE_SIZE];
            IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 9050);
            Socket sock = new Socket(AddressFamily.InterNetwork,
                                     SocketType.Stream,
                                     ProtocolType.Tcp);

            sock.Bind(ipep);
            sock.Listen(10);

            Console.WriteLine("Waiting for a client...");

            run();

            bool result = false;
            int i = 0;

            while (!result)
            {
                ++i;

                Console.WriteLine("Polling for accpet #{0}...", i);

                result = sock.Poll(1000000, SelectMode.SelectRead);
            }

            Socket client = sock.Accept();
            IPEndPoint clientIpep = client.RemoteEndPoint as IPEndPoint;

            Console.WriteLine("Connected with {0} at port {1}", clientIpep, clientIpep.Port);

            string str = "Welcome to my test server";
            data = Encoding.ASCII.GetBytes(str);
            client.Send(data, data.Length, SocketFlags.None);

            i = 0;
            while (true)
            {
                str = "";
                Console.WriteLine("Polling for recieve #{0}...", i++);

                result = client.Poll(3000000, SelectMode.SelectRead);

                if (result)
                {
                    i = 0;
                    data = new byte[MAX_BYTE_SIZE];
                    recv = client.Receive(data);

                    if (recv == 0)
                        break;

                    lock (queue)
                    {
                        str += "[읽기] Queue: [ ";
                        while (queue.Count > 0)
                        {
                            str += queue.Dequeue() + " ";
                        }
                        str += "]";
                        Console.WriteLine(str);
                    }
                }
            }

            Console.WriteLine("Disconnected from {0}", clientIpep.Address);

            client.Close();
            sock.Close();
        }

        static async void run()
        {
            while (true)
            {
                await Task.Run(() => Print());
                await Task.Run(() => Add());
                Thread.Sleep(1000);
            }
        }

        static async void add()
        {
            await Task.Run(() => Add());
        }

        static void Print()
        {
            lock (queue)
            {
                string str = "[목록] Queue: [ ";
                foreach (var item in queue.ToList())
                    str += item + " ";
                str += "]";
                Console.WriteLine(str);
            }
        }

        static void Add()
        {
            lock (queue)
            {
                if (queue.Count < 10)
                    queue.Enqueue(rand.Next(0, 100));
                Thread.Sleep(100);
            }
        }
    }
}
