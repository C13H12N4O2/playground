using System;
using System.Net;
using System.Text;

namespace DownloadDataExam
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("읽어올 웹 페이지 주소를 입력하세요. >> ");
            StringBuilder path = new StringBuilder(Console.ReadLine());
            string str = path.ToString(0, 4);
            if (str != "http")
                path.Insert(0, "http://");
            WebClient wc = new WebClient();
            byte[] data = wc.DownloadData(path.ToString().Trim());
            Console.WriteLine(Encoding.Default.GetString(data));

            ConsoleKeyInfo c;
            do
            {
                c = Console.ReadKey();
            } while (c.KeyChar == 'q');
        }
    }
}
