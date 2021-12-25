using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Net;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = "https://m.stock.naver.com/sise/siseList.nhn?menu=market_sum&sosok=0";
            WebClient wc = new WebClient();
            byte[] data = wc.DownloadData(path.Trim());
            string str = Encoding.UTF8.GetString(data);
            Console.WriteLine(str);
            // MatchCollection matches = Regex.Matches(str, "<script.*?>(.*?)<\\/script>");
            // MatchCollection matches = Regex.Matches(str, @"jsonData = {.*}", RegexOptions.Multiline);
            MatchCollection matches = Regex.Matches(str, @"jsonData = {.*}", RegexOptions.Multiline);
            foreach (var item in matches)
                Console.WriteLine(item);

            string pattern = "[a-z]+";
            string input = "Abc1234Def5678Ghi9012Jklm";
            string[] result = Regex.Split(input, pattern, RegexOptions.IgnoreCase, TimeSpan.FromMilliseconds(500));
            foreach (var item in result)
                Console.WriteLine(item);

            pattern = @"[\[{"":""}\],]+";
            result = Regex.Split(matches[0].Value, pattern, RegexOptions.IgnoreCase, TimeSpan.FromMilliseconds(500));
            foreach (var item in result)
                Console.WriteLine(item);

            Console.WriteLine("-------------------------------------------");
            matches = Regex.Matches(str, "{\"(.*)\"}", RegexOptions.IgnoreCase, TimeSpan.FromMilliseconds(500));
            foreach (var item in matches)
                Console.WriteLine(item);

            ConsoleKeyInfo c;
            do
            {
                c = Console.ReadKey();
            }
            while (c.KeyChar == 'q');
        }
    }
}
