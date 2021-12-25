using System;
using System.Net;

namespace DownloadFileExam
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("읽어올 웹페이지를 입력하세요 >> ");
            string adr = Console.ReadLine();
            Console.WriteLine("저장 파일 이름을 입력하세요 >> ");
            string fileName = Console.ReadLine();

            WebClient wc = new WebClient();
            wc.DownloadFile(adr, fileName);

            Console.WriteLine("파일 다운로드 완료");
            
            ConsoleKeyInfo c;
            do
            {
                c = Console.ReadKey();
            }
            while (c.KeyChar == 'q');
        }
    }
}
