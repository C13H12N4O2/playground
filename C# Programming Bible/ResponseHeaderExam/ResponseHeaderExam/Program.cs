using System;
using System.Net;
using System.Collections.Specialized;

namespace ResponseHeaderExam
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("웹페이지 주소를 입력하세요 >> ");
            string adr = Console.ReadLine();

            WebClient wc = new WebClient();
            byte[] data = wc.DownloadData(adr);
            WebHeaderCollection whc = wc.ResponseHeaders;

            Console.WriteLine(adr + " 페이지 HTTP 정보 출력");
            Console.WriteLine("헤더 정보 개수 : " + whc.Count);
            for (int i = 0; i != whc.Count; ++i)
                Console.WriteLine("{0} = {1}", whc.GetKey(i), whc.Get(i));

            ConsoleKeyInfo c;

            do
            {
                c = Console.ReadKey();
            }
            while (c.KeyChar == 'q');
        }
    }
}
