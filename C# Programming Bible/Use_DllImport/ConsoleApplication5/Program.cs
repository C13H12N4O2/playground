using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ConsoleApplication5
{
    class Program
    {
        [DllImport("User32.dll")]
        public static extern int MessageBox(int hWnd, string lpText, string lpCaption, int uType);
        static void Main(string[] args)
        {
            MessageBox(0, "Win32 MessageBox 호출", "DllImport 사용하기", 3);
        }
    }
}
