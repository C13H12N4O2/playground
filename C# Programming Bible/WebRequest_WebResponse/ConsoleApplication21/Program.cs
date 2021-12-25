using System;
using System.Net;

namespace ConsoleApplication21
{
    class Program
    {
        static void Main(string[] args)
        {
            Uri uri = new Uri("https://www.pixiv.net/ajax/user/14866303/profile/all");
            WebRequest request = WebRequest.Create(uri);
            Console.WriteLine("request.ToString() : " + request.ToString());
            Console.WriteLine("request.ConnectionGroupName : " + request.ConnectionGroupName);
            Console.WriteLine("request.Headers : " + request.Headers);
            Console.WriteLine("request.Credentials : " + request.Credentials);

            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            Console.WriteLine("response.StatusCode : " + response.StatusCode);
            Console.WriteLine("response.StatusDescription : " + response.StatusDescription);
            Console.WriteLine("response.Server : " + response.Server);
            Console.WriteLine("response.ResponseUri : " + response.ResponseUri);
            Console.WriteLine("response.ProtocolVersion : " + response.ProtocolVersion);
            Console.WriteLine("response.SupportsHeaders : " + response.SupportsHeaders);
            Console.WriteLine("response.Headers : " + response.Headers);
            Console.WriteLine("response.ContentEncoding : " + response.ContentEncoding);
            Console.WriteLine("response.Cookies : " + response.Cookies);
            Console.WriteLine("response.Cookies.Count : " + response.Cookies.Count);
            Console.WriteLine("response.Method : " + response.Method);

            while (true) { }
        }
    }
}
